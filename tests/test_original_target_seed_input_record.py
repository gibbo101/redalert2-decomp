"""Bounded console SDK records and preservation of a qualified byte read."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/original_target'))
import seed_candidate as seed

SLICE='record.Event.MouseEvent.dwControlKeyState._2_1_'
READ='(*(uchar const *)((char const *)&(record.Event.MouseEvent.dwControlKeyState) + 2))'


class InputRecordTests(unittest.TestCase):
    def body(self,expression=None,local='_INPUT_RECORD record;',extra=''):
        return '{\n    '+local+'\n    '+extra+'\n    return '+(expression or SLICE)+';\n}'

    def test_tag_completes_the_real_union_before_import_consumers(self):
        text=seed.sdk_preamble(self.body())
        self.assertIn(seed.SDK_INPUT_RECORD,text)
        self.assertNotIn('struct INPUT_RECORD;',text)
        self.assertIn('WINDOW_BUFFER_SIZE_RECORD WindowBufferSizeEvent;',text)
        self.assertIn('union { WCHAR UnicodeChar; CHAR AsciiChar; } uChar;',text)
        self.assertEqual(text.count('struct _INPUT_RECORD {'),1)

    def test_tag_in_signature_and_sizeof_are_type_demand(self):
        self.assertIn(seed.SDK_INPUT_RECORD,seed.sdk_preamble('{}',['_INPUT_RECORD *record']))
        self.assertIn(seed.SDK_INPUT_RECORD,seed.sdk_preamble('{return sizeof(_INPUT_RECORD);}'))

    def test_opaque_public_only_transport_keeps_previous_preamble(self):
        self.assertEqual(seed.sdk_preamble('{INPUT_RECORD *p; send(p);}'),seed.SDK_PREAMBLE)

    def test_unrelated_and_literal_only_text_stays_identical(self):
        for body in ('{return 1;}','{puts("_INPUT_RECORD"); /* _INPUT_RECORD */}'):
            self.assertEqual(seed.sdk_preamble(body),seed.SDK_PREAMBLE)
            self.assertEqual(seed.input_record_byte_partials(body),body)

    def test_authored_group_and_component_names_refuse_completion(self):
        for declaration in ('typedef int _INPUT_RECORD;', 'struct _INPUT_RECORD {int x;};',
                            'int _INPUT_RECORD;', 'int COORD;', 'struct COORD *p;',
                            'struct KEY_EVENT_RECORD *p;', 'enum _MOUSE_EVENT_RECORD {x};',
                            'typedef int DWORD;'):
            with self.subTest(declaration=declaration):
                text=seed.sdk_preamble(self.body(extra=declaration))
                self.assertNotIn('struct _INPUT_RECORD {',text)

    def test_unsupported_lexical_and_complex_scope_forms_refuse(self):
        for text in ('#define X 1\n'+self.body(),
                     self.body(extra='using N::x;'), self.body(extra='auto f=[&record]() {return 0;};'),
                     self.body(extra='int x=0; \\\n x++;')):
            self.assertEqual(seed.input_record_byte_partials(text),text)

    def test_full_owner_path_is_one_unsigned_character_read(self):
        text=seed.input_record_byte_partials(self.body())
        self.assertEqual(text,self.body(READ))
        self.assertNotIn('.MouseEvent.(*',text)

    def test_actual_cast_shift_and_other_union_fields_survive(self):
        body=self.body('(uint)(byte)'+SLICE+' >> 4 & 1',extra='if(record.EventType==1 && record.Event.KeyEvent.bKeyDown){}')
        self.assertEqual(seed.input_record_byte_partials(body),body.replace(SLICE,READ))

    def test_output_buffer_address_to_api_is_preserved(self):
        body=self.body(extra='ReadConsoleInputA(handle,(PINPUT_RECORD)(&record),1,&count);')
        self.assertEqual(seed.input_record_byte_partials(body),body.replace(SLICE,READ))

    def test_do_not_infer_another_union_arm(self):
        text=seed.input_record_byte_partials(self.body())
        self.assertIn('Event.MouseEvent.dwControlKeyState',text)
        self.assertNotIn('KeyEvent.uChar',text)

    def test_mutable_top_level_local_only(self):
        for declaration in ('volatile _INPUT_RECORD record;', 'const _INPUT_RECORD record;',
                            '_INPUT_RECORD *record;', '_INPUT_RECORD record[2];',
                            '_INPUT_RECORD &record=other;', 'INPUT_RECORD record;'):
            with self.subTest(declaration=declaration):
                body=self.body(local=declaration)
                self.assertEqual(seed.input_record_byte_partials(body),body)
        body=self.body(local='')
        self.assertEqual(seed.input_record_byte_partials(body,['_INPUT_RECORD record']),body)

    def test_shadowing_and_redeclarations_refuse(self):
        for extra in ('{int record; use(record);}', '{_INPUT_RECORD record; use(record.EventType);}',
                      '{int (record);}', '{int\n record;}', 'int other,record;',
                      'auto &ref='+SLICE+';'):
            with self.subTest(extra=extra):
                body=self.body(extra=extra)
                self.assertEqual(seed.input_record_byte_partials(body),body)

    def test_nested_local_is_outside_initial_scope(self):
        body='{ if(flag) '+self.body()+' }'
        self.assertEqual(seed.input_record_byte_partials(body),body)

    def test_foreign_and_effectful_owner_expressions_refuse(self):
        for expression in ('object.'+SLICE, 'object->'+SLICE, 'N::'+SLICE,
                           '(record).Event.MouseEvent.dwControlKeyState._2_1_',
                           'record[i++].Event.MouseEvent.dwControlKeyState._2_1_',
                           'GetRecord().Event.MouseEvent.dwControlKeyState._2_1_'):
            body=self.body(expression)
            self.assertEqual(seed.input_record_byte_partials(body),body)

    def test_wrong_offset_width_or_field_is_not_repaired(self):
        for expression in (SLICE.replace('_2_1_','_1_1_'),SLICE.replace('_2_1_','_2_2_'),
                           SLICE.replace('dwControlKeyState','dwButtonState')):
            body=self.body(expression)
            self.assertEqual(seed.input_record_byte_partials(body),body)

    def test_mutation_address_and_unevaluated_uses_refuse(self):
        for expression in (SLICE+'=1','++'+SLICE,SLICE+'++', '&'+SLICE,
                           'sizeof('+SLICE+')','sizeof '+SLICE,'('+SLICE+')=1',
                           'use('+SLICE+')'):
            body=self.body(expression)
            self.assertEqual(seed.input_record_byte_partials(body),body)

    def test_comments_in_path_are_never_deleted(self):
        expression=SLICE.replace('Event.MouseEvent','Event./*preserve*/MouseEvent')
        body=self.body(expression)
        self.assertEqual(seed.input_record_byte_partials(body),body)

    def test_string_and_comment_occurrences_stay_unchanged(self):
        body=self.body('0',extra='puts("'+SLICE+'"); /* '+SLICE+' */')
        self.assertEqual(seed.input_record_byte_partials(body),body)

    def test_appended_prototype_does_not_shadow_runtime_local(self):
        body=self.body()+'\nextern void Other(int record);'
        self.assertEqual(seed.input_record_byte_partials(body),body.replace(SLICE,READ))

    def test_qualified_non_input_family_remains_unhandled(self):
        body='{\n CLSID record;\n return record.Data4._0_4_;\n}'
        self.assertEqual(seed.input_record_byte_partials(body),body)

    def test_decorated_authored_record_cannot_gain_sdk_identity(self):
        for declaration in ('struct __declspec(align(8)) _INPUT_RECORD { int pretend; };',
                            'struct _INPUT_RECORD __declspec(align(8)) { int pretend; };',
                            'struct __attribute__((packed)) _INPUT_RECORD { int pretend; };',
                            'struct alignas(8) _INPUT_RECORD { int pretend; };'):
            body=self.body(extra=declaration)
            self.assertNotIn('struct _INPUT_RECORD {',seed.sdk_preamble(body))
            self.assertEqual(seed.input_record_byte_partials(body),body)

    def test_call_arguments_and_enclosing_lvalues_refuse(self):
        for expression in ('use(0,'+SLICE+')', 'use(0,(uint)'+SLICE+')',
                           'use((uint)'+SLICE+')', '(0,'+SLICE+')=1',
                           '(flag?'+SLICE+':other)=1', SLICE+'<<=1',SLICE+'>>=1',
                           'sizeof array['+SLICE+']'):
            body=self.body(expression)
            self.assertEqual(seed.input_record_byte_partials(body),body)

    def test_appended_dll_imports_do_not_own_console_record(self):
        body=self.body()+'\nextern "C" __declspec(dllimport) BOOL __stdcall ReadConsoleInputA(HANDLE,PINPUT_RECORD,DWORD,LPDWORD);'
        self.assertIn(seed.SDK_INPUT_RECORD,seed.sdk_preamble(body))
        self.assertEqual(seed.input_record_byte_partials(body),body.replace(SLICE,READ))

    def test_outer_unary_operators_do_not_escape_the_read_only_scope(self):
        for expression in ('&(flag?'+SLICE+':other)', '++(flag?'+SLICE+':other)',
                           '--(flag?'+SLICE+':other)'):
            body=self.body(expression,extra='uchar other;')
            self.assertEqual(seed.input_record_byte_partials(body,result='uchar const *'),body)


if __name__=='__main__':
    unittest.main()
