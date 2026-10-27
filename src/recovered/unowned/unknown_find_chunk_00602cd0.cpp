// UnknownChunk_602cd0 *UnknownChunkList_602cd0::Find(char const *id) -- 0x00602CD0
// Purpose: the first node of the singly linked list (+0x04, next at node
// +0x0C) whose four-character name (node +0x00) equals id; null when none.
// Assumptions: owner and node types are unidentified (no RTTI, no direct
// callers); four-character IDs suggest chunk tags. Names are hypotheses.
// @ref _strncmp=00783810

extern "C" int __cdecl strncmp(char const *left, char const *right, unsigned int count);

struct UnknownChunk_602cd0 {
    char Name[4];
    int unknown_04;
    int unknown_08;
    UnknownChunk_602cd0 *Next;      // +0x0C
};

class UnknownChunkList_602cd0 {
public:
    UnknownChunk_602cd0 *Find(char const *id);

    int unknown_00;
    UnknownChunk_602cd0 *Head;      // +0x04
};

UnknownChunk_602cd0 *UnknownChunkList_602cd0::Find(char const *id)
{
    for (UnknownChunk_602cd0 *chunk = Head; chunk != 0; chunk = chunk->Next) {
        if (strncmp(id, chunk->Name, 4) == 0) {
            return chunk;
        }
    }
    return 0;
}
