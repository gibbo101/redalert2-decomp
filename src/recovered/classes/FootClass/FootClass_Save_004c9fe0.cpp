// Foot.CPP: persist the route and navigation pointer queues, then the locomotor.
#include "shared/foot.hpp"
#include "shared/locomotion.hpp"
// @ref ?Save@TechnoClass@@UAGJPAUIStream@@H@Z=006d6a80
// @ref __imp__OleSaveToStream@8=0079a5e8
// Persistence query from the held locomotor: use its raw held interface after
// the null guard, then release and attach the queried stream interface inline.
template<>
inline HRESULT UnknownComPtr<IPersistStream,&unknown_uuid_IPersistStream_7d5f38>::Query(UnknownComPtr<ILocomotion,&unknown_uuid_ILocomotion_7ce600> const &other)
{
    if (other.Pointer) {
        IPersistStream *pointer;
        HRESULT result=other.Pointer->QueryInterface(unknown_uuid_IPersistStream_7d5f38,(void **)&pointer);
        if (FAILED(result)) Attach(0);
        else Attach(pointer);
        return result;
    }
    operator=((IPersistStream *)0);
    return E_NOINTERFACE;
}

HRESULT __stdcall FootClass::Save(IStream *stream,BOOL clear_dirty)
{
    HRESULT result=TechnoClass::Save(stream,clear_dirty);
    if (SUCCEEDED(result)) {
        int index;
        int count=unknown_478.Count();
        result=stream->Write(&count,sizeof(count),0);
        if (FAILED(result)) return result;
        for (index=0;index<count;++index) {
            result=stream->Write(&unknown_478[index],sizeof(unknown_478[index]),0);
            if (FAILED(result)) return result;
        }
        count=unknown_49c.Count();
        result=stream->Write(&count,sizeof(count),0);
        if (FAILED(result)) return result;
        for (index=0;index<count;++index) {
            result=stream->Write(&unknown_49c[index],sizeof(unknown_49c[index]),0);
            if (FAILED(result)) return result;
        }
        UnknownComPtr<IPersistStream,&unknown_uuid_IPersistStream_7d5f38> persist(Locomotor);
        OleSaveToStream(persist,stream);
        result=S_OK;
    }
    return result;
}
