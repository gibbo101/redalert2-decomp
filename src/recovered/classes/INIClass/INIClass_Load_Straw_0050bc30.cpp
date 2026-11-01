// INIClass::Load (0x0050BC30)
// Parses INI text from a straw (read through a 4 KB CacheStraw, lines of up
// to 511 bytes).
//
// An empty database is built directly: each "[name]" line starts a section,
// "key=value" lines become entries (key and value trimmed; lines without a
// key or value, or starting with ';' or '=', are skipped) and an empty
// section is dropped. With keep_comments every raw line is also kept as a
// comment line: the lines above a section header belong to the section, the
// lines above an entry to the entry (the entry's own line is blanked), the
// entry's trailing comment and column positions are recorded, and lines
// after the last entry become LineComments.
//
// A database that already has sections is merged instead: comments are not
// kept and every entry goes through Put_String, replacing existing values.
//
// Returns false when the text has no section at all (without keep_comments)
// or when memory runs out (the database is then cleared, except in a merge).
#include "shared/ini_class.hpp"

int INIClass::Load(Straw &file, bool keep_comments)
{
    bool end_of_file = false;
    INIComment *comment_head = 0;
    INIComment *comment_tail = 0;
    INIComment *comment = 0;
    bool merge = false;
    if (Section_Count() > 0) {
        merge = true;
        keep_comments = false;
    }

    CacheStraw ffile;
    ffile.Get_From(file);

    char buffer[512];

    // Comment lines before the first section.
    while (!end_of_file) {
        Read_Line(ffile, buffer, sizeof(buffer), end_of_file);
        if (end_of_file) {
            if (keep_comments) {
                LineComments = comment_head;
                return true;
            }
            while (comment_head != 0) {
                free(comment_head->Value);
                INIComment *next = comment_head->Next;
                delete comment_head;
                comment_head = next;
            }
            return false;
        }
        if (Is_Section_Header(buffer)) {
            break;
        }
        if (keep_comments) {
            comment = new INIComment;
            if (comment == 0) {
                keep_comments = false;
            }
        }
        if (keep_comments) {
            if (comment_tail != 0) {
                comment_tail->Next = comment;
                comment_tail = comment;
            } else {
                comment_tail = comment;
                comment_head = comment;
            }
            comment_tail->Value = _strdup(buffer);
        }
    }

    if (merge) {
        while (!end_of_file) {
            char section[512];
            section[0] = '\0';
            strtrim(buffer);
            if (buffer[0] == '[') {
                char *end = strchr(buffer, ']');
                if (end != 0) {
                    *end = '\0';
                }
                strcpy(section, &buffer[1]);
            }

            while (!end_of_file) {
                int length = Read_Line(ffile, buffer, sizeof(buffer), end_of_file);
                if (Is_Section_Header(buffer)) {
                    break;
                }
                Strip_Comments(buffer);
                if (length == 0 || buffer[0] == ';' || buffer[0] == '=') {
                    continue;
                }
                char *divider = strchr(buffer, '=');
                if (divider != 0) {
                    *divider++ = '\0';
                    strtrim(buffer);
                    if (strlen(buffer) == 0) {
                        continue;
                    }
                    strtrim(divider);
                    if (strlen(divider) == 0) {
                        continue;
                    }
                    if (!Put_String(section, buffer, divider)) {
                        return false;
                    }
                }
            }
        }
    } else {
        while (LineComments != 0) {
            free(LineComments->Value);
            INIComment *next = LineComments->Next;
            delete LineComments;
            LineComments = next;
        }

        while (!end_of_file) {
            strtrim(buffer);
            if (buffer[0] == '[') {
                char *end = strchr(buffer, ']');
                if (end != 0) {
                    *end = '\0';
                }
            } else {
                buffer[0] = '\0';
                buffer[1] = '\0';
            }

            INISection *secptr = new INISection(_strdup(&buffer[1]), comment_head);
            if (secptr == 0) {
                while (comment_head != 0) {
                    free(comment_head->Value);
                    INIComment *next = comment_head->Next;
                    delete comment_head;
                    comment_head = next;
                }
                Clear();
                return false;
            }
            comment_tail = 0;
            comment_head = 0;

            while (!end_of_file) {
                int length = Read_Line(ffile, buffer, sizeof(buffer), end_of_file);
                if (end_of_file) {
                    break;
                }
                if (Is_Section_Header(buffer)) {
                    break;
                }
                if (keep_comments) {
                    comment = new INIComment;
                    if (comment == 0) {
                        keep_comments = false;
                    }
                }
                if (keep_comments) {
                    if (comment_tail != 0) {
                        comment_tail->Next = comment;
                        comment_tail = comment;
                    } else {
                        comment_tail = comment;
                        comment_head = comment;
                    }
                    comment_tail->Value = _strdup(buffer);
                }

                int equals_column = 0;
                int value_column = 0;
                int comment_column = 0;
                char *comment_string = 0;
                if (keep_comments) {
                    comment_string = Locate_Line_Comment(buffer, equals_column, value_column, comment_column);
                    if (comment_string != 0) {
                        comment_string = _strdup(comment_string);
                    }
                }
                Strip_Comments(buffer);
                if (length == 0 || buffer[0] == ';' || buffer[0] == '=') {
                    free(comment_string);
                    continue;
                }
                char *divider = strchr(buffer, '=');
                if (divider == 0) {
                    free(comment_string);
                    continue;
                }
                *divider++ = '\0';
                strtrim(buffer);
                if (strlen(buffer) == 0) {
                    free(comment_string);
                    continue;
                }
                strtrim(divider);
                if (strlen(divider) == 0) {
                    free(comment_string);
                    continue;
                }

                // The entry's own line is not a comment of the entry.
                if (keep_comments && comment_tail != 0 && comment_tail->Value != 0) {
                    free(comment_tail->Value);
                    comment_tail->Value = 0;
                }

                INIEntry *entryptr = new INIEntry(_strdup(buffer), _strdup(divider), comment_head, comment_string,
                                                  comment_column, equals_column, value_column);
                if (entryptr == 0) {
                    free(comment_string);
                    while (comment_head != 0) {
                        free(comment_head->Value);
                        INIComment *next = comment_head->Next;
                        delete comment_head;
                        comment_head = next;
                    }
                    delete secptr;
                    Clear();
                    return false;
                }
                comment_tail = 0;
                comment_head = 0;

                secptr->EntryIndex.Add_Index(entryptr->Index_ID(), entryptr);
                secptr->EntryList.Add_Tail(entryptr);
            }

            if (!keep_comments && !secptr->EntryList.First()->Is_Valid()) {
                while (comment_head != 0) {
                    free(comment_head->Value);
                    INIComment *next = comment_head->Next;
                    delete comment_head;
                    comment_head = next;
                }
                delete secptr;
            } else {
                SectionIndex.Add_Index(secptr->Index_ID(), secptr);
                SectionList.Add_Tail(secptr);
            }
        }
    }

    LineComments = comment_head;
    return true;
}
// @ref ??0Buffer@@QAE@J@Z=00438380
// @ref ??0GenericList@@QAE@XZ=00490e80
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1Straw@@UAE@XZ=0069b010
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??RCRCEngine@@QAEJPBXH@Z=00493fc0
// @ref ??_7?$List@PAUINIEntry@INIClass@@@@6B@=007a3bac
// @ref ??_7?$Node@PAUINISection@INIClass@@@@6B@=007a3bb4
// @ref ??_7CacheStraw@@6B@=007a3bbc
// @ref ??_7INIEntry@INIClass@@6B@=007a3b9c
// @ref ??_7INISection@INIClass@@6B@=007a3ba4
// @ref ??_7Straw@@6B@=0079e9f8
// @ref ?Read_Line@@YIHAAVStraw@@PADHAA_N@Z=00639670
// @ref ?strtrim@@YIPADPAD@Z=006eef10
// @ref __strdup=0078d816
// @ref _free=007825e8
// @ref _strchr=00784130
