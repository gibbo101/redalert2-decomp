# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_mission_building_expiration_services as c
class BuildingServiceEvidence(unittest.TestCase):
 def test_roundtrip_and_scope(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),1621)
  for _,cmd in rows:self.assertEqual(c.command(c.parse(cmd)),cmd)
  self.assertEqual({c.parse(cmd)['entry'] for _,cmd in rows},set(range(11)))
  self.assertFalse(c.FLAGS['production_and_waypoint_join'])
 def test_rejection(self):
  with self.assertRaises(ValueError):c.parse('')
  f=c.base()
  for key,value in (('profile',2),('entry',11),('effectMode',5),('pending9C',2**31),('policyByte',-1),('byte404',256),('powerBits',2**64),('root',5),('childMode',1)):
   bad=copy.deepcopy(f);bad[key]=value
   with self.assertRaises((ValueError,IndexError)):c.parse(c.command(bad))
  for key,index,value in (('fields',7,1),('fields',9,8),('weapons',0,1),('typed',0,0)):
   bad=copy.deepcopy(f);bad[key][index]=value
   with self.assertRaises(ValueError):c.parse(c.command(bad))
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_reuse_identity_and_boundary_guards(self):
  identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original',audited_original_calls=0);e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[],labels=[],expected=[],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  with patch.object(c,'scenarios',return_value=[]):
   c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
   with self.assertRaises(ValueError):c.validate(e,r,'receipt',dict(identity,original={'engine':'changed'}))
   bad=copy.deepcopy(e);bad['evidence']['production_and_waypoint_join']=True
   with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()
