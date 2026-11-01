// bool __fastcall Hicolor_Init_Table(int mode) -- 0x0070B690
// Allocates the 32x32x32 pixel table and fills it for a screen pixel format.
// @ref ?HicolorTable@@3PAGA=00ad0614
// @ref ??2@YAPAXI@Z=00782017
// @ref ??_V@YAXPAX@Z=00781d3b
#include "shared/unvq_table.hpp"

static bool Hicolor_Set_Mode(int mode);

bool __fastcall Hicolor_Init_Table(int mode)
{
    Hicolor_Clear_Table();
    HicolorTable = new unsigned short[65534];
    if (HicolorTable != 0) {
        return Hicolor_Set_Mode(mode);
    }
    return false;
}
