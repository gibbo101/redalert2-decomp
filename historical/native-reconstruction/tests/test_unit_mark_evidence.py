# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as base
from compare_unit_mark import command,row,parse,validate
from verify_unit_mark import verify
class UnitMarkEvidenceGuards(unittest.TestCase):
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
  for cmd in ('','bad','M 0',command(root=3),command(present=-1),command(tacticalPresent=2),command(marked=256),
   command(redraw=-1),command(tactical=256),command(image=2147483648),command([row(x=-2147483649)]),
   command([row(limbo=256)]),command([row(special=-1)]),command([row(reset=-2)]),command(rows=[]),command()+' trailing'):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_full_signed_modes_and_byte_gates_preserved(self):
  h,r=parse(command([row(mode=-2147483648,limbo=255,special=128,reset=255)],image=2147483647,owner=-2147483648))
  self.assertEqual(h[2:4],[2147483647,-2147483648]);self.assertEqual(r[0][0],-2147483648);self.assertEqual(r[0][4:],[255,128,255])
 def test_row_limit_enforced(self):
  self.assertEqual(len(parse(command([row()]*128))[1]),128)
  with self.assertRaises(AssertionError):parse(command([row()]*129))
 def test_exact_engine_required(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
