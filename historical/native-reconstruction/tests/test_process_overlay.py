# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import compare_process_overlay as d
class ProcessOverlayEvidence(unittest.TestCase):
 def test_separate_prefix_and_raw_fields(self):
  cases=list(d.scenarios());self.assertGreater(len(cases),50)
  for _,cmd in cases:
   c=d.parse(cmd);self.assertEqual(len(c['candidate_overlay']),9)
   with self.assertRaises(ValueError):d.parent.parse(cmd)
 def test_invalid_inputs(self):
  cmd=next(d.scenarios())[1]
  for bad in ('','X 0',cmd+' trailing',cmd.replace('X 4','X 10',1)):
   with self.assertRaises(ValueError):d.parse(bad)
 def test_required_original_coverage(self):
  with self.assertRaises(ValueError):d.check_coverage({'actual_counts':{},'cases':1,'audited_complete_Process_calls':1})
 def test_exact_executable(self):
  with self.assertRaises(ValueError):d.verify(b'wrong executable')
if __name__=='__main__':unittest.main()
