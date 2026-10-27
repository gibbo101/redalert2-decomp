# SPDX-License-Identifier: GPL-3.0-or-later
import struct,unittest
import test_voxel_part_evidence as base
from compare_ground_movement_placement import command,parse,validate
from verify_ground_movement_placement import verify
class GroundMovementPlacementEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.VoxelPartEvidenceGuards().fixture();e['commands']=[command()];return e,r,c
 def test_current_runner_can_replay(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_changed_source_or_inspection_refused(self):
  for key in ('sources','inspection'):
   e,r,c=self.fixture();c[key]='changed'
   with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
 def test_changed_engine_or_profile_refused(self):
  for key in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[key]='changed'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
 def test_fingerprint_and_counts_refused(self):
  e,r,c=self.fixture();e['expected']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
 def test_unsupported_commands_refused(self):
  for cmd in ('','P 0',command(op=3),command(marked=-1),command(onmap=256),command(bridge=256),
   command(x=2147483648),command(nz=-2147483649),command(resident=2),command(ramp=21),command(fr=21),
   command(mutation=16),command(mode=4),command()+' trailing'):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_full_coordinates_and_nonzero_bytes_preserved(self):
  v,_=parse(command(x=-2147483648,nx=2147483647,onmap=255,marked=128,bridge=2,bh=-2147483648))
  self.assertEqual(v[1:6],[255,128,2,-2147483648,-2147483648]);self.assertEqual(v[8],2147483647)
 def test_nonfinite_plane_refused(self):
  planes=[0]*100;planes[19]=struct.unpack('<Q',struct.pack('<d',float('inf')))[0]
  with self.assertRaises(AssertionError):parse(command(planes))
 def test_exact_executable_required(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
