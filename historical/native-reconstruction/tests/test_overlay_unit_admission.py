# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_overlay_unit_admission as d
class OverlayAdmissionEvidence(unittest.TestCase):
 def test_overlay_prefix_is_separate_from_legacy(self):
  cmd=d.command();overlay,fixture=d.parse(cmd)
  self.assertEqual(overlay[3][0],[0,-1]);self.assertEqual(len(fixture),8)
  with self.assertRaises(ValueError):d.parent.parse(cmd)
 def test_scenario_inputs_and_raw_flags(self):
  cases=list(d.scenarios());self.assertEqual(len(cases),473)
  for _,cmd in cases:d.parse(cmd)
  self.assertTrue(any('255' in cmd for _,cmd in cases))
 def test_bounds_and_extra_tokens(self):
  for cmd in ('','V 0',d.command()+' trailing',d.command(override=2147483648),
   d.command(human=256),d.command(overlay_cells=[[3,0],[-1,-1],[-1,-1]])):
   with self.assertRaises(ValueError):d.parse(cmd)
 def test_exact_binary_required(self):
  with self.assertRaises(ValueError):d.verify(b'wrong executable')
 def fixture(self):
  current={'sources':{'kernel':'one'},'inspection':{'range':'two'}}
  proof={'evidence_mode':'fresh-original','identities':current,'native_sha256':'historical runner',
   'overlay_admission_only':True,'audited_original_calls':481,'root_returns':{str(i):1 for i in (0,4,5,6,7)},
   'overlay_instruction_counts':{k:1 for k in ('overlay_registry','House_control','0x703368','0x70338f','0x7033c1','0x703406','0x703428','0x703451')}}
  e={'executable_sha256':d.PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
   'commands':[d.command()],'expected':[['0']],'labels':['fixture'],'evidence':proof}
  return e,{**proof,'expectations_sha256':'fingerprint'},copy.deepcopy(current)
 def test_rebuilt_runner_and_guarded_receipts(self):
  e,r,c=self.fixture();d.validate(e,r,'fingerprint',c)
  for key in ('sources','inspection'):
   e,r,c=self.fixture();c[key]='changed'
   with self.assertRaises(ValueError):d.validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):d.validate(e,r,'wrong',c)
  for key in ('executable_sha256','profile','commands'):
   e,r,c=self.fixture();e[key]=[] if key=='commands' else 'wrong'
   with self.assertRaises(ValueError):d.validate(e,r,'fingerprint',c)
 def test_missing_branch_or_result_coverage_refused(self):
  for key in ('overlay_registry','House_control','0x703368','0x703406','0x703428','0x703451'):
   e,r,c=self.fixture();e['evidence']['overlay_instruction_counts'][key]=0
   with self.assertRaises(ValueError):d.check_coverage(e['evidence'])
  e,r,c=self.fixture();del e['evidence']['root_returns']['4']
  with self.assertRaises(ValueError):d.check_coverage(e['evidence'])
if __name__=='__main__':unittest.main()
