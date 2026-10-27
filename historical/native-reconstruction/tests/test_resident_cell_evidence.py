# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_map_cell_preparation_evidence as base
from compare_resident_cell import validate
from verify_resident_cell import verify

class ResidentCellEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=base.MapCellPreparationEvidenceGuards().fixture()
        e['commands']=['K '+e['commands'][0][2:]+' -1 0 0 0 0 0 0 0 0 4 8']
        return e,r,c
    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_changed_sources_inspection_refused(self):
        for key in ('sources','inspection'):
            e,r,c=self.fixture();c[key]='changed'
            with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)
    def test_engine_profile_refused(self):
        for key in ('executable_sha256','profile'):
            e,r,c=self.fixture();e[key]='changed'
            with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
    def test_missing_results_and_receipt_refused(self):
        e,r,c=self.fixture();e['expected']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
        e,r,c=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
    def test_malformed_command_refused(self):
        for command in ('','K 0','J '+'0 '*98,'K '+'0 '*97):
            e,r,c=self.fixture();e['commands']=[command]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_unsupported_profile_refused(self):
        for index,value in ((13,1),(88,-2),(89,11),(90,256),(96,4294967296)):
            e,r,c=self.fixture();v=e['commands'][0].split();v[index]=str(value);e['commands']=[' '.join(v)]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_unsupported_engine_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')

if __name__=='__main__':unittest.main()
