# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_owned_unit_world import parse,validate,resident
import test_shared_ground_world_evidence as base
from verify_owned_unit_world import verify
class OwnedWorldEvidence(unittest.TestCase):
 def fixture(self):
  e,r,c=base.SharedGroundWorldEvidence().fixture()
  init='I '+resident.command(steps=1,marked=0,effect=1,present=1,key=0,mode=0)[2:]+' 0 32768'
  e['commands']=[e['commands'][0],'O 0 0',init,'T 100',e['commands'][-1],'T 101']
  e['expected']=[['ok']]*6;e['labels']=['fixture']*6
  e['evidence']['same_guest_Process_interleaved_draws_Process']=r['same_guest_Process_interleaved_draws_Process']=True
  return e,r,c
 def test_complete_sequence(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_initialization_and_resets(self):
  for at in (0,1,2):
   e,r,c=self.fixture()
   for key in ('commands','expected','labels'):del e[key][at]
   with self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
  for cmd in ('O 0 0',self.fixture()[0]['commands'][0],self.fixture()[0]['commands'][2]):
   e,r,c=self.fixture()
   for key in ('commands','expected','labels'):e[key].insert(4,cmd if key=='commands' else ['fixture'])
   with self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_malformed_commands(self):
  init=self.fixture()[0]['commands'][2]
  for cmd in ('','T','T 2147483648','T 0 trailing','S 0','I 0',init+' 0',init[:-1]+'65536','O 1 0'):
   with self.subTest(cmd=cmd),self.assertRaises((ValueError,AssertionError)):parse(cmd)
 def test_identity_and_join(self):
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'changed',c)
  with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',{'changed':True})
  e['evidence']['same_guest_Process_interleaved_draws_Process']=r['same_guest_Process_interleaved_draws_Process']=False
  with self.assertRaisesRegex(ValueError,'join'):validate(e,r,'fingerprint',c)
 def test_unknown_binary_refused(self):
  with self.assertRaises(ValueError):verify(b'',b'unsupported')
if __name__=='__main__':unittest.main()
