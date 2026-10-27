# SPDX-License-Identifier: GPL-3.0-or-later
"""Archive evidence guards using authored inputs; no original instructions."""
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

from archive_profiles import archive_profile, address, EXPECTED, PATCHED_EXPECTED
from compare_archive import validate_cached
from presentation_evidence import validate_receipt, check_replay_destination, private_path

ROOT = Path(__file__).resolve().parents[1]


class ArchiveProfileTests(unittest.TestCase):
    def test_only_exact_engine_hashes_select_profiles(self):
        for data in (b'', b'MZ unknown archive engine', bytes(4096)):
            with self.assertRaisesRegex(ValueError, 'SHA-256'):
                archive_profile(data)
        for digest, profile in ((EXPECTED, 'allied-disc'), (PATCHED_EXPECTED, 'supplied-ra2-1006')):
            with patch('archive_profiles.hashlib.sha256', return_value=SimpleNamespace(hexdigest=lambda: digest)):
                self.assertEqual(archive_profile(b'authored selector fixture'), (digest, profile))

    def test_explicit_mapping_required(self):
        self.assertEqual(address('supplied-ra2-1006', 0x592750), 0x595aa0)
        for profile, va in (('unknown', 0x592750), ('supplied-ra2-1006', 0x592751)):
            with self.assertRaises(ValueError):
                address(profile, va)

    def test_cached_sources_engine_and_fixture_identity(self):
        current = {'executable_sha256': PATCHED_EXPECTED, 'profile': 'supplied-ra2-1006',
                   'sources': {'oracle': 'a'}, 'fixtures': {'plaintext': 'b'}}
        evidence = {'executable_sha256': PATCHED_EXPECTED, 'profile': 'supplied-ra2-1006',
                    'evidence': dict(current)}
        validate_cached(evidence, current)
        for key in current:
            with self.assertRaisesRegex(ValueError, 'identity differs'):
                validate_cached(evidence, {**current, key: 'changed'})
        for key in ('executable_sha256', 'profile'):
            with self.assertRaisesRegex(ValueError, 'envelope identity differs'):
                validate_cached({**evidence, key: 'changed'}, current)

    def test_fresh_receipt_and_fingerprint_required(self):
        report = {'evidence_mode': 'fresh-original', 'cases': 5344}
        evidence = {'evidence': report}
        receipt = {**report, 'expectations_sha256': 'recorded'}
        validate_receipt(evidence, receipt, 'recorded')
        for bad in ({**receipt, 'expectations_sha256': 'changed'},
                    {**receipt, 'evidence_mode': 'cached-original-replay'}, {**receipt, 'cases': 5343}):
            with self.assertRaises(ValueError):
                validate_receipt(evidence, bad, 'recorded')

    def test_private_replay_preserves_original_receipts_and_source(self):
        with tempfile.TemporaryDirectory(dir=ROOT/'build') as folder:
            work = Path(folder)
            source = work/'install'/'game.exe'; source.parent.mkdir(); source.write_bytes(b'authored fixture')
            expected, receipt = work/'expected.json', work/'report.json'
            receipt.write_text('{"evidence_mode":"fresh-original"}')
            for destination in (expected, receipt):
                with self.assertRaisesRegex(ValueError, 'cannot replace'):
                    check_replay_destination(destination, expected, receipt)
            for destination in (source, source.parent/'report.json', ROOT/'public-report.json'):
                with self.assertRaises(ValueError):
                    private_path(destination, source)
            check_replay_destination(work/'replay.json', expected, receipt)
            self.assertEqual(source.read_bytes(), b'authored fixture')


if __name__ == '__main__':
    unittest.main()
