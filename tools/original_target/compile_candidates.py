#!/usr/bin/env python3
"""Compile a frozen new-source population; retain misses and strictly audit matches.

This does not install candidates or alter the canonical catalog. Original bounds,
padding and references must be reviewed independently before invoking it.
"""
import argparse
from collections import Counter
import json
from pathlib import Path
import struct
import time

from build import check_toolchain, compile_units, write_json
from verify_manifest import local_label_target, prefix_bound_values, switch_data_start
from canonical import RECORDED_OPTIONS, compiler_arguments, sha, validate_headers, validate_includes
from coff import Coff
from verify_manifest import Audit, require, TARGET_SHA256
import catalog_io

REPOSITORY = Path(__file__).resolve().parents[2]
OPTIONS = [['/O2', '/Ob2', '/G5', '/Gy'], ['/O2', '/Ob2', '/G6', '/Gy'],
           ['/O1', '/Ob2', '/G5', '/Gy']]
# Option sets a plan may name explicitly but that are never tried by default
# (canonical.RECORDED_OPTIONS): /Gr makes __fastcall the default convention
# (the shell code around 0x006F1A00 was compiled that way); /Ob1 expands only
# functions marked inline (the audio event code around 0x00403EB0 was compiled
# that way); /GR enables RTTI for units that use dynamic_cast or typeid (the
# original was built with it; the audit binds every emitted RTTI structure to
# its original copy).
assert all(o in RECORDED_OPTIONS for o in OPTIONS)


def trial_options(population):
    options = population.get('compiler_trial_options', OPTIONS)
    require(isinstance(options, list) and options and
            all(isinstance(o, list) and o in RECORDED_OPTIONS for o in options) and
            len({tuple(o) for o in options}) == len(options),
            'Compiler trial options must be a nonempty unique subset of recorded options')
    return options


def accepted_region_ends(catalog):
    """End addresses (entry + full extent: body, switch data and frozen padding,
    as recorded) of every accepted canonical region."""
    return {r['entry'] + r['full_extent_bytes'] for r in catalog['regions']}


ALIGNMENT_FILLS = (b'\x8d\x64\x24\x00', b'\x8d\x49\x00', b'\x8b\xff')


def aligned_unreferenced_entry(audit, bound, gaps, accepted_ends=()):
    """Entry evidence for a function nothing calls directly (inlined everywhere).

    Accepted only from original bytes: the entry is 16-byte aligned and is
    preceded by alignment padding (0x90/0xCC), directly by the end of the
    previous function (ret, ret N or jmp), or by the recorded full extent of
    an accepted canonical region (`accepted_ends`: a predecessor ending in
    switch tables, which are data); the body decodes completely and its
    last instruction is ret or jmp. A body ending in switch tables that its own
    code indexes is decoded only up to those tables. The candidate's own end
    is established from its own bytes in every case.
    """
    import capstone
    entry = int(bound['entry'], 16)
    if entry % 16:
        return False
    # What precedes the entry, read from the original bytes: alignment
    # padding (0x90/0xCC), or the end of the previous function (ret, ret N,
    # jmp rel32 or jmp rel8).
    preceding = audit.original(entry - 5, 5)
    after_padding = preceding[4] in (0x90, 0xCC)
    after_return = preceding[4] == 0xC3 or preceding[2] == 0xC2
    after_jump = preceding[0] == 0xE9 or preceding[3] == 0xEB
    after_accepted = entry in accepted_ends
    if not (after_padding or after_return or after_jump or after_accepted):
        return False
    body = bytes.fromhex(bound['ranges'][0]['bytes_hex'])
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    data = switch_data_start(decoder, body, entry)
    if data is not None:
        # The tables are 4-byte aligned after the code; drop the alignment fill:
        # NOPs/INT3s, or one of VC6's multi-byte no-op fills when it ends exactly
        # at a 4-aligned table: `mov edi, edi` (8B FF, HouseClass 0x4EB8C0),
        # `lea ecx, [ecx]` (8D 49 00, HouseClass 0x4EAF30), `lea esp, [esp]` (8D 64 24 00).
        body = body[:data]
        if (entry + data) % 4 == 0:
            for fill in ALIGNMENT_FILLS:
                if body.endswith(fill):
                    body = body[:-len(fill)]
                    break
        body = body.rstrip(b'\x90\xcc')
    instructions = list(decoder.disasm(body, entry))
    return (sum(i.size for i in instructions) == len(body) and bool(instructions) and
            instructions[-1].mnemonic in ('ret', 'jmp'))


def check_population(audit, population, accepted_ends=()):
    inventory_path = population['inventory']
    inventory = {int(r['entry'], 16): r for r in
                 map(json.loads, audit.read(inventory_path, population['inventory_sha256']).splitlines())}
    gap_path = audit.path(inventory_path).parent / 'unassigned-executable.jsonl'
    gaps = {int(r['start'], 16): r for r in
            map(json.loads, audit.read(gap_path, population['gap_inventory_sha256']).splitlines())}
    rows = population['candidates']
    require(rows and len({r['entry'] for r in rows}) == len(rows) and
            len({r['method'] for r in rows}) == len(rows), 'Empty/duplicate candidate population')
    cursor = 0
    for row in sorted(rows, key=lambda r: r['entry']):
        va = row['entry']; bound = inventory.get(va)
        require(bound == row['original_inventory_row'] and bound['contiguous'] and
                len(bound['ranges']) == 1 and (bound['entry_references'] or
                                               aligned_unreferenced_entry(audit, bound, gaps, accepted_ends)),
                'Unsupported independent bound at 0x%08X' % va)
        span = bound['ranges'][0]
        require(int(span['start'], 16) == va and
                int(span['end_inclusive'], 16) + 1 - va == row['body_bytes'], 'Original body extent differs')
        body = audit.original(va, row['body_bytes'])
        require(body == bytes.fromhex(span['bytes_hex']) and sha(body) == row['body_sha256'], 'Original body drift')
        pad = bytes.fromhex(row['padding_hex'])
        require(not pad or (len(pad) <= 15 and pad == b'\x90' * len(pad) and
                row['padding_provenance'] == gaps.get(va + len(body)) and
                gaps[va + len(body)]['length'] == len(pad)), 'Unsupported independent padding')
        require(va >= cursor and row['region_bytes'] == len(body) + len(pad) and
                audit.original(va, row['region_bytes']) == body + pad and
                sha(body + pad) == row['region_sha256'], 'Original full region/overlap differs')
        audit.read(row['source'], row['source_sha256'])
        cursor = va + row['region_bytes']


def compare_candidate(audit, coff, candidate, obj, options, variant):
    row = dict(method=candidate['method'], variant=variant, options=options,
               source=candidate['source'], source_sha256=candidate['source_sha256'],
               object=str(obj), object_sha256=sha(obj.read_bytes()))
    try:
        symbol, section, start, end = coff.function(candidate['symbol_prefix'])
        raw = section['data'][start:end]; actual = bytearray(raw); bindings = []
        for offset, symbol_index, kind in section['relocs']:
            if not start <= offset < end: continue
            offset -= start; target_symbol = coff.symbols[symbol_index]
            local = local_label_target(coff, target_symbol, symbol['section'], start, end, candidate['entry'])
            matches = [local] if local is not None else sorted(
                prefix_bound_values(candidate.get('references', {}), target_symbol['name']))
            require(len(matches) == 1 and kind in (6, 20) and offset + 4 <= len(actual),
                    'Unsupported/unbound/cross-extent relocation')
            target = matches[0]; addend = struct.unpack_from('<I', actual, offset)[0]
            resolved = (target + addend - (candidate['entry'] + offset + 4 if kind == 20 else 0)) & 0xffffffff
            struct.pack_into('<I', actual, offset, resolved)
            # Compiler-local label names ($L5403) depend on the whole unit.
            bindings.append(dict(offset=offset, kind=kind, symbol='$local' if local is not None else target_symbol['name'],
                                 target=target, addend=addend, resolved=resolved))
        expected = audit.original(candidate['entry'], candidate['region_bytes'])
        row.update(status='extent-exact' if bytes(actual) == expected else 'mismatch',
                   actual_bytes=len(actual), expected_bytes=len(expected),
                   differing_bytes=sum(a != b for a, b in zip(actual, expected)) + abs(len(actual)-len(expected)),
                   symbol=symbol['name'], section_index=symbol['section'], section_start=start, section_end=end,
                   relocations=bindings, raw_section_sha256=sha(raw), actual_sha256=sha(actual))
    except ValueError as error:
        row.update(status='comparison-refused', reason=str(error))
    return row


def covered_retired(region, candidate, retiring):
    """True when `region` is a retired accepted region lying wholly inside the candidate's extent."""
    return (region['entry'] in retiring and candidate['entry'] < region['entry'] and
            region['entry'] + region['full_extent_bytes'] <= candidate['entry'] + candidate['region_bytes'])


def compile_population(manifest_path, output, config, replacing=(), retiring=()):
    """Compile and strictly audit a frozen population.

    `replacing` lists accepted entries this population may supersede (an
    identical original body rewritten as more readable source, which may also
    claim the complete inventoried padding gap after it). `retiring` lists
    accepted entries a candidate may swallow: a retired region is excused only
    when its entire extent (body and frozen padding) lies inside the
    candidate's own region; every other overlap with accepted source is still
    refused.
    """
    started = time.monotonic(); output = Path(output).resolve()
    require(not output.exists() and any(output.is_relative_to(REPOSITORY / name) and
            output != REPOSITORY / name for name in ('private', 'build')), 'Output must be new ignored directory')
    manifest_path = Path(manifest_path).resolve()
    population = json.loads(manifest_path.read_bytes())
    require(population['executable_sha256'] == TARGET_SHA256, 'Wrong population target')
    audit = Audit(REPOSITORY, config['executable'])
    catalog = catalog_io.load(catalog_io.locate(REPOSITORY))
    check_population(audit, population, accepted_region_ends(catalog))
    selected_options = trial_options(population)
    headers = validate_headers(REPOSITORY, catalog)
    for candidate in population['candidates']:
        validate_includes(audit.read(candidate['source']), headers)
        require(not any(r['entry'] < candidate['entry'] + candidate['region_bytes'] and
                        candidate['entry'] < r['entry'] + r['full_extent_bytes']
                        for r in catalog['regions'] if not (r['entry'] in replacing and
                                                            r['entry'] == candidate['entry'] and
                                                            r['body_bytes'] == candidate['body_bytes']) and
                        not covered_retired(r, candidate, retiring)),
                'Candidate overlaps accepted source')
    tools = check_toolchain(config, json.loads((REPOSITORY/'manifests/toolchain.json').read_bytes()))
    dependencies = {str(p.relative_to(REPOSITORY)): sha(p.read_bytes()) for p in
                    [Path(__file__), *[Path(__file__).with_name(n) for n in
                     ['build.py', 'remote_compile.py', 'canonical.py', 'source_paths.py', 'verify_manifest.py', 'coff.py', 'compiler_output.py']]]}
    output.mkdir(parents=True)
    source = output / 'candidates.cpp'
    source.write_bytes(b'\n'.join(audit.read(c['source']) for c in population['candidates']))
    units = []; objects = []
    separate = bool(population.get('separate_units'))
    for variant, options in enumerate(selected_options):
        directory = output / str(variant); directory.mkdir()
        sources = ([(c['method'], audit.path(c['source'])) for c in population['candidates']] if separate
                   else [('candidates', source)])
        for name, unit in sources:
            obj = directory/(name+'.obj'); objects.append((variant, options, name, obj))
            units.append(dict(cwd=directory, source=unit, obj=obj, log=directory/(name+'.log'),
                              returncode=directory/(name+'.returncode.txt'), args=compiler_arguments(options)))
    command = compile_units(config, output, units, 'compile-candidates', parallel=False, timeout=3600)
    comparison_start = time.monotonic(); results = []; chosen = {}
    by_method = {c['method']: c for c in population['candidates']}
    for variant, options, name, obj in objects:
        rc = int((obj.parent/(name+'.returncode.txt')).read_text().strip())
        if rc or not obj.exists():
            results.append(dict(variant=variant, status='batch-compile-failed', returncode=rc, unit=name)); continue
        coff = Coff(obj.read_bytes())
        for candidate in ([by_method[name]] if separate else population['candidates']):
            result = compare_candidate(audit, coff, candidate, obj, options, variant); results.append(result)
            if result['status'] == 'extent-exact': chosen.setdefault(candidate['method'], result)
    if population.get('single_variant') and not separate:
        # A class unit compiles as one translation unit: members accepted under
        # different options would be split into separate build groups and lose
        # the cross-member inlining they were matched with. Keep the variant
        # with the most exact members (earliest on ties).
        exact = Counter(r['variant'] for r in results if r.get('status') == 'extent-exact')
        if exact:
            best = min(exact, key=lambda v: (-exact[v], v))
            chosen = {}
            for result in results:
                if result.get('status') == 'extent-exact' and result['variant'] == best:
                    chosen.setdefault(result['method'], result)
    report = dict(manifest=str(manifest_path), manifest_sha256=sha(manifest_path.read_bytes()),
                  source=str(source), source_sha256=sha(source.read_bytes()), results=results,
                  counts=dict(Counter(r['status'] for r in results)), unique_extent_exact=len(chosen),
                  trial_options=selected_options, separate_units=bool(population.get('separate_units')),
                  compiler=tools, command=command, authored_dependencies=dependencies,
                  comparison_seconds=time.monotonic()-comparison_start)
    report_path=output/'report.json';write_json(report_path, report)
    accepted = []
    for candidate in population['candidates']:
        result = chosen.get(candidate['method'])
        if result is None: continue
        accepted.append(dict(candidate, **{k:v for k,v in result.items() if k not in candidate},
                             original_bound=candidate['original_inventory_row'],
                             body_sha256=candidate['body_sha256'], padding_bytes=len(bytes.fromhex(candidate['padding_hex'])),
                             full_extent_bytes=candidate['region_bytes'], full_extent_sha256=candidate['region_sha256']))
    acceptance = dict(executable_sha256=TARGET_SHA256, original_manifest=str(manifest_path),
                      original_manifest_sha256=report['manifest_sha256'], report=str(report_path),
                      report_sha256=sha(report_path.read_bytes()), accepted=accepted,
                      matched_source_regions=len(accepted), body_bytes=sum(r['body_bytes'] for r in accepted),
                      frozen_padding_bytes=sum(r['padding_bytes'] for r in accepted),
                      full_extent_bytes=sum(r['full_extent_bytes'] for r in accepted))
    acceptance_path=output/'accepted.json';write_json(acceptance_path, acceptance)
    # Preliminary equality is never sufficient: recheck every selected row with
    # the complete existing V4 provenance, section-coverage and operand verifier.
    if accepted: write_json(output/'strict-verification.json', audit.audit(acceptance_path))
    for path, data in audit.blobs.items(): require(path.read_bytes() == data, 'Candidate input changed during compilation')
    for name, digest in dependencies.items(): require(sha((REPOSITORY/name).read_bytes()) == digest, 'Candidate tool drift')
    require(validate_headers(REPOSITORY, catalog) == headers, 'Candidate header drift')
    receipt = dict(status='strict-candidates-only-not-canonical', accepted=len(accepted),
                   body_bytes=acceptance['body_bytes'], padding_bytes=acceptance['frozen_padding_bytes'],
                   counts=report['counts'], seconds=time.monotonic()-started, accepted_manifest=str(acceptance_path))
    write_json(output/'candidate-receipt.json', receipt)
    return receipt


if __name__ == '__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--manifest', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--config', type=Path, default=REPOSITORY/'private/original-target.local.json')
    args=parser.parse_args()
    print(json.dumps(compile_population(args.manifest, args.output, json.loads(args.config.read_bytes()))))
