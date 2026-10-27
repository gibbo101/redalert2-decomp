// INIClass::INIEntry::~INIEntry (0x005107C0)
// Frees the key, value, comment lines and trailing comment; the Node base
// destructor then unlinks the entry from its section's list.
#include "shared/ini_class.hpp"

INIClass::INIEntry::~INIEntry()
{
    free(Key);
    Key = 0;
    free(Value);
    Value = 0;
    while (Comments != 0) {
        free(Comments->Value);
        INIComment *next = Comments->Next;
        delete Comments;
        Comments = next;
    }
    free(CommentString);
    CommentString = 0;
}
