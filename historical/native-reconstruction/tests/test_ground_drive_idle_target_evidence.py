# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_ground_drive_idle_target import command,parse,validate,FLAGS,SOURCES,source_closure
from compare_original import PATCHED_EXPECTED
from verify_ground_drive_idle_target import verify

class GroundDriveIdleTargetEvidence(unittest.TestCase):
 def fixture(self):
  current=dict(sources={'one':'two'},inspection={'three':'four'})
  p=dict(FLAGS,identities=current,evidence_mode='fresh-original',native_sha256='old runner')
  e=dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[command()],
   expected=[['flow','return-false','state','retained']],labels=['fixture'],evidence=p)
  return e,dict(p,expectations_sha256='fingerprint'),copy.deepcopy(current)
 def test_binary_and_interior_scope_guards(self):
  with self.assertRaises(ValueError):verify(b'unsupported')
  for cmd in ('','X',command()+' 7',command(track=2,driving=1),command(driving=2),command(effect=256),
   command(kinds=(2,11)),command(actions=[[1,1,1,100,0]]),command(actions=[[0,0,1,100,0]]),
   command(actions=[[1,0,0,100,0]]),command(mission=7),command(queued=16)):
   with self.subTest(cmd=cmd[:40]),self.assertRaises(ValueError):parse(cmd)
 def test_rebuilt_runner_retains_original_identity(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_source_inspection_and_receipt_cannot_be_relabelled(self):
  for key in ('sources','inspection'):
   e,r,c=self.fixture();c[key]='changed'
   with self.subTest(key=key),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):validate(e,r,'wrong',c)
 def test_cannot_promote_interior_to_Process_world_or_runtime(self):
  for key,value in FLAGS.items():
   e,r,c=self.fixture();e['evidence'][key]=r[key]=not value
   with self.subTest(key=key),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_projection_requires_flow_for_every_action(self):
  for row in (['state','retained'],['flow','continue','flow','return-false','state','retained'],['flow','continue','state',0]):
   e,r,c=self.fixture();e['expected']=[row]
   with self.subTest(row=row),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_transitive_native_and_parent_oracle_sources_pinned(self):
  self.assertTrue(set(source_closure())<=set(SOURCES))
  for path in ('src/sim/GroundDriveIdleTarget.hpp','src/sim/UnitDestination.hpp','tests/original_unit_destination.py','tests/compare_unit_destination.py','tools/verify_unit_destination.py'):
   self.assertIn(path,SOURCES)
 def test_signed_words_raw_mission_and_queue_tails_retained(self):
  c=parse(command(mission=-1,queued=5,count=-2147483648,position=[-2147483648,2147483647,900],
   queue=list(range(24)),actions=[[1,0,1,-2147483648,2147483647]]))
  self.assertEqual(c['mission'],-1);self.assertEqual(c['queued'],5);self.assertEqual(c['count'],-2147483648)
  self.assertEqual(c['queue'],list(range(24)));self.assertEqual(c['actions'][0][3],-2147483648)

if __name__=='__main__':unittest.main()
