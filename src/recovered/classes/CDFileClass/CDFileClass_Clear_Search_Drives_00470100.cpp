// void __fastcall CDFileClass::Clear_Search_Drives() (0x00470100)
// Frees every search directory.
#include "shared/cd_file_class.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_tokens.hpp"

void __fastcall CDFileClass::Clear_Search_Drives()
{
    CDSearchDrive *drive = First;
    while (drive != 0) {
        CDSearchDrive *next = drive->Next;
        if (drive->Path != 0) {
            free((void *)drive->Path);
        }
        delete drive;
        drive = next;
    }
    First = 0;
}
