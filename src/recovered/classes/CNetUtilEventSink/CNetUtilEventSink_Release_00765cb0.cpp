#include "shared/wol_sink.hpp"
// @ref ?unknown_module_locks_b2930c=00b2930c
// @ref ??_7?$CComObject@VCNetUtilEventSink@@@ATL@@6B@=007af73c
namespace ATL {
template<> unsigned long __stdcall CComObject<CNetUtilEventSink>::Release()
{
    unsigned long count = InterlockedDecrement(&m_dwRef);
    if (count == 0) delete this;
    return count;
}
}
