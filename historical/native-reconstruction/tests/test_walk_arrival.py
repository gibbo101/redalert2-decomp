# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_walk_arrival as d
class WalkArrivalEvidence(unittest.TestCase):
 def test_cases_and_source_boundary(self):
  rows=list(d.scenarios());self.assertGreater(len(rows),300)
  for _,cmd in rows:self.assertEqual(len(d.parse(cmd)),59)
  self.assertTrue(set(d.source_closure())<=set(d.SOURCES));self.assertIn('src/sim/FootCoordinates.cpp',d.SOURCES)
  self.assertNotIn('src/platform/BootCampPreview.cpp',d.SOURCES)
 def test_bad_inputs_and_engine(self):
  for cmd in ('',d.command(onMap=256),d.command(route=[-1]),d.command(cell=(32768,0)),d.command(servicePolicy=512),d.command(head=(0,0,0))):
   with self.assertRaises((ValueError,IndexError)):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong executable')
 def test_replay_original_receipt_and_current_native(self):
  pairs=list(d.scenarios());identity=dict(original={'source':'original'},native_sources={'source':'old'})
  meta=dict(d.FLAGS,identities=identity,audited_complete_roots=len(pairs),evidence_mode='fresh-original')
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[p[1] for p in pairs],
   labels=[p[0] for p in pairs],expected=[['R','0','Z'] for p in pairs],evidence=meta)
  r=dict(meta,expectations_sha256='receipt');d.validate(e,r,'receipt',dict(identity,native_sources={'source':'rebuilt'}))
  for fingerprint,current in (('wrong',identity),('receipt',dict(identity,original={'source':'changed'}))):
   with self.assertRaises(ValueError):d.validate(e,r,fingerprint,current)
  altered=copy.deepcopy(e);altered['commands'][0]=d.command(moving=17)
  with self.assertRaises(ValueError):d.validate(altered,r,'receipt',identity)
  altered=copy.deepcopy(e);altered['evidence']['runtime_enabled']=True
  with self.assertRaises(ValueError):d.validate(altered,dict(altered['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()
