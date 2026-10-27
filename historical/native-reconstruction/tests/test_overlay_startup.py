# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from unittest.mock import patch
import compare_overlay_startup as c
class OverlayStartupDomain(unittest.TestCase):
 def test_inputs(self):
  rows=list(c.scenarios());self.assertGreater(len(rows),500)
  for _,cmd in rows:c.parse(cmd)
  base=[0,0,0,0,0,0,0,1,10,12,0,1,'GASAND']
  for i,value in ((0,3),(1,256),(8,32768),(9,-32769),(12,'../X')):
   values=base.copy();values[i]=value
   with self.assertRaises(ValueError):c.parse(c.command(*values))
 def test_identity_refusal(self):
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(c.FLAGS,identities=dict(original='old')))
  with patch.object(c,'validate_receipt'):
   with self.assertRaises(ValueError):c.validate(e,{},'receipt',dict(original='new'))
