# SPDX-License-Identifier: GPL-3.0-or-later
"""Stage source/profile guards without original execution or proprietary inputs."""
import unittest
from archive_sequence_profiles import address
from compare_archive_sequence import sources
import test_archive_profiles as primitives
from verify_archive_startup_order import verify as verify_order

class ArchiveSequenceProfileTests(primitives.ArchiveProfileTests):
    def test_stage_addresses_are_explicit_and_keep_primitive_mappings(self):
        self.assertEqual(address('supplied-ra2-1006',0x519290),0x519e70)
        self.assertEqual(address('supplied-ra2-1006',0x5152c0),0x515e70)
        self.assertEqual(address('supplied-ra2-1006',0x592750),0x595aa0)
        with self.assertRaisesRegex(ValueError,'Unmapped'):
            address('supplied-ra2-1006',0x519291)

    def test_receipt_pins_full_stage_and_inherited_source_closure(self):
        closure=sources()
        for path in ('tests/original_archive.py','tests/original_archive_sequence.py',
                     'tools/verify_archive_startup_order.py','tools/verify_archive_sequence_mapping.py',
                     'src/assets/ArchiveSequence.cpp','src/assets/ArchiveSequence.hpp'):
            self.assertIn(path,closure)
            self.assertEqual(len(closure[path]),64)

    def test_startup_inspection_rejects_an_unidentified_engine_before_parsing(self):
        for data in (b'',b'MZ authored fixture'):
            with self.assertRaisesRegex(ValueError,'SHA-256'):
                verify_order(data)

if __name__=='__main__':unittest.main()
