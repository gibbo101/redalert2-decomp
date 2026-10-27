# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from unittest.mock import patch
import compare_radar_projection as c
class ProjectionDomain(unittest.TestCase):
 def test_inputs(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),70)
  for _,cmd in rows:self.assertEqual(c.command(*c.parse(cmd)),cmd)
  for at,v in ((0,0),(1,33),(2,-1),(4,33),(6,2),(7,-1),(8,2),(9,256),(10,-1),(11,2)):
   f=c.parse(rows[0][1]);f[at]=v
   with self.assertRaises(ValueError):c.parse(c.command(*f))
 def test_trace_refusals(self):
  cmd=next(c.scenarios())[1]
  for row in ([],['R'],['S','0','4','3','R']):
   with self.assertRaises(ValueError):c.validate_row(cmd,row)
 def test_original_identity_and_scope_refuse(self):
  base=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(c.FLAGS,identities=dict(original='old')))
  with patch.object(c,'validate_receipt'):
   with self.assertRaises(ValueError):c.validate(base,{},'receipt',dict(original='new'))
   base['evidence']['identities']['original']='new';base['evidence']['production_or_SDL_adoption']=True
   with self.assertRaises(ValueError):c.validate(base,{},'receipt',dict(original='new'))
