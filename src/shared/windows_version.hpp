// WindowsVersionInfo: the Windows version facts read once at startup (name
// hypothesis; no RTTI). One global object, WinVersion (0x00839BC0), built by
// a dynamic initializer (0x0040FCD0) that calls the constructor 0x00736EB0;
// the destructor is empty (its atexit thunk 0x0040FCF0 is a bare `ret`).
//
// Layout from the constructor (GetVersionExA):
//   +0x00 major, +0x04 minor, +0x08 build number, +0x0C the service-pack
//   text (127 characters and a terminator), +0x8C Windows 9x, +0x8D NT.
// Older sources read the fields as separate globals: unknown_839bc0/
// unknown_839bc4 (shared/ipx_interface.hpp) and the 9x flag 0x00839C4C.
#ifndef RA2_SHARED_WINDOWS_VERSION_HPP
#define RA2_SHARED_WINDOWS_VERSION_HPP

class WindowsVersionInfo {
public:
    WindowsVersionInfo();                   // 0x00736EB0
    ~WindowsVersionInfo() {}

    int MajorVersion;                       // +0x00
    int MinorVersion;                       // +0x04
    int BuildNumber;                        // +0x08
    char AdditionalInfo[128];               // +0x0C
    bool IsWin9x;                           // +0x8C
    bool IsWinNT;                           // +0x8D
};

extern WindowsVersionInfo WinVersion;       // 0x00839BC0

#endif
