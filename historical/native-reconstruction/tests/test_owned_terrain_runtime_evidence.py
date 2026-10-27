# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from compare_owned_terrain_runtime import validate
import test_owned_scheduled_preview_evidence as scheduled_evidence

class RuntimeEvidence(unittest.TestCase):
    def fixture(self):
        e,r,c=scheduled_evidence.ScheduledEvidence().fixture()
        for v in (e['evidence'],r):
            v['runtime_owned_world_and_tick']=True
            v['runtime_unwired']=False
        return e,r,c
    def test_runtime_proof(self):
        validate(*self.fixture()[:2],'fingerprint',self.fixture()[2])
    def test_missing_runtime_boundary(self):
        for field,value in [('runtime_owned_world_and_tick',False),('runtime_unwired',True)]:
            e,r,c=self.fixture()
            e['evidence'][field]=r[field]=value
            with self.subTest(field=field),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)

if __name__=='__main__':unittest.main()
