// HRESULT __stdcall AtlAdvise(IUnknown *container, IUnknown *sink, GUID const &iid, unsigned long *cookie) (0x0075D0D0)
// ATL: connects a sink to the container's connection point for iid.
#include "shared/com_api.hpp"
#include "shared/connection_points.hpp"
// @ref _IID_IConnectionPointContainer=007afd20

extern "C" HRESULT __stdcall AtlAdvise(IUnknown *container, IUnknown *sink, GUID const &iid, unsigned long *cookie)
{
    CComPtr<IConnectionPointContainer> point_container;
    CComPtr<IConnectionPoint> point;
    HRESULT result = container->QueryInterface(IID_IConnectionPointContainer, (void **)&point_container);
    if (SUCCEEDED(result)) result = point_container->FindConnectionPoint(iid, &point);
    if (SUCCEEDED(result)) result = point->Advise(sink, cookie);
    return result;
}
