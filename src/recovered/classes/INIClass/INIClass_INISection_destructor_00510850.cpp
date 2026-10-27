// INIClass::INISection::~INISection (0x00510850)
// Frees the name, deletes every entry, empties the entry index and frees the
// comment lines above the section header; member destructors then empty the
// index again, unlink any remaining list nodes and unlink the section.
#include "shared/ini_class.hpp"

INIClass::INISection::~INISection()
{
    free(Name);
    Name = 0;
    EntryList.Delete();
    EntryIndex.Clear();
    while (Comments != 0) {
        free(Comments->Value);
        INIComment *next = Comments->Next;
        delete Comments;
        Comments = next;
    }
}
