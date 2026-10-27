#!/usr/bin/env python3
"""Draft readable member functions of a class from Ghidra and known layouts.

Given a class whose layout is declared in src/shared/ (members annotated
`// +0xNN`, bases included through the class chain from RTTI), this rewrites
the Ghidra export of each requested method into a class-aware first draft:

  *(int *)(param_1 + 0x14), param_1[5]    -> Filename
  (**(code **)(*param_1 + 0x34))()        -> Close()       (vtable slot names)
  FUN_00638c00(...)                       -> RawFileClass::Open(...)  (symbols.json)

Slot names come from manifests/rtti_classes.json and manifests/symbols.json;
unnamed slots become vslot_0xNN, unknown offsets stay as raw expressions with
a TODO. The draft is a starting point for diff_candidate.py iteration and
names nothing that is not already evidenced.

  class_seed.py --class CDFileClass --header shared/cd_file_class.hpp 470150 470250
"""
import argparse
import json
from pathlib import Path
import re
import sys

REPOSITORY = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))

from inventory import Inventory
from seed_candidate import parse_header, reindent

MEMBER = re.compile(r'^\s+([\w:<>\s\*&]+?)\s*\b(\w+)(?:\[[^\]]*\])?;\s*//\s*\+0x([0-9A-Fa-f]+)', re.M)
WIDTH = {'undefined1': 1, 'char': 1, 'byte': 1, 'uchar': 1, 'bool': 1, 'undefined2': 2, 'short': 2,
         'ushort': 2, 'word': 2}


def layout(header_names):
    """Member offset -> name from the given shared headers (and their includes)."""
    seen, members = set(), {}
    def read(name):
        if name in seen:
            return
        seen.add(name)
        path = REPOSITORY / 'src' / name
        text = path.read_text()
        for include in re.findall(r'#include "([^"]+)"', text):
            read(include)
        for kind, member, offset in MEMBER.findall(text):
            members[int(offset, 16)] = (member, kind.strip())
    for name in header_names:
        read(name)
    return members


def slot_names(class_name):
    """Vtable slot index -> method name for class_name (own or inherited)."""
    tables = json.loads((REPOSITORY / 'manifests/rtti_classes.json').read_text())['vtables']
    by_name = {t['class_name']: t for t in tables if t['class_name'] and not t['object_offset']}
    symbols = {int(s['address'], 16): s['name'] for s in
               json.loads((REPOSITORY / 'manifests/symbols.json').read_text())['symbols']}
    table = by_name.get(class_name)
    if table is None:
        return {}     # no vtable: nothing virtual to name
    chain = [class_name] + [b['name'] for b in table['bases']]
    names = {}
    for index in range(len(table['slots'])):
        for cls in chain:
            t = by_name.get(cls)
            if not t or index >= len(t['slots']):
                continue
            name = symbols.get(int(t['slots'][index], 16))
            if name and '::' in name and 'destructor' not in name:
                names[index] = re.sub(r'\(.*$', '', name.split('::')[-1])
                break
    return names


def function_names():
    return {int(s['address'], 16): re.sub(r'\(.*$', '', s['name']) for s in
            json.loads((REPOSITORY / 'manifests/symbols.json').read_text())['symbols']}


def rewrite(body, this, members, slots, functions):
    def member(offset, width=None):
        entry = members.get(offset)
        return entry[0] if entry else None

    # Virtual calls through the object's own vtable.
    def virtual(match):
        text = match.group(1)
        offset = int(text, 16) if text.startswith('0x') else int(text)
        name = slots.get(offset // 4, 'vslot_0x%x' % offset)
        return name + '('
    body = re.sub(r'\(\*\*\(code \*\*\)\(\*%s \+ (0x[0-9a-f]+|\d+)\)\)\(' % this, virtual, body)
    body = re.sub(r'\(\*\*\(code \*\*\)\*%s\)\(' % this, lambda m: slots.get(0, 'vslot_0x0') + '(', body)

    # Field accesses: *(T *)(this + 0xN), *(T *)((int)this + 0xN), this[k].
    def field(match):
        kind, offset = match.group(1), int(match.group(2), 16)
        name = member(offset)
        return name if name else match.group(0) + ' /* TODO: field +0x%x */' % offset
    body = re.sub(r'\*\((\w+) \*\)\(\(int\)%s \+ 0x([0-9a-f]+)\)' % this, field, body)
    body = re.sub(r'\*\((\w+) \*\)\(%s \+ 0x([0-9a-f]+)\)' % this, field, body)
    def indexed(match):
        offset = 4 * (int(match.group(1), 16) if match.group(1).startswith('0x') else int(match.group(1)))
        name = member(offset)
        return name if name else match.group(0)
    body = re.sub(r'\b%s\[(0x[0-9a-f]+|\d+)\]' % this, indexed, body)

    # Direct calls to functions with recorded names.
    def direct(match):
        address = int(match.group(1), 16)
        name = functions.get(address)
        return (name.replace('`', '').replace("'", '') if name else match.group(0)) + '('
    body = re.sub(r'\bFUN_([0-9a-f]{8})\(', direct, body)

    # bool members: Ghidra spells them as chars and 0/1.
    for name, kind in members.values():
        if kind == 'bool':
            body = re.sub(r'\(char\)%s\b' % name, name, body)
            body = re.sub(r'\b%s == \'\\0\'' % name, '!' + name, body)
            body = re.sub(r'\b%s != \'\\0\'' % name, name, body)
            body = re.sub(r'\b%s = 0;' % name, name + ' = false;', body)
            body = re.sub(r'\b%s = 1;' % name, name + ' = true;', body)
    body = re.sub(r'\n\s*return;\n\}$', '\n}', body.rstrip())
    return body


def draft(entry, class_name, headers, inventory):
    text = inventory.decompiled(entry)
    ret, conv, name, params, (start, end) = parse_header(text)
    this = params[0].split()[-1].lstrip('*') if conv in ('__thiscall', '__fastcall') and params else 'param_1'
    body = reindent(text[end:].strip())
    body = rewrite(body, this, layout(headers), slot_names(class_name), function_names())
    remaining = params[1:] if conv in ('__thiscall', '__fastcall') else params
    lines = ['// %s method at 0x%08x (class_seed.py draft; iterate with diff_candidate.py)' % (class_name, entry)]
    lines += ['#include "%s"' % h for h in headers]
    known = function_names().get(entry, '')
    method = known.split('::')[-1] if known.startswith(class_name + '::') else 'Method_%08x' % entry
    lines += ['', '%s %s::%s(%s)' % (ret, class_name, method, ', '.join(remaining) or 'void'), body, '']
    return '\n'.join(lines)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('entries', nargs='+')
    parser.add_argument('--class', dest='class_name', required=True)
    parser.add_argument('--header', action='append', required=True, help='shared header path relative to src/')
    parser.add_argument('--output', type=Path, default=REPOSITORY / 'build/class-work')
    args = parser.parse_args()
    inventory = Inventory()
    out = args.output / args.class_name; out.mkdir(parents=True, exist_ok=True)
    for item in args.entries:
        entry = int(item, 16)
        path = out / ('draft_%08x.cpp' % entry)
        path.write_text(draft(entry, args.class_name, args.header, inventory))
        print(path)


if __name__ == '__main__':
    main()
