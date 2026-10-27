#pragma once
#define RA2_ARRAY_EXTENSION_OFFSET_OF(type, member) ((unsigned int)&(((type*)0)->member))

// Observed original-target views. Each address has a distinct owner/type hypothesis.
// No original class names, destructor implementations or complete hierarchy claimed.
void* __cdecl operator new[](unsigned int byte_count);

// Ordinary authored placement-array boilerplate, not original game implementation.
inline void* __cdecl operator new[](unsigned int, void* supplied_storage)
{
    return supplied_storage;
}

typedef char ArrayExtension_pointer_width[(sizeof(void*) == 4) ? 1 : -1];
typedef char ArrayExtension_word_width[(sizeof(unsigned int) == 4) ? 1 : -1];
typedef char ArrayExtension_short_width[(sizeof(unsigned short) == 2) ? 1 : -1];

typedef unsigned short ArrayElementExtension_0042b620;
typedef char ArrayElementExtension_0042b620_stride[(sizeof(ArrayElementExtension_0042b620) == 2) ? 1 : -1];

class ArrayStorageExtension_0042b620 {
public:
    unsigned char* dispatch_table;
    ArrayElementExtension_0042b620* storage;
    int count;
    unsigned char unknown_0x0c; // Original only establishes the constant1 here.
    unsigned char owns_storage; // Observed supplied-vs-allocated branch, including failure.
    unsigned char untouched_0x0e[2];
    ArrayStorageExtension_0042b620(int initial_count, ArrayElementExtension_0042b620* supplied_storage);
};
typedef char ArrayStorageExtension_0042b620_dispatch_table_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0042b620, dispatch_table) == 0) ? 1 : -1];
typedef char ArrayStorageExtension_0042b620_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0042b620, storage) == 4) ? 1 : -1];
typedef char ArrayStorageExtension_0042b620_count_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0042b620, count) == 8) ? 1 : -1];
typedef char ArrayStorageExtension_0042b620_unknown_0x0c_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0042b620, unknown_0x0c) == 12) ? 1 : -1];
typedef char ArrayStorageExtension_0042b620_owns_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0042b620, owns_storage) == 13) ? 1 : -1];
typedef char ArrayStorageExtension_0042b620_untouched_0x0e_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0042b620, untouched_0x0e) == 14) ? 1 : -1];
typedef char ArrayStorageExtension_0042b620_view_extent[(sizeof(ArrayStorageExtension_0042b620) == 16) ? 1 : -1];

struct ArrayElementExtension_0042ce60 {
    unsigned int opaque_words[1];
    ArrayElementExtension_0042ce60() {}
};
typedef char ArrayElementExtension_0042ce60_stride[(sizeof(ArrayElementExtension_0042ce60) == 4) ? 1 : -1];

extern "C" unsigned char array_extension_base_dispatch_0042ce60[];
class ArrayStorageBaseExtension_0042ce60 {
public:
    unsigned char* dispatch_table;
    ArrayElementExtension_0042ce60* storage;
    int count;
    unsigned char unknown_0x0c; // Original only establishes the constant1 here.
    unsigned char owns_storage; // Observed supplied-vs-allocated branch, including failure.
    unsigned char untouched_0x0e[2];
    ArrayStorageBaseExtension_0042ce60(int initial_count, ArrayElementExtension_0042ce60* supplied_storage)
        : storage(0), count(initial_count), unknown_0x0c(1), owns_storage(0)
    {
        dispatch_table = array_extension_base_dispatch_0042ce60;
        if (initial_count != 0) {
            if (supplied_storage != 0) {
                storage = new (supplied_storage) ArrayElementExtension_0042ce60[initial_count];
            } else {
                storage = new ArrayElementExtension_0042ce60[initial_count];
                owns_storage = 1;
            }
        }
    }
};
typedef char ArrayStorageBaseExtension_0042ce60_dispatch_table_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_0042ce60, dispatch_table) == 0) ? 1 : -1];
typedef char ArrayStorageBaseExtension_0042ce60_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_0042ce60, storage) == 4) ? 1 : -1];
typedef char ArrayStorageBaseExtension_0042ce60_count_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_0042ce60, count) == 8) ? 1 : -1];
typedef char ArrayStorageBaseExtension_0042ce60_unknown_0x0c_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_0042ce60, unknown_0x0c) == 12) ? 1 : -1];
typedef char ArrayStorageBaseExtension_0042ce60_owns_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_0042ce60, owns_storage) == 13) ? 1 : -1];
typedef char ArrayStorageBaseExtension_0042ce60_untouched_0x0e_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_0042ce60, untouched_0x0e) == 14) ? 1 : -1];
typedef char ArrayStorageBaseExtension_0042ce60_view_extent[(sizeof(ArrayStorageBaseExtension_0042ce60) == 16) ? 1 : -1];

// A local base projection models the observed transient/final table sequence.
// It does not merge this address with another recovered owner identity.
class ArrayStorageExtension_0042ce60 : public ArrayStorageBaseExtension_0042ce60 {
public:
    unsigned int unknown_0x10;
    int unknown_0x14;
    ArrayStorageExtension_0042ce60(int initial_count, ArrayElementExtension_0042ce60* supplied_storage);
};
typedef char ArrayStorageExtension_0042ce60_unknown_0x10_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0042ce60, unknown_0x10) == 16) ? 1 : -1];
typedef char ArrayStorageExtension_0042ce60_unknown_0x14_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0042ce60, unknown_0x14) == 20) ? 1 : -1];
typedef char ArrayStorageExtension_0042ce60_view_extent[(sizeof(ArrayStorageExtension_0042ce60) == 24) ? 1 : -1];

struct ArrayElementExtension_0042d430 {
    unsigned int opaque_words[4];
    ArrayElementExtension_0042d430() {}
};
typedef char ArrayElementExtension_0042d430_stride[(sizeof(ArrayElementExtension_0042d430) == 16) ? 1 : -1];

class ArrayStorageExtension_0042d430 {
public:
    unsigned char* dispatch_table;
    ArrayElementExtension_0042d430* storage;
    int count;
    unsigned char unknown_0x0c; // Original only establishes the constant1 here.
    unsigned char owns_storage; // Observed supplied-vs-allocated branch, including failure.
    unsigned char untouched_0x0e[2];
    ArrayStorageExtension_0042d430(int initial_count, ArrayElementExtension_0042d430* supplied_storage);
};
typedef char ArrayStorageExtension_0042d430_dispatch_table_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0042d430, dispatch_table) == 0) ? 1 : -1];
typedef char ArrayStorageExtension_0042d430_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0042d430, storage) == 4) ? 1 : -1];
typedef char ArrayStorageExtension_0042d430_count_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0042d430, count) == 8) ? 1 : -1];
typedef char ArrayStorageExtension_0042d430_unknown_0x0c_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0042d430, unknown_0x0c) == 12) ? 1 : -1];
typedef char ArrayStorageExtension_0042d430_owns_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0042d430, owns_storage) == 13) ? 1 : -1];
typedef char ArrayStorageExtension_0042d430_untouched_0x0e_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0042d430, untouched_0x0e) == 14) ? 1 : -1];
typedef char ArrayStorageExtension_0042d430_view_extent[(sizeof(ArrayStorageExtension_0042d430) == 16) ? 1 : -1];

struct ArrayElementExtension_004c2520 {
    unsigned int first;
    unsigned int second;
    unsigned char byte_0x08;
    unsigned char untouched_0x09[3];
    unsigned int word_0x0c;
    ArrayElementExtension_004c2520() : first(0), second(0), byte_0x08(0), word_0x0c(0) {}
};
typedef char ArrayElementExtension_004c2520_stride[(sizeof(ArrayElementExtension_004c2520) == 16) ? 1 : -1];

class ArrayStorageExtension_004c2520 {
public:
    unsigned char* dispatch_table;
    ArrayElementExtension_004c2520* storage;
    int count;
    unsigned char unknown_0x0c; // Original only establishes the constant1 here.
    unsigned char owns_storage; // Observed supplied-vs-allocated branch, including failure.
    unsigned char untouched_0x0e[2];
    ArrayStorageExtension_004c2520(int initial_count, ArrayElementExtension_004c2520* supplied_storage);
};
typedef char ArrayStorageExtension_004c2520_dispatch_table_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_004c2520, dispatch_table) == 0) ? 1 : -1];
typedef char ArrayStorageExtension_004c2520_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_004c2520, storage) == 4) ? 1 : -1];
typedef char ArrayStorageExtension_004c2520_count_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_004c2520, count) == 8) ? 1 : -1];
typedef char ArrayStorageExtension_004c2520_unknown_0x0c_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_004c2520, unknown_0x0c) == 12) ? 1 : -1];
typedef char ArrayStorageExtension_004c2520_owns_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_004c2520, owns_storage) == 13) ? 1 : -1];
typedef char ArrayStorageExtension_004c2520_untouched_0x0e_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_004c2520, untouched_0x0e) == 14) ? 1 : -1];
typedef char ArrayStorageExtension_004c2520_view_extent[(sizeof(ArrayStorageExtension_004c2520) == 16) ? 1 : -1];

struct ArrayElementExtension_004f8ae0 {
    unsigned int first;
    unsigned int second;
    ArrayElementExtension_004f8ae0() : first(0), second(0) {}
};
typedef char ArrayElementExtension_004f8ae0_stride[(sizeof(ArrayElementExtension_004f8ae0) == 8) ? 1 : -1];

class ArrayStorageExtension_004f8ae0 {
public:
    unsigned char* dispatch_table;
    ArrayElementExtension_004f8ae0* storage;
    int count;
    unsigned char unknown_0x0c; // Original only establishes the constant1 here.
    unsigned char owns_storage; // Observed supplied-vs-allocated branch, including failure.
    unsigned char untouched_0x0e[2];
    ArrayStorageExtension_004f8ae0(int initial_count, ArrayElementExtension_004f8ae0* supplied_storage);
};
typedef char ArrayStorageExtension_004f8ae0_dispatch_table_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_004f8ae0, dispatch_table) == 0) ? 1 : -1];
typedef char ArrayStorageExtension_004f8ae0_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_004f8ae0, storage) == 4) ? 1 : -1];
typedef char ArrayStorageExtension_004f8ae0_count_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_004f8ae0, count) == 8) ? 1 : -1];
typedef char ArrayStorageExtension_004f8ae0_unknown_0x0c_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_004f8ae0, unknown_0x0c) == 12) ? 1 : -1];
typedef char ArrayStorageExtension_004f8ae0_owns_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_004f8ae0, owns_storage) == 13) ? 1 : -1];
typedef char ArrayStorageExtension_004f8ae0_untouched_0x0e_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_004f8ae0, untouched_0x0e) == 14) ? 1 : -1];
typedef char ArrayStorageExtension_004f8ae0_view_extent[(sizeof(ArrayStorageExtension_004f8ae0) == 16) ? 1 : -1];

typedef unsigned char ArrayElementExtension_004f8d20;
typedef char ArrayElementExtension_004f8d20_stride[(sizeof(ArrayElementExtension_004f8d20) == 1) ? 1 : -1];

class ArrayStorageExtension_004f8d20 {
public:
    unsigned char* dispatch_table;
    ArrayElementExtension_004f8d20* storage;
    int count;
    unsigned char unknown_0x0c; // Original only establishes the constant1 here.
    unsigned char owns_storage; // Observed supplied-vs-allocated branch, including failure.
    unsigned char untouched_0x0e[2];
    ArrayStorageExtension_004f8d20(int initial_count, ArrayElementExtension_004f8d20* supplied_storage);
};
typedef char ArrayStorageExtension_004f8d20_dispatch_table_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_004f8d20, dispatch_table) == 0) ? 1 : -1];
typedef char ArrayStorageExtension_004f8d20_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_004f8d20, storage) == 4) ? 1 : -1];
typedef char ArrayStorageExtension_004f8d20_count_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_004f8d20, count) == 8) ? 1 : -1];
typedef char ArrayStorageExtension_004f8d20_unknown_0x0c_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_004f8d20, unknown_0x0c) == 12) ? 1 : -1];
typedef char ArrayStorageExtension_004f8d20_owns_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_004f8d20, owns_storage) == 13) ? 1 : -1];
typedef char ArrayStorageExtension_004f8d20_untouched_0x0e_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_004f8d20, untouched_0x0e) == 14) ? 1 : -1];
typedef char ArrayStorageExtension_004f8d20_view_extent[(sizeof(ArrayStorageExtension_004f8d20) == 16) ? 1 : -1];

struct ArrayElementExtension_0056cb90 {
    unsigned short first;
    unsigned short second;
    unsigned short third;
    unsigned short fourth;
    unsigned char byte_0x08;
    unsigned char untouched_0x09[3];
    int word_0x0c;
    ArrayElementExtension_0056cb90() : first(0), second(0), third(0), fourth(0), byte_0x08(0), word_0x0c(-1) {}
};
typedef char ArrayElementExtension_0056cb90_stride[(sizeof(ArrayElementExtension_0056cb90) == 16) ? 1 : -1];

class ArrayStorageExtension_0056cb90 {
public:
    unsigned char* dispatch_table;
    ArrayElementExtension_0056cb90* storage;
    int count;
    unsigned char unknown_0x0c; // Original only establishes the constant1 here.
    unsigned char owns_storage; // Observed supplied-vs-allocated branch, including failure.
    unsigned char untouched_0x0e[2];
    ArrayStorageExtension_0056cb90(int initial_count, ArrayElementExtension_0056cb90* supplied_storage);
};
typedef char ArrayStorageExtension_0056cb90_dispatch_table_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0056cb90, dispatch_table) == 0) ? 1 : -1];
typedef char ArrayStorageExtension_0056cb90_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0056cb90, storage) == 4) ? 1 : -1];
typedef char ArrayStorageExtension_0056cb90_count_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0056cb90, count) == 8) ? 1 : -1];
typedef char ArrayStorageExtension_0056cb90_unknown_0x0c_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0056cb90, unknown_0x0c) == 12) ? 1 : -1];
typedef char ArrayStorageExtension_0056cb90_owns_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0056cb90, owns_storage) == 13) ? 1 : -1];
typedef char ArrayStorageExtension_0056cb90_untouched_0x0e_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0056cb90, untouched_0x0e) == 14) ? 1 : -1];
typedef char ArrayStorageExtension_0056cb90_view_extent[(sizeof(ArrayStorageExtension_0056cb90) == 16) ? 1 : -1];

struct ArrayElementExtension_0056ce50 {
    unsigned int opaque_0x00;
    unsigned int word_0x04;
    unsigned char byte_0x08;
    unsigned char untouched_0x09[3];
    ArrayElementExtension_0056ce50() : word_0x04(0), byte_0x08(0) {}
};
typedef char ArrayElementExtension_0056ce50_stride[(sizeof(ArrayElementExtension_0056ce50) == 12) ? 1 : -1];

class ArrayStorageExtension_0056ce50 {
public:
    unsigned char* dispatch_table;
    ArrayElementExtension_0056ce50* storage;
    int count;
    unsigned char unknown_0x0c; // Original only establishes the constant1 here.
    unsigned char owns_storage; // Observed supplied-vs-allocated branch, including failure.
    unsigned char untouched_0x0e[2];
    ArrayStorageExtension_0056ce50(int initial_count, ArrayElementExtension_0056ce50* supplied_storage);
};
typedef char ArrayStorageExtension_0056ce50_dispatch_table_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0056ce50, dispatch_table) == 0) ? 1 : -1];
typedef char ArrayStorageExtension_0056ce50_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0056ce50, storage) == 4) ? 1 : -1];
typedef char ArrayStorageExtension_0056ce50_count_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0056ce50, count) == 8) ? 1 : -1];
typedef char ArrayStorageExtension_0056ce50_unknown_0x0c_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0056ce50, unknown_0x0c) == 12) ? 1 : -1];
typedef char ArrayStorageExtension_0056ce50_owns_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0056ce50, owns_storage) == 13) ? 1 : -1];
typedef char ArrayStorageExtension_0056ce50_untouched_0x0e_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0056ce50, untouched_0x0e) == 14) ? 1 : -1];
typedef char ArrayStorageExtension_0056ce50_view_extent[(sizeof(ArrayStorageExtension_0056ce50) == 16) ? 1 : -1];

struct ArrayElementExtension_0058f260 {
    unsigned int opaque_words[4];
    ArrayElementExtension_0058f260() {}
};
typedef char ArrayElementExtension_0058f260_stride[(sizeof(ArrayElementExtension_0058f260) == 16) ? 1 : -1];

class ArrayStorageExtension_0058f260 {
public:
    unsigned char* dispatch_table;
    ArrayElementExtension_0058f260* storage;
    int count;
    unsigned char unknown_0x0c; // Original only establishes the constant1 here.
    unsigned char owns_storage; // Observed supplied-vs-allocated branch, including failure.
    unsigned char untouched_0x0e[2];
    ArrayStorageExtension_0058f260(int initial_count, ArrayElementExtension_0058f260* supplied_storage);
};
typedef char ArrayStorageExtension_0058f260_dispatch_table_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0058f260, dispatch_table) == 0) ? 1 : -1];
typedef char ArrayStorageExtension_0058f260_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0058f260, storage) == 4) ? 1 : -1];
typedef char ArrayStorageExtension_0058f260_count_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0058f260, count) == 8) ? 1 : -1];
typedef char ArrayStorageExtension_0058f260_unknown_0x0c_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0058f260, unknown_0x0c) == 12) ? 1 : -1];
typedef char ArrayStorageExtension_0058f260_owns_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0058f260, owns_storage) == 13) ? 1 : -1];
typedef char ArrayStorageExtension_0058f260_untouched_0x0e_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0058f260, untouched_0x0e) == 14) ? 1 : -1];
typedef char ArrayStorageExtension_0058f260_view_extent[(sizeof(ArrayStorageExtension_0058f260) == 16) ? 1 : -1];

struct ArrayElementExtension_0059ffe0 {
    unsigned int opaque_words[2];
    ArrayElementExtension_0059ffe0() {}
};
typedef char ArrayElementExtension_0059ffe0_stride[(sizeof(ArrayElementExtension_0059ffe0) == 8) ? 1 : -1];

extern "C" unsigned char array_extension_base_dispatch_0059ffe0[];
class ArrayStorageBaseExtension_0059ffe0 {
public:
    unsigned char* dispatch_table;
    ArrayElementExtension_0059ffe0* storage;
    int count;
    unsigned char unknown_0x0c; // Original only establishes the constant1 here.
    unsigned char owns_storage; // Observed supplied-vs-allocated branch, including failure.
    unsigned char untouched_0x0e[2];
    ArrayStorageBaseExtension_0059ffe0(int initial_count, ArrayElementExtension_0059ffe0* supplied_storage)
        : storage(0), count(initial_count), unknown_0x0c(1), owns_storage(0)
    {
        dispatch_table = array_extension_base_dispatch_0059ffe0;
        if (initial_count != 0) {
            if (supplied_storage != 0) {
                storage = new (supplied_storage) ArrayElementExtension_0059ffe0[initial_count];
            } else {
                storage = new ArrayElementExtension_0059ffe0[initial_count];
                owns_storage = 1;
            }
        }
    }
};
typedef char ArrayStorageBaseExtension_0059ffe0_dispatch_table_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_0059ffe0, dispatch_table) == 0) ? 1 : -1];
typedef char ArrayStorageBaseExtension_0059ffe0_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_0059ffe0, storage) == 4) ? 1 : -1];
typedef char ArrayStorageBaseExtension_0059ffe0_count_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_0059ffe0, count) == 8) ? 1 : -1];
typedef char ArrayStorageBaseExtension_0059ffe0_unknown_0x0c_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_0059ffe0, unknown_0x0c) == 12) ? 1 : -1];
typedef char ArrayStorageBaseExtension_0059ffe0_owns_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_0059ffe0, owns_storage) == 13) ? 1 : -1];
typedef char ArrayStorageBaseExtension_0059ffe0_untouched_0x0e_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_0059ffe0, untouched_0x0e) == 14) ? 1 : -1];
typedef char ArrayStorageBaseExtension_0059ffe0_view_extent[(sizeof(ArrayStorageBaseExtension_0059ffe0) == 16) ? 1 : -1];

// A local base projection models the observed transient/final table sequence.
// It does not merge this address with another recovered owner identity.
class ArrayStorageExtension_0059ffe0 : public ArrayStorageBaseExtension_0059ffe0 {
public:
    unsigned int unknown_0x10;
    int unknown_0x14;
    ArrayStorageExtension_0059ffe0(int initial_count, ArrayElementExtension_0059ffe0* supplied_storage);
};
typedef char ArrayStorageExtension_0059ffe0_unknown_0x10_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0059ffe0, unknown_0x10) == 16) ? 1 : -1];
typedef char ArrayStorageExtension_0059ffe0_unknown_0x14_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_0059ffe0, unknown_0x14) == 20) ? 1 : -1];
typedef char ArrayStorageExtension_0059ffe0_view_extent[(sizeof(ArrayStorageExtension_0059ffe0) == 24) ? 1 : -1];

struct ArrayElementExtension_006051f0 {
    unsigned char first;
    unsigned char second;
    unsigned char third;
    ArrayElementExtension_006051f0() : first(0), second(0), third(0) {}
};
typedef char ArrayElementExtension_006051f0_stride[(sizeof(ArrayElementExtension_006051f0) == 3) ? 1 : -1];

extern "C" unsigned char array_extension_base_dispatch_006051f0[];
class ArrayStorageBaseExtension_006051f0 {
public:
    unsigned char* dispatch_table;
    ArrayElementExtension_006051f0* storage;
    int count;
    unsigned char unknown_0x0c; // Original only establishes the constant1 here.
    unsigned char owns_storage; // Observed supplied-vs-allocated branch, including failure.
    unsigned char untouched_0x0e[2];
    ArrayStorageBaseExtension_006051f0(int initial_count, ArrayElementExtension_006051f0* supplied_storage)
        : storage(0), count(initial_count), unknown_0x0c(1), owns_storage(0)
    {
        dispatch_table = array_extension_base_dispatch_006051f0;
        if (initial_count != 0) {
            if (supplied_storage != 0) {
                storage = new (supplied_storage) ArrayElementExtension_006051f0[initial_count];
            } else {
                storage = new ArrayElementExtension_006051f0[initial_count];
                owns_storage = 1;
            }
        }
    }
};
typedef char ArrayStorageBaseExtension_006051f0_dispatch_table_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_006051f0, dispatch_table) == 0) ? 1 : -1];
typedef char ArrayStorageBaseExtension_006051f0_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_006051f0, storage) == 4) ? 1 : -1];
typedef char ArrayStorageBaseExtension_006051f0_count_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_006051f0, count) == 8) ? 1 : -1];
typedef char ArrayStorageBaseExtension_006051f0_unknown_0x0c_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_006051f0, unknown_0x0c) == 12) ? 1 : -1];
typedef char ArrayStorageBaseExtension_006051f0_owns_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_006051f0, owns_storage) == 13) ? 1 : -1];
typedef char ArrayStorageBaseExtension_006051f0_untouched_0x0e_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_006051f0, untouched_0x0e) == 14) ? 1 : -1];
typedef char ArrayStorageBaseExtension_006051f0_view_extent[(sizeof(ArrayStorageBaseExtension_006051f0) == 16) ? 1 : -1];

// A local base projection models the observed transient/final table sequence.
// It does not merge this address with another recovered owner identity.
class ArrayStorageExtension_006051f0 : public ArrayStorageBaseExtension_006051f0 {
public:
    unsigned int unknown_0x10;
    int unknown_0x14;
    ArrayStorageExtension_006051f0(int initial_count, ArrayElementExtension_006051f0* supplied_storage);
};
typedef char ArrayStorageExtension_006051f0_unknown_0x10_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_006051f0, unknown_0x10) == 16) ? 1 : -1];
typedef char ArrayStorageExtension_006051f0_unknown_0x14_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_006051f0, unknown_0x14) == 20) ? 1 : -1];
typedef char ArrayStorageExtension_006051f0_view_extent[(sizeof(ArrayStorageExtension_006051f0) == 24) ? 1 : -1];

struct ArrayElementExtension_00621fa0 {
    unsigned char first;
    unsigned char second;
    unsigned char third;
    ArrayElementExtension_00621fa0() : first(0), second(0), third(0) {}
};
typedef char ArrayElementExtension_00621fa0_stride[(sizeof(ArrayElementExtension_00621fa0) == 3) ? 1 : -1];

extern "C" unsigned char array_extension_base_dispatch_00621fa0[];
class ArrayStorageBaseExtension_00621fa0 {
public:
    unsigned char* dispatch_table;
    ArrayElementExtension_00621fa0* storage;
    int count;
    unsigned char unknown_0x0c; // Original only establishes the constant1 here.
    unsigned char owns_storage; // Observed supplied-vs-allocated branch, including failure.
    unsigned char untouched_0x0e[2];
    ArrayStorageBaseExtension_00621fa0(int initial_count, ArrayElementExtension_00621fa0* supplied_storage)
        : storage(0), count(initial_count), unknown_0x0c(1), owns_storage(0)
    {
        dispatch_table = array_extension_base_dispatch_00621fa0;
        if (initial_count != 0) {
            if (supplied_storage != 0) {
                storage = new (supplied_storage) ArrayElementExtension_00621fa0[initial_count];
            } else {
                storage = new ArrayElementExtension_00621fa0[initial_count];
                owns_storage = 1;
            }
        }
    }
};
typedef char ArrayStorageBaseExtension_00621fa0_dispatch_table_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_00621fa0, dispatch_table) == 0) ? 1 : -1];
typedef char ArrayStorageBaseExtension_00621fa0_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_00621fa0, storage) == 4) ? 1 : -1];
typedef char ArrayStorageBaseExtension_00621fa0_count_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_00621fa0, count) == 8) ? 1 : -1];
typedef char ArrayStorageBaseExtension_00621fa0_unknown_0x0c_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_00621fa0, unknown_0x0c) == 12) ? 1 : -1];
typedef char ArrayStorageBaseExtension_00621fa0_owns_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_00621fa0, owns_storage) == 13) ? 1 : -1];
typedef char ArrayStorageBaseExtension_00621fa0_untouched_0x0e_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_00621fa0, untouched_0x0e) == 14) ? 1 : -1];
typedef char ArrayStorageBaseExtension_00621fa0_view_extent[(sizeof(ArrayStorageBaseExtension_00621fa0) == 16) ? 1 : -1];

// A local base projection models the observed transient/final table sequence.
// It does not merge this address with another recovered owner identity.
class ArrayStorageExtension_00621fa0 : public ArrayStorageBaseExtension_00621fa0 {
public:
    unsigned int unknown_0x10;
    int unknown_0x14;
    ArrayStorageExtension_00621fa0(int initial_count, ArrayElementExtension_00621fa0* supplied_storage);
};
typedef char ArrayStorageExtension_00621fa0_unknown_0x10_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_00621fa0, unknown_0x10) == 16) ? 1 : -1];
typedef char ArrayStorageExtension_00621fa0_unknown_0x14_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_00621fa0, unknown_0x14) == 20) ? 1 : -1];
typedef char ArrayStorageExtension_00621fa0_view_extent[(sizeof(ArrayStorageExtension_00621fa0) == 24) ? 1 : -1];

struct ArrayElementExtension_00635110 {
    unsigned int first;
    unsigned int second;
    unsigned int third;
    unsigned int opaque_0x0c;
    ArrayElementExtension_00635110() : first(0), second(0), third(0) {}
};
typedef char ArrayElementExtension_00635110_stride[(sizeof(ArrayElementExtension_00635110) == 16) ? 1 : -1];

extern "C" unsigned char array_extension_base_dispatch_00635110[];
class ArrayStorageBaseExtension_00635110 {
public:
    unsigned char* dispatch_table;
    ArrayElementExtension_00635110* storage;
    int count;
    unsigned char unknown_0x0c; // Original only establishes the constant1 here.
    unsigned char owns_storage; // Observed supplied-vs-allocated branch, including failure.
    unsigned char untouched_0x0e[2];
    ArrayStorageBaseExtension_00635110(int initial_count, ArrayElementExtension_00635110* supplied_storage)
        : storage(0), count(initial_count), unknown_0x0c(1), owns_storage(0)
    {
        dispatch_table = array_extension_base_dispatch_00635110;
        if (initial_count != 0) {
            if (supplied_storage != 0) {
                storage = new (supplied_storage) ArrayElementExtension_00635110[initial_count];
            } else {
                storage = new ArrayElementExtension_00635110[initial_count];
                owns_storage = 1;
            }
        }
    }
};
typedef char ArrayStorageBaseExtension_00635110_dispatch_table_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_00635110, dispatch_table) == 0) ? 1 : -1];
typedef char ArrayStorageBaseExtension_00635110_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_00635110, storage) == 4) ? 1 : -1];
typedef char ArrayStorageBaseExtension_00635110_count_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_00635110, count) == 8) ? 1 : -1];
typedef char ArrayStorageBaseExtension_00635110_unknown_0x0c_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_00635110, unknown_0x0c) == 12) ? 1 : -1];
typedef char ArrayStorageBaseExtension_00635110_owns_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_00635110, owns_storage) == 13) ? 1 : -1];
typedef char ArrayStorageBaseExtension_00635110_untouched_0x0e_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_00635110, untouched_0x0e) == 14) ? 1 : -1];
typedef char ArrayStorageBaseExtension_00635110_view_extent[(sizeof(ArrayStorageBaseExtension_00635110) == 16) ? 1 : -1];

// A local base projection models the observed transient/final table sequence.
// It does not merge this address with another recovered owner identity.
class ArrayStorageExtension_00635110 : public ArrayStorageBaseExtension_00635110 {
public:
    unsigned int unknown_0x10;
    int unknown_0x14;
    ArrayStorageExtension_00635110(int initial_count, ArrayElementExtension_00635110* supplied_storage);
};
typedef char ArrayStorageExtension_00635110_unknown_0x10_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_00635110, unknown_0x10) == 16) ? 1 : -1];
typedef char ArrayStorageExtension_00635110_unknown_0x14_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_00635110, unknown_0x14) == 20) ? 1 : -1];
typedef char ArrayStorageExtension_00635110_view_extent[(sizeof(ArrayStorageExtension_00635110) == 24) ? 1 : -1];

struct ArrayElementExtension_00682580 {
    unsigned int opaque_words[2];
    ArrayElementExtension_00682580() {}
};
typedef char ArrayElementExtension_00682580_stride[(sizeof(ArrayElementExtension_00682580) == 8) ? 1 : -1];

extern "C" unsigned char array_extension_base_dispatch_00682580[];
class ArrayStorageBaseExtension_00682580 {
public:
    unsigned char* dispatch_table;
    ArrayElementExtension_00682580* storage;
    int count;
    unsigned char unknown_0x0c; // Original only establishes the constant1 here.
    unsigned char owns_storage; // Observed supplied-vs-allocated branch, including failure.
    unsigned char untouched_0x0e[2];
    ArrayStorageBaseExtension_00682580(int initial_count, ArrayElementExtension_00682580* supplied_storage)
        : storage(0), count(initial_count), unknown_0x0c(1), owns_storage(0)
    {
        dispatch_table = array_extension_base_dispatch_00682580;
        if (initial_count != 0) {
            if (supplied_storage != 0) {
                storage = new (supplied_storage) ArrayElementExtension_00682580[initial_count];
            } else {
                storage = new ArrayElementExtension_00682580[initial_count];
                owns_storage = 1;
            }
        }
    }
};
typedef char ArrayStorageBaseExtension_00682580_dispatch_table_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_00682580, dispatch_table) == 0) ? 1 : -1];
typedef char ArrayStorageBaseExtension_00682580_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_00682580, storage) == 4) ? 1 : -1];
typedef char ArrayStorageBaseExtension_00682580_count_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_00682580, count) == 8) ? 1 : -1];
typedef char ArrayStorageBaseExtension_00682580_unknown_0x0c_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_00682580, unknown_0x0c) == 12) ? 1 : -1];
typedef char ArrayStorageBaseExtension_00682580_owns_storage_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_00682580, owns_storage) == 13) ? 1 : -1];
typedef char ArrayStorageBaseExtension_00682580_untouched_0x0e_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageBaseExtension_00682580, untouched_0x0e) == 14) ? 1 : -1];
typedef char ArrayStorageBaseExtension_00682580_view_extent[(sizeof(ArrayStorageBaseExtension_00682580) == 16) ? 1 : -1];

// A local base projection models the observed transient/final table sequence.
// It does not merge this address with another recovered owner identity.
class ArrayStorageExtension_00682580 : public ArrayStorageBaseExtension_00682580 {
public:
    unsigned int unknown_0x10;
    int unknown_0x14;
    ArrayStorageExtension_00682580(int initial_count, ArrayElementExtension_00682580* supplied_storage);
};
typedef char ArrayStorageExtension_00682580_unknown_0x10_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_00682580, unknown_0x10) == 16) ? 1 : -1];
typedef char ArrayStorageExtension_00682580_unknown_0x14_offset[(RA2_ARRAY_EXTENSION_OFFSET_OF(ArrayStorageExtension_00682580, unknown_0x14) == 20) ? 1 : -1];
typedef char ArrayStorageExtension_00682580_view_extent[(sizeof(ArrayStorageExtension_00682580) == 24) ? 1 : -1];

#undef RA2_ARRAY_EXTENSION_OFFSET_OF
