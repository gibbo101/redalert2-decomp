# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_mission_typed_tag_expiration as c
class TypedTagEvidence(unittest.TestCase):
 def test_roundtrip_and_scope(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),871);values=[c.parse(cmd) for _,cmd in rows];self.assertEqual({v['root'] for v in values},set(range(7)));self.assertEqual({v['childMode'] for v in values},set(range(4)))
  self.assertTrue(any(v['root']==6 and v['strengths'][0]==0 for v in values));self.assertFalse(c.FLAGS['waypoint_recipients_and_runtime_join']);self.assertTrue(c.FLAGS['kind4_factory_path_excluded_by_actual_Tag_kind44'])
  f=c.parent.base();f.update(c.defaults());self.assertEqual(c.parse(c.command(f)),f)
 def test_rejection(self):
  with self.assertRaises(ValueError):c.parse('')
  f=c.parent.base();f.update(c.defaults())
  for key,value in (('flags',1),('root',7),('childMode',4),('strengthType',0),('extraCounts',[9,0,0])):
   bad=copy.deepcopy(f);bad[key]=value
   with self.assertRaises((ValueError,IndexError)):c.parse(c.command(bad))
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_reuse_identity_and_boundary_guards(self):
  identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original',audited_original_calls=0);e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[],labels=[],expected=[],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  with patch.object(c,'scenarios',return_value=[]):
   c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
   with self.assertRaises(ValueError):c.validate(e,r,'receipt',dict(identity,original={'engine':'changed'}))
   bad=copy.deepcopy(e);bad['evidence']['waypoint_recipients_and_runtime_join']=True
   with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()
