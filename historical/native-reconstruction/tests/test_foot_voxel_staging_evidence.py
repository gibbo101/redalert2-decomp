# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as fixtures
from compare_foot_voxel_staging import validate
from verify_foot_voxel_staging import verify
from original_foot_voxel_staging import ranges
class FootVoxelStagingEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=fixtures.VoxelPartEvidenceGuards().fixture();e['commands']=['D fixture'];return e,r,c
    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_changed_input_identity_refused(self):
        for field in ('joined_sources','joined_inspection','snapshot_sources','snapshot_inspection','palette_sha256','assets','pose_expectations_sha256'):
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
    def test_unknown_or_empty_command_refused(self):
        for command in ('unknown',''):
            e,r,c=self.fixture();e['commands']=[command]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_unsupported_engine_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported',b'unsupported')
    def test_instruction_allowlist_excludes_inspected_data(self):
        record={'ranges':[{'patched_va':'0x1000','bytes':4,'instructions':2}],
                'tables':[{'patched_va':'0x2000','bytes':8}],
                'nested':{'0x3000':{'bytes':9,'instructions':3},'0x4000':{'bytes':16}}}
        self.assertEqual(list(ranges(record)),[(0x1000,4),(0x3000,9)])
if __name__=='__main__':unittest.main()
