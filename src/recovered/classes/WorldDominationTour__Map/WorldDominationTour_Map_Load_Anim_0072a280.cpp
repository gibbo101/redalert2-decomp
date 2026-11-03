// MSAnim *WorldDominationTour::Map::Load_Anim(INIClass &ini, Wstring const &section, Wstring const &entry,
// ConvertClass *drawer) (0x0072A280): the shape animation an INI entry "file,x,y[,rate[,palette]]"
// describes, placed relative to unknown_44 (the map origin); rate 5 and `drawer` when the entry
// leaves them out or the palette cannot be loaded (Get_Drawer). 0 when the entry is missing or has
// no y, the file is not available or there is no drawer.
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
#include "shared/wdt_map.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/ms_anim.hpp"

namespace WorldDominationTour {

MSAnim *Map::Load_Anim(INIClass &ini, Wstring const &section, Wstring const &entry, ConvertClass *drawer)
{
    Wstring value;
    if (ini.Get_String(section, entry, 0, value) > 0) {
        Wstring filename;
        Wstring x;
        Wstring y;
        Wstring rate;
        Wstring palette;
        int position = value.Get_Token(0, ",", filename);
        position = value.Get_Token(position, ",", x);
        position = value.Get_Token(position, ",", y);
        position = value.Get_Token(position, ",", rate);
        value.Get_Token(position, ",", palette);
        if (y != 0) {
            int xpos = x.As_Integer() + unknown_44.X;
            int ypos = y.As_Integer() + unknown_44.Y;
            int frame_rate = 5;
            if (rate != 0 && rate.Length() > 0) {
                frame_rate = rate.As_Integer();
            }
            ConvertClass *anim_drawer = 0;
            if (palette != 0 && palette.Length() > 0) {
                anim_drawer = Get_Drawer(palette);
            }
            if (anim_drawer == 0) {
                anim_drawer = drawer;
            }
            bool available = CCFileClass(filename).Is_Available();
            if (available && anim_drawer != 0) {
                return new MSShapeAnim(filename, xpos, ypos, anim_drawer, frame_rate, true, 0);
            }
        }
    }
    return 0;
}

}
