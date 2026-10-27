# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as base
from compare_unit_discovery import parse,validate,visibility,discovery,VRECORDS,DHEADER
from verify_unit_discovery import verify
class UnitDiscoveryEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.VoxelPartEvidenceGuards().fixture();e['commands']=[discovery()];return e,r,c
 def test_current_runner_can_replay(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_source_inspection_and_prepared_input_changes_refused(self):
  for key in ('sources','inspection','prepared_inputs'):
   e,r,c=self.fixture();c[key]='changed'
   with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
 def test_wrong_profile_counts_and_receipt_refused(self):
  for key in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[key]='changed'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
  e['expected']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
 def test_secondary_shortcut_precedes_division_domain(self):
  for divisor,z in ((0,0),(-1,-2147483648)):
   parse(visibility([1,divisor,1,-1,255,0,0,z]))
   for secondary,mode,override,h in ((0,1,1,255),(1,0,1,255),(1,1,0,255),(1,1,1,0)):
    with self.assertRaises(AssertionError):parse(visibility([secondary,divisor,mode,override,h,0,0,z]))
 def test_signed_word_coordinates_and_unsigned_flags_preserved(self):
  rec=[r.copy() for r in VRECORDS];rec[0][1:]=[-32768,32767,0xffffffff,0x80000000]
  kind,(h,r)=parse(visibility([0,104,0,0,0,-2147483648,2147483647,-1],rec))
  self.assertEqual(r[0][1:],rec[0][1:]);self.assertEqual(h[5:],[-2147483648,2147483647,-1])
  rec[1][0]=rec[0][0]
  with self.assertRaises(AssertionError):parse(visibility([0,104,0,0,0,0,0,0],rec))
 def test_malformed_and_unsupported_commands_refused(self):
  for cmd in ('','bad','S','S 4','S -1','S 0 1','H 0 256 0','Q 14 -1 256 15','V 0',discovery()+' trailing',discovery(discoverers=[]),discovery(discoverers=[2]),discovery([*DHEADER[:4],-1,*DHEADER[5:]])):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_discovery_sequence_bound(self):
  self.assertEqual(len(parse(discovery(discoverers=[0]*128))[1][-1]),128)
  with self.assertRaises(AssertionError):parse(discovery(discoverers=[0]*129))
 def test_exact_engine_required(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
