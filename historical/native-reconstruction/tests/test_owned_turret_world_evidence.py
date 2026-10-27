# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from compare_owned_turret_world import parse, validate
from verify_owned_turret_world import verify
import test_owned_command_world_evidence as legacy


class TurretWorldEvidence(unittest.TestCase):
    def fixture(self):
        e, r, current = legacy.CommandWorldEvidence().fixture()
        e['evidence']['independent_turret_commands_on_actual_actors'] = r['independent_turret_commands_on_actual_actors'] = True
        e['evidence']['original_parent_turning_flag_compared'] = r['original_parent_turning_flag_compared'] = True
        extra = ['V 0 100 32768', 'V 1 100 -65537',
                 'U 0 100 0 1 4224 3200 0', 'U 1 100 1 2 0 0 0']
        e['commands'][6:6] = extra
        e['expected'][6:6] = [{'state': []} for _ in extra]
        e['labels'][6:6] = ['turrets']*len(extra)
        return e, r, current

    def test_complete_independent_streams(self):
        e, r, c = self.fixture(); validate(e, r, 'fingerprint', c)

    def test_malformed_turret_commands(self):
        for command in ('V 2 100 0', 'V 0 0 2147483648', 'U 0 0 2 0 0 0 0',
                        'U 0 0 0 3 0 0 0', 'U 0 0 0 0 0 0', 'V 0 0 0 trailing'):
            with self.subTest(command=command), self.assertRaises(ValueError): parse(command)

    def test_receipt_identity_and_missing_streams(self):
        e, r, c = self.fixture()
        with self.assertRaisesRegex(ValueError, 'fingerprint'): validate(e, r, 'wrong', c)
        with self.assertRaisesRegex(ValueError, 'identity'): validate(e, r, 'fingerprint', {'changed':True})
        for index in range(6, 10):
            e, r, c = self.fixture()
            for key in ('commands','expected','labels'): del e[key][index]
            with self.subTest(index=index), self.assertRaisesRegex(ValueError, 'Both independent'):
                validate(e, r, 'fingerprint', c)

    def test_unjoined_command_and_count_mismatch(self):
        e, r, c = self.fixture()
        e['commands'][0] = 'V 0 100 1'; e['expected'][0] = {'state':[]}
        with self.assertRaisesRegex(ValueError, 'joined'): validate(e, r, 'fingerprint', c)
        e, r, c = self.fixture(); e['labels'].pop()
        with self.assertRaisesRegex(ValueError, 'counts'): validate(e, r, 'fingerprint', c)

    def test_exact_binary_required(self):
        with self.assertRaisesRegex(ValueError, 'fingerprint'): verify(b'wrong engine')

    def test_parent_turning_flag_proof_required(self):
        e, r, c = self.fixture()
        e['evidence']['original_parent_turning_flag_compared'] = r['original_parent_turning_flag_compared'] = False
        with self.assertRaisesRegex(ValueError, 'parent turning flag'): validate(e, r, 'fingerprint', c)


if __name__ == '__main__': unittest.main()
