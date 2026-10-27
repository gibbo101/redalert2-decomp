// void UnknownList_00602A60::unknown_delete_all() -- 0x00602A60
// Purpose: deletes every node of the singly linked list headed at +0x04
// (next link at node +0x0C; each node's destructor is 0x004BB060).
// Assumptions: owner and node classes are unidentified; the head is not
// cleared.
// @ref ??1UnknownNode_00602a60@@QAE@XZ=004bb060
// @ref ??3@YAXPAX@Z=00781d3b

struct UnknownNode_00602a60 {
    ~UnknownNode_00602a60();                // 0x004BB060
    int unknown_00;
    int unknown_04;
    int unknown_08;
    UnknownNode_00602a60 *Next;             // +0x0C
};

struct UnknownList_00602a60 {
    int unknown_00;
    UnknownNode_00602a60 *Head;             // +0x04
    void unknown_delete_all();
};

void UnknownList_00602a60::unknown_delete_all()
{
    UnknownNode_00602a60 *node = Head;
    while (node != 0) {
        UnknownNode_00602a60 *next = node->Next;
        delete node;
        node = next;
    }
}
