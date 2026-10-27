"""Synthetic safety/binding checks for the bounded existing-family renderer."""
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/original_target'))
from generate_word_views import candidate_destination, renamed_symbol, render_source


class WordViewGenerationTests(unittest.TestCase):
    def test_renaming_keeps_owner_and_reference_abi_suffix(self):
        old='?get@Loop_fixture@@QBE_NABV1@@Z'
        self.assertEqual(renamed_symbol(old,'EqualWordSequences_fixture'),
                         '?EqualWordSequences_fixture@Loop_fixture@@QBE_NABV1@@Z')
        for symbol,name in [('_not_a_member','Named'),(old,'bad@name'),(old,'../escape')]:
            with self.subTest(symbol=symbol,name=name), self.assertRaises(ValueError):
                renamed_symbol(symbol,name)

    def test_output_cannot_overwrite_or_escape_into_canonical_sources(self):
        with tempfile.TemporaryDirectory() as temp:
            root=Path(temp).resolve();(root/'private').mkdir();(root/'src').mkdir()
            (root/'private/existing').mkdir()
            (root/'private/canonical-alias').symlink_to(root/'src',target_is_directory=True)
            for path in [root/'src/new',root/'private/existing',root/'private',
                         root/'private/canonical-alias/new',root/'elsewhere']:
                with self.subTest(path=path), self.assertRaises(ValueError):
                    candidate_destination(root,path)
            self.assertEqual(candidate_destination(root,root/'private/review'),root/'private/review')
            self.assertFalse((root/'private/review').exists())

    def test_incomplete_template_refuses_instead_of_emitting_partial_source(self):
        row=dict(entry=0x401000,owner='Owner',semantic_name='KnownOperation_00401000',shift=2)
        with self.assertRaisesRegex(ValueError,'Unexpanded'):
            render_source(row,'@OWNER@ @MISSING@','synthetic-target')
        self.assertEqual(render_source(row,'@FUNCTION_NAME@ at @ADDRESS@','synthetic-target'),
                         b'KnownOperation_00401000 at 0x00401000')


if __name__=='__main__':unittest.main()
