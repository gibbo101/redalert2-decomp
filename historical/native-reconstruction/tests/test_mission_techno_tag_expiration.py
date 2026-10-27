# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_mission_techno_tag_expiration as c
class TechnoTagEvidence(unittest.TestCase):
 def test_roundtrip_and_scope(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),448);values=[c.parse(cmd) for _,cmd in rows]
  self.assertEqual({v['root'] for v in values},set(range(4)));self.assertEqual({v['mode'] for v in values},set(range(4)))
  self.assertEqual({v['subject'] for v in values},{1,2});self.assertTrue(any(len(v['operations'])>1 for v in values));self.assertFalse(c.FLAGS['typed_Foot_Infantry_Building_and_runtime_join'])
  f=c.base();self.assertEqual(c.parse(c.command(f)),f)
 def test_rejection(self):
  with self.assertRaises(ValueError):c.parse('')
  for key,value in (('flags',1),('subject',0),('mode',4),('operations',[]),('next',[1,0,1])):
   f=c.base();f[key]=value
   with self.assertRaises(ValueError):c.parse(c.command(f))
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_original_identity_and_scope_guard(self):
  identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original',audited_original_calls=0);e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[],labels=[],expected=[],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  with patch.object(c,'scenarios',return_value=[]):
   c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
   with self.assertRaises(ValueError):c.validate(e,r,'receipt',dict(identity,original={'engine':'changed'}))
   bad=copy.deepcopy(e);bad['evidence']['typed_Foot_Infantry_Building_and_runtime_join']=True
   with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()
