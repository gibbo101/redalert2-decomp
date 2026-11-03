#include "shared/fly_locomotion.hpp"
HRESULT UnknownComPtr<IFlyControl,&unknown_uuid_7d80a8>::Query_From(FootClass * const &other)
{
    HRESULT result;
    if (other) {
        IFlyControl *pointer;
        result=other->QueryInterface(unknown_uuid_7d80a8,(void**)&pointer);
        if (FAILED(result)) {
            Attach(0);
            return result;
        }
        Attach(pointer);
    } else {
        operator=((IFlyControl *)0);
        result=E_NOINTERFACE;
    }
    return result;
}
