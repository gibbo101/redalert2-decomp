// bool IPXAddressClass::operator<=(IPXAddressClass &address) (0x00523810)
#include "shared/ipx_address.hpp"
#include "shared/crt_memory.hpp"

bool IPXAddressClass::operator<=(IPXAddressClass &address)
{
    return memcmp(this, &address, 10) <= 0;
}
