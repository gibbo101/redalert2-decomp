# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_nearby_location_map import command,parse,validate,FLAGS,SOURCES,source_closure
from compare_original import PATCHED_EXPECTED
from verify_nearby_location_map import verify
class NearbyLocationMapEvidence(unittest.TestCase):
 def fixture(self):
  current=dict(sources={'one':'two'},inspection={'three':'four'},render_data_sha256='data');proof=dict(FLAGS,identities=current,evidence_mode='fresh-original',native_sha256='old runner')
  e=dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[command()],expected=[['state','0']],labels=['fixture'],evidence=proof)
  return e,dict(proof,expectations_sha256='fingerprint'),copy.deepcopy(current)
 def test_rebuilt_runner_replays_original_identity(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_source_binary_and_data_identity_required(self):
  for k in ('sources','inspection','render_data_sha256'):
   e,r,c=self.fixture();c[k]='changed'
   with self.subTest(k=k),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):validate(e,r,'wrong',c)
 def test_scope_not_promoted(self):
  for k,v in FLAGS.items():
   e,r,c=self.fixture();e['evidence'][k]=r[k]=not v
   with self.subTest(k=k),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_exact_executable_before_parsing(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
 def test_raw_arguments_and_normalization_remain_separate(self):
  c=parse(command(zone=65535,alternate=0x80000001,skip=128));self.assertEqual((c['zone'],c['alternate'],c['skip']),(65535,0x80000001,128))
 def test_malformed_and_unjoined_inputs_refused(self):
  for cmd in ('','M 0',command()+' trailing',command(cells=[]),command(zone=0),command(alternate=-1),command(mode=4),command(skip=256),command(width=5)):
   with self.subTest(cmd=cmd[:50]),self.assertRaises(ValueError):parse(cmd)
 def test_output_shape_required(self):
  for field,value in (('expected',[['0']]),('expected',[['state','state']]),('expected',[['state',0]]),('labels',[])):
   e,r,c=self.fixture();e[field]=value
   with self.subTest(field=field),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_borrowed_join_and_numeric_policy_are_pinned(self):
  self.assertTrue(set(source_closure()).issubset(SOURCES))
  for p in ('src/assets/NearbyLocationMap.hpp','src/sim/NearbyLocationPolicy.hpp','src/assets/NearbyCellAdmission.hpp','src/assets/ScatterProjection.hpp'):self.assertIn(p,SOURCES)
  self.assertNotIn('src/platform/SDLApp.cpp',SOURCES)
if __name__=='__main__':unittest.main()
