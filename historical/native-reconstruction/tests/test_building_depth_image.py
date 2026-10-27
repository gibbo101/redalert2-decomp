# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_building_depth_image as d
class BuildingDepthEvidence(unittest.TestCase):
 def fixture(self):
  d.ASSET=d.fixture(3,2,1,32,71,3);rows=list(d.scenarios());current=dict(original={'inspection':'exact','asset_source_sha256':'asset','sources':{'oracle':'original'}},native_sources={'kernel':'old'})
  meta=dict(d.FLAGS,identities=current,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False)
  row=['F','2',*['0'*64]*4,'0'];e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in rows],labels=[s for s,_ in rows],expected=[row for _ in rows],evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),copy.deepcopy(current)
 def test_domain(self):
  d.ASSET=d.fixture(3,2,1,32,71,3)
  self.assertEqual(len(list(d.scenarios())),390)
  for _,cmd in d.scenarios():d.parse(cmd)
  for cmd in ([2,0,'00'*32],[0,3,'00'*32],[0,0,'00']):
   with self.assertRaises(ValueError):d.parse(cmd)
 def test_native_changes_reuse_original_only(self):
  e,r,c=self.fixture();c['native_sources']['kernel']='new';d.validate(e,r,'receipt',c)
  c['original']['sources']['oracle']='changed'
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
 def test_asset_and_receipt_refuse(self):
  e,r,c=self.fixture();c['original']['asset_source_sha256']='different'
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):d.validate(e,r,'different',c)
  for key in ('commands','labels','expected'):
   bad=copy.deepcopy(e);bad[key]=bad[key][1:]
   with self.assertRaises(ValueError):d.validate(bad,r,'receipt',c)
 def test_wrong_binary_and_row_refuse(self):
  with self.assertRaises(ValueError):d.verify(b'wrong executable')
  with self.assertRaises(ValueError):d.validate_row(['F','2','bad'],[0,0,'00'*32])
if __name__=='__main__':unittest.main()
