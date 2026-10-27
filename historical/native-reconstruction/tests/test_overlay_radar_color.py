# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from unittest.mock import patch
import compare_overlay_radar_color as c
class OverlayColorDomain(unittest.TestCase):
 def test_inputs(self):
  rows=list(c.scenarios());self.assertGreater(len(rows),350)
  for _,cmd in rows:c.parse(cmd)
  good=c.command(1,127,0,1,0,0,1,1).split()
  for at,v in ((1,256),(2,2**31),(3,2**32),(4,2),(5,2),(6,2),(7,32768),(8,-32769),(9,4),(10,-2**31-1)):
   bad=good.copy();bad[at]=str(v)
   with self.assertRaises(ValueError):c.parse(' '.join(bad))
 def test_wrapping_and_backing(self):
  c.parse(c.command(1,127,0x80000000,1,0,0,-1,0))
  with self.assertRaises(ValueError):c.parse(c.command(1,127,1000,1,0,0,-1,0))
 def test_identity_refusal(self):
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(c.FLAGS,identities=dict(original='old')))
  with patch.object(c,'validate_receipt'):
   with self.assertRaises(ValueError):c.validate(e,{},'receipt',dict(original='new'))
