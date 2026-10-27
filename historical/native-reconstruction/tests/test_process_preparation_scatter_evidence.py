# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_process_preparation_scatter as d
class ProcessPreparationEvidence(unittest.TestCase):
 def test_sources_and_scenarios(self):
  for path in d.SOURCES:self.assertTrue((d.ROOT/path).is_file(),path)
  cases=list(d.scenarios());self.assertGreaterEqual(len(cases),30)
  for _,cmd in cases:self.assertEqual(len(d.parse(cmd)['supplied_route']),24)
 def test_new_domain_does_not_widen_legacy_protocol(self):
  cmd=next(d.scenarios())[1]
  with self.assertRaises(ValueError):d.parent.parse(cmd)
  for changed in (cmd+' trailing',cmd.replace('R 256','R 2147483648',1),cmd.replace('R 256 -31 2','R 256 -31 9',1)):
   with self.assertRaises(ValueError):d.parse(changed)
 def test_scope_is_explicit(self):
  self.assertTrue(d.FLAGS['supplied_route_finder']);self.assertFalse(d.FLAGS['complete_Process1_verified']);self.assertFalse(d.FLAGS['production_runtime_enabled'])
 def test_binary_guard(self):
  with self.assertRaises(ValueError):d.verify(b'wrong executable')
 def test_neighbor_inputs_preserve_legacy_scope_and_direction_coverage(self):
  cases=[(label,cmd) for label,cmd in d.scenarios() if label.startswith('neighbor_')]
  self.assertEqual(len(cases),120)
  self.assertEqual({d.parse(cmd)['neighbor_overlay'][1] for _,cmd in cases},{0,1,255})
  for _,cmd in cases:
   c=d.parse(cmd);first,second=c['supplied_route'][:2]
   self.assertEqual(c['speed'],255)
   self.assertNotEqual(second,(first+4)%8)
   if c['neighbor_overlay'][1]==0:self.assertEqual(first,second)
   with self.assertRaises(ValueError):d.parent.parse(cmd)
  cmd=cases[0][1]
  for changed in (cmd.replace('L 1 ','L 9 ',1),cmd.replace(' 0 R ',' 256 R ',1),cmd+' trailing'):
   with self.assertRaises(ValueError):d.parse(changed)
if __name__=='__main__':unittest.main()
