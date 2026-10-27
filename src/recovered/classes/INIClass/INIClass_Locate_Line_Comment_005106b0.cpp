// INIClass::Locate_Line_Comment (0x005106B0)
// Scans an entry line and records the columns of its first '=', of the first
// visible character after that '=' and of its ';' (tabs advance to the next
// multiple of 8; missing items give column 0). Returns the comment text after
// the ';', or null when the line has no comment.
#include "shared/ini_class.hpp"

char *__fastcall INIClass::Locate_Line_Comment(char *line, int &equals_column, int &value_column,
                                               int &comment_column)
{
    equals_column = -1;
    value_column = -1;
    comment_column = -1;
    char *comment = 0;
    int column = 0;
    while (*line != '\0') {
        if (equals_column >= 0 && value_column < 0 && (unsigned char)*line > ' ') {
            value_column = column;
        }
        if (*line == ';') {
            comment_column = column;
            comment = line + 1;
            break;
        }
        switch (*line) {
            case '\t':
                column = (column & ~7) + 8;
                break;

            case '=':
                if (equals_column < 0) {
                    equals_column = column;
                }
                column++;
                break;

            default:
                column++;
                break;
        }
        line++;
    }
    equals_column = equals_column < 0 ? 0 : equals_column;
    value_column = value_column < 0 ? 0 : value_column;
    comment_column = comment_column < 0 ? 0 : comment_column;
    return comment;
}
