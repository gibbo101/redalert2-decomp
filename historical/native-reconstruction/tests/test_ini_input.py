# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from unittest.mock import patch
import compare_ini_input as d
class IniInputEvidence(unittest.TestCase):
 def row(self):return ['F']+['0']*657
 def test_matrix_and_domain(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),306)
  for _,c in rows:self.assertEqual(len(d.parse(c)),11)
  for c in ('',d.command(eof=-1),d.command(mode=4),d.command(bufferSize=65),d.command(cursor=63,available=2),d.command(capacity=2**31),d.command(reads=0)):
   with self.assertRaises(ValueError):d.parse(c)
  with self.assertRaises(ValueError):d.verify(b'wrong binary')
 def test_rows(self):
  d.validate_row(self.row());d.validate_row(['3','24','0','0']+self.row())
  for row in ([],['F'],self.row()+['0'],['99','0','0','0']+self.row(),['1','-1','0','0']+self.row()):
   with self.assertRaises(ValueError):d.validate_row(row)
 def test_reuse_scope_and_native_identity_separation(self):
  rows=list(d.scenarios());current={'original':{'pin':'exact'},'native_sources':{'new':'hash'}}
  receipt=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence=dict(d.FLAGS,identities={'original':{'pin':'exact'},'native_sources':{'old':'hash'}},original_instructions_executed=True,original_instructions_modified=False),labels=[x[0] for x in rows],commands=[x[1] for x in rows],expected=[self.row() for _ in rows])
  with patch.object(d,'validate_receipt'):
   d.validate(receipt,{},'hash',current)
   for change in (lambda e:e['evidence'].update(actual_buffered_pipe_source_forwarding=False),lambda e:e['evidence'].update(production_scheduling=True),lambda e:e['commands'].pop(),lambda e:e['evidence']['identities'].update(original={})):
    altered=copy.deepcopy(receipt);change(altered)
    with self.assertRaises((ValueError,KeyError)):d.validate(altered,{},'hash',current)
if __name__=='__main__':unittest.main()
