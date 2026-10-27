# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_mission_create_team_action as c
class MissionCreateTeamActionEvidence(unittest.TestCase):
 def test_sequences_and_scope(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),24)
  for _,cmd in rows:c.parse(cmd)
  self.assertIn('src/sim/MissionCreateTeamAction.hpp',c.NATIVE);self.assertNotIn('src/platform/BootCampMissionWorld.cpp',c.NATIVE)
 def test_input_and_binary_guards(self):
  good=next(c.scenarios())[1]
  for cmd in ('',good+' 0',good.replace('C ','X ',1),'C 4294967296 0 0 0'):
   with self.assertRaises(ValueError):c.parse(cmd)
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_reuse_guards(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');expected=[]
  for _,cmd in rows:
   q=c.parse(cmd);row=[];incremented=(q['initial']+1)&0xffffffff
   if q['present']:
    row+=['C','1','0',str(incremented)]
    if q['mutate']:row+=['M',str(q['childValue'])]
   final=((q['childValue'] if q['present'] and q['mutate'] else incremented)-1)&0xffffffff
   expected.append(row+['R','1','D',str(final)])
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=expected,evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
  bad=copy.deepcopy(e);bad['evidence']['production_team_association']=True
  with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()
