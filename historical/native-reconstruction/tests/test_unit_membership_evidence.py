# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as base
from compare_unit_membership import command,row,parse,validate,HEADER,RECORDS
from verify_unit_membership import verify
class UnitMembershipEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.VoxelPartEvidenceGuards().fixture();e['commands']=[command()];return e,r,c
 def test_current_runner_can_replay(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_source_and_inspection_change_refused(self):
  for key in ('sources','inspection'):
   e,r,c=self.fixture();c[key]='changed'
   with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
 def test_wrong_engine_profile_receipt_and_counts_refused(self):
  for key in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[key]='changed'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
  e['expected']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
 def test_malformed_or_unsupported_commands_refused(self):
  for cmd in ('','bad','U 0',command(header=[256,*HEADER[1:]]),command(header=[-1,*HEADER[1:]]),
   command([row(root=5)]),command([row(actor=1)]),command([row(cell=4)]),command([row(alt=256)]),
   command([row(eligible=-1)]),command([row(x=2147483648)]),command([row(root=2,x=-256,y=0)]),
   command(links=[4,-1,-1,-1]),command(planes=[0]*99+[0x7ff0000000000000]),command(rows=[]),command()+' trailing'):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_word_map_domain_differs_from_full_occupation_coordinates(self):
  h,records,links,planes,rows=parse(command([row(root=2,x=16777216+51*256+128)]))
  self.assertGreater(rows[0][4],16777216)
  # Combined slot remains valid despite a negative individual word coordinate.
  parse(command([row(root=2,x=-256,y=256)]))
  # Type-disabled and null-actor gates never reach the speculative slot read.
  parse(command([row(root=2,x=-256,y=0)],header=[0,0,0,*HEADER[3:]]))
  parse(command([row(root=2,x=-256,y=0,actor=-1)]))
 def test_row_limit_and_unsigned_occupation_fields(self):
  self.assertEqual(len(parse(command([row()]*128))[-1]),128)
  with self.assertRaises(AssertionError):parse(command([row()]*129))
  records=[r.copy() for r in RECORDS];records[0][3]=0xffffffff
  self.assertEqual(parse(command(records=records))[1][0][3],0xffffffff)
 def test_exact_engine_required(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
