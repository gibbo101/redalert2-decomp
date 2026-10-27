# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from unittest.mock import patch
import compare_radar_terrain as c
class TerrainDomain(unittest.TestCase):
 def test_inputs(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),88)
  for _,cmd in rows:c.parse(cmd)
  p=rows[0][1].split()
  for at,v in ((1,2),(2,1),(3,33),(4,-65),(5,0),(6,33),(7,-1),(9,17),(11,256),(12,-2),(13,65),(14,-1),(15,32768)):
   bad=p.copy();bad[at]=str(v)
   with self.assertRaises(ValueError):c.parse(' '.join(bad))
 def test_empty_map(self):
  row=list(c.scenarios())[-1][1];self.assertEqual(c.parse(row)[-1],[])
 def test_trace_refusals(self):
  cmd=next(c.scenarios())[1]
  for row in ([],['R'],['U','V','0','R']):
   with self.assertRaises(ValueError):c.validate_row(cmd,row)
 def test_original_identity_and_scope_refuse(self):
  base=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(c.FLAGS,identities=dict(original='old')))
  with patch.object(c,'validate_receipt'):
   with self.assertRaises(ValueError):c.validate(base,{},'receipt',dict(original='new'))
   base['evidence']['identities']['original']='new';base['evidence']['cell_colors4712C0_supplied']=False
   with self.assertRaises(ValueError):c.validate(base,{},'receipt',dict(original='new'))
