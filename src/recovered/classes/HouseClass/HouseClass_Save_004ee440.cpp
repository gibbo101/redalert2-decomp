// HRESULT __stdcall HouseClass::Save(IStream *stream, BOOL clear_dirty) (0x004EE440)
// Writes the abstract part, the base plan, the counters, the lists (count
// then elements) and the +0x56CC object (through OleSaveToStream).
#include "shared/techno.hpp"
#include "shared/house_views.hpp"

extern "C" __declspec(dllimport) HRESULT __stdcall OleSaveToStream(IPersistStream *persist, IStream *stream);
extern "C" GUID const IID_IPersistStream_7d5f38;    // 0x007D5F38 (__uuidof(IPersistStream))

// An IPersistStream smart pointer queried from an IUnknown (comip.h
// _com_ptr_t semantics: a failed query other than E_NOINTERFACE raises).
class PersistStreamPtr {
public:
    PersistStreamPtr(IUnknown *unknown) : Interface(0)
    {
        if (unknown != 0) {
            IPersistStream *persist;
            HRESULT result = unknown->QueryInterface(IID_IPersistStream_7d5f38, (void **)&persist);
            Interface = SUCCEEDED(result) ? persist : 0;
            if (FAILED(result) && result != E_NOINTERFACE) {
                _com_issue_error(result);
            }
        }
    }
    ~PersistStreamPtr()
    {
        if (Interface != 0) {
            Interface->Release();
        }
    }
    operator IPersistStream *() const { return Interface; }

    IPersistStream *Interface;
};

// Writes a list: its count, then each element; returns a failure.
#define SAVE_LIST(stream, list, type)                                       \
    {                                                                       \
        count = (list).Count();                                             \
        HRESULT list_result = (stream)->Write(&count, sizeof(count), 0);    \
        if (FAILED(list_result)) {                                          \
            return list_result;                                             \
        }                                                                   \
        for (int index = 0; index < count; index++) {                       \
            list_result = (stream)->Write(&(list)[index], sizeof(type), 0); \
            if (FAILED(list_result)) {                                      \
                return list_result;                                         \
            }                                                               \
        }                                                                   \
    }

HRESULT __stdcall HouseClass::Save(IStream *stream, BOOL clear_dirty)
{
    int count;
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
    unknown_55f0.Save(stream);
    unknown_5420.Save(stream);
    unknown_5430.Save(stream);
    unknown_5440.Save(stream);
    unknown_5450.Save(stream);
    unknown_5460.Save(stream);
    unknown_5470.Save(stream);
    unknown_5480.Save(stream);
    unknown_5490.Save(stream);
    unknown_54a0.Save(stream);
    unknown_54b0.Save(stream);
    unknown_54c0.Save(stream);
    unknown_54d0.Save(stream);

    SAVE_LIST(stream, Supers, SuperClass *);
    SAVE_LIST(stream, unknown_38, TagClass *);
    SAVE_LIST(stream, AngerNodes, AngerStruct);
    SAVE_LIST(stream, ScoutNodes, ScoutStruct);
    SAVE_LIST(stream, unknown_50, BuildingClass *);
    SAVE_LIST(stream, Buildings, BuildingClass *);
    SAVE_LIST(stream, unknown_80, BuildingClass *);
    SAVE_LIST(stream, unknown_98, BuildingClass *);
    SAVE_LIST(stream, unknown_b0, BuildingClass *);

    BOOL present = unknown_56cc != 0;
    result = stream->Write(&present, sizeof(present), 0);
    if (SUCCEEDED(result) && present) {
        PersistStreamPtr persist(unknown_56cc);
        result = OleSaveToStream(persist, stream);
    }
    }
    return result;
}
