# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_visibility_startup as comparison

class VisibilityStartupEvidence(unittest.TestCase):
 def test_scope(self):
  self.assertEqual(comparison.scenarios(),[('spread_height_and_projection_startup','V')])
  self.assertIn('src/sim/VisibilityStartup.cpp',comparison.NATIVE)
  self.assertFalse(comparison.FLAGS['production_visibility_schedule'])
 def test_binary_guard(self):
  with self.assertRaises(ValueError):comparison.verify(b'wrong executable')
 def test_reuse_scope_guard(self):
  identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(comparison.FLAGS,identities=identity,evidence_mode='fresh-original');row=['V']+['0']*1368;evidence=dict(executable_sha256=comparison.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=['V'],labels=['spread_height_and_projection_startup'],expected=[row],evidence=meta);receipt=dict(meta,expectations_sha256='receipt')
  class Args:exe=None
  comparison.validate(evidence,receipt,'receipt',identity,Args())
  bad=copy.deepcopy(evidence);bad['evidence']['production_visibility_schedule']=True
  with self.assertRaises(ValueError):comparison.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity,Args())
if __name__=='__main__':unittest.main()
