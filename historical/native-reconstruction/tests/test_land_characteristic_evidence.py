# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_voxel_part_evidence as fixtures
from compare_land_characteristics import command, validate
from verify_land_characteristics import verify

class LandCharacteristicEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,current = fixtures.VoxelPartEvidenceGuards().fixture()
        row = [1,1,*([0]*8),0,*([0,0]*7)]
        e['commands'] = [command(3,[row]*12)]
        return e,r,current

    def test_rebuilt_runner_allowed(self):
        e,r,c = self.fixture()
        validate(e,r,'fingerprint',c)

    def test_changed_source_inspection_or_rules_refused(self):
        for key in ('sources','inspection','owned_rules_sha256'):
            e,r,c = self.fixture()
            c[key] = 'changed'
            with self.assertRaisesRegex(ValueError,'identity differs'):
                validate(e,r,'fingerprint',c)

    def test_changed_engine_or_profile_refused(self):
        for key in ('executable_sha256','profile'):
            e,r,c = self.fixture()
            e[key] = 'changed'
            with self.assertRaisesRegex(ValueError,'engine/profile'):
                validate(e,r,'fingerprint',c)

    def test_missing_result_refused(self):
        e,r,c = self.fixture()
        e['expected'] = []
        with self.assertRaisesRegex(ValueError,'counts'):
            validate(e,r,'fingerprint',c)

    def test_receipt_mismatch_refused(self):
        e,r,c = self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):
            validate(e,r,'wrong',c)

    def test_bad_command_refused(self):
        for cmd in ('','L','Q 1','L bad','L 0 0'):
            e,r,c = self.fixture()
            e['commands'] = [cmd]
            with self.assertRaisesRegex(ValueError,'command'):
                validate(e,r,'fingerprint',c)

    def test_numeric_domains_and_trailing_data_refused(self):
        for index,value in ((1,'4'),(2,'-1'),(3,str(1<<32)),(12,'256'),(13,str(1<<64))):
            e,r,c = self.fixture()
            parts = e['commands'][0].split()
            parts[index] = value
            e['commands'] = [' '.join(parts)]
            with self.assertRaisesRegex(ValueError,'command'):
                validate(e,r,'fingerprint',c)
        e,r,c = self.fixture()
        e['commands'][0] += ' 0'
        with self.assertRaisesRegex(ValueError,'command'):
            validate(e,r,'fingerprint',c)

    def test_wrong_engine_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):
            verify(b'unsupported')

if __name__ == '__main__':
    unittest.main()
