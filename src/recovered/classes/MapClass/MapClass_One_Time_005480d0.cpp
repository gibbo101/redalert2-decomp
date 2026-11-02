// void MapClass::One_Time() (0x005480D0, slot 5)
// Sets the 512 x 512 cell dimensions, builds the cell vector (slot 22) and
// the hash tables (256 buckets, growth step 20) the zone code uses.
#include "shared/map.hpp"
// @ref ?One_Time@GScreenClass@@UAEXXZ=004e0950
// @ref ?Unknown_Hash_0054F240@@YIHABI@Z=0054f240
// @ref ??2@YAPAXI@Z=00782017

void MapClass::One_Time()
{
    GScreenClass::One_Time();
    MapCellWidth = 512;
    MapCellHeight = 512;
    MapCellTotal = 0x40000;
    unknown_slot22();
    if (unknown_14 == 0) {
        unknown_14 = new HashTableClass<unsigned int, unsigned int>(20, 256, Unknown_Hash_0054F240);
    }
    for (int index = 0; index < 3; index++) {
        SubzoneTracking[index].Clear();
        unknown_7c[index] = new HashTableClass<unsigned int, SubzoneConnectionStruct>(20, 256, Unknown_Hash_0054F240);
    }
    for (int clear = 0; clear < 12; clear++) {
        unknown_18[clear] = 0;
    }
}
// @ref ??0?$VectorClass@U?$HashObject@II@@@@QAE@IPBU?$HashObject@II@@@Z=0056cdd0
// @ref ??0?$VectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@QAE@IPBU?$HashObject@IUSubzoneConnectionStruct@@@@@Z=0056ce50
// @ref ??_7?$DynamicVectorClass@U?$HashObject@II@@@@6B@=007a5a78
// @ref ??_7?$DynamicVectorClass@U?$HashObject@IUSubzoneConnectionStruct@@@@@@6B@=007a5a58
