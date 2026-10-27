# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from unittest.mock import patch
import compare_radar_cell_notification as c
class NotificationEvidence(unittest.TestCase):
 def test_inputs_and_bounds(self):
  for _,cmd in c.scenarios():c.parse(cmd)
  for cmd in (c.command(x=32768),c.command(y=-32769),c.command(present=2),c.command(scale=-1),c.command()+' 1'):
   with self.assertRaises(ValueError):c.parse(cmd)
 def test_trace_shape(self):
  for row in ([],['W','Z'],['X','1','Z'],['Z','Z']):
   with self.assertRaises(ValueError):c.validate_row(c.command(),row)
 def test_changed_original_refuses(self):
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(c.FLAGS,identities=dict(original='old')))
  with patch.object(c,'validate_receipt'):
   with self.assertRaises(ValueError):c.validate(e,{},'hash',dict(original='new'))
 def test_relabelled_receipt_refuses(self):
  e=dict(evidence=dict(evidence_mode='fresh-original',original_instructions_executed=True))
  with self.assertRaises(ValueError):c.validate_receipt(e,dict(e['evidence'],expectations_sha256='wrong'),'hash')
