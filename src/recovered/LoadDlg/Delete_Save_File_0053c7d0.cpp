// bool __stdcall Delete_Save_File(char const *filename) (0x0053C7D0)
#include "shared/load_dlg.hpp"
// @ref __imp__DeleteFileA@4=0079a128

bool __stdcall Delete_Save_File(char const *filename)
{
    bool deleted = DeleteFileA(filename) == 1;
    return deleted;
}
