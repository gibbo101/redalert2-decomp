"""Byte slices and original-width guards; x86 fixtures are authored synthetic code."""
from pathlib import Path
import struct
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import seed_candidate as seed
from seed_byte_access import inspect_byte_fields


GLOBAL, ENTRY, FIELD = 0x12345000, 0x10001000, 8
PAIR = (GLOBAL, FIELD)
EXPRESSION = '(&SUB_00000008)[DAT_12345000]'
SHARED = {GLOBAL: {'kind': 'UnknownRecord *'}}
TYPES = {'DAT_12345000': 'UnknownRecord *'}
LOAD = b'\xa1' + struct.pack('<I', GLOBAL)
CMP_BYTE = b'\x80\x78\x08\x00'


def facts(code, changed_read=False):
    def read(at, count):
        value = code[at-ENTRY:at-ENTRY+count]
        return b'\xcc' * count if changed_read else value
    return inspect_byte_fields(ENTRY, [{'start': '%08x' % ENTRY, 'bytes_hex': code.hex()}], read, {PAIR})


def rewrite(body, shared=None, types=None, proof=None, params=()):
    return seed.low_offset_byte_fields(body, params, TYPES if types is None else types,
                                       SHARED if shared is None else shared, ENTRY,
                                       facts={PAIR: {'read_sites': [ENTRY+5]}} if proof is None else proof)


class ArrayByteTests(unittest.TestCase):
    def test_scalar_and_pointer_elements_keep_existing_storage(self):
        for kind, offset in [('uint', 3), ('double', 7), ('code *', 0), ('Unknown *', 3), ('ushort', 1)]:
            source = '{\n    %s values[2];\n    values[1]._%d_1_ = 7;\n}' % (kind, offset)
            result = seed.array_byte_partials(source)
            self.assertIn('(*((unsigned char *)&values[1] + %d)) = 7;' % offset, result)
            self.assertIn('%s values[2];' % kind, result)

    def test_unknown_record_and_qualified_or_invalid_slices_refuse(self):
        for kind, extent, index, part in [('Unknown', '2', '0', '_0_1_'),
                ('volatile uint', '2', '0', '_0_1_'), ('const uint', '2', '0', '_0_1_'),
                ('bool', '2', '0', '_0_1_'), ('uint', '2', '2', '_0_1_'),
                ('uint', '2', '0', '_4_1_'), ('uint', '2', '0', '_0_2_'),
                ('uint', 'n', '0', '_0_1_'), ('uint', '2', 'i++', '_0_1_'),
                ('uint', '0', '0', '_0_1_'), ('uint', '2', '-1', '_0_1_')]:
            source = '{\n    %s values[%s];\n    values[%s].%s = 7;\n}' % (kind, extent, index, part)
            with self.subTest(source=source):
                self.assertEqual(seed.array_byte_partials(source), source)

    def test_ghidra_whitespace_before_array_extent_is_preserved(self):
        source = '{\n    code *values [259];\n    values[0]._0_1_ = 0;\n}'
        result = seed.array_byte_partials(source)
        self.assertIn('code *values [259];', result)
        self.assertIn('(*((unsigned char *)&values[0] + 0)) = 0;', result)

    def test_duplicate_shadow_comma_and_parameter_names_refuse(self):
        for extra in ['    uint values[2];\n', '    { uint values[2]; }\n', '    int n, m;\n']:
            source = '{\n    uint values[2];\n' + extra + '    values[0]._0_1_ = 7;\n}'
            self.assertEqual(seed.array_byte_partials(source), source)
        source = '{\n    uint values[2];\n    values[0]._0_1_ = 7;\n}'
        self.assertEqual(seed.array_byte_partials(source, ['uint *values']), source)

    def test_comments_literals_members_and_macros_are_not_array_variables(self):
        for use in ['// values[0]._0_1_ = 7;', '"values[0]._0_1_";',
                    'object.values[0]._0_1_ = 7;', 'object->values[0]._0_1_ = 7;',
                    'Scope::values[0]._0_1_ = 7;']:
            source = '{\n    uint values[2];\n    ' + use + '\n}'
            self.assertEqual(seed.array_byte_partials(source), source)
        source = '#define values other\n{\n    uint values[2];\n    values[0]._0_1_ = 7;\n}'
        self.assertEqual(seed.array_byte_partials(source), source)


class OffsetSourceTests(unittest.TestCase):
    def test_direct_zero_comparison_and_byte_assignment(self):
        for body in ["{ if (%s != '\\0') return; }" % EXPRESSION,
                     '{ if (%s == 0) return; }' % EXPRESSION,
                     '{\n    char flag;\n    flag = %s;\n}' % EXPRESSION]:
            result, notes = rewrite(body)
            self.assertNotIn('SUB_', result)
            self.assertIn('(((unsigned char const *)DAT_12345000)[0x8])', result)
            self.assertEqual(len(notes), 1)

    def test_no_fact_or_shared_pointer_type_means_no_repair(self):
        body = '{ if (%s == 0) return; }' % EXPRESSION
        for kwargs in [dict(shared={}), dict(types={}), dict(proof={}),
                       dict(types={'DAT_12345000': 'void *'}),
                       dict(shared={GLOBAL: {'kind': 'code *'}}, types={'DAT_12345000': 'code *'})]:
            with self.subTest(kwargs=kwargs):
                self.assertEqual(rewrite(body, **kwargs), (body, []))
        self.assertEqual(seed.low_offset_byte_fields(body, (), TYPES, SHARED, ENTRY), (body, []))

    def test_wide_arithmetic_calls_stores_address_values_and_signedness_refuse(self):
        for statement in ['int x; x = %s;', 'f(%s);', '%s = 1;', '++%s;',
                          'if (3 + %s == 0) return;', 'if ((int)%s == 0) return;',
                          'if (%s < 0) return;', 'if (&%s == 0) return;',
                          'if (%s == 1) return;', 'if (%s == 0-1) return;',
                          'if (%s == 0 + x) return;', 'if (~%s == 0) return;',
                          'if (++%s == 0) return;']:
            body = '{ ' + statement % EXPRESSION + ' }'
            with self.subTest(body=body):
                self.assertEqual(rewrite(body), (body, []))

    def test_other_label_uses_and_local_or_macro_shadows_refuse(self):
        for extra in ['SUB_00000008();', 'void *p = &SUB_00000008;',
                      'int SUB_00000008;', 'int DAT_12345000;',
                      '#define DAT_12345000 other\n', '#define SUB_00000008 other\n']:
            body = '{\n' + extra + '\n if (%s == 0) return; }' % EXPRESSION
            self.assertEqual(rewrite(body), (body, []))
        body = '{ if (%s == 0) return; }' % EXPRESSION
        self.assertEqual(rewrite(body, params=['uint DAT_12345000']), (body, []))

    def test_actual_image_address_and_comments_are_not_low_field_offsets(self):
        for expression in ['(&SUB_10002000)[DAT_12345000]', '"' + EXPRESSION + '"',
                           '0 /* ' + EXPRESSION + ' */']:
            body = '{ if (%s == 0) return; }' % expression
            self.assertEqual(rewrite(body), (body, []))

    def test_one_observation_does_not_rewrite_multiple_source_uses(self):
        body = '{ if (%s == 0) return; if (%s != 0) return; }' % (EXPRESSION, EXPRESSION)
        self.assertEqual(rewrite(body), (body, []))

    def test_assignment_destination_must_have_one_unambiguous_byte_declaration(self):
        for declarations in ['int flag; { char flag; }', 'char flag; { int flag; }',
                             'char flag[2];', 'volatile char flag;']:
            body = '{ %s flag = %s; }' % (declarations, EXPRESSION)
            self.assertEqual(rewrite(body), (body, []))

    def test_pointer_global_reassignment_or_address_escape_refuses(self):
        for statement in ['DAT_12345000 = replacement;', 'DAT_12345000++;',
                          'f(&DAT_12345000);']:
            body = '{ %s if (%s == 0) return; }' % (statement, EXPRESSION)
            self.assertEqual(rewrite(body), (body, []))


class OriginalByteTests(unittest.TestCase):
    def test_original_local_read_and_register_copy(self):
        self.assertIn(PAIR, facts(LOAD + CMP_BYTE + b'\xc3'))
        self.assertIn(PAIR, facts(LOAD + b'\x89\xc1\x80\x79\x08\x00\xc3'))

    def test_wrong_global_or_field_or_width_refuses(self):
        for code in [b'\xa1' + struct.pack('<I', GLOBAL+4) + CMP_BYTE + b'\xc3',
                     LOAD + b'\x80\x78\x09\x00\xc3',
                     LOAD + b'\x83\x78\x08\x00\xc3',
                     LOAD + CMP_BYTE + b'\x83\x78\x08\x00\xc3']:
            with self.subTest(code=code.hex()):
                self.assertEqual(facts(code), {})

    def test_call_subregister_and_branch_clobbers_refuse(self):
        for middle in [b'\xe8\x00\x00\x00\x00', b'\xb0\x01', b'\xb4\x01',
                       b'\x66\xb8\x01\x00', b'\x75\x00', b'\xeb\x00']:
            with self.subTest(middle=middle.hex()):
                self.assertEqual(facts(LOAD + middle + CMP_BYTE + b'\xc3'), {})

    def test_indirect_jump_trap_and_return_do_not_decode_following_bytes(self):
        for stop in [b'\xff\xe0', b'\xcc', b'\xc3', b'\x0f\x34', b'\xcf']:
            self.assertEqual(facts(LOAD + stop + CMP_BYTE + b'\xc3'), {})

    def test_segment_and_address_size_overrides_refuse_flat_provenance(self):
        for code in [b'\x64' + LOAD + CMP_BYTE + b'\xc3',
                     LOAD + b'\x64' + CMP_BYTE + b'\xc3',
                     b'\x8b\x1d' + struct.pack('<I', GLOBAL) + b'\x67\x8a\x47\x08\xc3']:
            self.assertEqual(facts(code), {})

    def test_prefetch_and_cache_maintenance_are_not_byte_loads(self):
        for operation in [b'\x0f\x18\x40\x08', b'\x0f\xae\x78\x08']:
            self.assertEqual(facts(LOAD + operation + b'\xc3'), {})

    def test_global_or_potential_alias_write_invalidates_saved_pointer(self):
        for write in [b'\xc7\x05' + struct.pack('<II', GLOBAL, 0), b'\xc7\x03\x00\x00\x00\x00']:
            self.assertEqual(facts(LOAD + write + CMP_BYTE + b'\xc3'), {})

    def test_unbacked_or_changed_frozen_bytes_refuse(self):
        self.assertEqual(facts(LOAD + CMP_BYTE + b'\xc3', changed_read=True), {})


if __name__ == '__main__':
    unittest.main()
