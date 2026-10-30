import sys,tempfile,unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/original_target'))
from seed_typed import null_void_views,pointer_member_assignments
from seed_shared_types import SharedTypes
class TypedPointerConversionTests(unittest.TestCase):
 def setUp(self):
  self.temp=tempfile.TemporaryDirectory();self.addCleanup(self.temp.cleanup);p=Path(self.temp.name)
  (p/'owner.hpp').write_text('struct Item {}; struct Nested { Item *ptr; }; class Owner { public: Item *ptr; Nested child; Item *array[2]; private: Item *secret; };')
  self.schema=SharedTypes(p)
 def rewrite(self,text):return pointer_member_assignments(text,{'this':'Owner *'},self.schema)
 def test_pointer_store_uses_existing_real_field_type(self):
  self.assertEqual(self.rewrite('this->ptr = load();'),'this->ptr = (Item *)(load());')
 def test_nested_pointer_store_uses_aggregate_member_path(self):
  self.assertEqual(self.rewrite('this->child.ptr = raw;'),'this->child.ptr = (Item *)(raw);')
 def test_protected_and_array_stores_are_not_exposed(self):
  s='this->secret = raw;\nthis->array = raw;';self.assertEqual(self.rewrite(s),s)
 def test_comments_literals_and_unbalanced_rhs_remain_untouched(self):
  s='// this->ptr = raw;\n"this->ptr = raw;";\nthis->ptr = call())';self.assertEqual(self.rewrite(s),s)
 def test_nested_argument_comma_preserves_one_evaluation(self):
  self.assertEqual(self.rewrite('this->ptr = load(a,b);'),'this->ptr = (Item *)(load(a,b));')
 def test_matching_existing_pointer_cast_is_not_duplicated(self):
  s='this->ptr = (Item *)(raw);';self.assertEqual(self.rewrite(s),s)
 def test_only_zero_void_pointer_views_are_normalized(self):
  self.assertEqual(null_void_views('(void *)0x0; (void*)0; (void*)0x10; (void*)0.0;'),'0; 0; (void*)0x10; (void*)0.0;')
 def test_null_views_in_comments_and_literals_are_not_modified(self):
  s='// (void*)0\n"(void*)0"';self.assertEqual(null_void_views(s),s)
if __name__=='__main__':unittest.main()
