import sys,tempfile,unittest
from pathlib import Path
from unittest.mock import patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/original_target'))
from inventory import Inventory
import sweep_seeds as sweep
class SweepFallbackTests(unittest.TestCase):
 def setUp(self):
  self.temp=tempfile.TemporaryDirectory();self.addCleanup(self.temp.cleanup);self.root=Path(self.temp.name)
  self.new=self.root/'new';self.old=self.root/'old'
  for d in [self.new,self.old]:
   (d/'decompiled').mkdir(parents=True)
   for e in ['00401000','00402000']:(d/'decompiled'/(e+'.c')).write_text('export')
  self.inv=Inventory([self.new,self.old]);self.base=Inventory([self.old]);self.out=self.root/'output';(self.out/'0').mkdir(parents=True)
  (self.out/'0/00401000.cpp').write_text('preferred source')
 def run_retry(self,rows,success=True):
  def compile_batch(config,entries,directory,options):
   if success:
    for e in entries:(directory/('%08x.obj'%e)).write_bytes(b'test object')
   return []
  with patch.object(sweep,'seed',return_value='raw pass5 source') as render,patch.object(sweep,'compile_batch',side_effect=compile_batch) as compiler,patch.object(sweep,'score_object',return_value=dict(byte_exact=False,score=25.0)):
   sweep.retry_uncompiled({},rows,self.inv,{},self.out,[['/O2']],None,None,{},self.base)
   return render,compiler
 def test_only_uncompiled_entries_retry_and_provenance_matches_actual_payload(self):
  rows={0x401000:dict(length=16,status='compile-failed'),0x402000:dict(length=20,compiled=True,score=50.0,source='typed.cpp')}
  render,compiler=self.run_retry(rows);self.assertEqual(compiler.call_args.args[1],[0x401000]);self.assertEqual(rows[0x401000]['seed_mode'],'pass5');self.assertIn('fallback',rows[0x401000]['source']);self.assertEqual(Path(rows[0x401000]['source']).read_text(),'raw pass5 source');self.assertEqual((self.out/'0/00401000.cpp').read_text(),'preferred source');self.assertEqual(rows[0x402000]['source'],'typed.cpp');self.assertTrue(render.call_args.kwargs['_typed'] is False)
 def test_generation_refusal_can_recover_with_a_compiling_pass5_source(self):
  rows={0x401000:dict(length=16,status='seed-failed',reason='typed refusal')};self.run_retry(rows);self.assertTrue(rows[0x401000]['compiled']);self.assertNotIn('status',rows[0x401000]);self.assertEqual(rows[0x401000]['fallback']['preferred_reason'],'typed refusal')
 def test_failed_fallback_keeps_a_failure_status(self):
  rows={0x401000:dict(length=16,status='compile-failed')};self.run_retry(rows,False);self.assertFalse(rows[0x401000].get('compiled',False));self.assertEqual(rows[0x401000]['status'],'compile-failed');self.assertFalse(rows[0x401000]['fallback']['compiled'])
 def test_default_pass5_sweep_does_not_compile_a_duplicate_fallback(self):
  self.inv=self.base;rows={0x401000:dict(length=16,status='compile-failed')};_,compiler=self.run_retry(rows);compiler.assert_not_called()
if __name__=='__main__':unittest.main()
