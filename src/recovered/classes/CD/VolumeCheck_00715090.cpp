// Game disk volume check -- 0x00715090,407body+9NOP independently bounded.
#include "shared/cd.hpp"
#include "shared/cd_drive.hpp"
#include "shared/crt_string.hpp"
WIN32_IMPORT DWORD WINAPI GetLogicalDriveStringsA(DWORD size,char *buffer);
WIN32_IMPORT UINT WINAPI GetDriveTypeA(LPCSTR root);
extern char volume_label_format_007d5c68[];
// @ref __imp__GetLogicalDriveStringsA@8=0079a14c
// @ref __imp__GetDriveTypeA@4=0079a24c
// @ref ?volume_label_format_007d5c68@@3PADA=007d5c68
// @ref ??_C@_0CD@KBGG@VolumeCheck?$CI?$CJ?5?9?5GetVolInfo?5faile@=007f9b60
bool __fastcall VolumeCheck()
{
    char roots[260];
    DriveInfo info;
    if(!GetLogicalDriveStringsA(sizeof(roots),roots)) return false;
    char const *root=roots;
    while(strlen(root)!=0) {
        if(GetDriveTypeA(root)==5) {
            if(!Drive_Info_00715230(root,&info)) {
                Debug_Printf("VolumeCheck() - GetVolInfo failed\n");
                root+=strlen(root)+1;
                continue;
            } else {
                char label[32];
                for(int index=0;index<8;++index) {
                    sprintf(label,volume_label_format_007d5c68,index+1);
                    if(!_stricmp(label,info.label)) return true;
                }
            }
        }
        root+=strlen(root)+1;
    }
    if(CD().Force_Available(CD::RequiredCD)) return true;
    return false;
}
