# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as fixtures
from compare_unit_voxel_shadow_world import validate
from verify_unit_voxel_shadow_world import verify
class UnitVoxelShadowWorldEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=fixtures.VoxelPartEvidenceGuards().fixture();e['commands']=['D '+' '.join(['0']*23)];return e,r,c
    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_changed_input_identity_refused(self):
        for field in ('unit_shadow_world_sources','unit_shadow_world_inspection','shadow_world_sources','shadow_world_inspection',
                      'world_sources','world_inspection','snapshot_sources','raster_data_sha256','palette_sha256','assets'):
            e,r,c=self.fixture();c[field]='changed'
            with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)
    def test_changed_engine_or_profile_refused(self):
        for field in ('executable_sha256','profile'):
            e,r,c=self.fixture();e[field]='changed'
            with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
    def test_missing_result_refused(self):
        e,r,c=self.fixture();e['expected']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
    def test_wrong_receipt_refused(self):
        e,r,c=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
    def test_unknown_incomplete_or_nonnumeric_command_refused(self):
        for command in ('unknown','','O','O 1 2 3','D','D '+' '.join(['bad']*23)):
            e,r,c=self.fixture();e['commands']=[command]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_reset_allowed(self):
        e,r,c=self.fixture();e['commands']=['O 0 3'];validate(e,r,'fingerprint',c)
    def test_unsupported_engine_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported',b'unsupported')
if __name__=='__main__':unittest.main()
