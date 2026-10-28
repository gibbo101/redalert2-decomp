"""Candidate comparisons retain full extents and explicit binding refusals."""
from pathlib import Path
import sys
import tempfile
from types import SimpleNamespace
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]/'tools/original_target'))
from compile_candidates import compare_candidate, OPTIONS
from coff import Coff
from test_original_target_build import synthetic_object


class CandidateComparisonTests(unittest.TestCase):
    def compare(self, original, payload, references=None, relocation=None):
        with tempfile.TemporaryDirectory() as temp:
            obj=Path(temp)/'candidate.obj';obj.write_bytes(synthetic_object(payload, relocation))
            audit=SimpleNamespace(original=lambda va,size: original)
            candidate=dict(method='fixture',entry=0x401000,symbol_prefix='_fixture',source='private/fixture.cpp',
                           source_sha256='fixture',references=references or {},region_bytes=len(original))
            return compare_candidate(audit,Coff(obj.read_bytes()),candidate,obj,OPTIONS[0],0)

    def test_padding_is_part_of_full_comparison(self):
        self.assertEqual(self.compare(b'\xc3\x90',b'\xc3\x90')['status'],'extent-exact')
        result=self.compare(b'\xc3\x90',b'\xc3')
        self.assertEqual(result['status'],'mismatch')
        self.assertEqual(result['differing_bytes'],1)

    def test_unbound_relocation_refuses(self):
        result=self.compare(b'\xe8\0\0\0\0\xc3',b'\xe8\0\0\0\0\xc3',relocation=(1,20))
        self.assertEqual(result['status'],'comparison-refused')

    def test_resolved_binding_is_recorded_and_compared(self):
        result=self.compare(b'\xe8\xfb\x0f\0\0\xc3',b'\xe8\0\0\0\0\xc3',
                            references={'_target':0x402000},relocation=(1,20))
        self.assertEqual(result['status'],'extent-exact')
        self.assertEqual(result['relocations'][0]['resolved'],0xffb)
        wrong=self.compare(b'\xe8\xfb\x0f\0\0\xc3',b'\xe8\0\0\0\0\xc3',
                           references={'_target':0x402001},relocation=(1,20))
        self.assertEqual(wrong['status'],'mismatch')


if __name__=='__main__':unittest.main()


class RecordedTrialOptions(unittest.TestCase):
    def test_subset_and_default(self):
        from compile_candidates import OPTIONS, trial_options
        self.assertEqual(trial_options({}), OPTIONS)
        self.assertEqual(trial_options({'compiler_trial_options': [OPTIONS[0]]}), [OPTIONS[0]])

    def test_new_empty_duplicate_and_nonlist_options_refuse(self):
        from compile_candidates import OPTIONS, trial_options
        for value in [[], None, 'O2', [OPTIONS[0], OPTIONS[0]], [['/O2']], [tuple(OPTIONS[0])]]:
            with self.subTest(value=value), self.assertRaises(ValueError):
                trial_options({'compiler_trial_options': value})


class RetiredRegionTests(unittest.TestCase):
    """A plan may retire accepted regions that one of its items covers entirely."""
    def setUp(self):
        import accept_sources
        self.accept = accept_sources
        self.tail = dict(entry=0x4d0020, body_bytes=3, padding_bytes=13, full_extent_bytes=16,
                         symbol='?tail@@YAXXZ', source='src/recovered/tail.cpp', population='population-09')
        self.existing = {0x4d0020: self.tail}
        self.catalog = dict(regions=[self.tail, dict(entry=0x401000, source='x.cpp', relocations=[], references={})])
        self.plan = dict(retire=['004d0020'], sources=[dict(entry='004cffb0', body_bytes=115)])

    def test_covered_tail_is_retired(self):
        self.assertEqual(self.accept.retired_regions(self.plan, self.existing, self.catalog), {0x4d0020: self.tail})

    def test_refusals(self):
        retire = self.accept.retired_regions
        for change in (dict(retire=['004d0021']),                                    # no such region
                       dict(sources=[dict(entry='004cffb0', body_bytes=112)]),       # body does not reach the end of the tail
                       dict(sources=[dict(entry='004cffb0')]),                       # bound not stated
                       dict(sources=[dict(entry='004d0020', body_bytes=3)]),         # that is a replacement, not a retirement
                       dict(sources=[dict(entry='004d0030', body_bytes=115)])):      # plan item lies after the region
            with self.assertRaises(SystemExit, msg=str(change)):
                retire(dict(self.plan, **change), self.existing, self.catalog)

    def test_a_remaining_user_of_the_retired_symbol_refuses(self):
        self.catalog['regions'][1]['relocations'] = [dict(symbol='?tail@@YAXXZ')]
        with self.assertRaises(SystemExit):
            self.accept.retired_regions(self.plan, self.existing, self.catalog)

    def test_overlap_is_excused_only_for_a_wholly_covered_retired_region(self):
        from compile_candidates import covered_retired
        candidate = dict(entry=0x4cffb0, region_bytes=0x80)           # to 0x4d0030
        self.assertTrue(covered_retired(self.tail, candidate, {0x4d0020}))
        self.assertFalse(covered_retired(self.tail, candidate, set()))
        self.assertFalse(covered_retired(self.tail, dict(candidate, region_bytes=0x73), {0x4d0020}))   # padding left out
        self.assertFalse(covered_retired(dict(self.tail, entry=0x4cffb0), candidate, {0x4cffb0}))     # same entry
