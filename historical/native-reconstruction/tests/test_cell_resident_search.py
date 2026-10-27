# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from unittest.mock import patch
import compare_cell_resident_search as c
class ResidentSearchDomain(unittest.TestCase):
 def test_inputs(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),288)
  for _,cmd in rows:c.parse(cmd)
  base=c.command(1,0,36,1,[36,6]).split()
  for at,value in ((1,-1),(1,256),(2,-1),(2,2**32),(3,-2**31-1),(3,2**31),(4,-1),(4,3),(5,33),(6,2**31)):
   bad=base.copy();bad[at]=str(value)
   with self.assertRaises(ValueError):c.parse(' '.join(bad))
 def test_original_identity_and_scope_refuse(self):
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(c.FLAGS,identities=dict(original='old')))
  with patch.object(c,'validate_receipt'):
   with self.assertRaises(ValueError):c.validate(e,{},'receipt',dict(original='new'))
   e['evidence']['identities']['original']='new';e['evidence']['virtual_kind_supplied']=False
   with self.assertRaises(ValueError):c.validate(e,{},'receipt',dict(original='new'))
