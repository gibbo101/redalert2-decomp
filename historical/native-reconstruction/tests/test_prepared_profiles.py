# SPDX-License-Identifier: GPL-3.0-or-later
"""Synthetic source/default/mapping gates without original files."""
import sys,unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from prepared_data_profiles import DISC,PATCHED,readers,default_output
from prepare_direction_data import EXPECTED
class Profiles(unittest.TestCase):
 def test_unknown_source_rejected(self):
  with self.assertRaisesRegex(ValueError,'Unsupported executable hash'):readers(bytes(1024))
 def test_separate_defaults(self):
  self.assertEqual(default_output(DISC,'direction-data.bin'),Path('private/derived/direction-data.bin'))
  self.assertEqual(default_output(PATCHED,'direction-data.bin'),Path('private/derived/ra2-1006/direction-data.bin'))
  with self.assertRaisesRegex(ValueError,'Unknown prepared data source'):default_output('unknown','data.bin')
 def test_research_expected_stays_disc_only(self):self.assertEqual(EXPECTED,DISC)
if __name__=='__main__':unittest.main()
