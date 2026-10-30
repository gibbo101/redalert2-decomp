import sys,tempfile,unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/original_target'))
from seed_shared_types import SharedTypes
class IndexedSharedPathsTests(unittest.TestCase):
 def setUp(self):
  self.temp=tempfile.TemporaryDirectory();self.addCleanup(self.temp.cleanup);p=Path(self.temp.name)
  (p/'record.hpp').write_text('struct Timer { long Started; long DelayTime; }; struct Child { Timer timer; }; struct Owner { Timer countdown; Child entries[4]; };')
  self.schema=SharedTypes(p)
 def rewrite(self,body):return self.schema.rewrite_members(body,{'p':'Owner *'})[0]
 def test_indexed_receiver_flat_timer_path(self):
  self.assertEqual(self.rewrite('p[1].countdown_DelayTime;'),'p[1].countdown.DelayTime;')
 def test_array_member_then_nested_flat_field(self):
  self.assertEqual(self.rewrite('p->entries[i].timer_DelayTime;'),'p->entries[i].timer.DelayTime;')
 def test_index_expression_and_evaluation_are_preserved_once(self):
  text=self.rewrite('p[advance()].countdown_DelayTime;')
  self.assertEqual(text,'p[advance()].countdown.DelayTime;');self.assertEqual(text.count('advance()'),1)
 def test_dotted_index_expression_is_not_a_member_segment(self):
  self.assertEqual(self.rewrite('p->entries[index.X].timer_DelayTime;'),'p->entries[index.X].timer.DelayTime;')
 def test_index_comments_are_preserved(self):
  self.assertEqual(self.rewrite('p[1 /* offset */].countdown_DelayTime;'),'p[1 /* offset */].countdown.DelayTime;')
 def test_unknown_padding_is_not_invented(self):
  text='p[1].unknown_010;';self.assertEqual(self.rewrite(text),text)
if __name__=='__main__':unittest.main()
