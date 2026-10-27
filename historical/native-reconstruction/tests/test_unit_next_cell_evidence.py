# SPDX-License-Identifier: GPL-3.0-or-later
import copy,re,unittest
from compare_original import PATCHED_EXPECTED
from compare_unit_next_cell import command,parse,validate,ACTOR,CELLS,SLOTS,SOURCES
from presentation_evidence import ROOT
from verify_unit_next_cell import verify
class UnitNextCellEvidenceGuards(unittest.TestCase):
 def fixture(self):
  current={'sources':{'kernel':'one'},'inspection':{'range':'two'}}
  proof={'evidence_mode':'fresh-original','identities':current,'native_sha256':'historical runner'}
  e={'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
   'commands':[command()],'expected':[['0']],'labels':['fixture'],'evidence':proof}
  return e,{**proof,'expectations_sha256':'fingerprint'},copy.deepcopy(current)
 def test_rebuilt_runner_allowed_with_unchanged_sources(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_changed_source_or_inspection_refused(self):
  for k in ('sources','inspection'):
   e,r,c=self.fixture();c[k]='changed'
   with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
 def test_receipt_engine_profile_and_count_refusals(self):
  for k in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[k]='wrong'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'bad',c)
  e['labels']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
 def test_malformed_unsupported_and_aliased_slots_refused(self):
  bad=['','N 0','X',command()+' trailing',command(steps=[]),command(slots=[SLOTS[0]]*2),command(steps=[[0,0,0]])]
  cells=copy.deepcopy(CELLS);cells[0][2]=128;bad.append(command(cells=cells))
  for cmd in bad:
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_raw_bytes_word_edges_and_noncrusher_warning_zero(self):
  actor=ACTOR.copy();actor[4]=0;actor[3]=255;actor[:3]=[-2147483648,2147483647,-1]
  args=parse(command(actor=actor,steps=[[-32768,32767,256]]))
  self.assertEqual(args[2],actor);self.assertEqual(args[3],[[-32768,32767,256]])
 def test_sequence_limit(self):
  parse(command(steps=[[51,72,1]]*128))
  with self.assertRaises(ValueError):parse(command(steps=[[51,72,1]]*129))
 def test_exact_binary_required(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
 def test_transitive_native_headers_are_fingerprinted(self):
  pending=['src/sim/UnitNextCell.cpp','tests/unit_next_cell_vectors.cpp'];seen=set()
  while pending:
   path=pending.pop()
   if path in seen:continue
   seen.add(path);self.assertIn(path,SOURCES)
   for name in re.findall(r'^#include "([^"]+)"',(ROOT/path).read_text(),re.M):
    pending.append('src/'+name)
if __name__=='__main__':unittest.main()
