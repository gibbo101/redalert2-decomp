"""Alias ownership must survive the actual seed assembly and optional fallback."""
import importlib.util
from pathlib import Path
import sys
import unittest
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/original_target'))
import seed_candidate as seed


class Fixture:
    passes=[]
    def decompiled(self,entry):return 'void __cdecl FUN_00400010(void *h)\n{\n _BinkClose_4(h);\n}\n'
    def function(self,entry):return Path('fixture'),dict(name='FUN_00400010',ranges=[dict(start='00400010',length=1,bytes_hex='c3')])


def facts():
    return {'_BinkClose@4':dict(name='_BinkClose@4',dll='binkw32.dll',iat='0079a598',
        seed_declaration=dict(name='BinkClose',source_alias='_BinkClose_4',convention='__stdcall',parameters=1,
            signature='void __stdcall BinkClose(struct BinkHandleSize *bink)',model_source='src/shared/bink.hpp'))}


class SeedCase(unittest.TestCase):
    def run_seed(self,**kwargs):
        with patch.object(seed,'import_facts',return_value=facts()),patch.object(seed,'documentation',return_value=[]):
            return seed.seed(0x400010,Fixture(),{},**kwargs)


class OptionalFallbackTests(SeedCase):
    def test_missing_parser_preserves_old_complete_text(self):
        before=self.run_seed(_import_aliases=False)
        original_import=__import__
        def missing(name,*args,**kwargs):
            if name=='pycparser':raise ImportError('optional parser unavailable')
            return original_import(name,*args,**kwargs)
        with patch('builtins.__import__',side_effect=missing):
            self.assertEqual(self.run_seed(),before)


@unittest.skipUnless(importlib.util.find_spec('pycparser'),'optional pycparser is unavailable')
class AssemblyTests(SeedCase):
    def test_actual_import_declaration_and_original_iat(self):
        text=self.run_seed()
        self.assertIn('__imp__BinkClose@4=0079a598',text)
        self.assertIn('BinkClose((struct BinkHandleSize *)(h))',text)
        self.assertNotIn('_BinkClose_4(h)',text)
    def test_generated_preamble_macro_preserves_old_complete_text(self):
        with patch.object(seed,'sdk_preamble',return_value='#define BinkClose bad_macro'):
            self.assertEqual(self.run_seed(),self.run_seed(_import_aliases=False))
    def test_generated_declaration_collision_preserves_old_complete_text(self):
        # A real generated forward declaration collision must refuse the repair.
        with patch.object(seed,'check_generated_import_names',side_effect=seed.AliasRefusal('generated collision')):
            self.assertEqual(self.run_seed(),self.run_seed(_import_aliases=False))


if __name__=='__main__':unittest.main()
