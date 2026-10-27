# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from unittest.mock import patch
import compare_cell_radar_color as c
class ColorDomain(unittest.TestCase):
 def test_inputs(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),254)
  for _,cmd in rows:c.parse(cmd)
  p=rows[0][1].split()
  for at,v in ((1,256),(2,2),(3,2),(4,2**32),(5,2),(6,-2),(7,256),(8,4),(9,0),(10,-1),(11,4),(12,5),(13,16),(14,2),(15,3),(16,2),(17,2**32)):
   bad=p.copy();bad[at]=str(v)
   with self.assertRaises(ValueError):c.parse(' '.join(bad))
 def test_trace_refusals(self):
  cmd=next(c.scenarios())[1]
  for row in ([],['R'],['D','36','0','R']):
   with self.assertRaises(ValueError):c.validate_row(cmd,row)
 def test_original_identity_and_scope_refuse(self):
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(c.FLAGS,identities=dict(original='old')))
  with patch.object(c,'validate_receipt'):
   with self.assertRaises(ValueError):c.validate(e,{},'receipt',dict(original='new'))
   e['evidence']['identities']['original']='new';e['evidence']['authored_tmp_and_animation_and_scale_inputs']=False
   with self.assertRaises(ValueError):c.validate(e,{},'receipt',dict(original='new'))
