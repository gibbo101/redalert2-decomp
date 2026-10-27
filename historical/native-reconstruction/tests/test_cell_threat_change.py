# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_cell_threat_change as d
class CellThreatChangeEvidence(unittest.TestCase):
 def row(self):return ['R','0','G','0','G','0','G','0','D','0','0','0','0']
 def test_scenarios(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),1204)
  for _,cmd in rows:self.assertEqual(len(d.parse(cmd)),41)
 def test_inputs(self):
  for cmd in ('',d.command(root=4),d.command(count=5),d.command(nulls=16),d.command(duplicate=2),d.command(mutation=3),d.command(delta=2**31),d.command(x=-32769),d.command()+' tail'):
   with self.assertRaises(ValueError):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong executable')
 def test_rows(self):
  row=self.row();d.validate_row(row)
  for bad in (row+['0'],['4','0','0']+row,['0','999999','0']+row,row[:9]+['0','2','0','0']):
   with self.assertRaises(ValueError):d.validate_row(bad)
 def test_reuse_guards(self):
  rows=list(d.scenarios());current={'original':{'pin':'expected'}}
  evidence=dict(d.FLAGS,identities=current,original_instructions_executed=True,original_instructions_modified=False)
  receipt=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=evidence,labels=[x[0] for x in rows],commands=[x[1] for x in rows],expected=[self.row() for _ in rows])
  from unittest.mock import patch
  with patch.object(d,'validate_receipt'):
   d.validate(receipt,{},'ignored',current)
   for mutate in (lambda e:e['evidence'].update(complete_children=False),lambda e:e['evidence'].update(original_instructions_modified=True),lambda e:e['commands'].pop(),lambda e:e['evidence']['identities'].update(original={})):
    bad=copy.deepcopy(receipt);mutate(bad)
    with self.assertRaises((ValueError,KeyError)):d.validate(bad,{},'ignored',current)
if __name__=='__main__':unittest.main()
