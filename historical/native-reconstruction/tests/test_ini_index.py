# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_ini_index as d
class IniIndexEvidence(unittest.TestCase):
 def row(self):return ['F']+['0']*270
 def test_matrix_and_domain(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),1456)
  for _,c in rows:self.assertEqual(len(d.parse(c)),12)
  for c in ('',d.command(kind=2),d.command(op=6),d.command(pattern=4),d.command(hot=5),d.command(count=2**31),d.command(query=2**31),d.command(allocation=3),d.command(mutation=10),d.command(repeats=0),d.command(kind=1,op=1),d.command(kind=0,op=2),d.command(op=3,count=-1,sorted=0)):
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
   for change in (lambda e:e['evidence'].update(complete_index_construct_append_growth_lookup=False),lambda e:e['evidence'].update(production_scheduling=True),lambda e:e['commands'].pop(),lambda e:e['evidence']['identities'].update(original={})):
    altered=copy.deepcopy(receipt);change(altered)
    with self.assertRaises((ValueError,KeyError)):d.validate(altered,{},'hash',current)
if __name__=='__main__':unittest.main()
