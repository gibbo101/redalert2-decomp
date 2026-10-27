#include "shared/infantry_piggyback_ptr.hpp"
UnknownComPtr<IPiggyback, &unknown_uuid_IPiggyback_7cfc30>::~UnknownComPtr()
{
    if (Pointer != 0) {
        Pointer->Release();
    }
}
