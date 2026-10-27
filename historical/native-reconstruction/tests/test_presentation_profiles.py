# SPDX-License-Identifier: GPL-3.0-or-later
"""Presentation migration/profile/receipt guards; no original execution."""
from pathlib import Path
from types import SimpleNamespace
import tempfile
import unittest
from unittest.mock import patch

from compare_original import EXPECTED, PATCHED_EXPECTED
from presentation_profiles import address, presentation_profile
from presentation_evidence import (prepare, private_path, validate_cached,
    validate_receipt, check_replay_destination)
from original_presentation import PresentationOracle
from original_raster import RasterOracle
from verify_presentation_mapping import verify

ROOT=Path(__file__).resolve().parents[1]

class PresentationProfileTests(unittest.TestCase):
    def test_unknown_hashes_fail_before_mapping_or_execution(self):
        for data in (b'',b'MZ unknown engine',bytes(4096)):
            for enabled in (False,True):
                with self.assertRaisesRegex(ValueError,'Unsupported executable hash'):
                    presentation_profile(data,allow_patched=enabled)
            with self.assertRaisesRegex(ValueError,'SHA-256'):
                verify(data,data)
        with tempfile.TemporaryDirectory(dir=ROOT/'build') as folder:
            source=Path(folder)/'game.exe';source.write_bytes(b'MZ unknown engine')
            for oracle in (PresentationOracle,RasterOracle):
                with self.assertRaisesRegex(ValueError,'Unsupported executable hash'):
                    oracle(source)

    def test_patched_selection_requires_explicit_opt_in(self):
        with patch('presentation_profiles.hashlib.sha256',return_value=SimpleNamespace(hexdigest=lambda:PATCHED_EXPECTED)):
            with self.assertRaises(ValueError):presentation_profile(b'selector fixture')
            self.assertEqual(presentation_profile(b'selector fixture',allow_patched=True),(PATCHED_EXPECTED,'supplied-ra2-1006'))
            with tempfile.TemporaryDirectory(dir=ROOT/'build') as folder:
                source=Path(folder)/'game.exe';source.write_bytes(b'selector fixture')
                # Rejection occurs before PE parsing/Unicorn allocation in both.
                for oracle in (PresentationOracle,RasterOracle):
                    with self.assertRaises(ValueError):oracle(source)
        with patch('presentation_profiles.hashlib.sha256',return_value=SimpleNamespace(hexdigest=lambda:EXPECTED)):
            self.assertEqual(presentation_profile(b'selector fixture'),(EXPECTED,'allied-disc'))

    def test_no_blanket_offset_or_unknown_profile(self):
        self.assertEqual(address('supplied-ra2-1006',0x710480),0x71BA20)
        self.assertEqual(address('supplied-ra2-1006',0x487750),0x487970)
        self.assertEqual(address('allied-disc',0x710480),0x710480)
        for name,va in (('unknown',0x710480),('supplied-ra2-1006',0x710481)):
            with self.assertRaises(ValueError):address(name,va)

    def test_retained_native_data_identity_is_required(self):
        with tempfile.TemporaryDirectory(dir=ROOT/'build') as folder:
            source=Path(folder)/'game.exe';source.write_bytes(b'synthetic engine')
            args=SimpleNamespace(exe=source,native_data_exe=None)
            with patch('presentation_evidence.presentation_profile',return_value=(PATCHED_EXPECTED,'supplied-ra2-1006')):
                with self.assertRaisesRegex(ValueError,'Retained native render inputs'):
                    prepare(args)

    def test_cached_sources_profile_and_data_are_checked(self):
        current={'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                 'native_data_executable_sha256':EXPECTED,'oracle_sources':{'oracle.py':'current'},
                 'mapping_tool_sha256':'mapping','render_data_sha256':'render','vpl_sha256':'vpl'}
        evidence={'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence':dict(current)}
        validate_cached(evidence,current)
        for field in current:
            with self.assertRaisesRegex(ValueError,'identity differs'):
                validate_cached(evidence,{**current,field:'changed'})
        for field in ('executable_sha256','profile'):
            with self.assertRaisesRegex(ValueError,'envelope identity differs'):
                validate_cached({**evidence,field:'changed'},current)

    def test_cached_payload_requires_fresh_original_receipt(self):
        evidence={'evidence':{'evidence_mode':'fresh-original','cases':2}}
        receipt={**evidence['evidence'],'expectations_sha256':'recorded'}
        validate_receipt(evidence,receipt,'recorded')
        for changed in ({**receipt,'expectations_sha256':'changed'},
                        {**receipt,'evidence_mode':'cached-original-replay'},
                        {**receipt,'cases':1}):
            with self.assertRaises(ValueError):validate_receipt(evidence,changed,'recorded')

    def test_replay_preserves_expectations_and_original_receipts(self):
        with tempfile.TemporaryDirectory(dir=ROOT/'build') as folder:
            expected=Path(folder)/'expected.json';receipt=Path(folder)/'report.json'
            receipt.write_text('{"evidence_mode":"fresh-original"}')
            another=Path(folder)/'another-original.json';another.write_bytes(receipt.read_bytes())
            for path in (expected,receipt,another):
                with self.assertRaisesRegex(ValueError,'cannot replace'):
                    check_replay_destination(path,expected,receipt)
            check_replay_destination(Path(folder)/'replay.json',expected,receipt)
            self.assertEqual(receipt.read_text(),'{"evidence_mode":"fresh-original"}')
            self.assertFalse(expected.exists())

    def test_public_source_and_symlink_evidence_paths_are_refused(self):
        with tempfile.TemporaryDirectory(dir=ROOT/'build') as folder:
            source=Path(folder)/'install'/'game.exe';source.parent.mkdir();source.touch()
            for path in (ROOT/'public-report.json',source.parent/'private'/'expected.json'):
                with self.assertRaises(ValueError):private_path(path,source)
            link=Path(folder)/'linked';link.symlink_to(source.parent,target_is_directory=True)
            with self.assertRaisesRegex(ValueError,'Symlink'):
                private_path(link/'expected.json',source)
            self.assertFalse((ROOT/'public-report.json').exists())

if __name__=='__main__':unittest.main()
