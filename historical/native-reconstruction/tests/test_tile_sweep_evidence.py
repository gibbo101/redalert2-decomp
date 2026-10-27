# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as fixtures
from compare_tile_sweep import command,validate
from verify_tile_sweep import verify
class TileSweepEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=fixtures.VoxelPartEvidenceGuards().fixture()
        e['commands']=[command([2,0,0,0,[1,2,1,1025],[0],[[-1,1,0,0,0,0,'',-1,0,0]],[[1,2,0,0,0]],{},1,0,0,103,[0]*250,[0]*64,[0]*16,[[0,0]]*8])]
        return e,r,c
    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_changed_sources_inspection_or_owned_inputs_refused(self):
        for key in ('sources','inspection','owned_map_sha256','owned_ini_sha256','owned_TMPs','map_decoder_sha256'):
            e,r,c=self.fixture();c[key]='changed'
            with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)
    def test_changed_engine_or_profile_refused(self):
        for key in ('executable_sha256','profile'):
            e,r,c=self.fixture();e[key]='changed'
            with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
    def test_missing_result_refused(self):
        e,r,c=self.fixture();e['expected']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
    def test_receipt_mismatch_refused(self):
        e,r,c=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
    def test_bad_command_refused(self):
        for cmd in ('','S','Q 1','S bad','S 0 0'):
            e,r,c=self.fixture();e['commands']=[cmd]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_bad_geometry_state_and_trailing_data_refused(self):
        for index,value in ((1,'1'),(8,'262144'),(11,'250'),(13,'4294967296'),(360,'1'),(362,'1')):
            e,r,c=self.fixture();parts=e['commands'][0].split();parts[index]=value;e['commands']=[' '.join(parts)]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
        e,r,c=self.fixture();e['commands'][0]+=' extra'
        with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_wrong_engine_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
