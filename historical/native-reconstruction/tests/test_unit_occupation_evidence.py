# SPDX-License-Identifier: GPL-3.0-or-later
import struct,unittest
import test_voxel_part_evidence as base
from compare_unit_occupation import command,row,parse,validate
from verify_unit_occupation import verify
class UnitOccupationEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.VoxelPartEvidenceGuards().fixture();e['commands']=[command()];return e,r,c
 def test_current_runner_can_replay(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_source_and_inspection_changes_refused(self):
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
  for cmd in ('','bad','U 0',command([row(op=2)]),command([row(x=2147483648)]),command([row(resident=4)]),
   command([row(ramp=21)]),command([row(otherRamp=-1)]),command([row(framp=21)]),command([row(flags=-1)]),
   command([row(fflags=1<<32)]),command([row(level=128)]),command([row(mutation=4)]),command(mode=4),
   command(initial=[-1]*6),command()+' trailing'):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_unsigned_fields_and_signed_threshold_preserved(self):
  r=parse(command([row(flags=0xffffffff,threshold=-2147483648,z=2147483647)]))[3][0]
  self.assertEqual((r[3],r[11],r[14]),(2147483647,0xffffffff,-2147483648))
 def test_nonfinite_plane_refused(self):
  planes=[0]*100;planes[7]=struct.unpack('<Q',struct.pack('<d',float('nan')))[0]
  with self.assertRaises(AssertionError):parse(command(planes=planes))
 def test_exact_engine_required(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
