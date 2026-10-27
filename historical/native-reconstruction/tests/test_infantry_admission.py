# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_infantry_admission as d
class InfantryAdmissionEvidence(unittest.TestCase):
 def test_cases_and_native_boundary(self):
  rows=list(d.scenarios());self.assertGreater(len(rows),1000)
  for _,cmd in rows:self.assertEqual(len(d.parse(cmd)[0]),13)
  self.assertIn('src/sim/InfantryAdmission.hpp',d.SOURCES)
  self.assertIn('src/sim/UnitAdmission.hpp',d.SOURCES)
  self.assertNotIn('src/platform/BootCampPreview.cpp',d.SOURCES)
 def test_input_engine_and_receipt_guards(self):
  for cmd in ('',d.command(flag32d=256),d.command(origins=((32768,0),(0,0),(0,0))),d.command()+' tail'):
   with self.assertRaises(ValueError):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong executable')
 def test_original_provenance_separate_from_native(self):
  pairs=list(d.scenarios());identity=dict(original={'source':'original'},native_sources={'source':'old'})
  meta=dict(d.FLAGS,identities=identity,audited_original_calls=sum(len(d.parse(c)[1][-1]) for _,c in pairs),evidence_mode='fresh-original')
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in pairs],labels=[l for l,_ in pairs],
   expected=[['R','z']*len(d.parse(c)[1][-1]) for _,c in pairs],evidence=meta)
  r=dict(meta,expectations_sha256='receipt');d.validate(e,r,'receipt',dict(identity,native_sources={'source':'rebuilt'}))
  for fingerprint,current in (('wrong',identity),('receipt',dict(identity,original={'source':'changed'}))):
   with self.assertRaises(ValueError):d.validate(e,r,fingerprint,current)
  altered=copy.deepcopy(e);altered['evidence']['runtime_enabled']=True
  with self.assertRaises(ValueError):d.validate(altered,dict(altered['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()
