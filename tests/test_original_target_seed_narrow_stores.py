"""Authored synthetic word windows, metadata guards and scratch source contexts."""
from pathlib import Path
import struct
import sys
import unittest

import capstone
from capstone import x86_const as x86

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import seed_candidate as seed
from seed_narrow_stores import inspect_word_windows

ENTRY, DESTINATION, SOURCE = 0x10001000, 0x11223344, 0x55667788
PAIR = (DESTINATION, SOURCE)
LOAD = b'\x66\x8b\x14\x45' + struct.pack('<I', SOURCE)
ADD = b'\x83\xc1\x0c'
STORE = b'\x66\x89\x15' + struct.pack('<I', DESTINATION)
EXPRESSION = '_DAT_11223344 = CONCAT22(DAT_11223344_2,(&DAT_55667788)[index]);'
FACTS = {PAIR: [dict(load=ENTRY, store=ENTRY+11)]}


def observed(code, mutate=None, changed_bytes=False, is_code=lambda at, length: True):
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, ENTRY))
    rows = []
    for instruction in instructions:
        control = instruction.group(capstone.CS_GRP_JUMP) or instruction.group(capstone.CS_GRP_CALL)
        targets = ([instruction.operands[0].imm] if control and len(instruction.operands)==1 and
                   instruction.operands[0].type==x86.X86_OP_IMM else [])
        row = dict(function_entry='%08x' % ENTRY, address='%08x' % instruction.address,
                   length=instruction.size, flows=['%08x' % at for at in targets],
                   fallthrough=None if instruction.mnemonic=='jmp' or instruction.group(capstone.CS_GRP_RET)
                   else '%08x' % (instruction.address+instruction.size))
        rows.append(row)
    if mutate:
        mutate(rows, instructions, decoder)
    def read(at, count):
        return b'\xcc'*count if changed_bytes else code[at-ENTRY:at-ENTRY+count]
    return inspect_word_windows(ENTRY, [dict(start='%08x' % ENTRY, bytes_hex=code.hex())],
                                rows, read, {PAIR}, is_code)


def rewritten(body, facts=FACTS, params=()):
    return seed.word_store_artifacts(body, params, ENTRY, facts=facts)


class WordWindowTests(unittest.TestCase):
    def test_scalar_word_read_precedes_direct_word_write(self):
        for middle in (b'', ADD):
            facts = observed(LOAD + middle + STORE)
            self.assertEqual(facts[PAIR][0]['load'], ENTRY)
            self.assertEqual(facts[PAIR][0]['store'], ENTRY+len(LOAD+middle))

    def test_segment_and_address_overrides_refuse(self):
        for code in (b'\x64'+LOAD+STORE, LOAD+b'\x64'+STORE,
                     b'\x67\x66\x8b\x10'+STORE):
            self.assertEqual(observed(code), {})

    def test_value_index_stack_or_frame_clobber_refuses(self):
        for middle in (b'\xb2\x00', b'\xb6\x00', b'\x31\xd2', b'\x83\xc2\x01',
                       b'\x83\xc0\x01', b'\x83\xc4\x04', b'\x83\xc5\x04'):
            with self.subTest(middle=middle.hex()):
                self.assertEqual(observed(LOAD+middle+STORE), {})

    def test_memory_alias_call_branch_and_unsupported_work_refuse(self):
        for middle in (b'\x66\x89\x10', b'\xff\xd1', b'\xe8\x00\x00\x00\x00',
                       b'\xeb\x00', b'\x90', b'\x0f\x18\x0a', b'\x83\xd1\x01'):
            self.assertEqual(observed(LOAD+middle+STORE), {})

    def test_wrong_width_address_or_value_register_refuses(self):
        for code in (LOAD[1:]+STORE, LOAD+STORE[1:],
                     LOAD[:-4]+struct.pack('<I', SOURCE+1)+STORE,
                     LOAD+STORE[:-4]+struct.pack('<I', DESTINATION+1),
                     LOAD+b'\x66\x89\x05'+struct.pack('<I', DESTINATION)):
            self.assertEqual(observed(code), {})

    def test_missing_index_or_based_address_is_not_the_proved_table(self):
        for code in (b'\x66\x8b\x15'+struct.pack('<I', SOURCE)+STORE,
                     b'\x66\x8b\x94\x45'+struct.pack('<I', SOURCE)+STORE):
            self.assertEqual(observed(code), {})

    def test_omitted_actual_incoming_branch_does_not_hide_competing_entry(self):
        def omit(rows, instructions, decoder): rows[0]['flows']=[]
        self.assertEqual(observed(b'\x74\x0b'+LOAD+ADD+STORE, omit), {})

    def test_duplicate_and_overlapping_instruction_membership_refuses(self):
        def duplicate(rows, instructions, decoder): rows.append(dict(rows[0]))
        def overlap(rows, instructions, decoder):
            instruction=next(decoder.disasm((LOAD+ADD+STORE)[1:], ENTRY+1, 1))
            rows.append(dict(function_entry='%08x'%ENTRY,address='%08x'%(ENTRY+1),length=instruction.size,
                             flows=[],fallthrough=None))
        for mutate in (duplicate, overlap):
            self.assertEqual(observed(LOAD+ADD+STORE, mutate), {})

    def test_changed_original_noncode_or_wrong_member_refuses(self):
        self.assertEqual(observed(LOAD+ADD+STORE, changed_bytes=True), {})
        self.assertEqual(observed(LOAD+ADD+STORE, is_code=lambda at,n: False), {})
        def different_function(rows, instructions, decoder): rows[0]['function_entry']='10002000'
        self.assertEqual(observed(LOAD+ADD+STORE, different_function), {})

    def test_import_address_space_is_allowed_only_for_calls(self):
        def external(rows, instructions, decoder): rows[0]['flows']=['EXTERNAL:0000013d']
        self.assertIn(PAIR, observed(b'\xe8\x20\x00\x00\x00'+LOAD+ADD+STORE, external))
        self.assertEqual(observed(LOAD+ADD+STORE, external), {})

    def test_stack_or_frame_word_result_is_not_an_ordinary_value(self):
        for load_modrm,store_modrm in ((b'\x24',b'\x25'),(b'\x2c',b'\x2d')):
            code=b'\x66\x8b'+load_modrm+b'\x45'+struct.pack('<I',SOURCE)
            code+=b'\x66\x89'+store_modrm+struct.pack('<I',DESTINATION)
            self.assertEqual(observed(code), {})


class WordSourceTests(unittest.TestCase):
    def test_only_store_is_changed_no_suffix_storage_or_high_read(self):
        body='int index;\n    '+EXPRESSION+'\nmutate();\nreturn _DAT_11223344 & 0xffff;\n'
        result,notes=rewritten(body)
        self.assertEqual(len(notes),1)
        self.assertIn('    *(unsigned short *)&_DAT_11223344 = ((unsigned short const *)&DAT_55667788)[index];',result)
        self.assertNotIn('DAT_11223344_2',result)
        self.assertIn('mutate();\nreturn _DAT_11223344 & 0xffff;',result)

    def test_original_fact_and_stable_32bit_index_are_required(self):
        body='int index;\n'+EXPRESSION+'\n'
        self.assertEqual(rewritten(body,facts={}), (body,[]))
        self.assertEqual(seed.word_store_artifacts(body,[],ENTRY), (body,[]))
        for kind in ('short','volatile int','int *','Unknown','unsigned __int64'):
            source=kind+' index;\n'+EXPRESSION+'\n'
            self.assertEqual(rewritten(source),(source,[]))

    def test_duplicate_parameter_and_global_shadow_refuse(self):
        for declaration in ('int index; { int index; }','int index; int DAT_55667788;',
                            'int index; int _DAT_11223344;','int index; int DAT_11223344_2;'):
            body=declaration+'\n'+EXPRESSION+'\n'
            self.assertEqual(rewritten(body),(body,[]))
        body='int index;\n'+EXPRESSION+'\n'
        self.assertEqual(rewritten(body,params=['uint index']),(body,[]))

    def test_macro_storage_index_builtin_or_keyword_refuses(self):
        for name in ('index','DAT_55667788','_DAT_11223344','DAT_11223344_2','CONCAT22','unsigned','short'):
            body='#define '+name+' something\nint index;\n'+EXPRESSION+'\n'
            self.assertEqual(rewritten(body),(body,[]))

    def test_ushort_alias_cannot_change_emitted_builtin_width(self):
        for declaration in ('#define ushort unsigned int','int ushort;'):
            body=declaration+'\nint index;\n'+EXPRESSION+'\n'
            result,notes=rewritten(body)
            self.assertEqual(len(notes),1)
            self.assertIn('*(unsigned short *)&_DAT_11223344',result)
            self.assertNotIn('*(ushort',result)

    def test_effectful_nested_qualified_and_nonassignment_contexts_refuse(self):
        for expression in (EXPRESSION.replace('[index]','[index++]'), 'f('+EXPRESSION[:-1]+');',
                           'return '+EXPRESSION, 'object.'+EXPRESSION, 'Scope::'+EXPRESSION,
                           EXPRESSION.replace(' = ', ' += '),
                           EXPRESSION.replace('DAT_11223344_2','DAT_11223348_2')):
            body='int index;\n'+expression+'\n'
            self.assertEqual(rewritten(body),(body,[]))

    def test_comments_literals_other_high_use_and_callable_name_refuse(self):
        for prefix,use in (('', '// '+EXPRESSION), ('','"'+EXPRESSION+'";'),
                           ('consume(DAT_11223344_2);\n',EXPRESSION),
                           ('int CONCAT22(int,int);\n',EXPRESSION),
                           ('int (*CONCAT22)(int,int);\n',EXPRESSION)):
            body='int index;\n'+prefix+use+'\n'
            self.assertEqual(rewritten(body),(body,[]))

    def test_one_to_many_and_many_to_one_window_counts_refuse(self):
        body='int index;\n'+EXPRESSION+'\n'
        self.assertEqual(rewritten(body+EXPRESSION+'\n'),(body+EXPRESSION+'\n',[]))
        self.assertEqual(rewritten(body,facts={PAIR:FACTS[PAIR]*2}),(body,[]))


if __name__=='__main__':
    unittest.main()
