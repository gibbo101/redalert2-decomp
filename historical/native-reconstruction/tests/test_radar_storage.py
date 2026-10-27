# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from unittest.mock import patch
import compare_radar_storage as c
class RadarStorageDomain(unittest.TestCase):
 def test_input_refusals(self):
  for _,cmd in c.scenarios():c.parse(cmd)
  for cmd in ('J 0 1 0 0 0 0 0 1','J 33 1 0 0 0 0 0 1','J 1 1 2147483648 0 0 0 0 1','J 1 1 0 0 0 0 0 3','J 1 1 0 0 0 0 0 1 extra'):
   with self.assertRaises(ValueError):c.parse(cmd)
 def test_original_identity_refusal(self):
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(c.FLAGS,identities=dict(original='old')))
  with patch.object(c,'validate_receipt'):
   with self.assertRaises(ValueError):c.validate(e,{},'receipt',dict(original='new'))
