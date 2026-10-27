# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_infantry_speed as d
class InfantrySpeedEvidence(unittest.TestCase):
 def test_cases_and_native_boundary(self):
  rows=list(d.scenarios());self.assertGreater(len(rows),500)
  for _,cmd in rows:self.assertEqual(len(d.parse(cmd)),13)
  self.assertIn('src/sim/InfantrySpeed.hpp',d.SOURCES)
  self.assertIn('src/sim/InfantrySpeed.cpp',d.SOURCES)
  self.assertNotIn('src/platform/BootCampPreview.cpp',d.SOURCES)
 def test_input_engine_and_receipt_guards(self):
  for cmd in ('',d.command(flag=256),d.command(trigger=33),d.command(calls=0),d.command()+' tail'):
   with self.assertRaises(ValueError):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong executable')
 def test_original_provenance_separate_from_native(self):
  pairs=list(d.scenarios());identity=dict(original={'source':'original'},native_sources={'source':'old'})
  meta=dict(d.FLAGS,identities=identity,audited_original_calls=sum(d.parse(c)[6] for _,c in pairs),evidence_mode='fresh-original')
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in pairs],labels=[l for l,_ in pairs],
   expected=[['R']*d.parse(c)[6]+['Z'] for _,c in pairs],evidence=meta)
  r=dict(meta,expectations_sha256='receipt');d.validate(e,r,'receipt',dict(identity,native_sources={'source':'rebuilt'}))
  for fingerprint,current in (('wrong',identity),('receipt',dict(identity,original={'source':'changed'}))):
   with self.assertRaises(ValueError):d.validate(e,r,fingerprint,current)
  altered=copy.deepcopy(e);altered['evidence']['runtime_enabled']=True
  with self.assertRaises(ValueError):d.validate(altered,dict(altered['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()
