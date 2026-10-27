# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_cell_visibility_live_flags as c
class CellVisibilityLiveFlagsEvidence(unittest.TestCase):
 def test_command_and_scope(self):
  cmd='C 1 2 1 3 4 5 6 7 8 9 10 11 4096 0 2 1 0 0';self.assertEqual(c.parse(cmd)['counter'],6);self.assertIn('src/sim/CellVisibilityChange.cpp',c.NATIVE)
 def test_scenario_domains(self):
  rows=[c.parse(cmd) for _,cmd in c.scenarios()]
  self.assertEqual(len(rows),578)
  self.assertEqual({v['stage'] for v in rows},{0,1,2})
  self.assertEqual({v['rebind'] for v in rows},{0,1})
  self.assertEqual({v['cellMode'] for v in rows},{0,1,2})
  self.assertEqual({v['present'] for v in rows},{0,1})
  with self.assertRaises(ValueError):c.parse(c.command_base(rows[0])+' 3 0 0 0')
 def test_input_and_binary_guards(self):
  with self.assertRaises(ValueError):c.parse('')
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_reuse_scope_guard(self):
  identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[],labels=[],expected=[],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  class A:exe=None
  with patch.object(c,'scenarios',return_value=[]):c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}),A())
  with patch.object(c,'scenarios',return_value=[]):
   with self.assertRaises(ValueError):c.validate(e,r,'receipt',dict(identity,original={'engine':'different'}),A())
  bad=copy.deepcopy(e);bad['evidence']['production_visibility_schedule']=True
  with patch.object(c,'scenarios',return_value=[]):
   with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity,A())
if __name__=='__main__':unittest.main()
