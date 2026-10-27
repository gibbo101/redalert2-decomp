# SPDX-License-Identifier: GPL-3.0-or-later
import base64
import hashlib
import json
import struct
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import prepare_overlay_loading_fixture as fixture


def packed_fill(value):
    command = b'\xfe\x00\x20' + bytes([value]) + b'\x80'
    return base64.b64encode((struct.pack('<HH', len(command), 8192) + command) * 32).decode()


class OverlayFixturePreparation(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name).resolve()
        self.source = self.root / 'supplied'
        self.source.mkdir()
        self.output = self.root / 'private' / 'fixture.json'
        self.root_patch = patch.object(fixture, 'ROOT', self.root)
        self.root_patch.start()
        self.addCleanup(self.root_patch.stop)
        (self.source / 'map.ini').write_text('[Map]\nSize=0,0,1,1\n'
            '[OverlayPack]\n1=' + packed_fill(255) + '\n'
            '[OverlayDataPack]\n1=' + packed_fill(0) + '\n')
        (self.source / 'rules.ini').write_text('[OverlayTypes]\n1=FIRST\n2=SECOND\n'
            '[SECOND]\nCrate=yes\n')
        self.hashes = {p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in self.source.iterdir()}
        (self.source / 'manifest.json').write_text(json.dumps({'files': {
            name: {'sha256': value} for name, value in self.hashes.items()}}))

    def prepare(self, output=None, map_name='map.ini'):
        return fixture.prepare(self.source, output or self.output, map_name)

    def test_private_result_and_source_preservation(self):
        result = self.prepare()
        self.assertEqual(result, json.loads(self.output.read_text()))
        self.assertEqual(result['type_names'], ['FIRST', 'SECOND'])
        self.assertEqual(result['active_overlays'], 0)
        self.assertEqual(result['cell_count'], 1)
        self.assertEqual(result['decoded_sha256'], [hashlib.sha256(bytes([value]) * 262144).hexdigest() for value in (255, 0)])
        self.assertTrue(result['all_images_resident_supplied'])
        for name, digest in self.hashes.items():
            self.assertEqual(hashlib.sha256((self.source / name).read_bytes()).hexdigest(), digest)

    def test_manifest_mismatch_creates_no_output(self):
        (self.source / 'rules.ini').write_text('changed')
        with self.assertRaisesRegex(ValueError, 'hash differs'):
            self.prepare()
        self.assertFalse(self.output.exists())

    def test_existing_output_preserved(self):
        self.output.parent.mkdir()
        self.output.write_text('preserve')
        with self.assertRaisesRegex(ValueError, 'new ignored'):
            self.prepare()
        self.assertEqual(self.output.read_text(), 'preserve')

    def test_source_and_nonprivate_destinations_refused(self):
        for output in (self.source / 'result.json', self.root / 'result.json'):
            with self.assertRaisesRegex(ValueError, 'new ignored'):
                self.prepare(output)
            self.assertFalse(output.exists())
        self.output.parent.mkdir()
        nested = self.output.parent / 'source'
        nested.mkdir()
        with self.assertRaisesRegex(ValueError, 'separate'):
            fixture.prepare(nested, nested / 'result.json', 'map.ini')

    def test_symlink_escape_and_dangling_output_refused(self):
        self.output.parent.mkdir()
        escape = self.output.parent / 'escape'
        escape.symlink_to(self.source, target_is_directory=True)
        with self.assertRaisesRegex(ValueError, 'new ignored'):
            self.prepare(escape / 'result.json')
        self.output.symlink_to(self.output.parent / 'missing.json')
        with self.assertRaisesRegex(ValueError, 'new ignored'):
            self.prepare()
        self.assertFalse(self.output.resolve().exists())

    def test_map_path_traversal_refused(self):
        for name in ('../map.ini', '/map.ini', '.', '..'):
            with self.assertRaisesRegex(ValueError, 'single filename'):
                self.prepare(map_name=name)

    def test_truncated_commands_invalid_copies_and_overflow_refused(self):
        for data, wanted in ((b'\x81', 1), (b'\xfe', 1), (b'\xff\x01', 1),
                             (b'\x00\x01', 3), (b'\x81a\x00\x00', 4),
                             (b'\xfe\xff\xffa', 1), (b'\x82ab', 1), (b'\x80', 1)):
            with self.assertRaises(ValueError):
                fixture.decode_lcw(data, wanted)

    def test_overlapping_and_absolute_copies(self):
        # Literal A; overlapping back-reference; short and long absolute copies.
        self.assertEqual(fixture.decode_lcw(b'\x81A\x00\x01\xc0\x00\x00\xff\x02\x00\x01\x00\x80', 9), b'A' * 9)

    def test_malformed_packs_refused(self):
        for raw in (b'', b'\x01', struct.pack('<HH', 1, 8193) + b'x',
                    struct.pack('<HH', 9, 1) + b'x', b'\0' * 5):
            with self.assertRaises(ValueError):
                fixture.decode_pack({'1': base64.b64encode(raw).decode()})
        with self.assertRaises(ValueError):
            fixture.decode_pack({'1': '!!invalid!!'})


if __name__ == '__main__':
    unittest.main()
