"""Closed, reviewed accounting for explicitly omitted compiler output.

This is not dead stripping or original source/library recognition. An opt-in pins
an entire emitted object's structure, all section bytes, symbols and relocations,
in addition to a single positively identified implicit helper and closed sources.
Unknown output and references refuse. Game-region comparison stays in V4.
"""
import hashlib
import json
from pathlib import Path
import struct


def require(condition, reason):
    if not condition:
        raise ValueError(reason)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def object_structure(coff):
    """Ignore only COFF timestamp and the compiler's source-file debug pathname.

    Symbol-table indices vary with pathname auxiliary length. References retain
    complete target identities, including section and every alias/aux record.
    All section contents, flags, symbol values and other auxiliary bytes remain.
    """
    def symbol_record(symbol):
        return {k: v for k, v in symbol.items() if k != 'auxiliary'} | {
            'auxiliary_sha256': sha(symbol['auxiliary'])}
    # Close all physical storage ranges as well as parsed transfer semantics.
    raw = coff.data
    machine, count, _, table, nsyms, optional, flags = struct.unpack_from('<HHIIIHH', raw)
    require(machine == 0x14c and optional == flags == 0, 'Unsupported compiler COFF header')
    ranges = [(0, 20 + 40 * count)]
    for i in range(count):
        _, physical, virtual, size, at, reloc, lines, nreloc, nlines, _ = struct.unpack_from('<8sIIIIIIHHI', raw, 20 + 40*i)
        require(physical == virtual == lines == nlines == 0, 'Unsupported compiler section address/line metadata')
        if size: ranges.append((at, at + size))
        if nreloc: ranges.append((reloc, reloc + 10*nreloc))
    strings_at = table + 18*nsyms
    ranges.append((table, strings_at + struct.unpack_from('<I', raw, strings_at)[0]))
    cursor = 0
    for first, last in sorted(ranges):
        require(first == cursor and last >= first, 'Unclassified/overlapping compiler file storage')
        cursor = last
    require(cursor == len(raw), 'Trailing unclassified compiler file storage')
    symbols = []
    files = 0
    for symbol in coff.symbols.values():
        if symbol['storage'] == 103:
            require(symbol['name'] == '.file' and symbol['section'] == -2 and
                    symbol['value'] == symbol['type'] == symbol['size'] == 0,
                    'Unsupported compiler file metadata')
            require(b'\0' in symbol['auxiliary'] and not any(symbol['auxiliary'].split(b'\0', 1)[1]),
                    'Malformed compiler file metadata')
            files += 1
            symbols.append(dict(name='.file', value=0, section=-2, type=0, storage=103, size=0,
                                auxiliary='normalized-source-debug-path'))
            continue
        symbols.append(symbol_record(symbol))
    require(files == 1, 'Missing/duplicate compiler file metadata')
    sections = [dict(name=s['name'], size=s['size'], flags=s['flags'], sha256=sha(s['data']),
                     relocations=[dict(offset=o, kind=k, target=symbol_record(coff.symbols[t]))
                                  for o, t, k in s['relocs']]) for s in coff.sections]
    return dict(sections=sections, symbols=symbols, header_flags=flags,
                string_table_sha256=sha(raw[strings_at:]))


def structure_hash(coff):
    return sha(json.dumps(object_structure(coff), sort_keys=True, separators=(',', ':')).encode())


def section_record(coff, index):
    section = coff.sections[index - 1]
    records = [s for s in coff.symbols.values() if s['section'] == index and
               s['name'] == section['name'] and s['storage'] == 3 and s['type'] == 0]
    require(len(records) == 1 and records[0]['value'] == 0 and
            len(records[0]['auxiliary']) == 18, 'Invalid compiler section auxiliary')
    length, relocations, lines, checksum, association, selection, reserved = struct.unpack(
        '<IHHIhB3s', records[0]['auxiliary'])
    require(length == section['size'] and relocations == len(section['relocs']) and
            lines == 0 and reserved == bytes(3), 'Compiler section auxiliary differs')
    return records[0], association, selection


def classify(audit, coff, reference, sources, options, compiler, inventory_sha256, gaps_sha256, headers, original_bounds):
    """Return a disjoint whole-section discard receipt, or refuse the object."""
    if reference is None:
        return []
    path = Path(reference['path'])
    require(not path.is_absolute() and path.parts[:1] == ('manifests',) and
            '..' not in path.parts and path.as_posix() == reference['path'],
            'Noncanonical compiler-output policy')
    policy = audit.document(path, reference['sha256'])
    require(policy['schema'] == 'ra2-closed-compiler-output-v1' and
            policy['original_image_credit'] == 0, 'Unsupported compiler-output policy')
    require(policy['compiler'] == compiler and policy['options'] == options and
            policy['sources'] == [s['source_sha256'] for s in sources] and
            policy['inventory_sha256'] == inventory_sha256 and
            policy['gaps_sha256'] == gaps_sha256, 'Compiler-output closed population/toolchain differs')
    require(policy['headers'] == headers, 'Compiler-output include dependency closure differs')
    for header in policy['headers']:
        audit.read(header['path'], header['sha256'])
    # Full object pin closes aliases, all metadata, directives, roots, data and
    # relocation topology, including nonaccepted/mismatching candidate sections.
    require(structure_hash(coff) == policy['object_structure_sha256'],
            'Compiler-output complete object structure differs')
    helper = policy['helper']
    symbol, section, first, last = coff.function(helper['symbol'])
    index = symbol['section']
    require(symbol['name'] == helper['symbol'] and first == 0 and last == len(section['data']) and
            section['size'] == helper['bytes'] and sha(section['data']) == helper['sha256'] and
            section['flags'] == 0x60501020 and not section['relocs'],
            'Compiler-output helper full section differs')
    record, association, selection = section_record(coff, index)
    aliases = [s for s in coff.symbols.values() if s['section'] == index]
    require(len(aliases) == 2 and symbol in aliases and record in aliases and
            symbol['value'] == 0 and symbol['type'] == 32 and symbol['storage'] == 2 and
            not symbol['auxiliary'] and association == 0 and selection == 2,
            'Compiler-output helper aliases/COMDAT differ')
    incoming = []
    associated = []
    for source_index, source in enumerate(coff.sections, 1):
        # Reject an additional associative/root component even without relocations.
        for s in coff.symbols.values():
            if s['section'] == source_index and s['storage'] == 3 and len(s['auxiliary']) == 18:
                _, assoc, sel = section_record(coff, source_index)
                if sel == 5 and assoc == index:
                    associated.append(source_index)
        for offset, target, kind in source['relocs']:
            if coff.symbols[target]['section'] == index:
                incoming.append((source_index, offset, target, kind))
    require(len(incoming) == 1 and associated == [incoming[0][0]],
            'Compiler-output helper incoming/association topology differs')
    debug_index, offset, target, kind = incoming[0]
    debug = coff.sections[debug_index - 1]
    debug_symbols = [s for s in coff.symbols.values() if s['section'] == debug_index]
    require(debug['name'] == '.debug$F' and debug['flags'] == 0x42101048 and debug['size'] == 16 and
            sha(debug['data']) == helper['debug_sha256'] and len(debug['relocs']) == 1 and
            len(debug_symbols) == 1 and offset == 0 and kind == 7 and coff.symbols[target] == symbol,
            'Compiler-output metadata-only reference differs')
    _, association, selection = section_record(coff, debug_index)
    require(association == index and selection == 5 and
            struct.unpack_from('<III', debug['data']) == (0, helper['body_bytes'], 0),
            'Compiler-output debug structure differs')
    original = policy['original_identity']
    # Original evidence is independent provenance, not an image recipient.
    facts = audit.document(original['readiness_path'], original['readiness_sha256'])
    require(facts['status'] == 'independently-ready-original-helper' and
            facts['entry'] == original['entry'] and facts['body_bytes'] == helper['body_bytes'] and
            facts['padding_bytes'] == helper['bytes'] - helper['body_bytes'] and
            facts['region_sha256'] == helper['sha256'], 'Compiler-output original provenance differs')
    inventory, gaps = original_bounds
    bound = inventory.get(original['entry'])
    gap = gaps.get(original['entry'] + helper['body_bytes'])
    following = inventory.get(original['entry'] + helper['bytes'])
    require(bound and gap and following and bound['entry_references'] and following['entry_references'],
            'Compiler-output original entry/end witnesses missing')
    for key, row in [('body_inventory_row_sha256', bound), ('gap_row_sha256', gap),
                     ('following_inventory_row_sha256', following)]:
        require(sha(json.dumps(row, sort_keys=True, separators=(',', ':')).encode()) == original[key],
                'Compiler-output independently frozen original rows differ')
    require(audit.original(original['entry'], helper['bytes']) == section['data'],
            'Compiler-output full original identity differs')
    return [dict(policy=str(path), policy_sha256=reference['sha256'],
                 object_structure_sha256=policy['object_structure_sha256'],
                 symbol=helper['symbol'], section_index=index, first=0, last=helper['bytes'],
                 bytes=helper['bytes'], sha256=helper['sha256'], metadata_section_index=debug_index,
                 original_image_credit=0, source_credit=0, library_credit=0,
                 disposition='explicitly-omitted-before-link')]
