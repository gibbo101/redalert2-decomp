// bool IPXAddressClass::operator>=(IPXAddressClass &address) (0x005237E0)
#include "shared/ipx_address.hpp"
#include "shared/crt_memory.hpp"

bool IPXAddressClass::operator>=(IPXAddressClass &address)
{
    return memcmp(this, &address, 10) >= 0;
}
