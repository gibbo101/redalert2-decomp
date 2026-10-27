# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as base
from compare_occupied_cell import command,parse,validate,HEADER,UNIT
from compare_occupied_membership import command as joined,parse as joined_parse,validate as joined_validate,PREPARED
from verify_occupied_cell import verify
class OccupiedCellEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.VoxelPartEvidenceGuards().fixture();e['commands']=[command()];return e,r,c
 def test_current_receipt_replays(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
 def test_changed_source_and_engine_refused(self):
  e,r,c=self.fixture();c['sources']='changed'
  with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture();e['executable_sha256']='changed'
  with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
  with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
 def test_cycle_unknown_kind_bytes_and_shape_refused(self):
  for cmd in ('','P 0',command()+' trailing',command(actors=[[1,0,0,0,0,0,0,0]]),command(actors=[[2,-1,0,0,0,0,0,0]]),command(actors=[[6,-1,256,0,0,0,0,0]])):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
 def test_raw_building_fields_and_exact_theater_input_preserved(self):
  h=HEADER.copy();h[27]=-2147483648
  result=parse(command(h,[[6,1,255,128,255,2147483647,7,-1],[36,-1,0,0,0,0,-1,7]]))
  self.assertEqual(result[0][27],-2147483648);self.assertEqual(result[1][0][2:5],[255,128,255])
 def test_null_head_and_duplicate_unreachable_nodes(self):
  h=HEADER.copy();h[29]=-1
  self.assertEqual(parse(command(h,[]))[1],[])
  # Unreachable data does not turn an ordinary finite active list into a cycle.
  parse(command(actors=[UNIT,[1,1,0,0,0,0,0,0]]))
class OccupiedMembershipEvidenceGuards(unittest.TestCase):
 def fixture(self):
  e,r,c=base.VoxelPartEvidenceGuards().fixture();e['commands']=[joined()];return e,r,c
 def test_current_receipt_replays(self):
  e,r,c=self.fixture();joined_validate(e,r,'fingerprint',c)
 def test_missing_or_unsupported_resident_inputs_refused(self):
  for cmd in ('','K 0',joined()+' trailing',joined(prepared=[[4,*PREPARED[0][1:]],*PREPARED[1:]])):
   e,r,c=self.fixture();e['commands']=[cmd]
   with self.assertRaisesRegex(ValueError,'command'):joined_validate(e,r,'fingerprint',c)
 def test_original_profile_remains_explicit(self):
  p,*rest=joined_parse(joined());self.assertEqual(len(p),4);self.assertEqual(p[0][3],213)
  self.assertEqual(rest[1][8],0) # No diagnostic notification mutations in this join.
if __name__=='__main__':unittest.main()
