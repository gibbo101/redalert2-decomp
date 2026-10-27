# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_walk_route as d
class WalkRouteEvidence(unittest.TestCase):
 def test_scenarios_and_actual_dependencies(self):
  rows=list(d.scenarios());self.assertGreater(len(rows),100)
  self.assertEqual(len(set(c for _,c in rows)),len(rows))
  for _,c in rows:self.assertEqual(len(d.parse(c)[3]),13)
  for p in ('src/sim/WalkMovement.cpp','src/sim/WalkRoute.hpp','src/sim/FootDestination.hpp','src/sim/InfantryDestination.hpp','src/sim/WalkCommands.cpp'):
   self.assertIn(p,d.SOURCES)
  self.assertNotIn('src/platform/BootCampPreview.cpp',d.SOURCES)
 def test_input_and_binary_guards(self):
  for c in ('',d.command(length=0),d.command(length=25),d.command(response=0),d.command(response=256),d.command(order=2),d.command(target=2),d.command(diagnostic=4),d.command(start=2**31),d.command(calls=129),d.command(direction=8)):
   with self.assertRaises(ValueError):d.parse(c)
  with self.assertRaises(ValueError):d.verify(b'wrong engine')
 def test_native_rebuild_does_not_relabel_original(self):
  pairs=list(d.scenarios());identity=dict(original={'inspection':'base'},native_sources={'source':'old'})
  meta=dict(d.FLAGS,identities=identity,audited_original_calls=3+sum(d.parse(c)[0][7]+d.parse(c)[3][0] for _,c in pairs),evidence_mode='fresh-original')
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in pairs],labels=[s for s,_ in pairs],
   expected=[['R']*d.parse(c)[0][7]+['Z','rng'] for _,c in pairs],evidence=meta)
  r=dict(meta,expectations_sha256='receipt')
  d.validate(e,r,'receipt',dict(identity,native_sources={'source':'rebuilt'}))
  for fingerprint,current in (('wrong',identity),('receipt',dict(identity,original={'inspection':'changed'}))):
   with self.assertRaises(ValueError):d.validate(e,r,fingerprint,current)
  for flag in ('runtime_enabled','original_pathfinding_recovered','failed_routes_and_JumpJet_children_supported'):
   bad=copy.deepcopy(e);bad['evidence'][flag]=True
   with self.assertRaises(ValueError):d.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()
