# SPDX-License-Identifier: GPL-3.0-or-later
"""Identity guards for the complete Foot forwarding and nested cache receipts."""
import unittest
import test_terrain_visibility_evidence as fixture_guards
from compare_foot_lit import validate
from verify_foot_lit_draw import verify
class FootLitEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=fixture_guards.VisibilityEvidenceGuards().fixture();e['commands']=['Z 0 0'];return e,r,c
    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_changed_source_or_inspection_refused(self):
        for key in ('sources','inspection'):
            e,r,c=self.fixture();c[key]={'changed':True}
            with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)
    def test_engine_or_profile_refused(self):
        for key in ('executable_sha256','profile'):
            e,r,c=self.fixture();e[key]='wrong'
            with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
    def test_wrong_receipt_refused(self):
        e,r,c=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
    def test_missing_result_refused(self):
        e,r,c=self.fixture();e['expected']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
    def test_unknown_command_refused(self):
        e,r,c=self.fixture();e['commands']=['unrecognized']
        with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_wrong_binary_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
