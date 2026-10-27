# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import compare_radar_surface_startup as c
class RadarStartupDomain(unittest.TestCase):
 def test_inputs(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),304)
  for _,cmd in rows:self.assertEqual(c.command(*c.parse(cmd)),cmd)
  for at,v in ((0,2**31),(5,-2**31-1),(6,16),(7,256),(8,2),(9,-1),(10,2**32),(11,-1)):
   f=c.parse(rows[0][1]);f[at]=v
   with self.assertRaises(ValueError):c.parse(c.command(*f))
 def test_trace_refusals(self):
  cmd=next(c.scenarios())[1]
  for row in ([],['R'],['O','0','4','3','R']):
   with self.assertRaises(ValueError):c.validate_row(cmd,row)
