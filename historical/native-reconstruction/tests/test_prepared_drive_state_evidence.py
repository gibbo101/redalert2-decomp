# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from compare_prepared_drive_state import command,parse,validate
from compare_map_floor_height import bits
import test_resident_map_floor_evidence as base
from verify_prepared_drive_state import verify

class PreparedDriveStateEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.MapFloorFinalizationEvidenceGuards().fixture();e['commands']=['P '+e['commands'][0]]
  return e,r,c
 def test_rebuilt_runner_allowed(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_sources_inputs_and_inspection_refused(self):
  for key in ('prepared','process','body','inspection','sources','depth_input_snapshot_sha256'):
   e,r,c=self.fixture();c[key]='changed'
   with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
 def test_engine_profile_refused(self):
  for key in ('executable_sha256','profile'):
   e,r,c=self.fixture();e[key]='changed'
   with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
 def test_counts_and_receipt_refused(self):
  e,r,c=self.fixture();e['expected']=[]
  with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture()
  with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
 def test_prepared_map_required(self):
  e,r,c=self.fixture();e['commands']=[command()]
  with self.assertRaisesRegex(ValueError,'prepared map'):validate(e,r,'fingerprint',c)
 def test_malformed_and_trailing_commands_refused(self):
  for cmd in ('','M','M bad','W 0','P F',command()+' 0',command(route=(2,-1,2)),command(route=tuple([2]*24))):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_domain_boundaries_refused(self):
  for kw in ({'heading':65536},{'heading':-1},{'rot':0},{'rot':128},{'speed':256},{'speed':-1},{'steps':0},{'steps':257},
   {'marked':256},{'effect':2},{'mode':4},{'present':2},{'key':2147483648},{'tick':-2147483649},
   {'numeric':(1.,float('nan'),.7,1.2)},{'numeric':(1.,1.,float('inf'),1.2)}):
   with self.assertRaises((AssertionError,ValueError)):parse(command(**kw))
 def test_nonstock_height_refused(self):
  e,r,c=self.fixture();p=e['commands'][0].split();p[105]='208';e['commands']=[' '.join(p)]
  with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_valid_signed_and_numeric_edges_parse(self):
  for mode in range(4):
   op,(v,route,numeric)=parse(command(mode=mode,tick=2147483647,key=-2147483648,marked=255,present=0))
   self.assertEqual((op,v[13],route[-1],numeric),('M',mode,-1,[1.,1.,.7,1.2]))
 def test_wrong_engine_refused(self):
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
