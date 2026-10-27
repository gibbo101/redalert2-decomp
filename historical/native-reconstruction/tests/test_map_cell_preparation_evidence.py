# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as fixtures
from compare_map_cell_preparation import validate
from verify_map_cell_preparation import verify
class MapCellPreparationEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=fixtures.VoxelPartEvidenceGuards().fixture();e['commands']=['J '+' '.join(['0']*87)];return e,r,c
    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_changed_sources_refused(self):
        e,r,c=self.fixture();c['sources']='changed'
        with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)
    def test_changed_inspection_refused(self):
        e,r,c=self.fixture();c['inspection']='changed'
        with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)
    def test_changed_engine_profile_refused(self):
        for k in ('executable_sha256','profile'):
            e,r,c=self.fixture();e[k]='changed'
            with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
    def test_missing_result_refused(self):
        e,r,c=self.fixture();e['expected']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
    def test_wrong_receipt_refused(self):
        e,r,c=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
    def test_bad_command_refused(self):
        for command in ('','Q 1','J','J bad '+' '.join(['0']*86),'J '+' '.join(['0']*86)):
            e,r,c=self.fixture();e['commands']=[command]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_fallback_join_refused(self):
        e,r,c=self.fixture();v=e['commands'][0].split();v[13]='1';e['commands']=[' '.join(v)]
        with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_unsupported_engine_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
