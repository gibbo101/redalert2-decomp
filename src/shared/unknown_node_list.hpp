// A singly linked list of variable-length nodes headed at +0x34 of its owner
// (0x006003D0 pushes a node, 0x00600410 unlinks and frees one; callers in
// 0x005DE000..0x00601E00). Owner and node layouts are hypotheses.
#ifndef RA2_SHARED_UNKNOWN_NODE_LIST_HPP
#define RA2_SHARED_UNKNOWN_NODE_LIST_HPP

struct UnknownNode_006003d0 {
    UnknownNode_006003d0 *Next;             // +0x00
    int unknown_04;                         // +0x04
    unsigned short *Data;                   // +0x08 (its own Text)
    int unknown_0c;                         // +0x0C
    unsigned short Text[1];                 // +0x10 (the node is allocated with room for the text)
};

struct UnknownNodeList_006003d0 {
    char unknown_00[0x34];
    UnknownNode_006003d0 *Head;             // +0x34
    void unknown_add_node(int length);                      // 0x006003D0
    void unknown_remove_node(UnknownNode_006003d0 *node);   // 0x00600410
};

#endif
