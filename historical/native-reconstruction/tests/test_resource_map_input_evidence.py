# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_overlay_map_resource_evidence as base
from compare_resource_map_inputs import validate
from verify_resource_map_inputs import verify

class ResourceMapInputEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=base.OverlayMapResourceEvidenceGuards().fixture()
        e['commands']=['J 1 0 1 1 1 25 '+e['commands'][0][2:]]
        return e,r,c
    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_changed_inputs_refused(self):
        for field in ('sources','inspection','owned_fixture_sha256','owned_source_hashes'):
            e,r,c=self.fixture();c[field]='changed'
            with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)
    def test_engine_profile_refused(self):
        for field in ('executable_sha256','profile'):
            e,r,c=self.fixture();e[field]='changed'
            with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
    def test_counts_and_receipt_refused(self):
        e,r,c=self.fixture();e['expected']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
        e,r,c=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
    def test_malformed_rows_refused(self):
        for command in ('','J 0','J 9','J 1 -1 1 1 1 25','J 1 0 1 4294967296 1 25','N 0'):
            e,r,c=self.fixture();e['commands']=[command]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_nonempty_diagnostic_prefix_refused(self):
        e,r,c=self.fixture();e['commands']=[e['commands'][0].replace('25 0 1','25 1 0 0 1 0 1 0 1')]
        with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_unsupported_engine_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')

if __name__=='__main__':unittest.main()
