#include "shared/cell.hpp"
#include "shared/isometric_tile_type.hpp"
#include "shared/random2.hpp"
#include "shared/crt_memory.hpp"
struct ClearIconOffset { int X,Y; };
extern "C" bool Clear_Icon_Init;
extern "C" int Clear_Icon_Large[64];
extern "C" int const Clear_Icon_Small[16];
extern "C" ClearIconOffset const Clear_Icon_Adjacent[8];
// @ref _Clear_Icon_Init=00850c47
// @ref _Clear_Icon_Large=00850aa8
// @ref _Clear_Icon_Small=007d2b90
// @ref _Clear_Icon_Adjacent=007d2bd0
// Original tables above are independently inspected original data, not candidate-owned arrays.
static Point2D Clear_Icon_Dimensions(IsometricTileTypeClass const *type)
{
    Point2D size;
    size.X=((IsoTileImageStruct const*)type->unknown_slot39())->unknown_00[0];
    size.Y=((IsoTileImageStruct const*)type->unknown_slot39())->unknown_00[1];
    return size;
}
// Choose a tile variation from the cell's wrapped position and the seeded pattern.
int CellClass::Clear_Icon(int type,int count) const
{
    if(!Clear_Icon_Init) {
        Clear_Icon_Init=true;
        memset(Clear_Icon_Large,255,sizeof(Clear_Icon_Large));
        for(int i=0;i<64;++i) {
            int random=-1;
            for(int attempt=0;attempt<64;++attempt) {
                random=unknown_random_839218()&7;
                bool duplicate=false;
                for(int adjacent=0;adjacent<8;++adjacent) {
                    ClearIconOffset const &offset=Clear_Icon_Adjacent[adjacent];
                    int neighbor=i+offset.Y*8+offset.X;
                    if(neighbor<0) neighbor+=64;
                    if(neighbor>=64) neighbor-=64;
                    if(Clear_Icon_Large[neighbor]==random) { duplicate=true;break; }
                }
                if(!duplicate) break;
            }
            Clear_Icon_Large[i]=random;
        }
    }
    Cell cell=Fetch_CellID();
    if(unknown_11a) {
        IsometricTileTypeClass const *tile=IsoTileTypes[type];
        if(!tile->unknown_slot39()) return 0;
        Point2D dimensions=Clear_Icon_Dimensions(tile);
        cell=cell-Cell((unsigned char)unknown_11a%dimensions.X,(unsigned char)unknown_11a/dimensions.X);
        cell.X/=dimensions.X;
        cell.Y/=dimensions.Y;
    }
    if(count<=4) return Clear_Icon_Small[(cell.X&3)|((cell.Y&3)<<2)];
    return Clear_Icon_Large[(cell.X&7)+(cell.Y&7)*8];
}
