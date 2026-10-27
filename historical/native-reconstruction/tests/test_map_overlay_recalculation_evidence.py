# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as fixtures
from compare_map_overlay_recalculation import validate
from verify_map_overlay_recalculation import verify
class MapOverlayRecalculationEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=fixtures.VoxelPartEvidenceGuards().fixture();e['commands']=['O '+' '.join(['0']*76)];return e,r,c
    def test_valid_receipt(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_changed_identity(self):
        for key in ('sources','inspection'):
            e,r,c=self.fixture();c[key]='changed'
            with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'fingerprint',c)
    def test_changed_engine_profile(self):
        for key in ('executable_sha256','profile'):
            e,r,c=self.fixture();e[key]='changed'
            with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
    def test_missing_result(self):
        e,r,c=self.fixture();e['expected']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
    def test_wrong_receipt(self):
        e,r,c=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
    def test_bad_commands(self):
        for cmd in ('','O','O '+' '.join(['0']*75),'O bad '+' '.join(['0']*75),'A '+' '.join(['0']*76)):
            e,r,c=self.fixture();e['commands']=[cmd]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_unsupported_engine(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
