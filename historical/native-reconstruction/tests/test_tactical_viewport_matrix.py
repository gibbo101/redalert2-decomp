# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_tactical_viewport_matrix as d
from verify_tactical_viewport_matrix import inspect_dispatch
class TacticalViewportMatrixEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(d.scenarios());identity=dict(original={'inspection':'exact','sources':{'oracle':'original'}},native_sources={'kernel':'old'})
  row=['S','0','0']*4+['I','0','0','0','O','0','0','0']+['S','0','0']*4+['Z']+['0']*6
  meta=dict(d.FLAGS,identities=identity,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False)
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in rows],labels=[s for s,_ in rows],expected=[row]*len(rows),evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),copy.deepcopy(identity)
 def test_scenarios_and_finite_domain(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),688);self.assertEqual(len(rows),len(set(c for _,c in rows)))
  for _,c in rows:d.parse(c)
  v=d.parse(rows[0][1]);v[4]=0x7f800000
  with self.assertRaises(ValueError):d.parse(' '.join(map(str,v)))
 def test_native_rebuild_reuses_original_but_original_change_refuses(self):
  e,r,c=self.fixture();c['native_sources']['kernel']='current';d.validate(e,r,'receipt',c)
  c['original']['sources']['oracle']='changed'
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
 def test_provenance_and_rows(self):
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):d.validate(e,r,'wrong',c)
  for key in ('commands','labels','expected'):
   bad=copy.deepcopy(e);bad[key]=bad[key][1:]
   with self.assertRaises(ValueError):d.validate(bad,r,'receipt',c)
  bad=copy.deepcopy(e);bad['expected'][0]=bad['expected'][0][1:]
  with self.assertRaises(ValueError):d.validate(bad,r,'receipt',c)
 def test_scope_and_executable_identity(self):
  for verify in (d.verify,inspect_dispatch):
   with self.assertRaises(ValueError):verify(b'wrong engine')
  e,r,c=self.fixture();e['evidence']['actual_matrix_transform']=False;r=dict(e['evidence'],expectations_sha256='receipt')
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
if __name__=='__main__':unittest.main()
