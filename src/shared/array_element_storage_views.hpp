#pragma once
#define RA2_ARRAY_STORAGE_OFFSET_OF(type, member) ((unsigned int)&(((type*)0)->member))

// Target-only observed storage views. Names and source class identities are hypotheses.
// Distinct owners/elements retain unknown original type identities.
// No virtual hierarchy or complete original class size is asserted.

// Ordinary array allocation declaration; implementation remains at the original target.
void* __cdecl operator new[](unsigned int byte_count);

// Authored placement-array language boilerplate, not a recovered game helper.
// It must inline completely; any emitted helper section is outside this source credit.
inline void* __cdecl operator new[](unsigned int, void* supplied_storage)
{
    return supplied_storage;
}

typedef char ArrayStorage_pointer_width_check[(sizeof(void*) == 4) ? 1 : -1];
typedef char ArrayStorage_int_width_check[(sizeof(int) == 4) ? 1 : -1];

struct Element_0042d4a0 {
    unsigned int uninitialized_word;
    Element_0042d4a0() {}
};
typedef char Element_0042d4a0_stride_check[(sizeof(Element_0042d4a0) == 4) ? 1 : -1];

class ElementStorage_0042d4a0 {
public:
    unsigned char* dispatch_table; // 0x00: observed raw table identity.
    Element_0042d4a0* storage; // 0x04
    int count; // 0x08
    unsigned char unknown_0x0c; // 0x0c
    unsigned char owns_storage; // 0x0d
    unsigned char untouched_0x0e[2];
    ElementStorage_0042d4a0(int initial_count, Element_0042d4a0* supplied_storage);
};
typedef char ElementStorage_0042d4a0_dispatch_table_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_0042d4a0, dispatch_table) == 0) ? 1 : -1];
typedef char ElementStorage_0042d4a0_storage_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_0042d4a0, storage) == 4) ? 1 : -1];
typedef char ElementStorage_0042d4a0_count_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_0042d4a0, count) == 8) ? 1 : -1];
typedef char ElementStorage_0042d4a0_unknown_0x0c_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_0042d4a0, unknown_0x0c) == 12) ? 1 : -1];
typedef char ElementStorage_0042d4a0_owns_storage_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_0042d4a0, owns_storage) == 13) ? 1 : -1];
typedef char ElementStorage_0042d4a0_untouched_0x0e_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_0042d4a0, untouched_0x0e) == 14) ? 1 : -1];

struct Element_0056cdd0 {
    unsigned int uninitialized_word;
    unsigned int second_uninitialized_word;
    Element_0056cdd0() {}
};
typedef char Element_0056cdd0_stride_check[(sizeof(Element_0056cdd0) == 8) ? 1 : -1];

class ElementStorage_0056cdd0 {
public:
    unsigned char* dispatch_table; // 0x00: observed raw table identity.
    Element_0056cdd0* storage; // 0x04
    int count; // 0x08
    unsigned char unknown_0x0c; // 0x0c
    unsigned char owns_storage; // 0x0d
    unsigned char untouched_0x0e[2];
    ElementStorage_0056cdd0(int initial_count, Element_0056cdd0* supplied_storage);
};
typedef char ElementStorage_0056cdd0_dispatch_table_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_0056cdd0, dispatch_table) == 0) ? 1 : -1];
typedef char ElementStorage_0056cdd0_storage_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_0056cdd0, storage) == 4) ? 1 : -1];
typedef char ElementStorage_0056cdd0_count_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_0056cdd0, count) == 8) ? 1 : -1];
typedef char ElementStorage_0056cdd0_unknown_0x0c_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_0056cdd0, unknown_0x0c) == 12) ? 1 : -1];
typedef char ElementStorage_0056cdd0_owns_storage_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_0056cdd0, owns_storage) == 13) ? 1 : -1];
typedef char ElementStorage_0056cdd0_untouched_0x0e_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_0056cdd0, untouched_0x0e) == 14) ? 1 : -1];

struct Element_00635090 {
    unsigned int uninitialized_word;
    unsigned int second_uninitialized_word;
    Element_00635090() {}
};
typedef char Element_00635090_stride_check[(sizeof(Element_00635090) == 8) ? 1 : -1];

class ElementStorage_00635090 {
public:
    unsigned char* dispatch_table; // 0x00: observed raw table identity.
    Element_00635090* storage; // 0x04
    int count; // 0x08
    unsigned char unknown_0x0c; // 0x0c
    unsigned char owns_storage; // 0x0d
    unsigned char untouched_0x0e[2];
    ElementStorage_00635090(int initial_count, Element_00635090* supplied_storage);
};
typedef char ElementStorage_00635090_dispatch_table_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_00635090, dispatch_table) == 0) ? 1 : -1];
typedef char ElementStorage_00635090_storage_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_00635090, storage) == 4) ? 1 : -1];
typedef char ElementStorage_00635090_count_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_00635090, count) == 8) ? 1 : -1];
typedef char ElementStorage_00635090_unknown_0x0c_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_00635090, unknown_0x0c) == 12) ? 1 : -1];
typedef char ElementStorage_00635090_owns_storage_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_00635090, owns_storage) == 13) ? 1 : -1];
typedef char ElementStorage_00635090_untouched_0x0e_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_00635090, untouched_0x0e) == 14) ? 1 : -1];

struct Element_004f8b80 {
    unsigned int word;
    unsigned char byte;
    unsigned char untouched_0x05[3];
    Element_004f8b80() : word(0), byte(0) {}
};
typedef char Element_004f8b80_stride_check[(sizeof(Element_004f8b80) == 8) ? 1 : -1];

class ElementStorage_004f8b80 {
public:
    unsigned char* dispatch_table; // 0x00: observed raw table identity.
    Element_004f8b80* storage; // 0x04
    int count; // 0x08
    unsigned char unknown_0x0c; // 0x0c
    unsigned char owns_storage; // 0x0d
    unsigned char untouched_0x0e[2];
    ElementStorage_004f8b80(int initial_count, Element_004f8b80* supplied_storage);
};
typedef char ElementStorage_004f8b80_dispatch_table_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_004f8b80, dispatch_table) == 0) ? 1 : -1];
typedef char ElementStorage_004f8b80_storage_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_004f8b80, storage) == 4) ? 1 : -1];
typedef char ElementStorage_004f8b80_count_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_004f8b80, count) == 8) ? 1 : -1];
typedef char ElementStorage_004f8b80_unknown_0x0c_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_004f8b80, unknown_0x0c) == 12) ? 1 : -1];
typedef char ElementStorage_004f8b80_owns_storage_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_004f8b80, owns_storage) == 13) ? 1 : -1];
typedef char ElementStorage_004f8b80_untouched_0x0e_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_004f8b80, untouched_0x0e) == 14) ? 1 : -1];

struct Element_0046dc90 {
    unsigned char first;
    unsigned char second;
    unsigned char third;
    Element_0046dc90() : first(0), second(0), third(0) {}
};
typedef char Element_0046dc90_stride_check[(sizeof(Element_0046dc90) == 3) ? 1 : -1];

class ElementStorage_0046dc90 {
public:
    unsigned char* dispatch_table; // 0x00: observed raw table identity.
    Element_0046dc90* storage; // 0x04
    int count; // 0x08
    unsigned char unknown_0x0c; // 0x0c
    unsigned char owns_storage; // 0x0d
    unsigned char untouched_0x0e[2];
    ElementStorage_0046dc90(int initial_count, Element_0046dc90* supplied_storage);
};
typedef char ElementStorage_0046dc90_dispatch_table_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_0046dc90, dispatch_table) == 0) ? 1 : -1];
typedef char ElementStorage_0046dc90_storage_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_0046dc90, storage) == 4) ? 1 : -1];
typedef char ElementStorage_0046dc90_count_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_0046dc90, count) == 8) ? 1 : -1];
typedef char ElementStorage_0046dc90_unknown_0x0c_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_0046dc90, unknown_0x0c) == 12) ? 1 : -1];
typedef char ElementStorage_0046dc90_owns_storage_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_0046dc90, owns_storage) == 13) ? 1 : -1];
typedef char ElementStorage_0046dc90_untouched_0x0e_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_0046dc90, untouched_0x0e) == 14) ? 1 : -1];

struct Element_00605da0 {
    unsigned char first;
    unsigned char second;
    unsigned char third;
    Element_00605da0() : first(0), second(0), third(0) {}
};
typedef char Element_00605da0_stride_check[(sizeof(Element_00605da0) == 3) ? 1 : -1];

class ElementStorage_00605da0 {
public:
    unsigned char* dispatch_table; // 0x00: observed raw table identity.
    Element_00605da0* storage; // 0x04
    int count; // 0x08
    unsigned char unknown_0x0c; // 0x0c
    unsigned char owns_storage; // 0x0d
    unsigned char untouched_0x0e[2];
    ElementStorage_00605da0(int initial_count, Element_00605da0* supplied_storage);
};
typedef char ElementStorage_00605da0_dispatch_table_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_00605da0, dispatch_table) == 0) ? 1 : -1];
typedef char ElementStorage_00605da0_storage_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_00605da0, storage) == 4) ? 1 : -1];
typedef char ElementStorage_00605da0_count_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_00605da0, count) == 8) ? 1 : -1];
typedef char ElementStorage_00605da0_unknown_0x0c_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_00605da0, unknown_0x0c) == 12) ? 1 : -1];
typedef char ElementStorage_00605da0_owns_storage_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_00605da0, owns_storage) == 13) ? 1 : -1];
typedef char ElementStorage_00605da0_untouched_0x0e_offset_check[(RA2_ARRAY_STORAGE_OFFSET_OF(ElementStorage_00605da0, untouched_0x0e) == 14) ? 1 : -1];


#undef RA2_ARRAY_STORAGE_OFFSET_OF
