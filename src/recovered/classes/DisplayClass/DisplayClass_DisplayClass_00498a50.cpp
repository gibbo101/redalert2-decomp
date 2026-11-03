// DisplayClass::DisplayClass() (0x00498A50)
// Constructs the map, clears the display state (the two cursor cells start
// at the 0x00852610 cell, the -1 members are unset indexes) and the unit's
// shape and counter statics.
#include "shared/display.hpp"
// @ref ??0MapClass@@QAE@XZ=00547960
// @ref ??_7DisplayClass@@6B@=0079e91c
// @ref ?unknown_cell_852610@@3VCell@@A=00852610
// @ref ?TransIconset@DisplayClass@@2PBXB=00852614
// @ref ?ShadowShapes@DisplayClass@@2PBXB=00852934
// @ref ?unknown_852630@DisplayClass@@2HA=00852630

DisplayClass::DisplayClass()
    : unknown_1170(unknown_cell_852610), unknown_1174(0, 0), unknown_1178(0), unknown_117c(false),
      unknown_117d(false), unknown_117e(unknown_cell_852610), unknown_1182(0, 0), unknown_1188(0),
      unknown_118c(0), unknown_1190(0), unknown_1194(-1), unknown_1198(false), unknown_119c(0),
      unknown_11a0(0), unknown_11a4(0), unknown_11a8(-1), unknown_11ac(false), unknown_11ad(false),
      unknown_11ae(false), unknown_11af(false), unknown_11b0(false), unknown_11b4(-1), unknown_11b8(0),
      unknown_11bc(0), unknown_11c0(0), unknown_11c4(0), WaypointColor(0, 0, 0), unknown_11cb(false), unknown_11cc(false), unknown_11cd(false), unknown_11d0(0, 0),
      unknown_11d8(0, 0)
{
    ShadowShapes = 0;
    TransIconset = 0;
    unknown_852630 = 0;
}
