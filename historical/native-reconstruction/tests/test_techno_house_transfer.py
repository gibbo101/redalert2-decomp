# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_techno_house_transfer as d
class TechnoTransferEvidence(unittest.TestCase):
 def row(self):
  return ['F','0','1']+['0']*265
 def test_scenarios(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),616)
  for _,cmd in rows:self.assertEqual(len(d.parse(cmd)),13)
 def test_invalid_inputs(self):
  for cmd in ('',d.command(nextHouse=0),d.command(nextHouse=3),d.command(localHouse=-1),d.command(flag76=256),d.command(flags14=-1),d.command(root=2),d.command(mutation=2),d.command(cell=2),d.command()+' tail'):
   with self.assertRaises(ValueError):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong binary')
 def test_rows(self):
  row=self.row();d.validate_row(row)
  for bad in ([],['F'],['2']*6+row,row+['extra'],row[:5]+['-1']+row[6:],row[:2]+['3']+row[3:]):
   with self.assertRaises(ValueError):d.validate_row(bad)
 def test_replay_provenance(self):
  rows=list(d.scenarios());current={'original':{'pin':'expected'}}
  evidence=dict(d.FLAGS,identities=current,original_instructions_executed=True,original_instructions_modified=False)
  receipt=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=evidence,labels=[x[0] for x in rows],commands=[x[1] for x in rows],expected=[self.row() for _ in rows])
  from unittest.mock import patch
  with patch.object(d,'validate_receipt'):
   d.validate(receipt,{},'ignored',current)
   for mutate in (lambda e:e['evidence'].update(production_transfer_unjoined=False),lambda e:e['evidence'].update(original_instructions_modified=True),lambda e:e['commands'].pop(),lambda e:e['evidence']['identities'].update(original={})):
    bad=copy.deepcopy(receipt);mutate(bad)
    with self.assertRaises((ValueError,KeyError)):d.validate(bad,{},'ignored',current)
if __name__=='__main__':unittest.main()
