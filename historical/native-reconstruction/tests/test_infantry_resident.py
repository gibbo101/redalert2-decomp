# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import compare_infantry_resident as d
class ResidentEvidence(unittest.TestCase):
 def test_scenarios(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),518)
  for _,c in rows:self.assertEqual(len(d.parse(c)[0]),8)
 def test_invalid(self):
  for c in ('',d.command(moving=(0,0,256,0,0)),d.command()+' extra'):
   with self.assertRaises(ValueError):d.parse(c)
  with self.assertRaises(ValueError):d.verify(b'wrong executable')
if __name__=='__main__':unittest.main()
