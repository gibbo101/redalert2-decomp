#!/usr/bin/env python3
"""Strictly accept hand-written sources, adding new regions or replacing old ones.

Input: a JSON plan listing sources, each with its original entry and the
mangled symbol prefix of the function it defines:

  {"name": "rawfileclass-v1",
   "sources": [{"entry": "006394d0",
                "draft": "build/class-work/RawFileClass/RawFileClass_Is_Open_006394d0.cpp",
                "source": "src/recovered/classes/RawFileClass/RawFileClass_Is_Open_006394d0.cpp",
                "symbol_prefix": "?Is_Open@RawFileClass@@",
                "semantic_name": "RawFileClass_Is_Open_006394d0"}]}

Drafts live outside src/recovered/ (the build refuses uncatalogued sources);
an exact draft is copied to its `source` destination on acceptance. References are bound from manifests/symbols.json
(original names), accepted catalog symbols, address-named symbols, imports
and `// @ref NAME=ADDRESS` comments. The population is frozen against the
frozen inventory bounds (the region's current extent when replacing) and goes
through compile_candidates.py's strict audit. Only exact sources are
installed; a replaced region's old file is removed. If nothing matches, the
catalog is untouched and the new files are left for further iteration.

Run ./build.command afterwards; it must reproduce the complete file.
"""
import argparse
import json
from pathlib import Path
import re
import sys

REPOSITORY = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))

from canonical import sha
import diff_candidate as diff
from inventory import INVENTORY, PASSES, Inventory
from promote_sweep import CONFIGS, gap_padding, references as seed_references
from regenerate_seeds import sync_headers
import catalog_io

SYMBOLS = REPOSITORY / 'manifests/symbols.json'


def named_symbols():
    """Original-name database: mangled prefix -> address."""
    if not SYMBOLS.exists():
        return {}
    rows = json.loads(SYMBOLS.read_text())['symbols']
    return {r['mangled_prefix']: int(r['address'], 16) for r in rows if r.get('mangled_prefix')}


def scanned_references(entry, inventory, audit):
    """Direct call/jmp sites targeting entry, found in the original image.

    A site counts only when the bytes decode, at that address, as a call or
    jmp to exactly this entry and the site lies inside a known function body.
    """
    import capstone
    import struct as _struct
    from bisect import bisect_right
    if not hasattr(scanned_references, 'image'):
        # Text, decoder and function spans are prepared once per run.
        section = next(s for s in audit.pe.sections if s.Characteristics & 0x20)
        spans = sorted((int(r['start'], 16), int(r['end_inclusive'], 16))
                       for row in inventory.all_functions().values() for r in row['ranges'])
        scanned_references.image = (audit.base + section.VirtualAddress,
                                    section.get_data()[:section.Misc_VirtualSize],
                                    capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32),
                                    spans, [a for a, _ in spans])
    base, text, decoder, spans, starts = scanned_references.image
    found = []
    # Direct call/jmp targets, indexed once per run (the text is scanned a
    # single time instead of once per entry).
    if not hasattr(scanned_references, 'branch_index'):
        index = {}
        for opcode, kind in ((0xE8, 'UNCONDITIONAL_CALL'), (0xE9, 'UNCONDITIONAL_JUMP')):
            position = text.find(bytes([opcode]))
            while position >= 0 and position + 5 <= len(text):
                target = (_struct.unpack_from('<i', text, position + 1)[0] + base + position + 5) & 0xffffffff
                index.setdefault(target, []).append((position, kind))
                position = text.find(bytes([opcode]), position + 1)
        scanned_references.branch_index = index
    for position, kind in scanned_references.branch_index.get(entry, []):
        site = base + position
        insn = next(decoder.disasm(text[position:position + 5], site, 1), None)
        index = bisect_right(starts, site) - 1
        if insn and insn.size == 5 and index >= 0 and spans[index][0] <= site <= spans[index][1]:
            found.append({'from': '%08x' % site, 'type': kind, 'evidence': 'image-scan'})
    # Address taken: push imm32 / mov reg, imm32 / mov [mem], imm32 of the entry.
    needle = _struct.pack('<I', entry)
    position = text.find(needle)
    while position >= 0:
        for back in range(1, 7):
            start = position - back
            insn = next(decoder.disasm(text[start:position + 4], base + start, 1), None) if start >= 0 else None
            if insn and insn.size == back + 4 and insn.mnemonic in ('push', 'mov') and insn.op_str.endswith(hex(entry)):
                index = bisect_right(starts, base + start) - 1
                if index >= 0 and spans[index][0] <= base + start <= spans[index][1]:
                    found.append({'from': '%08x' % (base + start), 'type': 'ADDRESS_TAKEN', 'evidence': 'image-scan'})
                break
        position = text.find(needle, position + 1)
    return found


def partial_padding(audit, directory, row):
    """True when a bogus row inside the alignment NOPs after `row` leaves its
    gap row shorter than the NOP run (the composite pass takes the whole run)."""
    aligned = directory.with_name(directory.name + '-aligned')
    gap_file = (aligned if aligned.exists() else directory) / 'unassigned-executable.jsonl'
    if not hasattr(partial_padding, 'cache'):
        partial_padding.cache = {}
    if gap_file not in partial_padding.cache:
        partial_padding.cache[gap_file] = {int(g['start'], 16): g for g in
                                           map(json.loads, gap_file.read_text().splitlines())}
    end = int(row['ranges'][0]['end_inclusive'], 16) + 1
    run = 0
    while run < 15 and audit.original(end + run, 1) == b'\x90':
        run += 1
    gap = partial_padding.cache[gap_file].get(end)
    return bool(run) and (end + run) % 16 == 0 and (gap is None or gap['length'] < run)


def composite_pass(plan, inventory, existing, catalog, audit=None):
    """Frozen composite inventory for a plan no single pass covers.

    Each entry's row comes verbatim from the first frozen pass holding it as
    one contiguous body (the accepted pass's row for a replacement); the gap
    rows at each body end come from that pass's aligned gap list. The result
    is written once under the inventory root with its provenance, and is
    itself a frozen input of the population.
    """
    name = 'composite-' + plan['name']
    target = PASSES[0].parent / name
    rows, gaps, provenance, gap_cache = [], {}, [], {}
    for item in plan['sources']:
        entry = int(item['entry'], 16); chosen = None
        if item.get('body_bytes'):
            # Explicit bound from the plan (e.g. a linear sweep of the original
            # bytes to the final ret); reference evidence still comes from a
            # frozen pass or the image scan below.
            length = int(item['body_bytes'])
            base_row = next((inventory.rows(d).get(entry) for d in PASSES if inventory.rows(d).get(entry)), None) or {}
            body = audit.original(entry, length)
            row = dict(entry='%08x' % entry, name=base_row.get('name', 'FUN_%08x' % entry), contiguous=True,
                       ranges=[dict(start='%08x' % entry, end_inclusive='%08x' % (entry + length - 1),
                                    length=length, bytes_hex=body.hex())],
                       entry_references=base_row.get('entry_references') or [],
                       status='plan-stated bound: ' + item.get('bound_evidence', 'unspecified'))
            chosen = (PASSES[0], row)
        for directory in ([] if chosen else PASSES + sorted(INVENTORY.glob('composite-*'))):
            row = inventory.rows(directory).get(entry)
            if not row or not row['contiguous'] or len(row['ranges']) != 1 or int(row['ranges'][0]['start'], 16) != entry:
                continue
            if entry in existing and row['ranges'][0]['length'] != existing[entry]['body_bytes']:
                continue
            chosen = (directory, row); break
        if chosen is None:
            return None
        directory, row = chosen
        borrowed = None
        if not row.get('entry_references'):
            # Bounds stay from the chosen pass; reference evidence may come
            # from another frozen pass that analysed this entry's callers.
            for other in PASSES:
                refs = (inventory.rows(other).get(entry) or {}).get('entry_references')
                if refs:
                    row = dict(row, entry_references=refs); borrowed = str(other.relative_to(REPOSITORY)); break
            if not row.get('entry_references') and audit is not None:
                refs = scanned_references(entry, inventory, audit)
                if refs:
                    row = dict(row, entry_references=refs); borrowed = 'original image direct call/jmp scan'
        rows.append(row)
        aligned = directory.with_name(directory.name + '-aligned')
        gap_file = (aligned if aligned.exists() else directory) / 'unassigned-executable.jsonl'
        end = int(row['ranges'][0]['end_inclusive'], 16) + 1
        if gap_file not in gap_cache:
            rows_by_start, rows_by_end = {}, {}
            for gap in map(json.loads, gap_file.read_text().splitlines()):
                start = int(gap['start'], 16)
                rows_by_start[start] = gap; rows_by_end[start + gap['length']] = gap
            gap_cache[gap_file] = (rows_by_start, rows_by_end)
        rows_by_start, rows_by_end = gap_cache[gap_file]
        # the gap after the body (padding) and the one before it (entry evidence)
        for gap in (rows_by_start.get(end), rows_by_end.get(entry)):
            if gap:
                gaps[int(gap['start'], 16)] = gap
        # Alignment padding from original bytes: when no gap row starts at the
        # body end, or the row there is a shorter all-NOP fragment (a bogus
        # inventory row starting inside the padding claims the rest), use the
        # whole NOP run up to the next 16-byte boundary.
        count = 0
        while count < 15 and audit.original(end + count, 1) == b'\x90':
            count += 1
        existing_gap = gaps.get(end)
        if count and (end + count) % 16 == 0 and (
                existing_gap is None or (existing_gap['length'] < count and
                                         audit.original(end, existing_gap['length']) == b'\x90' * existing_gap['length'])):
            gaps[end] = dict(start='%08x' % end, end_inclusive='%08x' % (end + count - 1), length=count,
                             classification='alignment_nop_padding_from_original_bytes')
        provenance.append(dict(entry=item['entry'], row_from=str(directory.relative_to(REPOSITORY)),
                               gaps_from=str(gap_file.relative_to(REPOSITORY)),
                               **({'entry_references_from': borrowed} if borrowed else {})))
    if target.exists():
        return target
    target.mkdir(parents=True)
    (target / 'functions.jsonl').write_text(''.join(json.dumps(r) + '\n' for r in rows))
    (target / 'unassigned-executable.jsonl').write_text(
        ''.join(json.dumps(gaps[k]) + '\n' for k in sorted(gaps)))
    (target / 'composite.json').write_text(json.dumps(dict(
        rule='per-entry rows copied from the first frozen pass with a contiguous body (entry references from another '
             'frozen pass where that row has none); gap rows at body ends',
        entries=provenance), indent=1))
    return target


def with_headers(text, seen=None):
    """Source text plus the shared headers it includes (inline code calls too)."""
    seen = set() if seen is None else seen
    parts = [text]
    for name in re.findall(r'#\s*include\s+"([^"]+)"', text):
        path = REPOSITORY / 'src' / name
        if name not in seen and path.exists():
            seen.add(name)
            parts.append(with_headers(path.read_text(), seen))
    return '\n'.join(parts)


def bind(text, known):
    """Reference map for one source: address-named symbols and @ref comments,
    plus every known name (import slots, original names) the text mentions.
    The strict audit refuses any relocation left unbound or bound ambiguously."""
    refs = seed_references(text, 0, {})
    words = set(re.findall(r'[A-Za-z_]\w*', text))     # tokenize once; names are tested by membership
    word_matches = {}     # one visibility decision per distinct source spelling
    for name, address in known.items():
        if name in ('??2@YAPAXI@Z', '??3@YAXPAX@Z', '_atexit') or (name.startswith('__') and not name.startswith('__imp__')):
            # operator new/delete and compiler helpers (__ftol, __chkstk, __CIpow)
            # that the compiler calls without the source naming them.
            refs[name] = address
            continue
        if name.startswith('??_'):
            word = name[4:].split('@')[0]       # vtable/destructor of a class the source mentions
        elif name.startswith('??'):
            word = name[3:].split('@')[0]       # constructor, destructor or operator of a mentioned class
        else:
            word = re.sub(r'^(__imp__|_)', '', name).split('@')[0].lstrip('?')
        if not word:
            continue
        if word not in word_matches:
            word_matches[word] = (word in words) if re.fullmatch(r'[A-Za-z_]\w*', word) else bool(
                re.search(r'\b%s\b' % re.escape(word), text))
        if word_matches[word]:
            refs[name] = address
    # VC6 vtables name the vector deleting destructor (??_E), which aliases
    # the scalar one (??_G) when no array delete is used.
    for name, address in list(refs.items()):
        if name.startswith('??_G'):
            refs.setdefault('??_E' + name[4:], address)
    # Within one address, prefix-related names are consecutive in lexical order.
    # Keep the longest bindings, preserving the surviving dictionary order.
    by_address = {}
    for name, address in refs.items():
        by_address.setdefault(address, []).append(name)
    for names in by_address.values():
        names.sort()
        for name, following in zip(names, names[1:]):
            if name.startswith('?') and following.startswith(name):
                del refs[name]
    return refs


def rtti_references(text, descriptors):
    """Under /GR: the type_info vtable and the type descriptor (??_R0) of
    every plain class the source mentions, from the original's RTTI
    (Audit.original_type_descriptors). A dynamic_cast or typeid relocates
    them from code; every other RTTI structure the unit emits is bound by
    the audit from the original's RTTI graph."""
    words = set(re.findall(r'[A-Za-z_]\w*', text))
    refs = {'??_7type_info@@6B@': descriptors['??_7type_info@@6B@']}
    for name, address in descriptors.items():
        simple = re.fullmatch(r'\?\?_R0\?A[UV](\w+)@@@8', name)
        if simple and simple[1] in words:
            refs[name] = address
    return refs


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('plan', type=Path)
    parser.add_argument('--output', type=Path, help='new private directory (default private/.../accept-<name>)')
    parser.add_argument('--config', type=Path, default=REPOSITORY / 'private/original-target.local.json')
    args = parser.parse_args()
    from compile_candidates import compile_population
    from verify_manifest import Audit, TARGET_SHA256, switch_data_start
    plan = json.loads(args.plan.read_text())
    # A plan is one unit: in-source @ref bindings of any draft apply to all.
    plan.setdefault('references', {})
    for item in plan['sources']:
        for name, value in diff.SOURCE_REF.findall((REPOSITORY / item['draft']).read_text()):
            plan['references'].setdefault(name, value)
    from source_paths import source_path
    for item in plan['sources']:
        # The canonical build only reads sources under src/recovered with plain names.
        try:
            source_path(REPOSITORY, item['source'])
        except ValueError as error:
            raise SystemExit('%s: %s' % (error, item['source']))
        # The canonical build requires a semantic name to be the file stem.
        if item.get('semantic_name') and (Path(item['source']).stem != item['semantic_name'] or
                                          not item['semantic_name'].endswith('_%08x' % int(item['entry'], 16))):
            raise SystemExit('semantic_name must equal the source file stem and end with the entry: %s' % item['entry'])
    drafts = [item['draft'] for item in plan['sources']]
    if len(set(drafts)) != len(drafts):
        # Each draft is concatenated once per item into the unit; a second
        # function emitted by one definition (an atexit thunk, an inline
        # copy) needs its own comment-only draft.
        raise SystemExit('plan items share a draft: %s' % sorted({d for d in drafts if drafts.count(d) > 1}))
    # Calls between members of the unit bind to the members' own entries.
    for item in plan['sources']:
        plan['references'].setdefault(item['symbol_prefix'], item['entry'])
    config = json.loads(args.config.read_bytes())
    audit = Audit(REPOSITORY, config['executable'])
    catalog_path = REPOSITORY / 'manifests/original_target.json'
    catalog = catalog_io.loads(catalog_path.read_bytes())
    sync_headers(catalog); catalog_io.dump(catalog, catalog_path)
    existing = {r['entry']: r for r in catalog['regions']}
    # A replaced region keeps the bindings it was accepted with (its
    # population's table); the plan's own references take precedence.
    for item in plan['sources']:
        old = existing.get(int(item['entry'], 16))
        for name, value in (old or {}).get('references', {}).items():
            plan['references'].setdefault(name, '%08x' % value)
    known = diff.known_references(catalog)
    output = (args.output or REPOSITORY / 'private/original-target-20261020' / ('accept-' + plan['name'])).resolve()
    if output.exists():
        raise SystemExit('output exists: %s' % output)
    inventory = Inventory()
    replacing = {int(i['entry'], 16) for i in plan['sources'] if int(i['entry'], 16) in existing}
    # A hand-written unit compiles as one translation unit: replacing only
    # part of it would leave the rest compiling without the definitions (and
    # initializers) it was matched with.
    from canonical import separate_unit_populations
    separate = separate_unit_populations(catalog)
    for population in {existing[e]['population'] for e in replacing} - set(separate):
        members = [r for r in catalog['regions'] if r['population'] == population]
        if any(r.get('source_quality_family') == 'hand-written' for r in members):
            left = sorted(r['entry'] for r in members if r['entry'] not in replacing)
            if left and not plan.get('allow_split'):
                raise SystemExit('plan replaces part of hand-written %s; also include %s (or set allow_split)'
                                 % (population, ', '.join('%08x' % e for e in left[:8])))
    # A plan is one translation unit (like an original .cpp): compile it as a
    # single population when one inventory pass covers every entry with the
    # accepted extents, so cross-method inlining matches the original.
    shared_pass = None
    for candidate_pass in PASSES:
        rows = inventory.rows(candidate_pass)
        def fits(entry):
            row = rows.get(entry)
            if not row or not row['contiguous'] or int(row['ranges'][0]['start'], 16) != entry:
                return False
            return entry not in existing or row['ranges'][0]['length'] == existing[entry]['body_bytes']
        if not any(i.get('body_bytes') for i in plan['sources']) and \
                all(fits(int(i['entry'], 16)) for i in plan['sources']) and \
                not any(partial_padding(audit, candidate_pass, rows[int(i['entry'], 16)]) for i in plan['sources']):
            shared_pass = candidate_pass; break
    by_pass = {}
    if shared_pass is None:
        shared_pass = composite_pass(plan, inventory, existing, catalog, audit)
    if shared_pass is not None:
        aligned = shared_pass.with_name(shared_pass.name + '-aligned')
        rows = Inventory([shared_pass]).rows(shared_pass)
        by_pass[aligned if aligned.exists() else shared_pass] = [
            (int(i['entry'], 16), rows[int(i['entry'], 16)], i) for i in plan['sources']]
    for item in ([] if shared_pass is not None else plan['sources']):
        entry = int(item['entry'], 16)
        directory, bound = inventory.function(entry)
        if entry in existing:
            old = existing[entry]
            # Replacement keeps the accepted extent and its population's pass
            # (a base pass, or the composite pass the population was accepted under).
            for candidate_pass in PASSES + sorted(INVENTORY.glob('composite-*')):
                rows = inventory.rows(candidate_pass)
                if entry in rows and sha((candidate_pass / 'functions.jsonl').read_bytes()) == next(
                        p['inventory_sha256'] for p in catalog['populations'] if p['id'] == old['population']):
                    directory, bound = candidate_pass, rows[entry]
        aligned = directory.with_name(directory.name + '-aligned')
        by_pass.setdefault(aligned if aligned.exists() else directory, []).append((entry, bound, item))
    output.mkdir(parents=True)
    results = []
    next_population = max(int(p['id'].split('-')[1]) for p in catalog['populations']) + 1
    installs = []
    for directory, entries in sorted(by_pass.items()):
        gaps_path = directory / 'unassigned-executable.jsonl'
        gaps = {int(g['start'], 16): g for g in map(json.loads, gaps_path.read_text().splitlines())}
        candidates = []
        for entry, bound, item in entries:
            path = REPOSITORY / item['draft']; text = path.read_text()
            body = audit.original(entry, int(bound['ranges'][0]['end_inclusive'], 16) + 1 - entry)
            if entry in existing and existing[entry]['padding_bytes']:
                count = existing[entry]['padding_bytes']
                pad = audit.original(entry + len(body), count) if count else b''
                provenance = gaps.get(entry + len(body)) if pad else None
                pad_hex = pad.hex()
            else:
                pad_hex, provenance = gap_padding(audit.original, gaps, entry + len(body))
            region = body + bytes.fromhex(pad_hex)
            # A plan-stated bound may end in the switch tables the code indexes.
            code_size = switch_data_start(audit.decoder, body, entry) if item.get('body_bytes') else None
            switch = {'switch_data_bytes': len(body) - code_size} if code_size else {}
            rtti = rtti_references(with_headers(text), audit.original_type_descriptors()) if \
                any('/GR' in options for options in plan.get('options') or []) else {}
            candidates.append(dict(entry=entry, method='%08x' % entry, source=str(path), **switch,
                                   source_sha256=sha(path.read_bytes()), symbol_prefix=item['symbol_prefix'],
                                   references={**bind(with_headers(text), known), **rtti,
                                               **{k: int(v, 16) for k, v in plan.get('references', {}).items()}},
                                   body_bytes=len(body),
                                   body_sha256=sha(body), region_bytes=len(region), region_sha256=sha(region),
                                   padding_hex=pad_hex, padding_provenance=provenance,
                                   original_inventory_row=bound))
        population = dict(executable_sha256=TARGET_SHA256, inventory=str((directory / 'functions.jsonl').relative_to(REPOSITORY)),
                          inventory_sha256=sha((directory / 'functions.jsonl').read_bytes()),
                          gap_inventory_sha256=sha(gaps_path.read_bytes()), source_model='hand-written-' + plan['name'],
                          candidates=candidates, separate_units=bool(plan.get('separate_units')),
                          single_variant=not plan.get('separate_units'),
                          # Class units are matched under /O2 /Ob2 /G5 /Gy; a plan
                          # lists other option sets explicitly when it needs them.
                          compiler_trial_options=plan.get('options') or [['/O2', '/Ob2', '/G5', '/Gy']])
        label = directory.name; manifest_path = output / (label + '.json')
        manifest_path.write_text(json.dumps(population, indent=1))
        try:
            receipt = compile_population(manifest_path, output / label, config, replacing=replacing)
        except ValueError as error:
            results.append(dict(pass_=label, error=str(error))); continue
        accepted = json.loads(Path(receipt['accepted_manifest']).read_bytes())
        report = json.loads((output / label / 'report.json').read_bytes())
        missed = sorted({r['method'] for r in report['results'] if 'method' in r} -
                        {'%08x' % a['entry'] for a in accepted['accepted']})
        results.append(dict(pass_=label, candidates=len(candidates), accepted=len(accepted['accepted']), missed=missed))
        if missed and plan.get('all_or_nothing'):
            continue        # members of this unit depend on each other; install nothing
        if accepted['accepted']:
            installs.append((directory, gaps_path, population, manifest_path, receipt, accepted, entries))
    order_base = max(r['source_order'] for r in catalog['regions']) + 1
    for directory, gaps_path, population, manifest_path, receipt, accepted, entries in installs:
        population_id = 'population-%02d' % next_population; next_population += 1
        catalog['populations'].append(dict(id=population_id, inventory_sha256=population['inventory_sha256'],
                                           gaps_sha256=population['gap_inventory_sha256'],
                                           historical_population_sha256=sha(manifest_path.read_bytes()),
                                           historical_acceptance_sha256=sha(Path(receipt['accepted_manifest']).read_bytes()),
                                           **({'separate_units': True} if population.get('separate_units') else {})))
        items = {e: item for e, _, item in entries}
        keys = ['entry', 'method', 'symbol', 'symbol_prefix', 'options', 'body_bytes', 'body_sha256', 'padding_bytes',
                'full_extent_bytes', 'full_extent_sha256', 'references', 'relocations', 'source_sha256']
        for row in accepted['accepted']:
            item = items[row['entry']]
            region = {k: row.get(k, {}) for k in keys}
            if row.get('switch_data_bytes'):
                region['switch_data_bytes'] = row['switch_data_bytes']
            region.update(source=item['source'], population=population_id,
                          padding_sha256=sha(bytes.fromhex(row['padding_hex'])),
                          boundary_confidence='Frozen independent analysis hypothesis; exact compiler extent, not certified function',
                          source_quality_family='hand-written')
            if item.get('semantic_name'):
                region['semantic_name'] = item['semantic_name']
            destination = REPOSITORY / item['source']
            if destination.exists() and destination.read_bytes() != (REPOSITORY / item['draft']).read_bytes() and \
                    not (existing.get(row['entry']) and existing[row['entry']]['source'] == item['source']):
                raise SystemExit('refusing to overwrite %s' % destination)
            destination.parent.mkdir(parents=True, exist_ok=True)
            destination.write_bytes((REPOSITORY / item['draft']).read_bytes())
            # Plan order is translation-unit order; keep it in the canonical build.
            region['source_order'] = order_base + [int(i['entry'], 16) for i in plan['sources']].index(row['entry'])
            old = existing.get(row['entry'])
            if old:
                if old['source'] != item['source']:
                    (REPOSITORY / old['source']).unlink()
                catalog['regions'][catalog['regions'].index(old)] = region
            else:
                catalog['regions'].append(region)
        for name in CONFIGS:
            path = REPOSITORY / 'private' / name
            if path.exists():
                document = json.loads(path.read_bytes())
                document['populations'][population_id] = dict(inventory=population['inventory'],
                                                               gaps=str(gaps_path.relative_to(REPOSITORY)))
                path.write_text(json.dumps(document, indent=2) + '\n')
    catalog_io.dump(catalog, catalog_path)
    (output / 'results.json').write_text(json.dumps(results, indent=1))
    print(json.dumps(results, indent=1))


if __name__ == '__main__':
    main()
