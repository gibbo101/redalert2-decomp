# SPDX-License-Identifier: GPL-3.0-or-later
"""Research profile isolation: no original bytes or instruction execution."""
from pathlib import Path
from types import SimpleNamespace
import tempfile
import unittest
from unittest.mock import patch

from compare_original import EXPECTED, PATCHED_EXPECTED
from movement_profiles import address, movement_profile
from movement_evidence import prepare, validate_cached, validate_receipt, check_replay_destination
from original_movement import Oracle
from verify_movement_mapping import verify

ROOT = Path(__file__).resolve().parents[1]


class MovementProfileTests(unittest.TestCase):
    def test_unknown_bytes_fail_before_mapping_or_execution(self):
        for data in (b'', b'MZ unknown engine', bytes(4096)):
            for enabled in (False, True):
                with self.assertRaisesRegex(ValueError, 'Unsupported executable hash'):
                    movement_profile(data, allow_patched=enabled)
            with self.assertRaisesRegex(ValueError, 'SHA-256'):
                verify(data, data)
        with tempfile.TemporaryDirectory(dir=ROOT/'build') as folder:
            source = Path(folder)/'game.exe'
            source.write_bytes(b'MZ unknown engine')
            with self.assertRaisesRegex(ValueError, 'Unsupported executable hash'):
                Oracle(source)

    def test_patched_selection_is_explicit_and_default_stays_disc_only(self):
        # Selector-only fixtures mock a digest; no fabricated PE reaches Unicorn.
        with patch('movement_profiles.hashlib.sha256', return_value=SimpleNamespace(hexdigest=lambda: PATCHED_EXPECTED)):
            with self.assertRaises(ValueError):
                movement_profile(b'synthetic selector')
            self.assertEqual(movement_profile(b'synthetic selector', allow_patched=True),
                             (PATCHED_EXPECTED, 'supplied-ra2-1006'))
        with patch('movement_profiles.hashlib.sha256', return_value=SimpleNamespace(hexdigest=lambda: EXPECTED)):
            self.assertEqual(movement_profile(b'synthetic selector'), (EXPECTED, 'allied-disc'))

    def test_no_generic_relocation_or_unknown_profile(self):
        self.assertEqual(address('allied-disc', 0x4A01C0), 0x4A01C0)
        self.assertEqual(address('supplied-ra2-1006', 0x4A01C0), 0x4A05F0)
        for name, va in (('unknown', 0x4A01C0), ('supplied-ra2-1006', 0x4A01C1)):
            with self.assertRaises(ValueError):
                address(name, va)

    def test_native_input_requires_retained_disc_identity(self):
        with tempfile.TemporaryDirectory(dir=ROOT/'build') as folder:
            source = Path(folder)/'game.exe'
            source.write_bytes(b'synthetic engine')
            args = SimpleNamespace(exe=source, native_data_exe=None)
            with patch('movement_evidence.movement_profile', return_value=(PATCHED_EXPECTED, 'supplied-ra2-1006')):
                with self.assertRaisesRegex(ValueError, 'Native vectors still require'):
                    prepare(args, 'movement')

    def test_cached_source_profile_and_prepared_input_identities(self):
        current = {'executable_sha256': PATCHED_EXPECTED, 'profile': 'supplied-ra2-1006',
                   'native_data_executable_sha256': EXPECTED,
                   'oracle_sources': {'oracle.py': 'current'}, 'mapping_tool_sha256': 'mapping',
                   'direction_data_sha256': 'direction'}
        evidence = {'executable_sha256': PATCHED_EXPECTED, 'profile': 'supplied-ra2-1006',
                    'evidence': dict(current)}
        validate_cached(evidence, current)
        for field in current:
            changed = {**current, field: 'other identity'}
            with self.assertRaisesRegex(ValueError, 'identity differs'):
                validate_cached(evidence, changed)

    def test_cached_payload_requires_fresh_original_receipt(self):
        evidence = {'evidence': {'evidence_mode': 'fresh-original', 'matched': 2}}
        receipt = {**evidence['evidence'], 'expectations_sha256': 'recorded'}
        validate_receipt(evidence, receipt, 'recorded')
        for changed in ({**receipt, 'expectations_sha256': 'changed'},
                        {**receipt, 'evidence_mode': 'cached-original-replay'},
                        {**receipt, 'matched': 1}):
            with self.assertRaises(ValueError):
                validate_receipt(evidence, changed, 'recorded')

    def test_replay_cannot_replace_original_evidence(self):
        with tempfile.TemporaryDirectory(dir=ROOT/'build') as folder:
            expectations = Path(folder)/'expected.json'
            receipt = Path(folder)/'report.json'
            receipt.write_text('{"evidence_mode":"fresh-original"}')
            alternate = Path(folder)/'another-original.json'
            alternate.write_bytes(receipt.read_bytes())
            for target in (expectations, receipt, alternate):
                with self.assertRaisesRegex(ValueError, 'cannot replace'):
                    check_replay_destination(target, expectations, receipt)
            check_replay_destination(Path(folder)/'replay.json', expectations, receipt)
            self.assertEqual(receipt.read_text(), '{"evidence_mode":"fresh-original"}')
            self.assertFalse(expectations.exists())

if __name__ == '__main__':
    unittest.main()
