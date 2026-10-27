# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_unit_nearby_scatter import command,parse,defaults,validate,FLAGS,SOURCES,source_closure
from compare_original import PATCHED_EXPECTED
from verify_unit_nearby_scatter import verify
class UnitNearbyEvidence(unittest.TestCase):
 def fixture(self):
  current=dict(sources={'one':'two'},inspection={'three':'four'},direction_data_sha256='direction',render_data_sha256='render')
  meta=dict(FLAGS,identities=current,evidence_mode='fresh-original',native_sha256='old runner')
  e=dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[command()],expected=[['state','0']],labels=['fixture'],evidence=meta)
  return e,dict(meta,expectations_sha256='fingerprint'),copy.deepcopy(current)
 def test_actual_zero_entry_roundtrip(self):
  self.assertEqual(parse(command()),defaults());e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_nonzero_scatter_cannot_replace_zero_caller(self):
  with self.assertRaises(ValueError):parse(command(actions=[[1,0,0,1,1,100]]))
 def test_domain_and_binary_guards(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'other')
  for kw in ({'speed_type':9},{'speed_type':-1},{'fp_mode':4},{'dimension1':2147483648},{'actions':[[0,0,0,0,0,-1]]},{'projection':True}):
   with self.subTest(kw=kw),self.assertRaises(ValueError):parse(command(**kw))
 def test_scope_and_identity_guards(self):
  for key,value in FLAGS.items():
   e,r,c=self.fixture();e['evidence'][key]=r[key]=not value
   with self.subTest(key=key),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
  for key in ('sources','inspection','direction_data_sha256','render_data_sha256'):
   e,r,c=self.fixture();c[key]='changed'
   with self.subTest(key=key),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_expected_shape_and_receipt_guards(self):
  for key,value in (('commands',[]),('expected',[['0']]),('labels',[])):
   e,r,c=self.fixture();e[key]=value
   with self.subTest(key=key),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):validate(e,r,'wrong',c)
 def test_complete_source_closure(self):self.assertTrue(set(source_closure())<=set(SOURCES))
if __name__=='__main__':unittest.main()
