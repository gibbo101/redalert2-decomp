# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_unit_scatter_world import command,parse,validate,FLAGS,SOURCES,source_closure,defaults
from compare_original import PATCHED_EXPECTED
from verify_unit_scatter_world import verify

class ScatterWorldEvidence(unittest.TestCase):
 def fixture(self):
  current=dict(sources={'one':'two'},inspection={'three':'four'},direction_data_sha256='data')
  p=dict(FLAGS,identities=current,evidence_mode='fresh-original',native_sha256='old runner')
  e=dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[command()],expected=[['state','0']],labels=['fixture'],evidence=p)
  return e,dict(p,expectations_sha256='fingerprint'),copy.deepcopy(current)
 def test_round_trip_and_rebuilt_runner(self):
  self.assertEqual(parse(command()),defaults())
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_input_and_binary_guards(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
  for cmd in ('','X',command()+' 7',command(registry=-129),command(poolx=32768),command(queued=16),command(actions=[]),command(actions=[[0,0,0,0,0,100]]),command(buffer=1,owned=1),command(references=0)):
   with self.subTest(cmd=cmd[:30]),self.assertRaises(ValueError):parse(cmd)
 def test_cell_guards(self):
  for index,value in ((0,262144),(3,128),(4,21),(6,12),(7,5),(13,1)):
   cells=defaults()['cells'];cells[0][index]=value
   with self.subTest(index=index),self.assertRaises(ValueError):parse(command(cells=cells))
 def test_moving_residents_and_cycles_refused(self):
  objects=defaults()['objects'];objects[1][13]=0
  with self.assertRaises(ValueError):parse(command(objects=objects))
  objects=defaults()['objects'];objects[1][1]=1
  with self.assertRaises(ValueError):parse(command(objects=objects))
 def test_scope_cannot_be_promoted(self):
  for k,v in FLAGS.items():
   e,r,c=self.fixture();e['evidence'][k]=r[k]=not v
   with self.subTest(k=k),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_sources_and_input_cannot_be_relabelled(self):
  for key in ('sources','inspection','direction_data_sha256'):
   e,r,c=self.fixture();c[key]='changed'
   with self.subTest(key=key),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):validate(e,r,'wrong',c)
 def test_projection_shape_guard(self):
  for key,value in (('expected',[['0']]),('expected',[['state',0]]),('labels',[])):
   e,r,c=self.fixture();e[key]=value
   with self.subTest(key=key),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_source_closure(self):self.assertTrue(set(source_closure())<=set(SOURCES))
 def test_direct_projection_is_distinct_from_Scatter(self):
  c=parse(command(projection=True,actions=[[-2147483648,2147483647,0,0,0,100]]))
  self.assertTrue(c['projection'])
  self.assertFalse(parse(command())['projection'])

if __name__=='__main__':unittest.main()
