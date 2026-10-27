# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_unit_scatter import command,parse,validate,FLAGS,SOURCES,source_closure
from compare_original import PATCHED_EXPECTED
from verify_unit_scatter import verify
class UnitScatterEvidence(unittest.TestCase):
 def fixture(self):
  c=dict(sources={'one':'two'},inspection={'three':'four'},direction_data='five')
  p=dict(FLAGS,identities=c,evidence_mode='fresh-original',native_sha256='old runner')
  e=dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[command()],expected=[['state','0']],labels=['fixture'],evidence=p)
  return e,dict(p,expectations_sha256='fingerprint'),copy.deepcopy(c)
 def test_rebuilt_runner_and_canonical_identity(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_binary_and_input_guard(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
  for cmd in ('','X',command()+' 7',command(train=256),command(mission=32),command(references=0),command(bounds=[1]*7),command(neighbors=[(0,0)]*8),command(table=[0]*249)):
   with self.subTest(cmd=cmd[:40]),self.assertRaises(ValueError):parse(cmd)
 def test_source_and_prepared_data_receipt_identity(self):
  for k in ('sources','inspection','direction_data'):
   e,r,c=self.fixture();c[k]='different'
   with self.subTest(k=k),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):validate(e,r,'wrong',c)
 def test_cannot_promote_services_to_world_or_runtime(self):
  for k,v in FLAGS.items():
   e,r,c=self.fixture();e['evidence'][k]=r[k]=not v
   with self.subTest(k=k),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_all_linked_native_quoted_sources_covered(self):
  self.assertTrue(set(source_closure())<=set(SOURCES))
 def test_raw_bytes_wrapped_counter_and_nonzero_sentinel_preserved(self):
  c=parse(command(control9=255,ignore_destination=128,global_references=0xffffffff,empty_cell=[7,9],coordinates=[-257,-255,0]))
  self.assertEqual(c['control9'],255);self.assertEqual(c['global_references'],0xffffffff);self.assertEqual(c['coordinates'],[-257,-255,0])
 def test_projection_shape_guard(self):
  for key,value in (('expected',[['0']]),('expected',[['state',0]]),('labels',[])):
   e,r,c=self.fixture();e[key]=value
   with self.subTest(key=key),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
if __name__=='__main__':unittest.main()
