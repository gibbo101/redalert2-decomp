# SPDX-License-Identifier: GPL-3.0-or-later
import copy,re,unittest
from compare_original import PATCHED_EXPECTED
from compare_owned_unit_admission import command,parse,validate,SOURCES,blocked_trace_samples
from presentation_evidence import ROOT
from verify_owned_unit_admission import verify
class OwnedAdmissionEvidenceGuards(unittest.TestCase):
 def fixture(self):
  current={'sources':'fingerprint'};proof={'evidence_mode':'fresh-original','identities':current}
  e={'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':[command()],'expected':[['0']],'labels':['movement'],'evidence':proof}
  return e,{**proof,'expectations_sha256':'receipt'},copy.deepcopy(current)
 def test_prepared_map_required(self):
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'prepared map'):validate(e,r,'receipt',c)
 def test_retained_route_and_raw_crusher(self):
  _,(_,route,_,crusher)=parse(command(route=(2,-1,4,5),crusher=255))
  self.assertEqual(route[:4],[2,-1,4,5]);self.assertEqual(crusher,255)
 def test_bad_commands(self):
  for cmd in ('','A 0',command()+' trailing',command(crusher=256),command(route=(2,-1,8))):
   with self.assertRaises((ValueError,AssertionError)):parse(cmd)
 def test_profile_receipt_and_source_guards(self):
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
  e['profile']='wrong'
  with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'receipt',c)
  e,r,c=self.fixture();c['sources']='changed'
  with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'receipt',c)
 def test_native_header_closure(self):
  pending=['src/assets/PreparedUnitAdmission.cpp','src/platform/TerrainUnitContext.cpp','tests/runtime_membership_vectors.cpp'];seen=set()
  while pending:
   path=pending.pop()
   if path in seen:continue
   seen.add(path);self.assertIn(path,SOURCES)
   for name in re.findall(r'^#include "([^"]+)"',(ROOT/path).read_text(),re.M):
    candidate=ROOT/path.rsplit('/',1)[0]/name
    pending.append(str(candidate.relative_to(ROOT)) if candidate.exists() else 'src/'+name)
 def test_exact_binary(self):
  with self.assertRaises(ValueError):verify(b'unsupported')
 def test_blocked_coverage_requires_actual_state_and_return(self):
  with self.assertRaises(ValueError):blocked_trace_samples(['a','d','7','0','0'])
  state=[0]*57;state[1:4]=[18816,10624,832];state[33:36]=[-1,4,5];state[56]=-1
  row=['S',*map(str,state)]*32
  with self.assertRaisesRegex(ValueError,'result7'):blocked_trace_samples(row)
  row+=['a','d','7','0','0'];self.assertEqual(blocked_trace_samples(row),32)
  row[34]='2'
  with self.assertRaisesRegex(ValueError,'retained queue'):blocked_trace_samples(row)
if __name__=='__main__':unittest.main()
