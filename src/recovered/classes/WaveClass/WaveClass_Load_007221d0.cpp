// Complete WaveClass save-game load,007221D0:349body+3NOP.
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/wave.hpp"

HRESULT __stdcall WaveClass::Load(IStream *stream)
{
    HRESULT result=ObjectClass::Load(stream);
    if(SUCCEEDED(result)) {
        new(this) WaveClass(NoInitClass());
        Polygon_130.Points=&Polygon_130.InlinePoint0;
        Swizzle_Pointer(Target);
        Swizzle_Pointer(Owner);
        int count;
        result=stream->Read(&count,sizeof(count),0);
        if(FAILED(result)) return result;
        int index;
        for(index=0;index<count;++index) {
            CellClass *cell;
            result=stream->Read(&cell,sizeof(cell),0);
            if(FAILED(result)) return result;
            Cells.Add(cell);
        }
        for(index=0;index<count;++index) {
            Swizzle_Pointer(Cells[index]);
        }
    }
    return result;
}

// @ref ??0?$DynamicVectorClass@PAVCellClass@@@@QAE@IPBQAVCellClass@@@Z=007246d0
