# SPDX-License-Identifier: GPL-3.0-or-later
import copy,re,unittest
from compare_advance_admission import command,parse,validate,SOURCES,safety_commands
from compare_moving_resident_process import parse as old_parse
from compare_original import PATCHED_EXPECTED
from presentation_evidence import ROOT
from verify_advance_admission import verify,DISPATCH,ASSOCIATIONS
class AdvanceAdmissionEvidenceGuards(unittest.TestCase):
 def fixture(self):
  c={'sources':{'adapter':'one'},'inspection':'two','direction_data':'three'}
  proof={'evidence_mode':'fresh-original','identities':c,'root':'0x4a1000','complete_Advance_actual_admission':True,'Process_executed':False}
  e={'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':[command()],
   'expected':[['0']],'labels':['fixture'],'evidence':proof}
  return e,{**proof,'expectations_sha256':'fingerprint'},copy.deepcopy(c)
 def test_replay_and_changed_input_guards(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
  for key in c:
   changed=copy.deepcopy(c);changed[key]='changed'
   with self.subTest(key=key),self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',changed)
 def test_receipt_binary_and_count_guards(self):
  for field in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[field]='wrong'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
  e['labels']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
 def test_Advance_cannot_be_relabelled_Process(self):
  for field,value in (('root','0x4a05f0'),('complete_Advance_actual_admission',False),('Process_executed',True)):
   e,r,c=self.fixture();e['evidence'][field]=r[field]=value
   with self.assertRaisesRegex(ValueError,'root/scope'):validate(e,r,'fingerprint',c)
 def test_retained_tail_suppression_and_protocol(self):
  parsed=parse(command(route=(4,-1,7,6),suppress=1));self.assertEqual(parsed[0][7],1)
  self.assertEqual(parsed[2][:4],[4,-1,7,6])
  with self.assertRaises((AssertionError,ValueError)):old_parse(command())
 def test_malformed_inputs_refused(self):
  for cmd in safety_commands():
   with self.subTest(command=cmd[:24]),self.assertRaises((ValueError,AssertionError)):parse(cmd)
 def test_switch_is_pinned_as_unsigned_and_result6_distinct(self):
  self.assertEqual(ASSOCIATIONS[0x4a1ca2],('ja','0x4a1f8d'))
  self.assertEqual(DISPATCH[0],DISPATCH[2]);self.assertEqual(DISPATCH[6],0x4a1f05)
  with self.assertRaises(ValueError):verify(b'unsupported')
 def test_transitive_native_source_closure(self):
  pending=['src/sim/GroundDriveAdvanceAdmission.hpp','tests/advance_admission_vectors.cpp'];seen=set()
  while pending:
   path=pending.pop()
   if path in seen:continue
   seen.add(path);self.assertIn(path,SOURCES)
   for name in re.findall(r'^#include "([^"]+)"',(ROOT/path).read_text(),re.M):
    local=(ROOT/path).parent/name
    pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
if __name__=='__main__':unittest.main()
