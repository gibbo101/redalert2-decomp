"""Original-evidenced scratch word stores; no suffix-address or storage rule."""
import re


ASSIGNMENT = re.compile(
    r'(?m)^[ \t]*(_?DAT_([0-9a-fA-F]{8}))\s*=\s*CONCAT22\s*\(\s*'
    r'(_?DAT_[0-9a-fA-F]{8}_2)\s*,\s*\(\s*&\s*(_?DAT_([0-9a-fA-F]{8}))\s*\)'
    r'\s*\[\s*([A-Za-z_]\w*)\s*\]\s*\)\s*;[ \t]*(?=$|\n)')


def source_groups(body, view, declarations, params):
    """Only standalone, explicit preserved-high-half assignments are eligible.

    The high-token spelling is a filter, never evidence of another address.
    Ambiguous local scopes and indices remain unresolved.
    """
    declarations_of_builtin = re.finditer(
        r'(?:^|[;{}\n])[ \t]*((?:[A-Za-z_]\w*[ \t]+)+)[*& \t]*CONCAT22\s*\(', view)
    if (any(match[1].split()[0] not in ('return', 'throw', 'delete') for match in declarations_of_builtin) or
            re.search(r'\(\s*\*\s*CONCAT22\b', view)):
        return {}
    slots = {}
    for kind, name, array in declarations:
        slots.setdefault(name, []).append((kind.strip(), array))
    for kind, name in params:
        slots.setdefault(name, []).append((kind.strip(), None))
    matches = list(ASSIGNMENT.finditer(view))
    groups = {}
    for match in matches:
        destination, high, source, index = match[1], match[3], match[4], match[6]
        if high.lstrip('_').lower() != destination.lstrip('_').lower() + '_2':
            continue
        values = slots.get(index, [])
        if (len(values) != 1 or values[0][1] or values[0][0] not in
                ('int', 'uint', 'long', 'ulong', 'unsigned int', 'unsigned long', 'undefined4')):
            continue
        if any(name in slots for name in (destination, high, source)):
            continue
        names = '|'.join(map(re.escape, (destination, high, source, index, 'CONCAT22', 'unsigned', 'short')))
        if re.search(r'#\s*(?:define|undef)\s+(?:' + names + r')\b', view):
            continue
        if len(re.findall(r'\b' + re.escape(high) + r'\b', view)) != sum(other[3] == high for other in matches):
            continue
        groups.setdefault((int(match[2], 16), int(match[5], 16)), []).append(match)
    return groups


def inspect_word_windows(entry, ranges, instruction_rows, read_original, pairs,
                         is_code=lambda address, length: True):
    """Observe exact straight-line load/register-work/store windows.

    Frozen Ghidra instruction membership supplies candidate boundaries, checked
    against original bytes and local incoming edges. Neither membership nor
    counts certify complete CFGs, source/window correspondence or roots.
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
    rows, instructions = {}, {}
    for row in instruction_rows:
        if int(row['function_entry'], 16) != entry:
            return {}
        at = int(row['address'], 16)
        if at in rows:
            return {}
        length = row['length']
        chunk = next(((a, b, raw) for a, b, raw in chunks if a <= at < at+length <= b), None)
        if not chunk or not is_code(at, length):
            return {}
        first, last, raw = chunk
        instruction = next(decoder.disasm(raw[at-first:at-first+15], at, 1), None)
        if instruction is None or instruction.size != length:
            return {}
        rows[at], instructions[at] = row, instruction
    incoming = {}
    stops = {'int', 'int1', 'int3', 'into', 'ud0', 'ud1', 'ud2', 'hlt',
             'syscall', 'sysret', 'sysenter', 'sysexit', 'rsm', 'ljmp', 'lcall'}
    for at, row in rows.items():
        instruction = instructions[at]
        control = instruction.group(capstone.CS_GRP_CALL) or instruction.group(capstone.CS_GRP_JUMP)
        direct = (instruction.operands[0].imm & 0xffffffff if control and
                  len(instruction.operands) == 1 and instruction.operands[0].type == x86.X86_OP_IMM else None)
        targets = {direct} if direct is not None else set()
        for target in row.get('flows', []):
            if re.fullmatch(r'[0-9a-fA-F]{8}', target):
                # Indirect target metadata is only an additional conservative
                # incoming-edge filter, never proof of an exhaustive target set.
                targets.add(int(target, 16))
            elif not (target.startswith('EXTERNAL:') and instruction.group(capstone.CS_GRP_CALL)):
                return {}
        terminal = (instruction.group(capstone.CS_GRP_RET) or instruction.mnemonic.startswith('iret') or
                    instruction.mnemonic in stops or instruction.mnemonic == 'jmp')
        following = at + instruction.size
        if not terminal:
            targets.add(following)       # ordinary-call-return hypothesis
        recorded = row.get('fallthrough')
        if recorded and (terminal or not re.fullmatch(r'[0-9a-fA-F]{8}', recorded) or int(recorded, 16) != following):
            return {}
        for target in targets:
            incoming.setdefault(target, set()).add(at)

    def flat(instruction):
        return instruction.addr_size == 4 and not any(
            operand.type == x86.X86_OP_MEM and operand.mem.segment for operand in instruction.operands)

    families = [('eax', 'ax', 'al', 'ah'), ('ebx', 'bx', 'bl', 'bh'),
                ('ecx', 'cx', 'cl', 'ch'), ('edx', 'dx', 'dl', 'dh'),
                ('esi', 'si'), ('edi', 'di'), ('ebp', 'bp'), ('esp', 'sp')]
    result = {}
    for at, load in instructions.items():
        if load.mnemonic != 'mov' or not flat(load) or len(load.operands) != 2:
            continue
        register, memory = load.operands
        if (register.type != x86.X86_OP_REG or register.size != 2 or
                memory.type != x86.X86_OP_MEM or memory.size != 2 or
                memory.mem.base or not memory.mem.index or memory.mem.scale != 2):
            continue
        # Memory's index must really be a full i386 register, never BX/AX.
        if load.reg_name(memory.mem.index) not in {family[0] for family in families}:
            continue
        family = next((set(names) for names in families if load.reg_name(register.reg) in names), None)
        if family is None or load.reg_name(register.reg) in ('sp', 'bp'):
            continue
        if any(other != at and other < at+load.size and other+rows[other]['length'] > at for other in rows):
            continue
        cursor, previous, window = at + load.size, at, [at]
        for _ in range(4):
            instruction = instructions.get(cursor)
            if (instruction is None or not flat(instruction) or
                    incoming.get(cursor, set()) != {previous}):
                break
            # Every byte has one metadata instruction owner within this window.
            if any(other != cursor and other < cursor+instruction.size and
                   other+rows[other]['length'] > cursor for other in rows):
                break
            window.append(cursor)
            operands = instruction.operands
            if instruction.mnemonic == 'mov' and len(operands) == 2:
                destination, value = operands
                pair = (destination.mem.disp, memory.mem.disp) if destination.type == x86.X86_OP_MEM else None
                if (pair in pairs and destination.size == 2 and not destination.mem.base and not destination.mem.index and
                        value.type == x86.X86_OP_REG and value.size == 2 and value.reg == register.reg):
                    result.setdefault(pair, []).append(dict(load=at, store=cursor, instructions=window,
                                                           index_register=load.reg_name(memory.mem.index)))
                break
            # Initial rule permits only ADD of an immediate to an unrelated
            # full register. No memory, implicit stack, transfer or loaded-value
            # modification is silently treated as harmless.
            if (instruction.mnemonic != 'add' or len(operands) != 2 or
                    operands[0].type != x86.X86_OP_REG or operands[0].size != 4 or
                    operands[1].type != x86.X86_OP_IMM):
                break
            changed = instruction.reg_name(operands[0].reg)
            if changed in family or changed in ('esp', 'ebp', load.reg_name(memory.mem.index)):
                break
            following = instruction.address + instruction.size
            if rows[cursor].get('flows'):
                break
            previous, cursor = cursor, following
    return result


def apply_word_groups(body, groups, facts):
    edits, notes = [], []
    for pair, matches in groups.items():
        windows = facts.get(pair, [])
        if len(windows) != len(matches):
            continue
        for match in matches:
            replacement = ('*(unsigned short *)&%s = ((unsigned short const *)&%s)[%s];' %
                           (match[1], match[4], match[6]))
            # Preserve indentation; the matched statement begins before it.
            indentation = re.match(r'[ \t]*', match[0])[0]
            edits.append((match.start(), match.end(), indentation + replacement))
        notes.append('// Original word load/store %08x <- %08x: local scale-two/WORD windows only; '
                     'source/window correspondence remains a seed hypothesis. No suffix address, high-half read, '
                     'full CFG/root/type or source-acceptance proof.' % pair)
    for start, end, replacement in sorted(edits, reverse=True):
        body = body[:start] + replacement + body[end:]
    return body, notes
