// void GraphicMenu::Set_Anim(MSAnim *anim) (0x004DED20): replaces the background animation in the engine.
#include "shared/graphic_menu_class.hpp"
// @ref ?Add_Anim@MSEngine@@QAEHPAVMSAnim@@@Z=005b2d60
// @ref ?Replace_Anim@MSEngine@@QAEXPAVMSAnim@@0@Z=005b2dd0

void GraphicMenu::Set_Anim(MSAnim *anim)
{
    if (Anim) {
        Engine.Replace_Anim(Anim, anim);   // argument order as the original pushes it
    } else {
        Engine.Add_Anim(anim);
    }
    Anim = anim;
}
