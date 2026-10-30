import sys,unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/original_target'))
from seed_candidate import call_sites,declare_callee
class QualifiedCallTests(unittest.TestCase):
 def test_namespace_consumed_as_part_of_address_bound_call(self):
  body='Tactical::FUN_00401000(owner, 7);'
  text,_=declare_callee(body,'FUN_00401000',('void','__thiscall',['void *this','int value']))
  self.assertEqual(text,'((Callee_00401000*)(owner))->FUN_00401000((int)(7));')
 def test_nested_and_global_qualification_preserves_value_context(self):
  body='return ::Outer::Inner::FUN_00401000(7);'
  site=list(call_sites(body,'FUN_00401000'))[0]
  self.assertEqual(body[site[0]:site[1]],'::Outer::Inner::FUN_00401000(7)');self.assertTrue(site[3])
 def test_unqualified_call_keeps_existing_positions(self):
  body='x = FUN_00401000(7);';site=list(call_sites(body,'FUN_00401000'))[0]
  self.assertEqual(body[site[0]:site[1]],'FUN_00401000(7)');self.assertTrue(site[3])
 def test_no_value_use_in_qualified_void_statement(self):
  self.assertFalse(list(call_sites('Tactical::FUN_00401000(7);','FUN_00401000'))[0][3])
 def test_comments_and_strings_are_not_calls(self):
  self.assertEqual(list(call_sites('// T::FUN_00401000(7)\n"T::FUN_00401000(7)";','FUN_00401000')),[])
 def test_actual_member_prefix_is_not_removed(self):
  body='object->Class::FUN_00401000(7);';site=list(call_sites(body,'FUN_00401000'))[0]
  self.assertEqual(site[0],body.index('FUN_'))
if __name__=='__main__':unittest.main()
