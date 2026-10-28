// Two unidentified classes that own a singly linked list, a block and a wide string (their release functions
// 0x00600350 and 0x00602510; the second has four more bytes in front, so it may derive from a class like the first).
#ifndef RA2_SHARED_UNKNOWN_LIST_OWNERS_HPP
#define RA2_SHARED_UNKNOWN_LIST_OWNERS_HPP
class WideString;

struct UnknownListNode {
    UnknownListNode *Next;                  // +0x00
};

class UnknownListOwner_00600350 {
public:
    // Frees the block, every list node and the string (0x00600350).
    void Release_00600350();

    char unknown_00[0x28];
    void *Block;                            // +0x28
    char unknown_2c[0x34 - 0x2C];
    UnknownListNode *List;                  // +0x34
    char unknown_38[0x3C - 0x38];
    WideString *Text;                       // +0x3C
};

class UnknownListOwner_00602510 {
public:
    // The same with a flag: delete this when bit 0 is set (0x00602510).
    int Release_00602510(unsigned char flags);

    char unknown_00[0x2C];
    void *Block;                            // +0x2C
    char unknown_30[0x38 - 0x30];
    UnknownListNode *List;                  // +0x38
    char unknown_3c[0x40 - 0x3C];
    WideString *Text;                       // +0x40
};

#endif
