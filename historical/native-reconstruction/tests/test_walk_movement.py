# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_walk_movement as d
class WalkMovementEvidence(unittest.TestCase):
 def fixture(self):
  pairs=list(d.scenarios());current=dict(original={'fixture':'original'},native_sources={'fixture':'native'})
  meta=dict(d.FLAGS,identities=current,audited_complete_roots=len(pairs),evidence_mode='fresh-original')
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[p[1] for p in pairs],
   labels=[p[0] for p in pairs],expected=[['R','0','Z','0'] for _ in pairs],evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),current
 def test_scenarios_and_source_closure(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),624)
  for _,cmd in rows:self.assertEqual(len(d.parse(cmd)),25)
  self.assertTrue(set(d.source_closure())<=set(d.SOURCES))
  self.assertIn('src/sim/WalkMovement.cpp',d.SOURCES)
  self.assertNotIn('src/platform/SDLApp.cpp',d.SOURCES)
 def test_input_domain(self):
  for cmd in ('',d.command(head=(0,0,0)),d.command(head=(128,128,29)),d.command(marked=256),
   d.command(policy=8),d.command(oldLevel=-129),d.command(desired=65536),d.command(head=(2000000,128,29)),d.command()+' 0'):
   with self.assertRaises((ValueError,IndexError)):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong executable')
 def test_receipt_and_original_identity(self):
  e,r,current=self.fixture();d.validate(e,r,'receipt',current)
  for identity,fingerprint in ((current,'wrong'),(dict(current,original={'fixture':'changed'}),'receipt')):
   with self.assertRaises(ValueError):d.validate(e,r,fingerprint,identity)
  # Native changes are identified anew and must execute; they do not alter
  # the identity of an otherwise unchanged original generation.
  d.validate(e,r,'receipt',dict(current,native_sources={'fixture':'rebuilt'}))
 def test_changed_inputs_scope_and_answer_receipt(self):
  e,r,current=self.fixture()
  changed=copy.deepcopy(e);changed['commands'][0]=d.command(speed=17)
  with self.assertRaises(ValueError):d.validate(changed,r,'receipt',current)
  for flag in d.FLAGS:
   changed=copy.deepcopy(e);changed['evidence'][flag]=not d.FLAGS[flag]
   with self.assertRaises(ValueError):d.validate(changed,dict(changed['evidence'],expectations_sha256='receipt'),'receipt',current)
  changed=copy.deepcopy(e);changed['expected'][0]=['R','0']
  with self.assertRaises(ValueError):d.validate(changed,r,'receipt',current)
if __name__=='__main__':unittest.main()
