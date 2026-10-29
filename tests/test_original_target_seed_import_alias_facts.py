import copy,sys,unittest,importlib.util
from pathlib import Path
root=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(root/'tools/original_target'))
import seed_candidate as seed
from seed_import_alias_facts import recorded_direct_imports


@unittest.skipUnless(importlib.util.find_spec("pycparser"), "optional pycparser is unavailable")
class FactTests(unittest.TestCase):
    def setUp(self):
        self.fact=dict(name='_BinkClose@4',dll='binkw32.dll',iat='0079a598',
            seed_declaration=dict(name='BinkClose',source_alias='_BinkClose_4',convention='__stdcall',parameters=1,
                signature='void __stdcall BinkClose(struct BinkHandleSize *bink)',model_source='src/shared/bink.hpp'))
        self.text='void f(void*h){_BinkClose_4(h);}'
    def apply(self,facts=None,text=None,reserved=()):
        return recorded_direct_imports(text or self.text,facts or {'raw':self.fact},seed.parse_header,seed.stack_bytes,reserved)
    def test_positive_and_identity_unchanged(self):
        before=copy.deepcopy(self.fact)
        text,facts=self.apply()
        self.assertEqual(text,self.text.replace('_BinkClose_4','BinkClose'))
        self.assertEqual(facts['BinkClose']['iat'],'0079a598')
        self.assertEqual(self.fact,before)
    def test_no_signature_guess_from_suffix(self):
        del self.fact['seed_declaration']['signature']
        self.assertEqual(self.apply(),(self.text,{}))
    def test_wrong_formal_width(self):
        self.fact['seed_declaration']['signature']='void __stdcall BinkClose(double value)'
        self.assertEqual(self.apply(),(self.text,{}))
    def test_wrong_convention(self):
        self.fact['seed_declaration']['convention']='__cdecl'
        self.assertEqual(self.apply(),(self.text,{}))
    def test_wrong_name(self):
        self.fact['seed_declaration']['name']='Other'
        self.assertEqual(self.apply(),(self.text,{}))
    def test_no_provenance(self):
        del self.fact['seed_declaration']['model_source']
        self.assertEqual(self.apply(),(self.text,{}))
    def test_duplicate_alias_owner(self):
        other=copy.deepcopy(self.fact);other['dll']='other.dll';other['iat']='0079a59c'
        self.assertEqual(self.apply({'one':self.fact,'two':other}),(self.text,{}))
    def test_refusal_preserves_original_cpp(self):
        text='void f(void*h){ N::method(); _BinkClose_4(h); }'
        self.assertEqual(self.apply(text=text),(text,{}))
    def test_unrelated_does_not_validate_new_metadata(self):
        self.fact['seed_declaration']['signature']='not a prototype'
        text='unparsed::other;'
        self.assertEqual(self.apply(text=text),(text,{}))
    def test_replacement_preamble_owner(self):
        self.assertEqual(self.apply(reserved={'BinkClose'}),(self.text,{}))
    def test_missing_args_still_refused_by_existing_guard(self):
        text,facts=self.apply(text='void f(void){_BinkClose_4();}')
        self.assertIn('BinkClose()',text)
        with self.assertRaisesRegex(ValueError,'argument count'):
            seed.declare_import(text,'BinkClose',facts['BinkClose'])


if __name__=='__main__':unittest.main()
