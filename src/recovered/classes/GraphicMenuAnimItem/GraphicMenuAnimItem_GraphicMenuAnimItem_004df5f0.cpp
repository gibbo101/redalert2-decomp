// GraphicMenuAnimItem::GraphicMenuAnimItem(...) (0x004DF5F0)
// Takes the active area; when both the shape file and the palette file exist, loads the
// palette's drawer (kept in +0x24 and deleted by the destructor) and adds a shape
// animation of the image at the origin to the engine's list.
#include "shared/graphic_menu.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/ini_class.hpp"
#include "shared/wstring.hpp"
// @ref ??0GraphicMenuItem@@QAE@H@Z=004e0120
// @ref ??_7GraphicMenuAnimItem@@6B@=007a2b98
// @ref ?Add_Anim@MSEngine@@QAEHPAVMSAnim@@@Z=005b2d60

GraphicMenuAnimItem::GraphicMenuAnimItem(int id, void *unknown_list, Point2D const &origin, INIRect const &area,
                                         Wstring const &image, Wstring const &palette, int rate, bool loop)
    : GraphicMenuItem(id), Area(*(Rect const *)&area), unknown_20(0), Anim(0)
{
    CCFileClass image_file(image);
    CCFileClass palette_file(palette);
    if (image_file.Is_Available() && palette_file.Is_Available()) {
        {
            Wstring name(palette.Peek_Buffer());
            Anim = (MSAnim *)unknown_load_drawer_5ac560(name);
        }
        MSShapeAnim *shape = new MSShapeAnim(image, origin.X, origin.Y, (ConvertClass *)Anim, rate, loop, 0);
        if (shape != 0) {
            ((MSEngine *)unknown_list)->Add_Anim(shape);
        }
    }
}
