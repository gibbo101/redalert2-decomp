# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import verify_walk_update_position_schedule as schedule
class WalkUpdatePositionScheduleEvidence(unittest.TestCase):
 def test_pinned_boundaries(self):
  self.assertEqual(schedule.DISPATCH,0x71f196)
  self.assertEqual(schedule.UPDATE_POSITION,0x500aa0)
  self.assertLess(schedule.ARRIVAL_START,schedule.DISPATCH)
  self.assertGreater(schedule.ARRIVAL_END,schedule.DISPATCH)
 def test_wrong_engine_refused(self):
  with self.assertRaises(ValueError):schedule.verify(b'wrong executable')
if __name__=='__main__':unittest.main()
