"""Demand-driven documented HWND pointee, with source ownership kept explicit."""
from pathlib import Path
import sys
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/original_target'))
import seed_candidate as seed

class StrictHwndTypes(unittest.TestCase):
    definition='struct HWND__ { int unused; };'
    def preamble(self,body,params=(),result='void'):
        return seed.sdk_preamble(body,params,result)
    def test_scaled_parameter_demands_real_four_byte_pointee(self):
        text=self.preamble('{ return (HWND)(window - 1); }',('HWND window',),'HWND')
        self.assertTrue(text.startswith(self.definition+'\ntypedef HWND__ *HWND;'))
    def test_indexed_dummy_field_and_pointer_member(self):
        for operation in ('return window[0x1b].unused;','return window->unused;','return (*window).unused;'):
            with self.subTest(operation=operation):
                self.assertIn(self.definition,self.preamble('{ HWND window; '+operation+' }'))
    def test_increment_and_compound_arithmetic(self):
        for operation in ('window++;','--window;','window += count;','window -= count;'):
            self.assertIn(self.definition,self.preamble('{ HWND window; '+operation+' }'))
    def test_explicit_unqualified_sdk_tag_can_be_completed(self):
        self.assertIn(self.definition,self.preamble('{ struct HWND__ *value; return value->unused; }'))
    def test_definition_precedes_every_dependent_sdk_type(self):
        text=self.preamble('{ HWND window; return window[1].unused; }')
        for use in ('struct MSG {','*WNDPROC)','*DLGPROC)','*WNDENUMPROC)','*TIMERPROC)'):
            self.assertLess(text.index(self.definition),text.index(use))
    def test_opaque_transport_and_import_only_are_unchanged(self):
        for body in ('{ return window; }','{ return GetParent(window); }','{ use(window); }'):
            self.assertEqual(self.preamble(body,('HWND window',),'HWND'),seed.SDK_PREAMBLE)
    def test_unrelated_comments_strings_and_longer_names_do_not_demand(self):
        for body in ('{ int HWND_suffix; return 0; }','{ use("HWND window; window[1].unused"); }','{ /* HWND__ */ return 0; }'):
            self.assertEqual(self.preamble(body),seed.SDK_PREAMBLE)
    def test_foreign_handle_type_or_member_never_adds_a_local_type(self):
        for body in ('{ other::HWND window; use(window[1]); }','{ ::HWND window; use(window-1); }',
                     '{ obj.HWND; }','{ ptr->HWND__; }','{ HWND::member; }'):
            self.assertNotIn(self.definition,self.preamble(body))
    def test_authored_alias_tag_using_namespace_and_callable_refuse(self):
        for own in ('typedef void *HWND;','struct HWND__;','struct HWND__ { int own; };',
                    'namespace HWND { int own; }','using other::HWND;','HWND();','enum HWND { own };'):
            self.assertNotIn(self.definition,self.preamble('{ '+own+' HWND window; use(window[1].unused); }'))
    def test_parameter_or_variable_owns_coupled_names(self):
        for name in ('HWND','HWND__','MSG','LPMSG','WNDPROC','DLGPROC','WNDENUMPROC','TIMERPROC'):
            body='{ int '+name+'; HWND window; use(window[1].unused); }'
            self.assertNotIn(self.definition,self.preamble(body))
            self.assertNotIn(self.definition,self.preamble('{ HWND window; use(window[1].unused); }',('int '+name,)))
    def test_authored_dependent_callback_and_record_declarations_refuse(self):
        for declaration in ('typedef int (*WNDPROC)(int);','struct MSG { int x; };',
                            'typedef struct { int x; int y; } LPMSG;'):
            self.assertNotIn(self.definition,self.preamble(declaration+'\n{ HWND window; use(window[1].unused); }'))
    def test_complex_function_pointer_parameter_ownership_refuses(self):
        for parameter in ('void (*HWND)(void)','void (__stdcall * const HWND__)(int)',
                          'int (* volatile WNDPROC)(int)'):
            self.assertNotIn(self.definition,self.preamble('{ HWND window; use(window[1].unused); }',(parameter,)))
    def test_preprocessing_raw_strings_and_splicing_refuse(self):
        for prefix in ('#define s other\n','%:define s other\n','??=define s other\n',
                       '// splice??/\n','use(R"tag(HWND)tag");','use(va\\\nlue);'):
            self.assertNotIn(self.definition,self.preamble(prefix+'\n{ HWND window; use(window[1].unused); }'))
    def test_other_handle_arithmetic_is_outside_scope(self):
        for handle in ('HANDLE','HDC','HINSTANCE','HMODULE','HGLOBAL','HLOCAL','HGDIOBJ'):
            self.assertNotIn(self.definition,self.preamble('{ '+handle+' value; return value-1; }'))

    def test_alternative_scope_and_array_tokens_refuse_shadow_demand(self):
        for body in ('{ <% UINT window=0; window=window+1; %> return GetParent(window); }',
                     '{ { int window<:1:>; window[0]=window[0]+1; } return GetParent(window); }'):
            self.assertNotIn(self.definition,self.preamble(body,('HWND window',),'HWND'))
        for token in ('<%', '%>', '<:', ':>'):
            body='{ HWND window; return window[1].unused; }\nextern int FUN_00001000(int '+token+');'
            self.assertNotIn(self.definition,self.preamble(body))
    def test_other_handles_keep_their_existing_aliases(self):
        text=self.preamble('{ HWND window; return window[1].unused; }')
        self.assertIn('void *HACCEL, *HBITMAP, *HBRUSH, *HCURSOR, *HFONT, *HGDIOBJ, *HGLOBAL;',text)
        self.assertNotIn('struct HMODULE__',text)
        self.assertNotIn('struct HANDLE__',text)
    def test_two_seed_namespaces_are_independent(self):
        first=self.preamble('{ HWND window; return window-1; }')
        second=self.preamble('{ HWND window; return window[1].unused; }')
        self.assertIn(self.definition,first)
        self.assertIn(self.definition,second)
        self.assertNotIn('#ifndef',first)
    def test_other_objects_field_name_is_not_handle_demand(self):
        self.assertEqual(self.preamble('{ HWND window; use(other.window[1]); }'),seed.SDK_PREAMBLE)

    def test_qualified_integer_shadow_cannot_change_opaque_parameter_type(self):
        text=self.preamble('{ { ::UINT window=0; window=window+1; } return GetParent(window); }',('HWND window',),'HWND')
        self.assertNotIn(self.definition,text)

    def test_sdk_tag_as_label_or_enumerator_is_not_type_demand(self):
        for body in ('{ goto HWND__; HWND__: return GetParent(window); }',
                     '{ enum E { HWND__=0 }; return GetParent(window); }'):
            self.assertNotIn(self.definition,self.preamble(body,('HWND window',),'HWND'))

    def test_anonymous_aggregate_shadow_refuses_parameter_demand(self):
        body='{ { struct { int x; } window; use(window[1]); } return GetParent(window); }'
        self.assertNotIn(self.definition,self.preamble(body,('HWND window',),'HWND'))

    def test_parenthesized_integer_declaration_does_not_change_parameter(self):
        for kind in ('int','DWORD','LONG','UINT'):
            body='{ { '+kind+' (window)=0; window=window+1; } return GetParent(window); }'
            self.assertNotIn(self.definition,self.preamble(body,('HWND window',),'HWND'))

    def test_parenthesized_tag_value_is_not_a_type(self):
        body='{ int (HWND__)=2; int x=HWND__ * 4; return GetParent(window); }'
        self.assertNotIn(self.definition,self.preamble(body,('HWND window',),'HWND'))

    def test_unknown_call_or_type_syntax_refuses(self):
        body='{ HWND window; Mystery(window); return window[1].unused; }'
        self.assertNotIn(self.definition,self.preamble(body))

    def test_typedef_scope_is_outside_the_trusted_local_subset(self):
        body='{ typedef int Scalar; { Scalar(window); window++; } return GetParent(window); }'
        self.assertNotIn(self.definition,self.preamble(body,('HWND window',),'HWND'))

    def test_direct_initialization_and_comma_shadow_are_unresolved(self):
        for body in ('{ { int window(0); window++; } return GetParent(window); }',
                     '{ { int other=0,window=1; window++; } return GetParent(window); }'):
            self.assertNotIn(self.definition,self.preamble(body,('HWND window',),'HWND'))

    def test_generated_callee_parameters_do_not_shadow_function_locals(self):
        body='{ HWND window; return window[1].unused; }\nextern int FUN_00001000(int window,int other);'
        self.assertIn(self.definition,self.preamble(body))

    def test_parenthesized_array_declarator_is_not_handle_indexing(self):
        body='{ { int (window[2]); window[0]++; } return GetParent(window); }'
        self.assertNotIn(self.definition,self.preamble(body,('HWND window',),'HWND'))

    def test_guarded_sdk_pointer_cast_is_not_a_shadow_declaration(self):
        body='{ GetDlgItem((HWND)(window),0); return (HWND)(window-1); }'
        self.assertIn(self.definition,self.preamble(body,('HWND window',),'HWND'))

    def test_redundantly_parenthesized_declarators_are_not_expressions(self):
        for depth in range(1,6):
            for name in ('window','HWND__'):
                declarator='('*depth+name+')'*depth
                if name=='window':
                    body='{ { int '+declarator+'=0; window++; } return GetParent(window); }'
                else:
                    body='{ int '+declarator+'=2; int x=HWND__ * 4; return GetParent(window); }'
                self.assertNotIn(self.definition,self.preamble(body,('HWND window',),'HWND'))

    def test_nested_pointer_and_reference_declarators_are_not_reads(self):
        for declarator in ('((*window))','((&window))','(((*window)))'):
            body='{ { int '+declarator+'; window++; } return GetParent(window); }'
            self.assertNotIn(self.definition,self.preamble(body,('HWND window',),'HWND'))

if __name__=='__main__':unittest.main()
