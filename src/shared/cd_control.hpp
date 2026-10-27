// CDControlClass: locks, unlocks and ejects the CD tray (cdctrl.cpp,
// 0x0046EA40-0x0046FD1E; the class name is printed by its own debug strings
// "CDControlClass::Lock_CD_Drive_95").
//
// Windows NT goes through volume handles ("\\.\X:") and the FSCTL/IOCTL
// storage codes; Windows 95 goes through the VWIN32 device ("\\.\vwin32")
// with DOS IOCTL (int 21h function 440Dh) register blocks. The Win95 helpers
// follow Microsoft's published VWIN32 sample routines (OpenVWin32,
// LockLogicalVolume, UnlockMedia, EjectMedia, ...): the register usage
// (BL drive, CH category 08h/48h, CL minor code 48h/49h/4Ah/6Ah) and the
// FAT32 category retry are as in that sample. Method names are hypotheses
// from that vocabulary and the debug strings; Lock_Logical_Volume,
// Unlock_Logical_Volume, Open_VWin32 and Close_VWin32 keep the sample's
// WINAPI (this is passed on the stack; ret 0x14/0xC/4/8), the rest are
// __thiscall.
//
// Windows NT helpers follow Microsoft's published volume-ejection sample
// (OpenVolume, LockVolume, DismountVolume, PreventRemovalOfVolume,
// AutoEjectVolume, CloseVolume): FSCTL_LOCK_VOLUME etc., 20 lock attempts
// 500 ms apart.
//
// Layout: the global CDControl (0x00850830) is cleared as 0x68 bytes by the
// constructor (0x0046EA70); no member use is known yet.
#ifndef RA2_SHARED_CD_CONTROL_HPP
#define RA2_SHARED_CD_CONTROL_HPP

#include "shared/unknown_globals.hpp"
#include "shared/win32_api.hpp"
#include "shared/crt_memory.hpp"

extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);

typedef unsigned char BYTE;

// Register block of VWIN32_DIOC_DOS_IOCTL (as in the Windows 95 DDK).
struct DIOC_REGISTERS {
    DWORD reg_EBX;      // +0x00
    DWORD reg_EDX;      // +0x04
    DWORD reg_ECX;      // +0x08
    DWORD reg_EAX;      // +0x0C
    DWORD reg_EDI;      // +0x10
    DWORD reg_ESI;      // +0x14
    DWORD reg_Flags;    // +0x18
};

// Parameter block of IOCTL 440Dh minor code 48h (lock/unlock removable media).
struct PARAMBLOCK {
    BYTE Operation;     // +0x00 0 lock, 1 unlock, 2 query status
    BYTE NumLocks;      // +0x01 pending locks after the call
};

// Input of IOCTL_STORAGE_MEDIA_REMOVAL.
struct PREVENT_MEDIA_REMOVAL {
    BYTE PreventMediaRemoval;
};

#define VWIN32_DIOC_DOS_IOCTL 1
#define FSCTL_LOCK_VOLUME 0x00090018
#define FSCTL_UNLOCK_VOLUME 0x0009001C
#define FSCTL_DISMOUNT_VOLUME 0x00090020
#define IOCTL_STORAGE_MEDIA_REMOVAL 0x002D4804
#define IOCTL_STORAGE_EJECT_MEDIA 0x002D4808
#define DRIVE_REMOVABLE 2
#define DRIVE_CDROM 5
#define CARRY_FLAG 1
#define FILE_FLAG_DELETE_ON_CLOSE 0x04000000

WIN32_IMPORT unsigned int WINAPI GetDriveTypeA(LPCSTR root);
WIN32_IMPORT BOOL WINAPI DeviceIoControl(HANDLE device, DWORD code, LPVOID in, DWORD insize, LPVOID out,
                                         DWORD outsize, DWORD *returned, void *overlapped);

class CDControlClass {
public:
    CDControlClass();                                                   // 0x0046EA70
    ~CDControlClass();                                                  // 0x0046EA90

    // Ejects the CD in drive (0 = A:) through VWIN32 on Windows 95, else
    // through the volume handle.
    void Force_CD_Eject(char drive);                                    // 0x0046EAA0

    // Windows NT (drive 0 = A:).
    HANDLE Open_Removable_Volume(char drive);                           // 0x0046EC60
    bool Close_Removable_Volume(HANDLE volume);                         // 0x0046ED10
    bool Lock_Volume(HANDLE volume);                                    // 0x0046ED30
    bool Unlock_Volume(HANDLE volume);                                  // 0x0046EDA0
    bool Dismount_Volume(HANDLE volume);                                // 0x0046EE10
    bool Prevent_Removal_Of_Volume(HANDLE volume, bool prevent);        // 0x0046EE60
    bool Auto_Eject_Volume(HANDLE volume);                              // 0x0046EEB0
    bool Eject_CD(char drive);                                          // 0x0046EF00
    bool Lock_CD_Tray_NT(char drive);                                   // 0x0046F0C0
    bool Unlock_CD_Tray_NT(char drive);                                 // 0x0046F250

    // Windows 95 (drive 0 = A:; the VWIN32 calls take 1 = A:).
    void Eject_CD_Win95(char drive);                                    // 0x0046F3E0
    bool Lock_CD_Drive_95(char drive);                                  // 0x0046F510
    bool Unlock_CD_Drive_95(char drive);                                // 0x0046F630

    // Removes every pending lock on the media of drive (1 = A:): queries the
    // lock count, then unlocks that many times.
    bool Unlock_Media(HANDLE vwin32, char drive);                       // 0x0046F750
    // Locks the media of drive after clearing earlier locks.
    bool Lock_Media(HANDLE vwin32, char drive);                         // 0x0046F8C0
    // Ejects the media of drive.
    bool Eject_Media(HANDLE vwin32, char drive);                        // 0x0046F980
    HANDLE WINAPI Open_VWin32();                                        // 0x0046FA10
    bool WINAPI Close_VWin32(HANDLE vwin32);                            // 0x0046FA30
    // Takes a logical volume lock, trying the FAT32 category first, five
    // rounds with a one second pause and the DOS error logged.
    bool WINAPI Lock_Logical_Volume(HANDLE vwin32, char drive, char lock_level, short permissions);  // 0x0046FA50
    // Releases a logical volume lock (FAT32 category first).
    bool WINAPI Unlock_Logical_Volume(HANDLE vwin32, char drive);       // 0x0046FC80

    int unknown_00[26];     // +0x00 cleared by the constructor; use unknown
};

extern CDControlClass CDControl;    // 0x00850830

// Set when the Windows 95 (VWIN32) path is used (hypothesis; set elsewhere).

#include "shared/debug_printf.hpp"

#endif
