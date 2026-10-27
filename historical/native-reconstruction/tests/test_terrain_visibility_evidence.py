# SPDX-License-Identifier: GPL-3.0-or-later
"""Invalidation guards for private exact-engine Terrain visibility receipts."""
import copy
import unittest
from compare_original import PATCHED_EXPECTED
from compare_terrain_visibility import validate
from verify_terrain_visibility import verify
class VisibilityEvidenceGuards(unittest.TestCase):
    def fixture(self):
        current={'executable_sha256':PATCHED_EXPECTED,'sources':{'kernel':'one'},'assets':{'tree':'two'}}
        report={'evidence_mode':'fresh-original','identities':current,'native_sha256':'historical runner'}
        evidence={'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                  'commands':['I fixture'],'expected':[['0']],'labels':['fixture'],'evidence':report}
        return evidence,{**report,'expectations_sha256':'fingerprint'},copy.deepcopy(current)
    def test_unchanged_sources_allow_rebuilt_runner(self):
        evidence,receipt,current=self.fixture();validate(evidence,receipt,'fingerprint',current)
    def test_source_change_refused(self):
        evidence,receipt,current=self.fixture();current['sources']['kernel']='changed'
        with self.assertRaisesRegex(ValueError,'identity differs'):validate(evidence,receipt,'fingerprint',current)
    def test_asset_change_refused(self):
        evidence,receipt,current=self.fixture();current['assets']['tree']='changed'
        with self.assertRaisesRegex(ValueError,'identity differs'):validate(evidence,receipt,'fingerprint',current)
    def test_engine_change_refused(self):
        evidence,receipt,current=self.fixture();evidence['executable_sha256']='wrong'
        with self.assertRaisesRegex(ValueError,'engine/profile'):validate(evidence,receipt,'fingerprint',current)
    def test_receipt_fingerprint_refused(self):
        evidence,receipt,current=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(evidence,receipt,'wrong',current)
    def test_incomplete_vectors_refused(self):
        evidence,receipt,current=self.fixture();evidence['labels']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(evidence,receipt,'fingerprint',current)
    def test_unsupported_executable_refused(self):
        with self.assertRaisesRegex(ValueError,'executable'):verify(b'synthetic unsupported image')
if __name__=='__main__':unittest.main()
