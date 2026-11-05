#include "shared/voc_static.hpp"
#include "shared/com_persist.hpp"
// @ref __stricmp=00781f20
// @ref ??_C@_0M@OOFK@Invalid?5Voc?$AA@=007f9b3c
// Save static sound indices and coordinates in list order.
HRESULT __fastcall Voc_Static_Save(IStream *stream)
{
    int count=Audio_List_Count(&unknown_voc_static_list_ad07d0);
    HRESULT result=stream->Write(&count,sizeof(count),0);
    if(SUCCEEDED(result)) {
        VocStaticSound *sound=(VocStaticSound*)Audio_List_First(&unknown_voc_static_list_ad07d0);
        while(sound) {
            struct VocStaticRecord { int Index; CoordStruct Coord; } entry;
            int index=-1;
            entry.Index=index;
            if(sound->Handle.Type) {
                char const *name=Audio_Event_Type_Name(sound->Handle.Type);
                if(name) index=VocClass::From_Name(name);
                entry.Index=index;
            }
            entry.Coord.X=sound->Coord.X;
            entry.Coord.Y=sound->Coord.Y;
            entry.Coord.Z=sound->Coord.Z;
            result=stream->Write(&entry,sizeof(entry),0);
            if(FAILED(result)) return result;
            sound=(VocStaticSound*)Audio_List_Next(sound);
        }
    }
    return result;
}
