# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_moving_unit_admission import command,parse,validate,MOTION
from compare_original import PATCHED_EXPECTED
from verify_moving_unit_admission import verify
class MovingAdmissionEvidence(unittest.TestCase):
 def fixture(self):
  evidence={'identities':{'sources':'fixture'},'complete_parent_and_actual_moving_children':True}
  e={'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':[command()],
   'labels':['fixture'],'expected':[['ok']],'evidence':evidence}
  r={**evidence,'expectations_sha256':'fingerprint','evidence_mode':'fresh-original',
   'original_instructions_executed':True,'original_instructions_modified':False}
  e['evidence'].update({k:v for k,v in r.items() if k!='expectations_sha256'})
  return e,r,{'sources':'fixture'}
 def test_records_and_fp_mode(self):
  fixture,motion,mode=parse(command(mode=3));self.assertEqual(mode,3);self.assertEqual(motion,MOTION)
  self.assertEqual(len(fixture[-1]),1)
 def test_invalid_protocol_and_records(self):
  for cmd in ('','V 0',command()+' trailing',command(mode=4),command().replace(' M ',' X ',1)):
   with self.subTest(cmd=cmd[:20]),self.assertRaises(ValueError):parse(cmd)
  for index,value in ((9,65536),(13,-1),(14,256),(16,-1),(18,256)):
   motion=copy.deepcopy(MOTION);motion[1][index]=value
   with self.subTest(index=index),self.assertRaises(ValueError):parse(command(motion))
 def test_unknown_executable(self):
  with self.assertRaises(ValueError):verify(b'unsupported')
 def test_current_identity_and_join_required(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
  with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',{})
  e['evidence']['complete_parent_and_actual_moving_children']=r['complete_parent_and_actual_moving_children']=False
  with self.assertRaisesRegex(ValueError,'join'):validate(e,r,'fingerprint',c)
if __name__=='__main__':unittest.main()
