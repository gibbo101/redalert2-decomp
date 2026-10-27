#include "shared/wol_sink.hpp"
namespace ATL {
extern InterfaceMapEntry const CChatEventSinkInterfaceMap[]; // @ref ?CChatEventSinkInterfaceMap@ATL@@=007af760
template<> HRESULT __stdcall CComObject<CChatEventSink>::QueryInterface(GUID const &iid, void **object)
{
    return InternalQueryInterface(this, CChatEventSinkInterfaceMap, iid, object);
}
}
