# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from unittest.mock import patch
import compare_building_coordinates as c
class BuildingCoordinatesEvidence(unittest.TestCase):
 def rows(self):
  with patch('verify_building_coordinates.tables',return_value=([1]*22,[1]*22)):
   return list(c.scenarios(b'supplied table fixture only'))
 def test_domain(self):
  rows=self.rows();self.assertEqual(len(rows),1034)
  self.assertEqual(sum(c.parse(cmd)['op']=='R' for _,cmd in rows),528)
  self.assertEqual({c.parse(cmd)['index'] for _,cmd in rows},set(range(22)))
 def test_invalid_inputs(self):
  good=self.rows()[0][1]
  for cmd in ('',good+' 0',good.replace('W ','Z ',1)):
   with self.assertRaises((ValueError,IndexError)):c.parse(cmd)
  v=good.split();v[1]='-1'
  with self.assertRaises(ValueError):c.parse(' '.join(v))
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
if __name__=='__main__':unittest.main()
