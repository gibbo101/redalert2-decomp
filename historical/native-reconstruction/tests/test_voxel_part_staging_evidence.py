# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as fixture_guards
from compare_voxel_part_staging import validate
class VoxelPartStagingEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=fixture_guards.VoxelPartEvidenceGuards().fixture();e['commands']=['S fixture'];return e,r,c
    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_changed_inputs_refused(self):
        for field in ('nested_sources','palette_sha256','nested_inspection','sources','assets','pose_expectations_sha256'):
            e,r,c=self.fixture();c[field]='changed'
            with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)
    def test_changed_engine_or_profile_refused(self):
        for field in ('executable_sha256','profile'):
            e,r,c=self.fixture();e[field]='changed'
            with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
    def test_wrong_receipt_refused(self):
        e,r,c=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
    def test_missing_result_refused(self):
        e,r,c=self.fixture();e['expected']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
    def test_unknown_command_refused(self):
        e,r,c=self.fixture();e['commands']=['unknown']
        with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
if __name__=='__main__':unittest.main()
