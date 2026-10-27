#include "shared/cstream.hpp"
// @ref ?unknown_flush_495000@CStreamClass@@QAEJPAXH@Z=00495000
HRESULT CStreamClass::unknown_flush_pending()
{
    if (unknown_11 && unknown_14 > 0) {
        if (Stream==0) return E_FAIL;
        if(unknown_14>0) return unknown_flush_495000(unknown_18, unknown_14);
    }
    return S_OK;
}
