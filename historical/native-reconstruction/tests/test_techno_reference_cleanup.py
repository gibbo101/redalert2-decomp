# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_techno_reference_cleanup as d
class TechnoReferenceCleanupEvidence(unittest.TestCase):
 def row(self):
  return ['F']+['0']*31
 def test_scenarios(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),760)
  for _,cmd in rows:self.assertEqual(len(d.parse(cmd)),10)
 def test_invalid_inputs(self):
  for cmd in ('',d.command(footCount=-3),d.command(teamCount=5),d.command(subject=2),d.command(matches=16),d.command(mutation=6),d.command(teamMatches=256),d.command(duplicateTeams=2),d.command()+' tail'):
   with self.assertRaises(ValueError):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong binary')
 def test_rows(self):
  row=self.row();d.validate_row(row)
  for bad in ([],['F'],['9','0','0','0','0']+row,row+['extra'],row[:3]+['2']+row[4:],row[:4]+['5']+row[5:]):
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
