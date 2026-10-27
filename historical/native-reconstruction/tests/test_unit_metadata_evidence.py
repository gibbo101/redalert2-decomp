# SPDX-License-Identifier: GPL-3.0-or-later
"""Prevent stale source/asset/engine metadata proof from being replayed as current."""
import unittest
import test_terrain_visibility_evidence as visibility_guards
from compare_unit_metadata import validate
from verify_unit_metadata import verify
class MetadataEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=visibility_guards.VisibilityEvidenceGuards().fixture();e['commands']=['B 5 0 79'];return e,r,c
    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_changed_source_or_asset_refused(self):
        for field in ('sources','assets'):
            e,r,c=self.fixture();c[field]['new']='changed'
            with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)
    def test_wrong_engine_or_profile_refused(self):
        for field in ('executable_sha256','profile'):
            e,r,c=self.fixture();e[field]='wrong'
            with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
    def test_wrong_receipt_refused(self):
        e,r,c=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
    def test_incomplete_results_refused(self):
        e,r,c=self.fixture();e['labels']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
    def test_unknown_command_refused(self):
        e,r,c=self.fixture();e['commands']=['unsafe']
        with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_wrong_binary_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
