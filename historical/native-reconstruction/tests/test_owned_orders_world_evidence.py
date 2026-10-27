# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from compare_owned_orders_world import parse, validate
from verify_owned_orders_world import verify
import test_owned_command_world_evidence as legacy


class OrdersWorldEvidence(unittest.TestCase):
    def fixture(self):
        e, r, c = legacy.CommandWorldEvidence().fixture()
        e['evidence']['independent_original_order_calls_on_actual_actors'] = r['independent_original_order_calls_on_actual_actors'] = True
        commands = [command for id in (0, 1) for command in
                    (f'M {id} 100 384 384 0 2 2 3', f'S {id} 101',
                     f'B {id} 102 -65537', f'F {id} 103')]
        e['commands'][6:6] = commands
        e['expected'][6:6] = [{'state': []} for _ in commands]
        e['labels'][6:6] = ['commands']*len(commands)
        return e, r, c

    def test_independent_streams_and_original_required(self):
        e, r, c = self.fixture(); validate(e, r, 'fingerprint', c)
        e['evidence']['independent_original_order_calls_on_actual_actors'] = r['independent_original_order_calls_on_actual_actors'] = False
        with self.assertRaisesRegex(ValueError, 'Original per-actor'): validate(e, r, 'fingerprint', c)

    def test_malformed_orders(self):
        for command in ('M 0 100 1 2 3 0', 'M 0 100 0 0 0 1 2',
                        'M 0 100 1 2 3 1 8', 'M 2 100 1 2 3 1 2',
                        'M 0 100 1 2 3 2 2', 'S 0 100 extra', 'B 0 100',
                        'B 0 100 2147483648', 'F 0 100 0', 'S 0'):
            with self.subTest(command=command), self.assertRaises(ValueError): parse(command)

    def test_missing_stream_unjoined_and_counts(self):
        for index in range(6, 14):
            e, r, c = self.fixture()
            for key in ('commands', 'expected', 'labels'): del e[key][index]
            with self.assertRaisesRegex(ValueError, 'Both actors'): validate(e, r, 'fingerprint', c)
        e, r, c = self.fixture(); e['commands'][0] = 'S 0 100'; e['expected'][0] = {'state': []}
        with self.assertRaisesRegex(ValueError, 'joined'): validate(e, r, 'fingerprint', c)
        e, r, c = self.fixture(); e['labels'].pop()
        with self.assertRaisesRegex(ValueError, 'counts'): validate(e, r, 'fingerprint', c)

    def test_receipts_identities_and_exact_binary(self):
        e, r, c = self.fixture()
        with self.assertRaisesRegex(ValueError, 'fingerprint'): validate(e, r, 'wrong', c)
        with self.assertRaisesRegex(ValueError, 'identity'): validate(e, r, 'fingerprint', {'changed': True})
        with self.assertRaisesRegex(ValueError, 'fingerprint'): verify(b'wrong engine')


if __name__ == '__main__': unittest.main()
