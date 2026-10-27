# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_infantry_membership_discovery as c
class InfantryMembershipDiscoveryEvidence(unittest.TestCase):
 def test_complete_scenarios(self):
  rows=[c.parse(cmd) for _,cmd in c.scenarios([0]*100)]
  self.assertEqual(len(rows),142);self.assertEqual(sum(len(r[-1]) for r in rows),562)
  self.assertEqual({r[1][3] for r in rows},{-1,0,1})
  self.assertEqual({r[1][6] for r in rows},{0,1})
  self.assertIn('src/sim/MembershipPolicy.hpp',c.NATIVE)
 def test_guards(self):
  with self.assertRaises(ValueError):c.verify(b'wrong binary')
  with self.assertRaises(ValueError):c.parse('U 0')
  with self.assertRaises((ValueError,AssertionError,IndexError)):c.parse('D 0')
 def test_separate_original_native_identity(self):
  identity=dict(original={'engine':'one'},native_sources={'native':'old'},native_inputs={'data':'one'})
  meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original')
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[],labels=[],expected=[],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  class A:exe=None
  with patch.object(c,'plane_data',return_value=[0]*100),patch.object(c,'scenarios',return_value=[]):
   c.validate(e,r,'receipt',dict(identity,native_sources={'native':'rebuilt'}),A())
   with self.assertRaises(ValueError):c.validate(e,r,'receipt',dict(identity,original={'engine':'changed'}),A())
   bad=copy.deepcopy(e);bad['evidence']['full_Walk_sight_schedule']=True
   with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity,A())
if __name__=='__main__':unittest.main()
