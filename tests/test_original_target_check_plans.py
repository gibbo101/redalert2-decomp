"""Disposable-checker orchestration tests without proprietary inputs or tools."""
import contextlib
import io
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import check_plans


class CheckPlansTests(unittest.TestCase):
    def run_check(self, *, acceptance=0, build=0, rename=False, acceptance_report=None,
                  write_report=True, planned=1):
        previous = Path.cwd()
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            for name in ('src/shared', 'tools', 'manifests', 'private/original-target-20261020/inventory',
                         'build/class-work', 'headers'):
                (root / name).mkdir(parents=True, exist_ok=True)
            (root / 'tools/build-sentinel.txt').write_text('active tools, not HEAD')
            (root / 'manifests/original_target.json').write_text('{}')
            config = root / 'private/original-target.win.json'
            config.write_text('{}')
            spec = root / 'rename.json'
            spec.write_text('{}')
            (root / 'plan.json').write_text(json.dumps(dict(sources=[{}] * planned)))
            calls = []

            def execute(command, **kwargs):
                calls.append(command)
                result, stdout = 0, ''
                if command[:3] == ['git', 'worktree', 'add']:
                    Path(command[-2]).mkdir(parents=True)
                elif len(command) > 2 and command[2].endswith('accept_sources.py'):
                    result = acceptance
                    rows = acceptance_report if acceptance_report is not None else [
                        dict(candidates=1, accepted=int(not result), missed=[] if not result else ['fixture'])]
                    stdout = json.dumps(rows)
                    directory = Path(command[command.index('--output') + 1])
                    directory.mkdir(parents=True)
                    if write_report:
                        (directory / 'results.json').write_text(json.dumps(rows))
                elif len(command) > 2 and command[2].endswith('apply_rename.py'):
                    directory = Path(command[command.index('--output') + 1])
                    directory.mkdir()
                    (directory / 'receipt.json').write_text('{"verified_regions": 1}')
                    stdout = '{"verified_regions": 1}'
                elif len(command) > 2 and command[2].endswith('build.py'):
                    self.assertEqual((Path(kwargs['cwd']) / 'tools/build-sentinel.txt').read_text(),
                                     'active tools, not HEAD')
                    result = build
                    directory = Path(command[command.index('--output') + 1])
                    directory.mkdir()
                    (directory / 'assemble.log').write_text('assembler fixture diagnostic')
                    if not result:
                        (directory / 'build-receipt.json').write_text('{"whole_file_exact": true}')
                        stdout = '{"whole_file_exact": true}'
                return subprocess.CompletedProcess(command, result, stdout, 'failure' if result else '')

            def link_copy(source, destination):
                shutil.copytree(source, destination) if source.is_dir() else shutil.copy2(source, destination)

            arguments = ['check_plans.py', '--build', '--with-tools']
            arguments += ['--rename', str(spec)] if rename else []
            arguments += ['fixture', str(root / 'headers')]
            if not rename:
                arguments += ['plan.json']
            environment = dict(RA2_CONFIG=str(config), RA2_CHECK_ROOT=str(root / 'check-root'))
            try:
                with patch.object(check_plans, 'REPOSITORY', root), \
                     patch.object(check_plans.subprocess, 'run', side_effect=execute), \
                     patch.object(check_plans, 'link', side_effect=link_copy), \
                     patch.object(sys, 'argv', arguments), patch.dict(os.environ, environment), \
                     contextlib.redirect_stdout(io.StringIO()):
                    result = check_plans.main()
                base = root / 'build/check/fixture'
                receipt = base / 'check-build/build-receipt.json'
                evidence = dict(result=result, calls=calls, text=(base / 'results.txt').read_text(),
                                receipt=receipt.exists(),
                                assembly=(base / 'check-build/assemble.log').exists(),
                                renamed=(base / 'rename-check/receipt.json').exists())
                self.assertFalse((root / 'check-root/fixture').exists())
                return evidence
            finally:
                os.chdir(previous)

    def test_success_snapshots_active_tools_and_keeps_full_build_receipt(self):
        evidence = self.run_check()
        self.assertEqual(evidence['result'], 0)
        self.assertTrue(evidence['receipt'])
        self.assertIn('"whole_file_exact": true', evidence['text'])

    def test_build_failure_returns_nonzero_and_preserves_assembly_diagnostic(self):
        evidence = self.run_check(build=1)
        self.assertEqual(evidence['result'], 1)
        self.assertTrue(evidence['assembly'])
        self.assertFalse(evidence['receipt'])
        self.assertIn('exit_code: 1', evidence['text'])

    def test_failed_acceptance_does_not_prove_the_unchanged_tree(self):
        evidence = self.run_check(acceptance=1)
        self.assertEqual(evidence['result'], 1)
        self.assertFalse(evidence['receipt'])
        self.assertFalse(any(len(c) > 2 and c[2].endswith('build.py') for c in evidence['calls']))

    def test_zero_accepted_with_success_exit_and_empty_misses_stops_before_build(self):
        evidence = self.run_check(acceptance_report=[dict(candidates=1, accepted=0, missed=[])])
        self.assertEqual(evidence['result'], 1)
        self.assertIn('accepted 0 of 1 candidates', evidence['text'])
        self.assertFalse(any(len(c) > 2 and c[2].endswith('build.py') for c in evidence['calls']))

    def test_partial_acceptance_stops_before_build(self):
        evidence = self.run_check(acceptance_report=[dict(candidates=2, accepted=1, missed=[])], planned=2)
        self.assertEqual(evidence['result'], 1)
        self.assertFalse(evidence['receipt'])

    def test_absent_report_stops_before_build(self):
        evidence = self.run_check(write_report=False)
        self.assertEqual(evidence['result'], 1)
        self.assertIn('unreadable acceptance report', evidence['text'])
        self.assertFalse(evidence['receipt'])

    def test_report_must_cover_the_entire_plan(self):
        evidence = self.run_check(planned=2)
        self.assertEqual(evidence['result'], 1)
        self.assertIn('reported 1 candidates for 2 planned sources', evidence['text'])
        self.assertFalse(evidence['receipt'])

    def test_acceptance_report_validation_refuses_missing_or_invalid_counts(self):
        invalid = [[], {}, [dict(error='compile failed')], [dict(candidates=1, accepted=1)],
                   [dict(candidates=1, accepted=1, missed=['fixture'])],
                   [dict(candidates=True, accepted=True, missed=[])],
                   [dict(candidates=0, accepted=0, missed=[])],
                   [dict(candidates=-1, accepted=-1, missed=[])],
                   [dict(candidates=1, accepted='1', missed=[])]]
        for report in invalid:
            with self.subTest(report=report):
                self.assertIsNotNone(check_plans.acceptance_error(report, 1))
        self.assertIsNotNone(check_plans.acceptance_error([dict(candidates=1, accepted=1, missed=[])], 0))

    def test_multiple_complete_acceptance_rows_covering_plan_pass(self):
        evidence = self.run_check(planned=2, acceptance_report=[dict(candidates=1, accepted=1, missed=[])] * 2)
        self.assertEqual(evidence['result'], 0)
        self.assertTrue(evidence['receipt'])

    def test_rename_is_dry_run_then_real_audit_then_full_build_in_one_checkout(self):
        evidence = self.run_check(rename=True)
        self.assertEqual(evidence['result'], 0)
        rename_calls = [c for c in evidence['calls'] if len(c) > 2 and c[2].endswith('apply_rename.py')]
        self.assertEqual(len(rename_calls), 2)
        self.assertIn('--dry-run', rename_calls[0])
        self.assertNotIn('--dry-run', rename_calls[1])
        self.assertTrue(evidence['renamed'])
        self.assertTrue(evidence['receipt'])


if __name__ == '__main__':
    unittest.main()
