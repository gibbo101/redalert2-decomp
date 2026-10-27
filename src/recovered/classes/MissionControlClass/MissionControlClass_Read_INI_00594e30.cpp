// bool MissionControlClass::Read_INI(CCINIClass &ini) (0x00594E30)
// @ref ??_C@_04GGHG@Rate?$AA@=007cef5c
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??_C@_06DCKO@AARate?$AA@=007e1d34
// @ref ??_C@_06PEJJ@Zombie?$AA@=007e1d68
// @ref ??_C@_07FINC@Scatter?$AA@=007e1d3c
// @ref ??_C@_08PJNA@NoThreat?$AA@=007e1d70
// @ref ??_C@_09GJLF@Retaliate?$AA@=007e1d44
// @ref ??_C@_09OOLD@Paralyzed?$AA@=007e1d50
// @ref ??_C@_0M@FJOE@Recruitable?$AA@=007e1d5c
// Reads the mission's own section (named by Name()); AARate= defaults to Rate=.
#include "shared/mission.hpp"
#include "shared/ccini_class.hpp"

bool MissionControlClass::Read_INI(CCINIClass &ini)
{
    if (ini.Is_Present(Name())) {
        unknown_04 = ini.Get_Bool(Name(), "NoThreat", unknown_04);
        unknown_05 = ini.Get_Bool(Name(), "Zombie", unknown_05);
        unknown_06 = ini.Get_Bool(Name(), "Recruitable", unknown_06);
        unknown_07 = ini.Get_Bool(Name(), "Paralyzed", unknown_07);
        unknown_08 = ini.Get_Bool(Name(), "Retaliate", unknown_08);
        unknown_09 = ini.Get_Bool(Name(), "Scatter", unknown_09);
        unknown_10 = ini.Get_Double(Name(), "Rate", unknown_10);
        unknown_18 = ini.Get_Double(Name(), "AARate", 0);
        if (unknown_18 == 0) {
            unknown_18 = unknown_10;
        }
        return true;
    }
    return false;
}
