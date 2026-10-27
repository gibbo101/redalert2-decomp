# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_frame_invalidation as d
class FrameInvalidationEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(d.scenarios());identity=dict(original={'inspection':'exact','sources':{'oracle':'original'}},native_sources={'kernel':'old'})
  meta=dict(d.FLAGS,identities=identity,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False)
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in rows],labels=[s for s,_ in rows],expected=[['F']+['0']*32 for _ in rows],evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),copy.deepcopy(identity)
 def test_inputs(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),525)
  parsed=[d.parse(c) for _,c in rows];self.assertEqual({v[0] for v in parsed},{0,1,2});self.assertEqual({v[1] for v in parsed},set(range(7)))
  for index,value in ((0,3),(1,7),(9,4),(10,4),(14,4),(22,7),(23,256),(80,256)):
   bad=parsed[0].copy();bad[index]=value
   with self.assertRaises(ValueError):d.parse(' '.join(map(str,bad)))
 def test_reuse_separates_original_and_native(self):
  e,r,c=self.fixture();c['native_sources']['kernel']='current';d.validate(e,r,'receipt',c)
  c['original']['sources']['oracle']='changed'
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
 def test_invalid_receipts_and_rows(self):
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):d.validate(e,r,'wrong',c)
  for field in ('commands','labels','expected'):
   bad=copy.deepcopy(e);bad[field]=bad[field][1:]
   with self.assertRaises(ValueError):d.validate(bad,r,'receipt',c)
  for row in ([],['F'],['F','F'],['99','0','0','0','F']+['0']*32,['F']+['0']*30+['1','0']):
   with self.assertRaises(ValueError):d.validate_row(row)
 def test_exact_engine_and_scope(self):
  with self.assertRaises(ValueError):d.verify(b'wrong engine')
  e,r,c=self.fixture();e['evidence']['type_bounds_supplied']=False;r=dict(e['evidence'],expectations_sha256='receipt')
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
if __name__=='__main__':unittest.main()
