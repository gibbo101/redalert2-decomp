# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import compare_team_script as d
class TeamScriptEvidence(unittest.TestCase):
 def test_scenarios(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),585)
  for _,c in rows:self.assertEqual(len(d.parse(c)),9)
 def test_invalid(self):
  for c in ('',d.command(members=0),d.command(complete=0,cursor=-1),d.command(argument=2**31),d.command()+' tail'):
   with self.assertRaises(ValueError):d.parse(c)
  with self.assertRaises(ValueError):d.verify(b'wrong binary')
 def test_rows(self):
  for row in ([],['F'],['1']*6+['F']+['0']*26,['9']*6+['F']+['0']*27):
   with self.assertRaises(ValueError):d.validate_row(row)
if __name__=='__main__':unittest.main()
