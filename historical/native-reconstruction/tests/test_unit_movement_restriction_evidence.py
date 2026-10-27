# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_unit_movement_restriction import parse,validate
from compare_original import PATCHED_EXPECTED
from verify_unit_movement_restriction import verify
class RestrictionEvidenceGuards(unittest.TestCase):
    def fixture(self):
        current={'sources':'current'};r={'evidence_mode':'fresh-original','identities':copy.deepcopy(current)}
        e={'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':['M 0 66'],'expected':[['-1']],'labels':['missing'],'evidence':r}
        return e,{**r,'expectations_sha256':'receipt'},current
    def test_profile_and_source_guards(self):
        e,r,c=self.fixture();validate(e,r,'receipt',c)
        c['sources']='changed'
        with self.assertRaisesRegex(ValueError,'identity'):validate(e,r,'receipt',c)
        e,r,c=self.fixture();e['profile']='wrong'
        with self.assertRaisesRegex(ValueError,'engine/profile'):validate(e,r,'receipt',c)
    def test_receipt_and_count_guards(self):
        e,r,c=self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):validate(e,r,'wrong',c)
        e['commands']=[]
        with self.assertRaisesRegex(ValueError,'counts'):validate(e,r,'receipt',c)
    def test_domain_guards(self):
        for command in ('','M 5 1','M 1 -1','M 0 256','M 0 1 extra','X unknown'):
            with self.assertRaises(ValueError):parse(command)
    def test_exact_binary(self):
        with self.assertRaises(ValueError):verify(b'unsupported')
if __name__=='__main__':unittest.main()
