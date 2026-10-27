# SPDX-License-Identifier: GPL-3.0-or-later
import copy,re,unittest
from compare_original import PATCHED_EXPECTED
from compare_moving_resident_process import command,parse,validate,SOURCES,MOTION,WAIT,safety_commands
from compare_ground_drive_resident_process import parse as old_parse,command as old_command
from presentation_evidence import ROOT
from verify_moving_resident_process import verify
class MovingResidentProcessEvidenceGuards(unittest.TestCase):
 def fixture(self):
  current={'sources':{'kernel':'one'},'inspection':{'range':'two'},'direction_data':'three'}
  proof={'evidence_mode':'fresh-original','identities':current,'complete_Process_and_actual_moving_children':True}
  e={'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':[command()],
   'expected':[['0']],'labels':['fixture'],'evidence':proof}
  return e,{**proof,'expectations_sha256':'fingerprint'},copy.deepcopy(current)
 def test_unchanged_sources_allow_rebuilt_runner(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_changed_sources_inspection_or_direction_data_refused(self):
  for key in ('sources','inspection','direction_data'):
   e,r,c=self.fixture();c[key]='changed'
   with self.subTest(key=key),self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
 def test_receipt_engine_profile_counts_and_join(self):
  for key in ('profile','executable_sha256'):
   e,r,c=self.fixture();e[key]='wrong'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
  e['labels']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture();e['evidence']['complete_Process_and_actual_moving_children']=r['complete_Process_and_actual_moving_children']=False
  with self.assertRaisesRegex(ValueError,'join'):validate(e,r,'fingerprint',c)
 def test_distinct_actors_wait_padding_and_retained_queue_tail(self):
  result=parse(command(route=(2,-1,4,5)))
  self.assertEqual(result[2][:4],[2,-1,4,5]);self.assertEqual(result[-2],MOTION);self.assertEqual(result[-1],WAIT)
  rows=copy.deepcopy(MOTION);rows[2][0]+=256
  self.assertNotEqual(parse(command(motion=rows))[-2][2][0],parse(command())[-2][2][0])
 def test_bad_protocol_and_ranges(self):
  for cmd in safety_commands()[:-2]:
   with self.subTest(cmd=cmd[:24]),self.assertRaises((ValueError,AssertionError)):parse(cmd)
  for cmd in (command()[:-2],old_command(),command(resident_flags=4),command(steps=2,updates=[(2,1,0,1)])):
   with self.subTest(cmd=cmd[:24]),self.assertRaises((ValueError,AssertionError)):parse(cmd)
 def test_old_protocol_remains_distinct(self):
  with self.assertRaises((ValueError,AssertionError)):old_parse(command())
 def test_unsupported_Advance_guards_are_valid_commands(self):
  for cmd in safety_commands()[-2:]:parse(cmd)
 def test_exact_binary(self):
  with self.assertRaises(ValueError):verify(b'unsupported')
 def test_transitive_native_headers_fingerprinted(self):
  pending=['src/sim/GroundDriveProcess.cpp','src/sim/MovingUnitAdmission.cpp','tests/ground_drive_process_vectors.cpp'];seen=set()
  while pending:
   path=pending.pop()
   if path in seen:continue
   seen.add(path);self.assertIn(path,SOURCES)
   for name in re.findall(r'^#include "([^"]+)"',(ROOT/path).read_text(),re.M):
    candidate=ROOT/path.rsplit('/',1)[0]/name
    pending.append(str(candidate.relative_to(ROOT)) if candidate.exists() else 'src/'+name)
if __name__=='__main__':unittest.main()
