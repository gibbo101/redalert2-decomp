// void TechnoClass::unknown_6ca1d0(AbstractClass *target, int chrono) (0x006CA1D0)
// Draws a beam (RadBeam type 1) from the fire coordinate of weapon 0 to the
// target's coordinate (slot 40 for objects, slot 22 otherwise) in Rules
// RadColor, or ChronoBeamColor when chrono is 1, period 15, amplitude 40,
// with the screen height of the fire coordinate above slot 42's when they
// differ in Y (TechnoClass 0x006CA890).
#include "shared/techno.hpp"
#include "shared/rules.hpp"
#include "shared/tactical.hpp"
#include "shared/rad_beam.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Unknown_006A27A0@Tactical@@QAE?AUPoint2D@@ABUCoordStruct@@@Z=006a27a0
// @ref ?Allocate@RadBeam@@SIPAV1@H@Z=00635440
// @ref ?Set_Color@RadBeam@@QAEXABVRGBClass@@@Z=00635710
// @ref ?Set_Depth@RadBeam@@QAEXH@Z=00635730
// @ref ?Set_Source@RadBeam@@QAEXABUCoordStruct@@@Z=00635740
// @ref ?Set_Target@RadBeam@@QAEXABUCoordStruct@@@Z=00635760
// @ref ?Set_Period@RadBeam@@QAEXH@Z=00635780
// @ref ?Set_Amplitude@RadBeam@@QAEXN@Z=00635790

void TechnoClass::unknown_6ca1d0(AbstractClass *target, int chrono)
{
    RadBeam *beam = RadBeam::Allocate(1);
    int depth = 0;
    CoordStruct source = unknown_slot43(0);
    CoordStruct center = unknown_slot42();
    if (source.Y != center.Y) {
        Point2D from = unknown_tactical_83996c->Unknown_006A27A0(source);
        Point2D to = unknown_tactical_83996c->Unknown_006A27A0(center);
        depth = from.Y - to.Y;
    }
    CoordStruct coord;
    bool object = target != 0 && target->unknown_14_bit1;
    if (!object) {
        coord = target->unknown_slot22();
    } else {
        coord = ((ObjectClass *)target)->unknown_slot40();
    }
    RGBClass color;
    switch (chrono) {
    case 1:
        color = Rules->ChronoBeamColor;
        break;
    default:
        color = Rules->RadColor;
        break;
    }
    beam->Set_Source(source);
    beam->Set_Target(coord);
    beam->Set_Period(15);
    beam->Set_Amplitude(40.0);
    beam->Set_Color(color);
    beam->Set_Depth(depth);
}
