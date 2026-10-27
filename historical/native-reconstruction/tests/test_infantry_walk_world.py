# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_infantry_walk_world as d
class InfantryWalkWorldEvidence(unittest.TestCase):
 def test_scenarios_and_actual_production_dependencies(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),92);self.assertEqual(len(rows),len(set(c for _,c in rows)))
  for _,c in rows:d.parse(c)
  for p in ('src/assets/PreparedInfantryWalk.hpp','src/assets/PreparedInfantryMembership.hpp','src/sim/InfantryWalkState.hpp',
   'src/sim/WalkMovement.cpp','src/sim/InfantryAdmission.hpp','src/sim/InfantrySpeed.cpp','src/assets/MapFloorHeight.cpp'):
   self.assertIn(p,d.source_closure())
 def test_malformed_inputs(self):
  for c in ('J','',d.command(speed=0),d.command(direction=8),d.command(calls=97),d.command(stop=40),d.command(mutation=4),d.command(flags=256),d.command()+' trailing'):
   with self.assertRaises(ValueError):d.parse(c)
  d.parse(d.command(flags=768)) # Coherent bridge fixture supplies its height/byte too.
 def test_original_provenance_is_separate_from_native(self):
  rows=list(d.scenarios());identities=dict(original={'base':'exact'},native_sources={'source':'old'})
  meta=dict(d.FLAGS,identities=identities,evidence_mode='fresh-original',audited_original_calls=3+sum(d.parse(c)[3]+3+int(d.parse(c)[9]>=0) for _,c in rows))
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in rows],labels=[s for s,_ in rows],
   expected=[['P']*d.parse(c)[3]+['Z','rng'] for _,c in rows],evidence=meta)
  receipt=dict(meta,expectations_sha256='receipt');d.validate(e,receipt,'receipt',dict(identities,native_sources={'source':'rebuilt'}))
  for current,f in ((dict(identities,original={'base':'other'}),'receipt'),(identities,'wrong')):
   with self.assertRaises(ValueError):d.validate(e,receipt,f,current)
  bad=copy.deepcopy(e);bad['evidence']['runtime_enabled']=True
  with self.assertRaises(ValueError):d.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identities)
 def test_wrong_engine_refuses(self):
  with self.assertRaises(ValueError):d.verify(b'other engine')
if __name__=='__main__':unittest.main()
