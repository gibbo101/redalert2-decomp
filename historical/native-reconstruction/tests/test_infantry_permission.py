# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import compare_infantry_permission as d
class InfantryPermissionEvidence(unittest.TestCase):
 def test_complete_caller_scenarios(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),66)
  for _,cmd in rows:self.assertEqual(len(d.parse(cmd)[0]),9)
  self.assertIn('src/sim/FootPermissionOverride.cpp',d.SOURCES)
  self.assertIn('src/assets/NearbyCellAdmission.hpp',d.SOURCES)
 def test_invalid_inputs_and_engine_refused(self):
  for cmd in ('',d.command(train=256),d.command(shape=(2**31,0,0,1,1)),d.command()+' tail'):
   with self.assertRaises(ValueError):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong engine')
if __name__=='__main__':unittest.main()
