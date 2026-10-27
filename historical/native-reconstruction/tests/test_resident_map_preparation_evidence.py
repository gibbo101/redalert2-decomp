# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as fixtures
from compare_resident_map_preparation import command, parse, validate
from verify_resident_map_preparation import verify

class ResidentMapPreparationEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=fixtures.VoxelPartEvidenceGuards().fixture()
        land=[[1065353216]*8+[1] for _ in range(12)]
        common=[2,2,0,-1,0,100,100,100,100,0,28,*([0]*16),*([-1]*15),*([0]*8),*([1065353216]*11)]
        e['commands']=[command(common,land,[2,0,0,2,2],[[1,2,1,60,30,1,0,0,0,0,0,0,0,0,0,0,0]],
            [[1,2,0,0,4,0,-1,0,0,0,0,0,7,0]])]
        return e,r,c

    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)

    def test_changed_sources_and_owned_inputs_refused(self):
        for key in ('sources','inspection','owned_inputs','map_decoder_sha256','render_data_sha256'):
            e,r,c=self.fixture();c[key]='changed'
            with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)

    def test_engine_and_profile_refused(self):
        for key in ('executable_sha256','profile'):
            e,r,c=self.fixture();e[key]='changed'
            with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)

    def test_receipt_mismatch_refused(self):
        e,r,c=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)

    def test_missing_result_refused(self):
        e,r,c=self.fixture();e['expected']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)

    def test_bad_command_and_trailing_data_refused(self):
        for text in ('','Q','P 1','Q bad'):
            with self.assertRaises((AssertionError,ValueError,IndexError)):parse(text)
        e,r,c=self.fixture();e['commands'][0]+=' 0'
        with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)

    def test_Wheel_binding_and_dimensions_refused(self):
        # One-based command token positions include the operation at zero.
        for index,value in ((64,'0'),(170,'3'),(176,'61'),(177,'61'),(180,'2147483648')):
            e,r,c=self.fixture();parts=e['commands'][0].split();parts[index]=value;e['commands']=[' '.join(parts)]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)

    def test_wrong_engine_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')

if __name__=='__main__':unittest.main()
