// static bool __fastcall SmudgeTypeClass::Create_Crater(CoordStruct const &coord, int width, int height, bool big) (0x00688750)
// Places a random crater ("Crater" type) that fits at the cell: small
// (1 x 1) ones unless the area is large (width > 60 and height > 50), only
// multi-cell ones when big; any fitting crater when none matches. Always
// returns false.
#include "shared/smudge_type.hpp"
#include "shared/smudge.hpp"
#include "shared/random.hpp"
// @ref ??8?$VectorClass@PAVSmudgeTypeClass@@@@UBE_NABV0@@Z=006535b0
// @ref ??_7?$DynamicVectorClass@PAVSmudgeTypeClass@@@@6B@=007a91a4
// @ref ??_7?$VectorClass@PAVSmudgeTypeClass@@@@6B@=007a9138
// @ref ??_E?$DynamicVectorClass@PAVSmudgeTypeClass@@@@UAEPAXI@Z=00654480
// @ref ??_E?$VectorClass@PAVSmudgeTypeClass@@@@UAEPAXI@Z=00654430
// @ref ??_G?$DynamicVectorClass@PAVSmudgeTypeClass@@@@UAEPAXI@Z=00654480
// @ref ??_G?$VectorClass@PAVSmudgeTypeClass@@@@UAEPAXI@Z=00654430
// @ref ?Clear@?$DynamicVectorClass@PAVSmudgeTypeClass@@@@UAEXXZ=00652cd0
// @ref ?Clear@?$VectorClass@PAVSmudgeTypeClass@@@@UAEXXZ=006536a0
// @ref ?Fetch@?$VectorClass@PAVSmudgeTypeClass@@@@UBEPAVSmudgeTypeClass@@H@Z=00652db0
// @ref ?ID@?$DynamicVectorClass@PAVSmudgeTypeClass@@@@UAEHABQAVSmudgeTypeClass@@@Z=00653890
// @ref ?ID@?$DynamicVectorClass@PAVSmudgeTypeClass@@@@UAEHPBQAVSmudgeTypeClass@@@Z=00652d00
// @ref ?ID@?$VectorClass@PAVSmudgeTypeClass@@@@UAEHABQAVSmudgeTypeClass@@@Z=006536d0
// @ref ?ID@?$VectorClass@PAVSmudgeTypeClass@@@@UAEHPBQAVSmudgeTypeClass@@@Z=00653710
// @ref ?Resize@?$DynamicVectorClass@PAVSmudgeTypeClass@@@@UAE_NHPBQAVSmudgeTypeClass@@@Z=00653790
// @ref ?Resize@?$VectorClass@PAVSmudgeTypeClass@@@@UAE_NHPBQAVSmudgeTypeClass@@@Z=006535f0
// @ref ??0?$VectorClass@PAVSmudgeTypeClass@@@@QAE@IPBQAVSmudgeTypeClass@@@Z=006549b0
// @ref ?SmudgeTypes@@3V?$DynamicVectorClass@PAVSmudgeTypeClass@@@@A=00a40bc8
// @ref ?Can_Place@SmudgeTypeClass@@QBE_NABVCell@@_N@Z=00688a40
// @ref ??0SmudgeClass@@QAE@PAVSmudgeTypeClass@@ABUCoordStruct@@H@Z=006875c0
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b

bool __fastcall SmudgeTypeClass::Create_Crater(CoordStruct const &coord, int width, int height, bool big)
{
    Cell cell = Coord_Cell(coord);
    if (cell.X == unknown_geometry_k.X && cell.Y == unknown_geometry_k.Y) {
        return false;
    }
    DynamicVectorClass<SmudgeTypeClass *> scorches;
    for (int index = 0; index < SmudgeTypes.Count(); index++) {
        SmudgeTypeClass *smudge = SmudgeTypes[index];
        if (smudge->Crater && smudge->Can_Place(Coord_Cell(coord), big)) {
            scorches.Add(smudge);
        }
    }
    DynamicVectorClass<SmudgeTypeClass *> fits;
    for (index = 0; index < scorches.Count(); index++) {
        SmudgeTypeClass *smudge = scorches[index];
        if (!big) {
            if ((smudge->Width == 1 && smudge->Height == 1) || (width > 60 && height > 50)) {
                fits.Add(smudge);
            }
        } else if (smudge->Width > 1 && smudge->Height > 1) {
            fits.Add(smudge);
        }
    }
    if (fits.Count() > 0) {
        new SmudgeClass(fits[unknown_id_source_a3d290->Random()(0, fits.Count() - 1)], coord, -1);
    } else if (scorches.Count() > 0) {
        new SmudgeClass(scorches[unknown_id_source_a3d290->Random()(0, scorches.Count() - 1)], coord, -1);
    }
    return false;
}
