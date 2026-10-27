# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_reveal_area as c
class RevealAreaEvidence(unittest.TestCase):
 def test_sequences_and_scope(self):
  v=dict(x=0,y=0,z=0,range=0,house=0,trim=0,unused=0,fog=0,heightCheck=0,child=0,divisor=1,scaleBits=0,rule1432=0,rule142b=0,origin=0,extent=1,primaryMode=2,secondaryMode=2,predicate=0,allied=0,flagsSeed=0,levelSeed=0,size=1,counts=[1]*11,offsets=[(0,0)],heightOffsets=[(0,0)])
  self.assertEqual(c.parse(c.command(v))['size'],1)
  self.assertIn('src/sim/RevealArea.cpp',c.NATIVE)
 def test_input_and_binary_guards(self):
  with self.assertRaises(ValueError):c.parse('')
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_reuse_scope_guard(self):
  identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[],labels=[],expected=[],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  class A:exe=None
  with patch.object(c,'scenarios',return_value=[]):c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}),A())
  bad=copy.deepcopy(e);bad['evidence']['production_visibility_schedule']=True
  with patch.object(c,'scenarios',return_value=[]):
   with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity,A())
if __name__=='__main__':unittest.main()
