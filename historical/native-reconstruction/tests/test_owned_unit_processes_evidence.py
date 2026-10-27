# SPDX-License-Identifier: GPL-3.0-or-later
import copy
import unittest

from compare_owned_unit_processes import parse, validate
from owned_process_events import original, native
from verify_owned_unit_processes import verify
import test_owned_unit_world_evidence as legacy


class OwnedProcessesEvidence(unittest.TestCase):
    def fixture(self):
        evidence, receipt, current = legacy.OwnedWorldEvidence().fixture()
        commands = evidence['commands']
        join = 'J '+' '.join(map(str, [3968,3200,0,*([2]*4+[-1]*20),-1,-17,0]))
        evidence['commands'] = [*commands[:3],join,'T 0 100','T 1 100',commands[4],'T 0 101','T 1 101']
        evidence['expected'] = [({'state': []} if c.startswith(('I ','J ')) else
                                 {'events': [],'state': []} if c.startswith('T ') else {'tokens': []})
                                for c in evidence['commands']]
        evidence['labels'] = ['fixture']*len(evidence['commands'])
        for key in ('distinct_original_Process_records_shared_owned_world',
                    'selected_stores_and_all_logged_queries_compared'):
            evidence['evidence'][key] = receipt[key] = True
        return evidence, receipt, current

    def test_complete_pair_draw_later_pair(self):
        evidence, receipt, current = self.fixture()
        validate(evidence, receipt, 'fingerprint', current)

    def test_each_initialization_phase_required(self):
        for index in range(4):
            evidence, receipt, current = self.fixture()
            for key in ('commands','expected','labels'):
                del evidence[key][index]
            with self.subTest(index=index), self.assertRaises(ValueError):
                validate(evidence, receipt, 'fingerprint', current)

    def test_pair_order_tick_and_draw_boundary(self):
        for commands in (['T 1 100'],['T 0 100','T 0 100'],['T 0 100','T 1 101']):
            evidence, receipt, current = self.fixture()
            evidence['commands'][4:6] = commands
            evidence['expected'][4:6] = [{'state': [],'events': []}]*len(commands)
            evidence['labels'][4:6] = ['fixture']*len(commands)
            with self.subTest(commands=commands), self.assertRaises(ValueError):
                validate(evidence, receipt, 'fingerprint', current)
        evidence, receipt, current = self.fixture()
        for key in ('commands','expected','labels'):
            del evidence[key][4:6]
        with self.assertRaisesRegex(ValueError,'Process calls'):
            validate(evidence, receipt, 'fingerprint', current)
        evidence, receipt, current = self.fixture()
        for key in ('commands','expected','labels'):
            del evidence[key][-1]
        with self.assertRaisesRegex(ValueError,'Incomplete'):
            validate(evidence, receipt, 'fingerprint', current)

    def test_malformed_actor_route_timer_and_reset_commands(self):
        join = self.fixture()[0]['commands'][3]
        for command in ('','T','T 2 0','T -1 0','T 0 2147483648','T 0 0 trailing',
                        join+' 0',join.replace('3968','2147483648',1),
                        'J '+' '.join(['0']*30), 'O 1 0'):
            with self.subTest(command=command), self.assertRaises((ValueError,AssertionError)):
                parse(command)

    def test_identity_receipt_profile_and_join_guards(self):
        evidence, receipt, current = self.fixture()
        with self.assertRaisesRegex(ValueError,'fingerprint'):
            validate(evidence, receipt, 'wrong', current)
        with self.assertRaisesRegex(ValueError,'identity'):
            validate(evidence, receipt, 'fingerprint', {'changed': True})
        for key in ('distinct_original_Process_records_shared_owned_world',
                    'selected_stores_and_all_logged_queries_compared'):
            evidence, receipt, current = self.fixture()
            evidence['evidence'][key] = receipt[key] = False
            with self.subTest(key=key), self.assertRaisesRegex(ValueError,'join'):
                validate(evidence, receipt, 'fingerprint', current)
        evidence, receipt, current = self.fixture()
        evidence['profile'] = 'other'
        with self.assertRaisesRegex(ValueError,'profile'):
            validate(evidence, receipt, 'fingerprint', current)

    def test_missing_or_malformed_expectations_refused(self):
        for key in ('commands','expected','labels'):
            evidence, receipt, current = self.fixture()
            evidence[key] = []
            with self.subTest(key=key), self.assertRaisesRegex(ValueError,'counts'):
                validate(evidence, receipt, 'fingerprint', current)
        evidence, receipt, current = self.fixture()
        evidence['expected'][4] = {'state': []}
        with self.assertRaisesRegex(ValueError,'expectation'):
            validate(evidence, receipt, 'fingerprint', current)

    def test_logged_word_queries_and_selected_store_order_retained(self):
        events = ['write-Drive',1,0x40,4,0,'write-Drive',1,0x44,4,0,
                  'write-Drive',1,0x63,1,0,'write-Drive',1,0x48,4,0,
                  'query',1,'0x548070',12,13]
        expected = [['L',1,off,0] for off in (0x40,0x44,0x63,0x48)]+[['Q','W',1,12,13]]
        self.assertEqual(original(events),expected)
        self.assertEqual(native('L 64 0 L 68 0 L 99 0 L 72 0 W 12 13'.split(),1),expected)
        with self.assertRaises(ValueError):
            original(['unknown'])
        with self.assertRaises(ValueError):
            native(['unknown'],1)
        with self.assertRaises(AssertionError):
            original(['query',0,'0x123456',0,0,0])

    def test_exact_binary_required(self):
        with self.assertRaises(ValueError):
            verify(b'',b'unsupported')

    def test_process_returns_are_retained_in_order(self):
        self.assertEqual(original(['result',1,0,'result',0,1]), [['R',1,0],['R',0,1]])
        self.assertEqual(native('o R 1 0 o R 0 1'.split(),1), [['R',1,0],['R',0,1]])


if __name__ == '__main__':
    unittest.main()
