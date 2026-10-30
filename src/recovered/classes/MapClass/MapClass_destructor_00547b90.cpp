// MapClass::~MapClass() (0x00547B90)
// Runs four unidentified global cleanups, frees the owned buffers and hash
// tables, then the member vectors are destroyed.
#include "shared/map.hpp"
// @ref ?Unknown_00710B50@@YAXXZ=00710b50
// @ref ?Unknown_00711C70@@YAXXZ=00711c70
// @ref ?Unknown_006E9670@@YAXXZ=006e9670
// @ref ?Unknown_006EA130@@YIXXZ=006ea130
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??_ESubzoneTrackingStruct@@QAEPAXI@Z=0040afa0

MapClass::~MapClass()
{
    Unknown_00710B50();
    Unknown_00711C70();
    Unknown_006E9670();
    Unknown_006EA130();
    if (unknown_64 != 0) {
        delete unknown_64;
        unknown_64 = 0;
    }
    if (unknown_14 != 0) {
        delete unknown_14;
        unknown_14 = 0;
    }
    if (unknown_6c != 0) {
        delete unknown_6c;
        unknown_6c = 0;
    }
    for (int index = 0; index < 3; index++) {
        if (unknown_7c[index] != 0) {
            delete unknown_7c[index];
            unknown_7c[index] = 0;
        }
    }
}
// @ref ??_7?$VectorClass@PAVCellClass@@@@6B@=007a59b8
// @ref ??_7?$VectorClass@VCell@@@@6B@=0079c5e0
// @ref ??_7?$VectorClass@USubzoneTrackingStruct@@@@6B@=007a5a38
// @ref ??_7?$VectorClass@UZoneConnectionClass@@@@6B@=007a5a18
