# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_ground_drive_gate_process import command,parse,validate,HEADER,OBJECTS,HOUSES
import test_movement_gate_evidence as gate
from verify_ground_drive_gate_process import verify
class GroundDriveGateProcessEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=gate.MovementGateEvidenceGuards().fixture();e['commands']=[command()];return e,r,c
 def test_current_runner_can_replay(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_sources_and_original_inspection_must_match(self):
  for key in ('sources','inspection'):
   e,r,c=self.fixture();c[key]='changed'
   with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
 def test_engine_profile_counts_and_fingerprint_pinned(self):
  for key in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[key]='changed'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
  e['expected']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
 def test_unsupported_commands_refused(self):
  bad=['','G 0',command()+' trailing',command(steps=1,updates=[(1,1,0,1)]),command(updates=[(0,0,0,1)]),command(route=(2,-1,2))]
  objects=copy.deepcopy(OBJECTS[1:]);objects[0][1]=0;bad.append(command(objects=objects))
  objects=copy.deepcopy(OBJECTS[1:]);objects[0][2]=-1;bad.append(command(objects=objects))
  h=HEADER.copy();h[3]=h[2];bad.append(command(h=h))
  h=HEADER.copy();h[7]=-1;bad.append(command(h=h))
  for cmd in bad:
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_raw_bytes_signed_House_and_multiple_same_tick_transitions_preserved(self):
  h=HEADER.copy();h[0]=-2147483648;houses=copy.deepcopy(HOUSES);houses[0]=[-33,0xffffffff]
  values=parse(command(h=h,houses=houses,tick=2147483647,updates=[(0,1,128,255),(0,1,0,1)]))
  self.assertEqual(values[0][5],2147483647);self.assertEqual(values[5][0],-2147483648)
  self.assertEqual(values[6][0],[-33,0xffffffff]);self.assertEqual(values[-1],[[0,1,128,255],[0,1,0,1]])
 def test_old_Terrain_tag_and_different_resident_Unit_scope_refused(self):
  for kind in (21,1):
   objects=copy.deepcopy(OBJECTS[1:]);objects[3][0]=kind
   with self.assertRaisesRegex(ValueError,'command'):parse(command(objects=objects))
 def test_exact_binary_required(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
