# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_sprite_selection as d
class SpriteSelectionEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(d.scenarios());current=dict(original={'inspection':'exact','sources':{'oracle':'original'}},native_sources={'kernel':'old'})
  meta=dict(d.FLAGS,identities=current,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False)
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in rows],labels=[s for s,_ in rows],expected=[['F','0','0','1','0','0','4'] for _ in rows],evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),copy.deepcopy(current)
 def test_domain(self):
  self.assertEqual(len(list(d.scenarios())),2430)
  for _,cmd in d.scenarios():d.parse(cmd)
  for cmd in ([2,0,0,0,0,0,0,0],[0,0,256,0,0,0,0,0],[0,0,0,0,0,0,5,0]):
   with self.assertRaises(ValueError):d.parse(cmd)
 def test_original_identity_not_native_verdict_reused(self):
  e,r,c=self.fixture();c['native_sources']['kernel']='new';d.validate(e,r,'receipt',c)
  c['original']['sources']['oracle']='changed'
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
 def test_changed_receipt_and_corpus_refuse(self):
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):d.validate(e,r,'different',c)
  for key in ('commands','labels','expected'):
   bad=copy.deepcopy(e);bad[key]=bad[key][1:]
   with self.assertRaises(ValueError):d.validate(bad,r,'receipt',c)
  with self.assertRaises(ValueError):d.validate_row(['F'],[0]*8)
 def test_wrong_binary(self):
  with self.assertRaises(ValueError):d.verify(b'wrong executable')
if __name__=='__main__':unittest.main()
