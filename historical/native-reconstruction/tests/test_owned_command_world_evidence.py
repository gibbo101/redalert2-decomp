# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from compare_owned_command_world import validate
import test_owned_unit_processes_evidence as processes


class CommandWorldEvidence(unittest.TestCase):
    def fixture(self):
        evidence, receipt, current = processes.OwnedProcessesEvidence().fixture()
        evidence['evidence']['stable_command_world_owner'] = receipt['stable_command_world_owner'] = True
        return evidence, receipt, current

    def test_complete_owner_receipt(self):
        evidence, receipt, current = self.fixture()
        validate(evidence, receipt, 'fingerprint', current)

    def test_missing_owner_refused(self):
        evidence, receipt, current = self.fixture()
        evidence['evidence']['stable_command_world_owner'] = receipt['stable_command_world_owner'] = False
        with self.assertRaisesRegex(ValueError, 'owner'):
            validate(evidence, receipt, 'fingerprint', current)

    def test_owner_source_changes_refused(self):
        evidence, receipt, current = self.fixture()
        with self.assertRaisesRegex(ValueError, 'identity'):
            validate(evidence, receipt, 'fingerprint', {'changed_owner': True})

    def test_owner_retains_pair_and_return_evidence(self):
        evidence, receipt, current = self.fixture()
        evidence['expected'][4] = {'state': []}
        with self.assertRaisesRegex(ValueError, 'expectation'):
            validate(evidence, receipt, 'fingerprint', current)


if __name__ == '__main__':
    unittest.main()
