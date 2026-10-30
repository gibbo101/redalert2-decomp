"""Typed-owner and static-ABI safeguards for scratch generation."""
import sys,tempfile,unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/original_target'))
import seed_candidate as seed
from inventory import Inventory
from seed_typed import adapt_seed,TypedRefusal
from seed_shared_types import SharedTypes

class FrozenFallbackTests(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory();self.addCleanup(self.temp.cleanup)
        self.root=Path(self.temp.name);self.passes=[]
    def export(self,name,header):
        directory=self.root/name;(directory/'decompiled').mkdir(parents=True)
        (directory/'decompiled/00401000.c').write_text(header+'\n{\n return 0;\n}\n')
        self.passes.append(directory);return directory
    def test_contradictory_named_owner_is_not_reused(self):
        self.export('new','int __thiscall FUN_00401000(Wrong *this)')
        self.export('wrong_old','int __thiscall FUN_00401000(Other *this)')
        good=self.export('raw_old','int __thiscall FUN_00401000(int *this)')
        prior=seed.earlier_uncontradicted_inventory(0x401000,Inventory(self.passes),'Real')
        self.assertEqual(prior.passes[0],good)
    def test_missing_prior_does_not_reuse_the_contradicted_export(self):
        self.export('new','int __thiscall FUN_00401000(Wrong *this)')
        self.assertIsNone(seed.earlier_uncontradicted_inventory(0x401000,Inventory(self.passes),'Real'))
    def test_earlier_free_function_is_available_for_receiverless_thiscall(self):
        self.export('new','int __thiscall FUN_00401000(void)')
        good=self.export('old','int __cdecl FUN_00401000(void)')
        prior=seed.earlier_uncontradicted_inventory(0x401000,Inventory(self.passes))
        self.assertEqual(prior.passes[0],good)

class StaticSignatureTests(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory();self.addCleanup(self.temp.cleanup);self.root=Path(self.temp.name)
        (self.root/'owner.hpp').write_text('class Input { public: int value; };\nclass Owner { public:\n static int __fastcall Read(Input &ini); // 0x00401000\n};\n')
        (self.root/'ghidra_types.hpp').write_text('typedef unsigned char undefined;\ntypedef int code(...);\n// Win32 names\n#define CONCAT11(a,b) (((a)<<8)|(b))\n#endif\n')
        self.schema=SharedTypes(self.root)
        self.source='#include "shared/ghidra_types.hpp"\nnamespace seed_00401000 {\nstruct Owner_00401000 { int FUN_00401000(); };\nint Owner_00401000::FUN_00401000()\n{\nreturn this->value;\n}\n}  // namespace seed_00401000\n'
    def test_shared_static_signature_replaces_false_instance_receiver(self):
        method=self.schema.method_at(0x401000)[1]
        result,_=adapt_seed(self.source,'Owner *this',0x401000,'Owner',self.schema,{},lambda x:x,static_method=method)
        self.assertIn('int __fastcall FUN_00401000(Input &ini)',result)
        self.assertIn('Input *typed_this = &ini;',result)
        self.assertNotIn('Owner_00401000',result)
    def test_multiple_static_arguments_require_review(self):
        from dataclasses import replace
        method=replace(self.schema.method_at(0x401000)[1],parameters='Input &ini, int count')
        with self.assertRaises(TypedRefusal):
            adapt_seed(self.source,'Owner *this',0x401000,'Owner',self.schema,{},lambda x:x,static_method=method)

if __name__=='__main__':unittest.main()
