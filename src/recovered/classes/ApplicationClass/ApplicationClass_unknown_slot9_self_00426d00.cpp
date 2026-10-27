// HRESULT __stdcall ApplicationClass::unknown_slot9_self(void **object) -- 0x00426D00
// IApplication slot: the object itself as IApplication (a QueryInterface
// for IID 0x0079C3D0).
#include "shared/application.hpp"
// @ref _IID_IApplication_79c3d0=0079c3d0

HRESULT __stdcall ApplicationClass::unknown_slot9_self(void **object)
{
    return QueryInterface(IID_IApplication_79c3d0, object);
}
