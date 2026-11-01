// INIClass::Save (0x0050C620)
// Writes the database as INI text (CRLF line ends) and ends the pipe.
// Sections are separated by a blank line unless they have comment lines
// above them. Kept comment lines are written back above their section or
// entry, entries are padded with spaces so that '=', the value and a
// trailing ";comment" return to their loaded columns (at most 256 spaces
// each), and the LineComments follow the last section. Returns the byte
// count reported by the pipe.
#include "shared/ini_class.hpp"

int INIClass::Save(Pipe &pipe) const
{
    int total = 0;
    char spaces[512];
    memset(spaces, ' ', sizeof(spaces));
    spaces[sizeof(spaces) - 1] = '\0';

    INISection *secptr = SectionList.First();
    while (secptr != 0 && secptr->Is_Valid()) {
        if (total > 0 && secptr->Comments == 0) {
            total += pipe.Put("\r\n", strlen("\r\n"));
        }
        for (INIComment *comment = secptr->Comments; comment != 0; comment = comment->Next) {
            if (comment->Value != 0) {
                total += pipe.Put(comment->Value, strlen(comment->Value));
                total += pipe.Put("\r\n", strlen("\r\n"));
            }
        }

        total += pipe.Put("[", 1);
        total += pipe.Put(secptr->Name, strlen(secptr->Name));
        total += pipe.Put("]", 1);
        total += pipe.Put("\r\n", strlen("\r\n"));

        INIEntry *entryptr = secptr->EntryList.First();
        while (entryptr != 0 && entryptr->Is_Valid()) {
            for (INIComment *comment = entryptr->Comments; comment != 0; comment = comment->Next) {
                if (comment->Value != 0) {
                    total += pipe.Put(comment->Value, strlen(comment->Value));
                    total += pipe.Put("\r\n", strlen("\r\n"));
                }
            }

            int key_length = strlen(entryptr->Key);
            int value_length = strlen(entryptr->Value);
            int padding = entryptr->EqualsColumn - key_length;
            int padded = 0;
            if (padding > 256) {
                padding = 256;
            }
            total += pipe.Put(entryptr->Key, key_length);
            if (padding > 0) {
                total += pipe.Put(spaces, padding);
                padded = padding;
            }
            total += pipe.Put("=", 1);

            padding = entryptr->ValueColumn - (key_length + padded + 1);
            if (padding > 256) {
                padding = 256;
            }
            if (padding > 0) {
                total += pipe.Put(spaces, padding);
                padded += padding;
            }
            total += pipe.Put(entryptr->Value, value_length);

            if (entryptr->CommentString != 0) {
                padding = entryptr->CommentColumn - (key_length + value_length + padded + 1);
                if (padding > 256) {
                    padding = 256;
                }
                if (padding > 0) {
                    total += pipe.Put(spaces, padding);
                }
                total += pipe.Put(";", 1);
                total += pipe.Put(entryptr->CommentString, strlen(entryptr->CommentString));
            }
            total += pipe.Put("\r\n", strlen("\r\n"));

            entryptr = entryptr->Next();
        }

        secptr = secptr->Next();
    }

    for (INIComment *comment = LineComments; comment != 0; comment = comment->Next) {
        if (comment->Value != 0) {
            total += pipe.Put(comment->Value, strlen(comment->Value));
            total += pipe.Put("\r\n", strlen("\r\n"));
        }
    }

    total += pipe.End();
    return total;
}
// @ref ??_C@_01FAJB@?$DL?$AA@=007d27e4
// @ref ??_C@_01FIMD@?$FN?$AA@=007db444
// @ref ??_C@_01KHLB@?$FL?$AA@=007db448
// @ref ??_C@_01KPOD@?$DN?$AA@=007cf3bc
// @ref ??_C@_02PIMC@?$AN?6?$AA@=007d7cec
