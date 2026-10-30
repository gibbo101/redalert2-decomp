import sys,tempfile,unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/original_target'))
from inventory import Inventory
from seed_fallback import choose_seed,has_fallback,fallback_source
class SeedFallbackTests(unittest.TestCase):
 def setUp(self):
  self.temp=tempfile.TemporaryDirectory();self.addCleanup(self.temp.cleanup);self.root=Path(self.temp.name)
  self.new=self.root/'new';self.old=self.root/'old'
  for p in [self.new,self.old]:(p/'decompiled').mkdir(parents=True);(p/'decompiled/00401000.c').write_text('export')
  self.inventory=Inventory([self.new,self.old]);self.baseline=Inventory([self.old]);self.calls=[]
 def render(self,e,inv,accepted,**options):
  self.calls.append(('render',inv.passes[0],options));return 'old source' if inv.passes[0]==self.old else 'typed source'
 def choose(self,results):
  def compile_source(text,mode):self.calls.append(('compile',text,mode));return dict(compiled=results.pop(0),source_path=mode+'.cpp')
  return choose_seed(0x401000,self.inventory,{},self.render,compile_source,self.baseline)
 def test_compiling_typed_seed_is_retained_without_rendering_pass5(self):
  r=self.choose([True]);self.assertEqual(r['source'],'typed source');self.assertEqual(len(r['attempts']),1);self.assertEqual(len(self.calls),2)
 def test_failed_typed_compile_tries_exactly_one_untyped_frozen_seed(self):
  r=self.choose([False,True]);self.assertEqual(r['source'],'old source');self.assertEqual(r['seed_mode'],'pass5');self.assertTrue(r['compiled']);self.assertEqual(self.calls[2][2],{'_typed':False})
 def test_both_failures_preserve_preferred_source_and_attempts(self):
  r=self.choose([False,False]);self.assertFalse(r['compiled']);self.assertEqual(r['source'],'typed source');self.assertEqual(len(r['attempts']),2)
 def test_missing_baseline_export_is_not_invented(self):
  (self.old/'decompiled/00401000.c').unlink();r=self.choose([False]);self.assertEqual(len(r['attempts']),1);self.assertFalse(r['compiled'])
 def test_default_pass5_does_not_retry_itself(self):
  self.inventory=self.baseline;r=self.choose([False]);self.assertEqual(len(r['attempts']),1);self.assertFalse(has_fallback(0x401000,self.inventory,self.baseline))
 def test_typed_generation_refusal_can_fall_back(self):
  def render(e,inv,accepted,**options):
   if inv.passes[0]==self.new:raise ValueError('contradictory typed layout')
   return 'old source'
  r=choose_seed(0x401000,self.inventory,{},render,lambda *a:dict(compiled=True),self.baseline)
  self.assertEqual(r['source'],'old source');self.assertIn('generation_error',r['attempts'][0])
 def test_compiler_infrastructure_errors_propagate(self):
  def missing(*args):raise FileNotFoundError('compiler unavailable')
  with self.assertRaises(FileNotFoundError):choose_seed(0x401000,self.inventory,{},self.render,missing,self.baseline)
 def test_non_boolean_compile_result_is_refused(self):
  with self.assertRaisesRegex(ValueError,'Boolean'):
   choose_seed(0x401000,self.inventory,{},self.render,lambda *a:dict(compiled='yes'),self.baseline)
 def test_two_generation_refusals_do_not_fabricate_a_source(self):
  def refuse(*args,**kwargs):raise ValueError('unresolved export')
  with self.assertRaisesRegex(ValueError,'No compilable or reviewable seed'):
   choose_seed(0x401000,self.inventory,{},refuse,lambda *a:dict(compiled=True),self.baseline)
if __name__=='__main__':unittest.main()
