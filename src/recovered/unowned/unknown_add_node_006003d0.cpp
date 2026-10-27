// void UnknownNodeList_006003D0::unknown_add_node(int length) -- 0x006003D0
// Purpose: allocates a node with room for `length` 16-bit characters plus
// a 16-byte header (data pointer at +0x08 to its own +0x10, +0x04 = 0)
// and pushes it on the list at +0x34.
// Assumptions: owner and node layout are hypotheses.
// @ref ??2@YAPAXI@Z=00782017

struct UnknownNode_006003d0 {
    UnknownNode_006003d0 *Next;             // +0x00
    int unknown_04;                         // +0x04
    unsigned short *Data;                   // +0x08
    int unknown_0c;
    unsigned short Text[1];                 // +0x10
};
struct UnknownNodeList_006003d0 {
    char unknown_00[0x34];
    UnknownNode_006003d0 *Head;             // +0x34
    void unknown_add_node(int length);
};

void UnknownNodeList_006003d0::unknown_add_node(int length)
{
    UnknownNode_006003d0 *node = (UnknownNode_006003d0 *)operator new(length * 2 + 0x12);
    if (node != 0) {
        node->Data = node->Text;
        node->Next = Head;
        node->unknown_04 = 0;
        Head = node;
    }
}
