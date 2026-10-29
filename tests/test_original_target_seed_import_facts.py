"""Recorded SDK imports retain their real ABI and refuse missing arguments."""
import copy
import json
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools/original_target'))
import seed_candidate as seed


class DocumentedImportFactsTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.facts = {row['name']: row for row in json.loads(
            (ROOT / 'manifests/imports.json').read_bytes())['imports']}

    def test_code_page_imports_are_unsigned_no_argument_winapi(self):
        for name, slot in [('GetACP', '0079a2d0'), ('GetOEMCP', '0079a2d4')]:
            with self.subTest(name=name):
                fact = self.facts[name]
                self.assertEqual((fact['dll'], fact['iat']), ('KERNEL32.dll', slot))
                self.assertEqual((fact['convention'], fact['parameters']), ('__stdcall', 0))
                result, convention, parsed, params, _ = seed.parse_header(fact['signature'])
                self.assertEqual((result, convention, parsed, params),
                                 ('UINT', '__stdcall', name, []))
                self.assertTrue(fact['signature_source'].startswith('https://learn.microsoft.com/'))

    def test_directdraw_has_three_pointer_arguments_and_hresult(self):
        fact = self.facts['DirectDrawCreate']
        self.assertEqual((fact['dll'], fact['iat']), ('DDRAW.dll', '0079a048'))
        self.assertEqual((fact['convention'], fact['parameters']), ('__stdcall', 3))
        result, convention, name, params, _ = seed.parse_header(fact['signature'])
        self.assertEqual((result, convention, name), ('HRESULT', '__stdcall', 'DirectDrawCreate'))
        self.assertEqual([seed.param_parts(p)[0] for p in params],
                         ['GUID *', 'struct IDirectDraw **', 'struct IUnknown *'])

    def test_code_page_call_keeps_the_recorded_zero_byte_iat_binding(self):
        for name in ('GetACP', 'GetOEMCP'):
            with self.subTest(name=name):
                body = 'return ' + name + '();'
                changed, declaration = seed.declare_import(body, name, self.facts[name])
                self.assertEqual(changed, body)
                self.assertIn('UINT __stdcall ' + name + '(void);', declaration)
                self.assertIn('__imp__' + name + '@0=' + self.facts[name]['iat'], declaration)

    def test_directdraw_call_preserves_each_existing_argument_once(self):
        body = 'status = DirectDrawCreate(next_guid(), next_output(), next_outer());'
        changed, declaration = seed.declare_import(body, 'DirectDrawCreate', self.facts['DirectDrawCreate'])
        self.assertEqual(changed.count('next_guid()'), 1)
        self.assertEqual(changed.count('next_output()'), 1)
        self.assertEqual(changed.count('next_outer()'), 1)
        self.assertLess(changed.index('next_guid()'), changed.index('next_output()'))
        self.assertLess(changed.index('next_output()'), changed.index('next_outer()'))
        self.assertIn('(GUID *)(next_guid())', changed)
        self.assertIn('(struct IDirectDraw **)(next_output())', changed)
        self.assertIn('(struct IUnknown *)(next_outer())', changed)
        self.assertIn('__imp__DirectDrawCreate@12=0079a048', declaration)

    def test_directdraw_never_synthesizes_omitted_or_extra_arguments(self):
        for count in (0, 1, 2, 4):
            with self.subTest(count=count):
                body = 'DirectDrawCreate(' + ', '.join('arg%d' % i for i in range(count)) + ');'
                with self.assertRaisesRegex(ValueError, 'Import argument count disagrees'):
                    seed.declare_import(body, 'DirectDrawCreate', self.facts['DirectDrawCreate'])

    def test_code_page_functions_refuse_source_arguments(self):
        for name in ('GetACP', 'GetOEMCP'):
            with self.subTest(name=name):
                with self.assertRaisesRegex(ValueError, 'Import argument count disagrees'):
                    seed.declare_import(name + '(side_effect());', name, self.facts[name])

    def test_sdk_fact_does_not_enable_an_unknown_convention(self):
        fact = copy.deepcopy(self.facts['DirectDrawCreate'])
        fact['convention'] = 'unknown'
        with self.assertRaisesRegex(ValueError, 'Import signature/convention unavailable'):
            seed.declare_import('DirectDrawCreate(0, out, 0);', 'DirectDrawCreate', fact)

    def test_missing_signature_still_refuses_a_no_argument_call(self):
        fact = copy.deepcopy(self.facts['GetACP'])
        del fact['signature']
        with self.assertRaisesRegex(ValueError, 'Import signature/convention unavailable'):
            seed.declare_import('return GetACP();', 'GetACP', fact)

    def test_opaque_directdraw_pointee_has_no_invented_layout(self):
        _, declaration = seed.declare_import('DirectDrawCreate(0, out, 0);',
                                             'DirectDrawCreate', self.facts['DirectDrawCreate'])
        preamble = seed.sdk_preamble(declaration)
        self.assertNotIn('IDirectDraw {', preamble)
        self.assertNotIn('IDirectDrawVtbl', preamble)
        self.assertNotIn('sizeof(IDirectDraw)', preamble)

    def test_iat_binding_comes_from_the_record_not_an_api_name_fallback(self):
        fact = copy.deepcopy(self.facts['GetACP'])
        fact['iat'] = '00102030'
        _, declaration = seed.declare_import('return GetACP();', 'GetACP', fact)
        self.assertIn('__imp__GetACP@0=00102030', declaration)


if __name__ == '__main__':
    unittest.main()
