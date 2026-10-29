// int __cdecl Compare_Save_Times(FileEntryClass **first, FileEntryClass **second) (0x0053C650)
// The save list's qsort callback: the entry written last sorts first.
#include "shared/load_dlg.hpp"
// @ref __imp__CompareFileTime@8=0079a0f0

int __cdecl Compare_Save_Times(FileEntryClass **first, FileEntryClass **second)
{
    FileEntryClass *left = *first;
    FileEntryClass *right = *second;
    return -CompareFileTime(&left->LastWriteTime, &right->LastWriteTime);
}
