import unittest
import importlib.util
from pathlib import Path
import sys
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/"tools/original_target"))
from unittest import mock
from seed_import_aliases import AliasRefusal, direct_import_aliases, check_generated_import_names


@unittest.skipUnless(importlib.util.find_spec("pycparser"), "optional pycparser is unavailable")
class AliasTests(unittest.TestCase):
    mapping = {'_BinkClose_4': 'BinkClose', '_BinkGetError_0': 'BinkGetError'}
    def changed(self, text):
        return direct_import_aliases(text, self.mapping)[0]
    def refused(self, text):
        with self.assertRaises(AliasRefusal): self.changed(text)
    def test_real_direct_calls_preserve_arguments_and_comments(self):
        text='void f(void *h){ _BinkClose_4 /* named */ (h); _BinkGetError_0(); }'
        self.assertEqual(self.changed(text),text.replace('_BinkClose_4','BinkClose').replace('_BinkGetError_0','BinkGetError'))
    def test_same_arguments_once_in_order(self):
        text='void f(void){ _BinkClose_4(next(++index)); }'
        self.assertEqual(self.changed(text),'void f(void){ BinkClose(next(++index)); }')
    def test_ordinary_comments_and_literals_never_change(self):
        text='void f(void*h){ /* _BinkClose_4 */ say("_BinkClose_4"); _BinkClose_4(h); }'
        self.assertEqual(self.changed(text),'void f(void*h){ /* _BinkClose_4 */ say("_BinkClose_4"); BinkClose(h); }')
    def test_parameter_function_pointer_shadow(self):
        self.refused('void f(void (*_BinkClose_4)(void*),void*h){ _BinkClose_4(h); }')
    def test_local_function_pointer_shadow(self):
        self.refused('void f(void*h){ void (*_BinkClose_4)(void*)=other; _BinkClose_4(h); }')
    def test_parenthesized_pointer_shadow(self):
        self.refused('void f(void*h){ int *(_BinkClose_4); _BinkClose_4(h); }')
    def test_mixed_declarators(self):
        self.refused('void f(void*h){ int a,*_BinkClose_4; _BinkClose_4(h); }')
    def test_nested_pointer_to_array_declarator(self):
        self.refused('void f(void*h){ int (*(*_BinkClose_4)[3])(void*); _BinkClose_4(h); }')
    def test_typedef_shadow(self):
        self.refused('void f(void*h){ typedef int _BinkClose_4; _BinkClose_4(h); }')
    def test_tag_shadow(self):
        self.refused('void f(void*h){ struct _BinkClose_4 {int x;}; _BinkClose_4(h); }')
    def test_record_field_shadow(self):
        self.refused('void f(void*h){ struct X {int _BinkClose_4;}; _BinkClose_4(h); }')
    def test_enum_shadow(self):
        self.refused('void f(void*h){ enum X {_BinkClose_4}; _BinkClose_4(h); }')
    def test_replacement_parameter_shadow(self):
        self.refused('void f(void(*BinkClose)(void*),void*h){ _BinkClose_4(h); }')
    def test_replacement_local_shadow(self):
        self.refused('void f(void*h){ void (*BinkClose)(void*)=other; _BinkClose_4(h); }')
    def test_member_reference(self):
        self.refused('void f(void*h){ p->_BinkClose_4(h); }')
    def test_qualified_reference(self):
        self.refused('void f(void*h){ N::_BinkClose_4(h); }')
    def test_cpp_constructor_declaration(self):
        self.refused('void f(void*h){ Thing _BinkClose_4(h); }')
    def test_unknown_declaration_type(self):
        self.refused('void f(void*h){ Mystery value; _BinkClose_4(h); }')
    def test_macro(self):
        self.refused('#define _BinkClose_4 other\nvoid f(void*h){_BinkClose_4(h);}')
    def test_source_splice(self):
        self.refused('void f(void*h){ /'+'/'+'\\\n_BinkClose_4(h); }')
    def test_trigraph(self):
        self.refused('void f(void*h){ _BinkClose_4(h); } /'+'/'+'??/\nother')
    def test_digraph(self):
        self.refused('%:define X x\nvoid f(void*h){_BinkClose_4(h);}')
    def test_raw_literal(self):
        self.refused('void f(void*h){ say(R"x(raw)x"); _BinkClose_4(h); }')
    def test_pragma_operator(self):
        self.refused('void f(void*h){ _Pragma("pop_macro(\\"BinkClose\\")") _BinkClose_4(h); }')
    def test_msvc_pragma(self):
        self.refused('void f(void*h){ __pragma(pop_macro("BinkClose")); _BinkClose_4(h); }')
    def test_replacement_keywords_and_parser_types(self):
        for name in ['uint','DWORD','return','__stdcall','sizeof','new']:
            with self.subTest(name=name), self.assertRaises(AliasRefusal):
                direct_import_aliases('void f(void*h){_BinkClose_4(h);}',{'_BinkClose_4':name})
    def test_emission_context_macro(self):
        with self.assertRaises(AliasRefusal):
            direct_import_aliases('void f(void*h){_BinkClose_4(h);}',self.mapping,{'BinkClose'})
    def test_missing_optional_parser_refuses_relevant_input(self):
        original_import=__import__
        def missing(name,*args,**kwargs):
            if name=='pycparser':raise ImportError('not installed')
            return original_import(name,*args,**kwargs)
        with mock.patch('builtins.__import__',side_effect=missing):
            self.refused('void f(void*h){_BinkClose_4(h);}')
            self.assertEqual(self.changed('unparsed::unrelated'),'unparsed::unrelated')
    def test_value_use(self):
        self.refused('void f(void*h){ p=_BinkClose_4; _BinkClose_4(h); }')
    def test_address_use(self):
        self.refused('void f(void*h){ p=&_BinkClose_4; }')
    def test_declaration_after_body(self):
        self.refused('void f(void*h){_BinkClose_4(h);} int BinkClose;')
    def test_generated_record_collision(self):
        with self.assertRaises(AliasRefusal):
            check_generated_import_names(['extern int BinkClose(void*);','class BinkClose;'],{'BinkClose':'extern int BinkClose(void*);'})
    def test_generated_import_only(self):
        check_generated_import_names(['class Unrelated;','extern int BinkClose(void*);'],{'BinkClose':'extern int BinkClose(void*);'})
    def test_unrelated_text_does_not_require_parser(self):
        text='unknown::cpp unparsed;'
        self.assertEqual(direct_import_aliases(text,self.mapping),(text,[]))


if __name__=='__main__': unittest.main()
