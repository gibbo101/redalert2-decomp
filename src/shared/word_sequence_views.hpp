#ifndef RA2_RECOVERED_WORD_SEQUENCE_VIEWS_HPP
#define RA2_RECOVERED_WORD_SEQUENCE_VIEWS_HPP

// Bounded x86 storage views established by A3/A4 original proofs. Matching
// offsets do not identify or unify the original concrete game/container classes.
// Unique per-address owner classes retain their original calling conventions.
struct GuardedAddressOffsetView32 {
    unsigned int unknown_0x00;
    unsigned int base_address_word;
    unsigned int unknown_0x08;
    unsigned char offset_gate;
};

struct CountedWordSequenceView32 {
    unsigned int unknown_0x00;
    unsigned int* items;
    int count;
};

struct GuardedWordSequenceView32 {
    unsigned int unknown_0x00;
    unsigned int* items;
    int count;
    unsigned char search_gate;
};

struct WordSequenceCountAt16View32 {
    unsigned int unknown_0x00;
    unsigned int* items;
    unsigned char unknown_0x08[8];
    int count;
};

typedef char OffsetViewSize32[(sizeof(GuardedAddressOffsetView32) == 16) ? 1 : -1];
typedef char CountedViewSize32[(sizeof(CountedWordSequenceView32) == 12) ? 1 : -1];
typedef char GuardedViewSize32[(sizeof(GuardedWordSequenceView32) == 16) ? 1 : -1];
typedef char CountAt16ViewSize32[(sizeof(WordSequenceCountAt16View32) == 20) ? 1 : -1];

#endif
