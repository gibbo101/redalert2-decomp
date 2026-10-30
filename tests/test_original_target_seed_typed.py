import sys,tempfile,unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/original_target'))
from seed_typed import placeholder_types,byte_pointer_arithmetic,adapt_seed
from seed_shared_types import SharedTypes

class StubMetadataTests(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory();self.addCleanup(self.temp.cleanup);self.root=Path(self.temp.name)
        self.new=self.root/'new';self.old=self.root/'old'
        for d in [self.new,self.old]:
            (d/'decompiled').mkdir(parents=True);(d/'decompiled/00401000.c').write_text('export')
    def test_explicit_stub_enables_only_that_pointee_byte_scaling(self):
        (self.new/'types.h').write_text('struct Opaque { char unknown_0; }; struct Real { int X; };')
        stubs=placeholder_types([self.new],0x401000)
        self.assertEqual(stubs,{'Opaque'})
        body='p + 16; q + 16; array + 16; // p + 16'
        actual=byte_pointer_arithmetic(body,{'p':'Opaque *','q':'Real *','array':'Opaque **'},stubs)
        self.assertEqual(actual,'((char *)p) + 16; q + 16; array + 16; // p + 16')
    def test_new_full_type_is_not_overridden_by_old_stub(self):
        (self.new/'types.h').write_text('struct Item { int X; };')
        (self.old/'types.h').write_text('struct Item { char unknown_0; };')
        self.assertNotIn('Item',placeholder_types([self.new,self.old],0x401000))
    def test_missing_current_metadata_does_not_borrow_old_sizes(self):
        (self.old/'types.h').write_text('struct Item { char unknown_0; };')
        self.assertEqual(placeholder_types([self.new,self.old],0x401000),set())
    def test_conflicting_current_definitions_do_not_guess_a_size(self):
        (self.new/'types_body.h').write_text('struct Item { char unknown_0; };')
        (self.new/'types.h').write_text('struct Item { struct { int X; } nested; };')
        self.assertEqual(placeholder_types([self.new],0x401000),set())
    def test_metadata_follows_the_pass_that_contains_the_export(self):
        (self.new/'decompiled/00401000.c').unlink()
        (self.old/'types.h').write_text('struct Item { char unknown_0; };')
        self.assertEqual(placeholder_types([self.new,self.old],0x401000),{'Item'})

class TypedAdapterTests(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory();self.addCleanup(self.temp.cleanup);self.root=Path(self.temp.name)
        (self.root/'device.hpp').write_text('class Device { public: virtual ~Device(); int value; };')
        (self.root/'ghidra_types.hpp').write_text('typedef unsigned char undefined;\ntypedef unsigned int undefined4, uint;\ntypedef int code(...);\n// Win32 names\n#define CONCAT11(a,b) (((a)<<8)|(b))\n#endif\n')
        self.index=SharedTypes(self.root)
    def source(self,body):
        return '#include "shared/ghidra_types.hpp"\nnamespace seed_00401000 {\nclass Device;\nstruct Owner_00401000 { int FUN_00401000(); };\nint Owner_00401000::FUN_00401000()\n{\n'+body+'\n}\n}  // namespace seed_00401000\n'
    def adapt(self,body):
        return adapt_seed(self.source(body),'Device *this',0x401000,'Device',self.index,{'this':'Device *'},lambda x:x)[0]
    def test_real_header_and_real_body_receiver_without_fake_fields(self):
        text=self.adapt('return this->value;')
        self.assertIn('#include "shared/device.hpp"',text)
        self.assertIn('struct Owner_00401000 : public ::Device',text)
        self.assertIn('Device *typed_this = this;',text)
        self.assertIn('return typed_this->value;',text)
        self.assertNotIn('class Device;',text)
        self.assertNotIn('struct Device {',text)
    def test_sdk_record_uses_existing_global_header_type(self):
        (self.root/'device.hpp').write_text('class Device { public: virtual ~Device(); int value; }; struct POINT { long x; long y; };')
        index=SharedTypes(self.root)
        src=self.source('return this->value;').replace('class Device;','struct POINT { long x; long y; }; typedef POINT *LPPOINT;\nclass Device;')
        text,_=adapt_seed(src,'Device *this',0x401000,'Device',index,{'this':'Device *'},lambda x:x)
        self.assertNotIn('struct POINT {',text)
        self.assertIn('typedef POINT *LPPOINT;',text)
    def test_unused_receiver_alias_is_not_inserted(self):
        self.assertNotIn('typed_this',self.adapt('return 1;'))
    def test_virtual_table_aliases_remain_callable(self):
        text=self.adapt('void **table;\ntable = (void **)(this->vftable_0);\nreturn (*table[3])();')
        self.assertIn('code ** table;',text)
        self.assertIn('table = (code **)',text)
        self.assertNotIn('->vftable_0',text)
    def test_known_forward_declaration_before_typedef_does_not_shadow(self):
        src=self.source('return this->value;').replace('class Device;','class Device; typedef Device *PDevice;')
        text,_=adapt_seed(src,'Device *this',0x401000,'Device',self.index,{'this':'Device *'},lambda x:x)
        self.assertNotIn('class Device;',text)
        self.assertIn('typedef Device *PDevice;',text)

if __name__=='__main__':unittest.main()
