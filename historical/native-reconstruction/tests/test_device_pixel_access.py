# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from unittest.mock import patch
import compare_device_pixel_access as c
class DevicePixelDomain(unittest.TestCase):
 def test_inputs(self):
  for _,cmd in c.scenarios():c.parse(cmd)
  for cmd in [c.command()+' 1',c.command().rsplit(' ',1)[0],c.command(operations='X'),c.command(enabled=256),c.command(count=2147483648)]:
   with self.assertRaises(ValueError):c.parse(cmd)
 def test_identity(self):
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(c.FLAGS,identities=dict(original='old')))
  with patch.object(c,'validate_receipt'):
   with self.assertRaises(ValueError):c.validate(e,{},'receipt',dict(original='new'))
