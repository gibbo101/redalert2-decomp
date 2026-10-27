# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_advance_terminal import command,parse,defaults,FLAGS,SOURCES,source_closure,validate
from compare_original import PATCHED_EXPECTED
from verify_advance_terminal import verify
class AdvanceTerminalEvidence(unittest.TestCase):
 def fixture(self):
  current=dict(sources={'one':'two'},inspection={'three':'four'})
  meta=dict(FLAGS,identities=current,evidence_mode='fresh-original',native_sha256='runner')
  e=dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[command()],labels=['fixture'],expected=[['state','return','floor']],evidence=meta)
  return e,dict(meta,expectations_sha256='fingerprint'),copy.deepcopy(current)
 def test_roundtrip_and_identity(self):
  self.assertEqual(parse(command()),defaults());e,r,c=self.fixture();validate(e,r,'fingerprint',c)
  with self.assertRaises(ValueError):verify(b'other engine')
 def test_domain(self):
  for kw in ({'target':2},{'divisor':0},{'registry':128},{'flags':[1,-1,0]},{'notify_flags':[-1,0,0]},{'post_return':256},{'cell':[50,50,0,21]},{'pool':[32768,0]}):
   with self.subTest(kw=kw),self.assertRaises(ValueError):parse(command(**kw))
 def test_scope_and_receipt_guards(self):
  for k,v in FLAGS.items():
   e,r,c=self.fixture();e['evidence'][k]=r[k]=not v
   with self.subTest(k=k),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture();c['sources']={'changed':'value'}
  with self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_transitive_sources_and_required_projection(self):
  self.assertTrue(set(source_closure())<=set(SOURCES));self.assertIn('src/sim/GroundDriveTerminal.hpp',SOURCES)
  e,r,c=self.fixture();e['expected']=[['state']]
  with self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
if __name__=='__main__':unittest.main()
