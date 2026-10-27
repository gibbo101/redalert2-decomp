#!/usr/bin/env python3
"""Find vtables in the original image and rank classes by unrecovered bytes.

A vtable hypothesis is a run of dwords in a data section whose values are
inventory function entries, starting at an address that some instruction
stores into memory (`mov dword ptr [reg+disp], imm32`, the constructor and
destructor vptr write). Runs are split where another stored address begins.

For each vtable the report lists its slot functions, the functions that store
it (constructor/destructor candidates), accepted vs remaining body bytes, and
the vtable sharing the most slots (a likely base or sibling). Working a class
means recovering its layout once from those stores and sweeping all its slots
and constructors with shared types.

Where the image carries MSVC RTTI, each vtable's preceding complete object
locator supplies the original class name, the vtable's offset inside the
object (secondary vtables of multiple inheritance) and the ordered base-class
list with member displacements.

Hypotheses only: a run may merge adjacent tables, include non-virtual data, or
miss slots that point at unanalysed code.
"""
import argparse
from bisect import bisect_right
from collections import Counter
import json
import re
from pathlib import Path
import struct
import sys

REPOSITORY = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))


def function_spans(functions):
    spans = []
    for entry, row in functions.items():
        for span in row['ranges']:
            spans.append((int(span['start'], 16), int(span['end_inclusive'], 16) + 1, entry))
    spans.sort()
    return spans


def containing(spans, starts, address):
    index = bisect_right(starts, address) - 1
    if index >= 0 and spans[index][0] <= address < spans[index][1]:
        return spans[index][2]
    return None


def pointer_runs(data, base, entries, minimum=2):
    """Yield (address, [targets]) for aligned runs of function-entry dwords."""
    run_start, run = None, []
    for offset in range(0, len(data) - 3, 4):
        value = struct.unpack_from('<I', data, offset)[0]
        if value in entries:
            if run_start is None:
                run_start = base + offset
            run.append(value)
            continue
        if len(run) >= minimum:
            yield run_start, run
        run_start, run = None, []
    if len(run) >= minimum:
        yield run_start, run


def store_sites(decoder, text, text_base, value):
    """Addresses of `mov dword ptr [mem], value` instructions in text."""
    needle = struct.pack('<I', value); sites = []
    position = text.find(needle)
    while position >= 0:
        for back in range(2, 8):
            start = position - back
            if start < 0:
                break
            insn = next(decoder.disasm(text[start:position + 4], text_base + start, 1), None)
            if (insn and insn.size == back + 4 and insn.mnemonic == 'mov' and
                    insn.op_str.startswith('dword ptr [') and insn.op_str.endswith(hex(value))):
                # Stores into stack slots belong to inlined local objects, not
                # to the object a constructor/destructor is building.
                if not re.match(r'dword ptr \[e[sb]p', insn.op_str):
                    sites.append(text_base + start)
                break
        position = text.find(needle, position + 1)
    return sites


def split_runs(runs, stored):
    """Split each pointer run at every stored (vptr) address inside it."""
    for start, targets in runs:
        cuts = [i for i in range(len(targets)) if start + 4 * i in stored]
        if not cuts:
            continue
        for a, b in zip(cuts, cuts[1:] + [len(targets)]):
            yield start + 4 * a, targets[a:b]


PRIMITIVES = {'C': 'signed char', 'D': 'char', 'E': 'unsigned char', 'F': 'short', 'G': 'unsigned short',
              'H': 'int', 'I': 'unsigned int', 'J': 'long', 'K': 'unsigned long', 'M': 'float', 'N': 'double',
              'O': 'long double', 'X': 'void', '_N': 'bool', '_J': '__int64', '_K': 'unsigned __int64'}


class _Demangler:
    """Minimal MSVC type-name demangler for RTTI type descriptors.

    Covers the forms VC6 emits for class names: nested scopes, templates
    (?$Name@args@), back-references to earlier names (0-9), pointers and
    references to classes/structs/primitives, and integer template values.
    Anything else is returned verbatim rather than guessed.
    """

    def __init__(self, text):
        self.text, self.at, self.names = text, 0, []

    def peek(self, n=1):
        return self.text[self.at:self.at + n]

    def take(self, n=1):
        value = self.text[self.at:self.at + n]; self.at += n; return value

    def simple_name(self):
        if self.peek().isdigit():
            return self.names[int(self.take())]
        if self.peek(2) == '?$':
            self.take(2)
            outer = self.names; self.names = []
            name = self.text[self.at:self.text.index('@', self.at)]; self.at += len(name) + 1
            self.names.append(name)
            args = []
            while self.peek() != '@':
                args.append(self.type())
            self.take()
            self.names = outer
            value = '%s<%s>' % (name, ', '.join(args))
            self.names.append(value)
            return value
        end = self.text.index('@', self.at)
        name = self.text[self.at:end]; self.at = end + 1
        self.names.append(name)
        return name

    def qualified(self):
        parts = []
        while self.peek() != '@':
            parts.append(self.simple_name())
        self.take()
        return '::'.join(reversed(parts))

    def type(self):
        code = self.peek()
        if self.peek(2) in PRIMITIVES:
            return PRIMITIVES[self.take(2)]
        if code in PRIMITIVES:
            self.take(); return PRIMITIVES[code]
        if code in 'PQRS':                     # pointer (with cv qualifier letter)
            self.take(); self.take(); return self.type() + ' *'
        if code == 'A':                        # reference
            self.take(); self.take(); return self.type() + ' &'
        if code in 'UVW':                      # struct / class / enum
            self.take()
            if code == 'W':
                self.take()
            return self.qualified()
        if code == '$' and self.peek(2) == '$0':
            self.take(2); return self.number()
        raise ValueError('unsupported type code ' + self.text[self.at:])

    def number(self):
        negative = self.peek() == '?'
        if negative:
            self.take()
        if self.peek().isdigit():
            value = int(self.take()) + 1
        else:
            end = self.text.index('@', self.at)
            value = sum((ord(c) - ord('A')) << (4 * i) for i, c in enumerate(reversed(self.text[self.at:end])))
            self.at = end + 1
        return str(-value if negative else value)


def demangle_type(raw):
    """'.?AVFoo@Bar@@' -> 'Bar::Foo'; templates become Name<Args>."""
    if not raw.startswith(('.?AV', '.?AU')):
        return raw
    try:
        demangler = _Demangler(raw[4:])
        value = demangler.qualified()
        return value if demangler.at == len(demangler.text) else raw
    except (ValueError, IndexError):
        return raw


def rtti(read, vtable):
    """Decode the MSVC RTTI complete object locator preceding a vtable.

    Returns dict(name, offset, bases=[(name, mdisp)]) or None. The locator
    pointer sits in the dword before slot 0; its type descriptor holds the
    mangled class name and its hierarchy descriptor the ordered base list.
    """
    try:
        dword = lambda va: struct.unpack('<I', read(va, 4))[0]
        locator = dword(vtable - 4)
        signature, offset, _, descriptor, hierarchy = struct.unpack('<5I', read(locator, 20))
        if signature != 0:
            return None
        def type_name(td):
            raw = read(td + 8, 256).split(b'\0')[0].decode('ascii')
            return demangle_type(raw)
        name = type_name(descriptor)
        _, attributes, count, array = struct.unpack('<4I', read(hierarchy, 16))
        bases = []
        for index in range(1, min(count, 64)):
            base = dword(array + 4 * index)
            td, contained, mdisp, pdisp, vdisp = struct.unpack('<IIiii', read(base, 20))
            bases.append((type_name(td), mdisp))
        return dict(name=name, offset=offset, bases=bases, multiple=bool(attributes & 1),
                    virtual=bool(attributes & 2))
    except Exception:
        return None


def analyse(pe, functions, accepted, decoder, read=None):
    base = pe.OPTIONAL_HEADER.ImageBase
    sections = {s.Name.rstrip(b'\0').decode(errors='replace'): s for s in pe.sections}
    text_section = next(s for s in pe.sections if s.Characteristics & 0x20)
    text = text_section.get_data()[:text_section.Misc_VirtualSize]
    text_base = base + text_section.VirtualAddress
    entries = set(functions)
    runs = []
    for name, section in sections.items():
        if section is text_section or not section.Characteristics & 0x40:
            continue
        runs += list(pointer_runs(section.get_data()[:section.Misc_VirtualSize],
                                  base + section.VirtualAddress, entries))
    spans = function_spans(functions); starts = [s[0] for s in spans]
    stored = {}
    for start, targets in runs:
        for index in range(len(targets)):
            address = start + 4 * index
            sites = store_sites(decoder, text, text_base, address)
            if sites:
                stored[address] = sites
    lengths = {e: sum(int(s['end_inclusive'], 16) + 1 - int(s['start'], 16) for s in r['ranges'])
               for e, r in functions.items()}
    tables = []
    for address, targets in split_runs(runs, stored):
        unique = list(dict.fromkeys(targets))
        writers = sorted({containing(spans, starts, site) for site in stored[address]} - {None})
        members = list(dict.fromkeys(unique + writers))
        done = [e for e in members if e in accepted]
        info = rtti(read, address) if read else None
        tables.append(dict(vtable='%08x' % address, class_name=info['name'] if info else None,
                           object_offset=info['offset'] if info else None,
                           bases=[dict(name=n, offset=o) for n, o in info['bases']] if info else [],
                           slots=len(targets), unique_slots=len(unique),
                           slot_entries=['%08x' % e for e in targets],
                           vptr_writers=['%08x' % e for e in writers],
                           accepted_functions=len(done), member_functions=len(members),
                           accepted_bytes=sum(accepted[e] for e in done),
                           remaining_bytes=sum(lengths[e] for e in members if e not in accepted)))
    slot_owner = {}
    for table in tables:
        for slot in set(table['slot_entries']):
            slot_owner.setdefault(slot, []).append(table['vtable'])
    for table in tables:
        shared = Counter(other for slot in set(table['slot_entries']) for other in slot_owner[slot]
                         if other != table['vtable'])
        table['most_shared'] = (dict(vtable=shared.most_common(1)[0][0], slots=shared.most_common(1)[0][1])
                                if shared else None)
    tables.sort(key=lambda t: -t['remaining_bytes'])
    return tables


def write_markdown(path, tables):
    lines = ['# Vtable class inventory (hypotheses)', '',
             '%d vtables; %d slot/writer functions accepted; %d body bytes remaining in members.' % (
                 len(tables), sum(t['accepted_functions'] for t in tables),
                 sum(t['remaining_bytes'] for t in tables)), '',
             '| vtable | class (RTTI) | bases | slots | writers | accepted | remaining bytes |',
             '| --- | --- | --- | ---: | --- | ---: | ---: |']
    for t in tables:
        name = (t['class_name'] or '?') + ('' if not t['object_offset'] else ' @+0x%x' % t['object_offset'])
        bases = ' < '.join(b['name'] for b in t['bases'][:4]) + (' ...' if len(t['bases']) > 4 else '')
        lines.append('| %s | %s | %s | %d | %s | %d/%d | %d |' % (
            t['vtable'], name, bases, t['slots'],
            ' '.join(t['vptr_writers'][:3]) + (' ...' if len(t['vptr_writers']) > 3 else ''),
            t['accepted_functions'], t['member_functions'], t['remaining_bytes']))
    path.write_text('\n'.join(lines) + '\n')


def write_hierarchy(path, tables):
    """Tracked navigation doc: RTTI class tree with vtables and progress."""
    primary = {}
    for t in tables:
        if t['class_name'] and not t['object_offset']:
            primary.setdefault(t['class_name'], t)
    parent = {name: (t['bases'][0]['name'] if t['bases'] else None) for name, t in primary.items()}
    children = {}
    for name, base in parent.items():
        children.setdefault(base if base in primary else None, []).append(name)
    lines = ['# Original class hierarchy (from RTTI)', '',
             'Generated by `tools/original_target/class_inventory.py --write-docs` from the',
             'MSVC RTTI in the supplied executable: original class names, single-inheritance',
             'chains (first base) and primary vtables. Member counts are vtable slots plus',
             'vptr-writing functions (constructor/destructor candidates); "accepted" counts',
             'those with exact recovered source. Secondary vtables of multiple inheritance',
             'and classes without virtual functions are not listed.', '',
             '%d classes with primary vtables.' % len(primary), '']
    def walk(name, depth):
        t = primary[name]
        lines.append('%s- `%s` vtable `0x%s`, %d slots, %d/%d members accepted' % (
            '  ' * depth, name, t['vtable'].upper(), t['slots'], t['accepted_functions'], t['member_functions']))
        for child in sorted(children.get(name, [])):
            walk(child, depth + 1)
    for root in sorted(children.get(None, [])):
        walk(root, 0)
    path.write_text('\n'.join(lines) + '\n')


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--output', type=Path, default=REPOSITORY / 'build/classes')
    parser.add_argument('--config', type=Path, default=REPOSITORY / 'private/original-target.local.json')
    parser.add_argument('--write-docs', action='store_true', help='also write docs/CLASS_HIERARCHY.md')
    args = parser.parse_args()
    import capstone
    import pefile
    from inventory import Inventory
    from verify_manifest import Audit
    config = json.loads(args.config.read_bytes())
    audit = Audit(REPOSITORY, config['executable'])
    catalog = json.loads((REPOSITORY / 'manifests/original_target.json').read_bytes())
    accepted = {r['entry']: r['body_bytes'] for r in catalog['regions']}
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    tables = analyse(audit.pe, Inventory().all_functions(), accepted, decoder, audit.original)
    args.output.mkdir(parents=True, exist_ok=True)
    (args.output / 'vtables.json').write_text(json.dumps(tables, indent=1))
    write_markdown(args.output / 'classes.md', tables)
    if args.write_docs:
        write_hierarchy(REPOSITORY / 'docs/CLASS_HIERARCHY.md', tables)
        # Byte-free facts for generators and source organization.
        facts = [dict(vtable=t['vtable'], class_name=t['class_name'], object_offset=t['object_offset'],
                      bases=t['bases'], slots=t['slot_entries'], vptr_writers=t['vptr_writers'])
                 for t in sorted(tables, key=lambda t: t['vtable'])]
        (REPOSITORY / 'manifests/rtti_classes.json').write_text(json.dumps(dict(
            source='MSVC RTTI and vtable runs in the supplied executable (class_inventory.py)',
            vtables=facts), indent=1) + '\n')
    print('%d vtables -> %s' % (len(tables), args.output / 'classes.md'))


if __name__ == '__main__':
    main()
