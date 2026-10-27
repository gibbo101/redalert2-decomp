# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from unittest.mock import patch
import compare_radar_resource_color as c
class RadarResourceDomain(unittest.TestCase):
 def test_inputs(self):
  rows=list(c.scenarios());self.assertGreater(len(rows),900)
  for _,cmd in rows:c.parse(cmd)
  good=c.standalone(1,0,c.profile(overlay=127,mode=1),[[0,127,12,0,9,25]])
  for cmd in (good+' 1',good.rsplit(' ',1)[0],good.replace('127 12','2147483648 12'),c.standalone(1,0,c.profile(),[[0]*6]*9)):
   with self.assertRaises(ValueError):c.parse(cmd)
 def test_identity_refusal(self):
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(c.FLAGS,identities=dict(original='old')))
  with patch.object(c,'validate_receipt'):
   with self.assertRaises(ValueError):c.validate(e,{},'receipt',dict(original='new'))
