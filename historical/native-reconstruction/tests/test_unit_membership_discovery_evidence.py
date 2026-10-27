# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as base
from compare_unit_membership_discovery import parse,validate,command,FIELDS
class JoinedUnitDiscoveryEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.VoxelPartEvidenceGuards().fixture();e['commands']=[command()];return e,r,c
 def test_current_runner_can_replay(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_changed_identity_and_receipt_refused(self):
  e,r,c=self.fixture();c['sources']='changed'
  with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
 def test_invalid_join_and_diagnostic_mutation_refused(self):
  for cmd in ('','J 0',command()+' trailing',command(fields=[*FIELDS[:10],2,*FIELDS[11:]]),command(header=[0,0,1,0,0,0,-1,128,0]),command(header=[0,0,1,0,0,0,0,128,1])):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_current_House_owner_and_upper_visibility_flags_are_distinct(self):
  f=FIELDS.copy();f[0]=0xffffffff;f[10]=1
  parsed=parse(command(fields=f,header=[0,0,1,-1,0,0,0,128,0]))
  self.assertEqual(parsed[0][0],0xffffffff);self.assertEqual(parsed[0][10],1);self.assertEqual(parsed[1][6],0)
if __name__=='__main__':unittest.main()
