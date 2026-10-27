# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_cell_visibility_mask as c
class CellVisibilityMaskEvidence(unittest.TestCase):
 def test_command_and_scope(self):
  v=dict(x=1,y=2,mode=0,slots=[-1]*9,flags12c=[0]*10,flags140=[0]*10,seed=3);self.assertEqual(c.parse(c.command(v))['seed'],3);self.assertIn('src/sim/CellVisibilityMask.cpp',c.NATIVE)
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
