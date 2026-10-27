# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_mission_audio_action as c
class MissionAudioActionEvidence(unittest.TestCase):
 def test_sequences_and_scope(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),14)
  for _,cmd in rows:c.parse(cmd)
  self.assertIn('src/sim/MissionAudioAction.hpp',c.NATIVE);self.assertNotIn('src/platform/BootCampMissionWorld.cpp',c.NATIVE)
 def test_input_and_binary_guards(self):
  good=next(c.scenarios())[1]
  for cmd in ('',good+' 0','20 0'):
   with self.assertRaises(ValueError):c.parse(cmd)
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_reuse_guards(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');expected=[]
  for _,cmd in rows:
   f=c.parse(cmd);expected.append((['S',str(f['value']),'8192','1065353216','0'] if f['kind']==19 else ['V',str(f['value']),'2','-1'])+['R','1'])
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=expected,evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
  bad=copy.deepcopy(e);bad['evidence']['production_token_index_association']=True
  with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()
