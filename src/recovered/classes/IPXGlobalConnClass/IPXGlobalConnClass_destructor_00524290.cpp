// IPXGlobalConnClass::~IPXGlobalConnClass() (0x00524290)
#include "shared/ipx_global_conn.hpp"
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??1ConnectionClass@@UAE@XZ=00480ea0
// @ref ??_7IPXConnClass@@6B@=007a4644

IPXGlobalConnClass::~IPXGlobalConnClass()
{
    if (unknown_d0) {
        delete[] unknown_d0;
        unknown_d0 = 0;
    }
    if (unknown_cc) {
        delete[] unknown_cc;
        unknown_cc = 0;
    }
}
