# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_resource_map_input_evidence as base
from compare_resident_overlay import validate
from verify_resident_overlay import verify
class ResidentOverlayEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=base.ResourceMapInputEvidenceGuards().fixture();e['commands']=['R '+e['commands'][0][2:]+' 0'];return e,r,c
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
    def test_counts_receipt_refused(self):
        e,r,c=self.fixture();e['expected']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
        e,r,c=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
    def test_profile_command_refused(self):
        for command in ('','R 0','J 1','R 1 0 1 1 1 25 4'):
            e,r,c=self.fixture();e['commands']=[command]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_profile_bounds_refused(self):
        for n in (-1,4):
            e,r,c=self.fixture();e['commands']=[e['commands'][0][:-1]+str(n)]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_unsupported_engine_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
