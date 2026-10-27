# SPDX-License-Identifier: GPL-3.0-or-later
"""Patch identity/output guards using synthetic data only; research Python needed."""
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import inspect_patch


class PatchInspectionTests(unittest.TestCase):
    def test_unknown_or_tampered_package_never_parsed(self):
        with patch.object(inspect_patch.pefile, 'PE') as parser:
            for data in (b'', b'MZ synthetic', bytes(1024)):
                with self.assertRaisesRegex(ValueError, 'Unsupported patch hash'):
                    inspect_patch.inspect(data)
            parser.assert_not_called()

    def test_source_and_public_output_refused(self):
        with tempfile.TemporaryDirectory(dir=ROOT / 'build') as folder:
            source = Path(folder) / 'package.exe'
            source.write_bytes(b'untouched source')
            with self.assertRaisesRegex(ValueError, 'outside the source'):
                inspect_patch.write_report(source, source.parent / 'report.json', {})
            with self.assertRaisesRegex(ValueError, 'private/ or build/'):
                inspect_patch.write_report(source, ROOT / 'report.json', {})
            self.assertEqual(source.read_bytes(), b'untouched source')
            self.assertFalse((source.parent / 'report.json').exists())
            self.assertFalse((ROOT / 'report.json').exists())

    def test_preserve_existing_and_refuse_symlinks(self):
        with tempfile.TemporaryDirectory(dir=ROOT / 'build') as folder:
            root = Path(folder)
            source = root / 'source' / 'package.exe'
            source.parent.mkdir()
            source.write_bytes(b'untouched source')
            output = root / 'research' / 'report.json'
            inspect_patch.write_report(source, output, {'patch_applied': False})
            original = output.read_bytes()
            with self.assertRaises(FileExistsError):
                inspect_patch.write_report(source, output, {'patch_applied': True})
            self.assertEqual(output.read_bytes(), original)
            link = root / 'link'
            link.symlink_to(output.parent, target_is_directory=True)
            with self.assertRaisesRegex(ValueError, 'Symlink'):
                inspect_patch.write_report(source, link / 'new.json', {})
            dangling = output.parent / 'dangling.json'
            dangling.symlink_to(source.parent / 'absent.json')
            with self.assertRaisesRegex(ValueError, 'Symlink'):
                inspect_patch.write_report(source, dangling, {})
            self.assertFalse((source.parent / 'absent.json').exists())


if __name__ == '__main__':
    unittest.main()
