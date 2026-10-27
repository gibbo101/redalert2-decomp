# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_original import PATCHED_EXPECTED
from compare_shared_unit_staging import parse,validate
from verify_shared_unit_staging import verify,OPERANDS
class SharedUnitStagingEvidence(unittest.TestCase):
 def fixture(self):
  current={'source':'one'};proof={'evidence_mode':'fresh-original','identities':current}
  commands=['O 0 3','S 0 0 8192 14336 2560 2816 0','S 1 32768 40960 15360 2816 2816 0','D 1 1 0 7 1 0 1000 0 0 0 30 40 0 0 256 256']
  e={'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,
   'labels':['fixture']*4,'expected':[['0']]*4,'evidence':proof}
  return e,{**proof,'expectations_sha256':'receipt'},copy.deepcopy(current)
 def test_distinct_actors_valid(self):
  e,r,c=self.fixture();validate(e,r,'receipt',c)
  self.assertEqual(parse(e['commands'][-1])[1][0],1)
 def test_reset_and_both_actors_required(self):
  for delete in (0,1,2):
   e,r,c=self.fixture()
   for key in ('commands','labels','expected'):del e[key][delete]
   with self.assertRaisesRegex(ValueError,'required'):validate(e,r,'receipt',c)
 def test_reset_invalidates_previous_actors(self):
  e,r,c=self.fixture();e['commands'].insert(3,'O 1 9');e['labels'].insert(3,'reset');e['expected'].insert(3,['reset'])
  with self.assertRaisesRegex(ValueError,'Both supplied actors'):validate(e,r,'receipt',c)
 def test_bad_commands(self):
  for cmd in ('','O','O 2 3','O 0 -1','S 2 0 0 0 0 0 0','S 0 65536 0 0 0 0 0','S 0 0 0 0 0 0 1','D 1',
   'D 2 1 0 7 1 0 1000 0 0 0 30 40 0 0 256 256','D 1 1 0 8 1 0 1000 0 0 0 30 40 0 0 256 256'):
   with self.subTest(cmd=cmd),self.assertRaises(ValueError):parse(cmd)
 def test_receipt_source_and_counts(self):
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
  c['source']='changed'
  with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'receipt',c)
  e,r,c=self.fixture();e['labels']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'receipt',c)
 def test_no_other_binary(self):
  with self.assertRaises(ValueError):verify(b'',b'unsupported')
 def test_association_operands_are_explicit(self):
  self.assertIn('0x5bb',OPERANDS[0x6ff76c][1]);self.assertIn('0x214',OPERANDS[0x6ff8bf][1])
if __name__=='__main__':unittest.main()
