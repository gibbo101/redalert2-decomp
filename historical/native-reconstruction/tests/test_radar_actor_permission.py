# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from unittest.mock import patch
import compare_radar_actor_permission as c
class PermissionEvidence(unittest.TestCase):
 def test_inputs(self):
  for _,cmd in c.scenarios():c.parse(cmd)
  for cmd in (c.command(kind=2),c.command(vbits=-1),c.command(aa6=256),c.command(eligible=512),c.command()+' 1'):
   with self.assertRaises(ValueError):c.parse(cmd)
 def test_changed_original_refuses(self):
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(c.FLAGS,identities=dict(original='old')))
  with patch.object(c,'validate_receipt'):
   with self.assertRaises(ValueError):c.validate(e,{},'receipt',dict(original='new'))
 def test_malformed_output_refuses(self):
  for row in (['R'],['Q','1','R','1','2'],['R','1','2','3']):
   with self.assertRaises(ValueError):c.validate_row(c.command(),row)
