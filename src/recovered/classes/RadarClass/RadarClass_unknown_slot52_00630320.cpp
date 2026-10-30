// void RadarClass::unknown_slot52(CoordStruct const &coord) (0x00630320)
// Centres the tactical view on a coordinate; passes the call on (the radar
// adds nothing). Fill_In_Data 0x0065CDD0 passes a CoordStruct with its ground
// height.
#include "shared/radar.hpp"
// @ref ?Unknown_006A66B0@Tactical@@QAEXABUCoordStruct@@@Z=006a66b0
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c

void RadarClass::unknown_slot52(CoordStruct const &coord)
{
    unknown_tactical_83996c->Unknown_006A66B0(coord);
}
