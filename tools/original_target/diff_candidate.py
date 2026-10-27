#!/usr/bin/env python3
"""Compile one scratch candidate and score it instruction-by-instruction.

This is the fast iteration loop: edit a candidate source, rerun (or use
--watch), read the aligned diff, repeat. It never installs a candidate or
touches the canonical catalog; acceptance still goes through
compile_candidates.py and the strict audit.

Relocations are resolved from in-source `// @ref NAME=ADDRESS` comments, canonical accepted symbols/references, from
address-named symbols (FUN_00401000, DAT_00830b50, _data_402190_4022c0) and
from --ref NAME=ADDRESS. Unresolved relocations are shown as ?name and match
any address operand in the loose score, so a missing binding never hides
otherwise-correct code generation.
"""
import argparse
import difflib
import catalog_io
import json
from pathlib import Path
import re
import struct
import sys
import time

REPOSITORY = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))

OPTIONS = [['/O2', '/Ob2', '/G5', '/Gy'], ['/O2', '/Ob2', '/G6', '/Gy'],
           ['/O1', '/Ob2', '/G5', '/Gy'], ['/O2', '/Ob2', '/G5', '/Gy', '/Gr'],
           ['/O2', '/Ob1', '/G5', '/Gy'], ['/O2', '/Ob2', '/G5', '/Gy', '/GR']]
BASE_ARGS = ['/nologo', '/c', '/TP', '/Zp4', '/GX-', '/GR-', '/W3']


def compiler_args(options):
    """BASE_ARGS plus an option set; /GR (RTTI) replaces the base /GR-."""
    from canonical import compiler_arguments
    return compiler_arguments(options)
ADDRESS = re.compile(r'0x[0-9a-f]+')
SOURCE_REF = re.compile(r'@ref\s+([^\s=]+)=(?:0x)?([0-9a-fA-F]+)')
GHIDRA_NAME = re.compile(r'(?:FUN|DAT|PTR|SUB|LAB|thunk_FUN|switchD)_([0-9a-fA-F]{8})')
POINTER_NAME = re.compile(r'(?:^|[^A-Za-z0-9])_?PTR_(?:[A-Za-z0-9_]+_)?([0-9a-fA-F]{8})(?=$|@)')
STRING_NAME = re.compile(r'(?:^|_)[su]_\w*_([0-9a-f]{8})$')
OWNED_NAME = re.compile(r'_(?:data|global|import|vtable|string)_[0-9a-f]+_([0-9a-f]{6,8})')


def address_from_name(name):
    """Return the address a symbol name declares, or None."""
    for pattern in (POINTER_NAME, GHIDRA_NAME, OWNED_NAME, STRING_NAME):
        found = pattern.findall(name)
        if found:
            return int(found[-1], 16)
    return None


def canonical_references(catalog):
    """Map symbol name (or mangled prefix) -> address from accepted regions."""
    references = {}
    for region in catalog.get('regions', []):
        references.setdefault(region['symbol'], region['entry'])
        # Only bindings a relocation of the region actually used are evidence;
        # the rest of a region's reference map was merely available to it.
        for binding in region.get('relocations', []):
            references.setdefault(binding['symbol'], binding['target'])
    return references


def known_references(catalog):
    """Every name the tools can bind: accepted symbols, import slots, original names."""
    references = canonical_references(catalog)
    root = Path(__file__).resolve().parents[2] / 'manifests'
    imports = root / 'imports.json'
    if imports.exists():
        for item in json.loads(imports.read_text())['imports']:
            if item.get('convention') == '__stdcall' and item.get('parameters') is not None:
                references.setdefault('__imp__%s@%d' % (item['name'], 4 * item['parameters']), int(item['iat'], 16))
            references.setdefault('__imp__' + item['name'], int(item['iat'], 16))
    # Recorded names come before the RTTI guesses below, so a symbols.json
    # entry corrects a class whose slot 0 is not its deleting destructor.
    symbols = root / 'symbols.json'
    if symbols.exists():
        for item in json.loads(symbols.read_text())['symbols']:
            if item.get('mangled_prefix'):
                references.setdefault(item['mangled_prefix'], int(item['address'], 16))
                if item['mangled_prefix'].startswith('??_G'):
                    # VC6 vtables name the vector deleting destructor (??_E),
                    # which it aliases to the scalar one when no array delete
                    # is needed.
                    references.setdefault('??_E' + item['mangled_prefix'][4:], int(item['address'], 16))
    classes = root / 'rtti_classes.json'
    if classes.exists():
        for table in json.loads(classes.read_text())['vtables']:
            name = table['class_name']
            if name and not table['object_offset'] and re.fullmatch(r'\w+(::\w+)*', name):
                mangled = '@'.join(reversed(name.split('::')))
                references.setdefault('??_7%s@@6B@' % mangled, int(table['vtable'], 16))
                # Slot 0 holds the deleting destructor (vector name aliases
                # scalar), except in COM-derived classes, whose primary
                # vtable starts with QueryInterface.
                com = any(b['name'] in ('IUnknown', 'IPersist', 'IPersistStream') for b in table.get('bases', []))
                if table['slots'] and not com:
                    references.setdefault('??_E%s@@' % mangled, int(table['slots'][0], 16))
                    references.setdefault('??_G%s@@' % mangled, int(table['slots'][0], 16))
    return references


def lookup(name, references):
    if name in references:
        return references[name]
    for key, value in references.items():
        if key.startswith('?') and name.startswith(key):
            return value
    return address_from_name(name)


def resolve(raw, relocs, symbols, entry, references):
    """Patch resolvable relocations; return bytes and unresolved {offset: name}."""
    actual = bytearray(raw); unresolved = {}
    for offset, symbol_index, kind in relocs:
        name = symbols[symbol_index]['name']
        target = lookup(name, references)
        if target is None or kind not in (6, 20) or offset + 4 > len(actual):
            unresolved[offset] = name
            struct.pack_into('<I', actual, offset, 0)
            continue
        addend = struct.unpack_from('<I', actual, offset)[0]
        value = target + addend - (entry + offset + 4 if kind == 20 else 0)
        struct.pack_into('<I', actual, offset, value & 0xffffffff)
    return bytes(actual), unresolved


def disassemble(decoder, data, address, unresolved=None):
    """Return instruction rows; undecodable bytes become .byte rows."""
    unresolved = unresolved or {}; rows = []; offset = 0
    while offset < len(data):
        decoded = next(decoder.disasm(data[offset:], address + offset, 1), None)
        if decoded is None:
            rows.append(dict(offset=offset, size=1, text='.byte 0x%02x' % data[offset], loose='.byte',
                             bytes=data[offset:offset + 1].hex()))
            offset += 1; continue
        text = (decoded.mnemonic + ' ' + decoded.op_str).strip()
        names = [n for o, n in unresolved.items() if offset <= o < offset + decoded.size]
        if names:
            text = decoded.mnemonic + ' ?' + ','.join(names)
        loose = decoded.mnemonic + ' ' + ADDRESS.sub(
            lambda m: 'A' if int(m.group(0), 16) >= 0x10000 else m.group(0), decoded.op_str)
        if names:
            loose = decoded.mnemonic + ' A'
        rows.append(dict(offset=offset, size=decoded.size, text=text, loose=loose.strip(),
                         bytes=data[offset:offset + decoded.size].hex()))
        offset += decoded.size
    return rows


def score(original, candidate):
    """Align two instruction lists; return summary and aligned row pairs."""
    matcher = difflib.SequenceMatcher(None, [r['loose'] for r in original],
                                      [r['loose'] for r in candidate], autojunk=False)
    pairs = []; exact = loose = 0
    for tag, i1, i2, j1, j2 in matcher.get_opcodes():
        if tag == 'equal':
            for a, b in zip(original[i1:i2], candidate[j1:j2]):
                same = a['text'] == b['text']; exact += same; loose += 1
                pairs.append((' ' if same else '~', a, b))
            continue
        left, right = original[i1:i2], candidate[j1:j2]
        for index in range(max(len(left), len(right))):
            a = left[index] if index < len(left) else None
            b = right[index] if index < len(right) else None
            pairs.append(('|' if a and b else '<' if a else '>', a, b))
    total = len(original) + len(candidate)
    shape = difflib.SequenceMatcher(None, [r['loose'].split(' ')[0] for r in original],
                                    [r['loose'].split(' ')[0] for r in candidate], autojunk=False)
    return dict(shape_score=round(100.0 * shape.ratio(), 2),original_instructions=len(original), candidate_instructions=len(candidate),
                exact_instructions=exact, loose_instructions=loose,
                score=round(100.0 * 2 * exact / total, 2) if total else 100.0,
                loose_score=round(100.0 * 2 * loose / total, 2) if total else 100.0,
                first_difference=next((i for i, p in enumerate(pairs) if p[0] != ' '), None)), pairs


def render(pairs, width=46, context=None):
    lines = []
    keep = set(range(len(pairs)))
    if context is not None:
        changed = [i for i, p in enumerate(pairs) if p[0] != ' ']
        keep = {j for i in changed for j in range(i - context, i + context + 1)}
    skipped = False
    for index, (mark, a, b) in enumerate(pairs):
        if index not in keep:
            if not skipped: lines.append('  ...')
            skipped = True; continue
        skipped = False
        left = ('%04x %s' % (a['offset'], a['text']))[:width] if a else ''
        right = ('%04x %s' % (b['offset'], b['text']))[:width] if b else ''
        lines.append('%-*s %s %s' % (width, left, mark, right))
    return '\n'.join(lines)


def split_padding(data, length):
    """Separate trailing compiler alignment NOPs beyond the original body.

    The linker-facing padding is frozen separately; scoring compares bodies.
    """
    end = len(data)
    while end > length and data[end - 1] == 0x90:
        end -= 1
    return data[:end], len(data) - end


def pick_symbol(coff, prefix, entry):
    if prefix:
        return coff.function(prefix)
    functions = [s for s in coff.symbols.values() if s['section'] > 0 and s['type'] & 0x20 and
                 s['storage'] == 2 and coff.sections[s['section'] - 1]['flags'] & 0x20]
    named = [s for s in functions if ('%x' % entry) in s['name'].lower()]
    chosen = functions if len(functions) == 1 else named
    if len(chosen) != 1:
        raise ValueError('Choose --symbol from: ' + ', '.join(s['name'] for s in functions))
    return coff.function(chosen[0]['name'])


def compile_variants(config, source, output, variants, includes=()):
    from build import wine_command, win
    commands = []
    for index, options in enumerate(variants):
        directory = output / str(index); directory.mkdir(parents=True, exist_ok=True)
        obj = directory / 'candidate.obj'
        if obj.exists(): obj.unlink()
        args = (compiler_args(options) + ['/I' + win(path) for path in includes] +
                ['/I' + win(REPOSITORY / 'src'), '/Fo' + win(obj), win(source)])
        commands.append('"' + win(Path(config['compiler_directory']) / 'CL.EXE') + '" ' +
                        ' '.join('"' + a + '"' for a in args) + ' >"' + win(directory / 'compiler.log') + '" 2>&1')
    wine_command(config, output, commands + ['exit /b 0'], 'diff-compile')
    return [output / str(i) / 'candidate.obj' for i in range(len(variants))]


def run_once(args, config, audit_original, decoder, references):
    from coff import Coff
    entry = int(args.entry, 16)
    length = args.length or args.frozen_lengths.get(entry)
    if length is None:
        from inventory import Inventory
        length = Inventory().body_length(entry)
    original = disassemble(decoder, audit_original(entry, length), entry)
    output = args.output.resolve(); output.mkdir(parents=True, exist_ok=True)
    source = output / 'candidate.cpp'; source.write_bytes(args.source.read_bytes())
    variants = OPTIONS[:3] if args.options == 'all' else [OPTIONS[int(i)] for i in args.options.split(',')]
    references = dict(references)
    for name, value in SOURCE_REF.findall(source.read_text(errors='replace')):
        references[name] = int(value, 16)
    started = time.monotonic()
    objects = compile_variants(config, source, output, variants, args.include)
    compile_seconds = time.monotonic() - started
    results = []
    for options, obj in zip(variants, objects):
        row = dict(options=options)
        if not obj.exists():
            row.update(status='compile-failed', log=(obj.parent / 'compiler.log').read_text(errors='replace'))
            results.append(row); continue
        try:
            coff = Coff(obj.read_bytes())
            symbol, section, start, end = pick_symbol(coff, args.symbol, entry)
            relocs = [(o - start, s, k) for o, s, k in section['relocs'] if start <= o < end]
            data, unresolved = resolve(section['data'][start:end], relocs, coff.symbols, entry, references)
            body, padding = split_padding(data, length)
            candidate = disassemble(decoder, body, entry, unresolved)
            summary, pairs = score(original, candidate)
            exact = not unresolved and body == audit_original(entry, length)
            row.update(status='byte-exact' if exact else 'mismatch', symbol=symbol['name'],
                       unresolved=sorted(set(unresolved.values())), candidate_padding=padding, **summary)
            row['pairs'] = pairs
        except ValueError as error:
            row.update(status='refused', reason=str(error))
        results.append(row)
    return entry, length, compile_seconds, results


def report(args, entry, length, seconds, results):
    best = max((r for r in results if 'score' in r), key=lambda r: (r['status'] == 'byte-exact', r['score']),
               default=None)
    print('%08x  %d original bytes  compile %.1fs' % (entry, length, seconds))
    for r in results:
        if 'score' in r:
            print('  %-24s %-10s score %6.2f  loose %6.2f  shape %6.2f  insns %d/%d%s' % (
                ' '.join(r['options']), r['status'], r['score'], r['loose_score'], r['shape_score'],
                r['original_instructions'], r['candidate_instructions'],
                '  unresolved: ' + ', '.join(r['unresolved']) if r['unresolved'] else ''))
        else:
            print('  %-24s %s %s' % (' '.join(r['options']), r['status'], r.get('reason', '')))
            if r.get('log'): print('    ' + r['log'].strip().replace('\n', '\n    '))
    if best:
        print('\noriginal'.ljust(48) + '  candidate (' + ' '.join(best['options']) + ')')
        print(render(best['pairs'], context=None if args.full else 3))
    saved = [{k: v for k, v in r.items() if k != 'pairs'} for r in results]
    for r, s in zip(results, saved):
        if 'pairs' in r:
            s['diff'] = [[m, a and a['text'], b and b['text']] for m, a, b in r['pairs']]
    (args.output / 'diff.json').write_text(json.dumps(dict(entry='%08x' % entry, length=length,
                                                           source=str(args.source), results=saved), indent=1))


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('source', type=Path, help='scratch candidate .cpp')
    parser.add_argument('--entry', required=True, help='original entry address (hex)')
    parser.add_argument('--length', type=int, help='original body bytes (default: --refs-json frozen bound, else inventory extent)')
    parser.add_argument('--symbol', help='function symbol prefix in the object (default: auto)')
    parser.add_argument('--options', default='all', help="'all' or comma list of variant indexes 0-5 (3 = /Gr, 4 = /Ob1, 5 = /GR RTTI, only on request)")
    parser.add_argument('--ref', action='append', default=[], help='NAME=ADDRESS extra relocation binding')
    parser.add_argument('--include', type=Path, action='append', default=[],
                        help='extra include directory searched before root src/')
    parser.add_argument('--refs-json', type=Path, action='append', default=[],
                        help='JSON with "references" maps (a candidate population or region)')
    parser.add_argument('--output', type=Path, help='scratch directory (default build/diff/<entry>)')
    parser.add_argument('--full', action='store_true', help='show every instruction, not only changes')
    parser.add_argument('--watch', action='store_true', help='rerun whenever the source changes')
    parser.add_argument('--config', type=Path, default=REPOSITORY / 'private/original-target.local.json')
    args = parser.parse_args()
    args.output = args.output or REPOSITORY / 'build/diff' / args.entry.lower()
    import capstone
    from verify_manifest import Audit
    config = json.loads(args.config.read_bytes())
    audit = Audit(REPOSITORY, config['executable'])
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    references = known_references(catalog_io.load(catalog_io.locate(REPOSITORY), references=False))
    # RTTI type descriptors (??_R0) and the type_info vtable, read from the
    # original's RTTI, for dynamic_cast/typeid under the /GR variant.
    for name, value in audit.original_type_descriptors().items():
        references.setdefault(name, value)
    args.frozen_lengths = {}
    for path in args.refs_json:
        document = json.loads(path.read_bytes())
        rows = document.get('candidates', document.get('regions', [document]))
        for row in rows:
            if 'entry' in row and 'body_bytes' in row:
                key = row['entry'] if isinstance(row['entry'], int) else int(row['entry'], 16)
                args.frozen_lengths.setdefault(key, row['body_bytes'])
            for name, value in row.get('references', {}).items():
                references[name] = value if isinstance(value, int) else int(value, 16)
    for item in args.ref:
        name, value = item.split('=', 1); references[name] = int(value, 16)
    last = None
    while True:
        stamp = args.source.stat().st_mtime
        if stamp != last:
            last = stamp
            report(args, *run_once(args, config, audit.original, decoder, references))
        if not args.watch:
            break
        time.sleep(0.5)


if __name__ == '__main__':
    main()
