# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_scenario_special_flags as c
class ScenarioSpecialFlagsEvidence(unittest.TestCase):
 def test_command_and_scope(self):
  self.assertEqual(c.parse(c.command())['op'],2)
  self.assertIn('src/sim/ScenarioSpecialFlags.hpp',c.NATIVE)
 def test_scenario_domains(self):
  rows=[c.parse(cmd) for _,cmd in c.scenarios()]
  self.assertEqual(len(rows),613)
  self.assertEqual({v['op'] for v in rows},{0,1,2})
  self.assertEqual({v['mutation'] for v in rows},set(range(-1,13)))
  with self.assertRaises(ValueError):c.parse(c.command(op=3))
 def test_input_and_binary_guards(self):
  with self.assertRaises(ValueError):c.parse('')
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_reuse_scope_guard(self):
  identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[],labels=[],expected=[],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  class A:exe=None
  with patch.object(c,'scenarios',return_value=[]):c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}),A())
  with patch.object(c,'scenarios',return_value=[]):
   with self.assertRaises(ValueError):c.validate(e,r,'receipt',dict(identity,original={'engine':'different'}),A())
  bad=copy.deepcopy(e);bad['evidence']['full_scenario_startup']=True
  with patch.object(c,'scenarios',return_value=[]):
   with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity,A())
if __name__=='__main__':unittest.main()
