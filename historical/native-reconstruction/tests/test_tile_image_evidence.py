# SPDX-License-Identifier: GPL-3.0-or-later
import unittest,struct
import test_voxel_part_evidence as fixtures
from compare_tile_image import validate,valid_command
from verify_tile_image import verify
class TileImageEvidenceGuards(unittest.TestCase):
    def fixture(self):
        e,r,c=fixtures.VoxelPartEvidenceGuards().fixture()
        e['commands']=['L '+' '.join(map(str,[0,0,11,3,0,3,5,2,*range(16)]))+' '+bytes(16).hex()];return e,r,c
    def test_rebuilt_runner_allowed(self):
        e,r,c=self.fixture();validate(e,r,'fingerprint',c)
    def test_changed_sources_inspection_or_owned_TMP_refused(self):
        for key in ('sources','inspection','owned_TMPs'):
            e,r,c=self.fixture();c[key]='changed'
            with self.assertRaisesRegex(ValueError,'identity differs'):validate(e,r,'fingerprint',c)
    def test_changed_engine_or_profile_refused(self):
        for key in ('executable_sha256','profile'):
            e,r,c=self.fixture();e[key]='changed'
            with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'fingerprint',c)
    def test_missing_result_refused(self):
        e,r,c=self.fixture();e['expected']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'fingerprint',c)
    def test_receipt_mismatch_refused(self):
        e,r,c=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
    def test_bad_command_refused(self):
        for cmd in ('','G','Q 1','L bad','G 0 1'):
            e,r,c=self.fixture();e['commands']=[cmd]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_bad_subtile_or_geometry_refused(self):
        for data in (bytes(15),struct.pack('<4i',256,0,60,30),struct.pack('<4iI',1,1,60,30,4)):
            e,r,c=self.fixture();parts=e['commands'][0].split();parts[-1]=data.hex();e['commands']=[' '.join(parts)]
            with self.assertRaisesRegex(ValueError,'command'):validate(e,r,'fingerprint',c)
    def test_wrong_engine_refused(self):
        with self.assertRaisesRegex(ValueError,'engine'):verify(b'unsupported')
if __name__=='__main__':unittest.main()
