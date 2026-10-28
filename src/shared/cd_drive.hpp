// Drive information for the disk search (0x00715090 Find_Disk_Drive, inlining the query below).
#ifndef RA2_SHARED_CD_DRIVE_HPP
#define RA2_SHARED_CD_DRIVE_HPP

#include "shared/win32_api.hpp"

struct DriveInfo {
    UINT type;              // +0x00 GetDriveType
    char label[64];         // +0x04 volume label
    DWORD serial;           // +0x44 volume serial number
    char filesystem[64];    // +0x48 file system name
    DWORD used_bytes;       // +0x88 sectors * bytes * free clusters (the query fails when this is not 0)
    DWORD total_bytes;      // +0x8C sectors * bytes * clusters
};

// Fills info for a drive root; false when the drive cannot be queried (0x00715230, 201 bytes).
bool __fastcall Drive_Info_00715230(LPCSTR root, DriveInfo *info);

#endif
