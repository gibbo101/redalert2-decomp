"""Original evidence for address-only named thunks in scratch seeds.

Names can refer to several different thunk entries. Never choose by the name's
address suffix, inventory order, common jump target, or a candidate's score.
This does not establish source bounds, unique entry, invocation or callable ABI.
"""
from pathlib import Path
import struct


_ORIGINAL = []


def original_evidence():
    if not _ORIGINAL:
        from verify_manifest import Audit
        root = Path(__file__).resolve().parents[2]
        # Audit verifies the exact supplied target before any address is used.
        audit = Audit(root, 'private/original-target-20261020/inputs/game.exe')
        def executable(address):
            section = audit.pe.get_section_by_rva(address - audit.base)
            return section is not None and bool(section.Characteristics & 0x20)
        _ORIGINAL.append((audit.original, executable))
    return _ORIGINAL[0]


def prove_thunk_address(owner, candidates, inventory, read, executable):
    """One encoded entry, all occurrences explained by original DATA PUSHes.

    Inventory bounds and reference starts remain hypotheses. Original bytes
    must agree, and missing/conflicting evidence leaves the name unresolved.
    Only ordinary five-byte direct jump thunks and PUSH imm32 are supported.
    """
    candidates = sorted(set(candidates))
    if not candidates:
        return None
    targets = set()
    for entry in candidates:
        _, row = inventory.function(entry)
        if not row or row.get('external') or not row.get('thunk') or not row.get('contiguous') or len(row['ranges']) != 1:
            return None
        span = row['ranges'][0]
        if int(span['start'], 16) != entry or int(span['end_inclusive'], 16) != entry + 4:
            return None
        code = read(entry, 5)
        if len(code) != 5 or code[0] != 0xe9 or code != bytes.fromhex(span['bytes_hex']):
            return None
        target = (entry + 5 + struct.unpack_from('<i', code, 1)[0]) & 0xffffffff
        if not executable(entry) or not executable(target):
            return None
        targets.add(target)
    if len(targets) != 1:
        return None
    try:
        length = inventory.body_length(owner)
    except ValueError:
        return None
    if length <= 0:
        return None
    data = read(owner, length)
    if len(data) != length:
        return None
    matched_range = False
    for directory in inventory.passes:
        row = inventory.rows(directory).get(owner)
        if not row or not row.get('contiguous') or len(row['ranges']) != 1:
            continue
        span = row['ranges'][0]
        if (int(span['start'], 16) == owner and int(span['end_inclusive'], 16) == owner + length - 1 and
                bytes.fromhex(span['bytes_hex']) == data):
            matched_range = True
    if not matched_range:
        return None
    mentions = {}
    for entry in candidates:
        needle = struct.pack('<I', entry)
        start = data.find(needle)
        while start != -1:
            mentions.setdefault(entry, set()).add(owner + start)
            start = data.find(needle, start + 1)
    if len(mentions) != 1:
        return None
    entry, offsets = next(iter(mentions.items()))
    witnesses = set()
    for directory in inventory.passes:
        for ref in inventory.rows(directory).get(entry, {}).get('entry_references', []):
            if ref.get('type') != 'DATA':
                continue
            source = int(ref['from'], 16)
            if owner <= source <= owner + length - 5 and data[source-owner:source-owner+5] == b'\x68' + struct.pack('<I', entry):
                witnesses.add(source)
    if not witnesses or {source + 1 for source in witnesses} != offsets:
        return None
    return dict(entry=entry, push_sites=sorted(witnesses), inventory_body_bytes=length,
                thunk_entries=candidates, common_jump_target=next(iter(targets)))


def original_thunk_address(owner, candidates, inventory):
    read, executable = original_evidence()
    return prove_thunk_address(owner, candidates, inventory, read, executable)
