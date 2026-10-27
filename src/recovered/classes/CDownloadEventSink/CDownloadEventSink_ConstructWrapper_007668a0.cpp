#include "shared/wol_sink.hpp"
// @ref ?unknown_module_locks_b2930c=00b2930c
// @ref ??_7?$CComObject@VCDownloadEventSink@@@ATL@@6B@=007af9a4
namespace ATL {
template<> CComObject<CDownloadEventSink>::CComObject(void *outer)
{
    InterlockedIncrement(&unknown_module_locks_b2930c);
}
}
