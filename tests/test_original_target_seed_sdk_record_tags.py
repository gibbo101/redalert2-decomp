"""Demand-local SDK tag identity, ownership and declaration ordering."""
from pathlib import Path
import sys
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/original_target'))
import seed_candidate as seed

class SdkRecordTags(unittest.TestCase):
    groups=(('_MEMORYSTATUS','MEMORYSTATUS'),('_FILETIME','FILETIME'),('tagMSG','MSG'),
            ('_SECURITY_ATTRIBUTES','SECURITY_ATTRIBUTES'),('_EXCEPTION_POINTERS','EXCEPTION_POINTERS'))
    def complete(self,body,params=(),result='void'):
        return seed.sdk_preamble(body,params,result)
    def test_complete_real_tag_records_and_public_aliases(self):
        for tag,public in self.groups[:-1]:
            text=self.complete('{ struct '+tag+' value; return sizeof(value); }')
            self.assertIn('struct '+tag+' {',text)
            self.assertIn('typedef '+tag+' '+public+';',text)
    def test_exception_tag_remains_incomplete_before_callback(self):
        text=self.complete('{ return input; }',('struct _EXCEPTION_POINTERS *input',),'EXCEPTION_POINTERS *')
        self.assertIn('struct _EXCEPTION_POINTERS;',text)
        self.assertNotIn('struct _EXCEPTION_POINTERS {',text)
        self.assertLess(text.index('typedef _EXCEPTION_POINTERS EXCEPTION_POINTERS;'),text.index('*LPTOP_LEVEL_EXCEPTION_FILTER)'))
    def test_new_exception_pointer_alias_is_typed_when_tag_demanded(self):
        text=self.complete('{ struct _EXCEPTION_POINTERS *value; PEXCEPTION_POINTERS other; return value; }')
        self.assertIn('typedef EXCEPTION_POINTERS *PEXCEPTION_POINTERS;',text)
    def test_no_tag_demand_preserves_existing_preamble(self):
        for body in ('{ FILETIME value; return value.dwLowDateTime; }','{ MSG value; return value.hwnd; }',
                     '{ LPSECURITY_ATTRIBUTES value; return value; }','{ return 0; }'):
            self.assertEqual(self.complete(body),seed.SDK_PREAMBLE)
    def test_tag_in_comment_string_label_or_value_is_not_demand(self):
        for tag,public in self.groups:
            for body in ('{ /* '+tag+' */ return 0; }','{ use("'+tag+'"); }',
                         '{ goto '+tag+'; '+tag+': return 0; }','{ int '+tag+'; return '+tag+'; }'):
                self.assertNotIn('typedef '+tag+' '+public+';',self.complete(body))
    def test_authored_forward_definition_or_typedef_owns_group(self):
        for tag,public in self.groups:
            for own in ('struct '+tag+';','struct '+tag+' { int x; };','typedef int '+tag+';'):
                text=self.complete('{ '+own+' struct '+tag+' *value; }')
                self.assertNotIn('typedef '+tag+' '+public+';',text)
    def test_public_alias_variable_parameter_or_callback_owns_group(self):
        for tag,public in self.groups:
            for params in (('int '+public,),('void (*'+public+')(int)',)):
                text=self.complete('{ struct '+tag+' *value; }',params)
                self.assertNotIn('typedef '+tag+' '+public+';',text)
    def test_legacy_elaborated_public_tag_does_not_create_second_record(self):
        for tag,public in self.groups:
            body='{ struct '+tag+' *value; struct '+public+' *other; }'
            self.assertNotIn('typedef '+tag+' '+public+';',self.complete(body))
    def test_qualified_member_namespace_and_unknown_scope_refuse(self):
        for body in ('{ other::_FILETIME value; }','{ struct _FILETIME *value; object._FILETIME; }',
                     '{ namespace N {} struct _FILETIME *value; }','{ enum E { value }; struct _FILETIME *item; }'):
            self.assertNotIn('typedef _FILETIME FILETIME;',self.complete(body))
    def test_mixed_and_parenthesized_shadow_declarations_refuse(self):
        for declaration in ('int first,_FILETIME;','int ((_FILETIME));','int (*_FILETIME)(void);'):
            self.assertNotIn('typedef _FILETIME FILETIME;',self.complete('{ '+declaration+' struct _FILETIME *item; }'))
    def test_sizeof_complete_tag_is_real_demand(self):
        for tag,public in self.groups[:-1]:
            self.assertIn('typedef '+tag+' '+public+';',self.complete('{ return sizeof('+tag+'); }'))
    def test_explicit_tag_pointer_cast_is_real_demand(self):
        text=self.complete('{ return (_FILETIME *)value; }')
        self.assertIn('typedef _FILETIME FILETIME;',text)
    def test_exception_objects_arrays_sizeof_and_dereference_stay_unsupported(self):
        for body in ('{ struct _EXCEPTION_POINTERS value; }','{ struct _EXCEPTION_POINTERS value[2]; }',
                     '{ return sizeof(_EXCEPTION_POINTERS); }',
                     '{ struct _EXCEPTION_POINTERS *p; return p->ExceptionRecord; }',
                     '{ struct _EXCEPTION_POINTERS *p; use(*p); }'):
            self.assertNotIn('typedef _EXCEPTION_POINTERS EXCEPTION_POINTERS;',self.complete(body))
    def test_filetime_definition_precedes_find_data_and_com_uses(self):
        text=self.complete('{ struct _FILETIME value; WIN32_FIND_DATAA other; IStream *stream; }')
        self.assertLess(text.index('typedef _FILETIME FILETIME;'),text.index('struct _WIN32_FIND_DATAA {'))
        self.assertIn('FILETIME ftCreationTime',text)
    def test_msg_aliases_and_strict_hwnd_share_same_record(self):
        text=self.complete('{ struct tagMSG value; PMSG p; NPMSG other; HWND window; return window[1].unused; }')
        self.assertIn('typedef MSG *PMSG, *NPMSG, *LPMSG;',text)
        self.assertLess(text.index('struct HWND__ {'),text.index('struct tagMSG {'))
    def test_security_attributes_has_three_documented_fields(self):
        text=self.complete('{ struct _SECURITY_ATTRIBUTES value; }')
        self.assertIn('DWORD nLength; LPVOID lpSecurityDescriptor; BOOL bInheritHandle;',text)
        self.assertIn('typedef SECURITY_ATTRIBUTES *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;',text)
    def test_two_seed_namespaces_each_receive_their_own_aliases(self):
        first=self.complete('{ struct _FILETIME value; }')
        second=self.complete('{ struct _FILETIME other; }')
        self.assertIn('typedef _FILETIME FILETIME;',first)
        self.assertEqual(first,second)
        self.assertNotIn('#ifndef',first)
    def test_input_record_has_the_documented_console_union(self):
        text=self.complete('{ struct _INPUT_RECORD value; }')
        self.assertIn('struct _INPUT_RECORD {',text)
        self.assertIn('WORD EventType;',text)
        self.assertIn('MOUSE_EVENT_RECORD MouseEvent;',text)
        self.assertIn('typedef _INPUT_RECORD INPUT_RECORD;',text)
    def test_unsupported_lexical_forms_refuse(self):
        for prefix in ('#define X 1','%:define X 1','??=define X 1','<%',':>',
                       'use(R"x(tag)x");','name\\\nother'):
            self.assertNotIn('typedef _FILETIME FILETIME;',self.complete('{ '+prefix+' struct _FILETIME value; }'))

    def test_array_parameter_name_is_not_sizeof_type_demand(self):
        for tag,public in self.groups:
            text=self.complete('{ return sizeof('+tag+'); }',(public+' *p','int '+tag+'[2]'),'uint')
            self.assertNotIn('typedef '+tag+' '+public+';',text)

    def test_parenthesized_array_shadow_does_not_supply_tag_demand(self):
        for declaration in ('int (_FILETIME[2]);','int ((_FILETIME[2]));'):
            self.assertNotIn('typedef _FILETIME FILETIME;',self.complete('{ '+declaration+' return sizeof(_FILETIME); }'))

    def test_sdk_alias_casts_are_not_shadow_declarations(self):
        body='{ struct _MEMORYSTATUS value; GlobalMemoryStatus((LPMEMORYSTATUS)(&value)); value.dwLength=(DWORD)(32); }'
        self.assertIn('typedef _MEMORYSTATUS MEMORYSTATUS;',self.complete(body))

    def test_exception_cast_or_alias_cannot_hide_member_demand(self):
        for body in ('{ struct _EXCEPTION_POINTERS *p; return ((_EXCEPTION_POINTERS*)raw)->ExceptionRecord; }',
                     '{ struct _EXCEPTION_POINTERS *p; PEXCEPTION_POINTERS q; return q->ExceptionRecord; }'):
            self.assertNotIn('typedef _EXCEPTION_POINTERS EXCEPTION_POINTERS;',self.complete(body))

    def test_default_parameter_value_grammar_cannot_supply_type_demand(self):
        for tag,public in self.groups:
            text=self.complete('{ return sizeof('+tag+'); }',(public+' *p','int '+tag+'=0'),'uint')
            self.assertNotIn('typedef '+tag+' '+public+';',text)

    def test_exception_cast_value_dereference_is_not_pointer_only(self):
        for body in ('{ return sizeof(*(_EXCEPTION_POINTERS*)raw); }',
                     '{ struct _EXCEPTION_POINTERS *p; return ((PEXCEPTION_POINTERS)raw)->ExceptionRecord; }'):
            self.assertNotIn('typedef _EXCEPTION_POINTERS EXCEPTION_POINTERS;',self.complete(body))

    def test_exception_pointer_to_pointer_transports_need_no_record_definition(self):
        for body,params in (('{ *(_EXCEPTION_POINTERS **)(raw+4)=value; }',('_EXCEPTION_POINTERS *value',)),
                            ('{ return *input; }',('_EXCEPTION_POINTERS **input',))):
            text=self.complete(body,params)
            self.assertIn('typedef _EXCEPTION_POINTERS EXCEPTION_POINTERS;',text)
            self.assertNotIn('struct _EXCEPTION_POINTERS {',text)
        self.assertNotIn('typedef _EXCEPTION_POINTERS EXCEPTION_POINTERS;',self.complete('{ return sizeof(**(_EXCEPTION_POINTERS**)raw); }'))

    def test_legacy_class_or_union_public_tag_is_not_an_alias(self):
        for keyword in ('class','union'):
            text=self.complete('{ struct _FILETIME value; '+keyword+' FILETIME *old; }')
            self.assertNotIn('typedef _FILETIME FILETIME;',text)

    def test_complex_parameter_declarator_is_outside_tag_ownership_model(self):
        text=self.complete('{ return sizeof(_FILETIME); }',('FILETIME *p','int (*(_FILETIME)(void))(int)'),'uint')
        self.assertNotIn('typedef _FILETIME FILETIME;',text)

    def test_multiline_integer_shadow_is_not_a_sizeof_type(self):
        for declaration in ('int\n_FILETIME;','unsigned\nint\n_FILETIME;','int\nfirst,\n_FILETIME;'):
            text=self.complete('{ '+declaration+' return sizeof(_FILETIME); }',('FILETIME *p',),'uint')
            self.assertNotIn('typedef _FILETIME FILETIME;',text)

    def test_multiline_real_sdk_declaration_still_demands_tag(self):
        text=self.complete('{ struct\n_FILETIME\nvalue; return sizeof(value); }')
        self.assertIn('typedef _FILETIME FILETIME;',text)

if __name__=='__main__':unittest.main()
