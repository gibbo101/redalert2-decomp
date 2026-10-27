# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_cell_redraw as c
class CellRedrawEvidence(unittest.TestCase):
 def test_all_inputs_and_refused_queue_domain(self):
  for _,cmd in c.scenarios():c.parse(cmd)
  for cmd in (c.command(count=-1),c.command(count=801),c.command(redraw=256),c.command()+' 1'):
   with self.assertRaises(ValueError):c.parse(cmd)
 def test_truncated_and_unknown_trace_refused(self):
  for row in (['Z'],['W','1','Z']+['0']*804,['Z']+['0']*803):
   with self.assertRaises(ValueError):c.validate_row(c.command(),row)
 def test_changed_original_refused(self):
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(c.FLAGS,identities=dict(original='old')))
  with patch.object(c,'validate_receipt'):
   with self.assertRaises(ValueError):c.validate(e,dict(expectations_sha256='hash'), 'hash',dict(original='new'))
 def test_receipt_cannot_be_relabelled(self):
  e=dict(evidence=dict(evidence_mode='fresh-original',original_instructions_executed=True))
  r=dict(e['evidence'],expectations_sha256='hash');c.validate_receipt(e,r,'hash')
  for key,value in [('evidence_mode','cached-original-replay'),('original_instructions_executed',False),('expectations_sha256','different')]:
   bad=copy.deepcopy(r);bad[key]=value
   with self.assertRaises(ValueError):c.validate_receipt(e,bad,'hash')
