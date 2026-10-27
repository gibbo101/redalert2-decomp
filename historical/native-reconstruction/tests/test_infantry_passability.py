# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_infantry_passability as c
class InfantryPassabilityEvidence(unittest.TestCase):
 def test_scenarios_and_lists(self):
  rows=[c.parse(cmd) for _,cmd in c.scenarios()]
  self.assertEqual(len(rows),160)
  self.assertEqual({a[0] for _,actors in rows for a in actors},{1,6,15,36})
  self.assertTrue(any(len(a)==8 for _,a in rows))
 def test_wrong_binary_and_domain_refuse(self):
  with self.assertRaises(ValueError):c.verify(b'wrong binary')
  with self.assertRaises((ValueError,AssertionError)):c.parse(c.command(actors=[[2,-1,0,0,0,0,0,0]]))
  with self.assertRaises((ValueError,AssertionError)):c.parse(c.command(actors=[[15,0,0,0,0,0,0,0]]))
 def test_reuse_separates_original_from_current_native(self):
  identity=dict(original={'engine':'one'},native_sources={'native':'old'})
  meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original')
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[],labels=[],expected=[],evidence=meta)
  r=dict(meta,expectations_sha256='receipt')
  with patch.object(c,'scenarios',return_value=[]):
   c.validate(e,r,'receipt',dict(identity,native_sources={'native':'rebuilt'}),None)
   with self.assertRaises(ValueError):c.validate(e,r,'receipt',dict(identity,original={'engine':'changed'}),None)
   bad=copy.deepcopy(e);bad['evidence']['full_movement_original_proof']=True
   with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity,None)
if __name__=='__main__':unittest.main()
