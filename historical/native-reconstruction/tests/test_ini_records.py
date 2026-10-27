# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_ini_records as d
class IniRecordEvidence(unittest.TestCase):
 def row(self):return ['F']+['0']*49
 def test_matrix_and_domain(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),463)
  for _,c in rows:self.assertEqual(len(d.parse(c)),8)
  for c in ('',d.command(op=7),d.command(graph=8),d.command(anchor=0),d.command(member=7),d.command(flags=256),d.command(args=3),d.command(mutation=7),d.command(repeats=0)):
   with self.assertRaises(ValueError):d.parse(c)
  with self.assertRaises(ValueError):d.verify(b'wrong binary')
 def test_rows(self):
  d.validate_row(self.row());d.validate_row(['2','3','0','0','0']+self.row())
  for row in ([],['F'],self.row()+['0'],['99','0','0','0','0']+self.row(),['1','-1','0','0','0']+self.row()):
   with self.assertRaises(ValueError):d.validate_row(row)
 def test_reuse_scope_and_native_identity_separation(self):
  rows=list(d.scenarios());current={'original':{'pin':'exact'},'native_sources':{'new':'hash'}}
  receipt=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(d.FLAGS,identities={'original':{'pin':'exact'},'native_sources':{'old':'hash'}},original_instructions_executed=True,original_instructions_modified=False),labels=[x[0] for x in rows],commands=[x[1] for x in rows],expected=[self.row() for _ in rows])
  with patch.object(d,'validate_receipt'):
   d.validate(receipt,{},'hash',current)
   for change in (lambda e:e['evidence'].update(complete_node_list_entry_lifetime=False),lambda e:e['evidence'].update(production_scheduling=True),lambda e:e['commands'].pop(),lambda e:e['evidence']['identities'].update(original={})):
    altered=copy.deepcopy(receipt);change(altered)
    with self.assertRaises((ValueError,KeyError)):d.validate(altered,{},'hash',current)
if __name__=='__main__':unittest.main()
