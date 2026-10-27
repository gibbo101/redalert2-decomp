#!/usr/bin/env python3
"""Audit accepted original-target intervals against source, COFF and frozen bounds.
No compilation or original-code execution. Equality does not certify Ghidra bounds.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import time

import capstone
import pefile
from coff import Coff

TARGET_SHA256 = 'e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
TARGET_BYTES = 4485392


def require(condition, reason):
    if not condition:
        raise ValueError(reason)


class Audit:
    def __init__(self, repository, executable):
        self.repository = repository
        self.blobs = {}
        self.documents = {}
        self.coffs = {}
        self.validated_objects = set()
        raw = self.read(executable)
        require(len(raw) == TARGET_BYTES and self.sha(raw) == TARGET_SHA256, 'Wrong supplied executable')
        self.pe = pefile.PE(data=raw)
        self.base = self.pe.OPTIONAL_HEADER.ImageBase
        self.decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        self.decoder.detail = True

    def path(self, path):
        path = Path(path)
        return path if path.is_absolute() else self.repository / path

    @staticmethod
    def sha(data):
        return hashlib.sha256(data).hexdigest()

    def read(self, path, expected=None):
        path = self.path(path)
        if path not in self.blobs:
            self.blobs[path] = path.read_bytes()
        data = self.blobs[path]
        require(expected is None or self.sha(data) == expected, 'Hash drift: ' + str(path))
        return data

    def document(self, path, expected=None):
        raw = self.read(path, expected)
        key = self.path(path)
        if key not in self.documents:
            self.documents[key] = json.loads(raw)
        return self.documents[key]

    def original(self, va, count):
        require(count > 0 and va >= self.base, 'Invalid original range')
        section = self.pe.get_section_by_rva(va - self.base)
        require(section is not None, 'Original range outside image sections')
        require(va - self.base + count <= section.VirtualAddress + section.SizeOfRawData, 'Original range outside initialized section backing')
        data = self.pe.get_data(va - self.base, count)
        require(len(data) == count, 'Short original range')
        return data

    def population(self, manifest):
        require('original_manifest' in manifest, 'Missing candidate-population provenance')
        require(manifest.get('original_manifest_sha256') and manifest.get('report_sha256'), 'Missing frozen population/report identity')
        population = self.document(manifest['original_manifest'], manifest['original_manifest_sha256'])
        report = self.document(manifest['report'], manifest.get('report_sha256'))
        require(report['manifest_sha256'] == self.sha(self.read(manifest['original_manifest'])), 'Compiler report population differs')
        aggregate = self.read(report['source'], report['source_sha256'])
        require(aggregate == '\n'.join(self.read(c['source'], c['source_sha256']).decode() for c in population['candidates']).encode(), 'Compiler aggregate source differs from frozen candidates')
        cases = {(r['method'], r['variant']): r for r in report['results'] if 'method' in r}
        require('inventory' in population and 'inventory_sha256' in population, 'Missing independent inventory identity')
        inventory = self.read(population['inventory'], population['inventory_sha256'])
        inventory_rows = [json.loads(line) for line in inventory.splitlines() if line.strip()]
        by_entry = {int(r['entry'], 16): r for r in inventory_rows}
        require(len(by_entry) == len(inventory_rows), 'Duplicate independent inventory entries')
        gaps_path = self.path(population['inventory']).parent / 'unassigned-executable.jsonl'
        gaps = self.read(gaps_path, population['gap_inventory_sha256'])
        by_gap = {int(r['start'], 16): r for r in map(json.loads, gaps.splitlines())}
        candidates = {c['method']: c for c in population['candidates']}
        require(len(candidates) == len(population['candidates']), 'Duplicate candidate methods')
        require(len(cases) == sum('method' in r for r in report['results']), 'Duplicate compiler cases')
        # Aggregate compiler objects may contain other candidates, including misses;
        # every nonempty allocatable code section must belong to this frozen population.
        return candidates, by_entry, by_gap, cases, manifest['original_manifest_sha256']

    def audit(self, manifest_path):
        manifest = self.document(manifest_path)
        require(manifest.get('executable_sha256') == TARGET_SHA256, 'Manifest executable identity differs')
        result = []
        populations = {}
        cursor = 0
        for row in sorted(manifest['accepted'], key=lambda r: r['entry']):
            va = row['entry']
            require(va >= cursor, 'Overlapping accepted extents')
            owner = row.get('accepted_batch_manifest', str(manifest_path))
            if owner not in populations:
                populations[owner] = self.population(self.document(owner))
            candidates, inventory, gaps, cases, population_hash = populations[owner]
            candidate = candidates.get(row['method'])
            require(candidate is not None, 'Accepted interval absent from frozen candidate population')
            require(row['symbol_prefix'] == candidate['symbol_prefix'] and row.get('references', {}) == candidate.get('references', {}), 'Accepted symbol selector/reference bindings differ from frozen candidate')
            require(row['padding_provenance'] == candidate['padding_provenance'], 'Accepted padding provenance differs')
            case = cases.get((row['method'], row['variant']))
            require(case is not None and case['status'] == 'extent-exact', 'Missing exact compiler case')
            require(case['source_sha256'] == row['source_sha256'] and case['object_sha256'] == row['object_sha256'] and case['options'] == row['options'], 'Compiler case provenance differs')
            require(candidate['entry'] == va and row['original_bound'] == candidate['original_inventory_row'] == inventory.get(va), 'Independent bound provenance differs')
            bound = inventory[va]
            require(len(bound['ranges']) == 1 and int(bound['ranges'][0]['start'], 16) == va, 'Noncontiguous/nonentry accepted bound')
            body_size = int(bound['ranges'][0]['end_inclusive'], 16) + 1 - va
            require(body_size == row['body_bytes'] == candidate['body_bytes'], 'Source-body accounting differs from frozen inventory')
            body = self.original(va, body_size)
            require(self.sha(body) == row['body_sha256'] == candidate['body_sha256'], 'Original body fingerprint differs')
            require(bytes.fromhex(bound['ranges'][0]['bytes_hex']) == body, 'Inventory body bytes differ')
            instructions = list(self.decoder.disasm(body, va))
            require(sum(i.size for i in instructions) == body_size, 'Incomplete original body decoding')
            padding = bytes.fromhex(row['padding_hex'])
            require(padding == bytes.fromhex(candidate['padding_hex']) and len(padding) == row['padding_bytes'], 'Padding accounting differs')
            if padding:
                require(len(padding) <= 15 and padding == b'\x90' * len(padding), 'Unsupported frozen padding')
                require(candidate['padding_provenance'] == gaps.get(va + body_size), 'Padding not from independent gap inventory')
                require(gaps[va + body_size]['length'] == len(padding), 'Partial inferred gap padding')
            expected = self.original(va, body_size + len(padding))
            require(expected == body + padding and self.sha(expected) == candidate['region_sha256'], 'Original full region differs')
            require(len(expected) == row['full_extent_bytes'] == candidate['region_bytes'], 'Full extent accounting differs')
            self.read(row['source'], row['source_sha256'])
            require(row['source_sha256'] == candidate['source_sha256'], 'Source outside frozen population')
            obj_path = self.path(row['object'])
            obj = self.read(obj_path, row['object_sha256'])
            if obj_path not in self.coffs:
                self.coffs[obj_path] = Coff(obj)
            validation_key = (obj_path, population_hash)
            if validation_key not in self.validated_objects:
                coff = self.coffs[obj_path]
                mapped = {}
                for c in candidates.values():
                    symbol, section, first, last = coff.function(c['symbol_prefix'])
                    mapped.setdefault(symbol['section'], []).append((first, last))
                for index, section in enumerate(coff.sections, 1):
                    if not section['size']:
                        continue
                    if section['name'] == '.drectve':
                        require(not section['flags'] & 0xe00000e0 and section['flags'] & 0xa00 == 0xa00, 'Invalid directive metadata flags')
                        continue
                    if section['name'] in ('.debug$F', '.debug$S', '.debug$T'):
                        require(not section['flags'] & 0xa00000a0 and section['flags'] & 0x42000040 == 0x42000040, 'Invalid debug metadata flags')
                        continue
                    require(not section['flags'] & 0xc0, 'Unsupported allocatable data section')
                    require(section['flags'] & 0x20, 'Unsupported nonmetadata section classification')
                    if section['flags'] & 0x20:
                        intervals = sorted(mapped.get(index, []))
                        covered = 0
                        for first, last in intervals:
                            require(first == covered, 'Unaccounted/overlapping emitted code bytes')
                            covered = last
                        require(covered == len(section['data']), 'Unaccounted emitted code section bytes')
                self.validated_objects.add(validation_key)
            coff = self.coffs[obj_path]
            symbol, section, start, end = coff.function(row['symbol_prefix'])
            require(row['symbol'] == symbol['name'] and row['section_index'] == symbol['section'] and row['section_start'] == start and row['section_end'] == end, 'Recorded compiler section selector differs')
            raw = section['data'][start:end]
            if row.get('raw_section_sha256'):
                require(self.sha(raw) == row['raw_section_sha256'], 'Raw compiler-section fingerprint differs')
            actual = bytearray(raw)
            bindings = []
            for offset, symbol_index, kind in section['relocs']:
                if not start <= offset < end:
                    continue
                offset -= start
                require(offset + 4 <= len(actual) and kind in (6, 20), 'Unsupported/cross-extent relocation')
                target_symbol = coff.symbols[symbol_index]
                require(target_symbol['section'] != 0 or target_symbol['value'] == 0, 'Unsupported common symbol')
                matches = [value for name, value in row.get('references', {}).items() if target_symbol['name'] == name or name.startswith('?') and target_symbol['name'].startswith(name)]
                require(len(matches) == 1, 'Unbound/ambiguous original reference')
                target = matches[0]
                if target_symbol['section'] == -1:
                    require(target_symbol['value'] == target, 'Absolute symbol was rebound')
                elif target_symbol['section'] > 0:
                    peers = [c for c in candidates.values() if target_symbol['name'].startswith(c['symbol_prefix']) and c['entry'] == target]
                    require(len(peers) == 1, 'Unsupported local symbol binding')
                else:
                    require(target_symbol['section'] == 0, 'Unsupported symbol section kind')
                addend = struct.unpack_from('<I', actual, offset)[0]
                value = (target + addend - (va + offset + 4 if kind == 20 else 0)) & 0xffffffff
                if kind == 20:
                    sites = [i for i in instructions if i.address + i.imm_offset == va + offset and i.imm_size == 4 and i.mnemonic in ('call', 'jmp')]
                    require(len(sites) == 1 and sites[0].operands[0].type == capstone.x86_const.X86_OP_IMM and sites[0].operands[0].imm == target, 'Original direct call/jump reference differs')
                else:
                    sites = [i for i in instructions if (i.address + i.imm_offset == va + offset and i.imm_size == 4) or (i.address + i.disp_offset == va + offset and i.disp_size == 4)]
                    require(len(sites) == 1, 'DIR32 not at original operand boundary')
                    operand_values = [o.imm & 0xffffffff for o in sites[0].operands if o.type == capstone.x86_const.X86_OP_IMM]
                    operand_values += [o.mem.disp & 0xffffffff for o in sites[0].operands if o.type == capstone.x86_const.X86_OP_MEM]
                    require(value in operand_values and self.pe.get_section_by_rva(target - self.base) is not None, 'Original DIR32 operand/section binding differs')
                struct.pack_into('<I', actual, offset, value)
                bindings.append(dict(offset=offset, kind=kind, symbol=target_symbol['name'], target=target, addend=addend, resolved=value))
            require(bindings == row.get('relocations', []), 'Relocation receipt differs')
            require(bytes(actual) == expected and self.sha(actual) == row['full_extent_sha256'], 'Complete compiler extent differs')
            cursor = va + len(actual)
            result.append(dict(entry=va, body_bytes=body_size, padding_bytes=len(padding), full_extent_bytes=len(actual), boundary_confidence='Frozen independent analysis hypothesis; byte equality verified'))
        require(len(result) == manifest.get('matched_source_regions', manifest.get('unique_functions', len(result))), 'Manifest source-region count differs')
        totals = dict(matched_source_regions=len(result), body_bytes=sum(r['body_bytes'] for r in result), padding_bytes=sum(r['padding_bytes'] for r in result), full_extent_bytes=sum(r['full_extent_bytes'] for r in result))
        for field, reported in [('body_bytes', 'body_bytes'), ('padding_bytes', 'frozen_padding_bytes'), ('full_extent_bytes', 'full_extent_bytes')]:
            require(totals[field] == manifest[reported], 'Manifest total differs: ' + field)
        return dict(status='verified-exact-intervals-and-provenance', manifest=str(self.path(manifest_path)), manifest_sha256=self.sha(self.read(manifest_path)), executable_sha256=TARGET_SHA256, **totals, source_function_boundaries_certified=False, regions=result)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--manifest', required=True)
    parser.add_argument('--exe', required=True)
    parser.add_argument('--report', type=Path, required=True)
    parser.add_argument('--repository', type=Path, default=Path(__file__).resolve().parents[2])
    args = parser.parse_args()
    started = time.monotonic()
    result = Audit(args.repository, args.exe).audit(args.manifest)
    result['seconds'] = time.monotonic() - started
    result['verifier_sha256'] = hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
    result['coff_reader_sha256'] = hashlib.sha256(Path(__file__).with_name('coff.py').read_bytes()).hexdigest()
    args.report.write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps({k: v for k, v in result.items() if k != 'regions'}))


if __name__ == '__main__':
    main()
