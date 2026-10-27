// RulesClass::Land_Types (0x0064D610)
// @ref _LandNames=007eebbc
// @ref ?Ground@@3PAUGroundType@@A=00850ea0
// @ref ??_C@_04DNDI@Foot?$AA@=007d3a24
// @ref ??_C@_05BEHM@Hover?$AA@=007d3a0c
// @ref ??_C@_05FIKM@Wheel?$AA@=007d3a14
// @ref ??_C@_05OHJG@Track?$AA@=007d3a1c
// @ref ??_C@_05PMGO@Float?$AA@=007d39fc
// @ref ??_C@_09KKLH@Buildable?$AA@=007f1a10
// @ref ??_C@_0L@FLEG@FloatBeach?$AA@=007d39f0
// @ref ??_C@_0L@LLJJ@Amphibious?$AA@=007d1ae8
// @ref ??_C@_03PEOK@Ice?$AA@=007d3a48
// @ref ??_C@_04JGIK@Road?$AA@=007d3a64
// @ref ??_C@_04LKIC@Rock?$AA@=007d3a5c
// @ref ??_C@_04PHLO@Wall?$AA@=007d0fa8
// @ref ??_C@_05BHDE@Clear?$AA@=007d3a6c
// @ref ??_C@_05CEMB@Rough?$AA@=007d3a4c
// @ref ??_C@_05CGKI@Water?$AA@=007d1ab8
// @ref ??_C@_05HFDK@Beach?$AA@=007d3a54
// @ref ??_C@_05HMKB@Weeds?$AA@=007d3a2c
// @ref ??_C@_06MBKF@Tunnel?$AA@=007d3a34
// @ref ??_C@_08BEHN@Railroad?$AA@=007d3a3c
// @ref ??_C@_08EAIC@Tiberium?$AA@=007cdcd0
// Reads each land type's section: the speed factor of each movement type
// (at most 1.0; Winged is not read) and whether it is buildable.
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/rules_sections.hpp"

// Westwood-style macro: the value expression is evaluated twice.
#define Min(a, b) ((a) < (b) ? (a) : (b))

static char const * const LandNames[12] = {"Clear", "Road", "Water", "Rock", "Wall", "Tiberium", "Beach", "Rough", "Ice", "Railroad", "Tunnel", "Weeds"};

bool RulesClass::Land_Types(CCINIClass &ini)
{
    for (int land = 0; land < 12; land++) {
        GroundType &ground = Ground[land];
        if (ini.Is_Present(LandNames[land])) {
            ground.Cost[3] = Min(ini.Get_Double(LandNames[land], "Hover", 1.0), 1.0);
            ground.Cost[0] = Min(ini.Get_Double(LandNames[land], "Foot", 1.0), 1.0);
            ground.Cost[1] = Min(ini.Get_Double(LandNames[land], "Track", 1.0), 1.0);
            ground.Cost[2] = Min(ini.Get_Double(LandNames[land], "Wheel", 1.0), 1.0);
            ground.Cost[4] = 1.0;
            ground.Cost[5] = Min(ini.Get_Double(LandNames[land], "Float", 1.0), 1.0);
            ground.Cost[6] = Min(ini.Get_Double(LandNames[land], "Amphibious", 1.0), 1.0);
            ground.Cost[7] = Min(ini.Get_Double(LandNames[land], "FloatBeach", 1.0), 1.0);
            ground.Build = ini.Get_Bool(LandNames[land], "Buildable", false);
        }
    }
    return true;
}

#undef Min
