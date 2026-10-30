import sys,unittest,tempfile
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/original_target'))
from seed_shared_types import SharedTypes

FIXTURE='''
class VectorClass {
public:
    virtual ~VectorClass();
    int Length() const;
protected:
    int *Vector;
    int VectorMax;
};
class DynamicVectorClass : public VectorClass {
public:
    int Count() const;
protected:
    int ActiveCount;
};
struct Coord { int X; int Y; };
struct Timer { int Started; int DelayTime; };
class House {
public:
    Timer unknown_5530;
    Coord BaseCenter;
    DynamicVectorClass Buildings;
    int field_with_underscores;
};
'''

class SharedFieldTests(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory();self.addCleanup(self.temp.cleanup)
        self.root=Path(self.temp.name);(self.root/'fixture.hpp').write_text(FIXTURE)
        self.index=SharedTypes(self.root)
    def test_flat_paths_keep_existing_underscores(self):
        path=self.index.flat_path('House','unknown_5530_DelayTime')
        self.assertEqual([x.name for x in path],['unknown_5530','DelayTime'])
        self.assertEqual([x.name for x in self.index.flat_path('House','field_with_underscores')],['field_with_underscores'])
    def test_template_pointer_argument_is_not_an_aggregate_pointer(self):
        (self.root/'template.hpp').write_text('struct Root { DynamicVectorClass<House *> List; };\n')
        index=SharedTypes(self.root)
        self.assertEqual([f.name for f in index.flat_path('Root','List_Vector')],['List','Vector'])
    def test_explicit_constructor_and_static_owner_evidence(self):
        (self.root/'owners.hpp').write_text('class Country {\npublic:\n Country(char const *name); // 0x00401000\n static void __fastcall Read(int &ini); // 0x00402000\n};\n')
        index=SharedTypes(self.root)
        self.assertEqual(index.constructor_owner(0x401000),'Country')
        record,method=index.method_at(0x402000)
        self.assertEqual(record.name,'Country');self.assertTrue(method.static)
        self.assertEqual(method.parameters,'int &ini')
    def test_ambiguous_constructor_evidence_is_not_chosen(self):
        (self.root/'owners.hpp').write_text('class A {\n A(); // 0x00401000\n};\nclass B {\n B(); // 0x00401000\n};\n')
        self.assertIsNone(SharedTypes(self.root).constructor_owner(0x401000))
    def test_canonical_provider_is_preferred_to_an_equal_size_light_view(self):
        (self.root/'map_view.hpp').write_text('class GScreenClass { int X; };\n')
        (self.root/'gscreen.hpp').write_text('class GScreenClass : public Interface { int X; };\n')
        self.assertEqual(SharedTypes(self.root).records['GScreenClass'].header,'shared/gscreen.hpp')
    def test_vector_data_does_not_form_a_reference_to_element_zero(self):
        actual,notes=self.index.rewrite_members('p = this->Buildings_Vector;',{'this':'House *'})
        self.assertNotIn('operator[]',actual)
        self.assertIn('((char *)&(this->Buildings) + 4)',actual)
        self.assertEqual(notes,[])
    def test_vector_data_requires_evidenced_polymorphic_layout(self):
        (self.root/'fixture.hpp').write_text(FIXTURE.replace('virtual ~VectorClass();',''))
        index=SharedTypes(self.root)
        actual,notes=index.rewrite_members('p = this->Buildings_Vector;',{'this':'House *'})
        self.assertEqual(actual,'p = this->Buildings_Vector;');self.assertTrue(notes)
    def test_missing_field_is_not_invented(self):
        self.assertIsNone(self.index.flat_path('House','unknown_missing_X'))
    def test_reads_use_real_public_container_accessors(self):
        source='x = this->Buildings_ActiveCount; p = this->Buildings_Vector; n = this->Buildings_VectorMax;'
        actual,notes=self.index.rewrite_members(source,{'this':'House *'})
        self.assertEqual(actual,'x = this->Buildings.Count(); p = (*(int * *)((char *)&(this->Buildings) + 4)); n = this->Buildings.Length();')
        self.assertEqual(notes,[])
    def test_protected_store_and_address_are_not_getter_calls(self):
        for source in ['this->Buildings_ActiveCount = 0;','p = &this->Buildings_Vector;']:
            actual,notes=self.index.rewrite_members(source,{'this':'House *'})
            self.assertEqual(actual,source);self.assertTrue(notes)
    def test_comments_and_strings_are_not_rewritten(self):
        source='/* this->BaseCenter_X */ "this->BaseCenter_X"; n = this->BaseCenter_X;'
        actual,_=self.index.rewrite_members(source,{'this':'House *'})
        self.assertEqual(actual,'/* this->BaseCenter_X */ "this->BaseCenter_X"; n = this->BaseCenter.X;')
    def test_two_distinct_nested_paths_are_ambiguous(self):
        (self.root/'other.hpp').write_text('struct Child { int b_c; int c; };\nstruct Root { Child a; Child a_b; };\n')
        index=SharedTypes(self.root)
        self.assertIsNone(index.flat_path('Root','a_b_c'))
    def test_full_provider_wins_over_fieldless_stub(self):
        (self.root/'stub.hpp').write_text('class House {};\n')
        self.assertEqual(SharedTypes(self.root).records['House'].header,'shared/fixture.hpp')

if __name__=='__main__':unittest.main()
