# SPDX-License-Identifier: GPL-3.0-or-later
import copy,re,unittest
from compare_original import PATCHED_EXPECTED
from compare_cell_scatter import command,parse,validate,FLAGS,SOURCES,MEMBERS
from presentation_evidence import ROOT
from verify_cell_scatter import verify

class CellScatterEvidenceGuards(unittest.TestCase):
 def fixture(self):
  current={'sources':{'kernel':'one'},'inspection':{'range':'two'}}
  proof=dict(FLAGS,evidence_mode='fresh-original',identities=current,native_sha256='historical runner')
  envelope=dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[command()],expected=[['state','0']],labels=['fixture'],evidence=proof)
  return envelope,dict(proof,expectations_sha256='fingerprint'),copy.deepcopy(current)
 def test_rebuilt_runner_with_unchanged_source_and_fresh_receipt(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_source_inspection_receipt_and_engine_are_not_relabelled(self):
  for field in ('sources','inspection'):
   e,r,c=self.fixture();c[field]='changed'
   with self.subTest(field=field),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
  for field in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[field]='wrong'
   with self.subTest(field=field),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):validate(e,r,'wrong',c)
 def test_supplied_children_cannot_be_relabelled_as_Unit_or_Advance_proof(self):
  for field,value in FLAGS.items():
   e,r,c=self.fixture();e['evidence'][field]=r[field]=not value
   with self.subTest(field=field),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_exact_binary_required(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
 def test_parser_signed_bytes_nan_payload_and_full_growth_return(self):
  members=copy.deepcopy(MEMBERS);members[0][4]=0x7ff8000000000123
  result=parse(command(h=[4,0,2,255,-2147483648],members=members,call=[-2147483648,2147483647,-1,255,128,255,4],growth=[0xffffffff,256]))
  self.assertEqual(result[3],members);self.assertEqual(result[4],[-2147483648,2147483647,-1,255,128,255,4]);self.assertEqual(result[5],[0xffffffff,256])
 def test_invalid_cycles_heads_associations_and_protocol_refused(self):
  members=copy.deepcopy(MEMBERS);members[-1][1]=0
  bad=['','C 1','X',command()+' trailing',command(members=members),command(h=[4,4,2,0,3]),command(h=[4,0,2,256,3]),command(growth=[]),command(call=[0,0,0,0,0,0,6])]
  for cmd in bad:
   with self.subTest(cmd=cmd[:40]),self.assertRaises(ValueError):parse(cmd)
 def test_missing_output_shape_or_counts_refused(self):
  for field,value in (('expected',[['0']]),('expected',[['state','state']]),('expected',[['state',0]]),('labels',[])):
   e,r,c=self.fixture();e[field]=value
   with self.subTest(value=value),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_complete_quoted_native_header_closure_retained(self):
  pending=['tests/cell_scatter_vectors.cpp'];seen=set()
  while pending:
   file=pending.pop()
   if file in seen:continue
   seen.add(file);self.assertIn(file,SOURCES)
   for name in re.findall(r'^#include "([^"]+)"',(ROOT/file).read_text(),re.M):
    local=(ROOT/file).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
if __name__=='__main__':unittest.main()
