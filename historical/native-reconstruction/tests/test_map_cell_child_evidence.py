# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as fixtures
from compare_map_cell_children import validate
from verify_map_cell_children import verify
class MapCellChildEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=fixtures.VoxelPartEvidenceGuards().fixture();e['commands']=['E 0 0 0 1 100 0 0 100 100 1'];return e,r,c
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
        for command in ('','Q 1','E','E bad 0 0 1 100 0 0 100 100 1','L 0','P 0'):
            e,r,c=self.fixture();e['commands']=[command]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_unsupported_engine_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
