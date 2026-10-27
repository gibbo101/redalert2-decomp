# SPDX-License-Identifier: GPL-3.0-or-later
"""Identity and runner invalidation for original image-selection receipts."""
import unittest
import test_terrain_visibility_evidence as visibility_guards
from compare_unit_type_visibility import validate
from verify_unit_type_visibility import verify
class TypeEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=visibility_guards.VisibilityEvidenceGuards().fixture();e['commands']=['type H 0 0 0 0'];return e,r,c
    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_source_identity_refused(self):
        e,r,c=self.fixture();c['sources']['kernel']='changed'
        with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)
    def test_engine_refused(self):
        e,r,c=self.fixture();e['executable_sha256']='wrong'
        with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
    def test_profile_refused(self):
        e,r,c=self.fixture();e['profile']='allied-disc'
        with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
    def test_receipt_refused(self):
        e,r,c=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
    def test_counts_refused(self):
        e,r,c=self.fixture();e['labels']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
    def test_unknown_runner_refused(self):
        e,r,c=self.fixture();e['commands']=['unknown H 0 0 0 0']
        with self.assertRaisesRegex(ValueError,'runner'):validate(e,r,'fingerprint',c)
    def test_binary_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported synthetic image')
if __name__=='__main__':unittest.main()
