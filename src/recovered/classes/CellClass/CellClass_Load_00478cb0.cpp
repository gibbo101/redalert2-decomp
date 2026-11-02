// CellClass persistence at 0x00478CB0; saved pointers are fixed up after restoring the layout.
#include "shared/cell.hpp"
#include "shared/swizzle.hpp"

// Actual MapClass::Cells subobject, +0x134 from the global Map object.
extern VectorClass<CellClass *> unknown_map_cells_832614;
// @ref ?unknown_map_cells_832614@@3V?$VectorClass@PAVCellClass@@@@A=00832614

HRESULT __stdcall CellClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) CellClass(NoInitClass());
        if (FoggedObjects != 0) {
            FoggedObjects = new DynamicVectorClass<FoggedObjectClass *>;
            int count;
            result = stream->Read(&count, sizeof(count), 0);
            if (FAILED(result)) return result;
            for (int index = 0; index < count; index++) {
                FoggedObjectClass *fogged = 0;
                if (FAILED(stream->Read(&fogged, sizeof(fogged), 0))) return S_OK;
                FoggedObjects->Add(fogged);
            }
            for (int index2 = 0; index2 < FoggedObjects->Count(); index2++) {
                Swizzle_Pointer((*FoggedObjects)[index2]);
            }
        }
        unknown_fc = 0;
        int id = MapCoords.X + MapCoords.Y * 512;
        if (unknown_map_cells_832614[id] != 0) {
            delete unknown_map_cells_832614[id];
            unknown_map_cells_832614[id] = 0;
        }
        unknown_map_cells_832614[id] = this;
        Swizzle_Pointer(unknown_2c);
        Swizzle_Pointer(unknown_30);
        Swizzle_Pointer(unknown_3c);
        Swizzle_Pointer(unknown_e0);
        Swizzle_Pointer(OccupierPtr);
        Swizzle_Pointer(AltOccupierPtr);
        Swizzle_Pointer(unknown_f8);
        Swizzle_Pointer(unknown_40);
        if (OverlayIndex == 0xb3 || OverlayIndex == 0xf2) {
            OverlayIndex = -1;
            OverlayData = 0;
        }
        result = S_OK;
    }
    return result;
}

// @ref ??0?$VectorClass@PAVFoggedObjectClass@@@@QAE@IPBQAVFoggedObjectClass@@@Z=0047d0e0
// @ref ?unknown_map_cells_832618@@3PAPAVCellClass@@A=00832618
