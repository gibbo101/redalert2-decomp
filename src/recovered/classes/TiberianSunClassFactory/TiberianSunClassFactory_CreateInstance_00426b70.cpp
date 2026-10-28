// HRESULT __stdcall TiberianSunClassFactory::CreateInstance(IUnknown *outer, GUID const &iid, void **object) -- 0x00426B70
// The scripting application's class factory: no aggregation; IApplication and
// IUnknown ask the application object at 0x0084C7DC, the third interface the
// map at 0x008324E0; an object whose query fails is deleted.
#include "shared/tiberian_sun_class_factory.hpp"
// @ref _IID_IApplication_79c3d0=0079c3d0
// @ref _IID_IUnknown_7afce0=007afce0
// @ref _unknown_iid_7a2c28=007a2c28
// @ref ?unknown_application_object_84c7dc@@3VApplicationClass@@A=0084c7dc
// @ref ?unknown_map_object_8324e0@@3DA=008324e0
// @ref ??3@YAXPAX@Z=00781d3b

HRESULT __stdcall TiberianSunClassFactory::CreateInstance(IUnknown *outer, GUID const &iid, void **object)
{
    if (object == 0) {
        return E_INVALIDARG;
    }
    *object = 0;
    if (outer != 0) {
        return CLASS_E_NOAGGREGATION;
    }
    HRESULT result = E_NOINTERFACE;
    if (iid == IID_IApplication_79c3d0 || iid == IID_IUnknown_7afce0) {
        IUnknown *application = &unknown_application_object_84c7dc;
        if (application == 0) {
            return E_OUTOFMEMORY;
        }
        result = application->QueryInterface(iid, object);
        if (result < 0) {
            delete application;
        }
    }
    if (iid == unknown_iid_7a2c28) {
        IUnknown *map = (IUnknown *)&unknown_map_object_8324e0;
        if (map == 0) {
            return E_OUTOFMEMORY;
        }
        result = map->QueryInterface(iid, object);
        if (result < 0) {
            delete map;
        }
    }
    return result;
}
