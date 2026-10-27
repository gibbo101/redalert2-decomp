# SPDX-License-Identifier: GPL-3.0-or-later
import ast,copy,re,unittest
from compare_owned_advance_world import parse,validate,SOURCES
from compare_original import PATCHED_EXPECTED
from presentation_evidence import ROOT
class OwnedAdvanceEvidenceGuards(unittest.TestCase):
 def test_transitive_native_headers_are_fingerprinted(self):
  pending=[p for p in SOURCES if p.endswith('.cpp')];seen=set()
  while pending:
   path=pending.pop()
   if path in seen:continue
   seen.add(path);self.assertIn(path,SOURCES)
   for name in re.findall(r'^#include "([^"]+)"',(ROOT/path).read_text(),re.M):
    local=(ROOT/path).parent/name
    pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 def test_seed_domain(self):
  self.assertEqual(parse('K 1 3200 3200 0 19 37 7 1'),('K',[1,3200,3200,0,19,37,7,1]))
  for cmd in ('K','K 2 0 0 0 19 37 7 1','K 0 0 0 0 64 37 7 1','K 0 0 0 0 19 128 7 1','K 0 0 0 0 19 37 7 2','K 0 0 0 0 19 37 2147483648 1','K 0 0 0 0 19 37 7 1 trailing'):
   with self.subTest(cmd=cmd),self.assertRaises(ValueError):parse(cmd)
 def test_actual_Process_call_is_inherited(self):
  tree=ast.parse((ROOT/'tests/original_owned_advance_world.py').read_text())
  for cls in (n for n in tree.body if isinstance(n,ast.ClassDef)):
   self.assertNotIn('call',[n.name for n in cls.body if isinstance(n,ast.FunctionDef)])
 def test_missing_scope_and_identity_refused(self):
  current={'sources':{'test':'identity'}}
  proof={'evidence_mode':'fresh-original','identities':current,'genuine_shared_world_Advance_admission':True,
   'physical_target_membership_measured':True,'distinct_original_Process_records_shared_owned_world':True}
  e={'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence':proof,'commands':['K 0 0 0 0 19 37 7 1'],'expected':[{'state':[]}],'labels':['invalid sequence']}
  r={**proof,'expectations_sha256':'hash'}
  for flag in ('genuine_shared_world_Advance_admission','physical_target_membership_measured','distinct_original_Process_records_shared_owned_world'):
   bad=copy.deepcopy(e);bad['evidence'][flag]=False
   receipt={**bad['evidence'],'expectations_sha256':'hash'}
   with self.assertRaisesRegex(ValueError,'scope'):validate(bad,receipt,'hash',current)
  with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'hash',{'sources':{}})
  with self.assertRaisesRegex(ValueError,'seed required once'):validate(e,r,'hash',current)
if __name__=='__main__':unittest.main()
