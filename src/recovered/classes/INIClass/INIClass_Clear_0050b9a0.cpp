// INIClass::Clear (0x0050B9A0)
// With no section: deletes all sections (and their entries), empties the
// section index and frees the comment lines kept from the file head. With a
// section only: removes that section. With both: removes that entry from the
// section. Missing sections or entries are ignored; always returns true.
#include "shared/ini_class.hpp"

bool INIClass::Clear(char const *section, char const *entry)
{
    if (section == 0) {
        SectionList.Delete();
        SectionIndex.Clear();
        while (LineComments != 0) {
            free(LineComments->Value);
            INIComment *next = LineComments->Next;
            delete LineComments;
            LineComments = next;
        }
    } else {
        INISection *secptr = Find_Section(section);
        if (secptr != 0) {
            if (entry != 0) {
                INIEntry *entptr = secptr->Find_Entry(entry);
                if (entptr != 0) {
                    secptr->EntryIndex.Remove_Index(entptr->Index_ID());
                    delete entptr;
                }
            } else {
                SectionIndex.Remove_Index(secptr->Index_ID());
                delete secptr;
            }
        }
    }
    return true;
}
