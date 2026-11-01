// Save_Vector: the save/load unit's (0x00654A50) list writer, as in TibSun's saveload.cpp:
// the count, then each object streamed through its IPersistStream (OleSaveToStream).
// Put_All 0x006558B0 expands the early lists inline; its later calls keep the
// out-of-line __fastcall COMDAT copies 0x006580C0-0x00659140 (one per list type).
#ifndef RA2_SHARED_SAVE_VECTOR_HPP
#define RA2_SHARED_SAVE_VECTOR_HPP

#include "shared/com_persist.hpp"
#include "shared/vector_class.hpp"

WIN32_IMPORT HRESULT __stdcall OleSaveToStream(IPersistStream *object, IStream *stream);

template <class T>
inline HRESULT __fastcall Save_Vector(IStream *stream, DynamicVectorClass<T> const &list)
{
    int count = list.Count();
    HRESULT result = stream->Write(&count, sizeof(count), 0);
    if (SUCCEEDED(result)) {
        for (int index = 0; index < count; index++) {
            IPersistStream *lpPS = 0;
            result = list[index]->QueryInterface(IID_IPersistStream, (void **)&lpPS);
            if (FAILED(result)) {
                return result;
            }
            result = OleSaveToStream(lpPS, stream);
            if (FAILED(result)) {
                return result;
            }
            result = lpPS->Release();
            if (FAILED(result)) {
                return result;
            }
        }
        result = S_OK;
    }
    return result;
}

#endif
