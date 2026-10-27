# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_mission_waypoint_lookup as c
class WaypointRevealEvidence(unittest.TestCase):
 def test_scenarios(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),1374)
  values=[c.parse(cmd) for _,cmd in rows if not cmd.startswith('G ')]
  self.assertEqual({v['disabled'] for v in values},set(range(256)))
  self.assertEqual({v['mutation'] for v in values},{0,1,2})
  self.assertEqual({v['levels'][2] for v in values if not v['disabled']},set(range(-128,128)))
 def test_input_and_binary(self):
  good=next(cmd for _,cmd in c.scenarios() if cmd.startswith('W 1 '))
  for cmd in ('',good+' 0',good.replace('W ','R ',1),good.replace('W 1 ','W 256 ',1),good.replace(' 71 ',' 32768 ',1)):
   with self.assertRaises(ValueError):c.parse(cmd)
  with self.assertRaises(ValueError):c.verify(b'not the supplied target')
 def test_reuse_rejects_changed_original_and_scope(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');expected=[]
  for _,cmd in rows:
   q=c.parse(cmd)
   if q.get('getter'):expected.append(['W',str(q['waypoint']),'D',str(q['out'])]+['0']*4096+['R','1']);continue
   expected.append(([] if q['disabled'] else ['W']+['L']*(2 if q['flags'][0]&0x100 else 3)+['A','A'])+['R','1'])
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=expected,evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
  with self.assertRaises(ValueError):c.validate(e,r,'receipt',dict(identity,original={'engine':'changed'}))
  bad=copy.deepcopy(e);bad['evidence']['map_reveal_children_supplied']=False
  with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity)
  bad=copy.deepcopy(e);bad['expected'][0]=['R','1']
  with self.assertRaises(ValueError):c.validate(bad,r,'receipt',identity)
if __name__=='__main__':unittest.main()
