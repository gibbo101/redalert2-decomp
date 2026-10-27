# SPDX-License-Identifier: GPL-3.0-or-later
"""Research profile, input and evidence guards; no original execution."""
from pathlib import Path
from types import SimpleNamespace
import tempfile
import unittest
from unittest.mock import patch
from compare_original import EXPECTED, PATCHED_EXPECTED
from raster_profiles import address, raster_profile
from raster_evidence import prepare, validate_cached
from presentation_evidence import validate_receipt, check_replay_destination
from original_raster import RasterOracle
from original_composition import CompositionOracle
from verify_raster_mapping import verify

ROOT=Path(__file__).resolve().parents[1]

class RasterProfileTests(unittest.TestCase):
    def test_unknown_hash_fails_before_mapping_or_execution(self):
        for data in (b'',b'MZ unknown engine',bytes(4096)):
            for enabled in (False,True):
                with self.assertRaisesRegex(ValueError,'Unsupported executable hash'):
                    raster_profile(data,allow_patched=enabled)
            with self.assertRaisesRegex(ValueError,'SHA-256'):verify(data,data)

    def test_explicit_opt_in_preserves_unmigrated_child_default(self):
        with patch('presentation_profiles.hashlib.sha256',return_value=SimpleNamespace(hexdigest=lambda:PATCHED_EXPECTED)):
            with self.assertRaises(ValueError):raster_profile(b'selector fixture')
            self.assertEqual(raster_profile(b'selector fixture',allow_patched=True),(PATCHED_EXPECTED,'supplied-ra2-1006'))
            with tempfile.TemporaryDirectory(dir=ROOT/'build') as folder:
                source=Path(folder)/'game.exe';source.write_bytes(b'selector fixture')
                for oracle in (RasterOracle,CompositionOracle):
                    with self.assertRaises(ValueError):oracle(source)

    def test_only_explicit_raster_addresses_are_accepted(self):
        self.assertEqual(address('supplied-ra2-1006',0x70dbc0),0x719160)
        self.assertEqual(address('supplied-ra2-1006',0x784180),0x798c00)
        self.assertEqual(address('allied-disc',0x70dbc0),0x70dbc0)
        for profile,va in (('unknown',0x70dbc0),('supplied-ra2-1006',0x70dbc1)):
            with self.assertRaises(ValueError):address(profile,va)

    def test_patched_research_requires_explicit_native_data_identity(self):
        with tempfile.TemporaryDirectory(dir=ROOT/'build') as folder:
            source=Path(folder)/'game.exe';source.write_bytes(b'synthetic engine')
            args=SimpleNamespace(exe=source,native_data_exe=None)
            with patch('raster_evidence.raster_profile',return_value=(PATCHED_EXPECTED,'supplied-ra2-1006')):
                with self.assertRaisesRegex(ValueError,'Retained native raster/render inputs'):prepare(args)

    def test_replay_rejects_mixed_source_data_asset_or_engine_identities(self):
        current={'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                 'native_data_executable_sha256':EXPECTED,'oracle_sources':{'oracle.py':'current'},
                 'mapping_tools':{'mapping.py':'current'},'raster_data_sha256':'raster',
                 'render_data_sha256':'render','assets_sha256':{'htnk.vxl':'model'}}
        evidence={'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence':dict(current)}
        validate_cached(evidence,current)
        for field in current:
            with self.assertRaisesRegex(ValueError,'identity differs'):validate_cached(evidence,{**current,field:'changed'})
        for field in ('executable_sha256','profile'):
            with self.assertRaisesRegex(ValueError,'envelope identity differs'):
                validate_cached({**evidence,field:'changed'},current)

    def test_expectation_payload_requires_unchanged_fresh_receipt(self):
        evidence={'evidence':{'evidence_mode':'fresh-original','cases':707}}
        receipt={**evidence['evidence'],'expectations_sha256':'recorded'}
        validate_receipt(evidence,receipt,'recorded')
        for changed in ({**receipt,'expectations_sha256':'changed'},
                        {**receipt,'evidence_mode':'cached-original-replay'},{**receipt,'cases':706}):
            with self.assertRaises(ValueError):validate_receipt(evidence,changed,'recorded')

    def test_replay_cannot_replace_fresh_evidence(self):
        with tempfile.TemporaryDirectory(dir=ROOT/'build') as folder:
            expected=Path(folder)/'expected.json';receipt=Path(folder)/'report.json'
            receipt.write_text('{"evidence_mode":"fresh-original"}')
            for path in (expected,receipt):
                with self.assertRaisesRegex(ValueError,'cannot replace'):check_replay_destination(path,expected,receipt)
            check_replay_destination(Path(folder)/'replay.json',expected,receipt)
            self.assertFalse(expected.exists())

if __name__=='__main__':unittest.main()
