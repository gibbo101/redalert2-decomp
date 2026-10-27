# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_original import PATCHED_EXPECTED
from compare_movement_gate import command,parse,validate,HEADER,HOUSES,OBJECTS
from verify_movement_gate import verify
class MovementGateEvidenceGuards(unittest.TestCase):
 def fixture(self):
  current={'sources':{'kernel':'one'},'inspection':{'range':'two'}}
  proof={'evidence_mode':'fresh-original','identities':current,'native_sha256':'historical runner'}
  evidence={'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
   'commands':[command()],'expected':[['0']],'labels':['fixture'],'evidence':proof}
  return evidence,{**proof,'expectations_sha256':'fingerprint'},copy.deepcopy(current)
 def test_unchanged_sources_allow_rebuilt_native_runner(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_changed_source_or_inspection_refused(self):
  for key in ('sources','inspection'):
   e,r,c=self.fixture();c[key]='changed'
   with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
 def test_changed_engine_profile_fingerprint_or_counts_refused(self):
  for key in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[key]='wrong'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
  e['expected']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
 def test_malformed_and_unsupported_commands_refused(self):
  bad=['','W 0','X',command()+' trailing',command(steps=[]),command(steps=[['G',0,0,0]]),
   command(steps=[['C',0,32768,0]]),command(steps=[['A',-1,0,0]]),command(steps=[['T',1,256,0]])]
  h=HEADER.copy();h[4]=h[3];bad.append(command(h=h))
  objects=copy.deepcopy(OBJECTS);objects[1][1]=0;bad.append(command(objects=objects))
  objects=copy.deepcopy(OBJECTS);objects[1][2]=-1;bad.append(command(objects=objects))
  for cmd in bad:
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_raw_animation_bytes_and_signed_House_indices_retained(self):
  objects=copy.deepcopy(OBJECTS);objects[1][7:9]=[128,255]
  houses=copy.deepcopy(HOUSES);houses[1]=[-33,0xffffffff]
  _,parsed_houses,parsed_objects,_=parse(command(houses=houses,objects=objects))
  self.assertEqual(parsed_houses[1],[-33,0xffffffff]);self.assertEqual(parsed_objects[1][7:9],[128,255])
 def test_shared_heads_and_null_mover_allowed_but_cycle_refused(self):
  h=HEADER.copy();h[5:8]=[1,1,1]
  parse(command(h=h,steps=[['C',-1,-32768,32767]]))
  objects=copy.deepcopy(OBJECTS);objects[0][1]=0
  with self.assertRaises(ValueError):parse(command(objects=objects))
 def test_supplied_transition_and_sequence_bound(self):
  parse(command(steps=[['T',1,0,1]]*128))
  with self.assertRaises(ValueError):parse(command(steps=[['T',1,0,1]]*129))
 def test_actual_Terrain_kind_36_and_old_provisional_21_refused(self):
  _,_,objects,_=parse(command())
  self.assertEqual(objects[4][0],36)
  objects[4][0]=21
  with self.assertRaisesRegex(ValueError,'command'):parse(command(objects=objects))
 def test_exact_binary_required(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
