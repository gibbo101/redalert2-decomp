// Drive_Info_00715230 (0x00715230): queries a drive root for the disk search. A drive that reports free clusters is
// refused (hypothesis: the disk must be full, as a game disk is). Debug strings are independently checked.
#include "shared/cd_drive.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
WIN32_IMPORT UINT WINAPI GetDriveTypeA(LPCSTR root);
WIN32_IMPORT BOOL WINAPI GetDiskFreeSpaceA(LPCSTR root,DWORD *sectors,DWORD *bytes,DWORD *free_clusters,DWORD *clusters);
WIN32_IMPORT BOOL WINAPI GetVolumeInformationA(LPCSTR root,char *name,DWORD size,DWORD *serial,DWORD *max_component,DWORD *flags,char *filesystem,DWORD filesystem_size);
// @ref __imp__GetDriveTypeA@4=0079a24c
// @ref __imp__GetDiskFreeSpaceA@20=0079a244
// @ref __imp__GetVolumeInformationA@32=0079a20c
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0BP@MGCA@GetDiskFreeSpace?$CI?$CJ?5failed?3?5?$CFs?6?$AA@=007f9bac
// @ref ??_C@_0CF@MONL@GetVolumeInformation?$CI?$CJ?5?9?5failed?3@=007f9b84

bool __fastcall Drive_Info_00715230(LPCSTR root,DriveInfo *info)
{
    DWORD sectors,bytes,free_clusters,clusters,flags,max_component;
    memset(info,0,sizeof(*info));
    info->type=GetDriveTypeA(root);
    if (!GetDiskFreeSpaceA(root,&sectors,&bytes,&free_clusters,&clusters)) {
        Debug_Printf("GetDiskFreeSpace() failed: %s\n",0);
        return false;
    }
    info->used_bytes=sectors*bytes*free_clusters;
    if (free_clusters) return false;
    info->total_bytes=sectors*bytes*clusters;
    if (!GetVolumeInformationA(root,info->label,64,&info->serial,&max_component,&flags,info->filesystem,64)) {
        Debug_Printf("GetVolumeInformation() - failed: %s\n",0);
        return false;
    }
    return true;
}
