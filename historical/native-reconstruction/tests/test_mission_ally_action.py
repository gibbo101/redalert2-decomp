# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_mission_ally_action as c
class MissionAllyActionEvidence(unittest.TestCase):
 def test_sequences_and_scope(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),54)
  for _,cmd in rows:c.parse(cmd)
  self.assertIn('src/sim/MissionAllyAction.hpp',c.NATIVE);self.assertNotIn('src/platform/BootCampMissionWorld.cpp',c.NATIVE)
 def test_input_and_binary_guards(self):
  good=next(c.scenarios())[1]
  for cmd in ('',good+' 0',good.replace('A -2 ','X -2 ',1)):
   with self.assertRaises(ValueError):c.parse(cmd)
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_reuse_guards(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=[['R','1'] if c.parse(x)['value']==-1 else ['F','0','0','A','0','0','0','A','0','0','0','R','1'] for _,x in rows],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
  bad=copy.deepcopy(e);bad['evidence']['production_house_association_and_runtime_join']=True
  with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()
