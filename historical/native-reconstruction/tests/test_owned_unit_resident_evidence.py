# SPDX-License-Identifier: GPL-3.0-or-later
import copy,re,unittest
from compare_original import PATCHED_EXPECTED
from compare_owned_unit_resident import command,parse,validate,SOURCES
from presentation_evidence import ROOT
from verify_owned_unit_resident import verify
class OwnedResidentEvidenceGuards(unittest.TestCase):
 def fixture(self):
  from test_prepared_drive_state_evidence import PreparedDriveStateEvidenceGuards
  prepared,_,_=PreparedDriveStateEvidenceGuards().fixture()
  current={'sources':'one'};proof={'evidence_mode':'fresh-original','identities':current}
  e={'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':[prepared['commands'][0],command()],
   'expected':[['0'],['0']],'labels':['prepared','resident'],'evidence':proof}
  return e,{**proof,'expectations_sha256':'receipt'},copy.deepcopy(current)
 def test_valid_prepared_resident_receipt(self):
  e,r,c=self.fixture();validate(e,r,'receipt',c)
 def test_prepared_map_required(self):
  e,r,c=self.fixture()
  for key in ('commands','expected','labels'):e[key]=e[key][1:]
  with self.assertRaisesRegex(ValueError,'prepared map'):validate(e,r,'receipt',c)
 def test_retained_tail_and_distinct_signed_words(self):
  _,v=parse(command(route=(2,-1,4,5),first_padding=-2147483648,second_padding=2147483647,order=1))
  self.assertEqual(v[1][:4],[2,-1,4,5]);self.assertEqual(v[-3:],(-2147483648,2147483647,1))
 def test_bad_commands(self):
  for cmd in ('','R 0',command()+' trailing',command(order=2),command(parked_heading=65536),command(first_padding=2147483648),command(route=(2,-1,8))):
   with self.assertRaises((ValueError,AssertionError)):parse(cmd)
 def test_identity_and_receipt(self):
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
  c['sources']='changed'
  with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'receipt',c)
 def test_counts_profile_and_malformed_preparation(self):
  e,r,c=self.fixture();e['labels']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'receipt',c)
  e,r,c=self.fixture();e['profile']='wrong'
  with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'receipt',c)
  e,r,c=self.fixture();e['commands'][0]='P placeholder'
  with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'receipt',c)
 def test_native_header_closure(self):
  pending=['src/platform/TerrainUnitContext.cpp','src/assets/PreparedUnitAdmission.cpp','tests/runtime_membership_vectors.cpp'];seen=set()
  while pending:
   path=pending.pop()
   if path in seen:continue
   seen.add(path);self.assertIn(path,SOURCES)
   for name in re.findall(r'^#include "([^"]+)"',(ROOT/path).read_text(),re.M):
    p=ROOT/path.rsplit('/',1)[0]/name;pending.append(str(p.relative_to(ROOT)) if p.exists() else 'src/'+name)
 def test_exact_binary(self):
  with self.assertRaises(ValueError):verify(b'unsupported')
if __name__=='__main__':unittest.main()
