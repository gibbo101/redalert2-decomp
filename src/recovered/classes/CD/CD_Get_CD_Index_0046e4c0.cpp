// int __fastcall Unknown_0046E4C0(int timeout) (0x0046E4C0)
// The disk index (Get_CD_Index) of the current CD drive.
// Assumes: name and the meaning of the second Get_CD_Index argument
// (a timeout in the cdfile notes) are hypotheses.
#include "shared/cd.hpp"
#include "shared/cd_file_class.hpp"
// @ref ?Get_CD_Index@@YIHHH@Z=004983e0
// @ref ?CurrentCDDrive@CDFileClass@@2HA=0085089c

int __fastcall Unknown_0046E4C0(int timeout)
{
    return Get_CD_Index(CDFileClass::CurrentCDDrive, timeout);
}
