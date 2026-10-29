// HRESULT IUnknownPtr::CreateInstance(GUID const &clsid, IUnknown *outer, unsigned long context) (0x00691450)
// comip.h's _com_ptr_t::CreateInstance for IUnknown: releases the held
// interface, then creates the object (a local or remote server is created
// as IUnknown, run and queried).
#include "shared/com_api.hpp"
// @ref _IID_IUnknown=007ce610
// @ref __imp__CoCreateInstance@20=0079a5f0
// @ref __imp__OleRun@4=0079a5f4

HRESULT IUnknownPtr::CreateInstance(GUID const &clsid, IUnknown *outer, unsigned long context)
{
    HRESULT result;

    _Release();
    if (context & (CLSCTX_LOCAL_SERVER | 0x10)) {
        IUnknown *unknown;
        result = CoCreateInstance(clsid, outer, context, IID_IUnknown, (void **)&unknown);
        if (FAILED(result)) {
            return result;
        }
        result = OleRun(unknown);
        if (SUCCEEDED(result)) {
            result = unknown->QueryInterface(IID_IUnknown, (void **)&Interface);
        }
        unknown->Release();
    } else {
        result = CoCreateInstance(clsid, outer, context, IID_IUnknown, (void **)&Interface);
    }
    return result;
}
