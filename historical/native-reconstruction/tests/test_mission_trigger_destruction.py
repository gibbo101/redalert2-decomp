# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_mission_trigger_destruction as d
class MissionTriggerDestructionEvidence(unittest.TestCase):
 def test_sequences_and_source_scope(self):
  rows=list(d.scenarios());self.assertGreater(len(rows),250)
  for _,cmd in rows:d.parse(cmd)
  self.assertIn('src/sim/MissionTriggerDestruction.hpp',d.NATIVE);self.assertIn('tests/mission_tag_lifetime_world.cpp',d.SOURCES);self.assertNotIn('src/platform/BootCampWalkWorld.cpp',d.SOURCES)
 def test_input_and_binary_guards(self):
  good=next(d.scenarios())[1]
  for cmd in ('',good+' 0',good.replace('P 0 ','P 3 ',1)):
   with self.assertRaises(ValueError):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong executable')
 def test_reuse_guards(self):
  rows=list(d.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(d.FLAGS,identities=identity,evidence_mode='fresh-original');e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in rows],labels=[s for s,_ in rows],expected=[['state'] for _ in rows],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  d.validate(e,r,'receipt',dict(identity,native_sources={'native':'rebuilt'}))
  for fingerprint,current in (('wrong',identity),('receipt',dict(identity,original={'engine':'changed'}))):
   with self.assertRaises(ValueError):d.validate(e,r,fingerprint,current)
  bad=copy.deepcopy(e);bad['evidence']['discovery_actions_and_runtime_join']=True
  with self.assertRaises(ValueError):d.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()
