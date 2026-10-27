# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_boot_camp_walk_inputs as d
class BootCampWalkEvidence(unittest.TestCase):
 def test_real_E1_inputs_and_nonvacuous_scope(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),10);self.assertEqual(len(set(c for _,c in rows)),10)
  self.assertEqual({d.world.parse(c)[0] for _,c in rows},set(range(8)))
  for _,c in rows:
   v=d.world.parse(c);self.assertEqual((v[1],v[2],v[3],v[4],v[6],v[7]),(10,2,96,2,192,192))
 def test_receipt_original_and_native_identity_guards(self):
  rows=list(d.scenarios());identities=dict(original={'exact':'binary'},native_sources={'old':'native'})
  meta=dict(d.FLAGS,identities=identities,evidence_mode='fresh-original',audited_original_calls=995)
  e=dict(executable_sha256=d.world.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in rows],labels=[s for s,_ in rows],expected=[['P']*96+['Z','rng'] for _,c in rows],evidence=meta)
  r=dict(meta,expectations_sha256='origin');d.validate(e,r,'origin',dict(identities,native_sources={'new':'runner'}))
  for current,f in ((dict(identities,original={'changed':'binary'}),'origin'),(identities,'changed')):
   with self.assertRaises(ValueError):d.validate(e,r,f,current)
  bad=copy.deepcopy(e);bad['evidence']['original_Boot_Camp_startup_pathfinding_scheduler_drawing_verified']=True
  with self.assertRaises(ValueError):d.validate(bad,dict(bad['evidence'],expectations_sha256='origin'),'origin',identities)
 def test_retained_wrong_binary_refusal(self):
  with self.assertRaises(ValueError):d.world.verify(b'wrong executable')
if __name__=='__main__':unittest.main()
