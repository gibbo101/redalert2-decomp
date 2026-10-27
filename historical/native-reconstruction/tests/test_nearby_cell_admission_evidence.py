# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_nearby_cell_admission import command,parse,validate,FLAGS,SOURCES,source_closure
from compare_original import PATCHED_EXPECTED
from verify_nearby_cell_admission import verify
class NearbyCellAdmissionEvidence(unittest.TestCase):
 def fixture(self):
  current=dict(sources={'one':'two'},inspection={'three':'four'})
  proof=dict(FLAGS,identities=current,evidence_mode='fresh-original',native_sha256='old runner')
  e=dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[command()],expected=[['state','0']],labels=['fixture'],evidence=proof)
  return e,dict(proof,expectations_sha256='fingerprint'),copy.deepcopy(current)
 def test_rebuilt_runner_replays_original_identity(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_source_and_binary_identity_required(self):
  for k in ('sources','inspection'):
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
 def test_raw_byte_and_dword_arguments(self):
  c=parse(command(zone=65535,alternate=0x80000001,ignore_low=128))
  self.assertEqual((c['zone'],c['alternate'],c['ignore_low']),(65535,0x80000001,128))
 def test_malformed_input_refused(self):
  for cmd in ('','A 0',command()+' trailing',command(cells=[]),command(alternate=-1),command(mode=4),command(ignore_low=256),command(cells=[[-1,0,0,0,0,0,0,0,0,-1]]*2),command(width=9,op=1)):
   with self.subTest(cmd=cmd[:50]),self.assertRaises(ValueError):parse(cmd)
 def test_output_shape_required(self):
  for field,value in (('expected',[['0']]),('expected',[['state','state']]),('expected',[['state',0]]),('labels',[])):
   e,r,c=self.fixture();e[field]=value
   with self.subTest(field=field),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_borrowed_dependency_is_unwired_and_pinned(self):
  self.assertTrue(set(source_closure()).issubset(SOURCES));self.assertIn('src/assets/NearbyCellAdmission.hpp',SOURCES);self.assertNotIn('src/platform/SDLApp.cpp',SOURCES)
if __name__=='__main__':unittest.main()
