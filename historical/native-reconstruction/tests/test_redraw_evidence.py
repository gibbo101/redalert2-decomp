# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-engine/source/receipt invalidation for redraw evidence."""
import unittest
import test_terrain_visibility_evidence as fixtures
from compare_redraw import validate
from verify_redraw import verify
class RedrawEvidenceGuards(unittest.TestCase):
    def fixture(self):return fixtures.VisibilityEvidenceGuards().fixture()
    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_changed_sources_refused(self):
        e,r,c=self.fixture();c['sources']['kernel']='changed'
        with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)
    def test_changed_engine_refused(self):
        e,r,c=self.fixture();e['executable_sha256']='wrong'
        with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
    def test_changed_profile_refused(self):
        e,r,c=self.fixture();e['profile']='allied-disc'
        with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
    def test_changed_receipt_refused(self):
        e,r,c=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
    def test_incomplete_vectors_refused(self):
        e,r,c=self.fixture();e['labels']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
    def test_unsupported_binary_refused(self):
        with self.assertRaisesRegex(ValueError,'executable'):verify(b'synthetic unsupported executable')
if __name__=='__main__':unittest.main()
