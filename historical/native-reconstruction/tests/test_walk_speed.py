# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_walk_speed as d
class WalkSpeedEvidence(unittest.TestCase):
 def test_cases_and_sources(self):
  rows=list(d.scenarios());self.assertGreater(len(rows),100)
  for _,cmd in rows:self.assertEqual(len(d.parse(cmd)[0]),35)
  self.assertIn('src/sim/InfantrySpeed.cpp',d.SOURCES);self.assertIn('src/sim/InfantryAdmission.hpp',d.SOURCES);self.assertIn('src/sim/WalkMovement.cpp',d.SOURCES);self.assertIn('src/sim/WalkHead.cpp',d.SOURCES)
  self.assertNotIn('src/platform/BootCampPreview.cpp',d.SOURCES)
 def test_bad_inputs_and_engine(self):
  for cmd in ('',d.command(calls=0),d.command(calls=129),d.command(bridge=256),d.command(direction=8),
   d.command(direction=-1),d.command(levels=(-129,0)),d.command(mutation=512),d.command(trigger=33),d.command(flag=256),d.command(flag32d=256),d.command(bits=2**32),d.command(heads=(1,0))):
   with self.assertRaises(ValueError):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong executable')
 def test_original_provenance_native_rebuild_and_scope(self):
  pairs=list(d.scenarios());identity=dict(original={'source':'original'},native_sources={'source':'old'})
  meta=dict(d.FLAGS,identities=identity,audited_original_calls=3+sum(d.parse(c)[0][7] for _,c in pairs),evidence_mode='fresh-original')
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[p[1] for p in pairs],labels=[p[0] for p in pairs],
   expected=[['R']*d.parse(p[1])[0][7]+['Z','rng'] for p in pairs],evidence=meta)
  r=dict(meta,expectations_sha256='receipt');d.validate(e,r,'receipt',dict(identity,native_sources={'source':'rebuilt'}))
  for fingerprint,current in (('wrong',identity),('receipt',dict(identity,original={'source':'changed'}))):
   with self.assertRaises(ValueError):d.validate(e,r,fingerprint,current)
  altered=copy.deepcopy(e);altered['commands'][0]=d.command()
  with self.assertRaises(ValueError):d.validate(altered,r,'receipt',identity)
  altered=copy.deepcopy(e);altered['evidence']['runtime_enabled']=True
  with self.assertRaises(ValueError):d.validate(altered,dict(altered['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()
