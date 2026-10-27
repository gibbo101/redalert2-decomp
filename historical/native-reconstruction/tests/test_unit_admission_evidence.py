# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_original import PATCHED_EXPECTED
from compare_unit_admission import command,parse,validate,HEADER,CELLS,OBJECTS,STEP
from verify_unit_admission import verify
class UnitAdmissionEvidenceGuards(unittest.TestCase):
 def fixture(self):
  current={'sources':{'kernel':'one'},'inspection':{'range':'two'}}
  proof={'evidence_mode':'fresh-original','identities':current,'native_sha256':'historical runner'}
  e={'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
   'commands':[command()],'expected':[['0']],'labels':['fixture'],'evidence':proof}
  return e,{**proof,'expectations_sha256':'fingerprint'},copy.deepcopy(current)
 def test_rebuilt_runner_allowed_with_unchanged_sources(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_changed_sources_or_inspection_refused(self):
  for key in ('sources','inspection'):
   e,r,c=self.fixture();c[key]='changed'
   with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
 def test_engine_profile_fingerprint_and_counts_refused(self):
  for key in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[key]='wrong'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
  e['expected']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
 def test_malformed_and_unsupported_records_refused(self):
  bad=['','W 0','X',command()+' trailing',command(steps=[]),command(steps=[['U',1,0,2,0,-1,1,0]])]
  cells=copy.deepcopy(CELLS);cells[0][3]=128;bad.append(command(cells=cells))
  objects=copy.deepcopy(OBJECTS);objects[1][1]=1;bad.append(command(objects=objects))
  objects=copy.deepcopy(OBJECTS);objects[1][13]=0;bad.append(command(objects=objects))
  objects=copy.deepcopy(OBJECTS);objects[1][0]=36;bad.append(command(objects=objects))
  h=HEADER.copy();h[2]=h[1];bad.append(command(h=h))
  for cmd in bad:
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_exact_raw_speed_bits_occupation_and_outputs_preserved(self):
  cells=copy.deepcopy(CELLS);cells[0][6]=0xffffffff;cells[0][2]=-32768
  args=parse(command(cells=cells,speeds=[0x7f800001]*12,steps=[['T',0,0,-1,-2147483648,-1,255,128]]))
  self.assertEqual(args[2],[0x7f800001]*12);self.assertEqual(args[5][0][6],0xffffffff)
  self.assertEqual(args[-1][0][-1],128)
 def test_alias_heads_explicit_previous_and_sequence_limit(self):
  cells=copy.deepcopy(CELLS);cells[0][11:13]=[1,1]
  parse(command(cells=cells,steps=[['U',0,0,2,0,0,0,0]]*128))
  with self.assertRaises(ValueError):parse(command(steps=[STEP]*129))
 def test_exact_binary_required(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
