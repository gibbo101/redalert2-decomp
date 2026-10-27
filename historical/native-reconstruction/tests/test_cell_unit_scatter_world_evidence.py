# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_cell_unit_scatter_world import command,parse,defaults,validate,FLAGS,SOURCES,source_closure
from compare_original import PATCHED_EXPECTED
from verify_cell_unit_scatter_world import verify
class CellUnitScatterEvidence(unittest.TestCase):
 def fixture(self):
  identity=dict(sources={'a':'b'},inspection={'c':'d'},direction_data_sha256='data',render_data_sha256='render')
  proof=dict(FLAGS,identities=identity,evidence_mode='fresh-original',native_sha256='runner')
  e=dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[command()],expected=[['state','actor','actor','actor','actor']],labels=['fixture'],evidence=proof)
  return e,dict(proof,expectations_sha256='fingerprint'),copy.deepcopy(identity)
 def test_roundtrip_distinct_actors_and_rebuilt_runner(self):
  self.assertEqual(parse(command()),defaults());e,r,i=self.fixture();validate(e,r,'fingerprint',i)
  self.assertNotEqual(defaults()['queue'],defaults()['secondary'][0]['queue'])
 def test_identity_inputs_and_receipt_cannot_be_relabelled(self):
  for key in ('sources','inspection','direction_data_sha256','render_data_sha256'):
   e,r,i=self.fixture();i[key]='wrong'
   with self.subTest(key=key),self.assertRaises(ValueError):validate(e,r,'fingerprint',i)
  e,r,i=self.fixture()
  with self.assertRaises(ValueError):validate(e,r,'wrong',i)
 def test_scope_flags_cannot_be_promoted(self):
  for k,v in FLAGS.items():
   e,r,i=self.fixture();e['evidence'][k]=r[k]=not v
   with self.subTest(k=k),self.assertRaises(ValueError):validate(e,r,'fingerprint',i)
 def test_exact_binary(self):
  with self.assertRaises(ValueError):verify(b'wrong')
 def test_malformed_and_out_of_domain(self):
  for cmd in ('','J','X',command()+' 1',command(growth=[]),command(cell=10),command(track=[64]*5),command(eligibility=[256]*5)):
   with self.subTest(cmd=cmd[:35]),self.assertRaises(ValueError):parse(cmd)
 def test_Building_member_and_mirrored_invalid_records_refused(self):
  c=defaults();c['objects'][1][0]=6
  with self.assertRaises(ValueError):parse(command(**c))
  c=defaults();c['secondary'][0]['owned']=1;c['secondary'][0]['buffer']=1
  with self.assertRaises(ValueError):parse(command(**c))
 def test_actor_and_state_output_shape_retained(self):
  for row in (['state'],['actor']*4,['state','state',*(['actor']*4)],['state',0,*(['actor']*4)]):
   e,r,i=self.fixture();e['expected']=[row]
   with self.subTest(row=row),self.assertRaises(ValueError):validate(e,r,'fingerprint',i)
 def test_complete_source_closure(self):self.assertTrue(set(source_closure())<=set(SOURCES))
if __name__=='__main__':unittest.main()
