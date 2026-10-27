# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_tactical_viewport as d
class TacticalViewportEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(d.scenarios());origin=dict(original={'inspection':'exact','sources':{'oracle':'original'}},native_sources={'kernel':'old'})
  row=['S','0','0']*4+['I','0','0','0','L','0','0']+['S','0','0']*4+['Z']+['0']*6
  meta=dict(d.FLAGS,identities=origin,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False)
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in rows],labels=[s for s,_ in rows],expected=[row]*len(rows),evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),copy.deepcopy(origin)
 def test_scenarios_cover_boundaries(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),636)
  self.assertEqual(len(rows),len(set(c for _,c in rows)))
  for _,cmd in rows:d.parse(cmd)
  self.assertIn('late_dimensions_after_inverse',{s for s,_ in rows})
 def test_native_changes_allowed_original_changes_refused(self):
  e,r,c=self.fixture();c['native_sources']['kernel']='current';d.validate(e,r,'receipt',c)
  c['original']['sources']['oracle']='changed'
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
 def test_receipt_commands_and_rows_remain_checked(self):
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):d.validate(e,r,'wrong',c)
  for field in ('commands','expected','labels'):
   bad=copy.deepcopy(e);bad[field]=bad[field][1:]
   with self.assertRaises(ValueError):d.validate(bad,r,'receipt',c)
 def test_wrong_engine_and_observation_scope_refused(self):
  with self.assertRaises(ValueError):d.verify(b'wrong engine')
  e,r,c=self.fixture();e['executable_sha256']='other'
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
  e,r,c=self.fixture();e['evidence']['inverse_matrix_probe']=False;r=dict(e['evidence'],expectations_sha256='receipt')
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
if __name__=='__main__':unittest.main()
