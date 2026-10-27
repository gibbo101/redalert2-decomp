# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as fixtures
from compare_overlay_placement import validate
from verify_overlay_placement import verify

class OverlayPlacementEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=fixtures.VoxelPartEvidenceGuards().fixture()
        e['commands']=['C 0 102 0 0 0 1 1 0 0 1 1 4718643 2147450879 17 -1 4 2 3 1 1 73']
        return e,r,c
    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_changed_sources_or_inspection_refused(self):
        for field in ('sources','inspection'):
            e,r,c=self.fixture();c[field]='changed'
            with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)
    def test_changed_engine_or_profile_refused(self):
        for field in ('executable_sha256','profile'):
            e,r,c=self.fixture();e[field]='changed'
            with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
    def test_missing_results_and_empty_corpus_refused(self):
        e,r,c=self.fixture();e['expected']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
        e['commands']=e['labels']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
    def test_wrong_receipt_refused(self):
        e,r,c=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
    def test_malformed_or_outside_profile_command_refused(self):
        for command in ('','Q 1','C 1','M 0',
          'C 0 24 0 0 0 1 1 0 0 1 1 4718643 2147450879 17 -1 4 2 3 1 1 73',
          'C 0 102 9 0 0 1 1 0 0 1 1 4718643 2147450879 17 -1 4 2 3 1 1 73',
          'C 0 102 0 0 0 1 1 0 0 1 1 4718643 2147450879 17 -1 0 2 3 1 1 73'):
            e,r,c=self.fixture();e['commands']=[command]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_unsupported_engine_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')

if __name__=='__main__':unittest.main()
