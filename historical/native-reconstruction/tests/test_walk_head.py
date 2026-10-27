# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_walk_head as d
class WalkHeadEvidence(unittest.TestCase):
 def test_cases_and_source_boundary(self):
  rows=list(d.scenarios());self.assertGreater(len(rows),500)
  for _,cmd in rows:self.assertEqual(len(d.parse(cmd)),9)
  self.assertIn('src/sim/UnitDiscovery.cpp',d.SOURCES);self.assertIn('src/sim/InfantrySubcell.cpp',d.SOURCES)
  self.assertNotIn('src/platform/BootCampPreview.cpp',d.SOURCES)
 def test_bad_inputs_and_engine(self):
  for cmd in ('',d.command(steps=[]),d.command(first=250),d.command(target=2),d.command(steps=[d.step(kind=3)]),
   d.command(steps=[d.step(trigger=9)]),d.command(steps=[d.step(mutation=1024)])):
   with self.assertRaises((ValueError,IndexError)):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong executable')
 def test_original_receipt_current_native_and_scope(self):
  pairs=list(d.scenarios());identity=dict(original={'source':'original'},native_sources={'source':'old'})
  meta=dict(d.FLAGS,identities=identity,audited_original_calls=1+sum(len(d.parse(c)[-1]) for _,c in pairs),evidence_mode='fresh-original')
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[p[1] for p in pairs],labels=[p[0] for p in pairs],
   expected=[['R']*len(d.parse(p[1])[-1])+['Z','rng'] for p in pairs],evidence=meta)
  r=dict(meta,expectations_sha256='receipt');d.validate(e,r,'receipt',dict(identity,native_sources={'source':'rebuilt'}))
  for fingerprint,current in (('wrong',identity),('receipt',dict(identity,original={'source':'changed'}))):
   with self.assertRaises(ValueError):d.validate(e,r,fingerprint,current)
  altered=copy.deepcopy(e);altered['commands'][0]=d.command()
  with self.assertRaises(ValueError):d.validate(altered,r,'receipt',identity)
  altered=copy.deepcopy(e);altered['evidence']['runtime_enabled']=True
  with self.assertRaises(ValueError):d.validate(altered,dict(altered['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()
