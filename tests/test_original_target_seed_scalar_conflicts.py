import sys,unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/original_target'))
from seed_typed import scalar_conflict_aliases
class ScalarConflictAliasTests(unittest.TestCase):
 def test_exported_fixed_width_types_in_declarations_and_casts(self):
  text='ushort_conflict *p; x=(uchar_conflict)y;'
  self.assertEqual(scalar_conflict_aliases(text,{}),'typedef uchar uchar_conflict;\ntypedef ushort ushort_conflict;')
 def test_owned_identifier_is_not_shadowed_by_a_typedef(self):
  self.assertEqual(scalar_conflict_aliases('x=(uchar_conflict)y;',{'uchar_conflict':'int'}),'')
 def test_existing_typedef_remains_authoritative(self):
  self.assertEqual(scalar_conflict_aliases('typedef unsigned char uchar_conflict; x=(uchar_conflict)y;',{}),'')
 def test_unknown_alias_and_comments_are_not_guessed(self):
  self.assertEqual(scalar_conflict_aliases('// (uchar_conflict)y\nUnknown_conflict *p;',{}),'')
if __name__=='__main__':unittest.main()
