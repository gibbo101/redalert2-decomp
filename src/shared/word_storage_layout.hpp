#pragma once

// Observed word-storage layouts. Concrete game identities remain unknown.
// Per-address owners stay distinct except seven initializer/copy pairs sharing
// both original table identities and the same observed 24-byte operations.
struct WordStorageLayout {
    unsigned char* dispatch_table;
    unsigned int* storage;
    int capacity; // Signed loop bound; allocation preserves raw32 bits.
    unsigned char unknown_0x0c;
    unsigned char owns_storage;
};
typedef char WordStorageLayout_size_check[(sizeof(WordStorageLayout) == 16) ? 1 : -1];

struct WordStorageView : WordStorageLayout {
    unsigned int unknown_0x10;
    unsigned int unknown_0x14;
};
typedef char WordStorageView_size_check[(sizeof(WordStorageView) == 24) ? 1 : -1];

// Copy0x0046cbf0; base0x0079d9d4, derived0x0079d9f4; clear-slot0x0079d9e0 ->0x0046d160.
class WordStorageCopy_0046cbf0 : private WordStorageView {
public:
    WordStorageCopy_0046cbf0* CopyWordStorage_0046cbf0(const WordStorageCopy_0046cbf0& source);
};

// Copy0x0046ce20; base0x0079d9d4, derived0x0079da94; clear-slot0x0079d9e0 ->0x0046d160.
// Paired initializer0x0046d1f0 shares both tables; original class name unknown.
class WordStorage_0046d1f0 : private WordStorageView {
public:
    WordStorage_0046d1f0* initialize(unsigned int requested_capacity,
        unsigned int* supplied_storage);
    WordStorage_0046d1f0* CopyWordStorage_0046ce20(const WordStorage_0046d1f0& source);
};

// Copy0x004f6f30; base0x007a2ee4, derived0x007a2fec; clear-slot0x007a2ef0 ->0x004f7cd0.
// Paired initializer0x006c03e0 shares both tables; original class name unknown.
class WordStorage_006c03e0 : private WordStorageView {
public:
    WordStorage_006c03e0* initialize(unsigned int requested_capacity,
        unsigned int* supplied_storage);
    WordStorage_006c03e0* CopyWordStorage_004f6f30(const WordStorage_006c03e0& source);
};

// Copy0x004fb410; base0x007a3158, derived0x007a30b8; clear-slot0x007a3164 ->0x004fb1a0.
class WordStorageCopy_004fb410 : private WordStorageView {
public:
    WordStorageCopy_004fb410* CopyWordStorage_004fb410(const WordStorageCopy_004fb410& source);
};

// Copy0x004fb4a0; base0x007a3118, derived0x007a3178; clear-slot0x007a3124 ->0x004faa00.
// Paired initializer0x004faa90 shares both tables; original class name unknown.
class WordStorage_004faa90 : private WordStorageView {
public:
    WordStorage_004faa90* initialize(unsigned int requested_capacity,
        unsigned int* supplied_storage);
    WordStorage_004faa90* CopyWordStorage_004fb4a0(const WordStorage_004faa90& source);
};

// Copy0x004fb530; base0x007a3138, derived0x007a3198; clear-slot0x007a3144 ->0x004fadd0.
// Paired initializer0x004fae60 shares both tables; original class name unknown.
class WordStorage_004fae60 : private WordStorageView {
public:
    WordStorage_004fae60* initialize(unsigned int requested_capacity,
        unsigned int* supplied_storage);
    WordStorage_004fae60* CopyWordStorage_004fb530(const WordStorage_004fae60& source);
};

// Copy0x0050b7d0; base0x007a3b5c, derived0x007a3b3c; clear-slot0x007a3b68 ->0x0050b3f0.
class WordStorageCopy_0050b7d0 : private WordStorageView {
public:
    WordStorageCopy_0050b7d0* CopyWordStorage_0050b7d0(const WordStorageCopy_0050b7d0& source);
};

// Copy0x0058eed0; base0x007a2f08, derived0x007a5e4c; clear-slot0x007a2f14 ->0x004f7100.
class WordStorageCopy_0058eed0 : private WordStorageView {
public:
    WordStorageCopy_0058eed0* CopyWordStorage_0058eed0(const WordStorageCopy_0058eed0& source);
};

// Copy0x005a62d0; base0x007a68c4, derived0x007a68e4; clear-slot0x007a68d0 ->0x005a65c0.
class WordStorageCopy_005a62d0 : private WordStorageView {
public:
    WordStorageCopy_005a62d0* CopyWordStorage_005a62d0(const WordStorageCopy_005a62d0& source);
};

// Copy0x00654570; base0x007a9118, derived0x007a90f8; clear-slot0x007a9124 ->0x006532b0.
class WordStorageCopy_00654570 : private WordStorageView {
public:
    WordStorageCopy_00654570* CopyWordStorage_00654570(const WordStorageCopy_00654570& source);
};

// Copy0x00654600; base0x007a9138, derived0x007a90d8; clear-slot0x007a9144 ->0x006536a0.
class WordStorageCopy_00654600 : private WordStorageView {
public:
    WordStorageCopy_00654600* CopyWordStorage_00654600(const WordStorageCopy_00654600& source);
};

// Copy0x00654690; base0x007a3138, derived0x007a30d8; clear-slot0x007a3144 ->0x004fadd0.
class WordStorageCopy_00654690 : private WordStorageView {
public:
    WordStorageCopy_00654690* CopyWordStorage_00654690(const WordStorageCopy_00654690& source);
};

// Copy0x00654720; base0x007a3118, derived0x007a30f8; clear-slot0x007a3124 ->0x004faa00.
class WordStorageCopy_00654720 : private WordStorageView {
public:
    WordStorageCopy_00654720* CopyWordStorage_00654720(const WordStorageCopy_00654720& source);
};

// Copy0x006547b0; base0x007a2f08, derived0x007a2f28; clear-slot0x007a2f14 ->0x004f7100.
// Paired initializer0x0058e170 shares both tables; original class name unknown.
class WordStorage_0058e170 : private WordStorageView {
public:
    WordStorage_0058e170* initialize(unsigned int requested_capacity,
        unsigned int* supplied_storage);
    WordStorage_0058e170* CopyWordStorage_006547b0(const WordStorage_0058e170& source);
};

// Copy0x00654840; base0x007a9118, derived0x007a9184; clear-slot0x007a9124 ->0x006532b0.
// Paired initializer0x00653340 shares both tables; original class name unknown.
class WordStorage_00653340 : private WordStorageView {
public:
    WordStorage_00653340* initialize(unsigned int requested_capacity,
        unsigned int* supplied_storage);
    WordStorage_00653340* CopyWordStorage_00654840(const WordStorage_00653340& source);
};

// Copy0x006548d0; base0x007a3158, derived0x007a31b8; clear-slot0x007a3164 ->0x004fb1a0.
// Paired initializer0x004fb230 shares both tables; original class name unknown.
class WordStorage_004fb230 : private WordStorageView {
public:
    WordStorage_004fb230* initialize(unsigned int requested_capacity,
        unsigned int* supplied_storage);
    WordStorage_004fb230* CopyWordStorage_006548d0(const WordStorage_004fb230& source);
};

// Copy0x006df9e0; base0x0079d0ac, derived0x007ad144; clear-slot0x0079d0b8 ->0x00453fc0.
class WordStorageCopy_006df9e0 : private WordStorageView {
public:
    WordStorageCopy_006df9e0* CopyWordStorage_006df9e0(const WordStorageCopy_006df9e0& source);
};
