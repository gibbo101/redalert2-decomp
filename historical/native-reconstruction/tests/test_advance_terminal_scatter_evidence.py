# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_advance_terminal_scatter import command,parse,terminal_defaults,FLAGS,SOURCES,source_closure,validate
import compare_advance_nearby_scatter as legacy
from compare_original import PATCHED_EXPECTED
from verify_advance_terminal_scatter import verify
class CompleteAdvanceTerminalEvidence(unittest.TestCase):
 def fixture(self):
  current=dict(sources={'one':'two'},inspection={'three':'four'})
  meta=dict(FLAGS,identities=current,evidence_mode='fresh-original',native_sha256='runner')
  e=dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[command()],labels=['fixture'],expected=[['state',*['actor']*4,'geometry','scratch','moving','return']],evidence=meta)
  return e,dict(meta,expectations_sha256='fingerprint'),copy.deepcopy(current)
 def test_roundtrip_and_original_identity(self):
  c=parse(command());self.assertTrue(c.pop('terminal_record'))
  for k,v in terminal_defaults().items():self.assertEqual(c.pop(k),v)
  self.assertEqual(c,legacy.defaults());e,r,c=self.fixture();validate(e,r,'fingerprint',c)
  with self.assertRaises(ValueError):verify(b'other engine')
 def test_legacy_records_stay_identical(self):
  c=parse(legacy.command());self.assertFalse(c.pop('terminal_record'))
  for k in terminal_defaults():c.pop(k)
  self.assertEqual(c,legacy.defaults())
 def test_entered_domain_and_scope_cannot_be_relabelled(self):
  for kw in ({'terminal_flags':[0,0,0]},{'terminal_flags':[1,1,0]},{'mission_return':256},{'post_flags':[-1,0,0]},{'bridge':1}):
   with self.subTest(kw=kw),self.assertRaises(ValueError):parse(command(**kw))
  for k,v in FLAGS.items():
   e,r,c=self.fixture();e['evidence'][k]=r[k]=not v
   with self.subTest(k=k),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_transitive_sources_and_projection_guard(self):
  self.assertTrue(set(source_closure())<=set(SOURCES));self.assertIn('src/sim/GroundDriveAdvance.cpp',SOURCES)
  e,r,c=self.fixture();e['expected'][0].remove('return')
  with self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture();c['sources']={}
  with self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
if __name__=='__main__':unittest.main()
