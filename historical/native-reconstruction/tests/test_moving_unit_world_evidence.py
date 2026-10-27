# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from compare_moving_unit_world import parse,validate,movement,floor
from compare_original import PATCHED_EXPECTED
import test_ground_unit_world_evidence as base
from verify_moving_unit_world import verify
class MovingUnitEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.GroundUnitWorldEvidenceGuards().fixture()
  e['evidence']['same_guest_live_movement_and_complete_drawing']=True;r['same_guest_live_movement_and_complete_drawing']=True
  return e,r,c
 def test_rebuilt_runner_allowed(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_changed_source_or_inputs_refused(self):
  for key in ('height','movement','inspection','sources'):
   e,r,c=self.fixture();c[key]='changed'
   with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
 def test_missing_live_join_refused(self):
  e,r,c=self.fixture();e['evidence']['same_guest_live_movement_and_complete_drawing']=False;r['same_guest_live_movement_and_complete_drawing']=False
  with self.assertRaisesRegex(ValueError,'join'):validate(e,r,'fingerprint',c)
 def test_counts_and_receipt_refused(self):
  e,r,c=self.fixture();e['expected']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
 def test_actor_and_setup_required(self):
  for cmd in ('T 1',movement.command()):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'lacks'):validate(e,r,'fingerprint',c)
 def test_malformed_and_out_of_order_commands_refused(self):
  for cmd in ('','T','T 0','T 257','T 1 2','D 0','W 0','M bad'):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_actual_Unit_owns_seed(self):
  self.assertEqual(parse(movement.command())[0],'M')
  for kw in ({'key':17},{'present':0}):
   with self.assertRaises(AssertionError):parse(movement.command(**kw))
 def test_live_draw_has_no_supplied_body_or_location(self):
  v=[floor.bits(.125),31,0,0,0,8192,14336,1,0,7,1,0,1312,0,0,0,80,72,0,0,160,144]
  self.assertEqual(parse('D '+' '.join(map(str,v)))[1],v)
  with self.assertRaises(AssertionError):parse('D '+' '.join(map(str,[0,0,0,*v])))
 def test_wrong_executable_refused(self):
  with self.assertRaises(ValueError):verify(b'unsupported',b'unsupported')
if __name__=='__main__':unittest.main()
