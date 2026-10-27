# SPDX-License-Identifier: GPL-3.0-or-later
import struct,unittest
import test_voxel_part_evidence as base
from compare_actor_ground_state import command,parse,validate
from verify_actor_ground_state import verify
class ActorGroundStateEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.VoxelPartEvidenceGuards().fixture();e['commands']=[command()];return e,r,c
 def test_current_runner_can_replay(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_source_and_inspection_change_refused(self):
  for key in ('sources','inspection'):
   e,r,c=self.fixture();c[key]='changed'
   with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
 def test_wrong_engine_and_profile_refused(self):
  for key in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[key]='changed'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
 def test_fingerprint_and_counts_refused(self):
  e,r,c=self.fixture();e['expected']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
 def test_malformed_or_unsupported_command_refused(self):
  for cmd in ('','bad','G 0',command(op=6),command(x=2147483648),command(bridge=256),command(marked=-1),
   command(resident=2),command(level=128),command(op=0,ramp=21),command(op=5,framp=21),command(ramp=256),
   command(mutation=8),command(mode=4),command()+' trailing'):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_state_writer_byte_ramps_and_full_Force_input_are_preserved(self):
  self.assertEqual(parse(command(op=2,ramp=255))[0][11],255)
  self.assertEqual(parse(command(op=1,height=-2147483648))[0][2],-2147483648)
  self.assertEqual(parse(command(op=3,current=-1,start=-2147483648,duration=2147483647))[0][14],-1)
 def test_nonfinite_plane_refused(self):
  planes=[0]*100;planes[7]=struct.unpack('<Q',struct.pack('<d',float('nan')))[0]
  with self.assertRaises(AssertionError):parse(command(planes))
 def test_exact_engine_required(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
