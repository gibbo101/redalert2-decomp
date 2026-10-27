# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_tagged_infantry_discovery as d
class TaggedInfantryDiscoveryEvidence(unittest.TestCase):
 def row(self):
  return ['F']+['0']*11+['4','0']
 def test_scenarios(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),398)
  for _,cmd in rows:self.assertEqual(len(d.parse(cmd)),19)
 def test_invalid_inputs(self):
  for cmd in ('',d.command(current=2),d.command(owner=-1),d.command(discoverer=2),d.command(field372=256),d.command(tag=2),d.command(country=0),d.command(loading=2**31),d.command()+' tail'):
   with self.assertRaises(ValueError):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong binary')
 def test_rows(self):
  row=self.row();d.validate_row(row)
  for bad in ([],['F'],['11','0','0','0','0','0']+row,row+['extra'],row[:1]+['256']+row[2:],row[:-2]+['3','0'],row[:-1]+['1']):
   with self.assertRaises(ValueError):d.validate_row(bad)
 def test_replay_provenance(self):
  rows=list(d.scenarios());current={'original':{'pin':'expected'}}
  evidence=dict(d.FLAGS,identities=current,original_instructions_executed=True,original_instructions_modified=False)
  receipt=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=evidence,labels=[x[0] for x in rows],commands=[x[1] for x in rows],expected=[self.row() for _ in rows])
  from unittest.mock import patch
  with patch.object(d,'validate_receipt'):
   d.validate(receipt,{},'ignored',current)
   for mutate in (lambda e:e['evidence'].update(actual_tag_trigger_event7_mismatch=False),lambda e:e['evidence'].update(original_instructions_modified=True),lambda e:e['commands'].pop(),lambda e:e['evidence']['identities'].update(original={})):
    bad=copy.deepcopy(receipt);mutate(bad)
    with self.assertRaises((ValueError,KeyError)):d.validate(bad,{},'ignored',current)
if __name__=='__main__':unittest.main()
