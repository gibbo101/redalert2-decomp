#include "shared/win32_api.hpp"
#include "shared/fast_math.hpp"
#include "shared/crt_memory.hpp"
#include "shared/debug_printf.hpp"

struct MEMORY_BASIC_INFORMATION {
    void *BaseAddress;
    void *AllocationBase;
    DWORD AllocationProtect;
    unsigned int RegionSize;
    DWORD State;
    DWORD Protect;
    DWORD Type;
};
WIN32_IMPORT unsigned int WINAPI VirtualQuery(LPCVOID address, MEMORY_BASIC_INFORMATION *info, unsigned int length);
WIN32_IMPORT BOOL WINAPI VirtualProtect(LPVOID address, unsigned int length, DWORD protection, DWORD *oldProtection);
WIN32_IMPORT HANDLE WINAPI GetCurrentProcess();
WIN32_IMPORT BOOL WINAPI FlushInstructionCache(HANDLE process, LPCVOID address, unsigned int length);
extern char const memory_protection_error_007d8050[];
// @ref ?Fast_Sin@@=004ba480
// @ref ?memory_protection_error_007d8050@@=007d8050

// Actual original store: clear one DWORD at Fast_Sin, after changing page protection.
// No semantic claim about why the original invalidates that entry.
void __cdecl Clear_Fast_Sin_Entry_004bac90()
{
    MEMORY_BASIC_INFORMATION info;
    memset(&info, 0, sizeof(info));
    unsigned int *entry = (unsigned int *)Fast_Sin;
    if (VirtualQuery(entry, &info, sizeof(info))) {
        void *base = info.BaseAddress;
        unsigned int size = info.RegionSize;
        DWORD oldProtection = 0;
        BOOL result = VirtualProtect(base, size, 8, &oldProtection);
        if (!result) {
            Debug_Printf(memory_protection_error_007d8050, GetLastError(), result);
            return;
        }
        *entry = 0;
        result = VirtualProtect(base, size, 16, &oldProtection);
        if (!result) {
            Debug_Printf(memory_protection_error_007d8050, GetLastError(), result);
        }
        FlushInstructionCache(GetCurrentProcess(), 0, 0);
    }
}
