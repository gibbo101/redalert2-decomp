// long Voc_Static_Load(IStream *stream) (0x00714B80): drops every static sound,
// stops the audio, then adds back each saved one whose VocClass loops forever
// (name hypothesis).
#include "shared/voc_static.hpp"
#include "shared/vox_class.hpp"
#include "shared/com_persist.hpp"
// @ref ?Audio_Stop@@YIXXZ=00406dc0

long __fastcall Voc_Static_Load(IStream *stream)
{
    Unknown_00714410();
    Audio_Stop();
    int count;
    HRESULT result = stream->Read(&count, sizeof(count), 0);
    if (SUCCEEDED(result)) {
        for (int index = 0; index < count; index++) {
            struct VocStaticRecord {
                int Index;
                CoordStruct Coord;
            } entry;
            result = stream->Read(&entry, sizeof(entry), 0);
            if (FAILED(result)) {
                return result;
            }
            if (entry.Index != -1 && entry.Index < unknown_VocClass_list_00ad0818.Count() && entry.Index >= 0) {
                VocClass *voc = unknown_VocClass_list_00ad0818[entry.Index];
                if (voc->Event != 0 && Audio_Event_Type_Loops_Forever(voc->Event)) {
                    CoordStruct coord = entry.Coord;
                    Voc_Static_Add(entry.Index, coord, 0);
                }
            }
        }
    }
    return result;
}
