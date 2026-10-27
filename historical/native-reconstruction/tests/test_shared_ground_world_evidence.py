# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_shared_ground_world import parse,validate,floor
import test_ground_unit_world_evidence as base
from verify_shared_ground_world import verify
class SharedGroundWorldEvidence(unittest.TestCase):
 def fixture(self):
  e,r,c=base.GroundUnitWorldEvidenceGuards().fixture()
  p=e['commands'][0];s='S 0 1664 1664 0 0 8192 14336 2 1 0 0 7 3 3 0 0'
  d='D 1 '+' '.join(map(str,[floor.bits(.125),0,0,0,1,0,7,1,0,1312,0,0,0,80,72,0,0,160,144]))
  e['commands']=[p,'O 0 31',s,s.replace('S 0','S 1'),d];e['labels']=['fixture']*5;e['expected']=[['ok']]*5
  for k in ('same_guest_distinct_actors_prepared_map_world_and_shadow','world_not_reset_between_actors'):e['evidence'][k]=r[k]=True
  return e,r,c
 def test_distinct_actors_accepted(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c);self.assertEqual(parse(e['commands'][-1])[1][0],1)
 def test_both_actors_required(self):
  for at in (2,3):
   e,r,c=self.fixture()
   for key in ('commands','labels','expected'):del e[key][at]
   with self.assertRaisesRegex(ValueError,'Both'):validate(e,r,'fingerprint',c)
 def test_new_map_invalidates_reset_and_actors(self):
  e,r,c=self.fixture()
  for key in ('commands','labels','expected'):e[key].insert(4,copy.deepcopy(e[key][0]))
  with self.assertRaisesRegex(ValueError,'Both'):validate(e,r,'fingerprint',c)
 def test_reset_invalidates_actors(self):
  e,r,c=self.fixture()
  for key in ('commands','labels','expected'):e[key].insert(4,copy.deepcopy(e[key][1]))
  with self.assertRaisesRegex(ValueError,'Both'):validate(e,r,'fingerprint',c)
 def test_identity_receipt_counts_and_join(self):
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'changed',c)
  c['changed']='source'
  with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture();e['labels']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture();e['evidence']['world_not_reset_between_actors']=r['world_not_reset_between_actors']=False
  with self.assertRaisesRegex(ValueError,'join'):validate(e,r,'fingerprint',c)
 def test_bad_actor_and_draw_commands(self):
  e,_,_=self.fixture()
  for cmd in ('','S 0','D 1','S 2'+e['commands'][2][3:],e['commands'][-1].replace('D 1','D 2'),e['commands'][-1]+' 0'):
   with self.subTest(cmd=cmd),self.assertRaises((AssertionError,ValueError)):parse(cmd)
 def test_exact_engine_required(self):
  with self.assertRaises(ValueError):verify(b'',b'unsupported')
if __name__=='__main__':unittest.main()
