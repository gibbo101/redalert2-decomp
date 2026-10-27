# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_mission_tag_expiration as d
class MissionTagExpirationEvidence(unittest.TestCase):
 def test_sequences_and_source_scope(self):
  rows=list(d.scenarios());self.assertGreater(len(rows),480)
  for _,cmd in rows:d.parse(cmd)
  self.assertIn('src/sim/MissionTagExpiration.hpp',d.NATIVE)
  self.assertIn('src/sim/MissionTag.hpp',d.NATIVE)
  self.assertNotIn('src/platform/BootCampWalkWorld.cpp',d.SOURCES)
 def test_input_and_binary_guards(self):
  for cmd in ('',d.command(mode=6),d.command(instances=(2**31,0)),d.command(globals=(3,1)),d.command(cells=((0,262144,1,0,0,0),)),
              d.command(points=(-1,)),d.command(recipients=(0,)),d.command(operations=()),d.command(operations=((5,1,0),)),d.command()+' 0'):
   with self.assertRaises(ValueError):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong executable')
 def test_original_reuse_and_receipt_guards(self):
  rows=list(d.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'})
  meta=dict(d.FLAGS,identities=identity,audited_original_calls=sum(len(d.parse(c)['operations']) for _,c in rows),evidence_mode='fresh-original')
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in rows],labels=[s for s,_ in rows],expected=[['state']+['R']*len(d.parse(c)['operations']) for _,c in rows],evidence=meta)
  r=dict(meta,expectations_sha256='receipt');d.validate(e,r,'receipt',dict(identity,native_sources={'native':'rebuilt'}))
  for fingerprint,current in (('wrong',identity),('receipt',dict(identity,original={'engine':'changed'}))):
   with self.assertRaises(ValueError):d.validate(e,r,fingerprint,current)
  bad=copy.deepcopy(e);bad['evidence']['RaiseEvent_drain_destructor_discovery_scheduler_actions_and_runtime_join']=True
  with self.assertRaises(ValueError):d.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()
