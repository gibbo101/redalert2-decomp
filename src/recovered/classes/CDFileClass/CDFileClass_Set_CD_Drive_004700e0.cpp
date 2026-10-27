// void __fastcall CDFileClass::Set_CD_Drive(int drive) (0x004700E0)
// Makes drive the CD drive, remembering the previous one.
#include "shared/cd_file_class.hpp"
// @ref ?LastCDDrive@CDFileClass@@2HA=008508a0

void __fastcall CDFileClass::Set_CD_Drive(int drive)
{
    LastCDDrive = CurrentCDDrive;
    CurrentCDDrive = drive;
}
