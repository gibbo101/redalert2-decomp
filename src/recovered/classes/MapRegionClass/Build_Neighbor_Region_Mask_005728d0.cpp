#include "shared/map_region.hpp"
bool __fastcall Rectangle_Has_Region_Cells_00583630(Rect const &area,int region,int unknown,int required);
extern double const unknown_patch_minimum_7a5c10,unknown_patch_maximum_7a5c18;
extern float const unknown_patch_one_79b7f8;
extern unsigned unknown_neighbor_bits_7e09c8[3][3];
// @ref ?Rectangle_Has_Region_Cells_00583630@@=00583630
// @ref ?unknown_patch_minimum_7a5c10@@=007a5c10
// @ref ?unknown_patch_maximum_7a5c18@@=007a5c18
// @ref ?unknown_patch_one_79b7f8@@=0079b7f8
// @ref ?unknown_neighbor_bits_7e09c8@@=007e09c8
// @ref __ftol=0077f110
unsigned MapRegionClass::Build_Neighbor_Region_Mask_005728d0(Cell const &position,bool &valid,int unknown,float density)
{
    double threshold=unknown_patch_maximum_7a5c18;
    threshold-=unknown_patch_minimum_7a5c10;
    threshold*=unknown_patch_one_79b7f8-density;
    threshold+=unknown_patch_minimum_7a5c10;
    int required=(int)threshold;
    Cell corner=position-Cell(2,2);
    int left=corner.X;
    int top=corner.Y;
    if(!Rectangle_Has_Region_Cells_00583630(Rect(left,top,5,5),Index,unknown,required)) {
        valid=false;
        return 0;
    }
    unsigned mask=0;
    for(int row=0;row<3;++row) {
        for(int column=0;column<3;++column) {
            if(row!=1 || column!=1) {
                if(Rectangle_Has_Region_Cells_00583630(Rect(left+5*(column-1),top+5*(row-1),5,5),Index,unknown,required))
                    mask|=unknown_neighbor_bits_7e09c8[row][column];
            }
        }
    }
    return mask;
}
