"""Scalar slice widths must not silently become four-byte accesses."""
from pathlib import Path
import sys
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools/original_target'))
import seed_candidate as seed


class ScalarPartialTests(unittest.TestCase):
    def test_supported_load_and_store_widths_keep_existing_spelling(self):
        for size, kind in [('1', 'uchar'), ('2', 'ushort'), ('4', 'uint')]:
            for source in ['return value._2_%s_;', 'value._2_%s_ = next();']:
                source = source % size
                self.assertEqual(seed.scalar_partials(source),
                                 source.replace('value._2_'+size+'_',
                                                '(*('+kind+'*)((char*)&value + 2))'))

    def test_unsupported_read_write_and_address_widths_refuse(self):
        for size in [0, 3, 5, 6, 7, 8, 16]:
            for source in ['return slot._1_%d_;', 'slot._1_%d_ = next();',
                           'consume(&slot._1_%d_);']:
                with self.subTest(size=size, source=source):
                    with self.assertRaisesRegex(ValueError, 'scalar slice width '+str(size)):
                        seed.scalar_partials(source % size)

    def test_real_concat_high_six_bytes_are_not_truncated(self):
        source = 'CONCAT62(slot._2_6_, low)'
        expanded = seed.concat_artifacts(source)
        with self.assertRaisesRegex(ValueError, 'slot._2_6_'):
            seed.scalar_partials(expanded)

    def test_comments_and_literals_are_preserved(self):
        source = '// value._1_3_\n/* value._2_6_ */\nuse("value._0_5_");'
        self.assertEqual(seed.scalar_partials(source), source)

    def test_only_real_access_changes_next_to_masked_pseudocode(self):
        source = '/* x._0_4_ */ return x._0_4_; // x._0_3_'
        self.assertEqual(seed.scalar_partials(source),
                         '/* x._0_4_ */ return (*(uint*)((char*)&x + 0)); // x._0_3_')

    def test_replacement_keeps_effectful_rhs_once(self):
        result = seed.scalar_partials('value._0_2_ = next();')
        self.assertEqual(result.count('next()'), 1)


if __name__ == '__main__':
    unittest.main()
