#include "shared/wol_sink.hpp"
namespace ATL {
extern InterfaceMapEntry const CNetUtilEventSinkInterfaceMap[]; // @ref ?CNetUtilEventSinkInterfaceMap@ATL@@=007af720
template<> HRESULT __stdcall CComObject<CNetUtilEventSink>::QueryInterface(GUID const &iid, void **object)
{
    return InternalQueryInterface(this, CNetUtilEventSinkInterfaceMap, iid, object);
}
}
