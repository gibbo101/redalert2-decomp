// HRESULT SwizzleManagerClass::Load_Interface(IStream *, GUID *, void **) (0x0069FDC0, slot 8): not implemented.
#include "shared/swizzle.hpp"

HRESULT __stdcall SwizzleManagerClass::Load_Interface(IStream *stream, GUID *riid, void **object)
{
    return E_NOTIMPL;
}
