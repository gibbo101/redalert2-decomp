# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_nearby_location import command,parse,validate,FLAGS,SOURCES,source_closure
from compare_original import PATCHED_EXPECTED
from verify_nearby_location import verify
class NearbyLocationEvidence(unittest.TestCase):
 def fixture(self):
  current=dict(sources={'one':'two'},inspection={'three':'four'},render_data_sha256='data')
  proof=dict(FLAGS,identities=current,evidence_mode='fresh-original',native_sha256='old runner')
  e=dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[command()],expected=[['state','0']],labels=['fixture'],evidence=proof)
  return e,dict(proof,expectations_sha256='fingerprint'),copy.deepcopy(current)
 def test_rebuilt_runner_replays_original_identity(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_binary_source_inspection_and_data_identity_required(self):
  for key in ('sources','inspection','render_data_sha256'):
   e,r,c=self.fixture();c[key]='changed'
   with self.subTest(key=key),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
  for key in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[key]='wrong'
   with self.subTest(key=key),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):validate(e,r,'wrong',c)
 def test_scope_cannot_promote_supplied_services_to_runtime_or_original_callers(self):
  for k,v in FLAGS.items():
   e,r,c=self.fixture();e['evidence'][k]=r[k]=not v
   with self.subTest(k=k),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_exact_executable_gate_precedes_PE_parsing(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
 def test_raw_dword_and_signed_inputs_preserved(self):
  c=parse(command(source=[-32768,32767],zone=65535,alternate=0x80000001,frame=-2147483648))
  self.assertEqual((c['source'],c['zone'],c['alternate'],c['frame']),([-32768,32767],65535,0x80000001,-2147483648))
 def test_malformed_fields_counts_and_noncanonical_fallback_refused(self):
  for cmd in ('','X','N 0',command()+' trailing',command(source=[32768,0]),command(alternate=-1),command(mode=4),command(cells=[]),command(cells=[[-1,0,0,0,0,1,1,1,1]]*2),command(match=256)):
   with self.subTest(cmd=cmd[:40]),self.assertRaises(ValueError):parse(cmd)
 def test_output_shape_and_counts_required(self):
  for field,value in (('expected',[['0']]),('expected',[['state','state']]),('expected',[['state',0]]),('labels',[])):
   e,r,c=self.fixture();e[field]=value
   with self.subTest(field=field),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_transitive_native_sources_are_pinned_and_unwired(self):
  self.assertTrue(set(source_closure()).issubset(SOURCES))
  self.assertIn('src/sim/NearbyLocation.cpp',SOURCES)
  self.assertNotIn('src/platform/SDLApp.cpp',SOURCES)
if __name__=='__main__':unittest.main()
