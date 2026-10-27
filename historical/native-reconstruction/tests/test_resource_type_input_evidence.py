# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as fixtures
from compare_resource_type_inputs import validate
from verify_resource_type_inputs import verify
class ResourceTypeInputEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=fixtures.VoxelPartEvidenceGuards().fixture()
        e['commands']=['C 0 0 1 4 1 0 0 1 4 1 0 0 Test'];return e,r,c
    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_changed_sources_inspection_rules_refused(self):
        for field in ('sources','inspection','rules_sha256'):
            e,r,c=self.fixture();c[field]='changed'
            with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)
    def test_engine_profile_refused(self):
        for field in ('executable_sha256','profile'):
            e,r,c=self.fixture();e[field]='changed'
            with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
    def test_empty_or_missing_results_refused(self):
        e,r,c=self.fixture();e['expected']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
        e['commands']=e['labels']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
    def test_wrong_receipt_refused(self):
        e,r,c=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
    def test_malformed_command_refused(self):
        for cmd in ('','Q 0','C 0','I 0','L 0 0 1 4 1 0 0 1 4 1 0 1'):
            e,r,c=self.fixture();e['commands']=[cmd]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_unsupported_engine_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
