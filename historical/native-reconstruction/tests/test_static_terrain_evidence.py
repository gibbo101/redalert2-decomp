# SPDX-License-Identifier: GPL-3.0-or-later
"""Source/profile/receipt invalidation for the static Terrain traversal oracle."""
import unittest
import test_terrain_visibility_evidence as visibility_guards
from compare_static_terrain import validate
class StaticEvidenceGuards(unittest.TestCase):
    def fixture(self):return visibility_guards.VisibilityEvidenceGuards().fixture()
    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_profile_refused(self):
        e,r,c=self.fixture();e['profile']='allied-disc'
        with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
    def test_sources_refused(self):
        e,r,c=self.fixture();c['sources']['kernel']='changed'
        with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)
    def test_receipt_refused(self):
        e,r,c=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
    def test_incomplete_vectors_refused(self):
        e,r,c=self.fixture();e['expected']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
if __name__=='__main__':unittest.main()
