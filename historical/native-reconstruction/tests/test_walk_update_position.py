# SPDX-License-Identifier: GPL-3.0-or-later
import copy
import unittest
import compare_walk_update_position as joined

class JoinedWalkEvidenceTests(unittest.TestCase):
 def test_scenarios_cover_arrival_boundary_and_each_late_exit(self):
  cases=list(joined.scenarios());self.assertEqual(len(cases),48)
  parsed=[joined.parse(command) for _,command in cases]
  self.assertEqual({distance for distance,_,_ in parsed},{0,1,16})
  self.assertEqual({flags for _,flags,_ in parsed},{(1,0,0),(0,0,0),(1,255,0),(1,0,128)})
  self.assertEqual(sum(label=='ordinary_return' for label,_ in cases),12)
  self.assertTrue(all(f['fullPost'] and f['onMap'] for _,_,f in parsed))
 def test_invalid_head_and_flags_refused(self):
  _,command=next(joined.scenarios())
  for bad in ('17 '+command.split(' ',1)[1],command.replace('0 1 0 0 J','0 1 1 1 J'),command+' extra'):
   with self.assertRaises(ValueError):joined.parse(bad)
 def valid_row(self):
  return dict(child=['H']*3+['W']*6+['M','P'],walk=dict(callbacks=1,position=[15040,22976,208],head=[0,0,0],flags=[1,0,0],route=[-1,*range(102,124),-1],late=[['0x71f19f',1],['0x71f1aa',0],['0x71f1b5',0]],events=['mark0','release','occupy','child','return','mark1']))
 def test_late_observation_and_queue_tails_are_required(self):
  row=self.valid_row();joined.validate_row(row,(1,0,0))
  for key,value in (('late',[['0x71f19f',1]]),('callbacks',2),('route',[-1]*24),('events',['child','return'])):
   bad=copy.deepcopy(row);bad['walk'][key]=value
   with self.assertRaises(ValueError):joined.validate_row(bad,(1,0,0))
if __name__=='__main__':unittest.main()
