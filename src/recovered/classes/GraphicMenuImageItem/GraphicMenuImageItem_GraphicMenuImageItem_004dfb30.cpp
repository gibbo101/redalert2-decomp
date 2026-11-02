// GraphicMenuImageItem::GraphicMenuImageItem(...) (0x004DFB30)
// Takes the engine and the active area, the hover sound and the select movie name, and
// adds the PCX images that are named (highlighted and disabled ones start hidden).
#include "shared/graphic_menu.hpp"
#include "shared/wstring.hpp"
// @ref ??0GraphicMenuItem@@QAE@H@Z=004e0120
// @ref ??_7GraphicMenuImageItem@@6B@=007a2bb4
// @ref ?Add_Anim@MSEngine@@QAEHPAVMSAnim@@@Z=005b2d60

GraphicMenuImageItem::GraphicMenuImageItem(int id, void *unknown_list, Point2D const &origin, INIRect const &area,
                                           Wstring const &image, Wstring const &highlighted, Wstring const &disabled,
                                           Wstring const &highlight_sound, Wstring const &select_vq)
    : GraphicMenuItem(id), Engine((MSEngine *)unknown_list), Area(*(Rect const *)&area),
      unknown_image_24(0), unknown_image_28(0), unknown_image_2c(0), unknown_sound_30(0)
{
    MSEngine *engine = (MSEngine *)unknown_list;
    unknown_sound_30 = highlight_sound.Length() > 0 ? new MSSfxEntry("HighlightSound", highlight_sound) : 0;
    unknown_name_34 = select_vq;

    if (highlighted.Length() > 0) {
        unknown_image_28 = new MSPCXAnim(highlighted, &engine->Anims, origin, true);
        if (unknown_image_28 != 0) {
            unknown_image_28->Set_Unknown_0C(false);
            engine->Add_Anim(unknown_image_28);
        }
    }
    if (image.Length() > 0) {
        unknown_image_24 = new MSPCXAnim(image, &engine->Anims, origin, true);
        if (unknown_image_24 != 0) {
            engine->Add_Anim(unknown_image_24);
        }
    }
    if (disabled.Length() > 0) {
        unknown_image_2c = new MSPCXAnim(disabled, &engine->Anims, origin, true);
        if (unknown_image_2c != 0) {
            unknown_image_2c->Set_Unknown_0C(false);
            engine->Add_Anim(unknown_image_2c);
        }
    }
}
