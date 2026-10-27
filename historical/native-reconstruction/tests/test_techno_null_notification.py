# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_techno_null_notification as d
class TechnoNullNotificationEvidence(unittest.TestCase):
 def row(self):
  return ['F']+['0']*7
 def test_scenarios(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),390)
  for _,cmd in rows:self.assertEqual(len(d.parse(cmd)),14)
 def test_invalid_inputs(self):
  for cmd in ('',d.command(root=4),d.command(owner=2),d.command(onMap=256),d.command(executing=-1),d.command(tag=2),d.command(root=2,cost=7),d.command()+' tail'):
   with self.assertRaises(ValueError):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong binary')
 def test_rows(self):
  row=self.row();d.validate_row(row)
  for bad in ([],['F'],['11']*6+row,row+['extra'],row[:5]+['-1']+row[6:],row[:1]+['3']+row[2:]):
   with self.assertRaises(ValueError):d.validate_row(bad)
 def test_replay_provenance(self):
  rows=list(d.scenarios());current={'original':{'pin':'expected'}}
  evidence=dict(d.FLAGS,identities=current,original_instructions_executed=True,original_instructions_modified=False)
  receipt=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=evidence,labels=[x[0] for x in rows],commands=[x[1] for x in rows],expected=[self.row() for _ in rows])
  from unittest.mock import patch
  with patch.object(d,'validate_receipt'):
   d.validate(receipt,{},'ignored',current)
   for mutate in (lambda e:e['evidence'].update(matching_event7_and_live_transfer_unjoined=False),lambda e:e['evidence'].update(original_instructions_modified=True),lambda e:e['commands'].pop(),lambda e:e['evidence']['identities'].update(original={})):
    bad=copy.deepcopy(receipt);mutate(bad)
    with self.assertRaises((ValueError,KeyError)):d.validate(bad,{},'ignored',current)
if __name__=='__main__':unittest.main()
