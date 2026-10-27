# SPDX-License-Identifier: GPL-3.0-or-later
import copy,re,unittest
from compare_original import PATCHED_EXPECTED
from compare_ground_drive_resident_process import command,parse,validate,SOURCES
from compare_ground_drive_process import parse as legacy_parse,command as legacy_command
from presentation_evidence import ROOT
from verify_ground_drive_resident_process import verify
class ResidentProcessEvidenceGuards(unittest.TestCase):
 def fixture(self):
  current={'sources':{'kernel':'one'},'inspection':{'range':'two'}};proof={'evidence_mode':'fresh-original','identities':current}
  e={'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':[command()],'expected':[['0']],'labels':['fixture'],'evidence':proof}
  return e,{**proof,'expectations_sha256':'fingerprint'},copy.deepcopy(current)
 def test_rebuilt_runner_allowed_with_unchanged_sources(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_changed_sources_or_inspection_refused(self):
  for k in ('sources','inspection'):
   e,r,c=self.fixture();c[k]='changed'
   with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
 def test_counts_profile_engine_and_receipt(self):
  for k in ('profile','executable_sha256'):
   e,r,c=self.fixture();e[k]='wrong'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
  e['labels']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
 def test_retained_tail_is_preserved(self):
  route=[2,-1,4,5,*[-1]*20];self.assertEqual(parse(command(route=route))[2],route)
 def test_bad_commands(self):
  for cmd in ('','R 0',command()+' trailing',command(crusher=256),command(route=(2,-1,8)),command(steps=2,updates=[(2,1,0,1)])):
   with self.assertRaises((ValueError,AssertionError)):parse(cmd)
 def test_legacy_queue_domain_stays_canonical(self):
  with self.assertRaises(AssertionError):legacy_parse(legacy_command(route=(2,-1,4)))
 def test_transitive_native_headers_are_fingerprinted(self):
  pending=['src/sim/GroundDriveProcess.cpp','src/sim/UnitAdmission.cpp','src/sim/UnitNextCell.cpp','tests/ground_drive_process_vectors.cpp'];seen=set()
  while pending:
   path=pending.pop()
   if path in seen:continue
   seen.add(path);self.assertIn(path,SOURCES)
   for name in re.findall(r'^#include "([^"]+)"',(ROOT/path).read_text(),re.M):
    candidate=ROOT/path.rsplit('/',1)[0]/name
    pending.append(str(candidate.relative_to(ROOT)) if candidate.exists() else 'src/'+name)
 def test_legacy_admission_still_refuses_Unit_residents(self):
  from compare_ground_drive_admission_process import parse as old_parse
  p=command().split();p[169]='1'
  with self.assertRaises(ValueError):old_parse('A '+' '.join(p[1:-3]))
 def test_resident_kind_and_distinct_padding_preserved(self):
  p=command(first_padding=-2147483648,second_padding=2147483647).split();p[169]='1'
  result=parse(' '.join(p));self.assertEqual(result[7][0][0],1)
  self.assertEqual(result[-3:-1],(-2147483648,2147483647))
  p[169]='36'
  with self.assertRaises(ValueError):parse(' '.join(p))
 def test_exact_binary(self):
  with self.assertRaises(ValueError):verify(b'unsupported')
if __name__=='__main__':unittest.main()
