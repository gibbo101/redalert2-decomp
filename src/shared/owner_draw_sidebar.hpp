// Placement helpers shared by the sidebar control placement functions 0x005E8C50-0x005E9260 (ownrdraw.cpp).
#ifndef RA2_SHARED_OWNER_DRAW_SIDEBAR_HPP
#define RA2_SHARED_OWNER_DRAW_SIDEBAR_HPP
#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/rect.hpp"
#include "shared/session_state.hpp"
#include "shared/shape_file.hpp"
#include "shared/unknown_globals.hpp"
extern Rect *unknown_rect_ac11c8;
extern Rect *unknown_rect_ac11cc;
extern Rect *unknown_rect_ac11ec;
extern Rect *unknown_rect_ac11f0;
extern Rect *unknown_rect_ac11f4;
extern ShapeFileStruct *unknown_shape_ac10b8;
extern ShapeFileStruct *unknown_shape_ac0ff8;
namespace OwnerDraw {
inline int Sidebar_Inset(int width, unsigned char flag)
{
    int inset = 0;
    if (!flag) {
        int excess = (width - unknown_7add6c) / 2;
        inset = excess < 0 ? 0 : excess;
    }
    return inset;
}
inline int Sidebar_Margin(HWND window, int width)
{
    UnknownControlRecord *record = unknown_registry_a73640.Find((unsigned int)window);
    if (record && record->unknown_dc) return record->unknown_dc;
    return (unknown_int_7add80 - width) / 2;
}
}
#endif
