# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_mission_reveal_action as c
class MissionRevealActionEvidence(unittest.TestCase):
 def test_sequences_and_scope(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),9)
  for _,cmd in rows:c.parse(cmd)
  self.assertIn('src/sim/MissionRevealAction.hpp',c.NATIVE);self.assertNotIn('src/platform/BootCampMissionWorld.cpp',c.NATIVE)
 def test_input_and_binary_guards(self):
  good=next(c.scenarios())[1]
  for cmd in ('',good+' 0',good.replace('R ','X ',1),'R 0 3 0 0 0','R 4294967296 0 0 0 0'):
   with self.assertRaises(ValueError):c.parse(cmd)
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_reuse_guards(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');expected=[]
  for _,cmd in rows:
   q=c.parse(cmd);expected.append(['C',str(0x3000100),str(q['first']),str(0x3001000 if q['object']==2 else 0),str(q['third']),str(q['fourth']),'R',str(q['result']&255)])
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=expected,evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
  bad=copy.deepcopy(e);bad['evidence']['production_action_association']=True
  with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()
