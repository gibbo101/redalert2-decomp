# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from unittest.mock import patch
import compare_radar_actor_placement as c
class PlacementEvidence(unittest.TestCase):
 def test_inputs(self):
  for _,cmd in c.scenarios():c.parse(cmd)
  for cmd in (c.command(kind=7),c.command(divisor=0),c.command(permission=512),c.command(secondary=128),c.command()+' 1'):
   with self.assertRaises(ValueError):c.parse(cmd)
 def test_changed_original_refuses(self):
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(c.FLAGS,identities=dict(original='old')))
  with patch.object(c,'validate_receipt'):
   with self.assertRaises(ValueError):c.validate(e,{},'receipt',dict(original='new'))
 def test_malformed_output_refuses(self):
  for row in (['F'],['Q','1','F','1','2','3','4','5'],['F','1','2','3','4','5','6']):
   with self.assertRaises(ValueError):c.validate_row(c.command(),row)
