#include "shared/cstream.hpp"
#ifndef E_NOINTERFACE
#define E_NOINTERFACE ((HRESULT)0x80004002L)
#endif
extern "C" GUID const IID_IStream_7afd40;
extern "C" GUID const IID_ILinkStream_7a1aa0;
// @ref _IID_IUnknown_7afce0=007afce0
// @ref _IID_IStream_7afd40=007afd40
// @ref _IID_ILinkStream_7a1aa0=007a1aa0
HRESULT __stdcall CStreamClass::QueryInterface(GUID const &iid, void **object)
{
    if (!object) return E_POINTER;
    *object = 0;
    if (iid == IID_IUnknown_7afce0) *object = static_cast<IStream *>(this);
    if (iid == IID_IStream_7afd40) *object = static_cast<IStream *>(this);
    if (iid == IID_ILinkStream_7a1aa0) *object = static_cast<ILinkStream *>(this);
    if (!*object) return E_NOINTERFACE;
    AddRef();
    return S_OK;
}
