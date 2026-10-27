# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_mission_waypoint_discovery as c
class RevealAreaEvidence(unittest.TestCase):
 def test_sequences_and_scope(self):
  v=dict(x=0,y=0,z=0,range=0,disabled=0,waypoint=6,heightScale=104,bridge=0,house=0,trim=0,unused=0,fog=0,heightCheck=0,child=0,divisor=1,scaleBits=0,rule1432=0,rule142b=0,origin=0,extent=1,primaryMode=2,secondaryMode=2,predicate=0,allied=0,flagsSeed=0,levelSeed=0,size=1,counts=[1]*11,offsets=[(0,0)],heightOffsets=[(0,0)])
  self.assertEqual(c.parse(c.command(v))['size'],1)
  self.assertIn('src/sim/RevealArea.cpp',c.NATIVE)
  class Exe:
   def read_bytes(self):return b'fixture'
  with patch.object(c,'verify',return_value={'counts':[1]*11}):rows=list(c.scenarios(Exe()))
  self.assertEqual(len(rows),96);values=[c.parse(cmd) for _,cmd in rows]
  self.assertEqual(sum(v['disabled']==0 for v in values),72)
  self.assertEqual({v['bridge'] for v in values},{0,0x100,0x400})
  self.assertEqual({v['primaryMode'] for v in values},{0,1,2})
 def test_input_and_binary_guards(self):
  with self.assertRaises(ValueError):c.parse('')
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_reuse_scope_guard(self):
  identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[],labels=[],expected=[],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  class A:exe=None
  with patch.object(c,'scenarios',return_value=[]):c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}),A())
  with patch.object(c,'scenarios',return_value=[]):
   with self.assertRaises(ValueError):c.validate(e,r,'receipt',dict(identity,original={'engine':'changed'}),A())
  bad=copy.deepcopy(e);bad['evidence']['production_visibility_schedule']=True
  with patch.object(c,'scenarios',return_value=[]):
   with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity,A())
if __name__=='__main__':unittest.main()
