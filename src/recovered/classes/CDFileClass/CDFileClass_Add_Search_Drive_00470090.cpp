// void __fastcall CDFileClass::Add_Search_Drive(char *path) (0x00470090)
// Appends a copy of path to the end of the search list.
#include "shared/cd_file_class.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_tokens.hpp"

void __fastcall CDFileClass::Add_Search_Drive(char *path)
{
    CDSearchDrive *drive = new CDSearchDrive;
    drive->Path = _strdup(path);
    drive->Next = 0;

    if (First == 0) {
        First = drive;
    } else {
        CDSearchDrive *last = First;
        while (last->Next != 0) {
            last = last->Next;
        }
        last->Next = drive;
    }
}
