# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as fixtures
from compare_map_preparation import command,validate
from verify_map_preparation import verify
class MapPreparationEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=fixtures.VoxelPartEvidenceGuards().fixture()
        e['commands']=[command([2,2,0,-1,0,[100,100,100,100,0,28],[0]*16,[-1]*15,[0]*8,[1065353216]*11,[[0,0,0,0,30,0,0,0]],[[1,2,0,0,4,0,-1,0,0,0,0,0,7,0]]])]
        return e,r,c
    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_changed_sources_inspection_or_inputs_refused(self):
        for key in ('sources','inspection','owned_map_sha256','map_decoder_sha256','render_data_sha256'):
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
        for cmd in ('','P','Q 1','P bad','P 0 0'):
            e,r,c=self.fixture();e['commands']=[cmd]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_bad_geometry_domain_and_trailing_data_refused(self):
        for index,value in ((1,'1'),(2,'255'),(4,'1'),(5,'3'),(12,'10'),(62,'0')):
            e,r,c=self.fixture();parts=e['commands'][0].split();parts[index]=value;e['commands']=[' '.join(parts)]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
        e,r,c=self.fixture();e['commands'][0]+=' 0'
        with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_wrong_engine_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
