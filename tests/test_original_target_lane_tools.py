"""Lane helper tests on synthetic catalog rows; no proprietary inputs or tools."""
import json
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import lane_tools


def region(entry, order, population='population-1', source=None):
    return dict(entry=entry, source_order=order, population=population, symbol_prefix='?f%x@@YAXXZ' % entry,
                source=source or 'src/recovered/f_%08x.cpp' % entry)


class LaneToolsTests(unittest.TestCase):
    def test_plan_keeps_population_order_and_inserts_by_address(self):
        regions = [region(0x500020, 1), region(0x500000, 0), region(0x600000, 0, 'population-2')]
        copies = []
        population, plan = lane_tools.build_plan(
            regions, '500000', 'lane', [('500020', 'w/a.cpp', ''), ('500010', 'w/b.cpp', '?b@@YAXXZ')],
            'p/lane', copy=lambda a, b: copies.append((a, str(b))))
        self.assertEqual(population, 'population-1')
        self.assertEqual([s['entry'] for s in plan['sources']], ['00500000', '00500010', '00500020'])
        self.assertEqual(plan['sources'][2]['draft'], 'w/a.cpp')
        self.assertEqual(plan['sources'][1]['symbol_prefix'], '?b@@YAXXZ')
        self.assertEqual(plan['sources'][0]['draft'], 'p/lane/f_00500000.cpp')
        self.assertEqual(len(copies), 2)
        self.assertEqual(plan['options'], lane_tools.DEFAULT_OPTIONS)

    def test_plan_takes_population_option_sets(self):
        o1 = ['/O1', '/Ob2', '/G5', '/Gy']
        regions = [region(0x500000, 0), dict(region(0x500020, 1), options=o1)]
        regions[0]['options'] = lane_tools.DEFAULT_OPTIONS[0]
        _, plan = lane_tools.build_plan(regions, '500000', 'lane', [], 'p', copy=lambda a, b: None)
        self.assertEqual(plan['options'], [lane_tools.DEFAULT_OPTIONS[0], o1])
        self.assertTrue(plan['separate_units'])

    def test_plan_refuses_unaccepted_anchor(self):
        with self.assertRaises(SystemExit):
            lane_tools.build_plan([region(0x500000, 0)], '500010', 'lane', [], 'p', copy=lambda a, b: None)

    def test_freeze_names_new_sources_and_writes_lf(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            (root / 'a.cpp').write_text('int a;\n')
            (root / 'b.cpp').write_text('int b;\n')
            plan = dict(name='old', sources=[
                dict(entry='00500000', draft=str(root / 'a.cpp'), source='src/recovered/f_00500000.cpp'),
                dict(entry='00500010', draft=str(root / 'b.cpp'), source='src/recovered/x_00500010.cpp')])
            path = lane_tools.freeze_plan(plan, root / 'd/r1', 'lane-r1', {'500010': 'classes/Foo/Foo_Bar_00500010.cpp'})
            written = json.loads(path.read_text())
            self.assertNotIn(b'\r\n', path.read_bytes())
            self.assertEqual(written['name'], 'lane-r1')
            self.assertEqual(written['sources'][1]['source'], 'src/recovered/classes/Foo/Foo_Bar_00500010.cpp')
            self.assertEqual(written['sources'][1]['semantic_name'], 'Foo_Bar_00500010')
            self.assertTrue((root / 'd/r1/unit/Foo_Bar_00500010.cpp').exists())
            self.assertEqual(plan['name'], 'old')

    def test_summarize_prefers_exact_and_reports_compile_errors(self):
        row = dict(options=['/O2'], status='mismatch', score=99.5, shape_score=100.0, original_instructions=10,
                   candidate_instructions=10, unresolved=[])
        exact = dict(row, status='byte-exact', score=98.0)
        self.assertEqual(lane_tools.summarize(dict(results=[row, exact]))['status'], 'byte-exact')
        failed = lane_tools.summarize(dict(results=[dict(options=['/O2'], status='compile-failed')]),
                                      'x.cpp(3) : error C2065: undeclared\n')
        self.assertEqual((failed['score'], failed['status']), (-1.0, 'compile-failed'))
        self.assertIn('C2065', failed['detail'])
        self.assertEqual(lane_tools.summarize(None)['status'], 'no-result')


if __name__ == '__main__':
    unittest.main()
