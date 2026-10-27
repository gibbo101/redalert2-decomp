# SPDX-License-Identifier: GPL-3.0-or-later
import copy
import unittest
from unittest.mock import patch
from compare_owned_target_drawing import parse, validate, compare
from compare_original import PATCHED_EXPECTED
from original_owned_unit_world import OwnedUnitWorldOracle, UNIT, PARKED, CONTACTS
from original_shared_ground_world import SharedGroundWorldOracle
import test_owned_terrain_runtime_evidence as runtime_evidence
from types import SimpleNamespace
from tempfile import TemporaryDirectory
from pathlib import Path


class TargetDrawingEvidence(unittest.TestCase):
    def fixture(self):
        old, _, current = runtime_evidence.RuntimeEvidence().fixture()
        commands = [c for c in old['commands'] if c.split()[0] in ('P', 'O', 'I', 'J')]
        draw = next(c for c in old['commands'] if c.startswith('D ')).split()
        results = [{'tokens': []} for c in commands]
        tail = ['draw-target', '0', '-1', '-1', 'draw-target', '1', '-1', '-1']
        results[2]['tokens'] = tail.copy()
        results[3]['tokens'] = tail.copy()
        for a, b in ((False, False), (True, False), (False, True), (True, True)):
            for id, present in enumerate((a, b)):
                x, y = (12, 12) if present else (-1, -1)
                commands.append(f'Y {id} {x} {y}')
                tail[id*4+2:id*4+4] = map(str, (x, y))
                results.append({'tokens': tail.copy()})
            for id in (0, 1):
                draw[1] = str(id)
                commands.append(' '.join(draw))
                results.append({'tokens': tail.copy()})
        proof = {'evidence_mode': 'fresh-original', 'identities': current,
                 'supplied_targets_on_actual_owners': True,
                 'targets_preserved_before_and_after_binding': True, 'actual_Process_roots': 0}
        e = {'executable_sha256': PATCHED_EXPECTED, 'profile': 'supplied-ra2-1006',
             'evidence': proof, 'commands': commands, 'expected': results, 'labels': ['draw']*len(commands)}
        return e, {**proof, 'expectations_sha256': 'fingerprint'}, current

    def test_complete_scope_and_observations(self):
        e, r, c = self.fixture()
        validate(e, r, 'fingerprint', c)

    def test_no_movement_invalid_target_or_contact(self):
        for command in ('Y', 'Y 0 12', 'Y 2 1 1', 'Y 0 -1 1', 'Y 0 512 0',
                        'Y 0 0 0 extra', 'H 101', 'T 0 101', 'M 0 100 384 384 0 1 2'):
            with self.subTest(command=command), self.assertRaises(ValueError):
                parse(command)
        e, _, _ = self.fixture()
        draw = next(c for c in e['commands'] if c.startswith('D ')).split()
        draw[3] = '1'
        with self.assertRaises(ValueError):
            parse(' '.join(draw))

    def test_missing_scope_observations_and_receipt_fail(self):
        for mutation in ('scope', 'original', 'target', 'counts', 'initialization', 'receipt', 'identity', 'coverage'):
            e, r, c = copy.deepcopy(self.fixture())
            if mutation == 'scope':
                e['evidence']['targets_preserved_before_and_after_binding'] = r['targets_preserved_before_and_after_binding'] = False
            elif mutation == 'original':
                e['evidence']['actual_Process_roots'] = r['actual_Process_roots'] = 1
            elif mutation == 'target':
                e['expected'][-1]['tokens'][-1] = '-1'
            elif mutation == 'counts':
                e['labels'].pop()
            elif mutation == 'initialization':
                e['commands'][0] = 'Y 0 -1 -1'
            elif mutation == 'receipt':
                r['expectations_sha256'] = 'wrong'
            elif mutation == 'identity':
                c = {}
            else:
                for key in ('commands', 'expected', 'labels'):
                    del e[key][-4:]
            with self.subTest(mutation=mutation), self.assertRaises(ValueError):
                validate(e, r, 'fingerprint', c)

    def owner(self):
        o = OwnedUnitWorldOracle.__new__(OwnedUnitWorldOracle)
        o.values = {UNIT+0x494: 123, PARKED+0x494: 456, CONTACTS: 0}
        o.get_own = o.values.__getitem__
        return o

    def test_binding_preserves_actual_targets(self):
        o = self.owner()
        before = o.values.copy()
        o.bind_draw_target(0)
        self.assertEqual(o.values, before)

    def test_contact_mismatch_is_refused_without_repair(self):
        for contact, actual in ((1, 0), (0, 123)):
            o = self.owner()
            o.values[CONTACTS] = actual
            before = o.values.copy()
            with self.assertRaises(AssertionError):
                o.bind_draw_target(contact)
            self.assertEqual(o.values, before)

    def test_guard_covers_pre_original_binding_writes(self):
        o = self.owner()
        def clear_before_snapshot(self, *args):
            self.values[UNIT+0x494] = 0
            return []
        with patch.object(SharedGroundWorldOracle, 'draw_shared', clear_before_snapshot):
            with self.assertRaises(AssertionError):
                o.draw_shared(0, 100, [])

    def test_guard_preserves_original_exception(self):
        o = self.owner()
        with patch.object(SharedGroundWorldOracle, 'draw_shared', side_effect=RuntimeError('draw fault')):
            with self.assertRaisesRegex(RuntimeError, 'draw fault'):
                o.draw_shared(0, 100, [])

    def test_initial_placement_prefix_is_not_drawing_output(self):
        e, _, _ = self.fixture()
        e['expected'][2]['tokens'].insert(0, 'actor-state')
        e['expected'][3]['tokens'].insert(0, 'actor-state')
        for command, result in zip(e['commands'], e['expected']):
            if command.startswith('Y '):
                result['tokens'].insert(0, 'actor-state')
        rows = [' '.join((['F', '128', '128', '0'] if c.startswith('I ') else [])+r['tokens'])
                for c, r in zip(e['commands'], e['expected'])]
        proc = SimpleNamespace(returncode=0, stdout='\n'.join(rows)+'\n',
            stderr='Owned world guards: 6; unknown actor: 1; warm clone pairs: 0; actual Advance6/7 clone refusals: 0: PASS\n')
        with TemporaryDirectory() as folder, patch('compare_owned_target_drawing.native_args', return_value=[]), \
                patch('compare_owned_target_drawing.subprocess.run', return_value=proc):
            compare(None, e['commands'], e['expected'], Path(folder)/'native')
            at = next(i for i, c in enumerate(e['commands']) if c.startswith('D '))
            rows[at] = 'discarded '+rows[at]
            proc.stdout = '\n'.join(rows)+'\n'
            with self.assertRaises(AssertionError):
                compare(None, e['commands'], e['expected'], Path(folder)/'native')


if __name__ == '__main__':
    unittest.main()
