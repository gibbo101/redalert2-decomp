# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_sprite_depth_pixels as d
class SpriteDepthPixelsEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(d.scenarios());identity=dict(original={'inspection':'exact','sources':{'oracle':'original'}},native_sources={'kernel':'old'},auxiliary_asset_sha256='asset')
  meta=dict(d.FLAGS,identities=identity,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False)
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in rows],labels=[s for s,_ in rows],expected=[['0'*64,'1'*64] for _ in rows],evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),copy.deepcopy(identity)
 def test_domain(self):
  self.assertEqual(len(list(d.scenarios())),480)
  self.assertNotEqual(d.fixture(1),d.fixture(3))
  for cmd in ([1,0x2000,0,0,0,0,0],[3,0x6e01,2,0,0,0,0],[3,0x6e00,0,8,0,0,0],[3,0x6e00,0,0,0,0,10]):
   with self.assertRaises(ValueError):d.inputs(cmd)
 def test_original_reuse_native_is_current(self):
  e,r,c=self.fixture();c['native_sources']['kernel']='new';d.validate(e,r,'receipt',c)
  c['original']['sources']['oracle']='changed'
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
 def test_receipt_scope_and_rows(self):
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):d.validate(e,r,'wrong',c)
  for key in ('commands','labels','expected'):
   bad=copy.deepcopy(e);bad[key]=bad[key][1:]
   with self.assertRaises(ValueError):d.validate(bad,r,'receipt',c)
  e['expected'][0]=['garbage','0'*64]
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
 def test_engine_refusal(self):
  with self.assertRaises(ValueError):d.verify(b'wrong engine')
if __name__=='__main__':unittest.main()
