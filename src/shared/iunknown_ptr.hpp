// The IUnknown smart pointer operations used by startup's registration loop.
// Keep implementation dependencies out of the common Win32 COM declarations.
#ifndef RA2_SHARED_IUNKNOWN_PTR_HPP
#define RA2_SHARED_IUNKNOWN_PTR_HPP
#define RA2_IUNKNOWN_PTR_LIFETIME
#include "shared/com_api.hpp"
inline IUnknownPtr::IUnknownPtr() : Interface(0) {}
inline void IUnknownPtr::Release()
{
    if (Interface == 0) _com_issue_error(E_POINTER);
    Interface->Release();
    Interface = 0;
}
#endif
