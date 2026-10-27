# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_cell_nearby_scatter import command,parse,defaults,validate,FLAGS,SOURCES,source_closure
from compare_original import PATCHED_EXPECTED
from verify_cell_nearby_scatter import verify
class CellNearbyEvidence(unittest.TestCase):
 def fixture(self):
  current=dict(sources={'one':'two'},inspection={'three':'four'},direction_data_sha256='direction',render_data_sha256='render')
  meta=dict(FLAGS,identities=current,evidence_mode='fresh-original',native_sha256='old runner')
  e=dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[command()],expected=[['state',*['actor']*4]],labels=['fixture'],evidence=meta)
  return e,dict(meta,expectations_sha256='fingerprint'),copy.deepcopy(current)
 def test_complete_zero_entry_roundtrip(self):
  self.assertEqual(parse(command()),defaults());e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_mixed_zero_nonzero_points_preserved(self):
  actions=[[0,0,0,1,1,100],[1,2,3,1,1,101]];self.assertEqual(parse(command(actions=actions))['actions'],actions)
 def test_domain_and_binary_guards(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'other')
  for kw in ({'speed_types':[9]*5},{'type_indexes':[5]*5},{'fp_mode':4},{'dimension1':2147483648},{'actions':[[0,0,0,0,0,-1]]},{'nearby_speeds':[0]*108}):
   with self.subTest(kw=kw),self.assertRaises(ValueError):parse(command(**kw))
 def test_shared_type_fields_cannot_disagree(self):
  objects=defaults()['objects'];objects[1][10]=1
  with self.assertRaises(ValueError):parse(command(objects=objects,type_indexes=[0,0,2,3,4]))
 def test_scope_and_identity_guards(self):
  for key,value in FLAGS.items():
   e,r,c=self.fixture();e['evidence'][key]=r[key]=not value
   with self.subTest(key=key),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
  for key in ('sources','inspection','direction_data_sha256','render_data_sha256'):
   e,r,c=self.fixture();c[key]='changed'
   with self.subTest(key=key),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_source_and_result_guards(self):
  self.assertTrue(set(source_closure())<=set(SOURCES))
  e,r,c=self.fixture();e['expected']=[['state']]
  with self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
if __name__=='__main__':unittest.main()
