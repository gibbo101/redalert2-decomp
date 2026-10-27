// bool CDControlClass::Close_Removable_Volume(HANDLE volume) (0x0046ED10)
#include "shared/cd_control.hpp"
// @ref __imp__CloseHandle@4=0079a1d4

bool CDControlClass::Close_Removable_Volume(HANDLE volume)
{
    return CloseHandle(volume) ? true : false;
}
