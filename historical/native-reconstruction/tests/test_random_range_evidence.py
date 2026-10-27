# SPDX-License-Identifier: GPL-3.0-or-later
import copy,re,unittest
from compare_random_range import command,parse,validate,FLAGS,SOURCES
from compare_original import PATCHED_EXPECTED
from presentation_evidence import ROOT
from verify_random_range import verify
class RandomRangeEvidence(unittest.TestCase):
 def fixture(self):
  current=dict(sources={'one':'two'},inspection={'three':'four'})
  proof=dict(FLAGS,identities=current,evidence_mode='fresh-original',native_sha256='old runner')
  e=dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[command()],expected=[['state','0']],labels=['fixture'],evidence=proof)
  return e,dict(proof,expectations_sha256='fingerprint'),copy.deepcopy(current)
 def test_rebuilt_runner_keeps_canonical_receipt_and_source(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_wrong_binary_source_inspection_profile_and_receipt_refused(self):
  for key in ('sources','inspection'):
   e,r,c=self.fixture();c[key]='changed'
   with self.subTest(key=key),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
  for key in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[key]='wrong'
   with self.subTest(key=key),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):validate(e,r,'wrong',c)
 def test_scope_flags_cannot_promote_to_Scatter_or_runtime(self):
  for k,v in FLAGS.items():
   e,r,c=self.fixture();e['evidence'][k]=r[k]=not v
   with self.subTest(k=k),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_exact_binary_required(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
 def test_signed_endpoints_and_bypass_invalid_indices_preserved(self):
  parsed=parse(command(first=-2147483648,second=2147483647,ranges=[(-2147483648,-1),(17,17)]))
  self.assertEqual(parsed[1:4],(-2147483648,2147483647,[(-2147483648,-1),(17,17)]))
  self.assertEqual(parse(command(disabled=255,first=-1,second=999))[1:3],(-1,999))
 def test_malformed_and_nonterminating_profiles_refused(self):
  for cmd in ('','X','R 0',command()+' trailing',command(first=-1),command(ranges=[]),command(ranges=[(-2147483648,2147483647)]),command(table=[0]*249),command(disabled=256)):
   with self.subTest(cmd=cmd[:40]),self.assertRaises(ValueError):parse(cmd)
 def test_output_shape_and_counts_refused(self):
  for field,value in (('expected',[['0']]),('expected',[['state','state']]),('expected',[['state',0]]),('labels',[])):
   e,r,c=self.fixture();e[field]=value
   with self.subTest(field=field),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_complete_native_quoted_header_closure(self):
  pending=['tests/random_range_vectors.cpp','src/sim/OriginalRandom.cpp'];seen=set()
  while pending:
   path=pending.pop()
   if path in seen:continue
   seen.add(path);self.assertIn(path,SOURCES)
   for name in re.findall(r'^#include "([^"]+)"',(ROOT/path).read_text(),re.M):
    local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
if __name__=='__main__':unittest.main()
