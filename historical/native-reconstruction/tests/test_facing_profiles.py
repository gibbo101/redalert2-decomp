# SPDX-License-Identifier: GPL-3.0-or-later
"""Fail-closed Facing identities and private evidence preservation; no game bytes."""
import tempfile
import unittest
from pathlib import Path

from compare_original import EXPECTED, PATCHED_EXPECTED, facing_profile, write_report
from original_movement import EXPECTED as MOVEMENT_EXPECTED

ROOT = Path(__file__).resolve().parents[1]


class FacingProfileTests(unittest.TestCase):
    def test_unknown_hash_rejected_and_movement_keeps_its_disc_gate(self):
        for data in (b'', b'MZ unknown engine', bytes(4096)):
            with self.assertRaisesRegex(ValueError, 'SHA-256 differs'):
                facing_profile(data)
        self.assertEqual(MOVEMENT_EXPECTED, EXPECTED)
        self.assertNotEqual(MOVEMENT_EXPECTED, PATCHED_EXPECTED)

    def test_report_cannot_replace_source_public_or_other_profile(self):
        with tempfile.TemporaryDirectory(dir=ROOT / 'build') as folder:
            source = Path(folder) / 'input' / 'game.exe'
            source.parent.mkdir()
            source.write_bytes(b'owned synthetic source')
            report = {'executable_sha256': EXPECTED}
            for destination in (source, source.parent / 'report.json', ROOT / 'report.json'):
                with self.assertRaises(ValueError):
                    write_report(source, destination, report)
            destination = Path(folder) / 'report.json'
            write_report(source, destination, report)
            before = destination.read_bytes()
            with self.assertRaisesRegex(ValueError, 'another executable'):
                write_report(source, destination, {'executable_sha256': PATCHED_EXPECTED})
            self.assertEqual(destination.read_bytes(), before)
            self.assertEqual(source.read_bytes(), b'owned synthetic source')

    def test_report_symlink_and_malformed_evidence_preserved(self):
        with tempfile.TemporaryDirectory(dir=ROOT / 'build') as folder:
            source = Path(folder) / 'input' / 'game.exe'
            source.parent.mkdir()
            source.write_bytes(b'owned synthetic source')
            destination = Path(folder) / 'report.json'
            destination.write_text('incomplete evidence')
            with self.assertRaises(ValueError):
                write_report(source, destination, {'executable_sha256': EXPECTED})
            self.assertEqual(destination.read_text(), 'incomplete evidence')
            link = Path(folder) / 'link'
            link.symlink_to(source.parent, target_is_directory=True)
            with self.assertRaisesRegex(ValueError, 'Symlink'):
                write_report(source, link / 'new.json', {'executable_sha256': EXPECTED})
            self.assertFalse((source.parent / 'new.json').exists())


if __name__ == '__main__':
    unittest.main()
