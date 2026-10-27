# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
import test_map_preparation_evidence as base
from compare_map_wall_owner import command,validate
from verify_map_wall_owner import verify
class MapWallOwnerEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=base.MapPreparationEvidenceGuards().fixture()
        e['commands']=[command('W',0,1,42,0,0,[[1,1,1,7,0,1,1,0,0,0]])]
        return e,r,c
    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_changed_identity_refused(self):
        for key in ('sources','inspection','render_data_sha256'):
            e,r,c=self.fixture();c[key]='changed'
            with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)
    def test_changed_engine_profile_refused(self):
        for key in ('executable_sha256','profile'):
            e,r,c=self.fixture();e[key]='changed'
            with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
    def test_missing_result_or_receipt_refused(self):
        e,r,c=self.fixture();e['expected']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
        e,r,c=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
    def test_bad_command_refused(self):
        for cmd in ('','W','S 0 1 0 -1','W 0 1 0 0 0 1','W bad','D 0 1 0 0'):
            e,r,c=self.fixture();e['commands']=[cmd]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_bad_domain_and_trailing_values_refused(self):
        for index,value in ((1,8),(2,256),(4,-1),(6,1025),(7,256),(11,22),(12,-1)):
            e,r,c=self.fixture();parts=e['commands'][0].split();parts[index]=str(value);e['commands']=[' '.join(parts)]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
        e,r,c=self.fixture();e['commands'][0]+=' 0'
        with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_wrong_engine_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
