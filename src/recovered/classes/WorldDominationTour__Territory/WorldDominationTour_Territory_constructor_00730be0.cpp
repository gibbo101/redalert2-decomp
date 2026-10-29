// WorldDominationTour::Territory::Territory(...) (0x00730BE0, 541 bytes; the inventory bound of 234 stops at a Ghidra noreturn call)
// Name is the CSF text of <name_prefix><NN>, ShapeName <shape_prefix><NN>.shp, Target/Origin the INI points
// "Target_<width>"/"Origin_<width>" with the _800 keys as fallback on screens wider than 800.
// @ref ??_C@_04NLOD@?4shp?$AA@=007fc6c0
// @ref ??_C@_07GLHL@Target_?$AA@=007fc124
// @ref ??_C@_07KIIH@Origin_?$AA@=007fc6a4
// @ref ??_C@_0BD@HPLF@D?3?2Ra2?2WDTTerr?4cpp?$AA@=007fc6ac
// @ref ??_C@_0L@HOPG@Target_800?$AA@=007fc698
// @ref ??_C@_0L@KNIG@Origin_800?$AA@=007fc68c
#include "shared/world_domination_tour.hpp"
#include "shared/string_table.hpp"
#include "shared/unknown_globals.hpp"
namespace WorldDominationTour {

Territory::Territory(int index, INIClass const &ini, Wstring const &section, Wstring const &shape_prefix,
                     Wstring const &name_prefix) :
    Index(index),
    OwnerAnim(0),
    HighlightAnim(0),
    unknown_2c(0)
{
    ShapeName = Wstring_Join(shape_prefix, Wstring_From_Integer(index, 2)) + ".shp";
    Wstring label = Wstring_Join(name_prefix, Wstring_From_Integer(index, 2));
    Name = StringTable::Load_String(label.Get(), 0, "D:\\Ra2\\WDTTerr.cpp", 39);
    Wstring width = Wstring_From_Integer(unknown_8523e0);
    Target = ini.Get_Point(section, "Target_" + width, Target);
    Origin = ini.Get_Point(section, "Origin_" + width, Origin);
    if (unknown_8523e0 > 800) {
        if (Target.X == 0 && Target.Y == 0) {
            Wstring key("Target_800");
            Target = ini.Get_Point(section, key, Target);
        }
        if (Origin.X == 0 && Origin.Y == 0) {
            Wstring key("Origin_800");
            Origin = ini.Get_Point(section, key, Origin);
        }
    }
}
}
