# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_foot_layer import command,parse,validate,FLAGS,SOURCES,source_closure
from compare_original import PATCHED_EXPECTED
from verify_foot_layer import verify
class FootLayerEvidence(unittest.TestCase):
 def fixture(self):
  current=dict(sources={'one':'two'},inspection={'three':'four'})
  p=dict(FLAGS,identities=current,evidence_mode='fresh-original',native_sha256='old runner')
  e=dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[command()],expected=[['state','0']],labels=['fixture'],evidence=p)
  return e,dict(p,expectations_sha256='fingerprint'),copy.deepcopy(current)
 def test_rebuilt_runner_retains_original_identity(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_binary_input_and_scope_guards(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
  for cmd in ('','X',command()+' 7',command(index=-129),command(poolx=32768),command(framp=21),command(actions=[]),command(actions=[[2,0,0,104,104,-1]]),command(cells=[[0,0,0,0],[0,1,0,256]])):
   with self.subTest(cmd=cmd[:40]),self.assertRaises(ValueError):parse(cmd)
 def test_receipt_and_sources_cannot_be_relabelled(self):
  for k in ('sources','inspection'):
   e,r,c=self.fixture();c[k]='different'
   with self.subTest(k=k),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):validate(e,r,'wrong',c)
 def test_cannot_promote_to_Scatter_world_or_runtime(self):
  for k,v in FLAGS.items():
   e,r,c=self.fixture();e['evidence'][k]=r[k]=not v
   with self.subTest(k=k),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_all_linked_quoted_native_sources_covered(self):self.assertTrue(set(source_closure())<=set(SOURCES))
 def test_raw_bridge_signed_flag_extremes_and_global_separation(self):
  c=parse(command(index=-128,poolx=-32768,actions=[[0,-2147483648,255,-2147483648,2147483647,128]]))
  self.assertEqual(c['actions'][0],[0,-2147483648,255,-2147483648,2147483647,128])
 def test_projection_shape_guard(self):
  for key,value in (('expected',[['0']]),('expected',[['state',0]]),('labels',[])):
   e,r,c=self.fixture();e[key]=value
   with self.subTest(key=key),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
if __name__=='__main__':unittest.main()
