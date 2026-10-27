# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_infantry_mark as d
class InfantryMarkEvidence(unittest.TestCase):
 def test_scenarios_and_shared_native_kernel(self):
  rows=list(d.scenarios());self.assertGreater(len(rows),600)
  self.assertEqual(len(rows),len(set(c for _,c in rows)))
  for _,c in rows:d.parent.parse(c)
  self.assertIn('src/sim/UnitMark.cpp',d.source_closure())
  self.assertIn('tests/original_unit_mark.py',d.ORIGINAL)
  self.assertNotIn('src/platform/BootCampPreview.cpp',d.SOURCES)
 def test_wrong_binary_refuses(self):
  with self.assertRaises(ValueError):d.verify(b'wrong engine')
 def test_original_identity_and_receipt_guards(self):
  rows=list(d.scenarios());identity=dict(original={'inspection':'base'},native_sources={'source':'old'})
  meta=dict(d.FLAGS,identities=identity,evidence_mode='fresh-original',
   audited_original_calls=sum(len(d.parent.parse(c)[1]) for _,c in rows))
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in rows],
   labels=[s for s,_ in rows],expected=[['S']*len(d.parent.parse(c)[1]) for _,c in rows],evidence=meta)
  r=dict(meta,expectations_sha256='receipt')
  d.validate(e,r,'receipt',dict(identity,native_sources={'source':'rebuilt'}))
  for fingerprint,current in (('wrong',identity),('receipt',dict(identity,original={'inspection':'changed'}))):
   with self.assertRaises(ValueError):d.validate(e,r,fingerprint,current)
  for flag in ('runtime_enabled','actual_Infantry_membership_join','full_frame_fidelity'):
   bad=copy.deepcopy(e);bad['evidence'][flag]=True
   with self.assertRaises(ValueError):d.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()
