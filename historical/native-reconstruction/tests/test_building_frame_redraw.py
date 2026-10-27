# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_building_frame_redraw as d
class BuildingFrameEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(d.scenarios());identity=dict(original={'inspection':'exact','sources':{'oracle':'original'}},native_sources={'kernel':'old'})
  meta=dict(d.FLAGS,identities=identity,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False)
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in rows],labels=[s for s,_ in rows],expected=[['N','0','R','0']]*len(rows),evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),copy.deepcopy(identity)
 def test_inputs_cover_edges_and_live_mutation(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),553);self.assertEqual(len(rows),len(set(c for _,c in rows)))
  parsed=[d.parse(c) for _,c in rows];self.assertEqual({v[8] for v in parsed},set(range(7)))
  bad=parsed[0].copy();bad[7]=4
  with self.assertRaises(ValueError):d.parse(' '.join(map(str,bad)))
 def test_reuse_separates_original_and_native(self):
  e,r,c=self.fixture();c['native_sources']['kernel']='current';d.validate(e,r,'receipt',c)
  c['original']['sources']['oracle']='changed'
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
 def test_rows_and_provenance_refuse_changes(self):
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):d.validate(e,r,'wrong',c)
  for field in ('commands','labels','expected'):
   bad=copy.deepcopy(e);bad[field]=bad[field][1:]
   with self.assertRaises(ValueError):d.validate(bad,r,'receipt',c)
  for row in ([],['N','0','R','2'],['N','0','G','0','R','0'],['N','0','Z','1','R','0']):
   with self.assertRaises(ValueError):d.validate_row(row)
 def test_exact_engine_and_scope(self):
  with self.assertRaises(ValueError):d.verify(b'wrong engine')
  e,r,c=self.fixture();e['evidence']['actual_building_A8']=False;r=dict(e['evidence'],expectations_sha256='receipt')
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
if __name__=='__main__':unittest.main()
