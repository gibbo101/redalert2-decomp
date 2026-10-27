// int __stdcall TunnelLocomotionClass::Z_Adjust() (0x006F0FF0, ILocomotion 14)
#include "shared/tunnel_locomotion.hpp"
#include "shared/tactical.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Unknown_006A29D0@Tactical@@QAE_NABUCoordStruct@@AAUPoint2D@@@Z=006a29d0
// @ref ?unknown_7f8660@@3HA=007f8660
// @ref ?unknown_7f8664@@3HA=007f8664
// @ref __real@8@3ffdccccccccccccd000=0079c268
// @ref ?Z_Adjust@LocomotionClass@@UAGHXZ=0053d4a0
extern int unknown_7f8660;
extern int unknown_7f8664;

int __stdcall TunnelLocomotionClass::Z_Adjust()
{
    CoordStruct coord = LinkedTo->Coord;
    Point2D from;
    unknown_tactical_83996c->Unknown_006A29D0(coord, from);
    coord.Z = Map.Unknown_0055A280(coord);
    Point2D to;
    unknown_tactical_83996c->Unknown_006A29D0(coord, to);
    int height = from.Y - to.Y;
    double ratio = Timer_Ratio();
    int facing = Dir_To_256(LinkedTo->unknown_2e0.Current());
    switch (unknown_18) {
    case 4:
        return unknown_7f8664 + height;
    case 6:
        return (int)((1.0 - ratio) * unknown_7f8660 + height);
    case 2:
        if (ratio > 0.4 && !unknown_38) {
            unknown_38 = true;
        }
        if (facing > 0x46 && facing < 0x8c) {
            height += unknown_7f8664;
        } else {
            height = (int)(unknown_7f8664 * ratio + height);
        }
        return height;
    case 3:
        return unknown_7f8664 + height;
    case 5:
        return unknown_7f8660 + height;
    default:
        return LocomotionClass::Z_Adjust();
    }
}
