# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as fixtures
from compare_tile_variants import validate
from verify_tile_variants import verify
class TileVariantEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=fixtures.VoxelPartEvidenceGuards().fixture();e['commands']=['R '+' '.join(map(str,[0,0,103,1,*([0]*250)]))];return e,r,c
    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_changed_sources_or_inspection_refused(self):
        for key in ('sources','inspection'):
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
        for cmd in ('','R','Q 1','V bad','V 0 0'):
            e,r,c=self.fixture();e['commands']=[cmd]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_bad_state_indices_refused(self):
        e,r,c=self.fixture();parts=e['commands'][0].split();parts[2]='250';e['commands']=[' '.join(parts)]
        with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_wrong_engine_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
