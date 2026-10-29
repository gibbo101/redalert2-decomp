"""Documented SDK interfaces must not become guessed game layouts."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import seed_candidate as seed


class ComInterfaceTypes(unittest.TestCase):
    def preamble(self, body='{}', params=(), result='void'):
        return seed.sdk_preamble(body, params, result)

    def test_explicit_stream_parameter(self):
        text = self.preamble('{ p->lpVtbl->Read(p, dst, 4, 0); }', ['IStream *p'])
        self.assertIn('struct IStream { IStreamVtbl *lpVtbl; };', text)
        self.assertIn('HRESULT (__stdcall *Read)(IStream *, void *, ULONG, ULONG *);', text)
        self.assertIn('HRESULT (__stdcall *Write)(IStream *, void const *, ULONG, ULONG *);', text)

    def test_explicit_unknown_alias(self):
        text = self.preamble(params=['LPUNKNOWN object'])
        self.assertIn('struct IUnknown { IUnknownVtbl *lpVtbl; };', text)
        self.assertIn('HRESULT (__stdcall *QueryInterface)(IUnknown *, IID const *, void **);', text)
        self.assertIn('ULONG (__stdcall *Release)(IUnknown *);', text)

    def test_vtable_pointer_local(self):
        self.assertIn('struct IStreamVtbl {', self.preamble('{\n    IStreamVtbl *table;\n}'))

    def test_storage_result_alias(self):
        text = self.preamble(result='LPSTORAGE')
        self.assertIn('typedef IStorage *LPSTORAGE;', text)
        self.assertIn('HRESULT (__stdcall *Revert)(IStorage *);', text)

    def test_persistence_alias(self):
        text = self.preamble(params=['LPPERSISTSTREAM source'])
        self.assertIn('HRESULT (__stdcall *Save)(IPersistStream *, IStream *, BOOL);', text)
        self.assertIn('HRESULT (__stdcall *GetSizeMax)(IPersistStream *, ULARGE_INTEGER *);', text)

    def test_no_unrelated_interface_guess(self):
        text = self.preamble('{ unknown->lpVtbl->Read(unknown, dst, 4, 0); }', ['CustomStream *unknown'])
        self.assertNotIn('struct IStreamVtbl {', text)

    def test_comments_and_strings_do_not_trigger(self):
        text = self.preamble('{ /* IStream */ log("IUnknown"); }')
        self.assertNotIn('struct IUnknownVtbl {', text)

    def test_identifier_shadowing_blocks_group(self):
        text = self.preamble('{\n    int IUnknown;\n}', ['IStream *source'])
        self.assertNotIn('struct IStreamVtbl {', text)

    def test_parameter_shadowing_blocks_group(self):
        text = self.preamble(params=['int IStream', 'LPUNKNOWN object'])
        self.assertNotIn('struct IUnknownVtbl {', text)

    def test_authored_type_blocks_group(self):
        text = self.preamble('{ typedef int IStream; IStream x; }', ['LPUNKNOWN object'])
        self.assertNotIn('struct IUnknownVtbl {', text)

    def test_authored_record_blocks_group(self):
        text = self.preamble('{ struct IStream { int field; }; }', ['LPUNKNOWN object'])
        self.assertNotIn('struct IUnknownVtbl {', text)

    def test_macro_blocks_group(self):
        text = self.preamble('#define IStream OtherType\n{}', ['LPUNKNOWN object'])
        self.assertNotIn('struct IUnknownVtbl {', text)

    def test_callable_name_blocks_group(self):
        text = self.preamble('{ IStream(); }', ['LPUNKNOWN object'])
        self.assertNotIn('struct IUnknownVtbl {', text)

    def test_integer_dependency_shadow_blocks_group(self):
        text = self.preamble('{ typedef short ULONG; }', ['IStream *source'])
        self.assertNotIn('struct IStreamVtbl {', text)

    def test_ulong_defined_once(self):
        text = self.preamble('{\n    ULONG count;\n}', ['IStream *source'])
        self.assertEqual(text.count('typedef unsigned long ULONG;'), 1)

    def test_existing_large_integer_is_reused(self):
        text = self.preamble(params=['IStream *source'])
        self.assertEqual(text.count('union LARGE_INTEGER {'), 1)
        self.assertNotIn('typedef _LARGE_INTEGER LARGE_INTEGER;', text)
        self.assertEqual(text.count('union ULARGE_INTEGER {'), 1)

    def test_namespace_composition_keeps_definitions(self):
        first = self.preamble(params=['IStream *source'])
        second = self.preamble(params=['IStream *source'])
        self.assertEqual(first, second)
        self.assertNotIn('#define', first)
        self.assertNotIn('#include', first)
        self.assertNotIn('__forceinline', first)
        self.assertNotIn('__asm', first)
        self.assertNotIn('virtual ', first)


if __name__ == '__main__':
    unittest.main()
