// INIClass::Put_String (0x0050E5F0)
// Sets section/entry to a copy of string, creating the section if needed.
// An existing entry is replaced; the comment lines and trailing comment it
// carried (and its three column positions) move to the new entry. A null or
// empty string removes the entry. Returns false on a null section/entry or
// when memory runs out.
#include "shared/ini_class.hpp"

bool INIClass::Put_String(char const *section, char const *entry, char const *string)
{
    if (section == 0 || entry == 0) {
        return false;
    }

    INISection *secptr = Find_Section(section);
    if (secptr == 0) {
        secptr = new INISection(_strdup(section));
        if (secptr == 0) {
            return false;
        }
        SectionList.Add_Tail(secptr);
        SectionIndex.Add_Index(secptr->Index_ID(), secptr);
    }

    INIComment *comments = 0;
    char *comment_string = 0;
    int comment_column = 0;
    int equals_column = 0;
    int value_column = 0;
    INIEntry *entptr = secptr->Find_Entry(entry);
    if (entptr != 0) {
        comment_string = entptr->CommentString;
        comment_column = entptr->CommentColumn;
        comments = entptr->Comments;
        equals_column = entptr->EqualsColumn;
        value_column = entptr->ValueColumn;
        entptr->Comments = 0;
        entptr->CommentString = 0;
        secptr->EntryIndex.Remove_Index(entptr->Index_ID());
        delete entptr;
    }

    if (string != 0 && strlen(string) > 0) {
        entptr = new INIEntry(_strdup(entry), _strdup(string), comments, comment_string,
                              comment_column, equals_column, value_column);
        if (entptr == 0) {
            free(comment_string);
            while (comments != 0) {
                free(comments->Value);
                INIComment *next = comments->Next;
                delete comments;
                comments = next;
            }
            return false;
        }
        secptr->EntryList.Add_Tail(entptr);
        secptr->EntryIndex.Add_Index(entptr->Index_ID(), entptr);
    }
    return true;
}
