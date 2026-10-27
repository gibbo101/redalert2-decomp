# SPDX-License-Identifier: GPL-3.0-or-later
import unittest
from collections import Counter
from types import SimpleNamespace
from unittest.mock import patch
from compare_owned_scatter_world import parse, validate_stream, identities
from original_owned_scatter_world import AttachedScatterProcesses, OwnedScatterWorldOracle
from original_owned_orders_world import OwnedOrdersWorldOracle
from original_owned_unit_processes import AttachedProcesses, ACTOR_WRITES, DRIVE_WRITES, DRIVES


class ScatterGuestGuards(unittest.TestCase):
    def guest(self, cls=AttachedScatterProcesses):
        m = object.__new__(cls)
        m.installing = False; m.actor = 0; m.destination_scope = None
        m.wait_stores = Counter(); m.scatter_counts = Counter()
        return m

    def test_legacy_field_and_inactive_owner_boundaries(self):
        m = self.guest(AttachedProcesses)
        self.assertEqual(m.actor_fields(0), ACTOR_WRITES)
        self.assertEqual(m.actor_fields(1), ((0x30,4),))
        self.assertEqual(m.drive_fields(0), DRIVE_WRITES)
        self.assertEqual(m.drive_fields(1), ())
        m.actor_store_guard(1, 0x30, 4, 0)
        for id, off in ((1,0x494), (1,0x88)):
            with self.subTest(off=off), self.assertRaises(AssertionError):
                m.actor_store_guard(id, off, 4, 0x4c8047)
        with self.assertRaises(AssertionError): m.drive_store_guard(1, 0x34, 4, 0x49fe89)

    def test_destination_scope_requires_actual_actor_and_store_site(self):
        m = self.guest(); m.actor = 1; m.destination_scope = (1,2,3)
        m.actor_store_guard(1, 0x494, 4, 0x4c8047)
        for id, off, n, ip in ((0,0x494,4,0x4c8047),(1,0x490,4,0x4c8047),
                               (1,0x494,1,0x4c8047),(1,0x494,4,0),(1,0x88,4,0x4c8047)):
            with self.subTest(case=(id,off,n,ip)), self.assertRaises(AssertionError):
                m.actor_store_guard(id, off, n, ip)
        m.drive_store_guard(1, 0x34, 4, 0x49fe89)
        for id, off, n, ip in ((0,0x34,4,0x49fe89),(1,0x40,4,0x49fe89),(1,0x34,8,0x49fe89),(1,0x34,4,0)):
            with self.subTest(case=(id,off,n,ip)), self.assertRaises(AssertionError):
                m.drive_store_guard(id, off, n, ip)

    def test_destination_wait_stores_do_not_widen_ordinary_wait(self):
        m = self.guest()
        m.actor_store_guard(0, 0x558, 4, 0x4a367d)
        with self.assertRaises(AssertionError): m.actor_store_guard(0,0x558,4,0x4c81ea)
        m.destination_scope = (1,2,3)
        m.actor_store_guard(0, 0x558, 4, 0x4c81ea)
        with self.assertRaises(AssertionError): m.actor_store_guard(0,0x558,4,0x4a367d)

    def test_counter_and_terminal_clear_are_narrow(self):
        m = self.guest()
        m.actor_store_guard(0,0x53c,4,0x4a32b7)
        self.assertEqual(m.scatter_counts['actual.counter.0'],1)
        m.actor_store_guard(0,0x494,4,0x4cd9b8)
        for id, off, n, ip in ((1,0x53c,4,0x4a32b7),(0,0x53c,1,0x4a32b7),
                               (0,0x53c,4,0),(1,0x494,4,0x4cd9b8),(0,0x490,4,0x4cd9b8)):
            with self.subTest(case=(id,off,n,ip)), self.assertRaises(AssertionError):
                m.actor_store_guard(id, off, n, ip)

    def test_scatter_profile_retains_other_admission_exclusions(self):
        self.assertEqual(AttachedScatterProcesses.excluded_branches, AttachedProcesses.excluded_branches)
        self.assertIn(0x4a3ab5, AttachedScatterProcesses.unsupported_entries)
        self.assertIn(0x476920, AttachedProcesses.unsupported_entries)

    def test_no_diagnostic_position_or_target_supply_in_interaction(self):
        for command in ('K 0 0 0 0 0 0 0 0','Y 0 1 1','X 0','T 0 100','F 0 100',
                        'H','H 100','H 4097','H 101 trailing',''):
            with self.subTest(command=command), self.assertRaises((ValueError,AssertionError)):
                parse(command)
        self.assertEqual(parse('H 101'),('H',101))

    def test_snapshot_release_does_not_call_loader_free(self):
        o = object.__new__(OwnedScatterWorldOracle)
        o.movement = SimpleNamespace(active=True, cell_scope=(1,2,3), hooks={0x781d3b: None})
        with patch.object(OwnedOrdersWorldOracle, 'hook') as loader:
            o.hook(None, 0x781d3b, 1, None)
            loader.assert_not_called()
            o.movement.active = False
            o.hook(None, 0x781d3b, 1, None)
            loader.assert_called_once()
        o.movement.active = True; o.movement.cell_scope = None
        with self.assertRaises(AssertionError): o.hook(None,0x781d3b,1,None)

    def test_only_initial_preparation_can_supply_positive_routing(self):
        m = self.guest(); m.u = SimpleNamespace(reg_read=lambda r: 0x1100000)
        m.get = lambda p: 0x4a3a0a
        m.owner = SimpleNamespace(supply_route=lambda *a: self.fail('moving-wait cannot route'))
        with patch.object(AttachedProcesses, 'pathfinder', return_value=0) as failed:
            self.assertEqual(m.pathfinder(), 0)
            failed.assert_called_once()
        self.assertEqual(m.scatter_counts['supplied.failed_route.0'], 1)
        m.get = lambda p: 0x4a3f4a
        with self.assertRaises(AssertionError): m.pathfinder()

    def test_duplicate_terminal_driving_store_is_exact_and_scoped(self):
        m = self.guest(); m.active = True; m.unit_scope = m.cell_scope = None
        m.drive_store_sites = Counter(); m.events = []
        u = SimpleNamespace(reg_read=lambda reg: 0x4a2249)
        m.store(u, 0, DRIVES[0]+0x63, 1, 0, None)
        self.assertEqual(m.drive_store_sites['0x4a2249'], 1)
        for p,n in ((DRIVES[1]+0x63,1),(DRIVES[0]+0x62,1),(DRIVES[0]+0x63,4)):
            with self.subTest(p=p,n=n), self.assertRaises(AssertionError):
                m.store(u,0,p,n,0,None)
        m.cell_scope = (1,2,3)
        with self.assertRaises(AssertionError): m.store(u,0,DRIVES[0]+0x63,1,0,None)


class ScatterEvidenceGuards(unittest.TestCase):
    def fixture(self):
        commands = ['P 0', 'O 0', 'I 0', 'J 0']
        targets = [[-1,-1,0],[-1,-1,0]]
        def state(arrived=False):
            return ['actor-state','0','2944','3200','0','actor-state','1',
                    *map(str, (3200,2944,0) if arrived else (3456,3200,0)),
                    *[str(v) for id in (0,1) for v in ('scatter-state',id,*targets[id])]]
        expected = [{'tokens':[]},{'tokens':[]},{'state':state()},{'state':state()}]
        def draw():
            for id in (0,1):
                commands.append(f'D {id}')
                expected.append({'tokens':['actor',str(id),'surface','world',*state(len(commands)>100)]})
        draw()
        for tick in range(101,229):
            if tick == 112: targets[1] = [12,11,0]
            if tick == 145: targets[1] = [-1,-1,0]
            commands.append(f'H {tick}'); expected.append({'state':state(tick>=145)})
            if tick == 112: draw()
        draw()
        proof = {'process_counts':{'0':128,'1':128}, 'actual_Process_entries':{'0':128,'1':128},
                 'supplied_separate_Drive_height_divisor':104,
                 'draws':6, 'scatter_destinations':[[112,1,3200,2944,0]],
                 'actual_terminal_drive_store_sites':dict.fromkeys(('0x4a21fb','0x4a2203','0x4a220c','0x4a2249'),1),
                 'child_counts':{'actual.Cell.0x4a32b4':1,'actual.Unit.1':1,'actual.nearby.1':1,
                                 'actual.counter.0':1,'actual.destination.1':1,'supplied.snapshot_growth':1,
                                 'supplied.snapshot_release':1,'supplied.atomic.1':3,'supplied.atomic.-1':3}}
        return commands,expected,['supplied_flat_two_tank_encounter']*len(commands),proof

    def check(self, values):
        real_parse = parse
        # Compact records replace unrelated numeric fixture inputs in this
        # validator-only test; scheduling/owner/target/arrival records are real.
        def compact(command):
            op,*values = command.split()
            if op in ('H',): return real_parse(command)
            return op, tuple(map(int,values))
        with patch('compare_owned_scatter_world.parse', side_effect=compact):
            validate_stream(*values)

    def test_actual_arrival_and_drawing_stream_pass(self):
        self.check(self.fixture())

    def test_missing_or_relabelled_coverage_fails(self):
        for field in ('process_counts','actual_Process_entries','draws','scatter_destinations','child_counts',
                      'supplied_separate_Drive_height_divisor','actual_terminal_drive_store_sites'):
            with self.subTest(field=field):
                data = self.fixture(); data[3].pop(field)
                with self.assertRaises(ValueError): self.check(data)
        data = self.fixture(); data[2][-1] = 'other'
        with self.assertRaises(ValueError): self.check(data)

    def test_destination_must_be_reached_and_visible_in_middle_draws(self):
        data = self.fixture(); tokens = data[1][-1]['tokens']
        at = next(i for i,v in enumerate(tokens) if v == 'actor-state' and tokens[i+1] == '1')
        tokens[at+2] = '9999'
        with self.assertRaises(ValueError): self.check(data)
        data = self.fixture()
        middle = [i for i,c in enumerate(data[0]) if c.startswith('D ')][2]
        data[1][middle]['tokens'][-3:-1] = ['-1','-1']
        with self.assertRaises(ValueError): self.check(data)

    def test_missing_process_tick_and_duplicate_owner_fail(self):
        data = self.fixture(); data[0][data[0].index('H 121')] = 'H 122'
        with self.assertRaises(ValueError): self.check(data)
        data = self.fixture(); data[1][-1]['tokens'].extend(['scatter-state','1','-1','-1','0'])
        with self.assertRaises(ValueError): self.check(data)

    def test_transitive_inspection_sources_are_identified(self):
        with patch('compare_owned_scatter_world.runtime.identities', return_value={}), \
             patch('compare_owned_scatter_world.hash_file', return_value='test'):
            sources = identities(None)['python_sources']
        self.assertIn('tools/verify_process_preparation_scatter.py', sources)
        self.assertIn('tools/verify_nearby_location_map.py', sources)


if __name__ == '__main__': unittest.main()
