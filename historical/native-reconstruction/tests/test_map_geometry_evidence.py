# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as fixtures
from compare_map_geometry import validate,valid_command
from verify_map_geometry import verify
class MapGeometryEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=fixtures.VoxelPartEvidenceGuards().fixture();e['commands']=['G 0 0 1 1 80 85 0 1'];return e,r,c
    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_changed_sources_inspection_or_owned_map_refused(self):
        for key in ('sources','inspection','owned_map_sha256'):
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
        for cmd in ('','G','Q 1','G 0 0 0 0 0 1 0 1','G 0 0 0 0 128 129 0 1','G 0 0 0 0 1 1 256 1','G 0 0 0 0 1 1 0 2','B 300 300 0 0','V 0 0 1 1 0 0 1 1 -1'):
            e,r,c=self.fixture();e['commands']=[cmd]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_signed_and_wrapped_profiles_are_valid(self):
        for cmd in ('B 2147483647 -2147483648 1 4294967295','V -2147483648 0 2147483647 85 0 0 80 85 0','G 0 4294967295 -2147483648 2147483647 128 128 255 0'):
            valid_command(cmd)
    def test_wrong_engine_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
