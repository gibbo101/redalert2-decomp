"""Original-byte evidence for lowering Ghidra's pointer-valued switch artifact.

This is a scratch-seed transformation, never a function-bound acceptance rule.
Unknown guards, overlapping decodes, writable tables or unexplained local flow
refuse the transformation. Calls and known external tail exits remain qualified.
"""
from collections import defaultdict
import struct

import capstone


class UnsupportedSwitch(ValueError):
    pass


def require(condition, reason):
    if not condition:
        raise UnsupportedSwitch(reason)


def inspect_index_switch(audit, entry, dispatch, table, accepted_entries=()):
    """Prove one-level index mapping from original guards and a closed local CFG.

    The case count comes from each actual unsigned range guard, not the source's
    case count. Every incoming dispatch edge must pass an adjacent CMP/range
    branch, with no bypass of the flags or index register. External direct tail
    exits must name already accepted entries and are not followed or certified.
    """
    xc = capstone.x86_const
    require(entry <= dispatch < table and 0 < table-entry <= 0x20000 and table % 4 == 0,
            'Unsupported switch address window/alignment')
    instruction = next(audit.decoder.disasm(audit.original(dispatch, 16), dispatch, 1), None)
    require(instruction is not None and instruction.mnemonic == 'jmp' and len(instruction.operands) == 1,
            'Switch label does not name an indirect jump')
    operand = instruction.operands[0]
    require(operand.type == xc.X86_OP_MEM and operand.size == 4 and operand.mem.base == 0 and
            operand.mem.index != 0 and operand.mem.scale == 4 and operand.mem.disp == table,
            'Unsupported original indexed dispatch operand')
    register = operand.mem.index

    def walk(targets):
        pending, nodes, graph, occupied, tails, calls = [entry], {}, {}, {}, [], []
        while pending:
            at = pending.pop()
            if at in nodes:
                continue
            require(entry <= at < table and len(nodes) < 32768, 'Unexplained local transfer/window')
            ins = next(audit.decoder.disasm(audit.original(at, 16), at, 1), None)
            require(ins is not None and at+ins.size <= table, 'Undecoded or table-crossing instruction')
            for byte in range(at, at+ins.size):
                require(byte not in occupied or occupied[byte] == at, 'Overlapping original decode')
                occupied[byte] = at
            nodes[at] = ins
            if at == dispatch:
                edges = list(targets or ())
            elif ins.mnemonic.startswith('ret'):
                edges = []
            elif ins.mnemonic in ('ud2', 'hlt', 'int', 'int1', 'int3', 'iret', 'iretd'):
                raise UnsupportedSwitch('Unmodeled trap/exception transfer')
            elif ins.group(capstone.CS_GRP_JUMP):
                require(len(ins.operands) == 1 and ins.operands[0].type == xc.X86_OP_IMM,
                        'Another opaque indirect jump')
                destination = ins.operands[0].imm & 0xffffffff
                if ins.mnemonic == 'jmp' and not entry <= destination < table:
                    require(destination in accepted_entries, 'Unknown external direct tail destination')
                    tails.append((at, destination))
                    edges = []
                else:
                    edges = [destination] + ([] if ins.mnemonic == 'jmp' else [at+ins.size])
            else:
                edges = [at+ins.size]
                if ins.group(capstone.CS_GRP_CALL):
                    calls.append(at)
            graph[at] = edges
            pending.extend(edges)
        predecessors = defaultdict(set)
        for at, edges in graph.items():
            for destination in edges:
                predecessors[destination].add(at)
        return nodes, graph, occupied, predecessors, tails, calls

    def guards(nodes, predecessors):
        incoming = predecessors[dispatch]
        require(incoming and dispatch != entry, 'Dispatch has no guarded incoming edge')
        limits, sites = set(), []
        for branch in sorted(incoming):
            ins = nodes[branch]
            require(len(predecessors[branch]) == 1 and branch != entry, 'Guard flags can be bypassed')
            compare = nodes[next(iter(predecessors[branch]))]
            require(compare.mnemonic == 'cmp' and compare.address+compare.size == branch and
                    len(compare.operands) == 2 and compare.operands[0].type == xc.X86_OP_REG and
                    compare.operands[0].size == 4 and compare.operands[0].reg == register and
                    compare.operands[1].type == xc.X86_OP_IMM,
                    'Guard is not an adjacent original index comparison')
            limit = compare.operands[1].imm
            require(0 <= limit < 256, 'Unbounded or unsupported switch range')
            require(ins.mnemonic == 'ja' and branch+ins.size == dispatch or
                    ins.mnemonic == 'jbe' and ins.operands[0].imm == dispatch,
                    'Incoming edge does not establish an unsigned upper bound')
            limits.add(limit)
            sites.append((compare.address, branch))
        require(len(limits) == 1, 'Reentry guards disagree')
        return next(iter(limits))+1, sites

    preliminary = walk(None)
    require(dispatch in preliminary[0], 'Dispatch is not reached from the proposed entry')
    count, _ = guards(preliminary[0], preliminary[3])
    section = audit.pe.get_section_by_rva(table-audit.base)
    require(section is not None and section.Characteristics & 0x40000000 and
            not section.Characteristics & 0x80000000 and
            table-audit.base+4*count <= section.VirtualAddress+section.SizeOfRawData,
            'Switch table is not wholly initialized read-only data')
    data = audit.original(table, 4*count)
    require(len(data) == 4*count, 'Truncated original switch table')
    targets = list(struct.unpack('<%dI' % count, data))
    require(all(entry <= at < table for at in targets), 'Table target outside the local code model')
    nodes, graph, occupied, predecessors, tails, calls = walk(targets)
    final_count, guard_sites = guards(nodes, predecessors)
    require(final_count == count, 'Expanded original guard count changed')
    code_end = max(occupied)+1
    require(len(occupied) == code_end-entry, 'Unexplained original code gap')
    gap = table-code_end
    require(0 <= gap <= 3, 'Unknown gap before the switch table')
    alignment = audit.original(code_end, gap) if gap else b''
    require(all(byte in (0x90, 0xcc) for byte in alignment) or alignment == b'\x8b\xff',
            'Unidentified original internal alignment')
    return dict(entry=entry, dispatch=dispatch, table=table, targets=targets,
                original_code_bytes=code_end-entry, internal_alignment_bytes=gap,
                code_and_table_bytes=table+4*count-entry, original_instructions=len(nodes),
                guard_sites=guard_sites, qualified_direct_tail_exits=tails,
                calls_assumed_returning=len(calls), table_read_only=True,
                scope='Closed local graph with actual guarded table edges; known external tails not followed. '
                      'No entry-root/exception/callee-return/alternate-entry or accepted-bound claim.')
