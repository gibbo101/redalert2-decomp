#!/usr/bin/env python3
"""Audit accepted original-target intervals against source, COFF and frozen bounds.
No compilation or original-code execution. Equality does not certify Ghidra bounds.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re
import struct
import time

import capstone
import pefile
from coff import Coff
from compiler_output import classify

COMPILER_STATIC_NAME = re.compile(r'_\$E\d+')

TARGET_SHA256 = 'e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
TARGET_BYTES = 4485392
# MSVC RTTI structures (/GR): type descriptor, base class descriptor, base
# class array, class hierarchy descriptor, complete object locator.
RTTI_STRUCTURES = ('??_R0', '??_R1', '??_R2', '??_R3', '??_R4')


def require(condition, reason):
    if not condition:
        raise ValueError(reason)


def extent_difference(actual, expected, va):
    """Where a fresh extent first differs from the original (for the refusal
    message): offset, both lengths and a few bytes from each side."""
    actual, expected = bytes(actual), bytes(expected)
    first = next((i for i, (a, b) in enumerate(zip(actual, expected)) if a != b), min(len(actual), len(expected)))
    if actual == expected:
        return ' (bytes equal; recorded extent fingerprint differs)'
    return ' at %08x+%x (fresh %d bytes, original %d; fresh %s, original %s)' % (
        va, first, len(actual), len(expected), actual[first:first + 8].hex(), expected[first:first + 8].hex())


def longest_prefix_binding(references, name):
    """The address a symbol-prefix binding gives `name`, or None.

    A plan may bind a whole overload family by prefix (`?Remove@ListClass@@`);
    the longest matching prefix wins, and two equally long prefixes that bind
    different addresses are ambiguous, so nothing binds.
    """
    matches = [(len(n), v) for n, v in references.items() if n.startswith('?') and name.startswith(n)]
    if not matches:
        return None
    longest = max(length for length, _ in matches)
    values = {v for length, v in matches if length == longest}
    return values.pop() if len(values) == 1 else None


def prefix_bound_values(references, name):
    """Addresses `references` binds to symbol `name`: its exact entry plus every
    entry for a '?'-prefix of it. The same set as testing each binding n with
    `name == n or (n.startswith('?') and name.startswith(n))`, found by looking
    up the name's own prefixes instead of scanning the whole table."""
    values = {references[name]} if name in references else set()
    if name.startswith('?'):
        for length in range(1, len(name)):
            if name[:length] in references:
                values.add(references[name[:length]])
    return values


def switch_data_start(decoder, body, va):
    """Offset where trailing switch data begins in an original body, or None.

    VC6 places a switch's jump table (and byte index table) directly after the
    function's code. Such data counts as part of the body only when the code
    itself indexes it: a `jmp [reg*4 + X]` or an indexed byte load
    `mov r8, [reg + X]` whose X lies inside the body. Code is decoded
    linearly from the entry and stops at the lowest such table address.
    """
    limit, position, tables = len(body), 0, []
    while position < limit:
        insn = next(decoder.disasm(body[position:limit], va + position, 1), None)
        if insn is None:
            return None
        for operand in insn.operands:
            if operand.type != capstone.x86_const.X86_OP_MEM or not operand.mem.index:
                continue
            target = operand.mem.disp & 0xffffffff
            indexed = (insn.mnemonic == 'jmp' and operand.mem.scale == 4) or \
                (insn.mnemonic in ('mov', 'movzx') and operand.size == 1)
            if indexed and va < target < va + len(body):
                tables.append(target - va)
                limit = min(limit, target - va)
        position += insn.size
    return min(tables) if tables and position == limit else None


def local_label_target(coff, symbol, section_index, start, end, va):
    """Original address of a compiler-local label inside the same function.

    `$L` labels (switch cases and tables) are section-local symbols; inside
    the compared extent they bind to the same relative offset in the original.
    """
    if symbol['section'] == section_index and symbol['storage'] in (3, 6) and start <= symbol['value'] < end:
        return va + symbol['value'] - start
    return None


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

    @staticmethod
    def file_sha256(path):
        """SHA-256 of a file read in chunks (for inputs too large to keep)."""
        digest = hashlib.sha256()
        with Path(path).open('rb') as handle:
            for chunk in iter(lambda: handle.read(1 << 24), b''):
                digest.update(chunk)
        return digest.hexdigest()

    def verify_inputs_unchanged(self, current=None):
        """Require every proof input this run read to be unchanged on disk.

        `blobs` holds the bytes read here; `blob_digests` the SHA-256 of
        inputs read by verification worker processes or streamed (the fresh
        manifest), which are compared by hash. `current` may supply bytes
        just read from disk by another final check, so no file is read twice.
        """
        current = current or {}
        for path, data in self.blobs.items():
            now = current.get(path)
            require((now if now is not None else path.read_bytes()) == data, 'Proof input changed during build: '+str(path))
        for path, digest in getattr(self, 'blob_digests', {}).items():
            now = current.get(path)
            require((self.sha(now) if now is not None else self.file_sha256(path)) == digest,
                    'Proof input changed during build: '+str(path))

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

    def compiler_output(self, owner, candidates, case, coff, inventory, gaps):
        manifest = self.document(owner)
        population = self.document(manifest['original_manifest'])
        if population.get('compiler_output_policy') is None: return []
        report = self.document(manifest['report'])
        from canonical import dependency_headers
        return classify(self, coff, population.get('compiler_output_policy'),
                        list(candidates.values()), case['options'], report['compiler']['compiler'],
                        population['inventory_sha256'], population['gap_inventory_sha256'],
                        dependency_headers(self, list(candidates.values())), (inventory, gaps))

    def original_type_descriptors(self):
        """RTTI type descriptors of the original image: ??_R0 name -> address.

        Every vtable recorded from the original's RTTI
        (manifests/rtti_classes.json) is preceded by its complete object
        locator, whose type descriptor starts with the type_info vtable; all
        of them must agree on it (it is returned as ??_7type_info@@6B@). A
        type descriptor is then a 4-aligned {that vtable, 0, ".?A...@@"} in
        initialized data; its symbol is ??_R0 plus the decorated name after
        the dot plus @8. A name found twice binds nothing. These are only
        name bindings: the audit still compares every emitted descriptor with
        the original bytes at its bound address.
        """
        if hasattr(self, '_type_descriptors'):
            return self._type_descriptors
        word = lambda va: struct.unpack('<I', self.original(va, 4))[0]
        tables = self.document('manifests/rtti_classes.json')['vtables']
        shared = {word(word(word(int(t['vtable'], 16) - 4) + 12)) for t in tables}
        require(len(shared) == 1, 'Original RTTI type descriptors disagree on the type_info vtable')
        type_info = shared.pop()
        needle = struct.pack('<II', type_info, 0)
        found, repeated = {}, set()
        for section in self.pe.sections:
            if section.Characteristics & 0x20 or not section.Characteristics & 0x40:
                continue
            data = section.get_data()[:min(section.SizeOfRawData, section.Misc_VirtualSize)]
            position = data.find(needle)
            while position >= 0:
                end = data.find(b'\0', position + 8)
                name = data[position + 8:end]
                if not position % 4 and end > 0 and name.startswith(b'.?A') and name.endswith(b'@@') and \
                        all(0x20 < c < 0x7f for c in name):
                    symbol = '??_R0' + name[1:].decode() + '@8'
                    if symbol in found:
                        repeated.add(symbol)
                    found[symbol] = self.base + section.VirtualAddress + position
                position = data.find(needle, position + 1)
        for symbol in repeated:
            del found[symbol]
        found['??_7type_info@@6B@'] = type_info
        self._type_descriptors = found
        return found

    def original_vtables(self):
        """Primary vtables of the original by their decorated names, from its RTTI.

        For every vtable recorded in manifests/rtti_classes.json whose
        complete object locator (the word before it) has offset 0, the
        locator's type descriptor holds the class's decorated name
        `.?AV<name>`; the vtable symbol is `??_7<name>6B@`. Each template
        instance has its own decorated name (DynamicVectorClass<T *> and
        DynamicVectorClass<T const *> differ; VectorClass<T *> is another
        class), so each binds to its own original copy. A name found twice
        binds nothing. Returns name -> (vtable, slot 0, COM-derived).
        """
        if hasattr(self, '_original_vtables'):
            return self._original_vtables
        word = lambda va: struct.unpack('<I', self.original(va, 4))[0]
        found, repeated = {}, set()
        for table in self.document('manifests/rtti_classes.json')['vtables']:
            vtable = int(table['vtable'], 16)
            try:
                locator = word(vtable - 4)
                if word(locator + 4):
                    continue        # a secondary vtable (its name carries the base)
                raw = self.original(word(locator + 12) + 8, 256)
            except ValueError:
                continue
            name = raw[:raw.find(b'\0')]
            if not name.startswith((b'.?AV', b'.?AU')) or not name.endswith(b'@@'):
                continue
            symbol = '??_7' + name[4:].decode('ascii', 'replace') + '6B@'
            if symbol in found:
                repeated.add(symbol)
            com = any(b['name'] in ('IUnknown', 'IPersist', 'IPersistStream') for b in table.get('bases', []))
            found[symbol] = (vtable, word(vtable), com)
        for symbol in repeated:
            del found[symbol]
        self._original_vtables = found
        return found

    def rtti_binding(self, name):
        """Original address of a class's primary vtable (`??_7X6B@`) or of
        its deleting destructor (`??_EX`/`??_GX`: slot 0 of that vtable, except
        in COM-derived classes, whose slot 0 is QueryInterface), else None.

        Used only for compiler-emitted COMDAT copies a population's
        references leave unbound; the audit still compares every emitted
        vtable with the original bytes at the bound address."""
        tables = self.original_vtables()
        if name.startswith('??_7') and name.endswith('6B@'):
            row = tables.get(name)
            return row[0] if row else None
        if name.startswith(('??_E', '??_G')) and name.endswith('@@UAEPAXI@Z'):
            row = tables.get('??_7' + name[4:-len('UAEPAXI@Z')] + '6B@')
            return row[1] if row and not row[2] else None
        return None

    def vtable_name_at(self, address):
        """The decorated primary vtable name the original's RTTI gives the
        vtable at `address`, else None (for diagnostics)."""
        for name, row in self.original_vtables().items():
            if row[0] == address:
                return name
        return None

    def merged_references(self, candidates):
        """All reference bindings of a population (one dict per population)."""
        cache = self.__dict__.setdefault('_merged_references', {})
        if id(candidates) not in cache:
            references = {}
            for candidate in candidates.values():
                references.update(candidate.get('references', {}))
            cache[id(candidates)] = (candidates, references)
        return cache[id(candidates)][1]

    def rtti_layout(self, coff, candidates):
        """Original address of every RTTI structure (??_R0-??_R4) the object defines.

        /GR makes VC6 emit, as one COMDAT per structure, the type descriptors,
        base class descriptors and arrays, hierarchy descriptors and complete
        object locators of every class it emits a vtable or a dynamic_cast or
        typeid for, and puts a pointer to the locator in front of each vtable.
        The original linker kept one copy of each. Addresses come only from
        the original: a structure named in the population's references (a
        type descriptor a function's code uses) is bound there; the locator of
        an emitted vtable bound to its original address V is the word the
        original holds at V-4; and every structure another bound structure
        points to is the word the original holds at that pointer's place.
        A structure bound twice to different addresses, or outside the
        original's initialized data, binds nothing. The bound addresses are
        candidates only: original_duplicate still requires every structure's
        relocated bytes to equal the original bytes there, so the complete
        emitted RTTI graph must be isomorphic to the original's.
        """
        cache = self.__dict__.setdefault('_rtti_layouts', {})
        key = (id(coff), id(candidates))
        if key in cache:
            return cache[key][2]
        references = self.merged_references(candidates)
        defined = {s['name']: s for s in coff.symbols.values()
                   if s['storage'] == 2 and s['section'] > 0 and s['name'] in self.rtti_names(coff)}
        bound, conflicts, pending = {}, set(), []

        def data_address(value):
            section = self.pe.get_section_by_rva((value - self.base) & 0xffffffff)
            return section is not None and not section.Characteristics & 0x20 and section.Characteristics & 0x40

        def assign(name, value):
            value &= 0xffffffff
            if name in conflicts:
                return
            if not data_address(value) or bound.get(name, value) != value:
                conflicts.add(name)
                return
            if name not in bound:
                bound[name] = value
                pending.append(name)

        def word(va):
            return struct.unpack('<I', self.original(va, 4))[0]

        for name in defined:
            if name in references:
                assign(name, references[name])
        for index, section in enumerate(coff.sections, 1):
            vtable = self.vtable_with_locator(coff, index, section)
            if vtable is None:
                continue
            address = references.get(vtable) or longest_prefix_binding(references, vtable)
            locator = coff.symbols[next(t for o, t, k in section['relocs'] if o == 0)]['name']
            if address and locator in defined:
                try:
                    assign(locator, word(address - 4) - struct.unpack_from('<I', section['data'], 0)[0])
                except ValueError:
                    conflicts.add(locator)
        while pending:
            name = pending.pop()
            symbol = defined[name]
            section = coff.sections[symbol['section'] - 1]
            if name in conflicts or symbol['value'] or not section['flags'] & 0x1000:
                continue
            for offset, target, kind in section['relocs']:
                target_name = coff.symbols[target]['name']
                if target_name in defined and kind == 6 and offset + 4 <= len(section['data']):
                    try:
                        value = word(bound[name] + offset)
                    except ValueError:
                        conflicts.add(target_name)
                        continue
                    assign(target_name, value - struct.unpack_from('<I', section['data'], offset)[0])
        layout = {name: value for name, value in bound.items() if name not in conflicts}
        cache[key] = (coff, candidates, layout)
        return layout

    def rtti_names(self, coff):
        """External RTTI structure symbols (??_R0-??_R4) the object defines."""
        cache = self.__dict__.setdefault('_rtti_names', {})
        if id(coff) not in cache:
            cache[id(coff)] = (coff, frozenset(s['name'] for s in coff.symbols.values()
                                               if s['storage'] == 2 and s['section'] > 0 and
                                               s['name'].startswith(RTTI_STRUCTURES)))
        return cache[id(coff)][1]

    @staticmethod
    def vtable_with_locator(coff, index, section):
        """The ??_7 name of a /GR vtable COMDAT, else None: one external
        symbol, a vtable name at offset 4, and offset 0 relocated to a
        complete object locator (??_R4)."""
        if not section['flags'] & 0x1000 or section['flags'] & 0x20:
            return None
        defined = [s for s in coff.symbols.values() if s['section'] == index and s['storage'] == 2]
        first = [coff.symbols[t]['name'] for o, t, k in section['relocs'] if o == 0 and k == 6]
        if len(defined) == 1 and defined[0]['value'] == 4 and defined[0]['name'].startswith('??_7') and \
                len(first) == 1 and first[0].startswith('??_R4'):
            return defined[0]['name']
        return None

    def original_duplicate(self, coff, index, section, candidates):
        """A compiler COMDAT that duplicates original bytes exactly.

        Constructors, destructors, inline functions and string literals make VC6 emit
        per-translation-unit COMDAT copies the original linker folded: class
        vtables (`??_7Class@@6B@`, read-only data) and compiler-generated
        functions such as scalar deleting destructors (`??_G...`). Such a
        section is accepted, never transferred and never credited, only when
        its defining symbol is bound to an original address and every
        relocation binds so that the relocated bytes equal the original bytes
        there. Anything else still refuses.
        """
        flags = section['flags']
        if flags & 0x80 and not flags & 0x60:
            return self.zero_fill_duplicate(coff, index, section, candidates)
        if section['name'].startswith('.CRT$XC'):
            return self.initializer_entry(coff, section, candidates)
        if not flags & 0x1000 and flags & 0x40 and not flags & 0x20:
            return self.defined_data_duplicate(coff, index, section, candidates)
        if not flags & 0x1000 or not flags & 0x60:
            return False
        if flags & 0x80000000 and flags & 0x20:
            return False        # writable data is fine (VC6 string literals), writable code is not
        # A compiler-generated static initializer or destructor (`_$E<n>`) is a
        # static (storage 3) code COMDAT; it binds only through an explicit
        # reference, since the name repeats in every unit.
        names = [s['name'] for s in coff.symbols.values()
                 if s['section'] == index and s['value'] == 0 and
                 (s['storage'] == 2 or s['storage'] == 3 and flags & 0x20 and
                  COMPILER_STATIC_NAME.fullmatch(s['name']))]
        # A /GR vtable starts with its locator pointer; its name is at offset 4.
        vtable = self.vtable_with_locator(coff, index, section)
        if vtable is not None:
            names, start = [vtable], 4
        else:
            start = 0
        if len(names) != 1:
            return False
        references = self.merged_references(candidates)
        layout = self.rtti_layout(coff, candidates)
        rtti = self.rtti_names(coff)
        if names[0] in rtti:
            # An RTTI structure binds only through the original's RTTI graph.
            address = layout.get(names[0])
        else:
            address = references.get(names[0])
            if address is None and not COMPILER_STATIC_NAME.fullmatch(names[0]):
                address = longest_prefix_binding(references, names[0])
            if address is None:
                # A vtable no source binds: its own original copy, by the
                # decorated name in the original's RTTI.
                address = self.rtti_binding(names[0]) if names[0].startswith('??_7') else None
        if address is None:
            return False
        address -= start
        data = bytearray(section['data'])
        for offset, symbol_index, kind in section['relocs']:
            target = coff.symbols[symbol_index]; name = target['name']
            if name in rtti:
                matches = [layout[name]] if name in layout else []
            else:
                matches = sorted(prefix_bound_values(references, name))
                if not matches and names[0].startswith('??_7') and self.rtti_binding(name) is not None:
                    matches = [self.rtti_binding(name)]     # a deleting destructor slot
            if not matches and names[0].startswith('??_7') and kind == 6 and target['section'] == 0 \
                    and offset + 4 <= len(data) and not struct.unpack_from('<I', data, offset)[0]:
                # A vtable slot naming a virtual function not recovered yet:
                # the emitted vtable is never transferred, so the slot keeps
                # the original entry, which must be a code address.
                slot = struct.unpack_from('<I', self.original(address + offset, 4))[0]
                code = self.pe.get_section_by_rva((slot - self.base) & 0xffffffff)
                if code is None or not code.Characteristics & 0x20:
                    return False
                struct.pack_into('<I', data, offset, slot)
                continue
            if kind not in (6, 20) or len(matches) != 1 or offset + 4 > len(data):
                return False
            addend = struct.unpack_from('<I', data, offset)[0]
            value = matches[0] + addend - (address + offset + 4 if kind == 20 else 0)
            struct.pack_into('<I', data, offset, value & 0xffffffff)
        try:
            same = bytes(data) == self.original(address, len(data))
        except ValueError:
            return False
        if not same and names[0].startswith('??_7'):
            self.record_vtable_mismatch(names[0], address, start, bytes(data), section, coff)
        if same and (names[0] in rtti or vtable is not None):
            # Recorded in the audit result: each RTTI structure and /GR
            # vtable with the original copy its bytes equal.
            self.__dict__.setdefault('rtti_original_copies', {})[names[0]] = address + start
        return same

    def record_vtable_mismatch(self, name, address, start, data, section, coff):
        """Diagnostic text for an emitted vtable that differs from the
        original at its bound address: which class the original's RTTI says
        is there, where the name's own original copy is, and each differing
        slot with the name the unit binds it to. Only explains a refusal."""
        notes, hint = [], []
        there = self.vtable_name_at(address + start)
        if there and there != name:
            notes.append('the original RTTI names the vtable at %08x %s' % (address + start, there))
        own = self.rtti_binding(name)
        if own is not None and own != address + start:
            notes.append('%s is %08x in the original RTTI' % (name, own))
        original = self.original(address, len(data))
        slots = {offset: coff.symbols[target]['name'] for offset, target, _ in section['relocs']}
        for offset in range(start, len(data) - 3, 4):
            emitted, kept = (struct.unpack_from('<I', d, offset)[0] for d in (data, original))
            if emitted != kept:
                notes.append('+%02x %s bound %08x, original %08x' % (offset - start, slots.get(offset, '?'), emitted, kept))
        if own is not None and own != address + start:
            # The table binds the name to another instance's vtable. When the
            # slots the unit emits are right for this class's own copy, only
            # the bindings are stale: the plan states them (the audit still
            # compares every byte against the copy the RTTI names).
            try:
                right = self.original(own - start, len(data))
            except ValueError:
                right = None
            if right is not None:
                fixes = ['%s=%08x' % (name, own)]
                for offset in range(start, len(data) - 3, 4):
                    emitted, kept = (struct.unpack_from('<I', d, offset)[0] for d in (data, right))
                    if emitted != kept and offset in slots and slots[offset] != name:
                        fixes.append('%s=%08x' % (slots[offset], kept))
                hint = ['try plan bindings: ' + ' '.join('// @ref ' + f for f in fixes)]
        self.__dict__.setdefault('vtable_mismatches', {})[name] = '; '.join(notes[:8] + hint)

    def defined_data_duplicate(self, coff, index, section, candidates):
        """Initialized data a unit defines (a table written out in source).

        Accepted, never transferred, only when every external symbol it
        defines is bound and all of them place the section at one original
        address, the section has no relocations, and its bytes equal the
        original bytes there.
        """
        if section['relocs']:
            return self.relocated_data_duplicate(coff, index, section, candidates)
        defined = [(s['value'], s['name']) for s in coff.symbols.values()
                   if s['section'] == index and (s['storage'] == 2 or
                                                s['storage'] == 3 and not s['name'].startswith('.'))]
        if not defined:
            return False
        references = self.merged_references(candidates)
        bases = {references.get(name, -1) - value for value, name in defined}
        if len(bases) != 1:
            # The unit's constants come from different original places (a
            # function-local static beside header constants in one .rdata):
            # verify each bound symbol at its own address instead.
            return self.relocated_data_duplicate(coff, index, section, candidates)
        address = bases.pop()
        if address < self.base:
            return False
        return bytes(section['data']) == self.original(address, len(section['data']))

    def relocated_data_duplicate(self, coff, index, section, candidates):
        """Initialized data with pointers a unit defines (string-name tables,
        `static char const * const NAME = "...";` section names).

        Accepted, never transferred and never credited, only per symbol:
        every external or named static symbol the section defines is bound by
        @ref to an original address, the symbols tile the section from offset
        0 (each extent runs to the next symbol or the section end), every
        relocation is a 32-bit absolute pointer whose target is bound by name
        (a string literal COMDAT is itself verified as an original duplicate),
        and each symbol's bytes, after resolving its relocations, equal the
        original bytes at its own address. The original copy must lie in an
        initialized, non-executable section (never in accepted code). Partial
        units therefore work: VC6 drops unreferenced statics and the emitted
        layout need not be the original's. Recorded in the audit result under
        data_original_copies.
        """
        if section['flags'] & 0x20 or not section['flags'] & 0x40:
            return False
        defined = sorted((s['value'], s['name']) for s in coff.symbols.values()
                         if s['section'] == index and (s['storage'] == 2 or
                                                       s['storage'] == 3 and not s['name'].startswith('.')))
        if not defined or defined[0][0] != 0 or len({v for v, n in defined}) != len(defined):
            return False
        references = self.merged_references(candidates)
        data = bytes(section['data'])
        relocs = sorted(section['relocs'])
        copies = {}
        for position, (value, name) in enumerate(defined):
            end = defined[position + 1][0] if position + 1 < len(defined) else len(data)
            address = references.get(name)
            if address is None or end <= value:
                return False
            target_section = self.pe.get_section_by_rva((address - self.base) & 0xffffffff)
            if target_section is None or target_section.Characteristics & 0x20000020 or \
                    not target_section.Characteristics & 0x40:
                return False
            piece = bytearray(data[value:end])
            for offset, symbol_index, kind in relocs:
                if not value <= offset < end:
                    continue
                if kind != 6 or offset + 4 > end:
                    return False
                target = coff.symbols[symbol_index]['name']
                bound = references.get(target)
                if bound is None:
                    return False
                addend = struct.unpack_from('<I', piece, offset - value)[0]
                struct.pack_into('<I', piece, offset - value, (bound + addend) & 0xffffffff)
            try:
                if bytes(piece) != self.original(address, len(piece)):
                    return False
            except ValueError:
                return False
            copies[name] = address
        self.__dict__.setdefault('data_original_copies', {}).update(copies)
        return True

    def zero_fill_duplicate(self, coff, index, section, candidates):
        """Uninitialized data: the empty literal "" (a .bss COMDAT) or globals.

        Accepted only when the section carries no relocations and every symbol
        it defines is bound to an original address whose extent (to the next
        symbol or the section end) lies in the zero-filled part (beyond the
        raw data) of a writable original data section.
        """
        if section['relocs']:
            return False
        # External and named static objects (not the section symbol itself).
        defined = sorted((s['value'], s['name']) for s in coff.symbols.values()
                         if s['section'] == index and (s['storage'] == 2 or
                                                      s['storage'] == 3 and not s['name'].startswith('.')))
        if not defined or defined[0][0] != 0:
            return False
        references = self.merged_references(candidates)
        for position, (value, name) in enumerate(defined):
            size = (defined[position + 1][0] if position + 1 < len(defined) else section['size']) - value
            address = references.get(name)
            if address is None or address < self.base or size <= 0:
                return False
            original = self.pe.get_section_by_rva(address - self.base)
            if original is None or not original.Characteristics & 0x80000000 or original.Characteristics & 0x20:
                return False
            start = address - self.base
            if start + size > original.VirtualAddress + original.Misc_VirtualSize:
                return False
            # Beyond the raw data the loader zero-fills; inside it the original
            # bytes themselves must be zero.
            raw_end = original.VirtualAddress + original.SizeOfRawData
            if start < raw_end and self.original(address, min(size, raw_end - start)) != bytes(min(size, raw_end - start)):
                return False
        return True

    def initializer_entry(self, coff, section, candidates):
        """A `.CRT$XC*` section registering dynamic initializers of the unit.

        Accepted when each 4-byte entry is a relocation to an initializer this
        population compiles and the original's initialized data holds the
        whole table (the entries' addresses, in order) exactly once: the
        linker concatenates each object's registrations contiguously.
        """
        if not section['size'] or section['size'] % 4 or len(section['relocs']) != section['size'] // 4:
            return False
        table = bytearray(section['size'])
        for offset, symbol_index, kind in section['relocs']:
            name = coff.symbols[symbol_index]['name']
            entries = [c['entry'] for c in candidates.values() if name == c['symbol_prefix']] or \
                [c['entry'] for c in candidates.values() if name.startswith(c['symbol_prefix'])]
            if kind != 6 or len(entries) != 1 or offset % 4:
                return False
            struct.pack_into('<I', table, offset, entries[0])
        found = 0
        for original in self.pe.sections:
            if not original.Characteristics & 0x20:
                found += original.get_data().count(bytes(table))
        return found == 1

    def kept_elsewhere(self, coff, index, section, candidates):
        """Compiler-generated special functions whose kept copy is elsewhere.

        Every object file that needs a class vtable or an array of objects
        emits its own COMDAT copy of the compiler-generated deleting
        destructor (??_G/??_E) or array iterator (??_H/??_I); the original
        linker kept one copy, often compiled in another file with different
        inlining. Such a section is omitted (never transferred, never
        credited) only when it is a COMDAT code section defining exactly one of
        these manglings and, for deleting destructors, the name or its alias
        is bound to an original address (the kept copy). Each omission is
        recorded in the audit result.
        """
        if not section['flags'] & 0x1000 or not section['flags'] & 0x20:
            return False
        names = [s['name'] for s in coff.symbols.values()
                 if s['section'] == index and s['storage'] == 2 and s['value'] == 0]
        if len(names) != 1:
            return False
        if not names[0].startswith(('??_G', '??_E', '??_H', '??_I')):
            # An inline function or template member instance whose kept copy
            # is another original function (an inline member emitted by every
            # unit that uses it, or a hand-written assembly specialization VC6
            # still instantiates generically): bound to a code address that
            # no candidate of this population claims.
            references = self.merged_references(candidates)
            address = references.get(names[0])
            claimed = {c['entry'] for c in candidates.values()}
            code = self.pe.get_section_by_rva((address - self.base) & 0xffffffff) if address else None
            if address is None or address in claimed or code is None or not code.Characteristics & 0x20:
                return False
        if names[0].startswith(('??_G', '??_E')):
            references = self.merged_references(candidates)
            aliases = {names[0], '??_E' + names[0][4:], '??_G' + names[0][4:]}
            # Bound by the population, or else slot 0 of its class's own
            # original vtable (by decorated name, from the original's RTTI).
            if not any(prefix_bound_values(references, n) for n in aliases) and \
                    self.rtti_binding(names[0]) is None:
                return False
        if not hasattr(self, 'kept_elsewhere_omitted'):
            self.kept_elsewhere_omitted = []
        self.kept_elsewhere_omitted.append(names[0])
        return True

    def audit(self, manifest_path):
        manifest = self.document(manifest_path)
        require(manifest.get('executable_sha256') == TARGET_SHA256, 'Manifest executable identity differs')
        result = []
        populations = {}
        cursor = 0
        for row in sorted(manifest['accepted'], key=lambda r: r['entry']):
            require(row['entry'] >= cursor, 'Overlapping accepted extents')
            result.append(self.audit_row(row, manifest_path, populations))
            cursor = row['entry'] + result[-1]['full_extent_bytes']
        return self.audit_result(manifest_path, manifest, result, self.sha(self.read(manifest_path)))

    def audit_row(self, row, manifest_path, populations):
        """Verify one accepted interval (see verify_row); a refusal names the
        row: entry, method, source and compiler object."""
        try:
            return self.verify_row(row, manifest_path, populations)
        except ValueError as error:
            raise ValueError('%s [row %s %s, source %s, object %s]' % (
                error, '%08X' % row['entry'] if isinstance(row.get('entry'), int) else row.get('entry'),
                row.get('method'), row.get('source'), row.get('object'))) from None

    def verify_row(self, row, manifest_path, populations):
        """Verify one accepted interval completely; return its result row.

        `populations` caches each owner's frozen population for the caller's
        run. Rows are independent apart from the extent-overlap check, which
        the caller makes over all rows in entry order."""
        va = row['entry']
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
        code_size = body_size
        instructions = list(self.decoder.disasm(body, va))
        if sum(i.size for i in instructions) != body_size or row.get('switch_data_bytes'):
            code_size = switch_data_start(self.decoder, body, va)
            require(code_size is not None and body_size - code_size == row.get('switch_data_bytes'),
                    'Incomplete original body decoding')
            instructions = list(self.decoder.disasm(body[:code_size], va))
            require(sum(i.size for i in instructions) == code_size, 'Incomplete original body decoding')
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
                try:
                    symbol, section, first, last = coff.function(c['symbol_prefix'])
                except ValueError:
                    continue    # compiled in another unit of this population
                mapped.setdefault(symbol['section'], []).append((first, last))
            discarded = self.compiler_output(owner, candidates, case, coff, inventory, gaps)
            if not hasattr(self, 'discarded_outputs'): self.discarded_outputs = {}
            self.discarded_outputs[str(obj_path)] = discarded
            for component in discarded:
                mapped.setdefault(component['section_index'], []).append((component['first'], component['last']))
            for index, section in enumerate(coff.sections, 1):
                if not section['size']:
                    continue
                if section['name'] == '.drectve':
                    require(not section['flags'] & 0xe00000e0 and section['flags'] & 0xa00 == 0xa00, 'Invalid directive metadata flags')
                    continue
                if section['name'] in ('.debug$F', '.debug$S', '.debug$T'):
                    require(not section['flags'] & 0xa00000a0 and section['flags'] & 0x42000040 == 0x42000040, 'Invalid debug metadata flags')
                    continue
                if section['flags'] & 0xc0:
                    names = [s['name'] for s in coff.symbols.values() if s['section'] == index][:4]
                    # The condition runs first, so a vtable's mismatch note exists.
                    require(self.original_duplicate(coff, index, section, candidates),
                            'Unsupported allocatable data section %s #%d in %s (%s)%s' % (
                                section['name'], index, obj_path, names,
                                ''.join(': ' + m for m in
                                        [getattr(self, 'vtable_mismatches', {}).get(n) for n in names] if m)))
                    continue
                require(section['flags'] & 0x20, 'Unsupported nonmetadata section classification')
                if section['flags'] & 0x20:
                    if index not in mapped and self.original_duplicate(coff, index, section, candidates):
                        continue
                    if index not in mapped and self.kept_elsewhere(coff, index, section, candidates):
                        continue
                    # Identical intervals are one function claimed by two
                    # candidates with the same symbol (duplicate instantiations).
                    intervals = sorted(set(mapped.get(index, [])))
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
            local = local_label_target(coff, target_symbol, symbol['section'], start, end, va)
            if offset >= code_size:
                # Switch data: only table entries pointing into this function.
                require(kind == 6 and local is not None and va <= local < va + body_size,
                        'Unsupported switch-data relocation at 0x%08X' % va)
            # A common symbol (uninitialized data such as a function-local
            # static) is allowed only when it is bound to an original address.
            require(target_symbol['section'] != 0 or target_symbol['value'] == 0 or
                    target_symbol['name'] in row.get('references', {}), 'Unsupported common symbol')
            matches = [local] if local is not None else sorted(prefix_bound_values(row.get('references', {}), target_symbol['name']))
            require(len(matches) == 1, 'Unbound/ambiguous original reference')
            target = matches[0]
            if local is not None:
                pass
            elif target_symbol['section'] == -1:
                require(target_symbol['value'] == target, 'Absolute symbol was rebound')
            elif target_symbol['section'] > 0:
                peers = [c for c in candidates.values() if target_symbol['name'].startswith(c['symbol_prefix']) and c['entry'] == target]
                # A reference into a verified duplicate of original data or
                # code (an emitted vtable) binds to its original address.
                duplicate = self.original_duplicate(coff, target_symbol['section'],
                                                    coff.sections[target_symbol['section'] - 1], candidates)
                # Or a compiler copy the original linker kept from another
                # object (bound to that kept copy's address).
                kept = not peers and not duplicate and self.kept_elsewhere(
                    coff, target_symbol['section'], coff.sections[target_symbol['section'] - 1], candidates)
                require(len(peers) == 1 or duplicate or kept, 'Unsupported local symbol binding')
            else:
                require(target_symbol['section'] == 0, 'Unsupported symbol section kind')
            addend = struct.unpack_from('<I', actual, offset)[0]
            value = (target + addend - (va + offset + 4 if kind == 20 else 0)) & 0xffffffff
            if offset >= code_size:
                pass        # table entry: the byte comparison below verifies it
            elif kind == 20:
                sites = [i for i in instructions if i.address + i.imm_offset == va + offset and i.imm_size == 4 and i.mnemonic in ('call', 'jmp')]
                require(len(sites) == 1 and sites[0].operands[0].type == capstone.x86_const.X86_OP_IMM and sites[0].operands[0].imm == target, 'Original direct call/jump reference differs at %08x+%x (%s)' % (va, offset, target_symbol['name']))
            else:
                sites = [i for i in instructions if (i.address + i.imm_offset == va + offset and i.imm_size == 4) or (i.address + i.disp_offset == va + offset and i.disp_size == 4)]
                require(len(sites) == 1, 'DIR32 not at original operand boundary at %08x+%x (%s)' % (va, offset, target_symbol['name']))
                operand_values = [o.imm & 0xffffffff for o in sites[0].operands if o.type == capstone.x86_const.X86_OP_IMM]
                operand_values += [o.mem.disp & 0xffffffff for o in sites[0].operands if o.type == capstone.x86_const.X86_OP_MEM]
                require(value in operand_values and self.pe.get_section_by_rva(target - self.base) is not None, 'Original DIR32 operand/section binding differs')
            struct.pack_into('<I', actual, offset, value)
            bindings.append(dict(offset=offset, kind=kind, symbol='$local' if local is not None else target_symbol['name'], target=target, addend=addend, resolved=value))
        require(bindings == row.get('relocations', []), 'Relocation receipt differs at %08x: %s' % (va, [(a, b) for a, b in zip(bindings, row.get('relocations', [])) if a != b][:2] or (len(bindings), len(row.get('relocations', [])))))
        require(bytes(actual) == expected and self.sha(actual) == row['full_extent_sha256'],
                'Complete compiler extent differs' + extent_difference(actual, expected, va))
        return dict(entry=va, body_bytes=body_size, padding_bytes=len(padding), full_extent_bytes=len(actual), boundary_confidence='Frozen independent analysis hypothesis; byte equality verified')

    def audit_result(self, manifest_path, manifest, result, manifest_sha256):
        """The audit report for verified result rows (in entry order)."""
        require(len(result) == manifest.get('matched_source_regions', manifest.get('unique_functions', len(result))), 'Manifest source-region count differs')
        totals = dict(matched_source_regions=len(result), body_bytes=sum(r['body_bytes'] for r in result), padding_bytes=sum(r['padding_bytes'] for r in result), full_extent_bytes=sum(r['full_extent_bytes'] for r in result))
        for field, reported in [('body_bytes', 'body_bytes'), ('padding_bytes', 'frozen_padding_bytes'), ('full_extent_bytes', 'full_extent_bytes')]:
            require(totals[field] == manifest[reported], 'Manifest total differs: ' + field)
        return dict(status='verified-exact-intervals-and-provenance', manifest=str(self.path(manifest_path)), manifest_sha256=manifest_sha256, executable_sha256=TARGET_SHA256, **totals, source_function_boundaries_certified=False, regions=result,
                    discarded_compiler_output=getattr(self, 'discarded_outputs', {}),
                    compiler_generated_kept_elsewhere=sorted(set(getattr(self, 'kept_elsewhere_omitted', []))),
                    **({'rtti_original_copies': {n: '%08x' % a for n, a in sorted(self.rtti_original_copies.items())}}
                       if getattr(self, 'rtti_original_copies', None) else {}),
                    **({'data_original_copies': {n: '%08x' % a for n, a in sorted(self.data_original_copies.items())}}
                       if getattr(self, 'data_original_copies', None) else {}))


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
