# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_infantry_resume_ability as d
class InfantryResumeAbilityEvidence(unittest.TestCase):
 def row(self):return ['F','0','1','0',str((-999)&0xffffffff),'0','0','7','3','0','0','0','A','0','0','0','0','0','255','255',str((-1)&0xffffffff),'128']
 def test_scenarios(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),3320)
  for _,cmd in rows:self.assertEqual(len(d.parse(cmd)),35)
 def test_inputs(self):
  for cmd in ('',d.command(root=1),d.command(index=18),d.command(index=5),d.command(pending=1),d.command(entered=256),d.command(mutation=4),d.command(at=9),d.command(vflag=256),d.command()+' tail'):
   with self.assertRaises(ValueError):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong executable')
 def test_rows(self):
  row=self.row();d.validate_row(row)
  for bad in (row+['0'],['34','0','0']+row,['1','0']+row,row[:15]+['2']+row[16:]):
   with self.assertRaises(ValueError):d.validate_row(bad)
 def test_reuse_guards(self):
  rows=list(d.scenarios());current={'original':{'pin':'expected'}}
  evidence=dict(d.FLAGS,identities=current,original_instructions_executed=True,original_instructions_modified=False)
  receipt=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=evidence,labels=[x[0] for x in rows],commands=[x[1] for x in rows],expected=[self.row() for _ in rows])
  from unittest.mock import patch
  with patch.object(d,'validate_receipt'):
   d.validate(receipt,{},'ignored',current)
   for mutate in (lambda e:e['evidence'].update(complete_infantry_parent=False),lambda e:e['evidence'].update(original_instructions_modified=True),lambda e:e['commands'].pop(),lambda e:e['evidence']['identities'].update(original={})):
    bad=copy.deepcopy(receipt);mutate(bad)
    with self.assertRaises((ValueError,KeyError)):d.validate(bad,{},'ignored',current)
if __name__=='__main__':unittest.main()
