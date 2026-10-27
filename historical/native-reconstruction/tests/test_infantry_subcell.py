# SPDX-License-Identifier: GPL-3.0-or-later
import copy,tempfile,unittest
from pathlib import Path
import compare_infantry_subcell as d
from run_evidence import input_identities
class InfantrySubcellEvidence(unittest.TestCase):
 def test_cases_and_source_boundary(self):
  rows=list(d.scenarios());self.assertGreater(len(rows),300)
  self.assertGreater(sum(len(d.parse(cmd)[-1]) for _,cmd in rows),4000)
  self.assertTrue(set(d.source_closure())<=set(d.SOURCES))
  self.assertNotIn('src/platform/BootCampPreview.cpp',d.SOURCES)
  self.assertIn('src/sim/OriginalRandom.cpp',d.SOURCES)
 def test_bad_inputs_and_engine(self):
  for cmd in ('',d.command(steps=[]),d.command(first=250),d.command(steps=[d.step(force=256)]),
   d.command(steps=[d.step(mutation=512)]),d.command(steps=[d.step(cell=2)])):
   with self.assertRaises((ValueError,IndexError)):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong executable')
 def test_replay_receipt_original_and_native_identities(self):
  pairs=list(d.scenarios());identity=dict(original={'source':'original'},native_sources={'source':'old'})
  calls=1+sum(len(d.parse(cmd)[-1]) for _,cmd in pairs)
  meta=dict(d.FLAGS,identities=identity,audited_original_calls=calls,evidence_mode='fresh-original')
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[p[1] for p in pairs],
   labels=[p[0] for p in pairs],expected=[['Z','rng'] for p in pairs],evidence=meta)
  r=dict(meta,expectations_sha256='receipt');d.validate(e,r,'receipt',dict(identity,native_sources={'source':'rebuilt'}))
  for fingerprint,current in (('wrong',identity),('receipt',dict(identity,original={'source':'changed'}))):
   with self.assertRaises(ValueError):d.validate(e,r,fingerprint,current)
  altered=copy.deepcopy(e);altered['commands'][0]=d.command()
  with self.assertRaises(ValueError):d.validate(altered,r,'receipt',identity)
  altered=copy.deepcopy(e);altered['evidence']['runtime_enabled']=True
  with self.assertRaises(ValueError):d.validate(altered,dict(altered['evidence'],expectations_sha256='receipt'),'receipt',identity)
 def test_subcell_data_is_a_guarded_input(self):
  with tempfile.TemporaryDirectory() as folder:
   paths=[Path(folder)/name for name in ('exe','native','subcell')]
   for p in paths:p.write_bytes(b'first')
   args=['--exe',str(paths[0]),'--native',str(paths[1]),'--subcell-data',str(paths[2])]
   before=input_identities(args);paths[2].write_bytes(b'changed')
   self.assertNotEqual(before,input_identities(args));self.assertIn(str(paths[2].resolve()),before)
if __name__=='__main__':unittest.main()
