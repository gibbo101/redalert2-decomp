// void SpecialClass::Init() (0x0068B320)
// The default options: bits 0-2 clear, TiberiumSpreads and DestroyableBridges
// set, EscapeMovies from HKLM\SOFTWARE\Westwood\Red Alert 2\ EscapeMovies
// (a REG_DWORD, bit 0), everything else clear. `size` is set before the key
// copy: after it, the constant 4 is kept in a register and the size store and
// type test no longer use immediates.
#include "shared/special.hpp"
#include "shared/win32_api.hpp"
#include "shared/crt_memory.hpp"
// @ref ??_C@_0BP@KEJB@SOFTWARE?2Westwood?2Red?5Alert?52?2?$AA@=007f4418
// @ref ??_C@_0N@KCBD@EscapeMovies?$AA@=007f4408
// @ref __imp__RegCloseKey@4=0079a004
// @ref __imp__RegOpenKeyExA@20=0079a00c
// @ref __imp__RegQueryValueExA@24=0079a008

void SpecialClass::Init()
{
    unknown_bits_0 = 0;
    IsFromInstall = 0;
    bool escape = false;
    HKEY handle;
    DWORD size = 4;
    char key[128];
    strcpy(key, "SOFTWARE\\Westwood\\Red Alert 2\\");
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, key, 0, KEY_ALL_ACCESS, &handle) == 0) {
        DWORD type;
        DWORD value = 0;
        if (RegQueryValueExA(handle, "EscapeMovies", 0, &type, (BYTE *)&value, &size) == 0 && type == 4) {
            escape = value & 1;
        }
        RegCloseKey(handle);
    }
    EscapeMovies = escape;
    unknown_bit_4 = 0;
    Inert = 0;
    TiberiumGrows = 0;
    TiberiumSpreads = 1;
    MCVDeploy = 0;
    InitialVeteran = 0;
    FixedAlliance = 0;
    HarvesterImmune = 0;
    FogOfWar = 0;
    unknown_bit_13 = 0;
    TiberiumExplosive = 0;
    DestroyableBridges = 1;
    Meteorites = 0;
    IonStorms = 0;
    Visceroids = 0;
}

