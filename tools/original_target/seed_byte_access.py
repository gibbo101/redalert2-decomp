"""Conservative byte-lvalue repairs; no new storage, callable or game layout."""
import re


def integer_literal(text):
    if not re.fullmatch(r'(?:0[xX][0-9a-fA-F]+|[0-9]+)', text):
        return None
    try:
        return int(text, 16 if text.lower().startswith('0x') else 8 if len(text) > 1 and text[0] == '0' else 10)
    except ValueError:
        return None


def element_bytes(kind):
    kind = ' '.join(kind.split())
    if re.search(r'\b(?:const|volatile)\b', kind):
        return None
    if kind.endswith('*'):
        return 4                  # fixed native i386 target, not host sizeof
    return {'char': 1, 'unsigned char': 1, 'signed char': 1, 'byte': 1, 'uchar': 1,
            'undefined': 1, 'undefined1': 1, 'short': 2, 'unsigned short': 2,
            'ushort': 2, 'undefined2': 2, 'int': 4, 'unsigned int': 4,
            'uint': 4, 'long': 4, 'unsigned long': 4, 'ulong': 4, 'undefined4': 4,
            'float': 4, 'double': 8, '__int64': 8, 'unsigned __int64': 8,
            'longlong': 8, 'ulonglong': 8, 'undefined8': 8, 'qword': 8}.get(kind)


def array_byte_parts(body, view, declarations, parameter_names):
    """Preserve explicit one-byte slices of known scalar/pointer array elements.

    Only constant, in-bounds subscripts and byte offsets are repaired. This
    uses an existing declaration; it does not certify its original identity or
    infer an array from stack size. Character access preserves other bytes.
    """
    slots = {}
    for kind, name, array in declarations:
        slots.setdefault(name, []).append((kind, array))
    for name in parameter_names:
        slots.setdefault(name, []).append(('', None))
    pattern = re.compile(r'\b([A-Za-z_]\w*)\s*\[\s*(0[xX][0-9a-fA-F]+|[0-9]+)\s*\]'
                         r'\s*\._([0-9]+)_1_\b')
    edits = []
    for match in pattern.finditer(view):
        before = view[:match.start()].rstrip()
        if (before.endswith(('.', '->', '::')) or
                re.search(r'#\s*(?:define|undef)\s+' + re.escape(match[1]) + r'\b', view)):
            continue
        values = slots.get(match[1], [])
        if len(values) != 1:
            continue
        kind, array = values[0]
        size = element_bytes(kind)
        extent = re.fullmatch(r'\[\s*(0[xX][0-9a-fA-F]+|[0-9]+)\s*\]', (array or '').strip())
        count = integer_literal(extent[1]) if extent else None
        index, offset = integer_literal(match[2]), int(match[3])
        if size is None or count is None or count < 1 or index is None or not 0 <= index < count or not 0 <= offset < size:
            continue
        expression = '(*((unsigned char *)&%s[%s] + %d))' % (match[1], match[2], offset)
        edits.append((match.start(), match.end(), expression))
    for start, end, expression in reversed(edits):
        body = body[:start] + expression + body[end:]
    return body


OFFSET = re.compile(r'\(\s*&\s*(SUB_([0-9a-fA-F]{8}))\s*\)\s*'
                    r'\[\s*(_?DAT_[0-9a-fA-F]{8})\s*\]')


def byte_context(body, start, end, local_types):
    before, after = body[:start], body[end:]
    # Initial repair is read-only. Do not infer signedness for wide arithmetic,
    # call arguments or stores from an untyped label spelling.
    if re.match(r'\s*(?:=(?!=)|\+=|-=|\+\+|--|\*=|/=|&=|\|=|\^=)', after):
        return False
    if (re.search(r'(?:\(|&&|\|\||\breturn)\s*$', before) and
            re.match(r"\s*(?:==|!=)\s*(?:'\\0'|0[uU]?)\s*(?=[);?:,]|&&|\|\||$)", after)):
        return True
    assigned = re.search(r'(?:^|[;{}\n])\s*([A-Za-z_]\w*)\s*=\s*$', before)
    if assigned and local_types.get(assigned[1], '').strip() in ('char', 'byte', 'uchar', 'undefined1', 'signed char', 'unsigned char'):
        return bool(re.match(r'\s*;', after))
    return False


def offset_groups(body, view, global_types, shared, local_types, local_names, image_base):
    groups = {}
    matches = list(OFFSET.finditer(view))
    for match in matches:
        label, offset, symbol = match[1], int(match[2], 16), match[3]
        address = int(symbol[-8:], 16)
        known = shared.get(address)
        kind = global_types.get(symbol, '')
        if (not known or known['kind'] != kind or not kind.rstrip().endswith('*') or
                re.search(r'\b(?:code|const|volatile)\b', kind) or not 0 <= offset < image_base or
                symbol in local_names or label in local_names or
                re.search(r'#\s*(?:define|undef)\s+(?:' + re.escape(symbol) + '|' + re.escape(label) + r')\b', view) or
                re.search(r'\b' + re.escape(symbol) + r'\s*(?:=(?!=)|\+=|-=|\+\+|--)', view) or
                re.search(r'&\s*\b' + re.escape(symbol) + r'\b', view) or
                not byte_context(body, match.start(), match.end(), local_types)):
            continue
        # Any other use keeps the name unresolved; never redirect a real call,
        # address value, macro, shadow or independently referenced label.
        all_uses = len(re.findall(r'\b' + label + r'\b', view))
        indexed_uses = sum(other[1] == label for other in matches)
        if all_uses != indexed_uses:
            continue
        groups.setdefault((address, offset), []).append(match)
    return groups


def inspect_byte_fields(entry, ranges, read_original, pairs):
    """Observe byte-read sites with block-local pointer provenance.

    Calls/branches discard provenance; unknown indirect jumps stop that path.
    This proves observed local access widths, not exclusive field width,
    function bounds, roots or correspondence to other source occurrences.
    Frozen range bytes are checked against the independently hashed target.
    """
    import capstone
    from capstone import x86_const as x86
    chunks = []
    for span in ranges:
        at = int(span['start'], 16)
        raw = bytes.fromhex(span['bytes_hex'])
        if read_original(at, len(raw)) != raw:
            return {}
        chunks.append((at, at + len(raw), raw))
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    globals_ = {address for address, _ in pairs}
    result = {pair: dict(sizes=set(), read_sites=[]) for pair in pairs}

    def family(name):
        for full, names in [('eax', ('eax', 'ax', 'al', 'ah')), ('ebx', ('ebx', 'bx', 'bl', 'bh')),
                            ('ecx', ('ecx', 'cx', 'cl', 'ch')), ('edx', ('edx', 'dx', 'dl', 'dh')),
                            ('esi', ('esi', 'si')), ('edi', ('edi', 'di')), ('ebp', ('ebp', 'bp')), ('esp', ('esp', 'sp'))]:
            if name in names:
                return full
        return None

    def decode(at):
        for start, end, raw in chunks:
            if start <= at < end:
                return next(decoder.disasm(raw[at-start:at-start+15], at, 1), None)
        return None

    pending, visited = [entry], set()
    while pending:
        at, registers = pending.pop(), {}
        while at not in visited:
            ins = decode(at)
            if ins is None:
                break
            visited.add(at)
            if (ins.group(capstone.CS_GRP_RET) or ins.mnemonic.startswith('iret') or
                    ins.mnemonic in ('int', 'int1', 'int3', 'into', 'ud0', 'ud1', 'ud2', 'hlt',
                                     'syscall', 'sysret', 'sysenter', 'sysexit', 'rsm', 'ljmp', 'lcall')):
                break
            flat = ins.addr_size == 4 and not any(
                operand.type == x86.X86_OP_MEM and operand.mem.segment for operand in ins.operands)
            if not flat:
                registers.clear()
            for operand in ins.operands:
                if flat and operand.type == x86.X86_OP_MEM and not operand.mem.index:
                    address = registers.get(family(ins.reg_name(operand.mem.base)))
                    pair = (address, operand.mem.disp)
                    if pair in result:
                        data_operation = ins.mnemonic in ('mov', 'movzx', 'movsx', 'cmp', 'test')
                        result[pair]['sizes'].add(operand.size if data_operation else None)
                        if data_operation and operand.access & capstone.CS_AC_READ:
                            result[pair]['read_sites'].append(ins.address)
            copied = None
            if flat and ins.mnemonic == 'mov' and len(ins.operands) == 2 and ins.operands[0].type == x86.X86_OP_REG and ins.operands[0].size == 4:
                source = ins.operands[1]
                if source.type == x86.X86_OP_REG and source.size == 4:
                    copied = registers.get(family(ins.reg_name(source.reg)))
                elif (source.type == x86.X86_OP_MEM and source.size == 4 and not source.mem.base and not source.mem.index and source.mem.disp in globals_):
                    copied = source.mem.disp
            try:
                _, writes = ins.regs_access()
                for register in writes:
                    registers.pop(family(ins.reg_name(register)), None)
            except capstone.CsError:
                registers.clear()
            if copied is not None:
                registers[family(ins.reg_name(ins.operands[0].reg))] = copied
            # A saved pointer no longer proves the current global after an
            # overlapping or possibly aliasing write. Do not assume disjoint
            # stack/heap/global storage merely from Ghidra's variable names.
            if any(operand.type == x86.X86_OP_MEM and operand.access & capstone.CS_AC_WRITE
                   for operand in ins.operands):
                registers.clear()
            following = ins.address + ins.size
            if ins.group(capstone.CS_GRP_JUMP):
                if len(ins.operands) == 1 and ins.operands[0].type == x86.X86_OP_IMM:
                    pending.append(ins.operands[0].imm & 0xffffffff)
                if ins.mnemonic != 'jmp':
                    pending.append(following)
                break
            if ins.mnemonic == 'call':
                registers.clear()
            at = following
    return {pair: value for pair, value in result.items() if value['sizes'] == {1} and value['read_sites']}


def apply_offset_groups(body, groups, facts):
    edits, notes = [], []
    for pair, matches in sorted(groups.items()):
        # A lone local byte observation must not repair an arbitrary number of
        # unconnected source uses, including text beyond truncated inventories.
        if pair not in facts or len(set(facts[pair]['read_sites'])) != len(matches):
            continue
        for match in matches:
            edits.append((match.start(), match.end(), '(((unsigned char const *)%s)[0x%x])' % (match[3], pair[1])))
        notes.append('// Low offset %08x from pointer global %08x: %d local byte-read sites and explicit byte/zero source uses; '
                     'count correspondence is a seed hypothesis, not exclusive width, complete bounds/root or source acceptance proof.' %
                     (pair[1], pair[0], len(matches)))
    for start, end, expression in sorted(edits, reverse=True):
        body = body[:start] + expression + body[end:]
    return body, notes
