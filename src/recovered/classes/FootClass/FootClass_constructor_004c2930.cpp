// FootClass::FootClass(HouseClass *house) (0x004C2930)
// A foot unit of a house: no path, no team, no destination; listed in the FootClass list
// (0x00865F38) and in the list at 0x00AC0C18.
#include "shared/foot.hpp"
#include "shared/object_lists.hpp"

FootClass::FootClass(HouseClass *house) :
    TechnoClass(house),
    unknown_418(-1),
    unknown_41c(0, 0),
    unknown_420(0, 0),
    unknown_428(0.0),
    unknown_430(0),
    unknown_434(false),
    unknown_438(0),
    unknown_450(0, 0),
    unknown_454(0, 0),
    unknown_458(0, 0),
    unknown_45c(0, 0, 0),
    unknown_468(0.0),
    unknown_470(1.0),
    unknown_478(0, 0),
    unknown_490(0),
    unknown_494(0),
    unknown_498(0),
    unknown_49c(0, 0),
    unknown_4b4(-1),
    unknown_4b8(0),
    unknown_4bc(0),
    unknown_4c1(false),
    Team(0),
    unknown_4c8(0),
    unknown_4cc(0),
    unknown_53c(10),
    unknown_568(unknown_geometry_l),
    unknown_574(-1),
    unknown_575(false),
    unknown_576(0),
    unknown_577(false),
    unknown_578(false),
    unknown_579(false),
    unknown_57a(false),
    unknown_57b(false),
    unknown_57c(false),
    unknown_57d(false),
    unknown_57e(false),
    unknown_580(0),
    unknown_584(0),
    unknown_588(0),
    unknown_598(false),
    unknown_599(false),
    unknown_59a(false),
    unknown_59b(false),
    unknown_59c(false),
    unknown_59d(false),
    unknown_59e(false),
    unknown_59f(false),
    unknown_5a0(true),
    unknown_5a1(false),
    unknown_5a2(false)
{
    unknown_4d0 = -1;
    unknown_43c.Init();
    unknown_FootClass_list_00865f38.Add(this);
    unknown_14_bit2 = 1;
    unknown_list_ac0c18.Add(this);
}
