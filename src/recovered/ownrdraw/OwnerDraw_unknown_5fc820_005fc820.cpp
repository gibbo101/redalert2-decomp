// @ref ?Get_Red_Left@@YAHXZ=004abb30
// @ref ?Get_Red_Right@@YAHXZ=004abb40
// @ref ?Get_Green_Left@@YAHXZ=004abb50
// @ref ?Get_Green_Right@@YAHXZ=004abb60
// @ref ?Get_Blue_Left@@YAHXZ=004abb70
// @ref ?Get_Blue_Right@@YAHXZ=004abb80
// @ref ?unknown_red_mask_a763dc@OwnerDraw@@3GA=00a763dc
// @ref ?unknown_green_mask_a763de@OwnerDraw@@3GA=00a763de
// @ref ?unknown_blue_mask_a763e0@OwnerDraw@@3GA=00a763e0
#include "shared/hicolor.hpp"
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

unsigned short unknown_red_mask_a763dc = 0;
unsigned short unknown_green_mask_a763de = 0;
unsigned short unknown_blue_mask_a763e0 = 0;

// Builds the screen pixel format's channel masks from the hicolor shifts (0x005FC820).
void unknown_5fc820()
{
    unknown_red_mask_a763dc = 0xff;
    unknown_red_mask_a763dc >>= Get_Red_Right();
    unknown_red_mask_a763dc <<= Get_Red_Left();
    unknown_green_mask_a763de = 0xff;
    unknown_green_mask_a763de >>= Get_Green_Right();
    unknown_green_mask_a763de <<= Get_Green_Left();
    unknown_blue_mask_a763e0 = 0xff;
    unknown_blue_mask_a763e0 >>= Get_Blue_Right();
    unknown_blue_mask_a763e0 <<= Get_Blue_Left();
}

}
