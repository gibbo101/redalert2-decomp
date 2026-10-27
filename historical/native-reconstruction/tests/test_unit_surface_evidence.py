# SPDX-License-Identifier: GPL-3.0-or-later
"""Receipt invalidation for final Unit drawing; native pixels are not frame proof."""
import unittest
import test_terrain_visibility_evidence as fixture_guards
from compare_unit_surface import validate
from verify_unit_surface import verify
class UnitSurfaceEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=fixture_guards.VisibilityEvidenceGuards().fixture();e['commands']=['S fixture'];return e,r,c
    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_changed_source_refused(self):
        e,r,c=self.fixture();c['sources']['kernel']='changed'
        with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)
    def test_changed_inspection_refused(self):
        e,r,c=self.fixture();c['inspection']='changed'
        with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)
    def test_changed_engine_or_profile_refused(self):
        for field in ('executable_sha256','profile'):
            e,r,c=self.fixture();e[field]='wrong'
            with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
    def test_wrong_receipt_refused(self):
        e,r,c=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
    def test_missing_result_refused(self):
        e,r,c=self.fixture();e['expected']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
    def test_unknown_command_refused(self):
        e,r,c=self.fixture();e['commands']=['unknown']
        with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_unsupported_engine_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
