# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_overlay_map_preparation_evidence as base
from compare_overlay_map_resources import validate,parse
from verify_overlay_map_resources import verify
class OverlayMapResourceEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=base.OverlayMapPreparationEvidenceGuards().fixture()
        e['commands']=['N 0 1 0 '+'0 '*9+e['commands'][0][2:]]
        return e,r,c
    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_changed_inputs_refused(self):
        for field in ('sources','inspection','owned_fixture_sha256','owned_source_hashes'):
            e,r,c=self.fixture();c[field]='changed'
            with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)
    def test_engine_and_profile_refused(self):
        for field in ('executable_sha256','profile'):
            e,r,c=self.fixture();e[field]='changed'
            with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
    def test_counts_and_receipt_refused(self):
        e,r,c=self.fixture();e['expected']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
        e,r,c=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
    def test_malformed_command_refused(self):
        for cmd in ('','M 0','N 0','N 9','N 0 256','N 0 1 256 '+'0 '*40):
            e,r,c=self.fixture();e['commands']=[cmd]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_invalid_resource_registry_refused(self):
        e,_,_=self.fixture();tail=e['commands'][0][2:]
        for row in ('0 1 1 0 1 0','1 0 1 0 1 0','0 0 1 0 0 0','0 0 1 0 -1 0'):
            with self.assertRaises(AssertionError):parse('N 1 '+row+' '+tail[2:])
    def test_unsupported_engine_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
