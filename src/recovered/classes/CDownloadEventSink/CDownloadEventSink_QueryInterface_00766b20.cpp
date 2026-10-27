#include "shared/wol_sink.hpp"
namespace ATL {
extern InterfaceMapEntry const CDownloadEventSinkInterfaceMap[]; // @ref ?CDownloadEventSinkInterfaceMap@ATL@@=007af708
template<> HRESULT __stdcall CComObject<CDownloadEventSink>::QueryInterface(GUID const &iid, void **object)
{
    return InternalQueryInterface(this, CDownloadEventSinkInterfaceMap, iid, object);
}
}
