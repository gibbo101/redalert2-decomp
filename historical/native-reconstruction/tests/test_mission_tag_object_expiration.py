# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_mission_tag_object_expiration as d
class MissionTagObjectExpirationEvidence(unittest.TestCase):
 def test_sequences_and_source_scope(self):
  rows=list(d.scenarios());self.assertGreater(len(rows),300)
  for _,cmd in rows:d.parse(cmd)
  self.assertIn('src/sim/MissionTagObjectExpiration.hpp',d.NATIVE);self.assertNotIn('src/platform/BootCampWalkWorld.cpp',d.SOURCES)
 def test_input_and_binary_guards(self):
  for cmd in ('',d.command(instances=(2**31,0)),d.command(object_tag=3),d.command(subject=0),d.command(operations=()),d.command(operations=(-1,)),d.command()+' 0'):
   with self.assertRaises(ValueError):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong executable')
 def test_reuse_guards(self):
  rows=list(d.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(d.FLAGS,identities=identity,audited_original_calls=sum(len(d.parse(c)['operations']) for _,c in rows),evidence_mode='fresh-original')
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in rows],labels=[s for s,_ in rows],expected=[['state']+['R']*len(d.parse(c)['operations']) for _,c in rows],evidence=meta);r=dict(meta,expectations_sha256='receipt')
  d.validate(e,r,'receipt',dict(identity,native_sources={'native':'rebuilt'}))
  for fingerprint,current in (('wrong',identity),('receipt',dict(identity,original={'engine':'changed'}))):
   with self.assertRaises(ValueError):d.validate(e,r,fingerprint,current)
  bad=copy.deepcopy(e);bad['evidence']['broadcast_RaiseEvent_drain_discovery_actions_and_runtime_join']=True
  with self.assertRaises(ValueError):d.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()
