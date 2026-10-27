// PRIVATE complete177-body+15-padding Building animation refresh.
// Uses approved private Tactical::Unknown_006A2BF0(Point2D const&).
#include "shared/building.hpp"
#include "shared/tactical.hpp"
// @ref ?Unknown_006A2BF0@Tactical@@=006a2bf0
void BuildingClass::unknown_44c9a0()
{
    CoordStruct center=unknown_slot42();
    for(int index=0;index<18;++index) {
        // Original dispatch requires the ObjectClass slot103 interface; concrete entry class is not assumed.
        ObjectClass *animation=static_cast<ObjectClass *>(unknown_454[index]);
        if(animation) {
            CoordStruct position=unknown_tactical_83996c->Unknown_006A2BF0(Type->Anims[index].Offset)+center;
            animation->unknown_slot103(position);
        }
    }
}
