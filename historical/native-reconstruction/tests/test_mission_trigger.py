# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_mission_trigger as d
class MissionTriggerEvidence(unittest.TestCase):
 def test_sequences_and_dependencies(self):
  rows=list(d.scenarios());self.assertGreater(len(rows),350)
  for _,cmd in rows:d.parse(cmd)
  self.assertIn('src/sim/MissionEvent.hpp',d.NATIVE)
  self.assertNotIn('src/platform/BootCampWalkWorld.cpp',d.SOURCES)
  self.assertTrue(any(len(d.parse(cmd)['events'])==65 for _,cmd in rows))
 def test_input_and_binary_guards(self):
  for cmd in ('',d.command(enabled=256),d.command(destroyed=-1),d.command(mask=2**32),d.command(events=((51,1),)),
              d.command(houses=[0]*17),d.command(operations=[]),d.command(operations=[d.op(b=3)]),d.command(scratch=2**31),d.command()+' 0'):
   with self.assertRaises(ValueError):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong engine')
 def test_receipt_keeps_original_identity_across_native_rebuild(self):
  rows=list(d.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'})
  meta=dict(d.FLAGS,identities=identity,audited_original_calls=sum(len(d.parse(c)['operations']) for _,c in rows),evidence_mode='fresh-original')
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in rows],labels=[s for s,_ in rows],
   expected=[['state']+['R']*len(d.parse(c)['operations']) for _,c in rows],evidence=meta)
  receipt=dict(meta,expectations_sha256='receipt')
  d.validate(e,receipt,'receipt',dict(identity,native_sources={'native':'rebuilt'}))
  for fingerprint,current in (('wrong',identity),('receipt',dict(identity,original={'engine':'changed'}))):
   with self.assertRaises(ValueError):d.validate(e,receipt,fingerprint,current)
  for flag in ('runtime_enabled','Tag_discovery_or_scheduler_join','random_timer51_supported'):
   bad=copy.deepcopy(e);bad['evidence'][flag]=True
   with self.assertRaises(ValueError):d.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()
