// WindowsVersionInfo::WindowsVersionInfo() (0x00736EB0)
// Asks Windows for its version: the numbers, the platform flags and the
// service-pack text.
#include "shared/win32_api.hpp"
#include "shared/windows_version.hpp"
#include "shared/crt_string.hpp"
// @ref _strncpy=007823d0

WindowsVersionInfo::WindowsVersionInfo() :
    MajorVersion(0),
    MinorVersion(0),
    BuildNumber(0),
    IsWin9x(false),
    IsWinNT(false)
{
    OSVERSIONINFOA info;
    info.dwOSVersionInfoSize = sizeof(info);
    GetVersionExA(&info);
    MajorVersion = info.dwMajorVersion;
    MinorVersion = info.dwMinorVersion;
    BuildNumber = info.dwBuildNumber;
    if (info.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
        IsWin9x = true;
    } else if (info.dwPlatformId == VER_PLATFORM_WIN32_NT) {
        IsWinNT = true;
    }
    strncpy(AdditionalInfo, info.szCSDVersion, sizeof(AdditionalInfo) - 1);
    AdditionalInfo[sizeof(AdditionalInfo) - 1] = '\0';
}
