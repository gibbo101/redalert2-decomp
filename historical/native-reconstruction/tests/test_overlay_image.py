# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from unittest.mock import patch
import compare_overlay_image as c
class OverlayImageDomain(unittest.TestCase):
 def test_inputs(self):
  rows=list(c.scenarios());self.assertGreater(len(rows),250)
  for _,cmd in rows:c.parse(cmd)
  for cmd in (c.command(0,1,0,0,0,0,1,1,'X'),c.command(-1,1,1,0,0,0,1,1,'X'),c.command(0,1,1,0,0,0,1,1,'../X'),c.command(3,1,1,0,0,0,1,1,'X')):
   with self.assertRaises(ValueError):c.parse(cmd)
 def test_identity_refusal(self):
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(c.FLAGS,identities=dict(original='old')))
  with patch.object(c,'validate_receipt'):
   with self.assertRaises(ValueError):c.validate(e,{},'receipt',dict(original='new'))
