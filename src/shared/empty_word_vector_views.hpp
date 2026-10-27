#pragma once
#include "shared/word_storage_layout.hpp"

// Minimum observed 24-byte views; concrete game identities remain unknown.
// Ordinary constructor syntax is a first ABI hypothesis, not recovered API identity.
// Explicit dispatch word is observed data, with no C++ virtual hierarchy invented.

// Entry 0x004fa630; observed dispatch 0x007a30b8; bytes 0x0e/0x0f untouched.
class EmptyWordVector_004fa630 : private WordStorageView {
public:
    EmptyWordVector_004fa630();
};

// Entry 0x00652a70; observed dispatch 0x007a90f8; bytes 0x0e/0x0f untouched.
class EmptyWordVector_00652a70 : private WordStorageView {
public:
    EmptyWordVector_00652a70();
};

// Entry 0x00652b50; observed dispatch 0x007a3b3c; bytes 0x0e/0x0f untouched.
class EmptyWordVector_00652b50 : private WordStorageView {
public:
    EmptyWordVector_00652b50();
};

// Entry 0x00652bd0; observed dispatch 0x0079d9f4; bytes 0x0e/0x0f untouched.
class EmptyWordVector_00652bd0 : private WordStorageView {
public:
    EmptyWordVector_00652bd0();
};

// Entry 0x00652c50; observed dispatch 0x007a90d8; bytes 0x0e/0x0f untouched.
class EmptyWordVector_00652c50 : private WordStorageView {
public:
    EmptyWordVector_00652c50();
};

// Entry 0x00652dc0; observed dispatch 0x007a30d8; bytes 0x0e/0x0f untouched.
class EmptyWordVector_00652dc0 : private WordStorageView {
public:
    EmptyWordVector_00652dc0();
};

// Entry 0x00652e90; observed dispatch 0x007a30f8; bytes 0x0e/0x0f untouched.
class EmptyWordVector_00652e90 : private WordStorageView {
public:
    EmptyWordVector_00652e90();
};

// Entry 0x00652f10; observed dispatch 0x007a90b8; bytes 0x0e/0x0f untouched.
class EmptyWordVector_00652f10 : private WordStorageView {
public:
    EmptyWordVector_00652f10();
};

// Entry 0x006df7c0; observed dispatch 0x007ad144; bytes 0x0e/0x0f untouched.
class EmptyWordVector_006df7c0 : private WordStorageView {
public:
    EmptyWordVector_006df7c0();
};
