// INIClass::INIEntry::INIEntry (0x00510B60)
// Takes ownership of the key/value strings, the comment lines above the
// entry and its trailing comment, and records the entry's column positions.
#include "shared/ini_class.hpp"

INIClass::INIEntry::INIEntry(char *key, char *value, INIComment *comments, char *comment_string,
                             int comment_column, int equals_column, int value_column) :
    Key(key),
    Value(value),
    Comments(comments),
    CommentString(comment_string),
    EqualsColumn(equals_column),
    ValueColumn(value_column),
    CommentColumn(comment_column)
{
}
