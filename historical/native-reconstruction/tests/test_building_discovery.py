# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import compare_building_discovery as c
class BuildingDiscoveryEvidence(unittest.TestCase):
 def test_domain(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),816)
  self.assertEqual(sum(len(c.parse(cmd)['discoverers']) for _,cmd in rows),3984)
  self.assertEqual({c.parse(cmd)['count'] for _,cmd in rows},{-1,0,3})
 def test_invalid_input(self):
  good=next(c.scenarios())[1]
  for cmd in ('',good+' 0',good.replace('B ','D ',1),'B 0 1 0 '+good.split(' ',4)[4]):
   with self.assertRaises((ValueError,IndexError)):c.parse(cmd)
  with self.assertRaises(ValueError):c.verify(b'not the supplied executable')
if __name__=='__main__':unittest.main()
