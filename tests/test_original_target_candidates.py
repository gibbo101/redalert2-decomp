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
