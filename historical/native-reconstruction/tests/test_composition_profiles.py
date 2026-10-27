# SPDX-License-Identifier: GPL-3.0-or-later
"""Research profile/evidence guards; these tests never execute original code."""
from pathlib import Path
from types import SimpleNamespace
import tempfile
import unittest
from unittest.mock import patch
from compare_original import EXPECTED, PATCHED_EXPECTED
from composition_profiles import address, composition_profile, PATCHED_ADDRESSES
from composition_evidence import prepare, validate_cached
from presentation_evidence import validate_receipt, check_replay_destination, private_path
from presentation_profiles import RETAINED_RENDER_SHA256
from raster_profiles import RETAINED_RASTER_SHA256, PATCHED_ADDRESSES as RASTER
from movement_profiles import PATCHED_ADDRESSES as MOVEMENT
from original_composition import CompositionOracle, TmpOracle, FlatDepthOracle
from original_shadow_color import ShadowColorOracle
from verify_composition_mapping import verify

ROOT=Path(__file__).resolve().parents[1]

class CompositionProfileTests(unittest.TestCase):
    def test_unknown_hash_fails_before_execution(self):
        for data in (b'',b'MZ unknown engine',bytes(4096)):
            for enabled in (False,True):
                with self.assertRaisesRegex(ValueError,'Unsupported executable hash'):
                    composition_profile(data,allow_patched=enabled)
            with self.assertRaisesRegex(ValueError,'SHA-256'):verify(data,data)

    def test_explicit_opt_in_and_descendants_keep_disc_default(self):
        with patch('presentation_profiles.hashlib.sha256',return_value=SimpleNamespace(hexdigest=lambda:PATCHED_EXPECTED)):
            with self.assertRaises(ValueError):composition_profile(b'selector fixture')
            self.assertEqual(composition_profile(b'selector fixture',allow_patched=True),(PATCHED_EXPECTED,'supplied-ra2-1006'))
            with tempfile.TemporaryDirectory(dir=ROOT/'build') as folder:
                source=Path(folder)/'game.exe';source.write_bytes(b'selector fixture')
                for oracle in (CompositionOracle,TmpOracle,FlatDepthOracle,ShadowColorOracle):
                    with self.assertRaises(ValueError):oracle(source)

    def test_only_explicit_addresses_are_accepted(self):
        for before,after in ((0x52a340,0x52c230),(0x785ef8,0x79aef8),
                             (0x78920c,0x79e20c),(0x824904,0x83c5dc),
                             (0x6c52c0,0x6cfea0),(0x41e475,0x41e475)):
            self.assertEqual(address('supplied-ra2-1006',before),after)
            self.assertEqual(address('allied-disc',before),before)
        for profile,va in (('unknown',0x52a340),('supplied-ra2-1006',0x52a341)):
            with self.assertRaises(ValueError):address(profile,va)
        for inherited in (RASTER,MOVEMENT):
            for old,new in inherited.items():self.assertEqual(PATCHED_ADDRESSES[old],new)

    def test_patched_research_requires_explicit_native_input_identity(self):
        with tempfile.TemporaryDirectory(dir=ROOT/'build') as folder:
            source=Path(folder)/'game.exe';source.write_bytes(b'synthetic engine')
            args=SimpleNamespace(exe=source,native_data_exe=None)
            with patch('composition_evidence.composition_profile',return_value=(PATCHED_EXPECTED,'supplied-ra2-1006')):
                with self.assertRaisesRegex(ValueError,'Retained native composition inputs'):prepare(args)

    def test_fresh_run_refuses_existing_receipt_before_export(self):
        with tempfile.TemporaryDirectory(dir=ROOT/'build') as folder:
            root=Path(folder);source=root/'game.exe';source.write_bytes(b'synthetic engine')
            output=root/'private/migration/allied-disc/composition';output.mkdir(parents=True)
            (output/'report.json').write_text('{"evidence_mode":"fresh-original"}')
            args=SimpleNamespace(exe=source,native_data_exe=None,raster_data=root/'raster',render_data=root/'render',expectations=None)
            def identity(path):return RETAINED_RASTER_SHA256 if path==args.raster_data else RETAINED_RENDER_SHA256 if path==args.render_data else EXPECTED
            with patch('composition_evidence.composition_profile',return_value=(EXPECTED,'allied-disc')), \
                 patch('composition_evidence.hash_file',side_effect=identity), \
                 patch('composition_evidence.ROOT',root), \
                 patch('composition_evidence.private_path',side_effect=lambda path,source:path), \
                 patch('composition_evidence.subprocess.run') as export:
                with self.assertRaisesRegex(ValueError,'Fresh composition evidence already exists'):prepare(args)
                export.assert_not_called()

    def test_replay_rejects_changed_sources_tables_assets_and_engines(self):
        current={'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                 'native_data_executable_sha256':EXPECTED,'oracle_sources':{'oracle.py':'current'},
                 'mapping_tools':{'mapping.py':'current'},'raster_data_sha256':'raster',
                 'render_data_sha256':'render','assets_sha256':{'clear01.tem':'tile'}}
        evidence={'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence':dict(current)}
        validate_cached(evidence,current)
        for field in current:
            with self.assertRaisesRegex(ValueError,'identity differs'):validate_cached(evidence,{**current,field:'changed'})
        for field in ('executable_sha256','profile'):
            with self.assertRaisesRegex(ValueError,'envelope identity differs'):validate_cached({**evidence,field:'changed'},current)

    def test_unchanged_expectation_fingerprint_and_receipt_are_required(self):
        evidence={'evidence':{'evidence_mode':'fresh-original','cases':424}}
        receipt={**evidence['evidence'],'expectations_sha256':'recorded'}
        validate_receipt(evidence,receipt,'recorded')
        for changed in ({**receipt,'expectations_sha256':'changed'},
                        {**receipt,'evidence_mode':'cached-original-replay'},{**receipt,'cases':423}):
            with self.assertRaises(ValueError):validate_receipt(evidence,changed,'recorded')

    def test_replay_cannot_replace_original_evidence(self):
        with tempfile.TemporaryDirectory(dir=ROOT/'build') as folder:
            expected=Path(folder)/'expected.json';receipt=Path(folder)/'report.json'
            receipt.write_text('{"evidence_mode":"fresh-original"}')
            for path in (expected,receipt):
                with self.assertRaisesRegex(ValueError,'cannot replace'):check_replay_destination(path,expected,receipt)
            check_replay_destination(Path(folder)/'replay.json',expected,receipt)

    def test_private_evidence_cannot_target_sources_or_symlinks(self):
        with tempfile.TemporaryDirectory(dir=ROOT/'build') as folder:
            root=Path(folder);source=root/'install/game.exe';source.parent.mkdir();source.write_bytes(b'input')
            with self.assertRaisesRegex(ValueError,'outside the source installation'):private_path(source.parent/'report.json',source)
            link=root/'link';link.symlink_to(source.parent,target_is_directory=True)
            with self.assertRaisesRegex(ValueError,'Symlink'):private_path(link/'report.json',source)
            with self.assertRaisesRegex(ValueError,'private/ or build/'):private_path(ROOT/'docs/refused.json',source)

if __name__=='__main__':unittest.main()
