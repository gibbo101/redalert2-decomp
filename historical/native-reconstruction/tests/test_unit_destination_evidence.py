# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_unit_destination import command,parse,validate,FLAGS,SOURCES,source_closure,bits
from compare_original import PATCHED_EXPECTED
from verify_unit_destination import verify
class UnitDestinationEvidence(unittest.TestCase):
 def fixture(self):
  current=dict(sources={'one':'two'},inspection={'three':'four'})
  p=dict(FLAGS,identities=current,evidence_mode='fresh-original',native_sha256='old runner')
  e=dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[command()],expected=[['state','0']],labels=['fixture'],evidence=p)
  return e,dict(p,expectations_sha256='fingerprint'),copy.deepcopy(current)
 def test_rebuilt_runner_retains_original_identity(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_binary_input_and_scope_guards(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
  for cmd in ('','X',command()+' 7',command(mission=7),command(queued=16),command(powered=0),command(field5c8=1),command(references=0),command(percentage_bits=bits(float('nan'))),command(actions=[]),command(actions=[[1,3,1,100,0]]),command(cells=[[1,2,0,21,0,1],[2,3,0,0,0,1]])):
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
 def test_raw_bytes_wrapped_timers_tails_and_coordinates(self):
  c=parse(command(powered=255,owned=128,global_references=0xffffffff,guard_start=2147483647,guard_remaining=-2147483648,actions=[[0,1,255,-2147483648,-31]]))
  self.assertEqual(c['powered'],255);self.assertEqual(c['queue'][2],-1);self.assertEqual(c['actions'][0][3],-2147483648)
 def test_projection_shape_guard(self):
  for key,value in (('expected',[['0']]),('expected',[['state',0]]),('labels',[])):
   e,r,c=self.fixture();e[key]=value
   with self.subTest(key=key),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
if __name__=='__main__':unittest.main()
