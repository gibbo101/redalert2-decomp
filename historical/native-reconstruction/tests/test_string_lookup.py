# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_string_lookup as c

class StringLookupEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'})
  meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original')
  evidence=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=[['R','1','F','0'] for _ in rows],evidence=meta)
  return evidence,dict(meta,expectations_sha256='receipt'),identity
 def test_sequences_and_scope(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),3224)
  for _,cmd in rows:c.parse(cmd)
  self.assertEqual({c.parse(cmd)['outKind'] for _,cmd in rows},set(range(5)))
  self.assertFalse(c.FLAGS['missing_label_fallback_recovered'])
  self.assertFalse(c.FLAGS['original_CSF_loader_recovered'])
  self.assertFalse(c.FLAGS['production_UI_enabled'])
 def test_input_and_binary_guards(self):
  good=next(c.scenarios())[1]
  for cmd in ('',good+' 0','X 1 0 0 0 -','L 1 0 2 0 -','B 1 0 0 0 00','B 1 0 0 0 xx'):
   with self.assertRaises(ValueError):c.parse(cmd)
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_reuse_allows_rebuilt_native_only(self):
  e,r,i=self.fixture();c.validate(e,r,'receipt',dict(i,native_sources={'native':'new'}))
  with self.assertRaises(ValueError):c.validate(e,r,'receipt',dict(i,original={'engine':'other'}))
 def test_receipt_and_scope_guards(self):
  e,r,i=self.fixture()
  with self.assertRaises(ValueError):c.validate(e,r,'changed receipt',i)
  for flag in c.FLAGS:
   bad=copy.deepcopy(e);bad['evidence'][flag]=not c.FLAGS[flag]
   with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',i)
 def test_input_identity_guards(self):
  e,r,i=self.fixture()
  for key,value in (('executable_sha256','other'),('profile','other'),('commands',e['commands'][::-1]),('labels',[]),('expected',[])):
   bad=copy.deepcopy(e);bad[key]=value
   with self.assertRaises(ValueError):c.validate(bad,r,'receipt',i)

if __name__=='__main__':unittest.main()
