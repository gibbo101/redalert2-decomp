// void UnitClass::unknown_slot312(Surface &surface, Point2D point, Rect window,
// int depth) (slot 312, 0x006FF3E0; slots 310/311 call it). Blits the
// unit's image surface (unknown_surface_83995c, through the unit rectangle
// 0x00AD0490 moved to point - (128, 128)) with the house color scheme's
// blitter for the cloak/flag state. A TooBigToFitUnderBridge unit (when
// 0x006CF670 holds and 0x006CF9D0 is 0, or it is in radio contact with a
// weapons factory) is drawn in two parts: all but the bottom 16 rows at
// depth slot 176 - 5, then the bottom 16 rows. Names are hypotheses.
#include "shared/unit.hpp"
#include "shared/building_type.hpp"
#include "shared/text_print.hpp"
#include "shared/blit.hpp"

void UnitClass::unknown_slot312(Surface &surface, Point2D point, Rect window, int depth)
{
    bool split = false;
    if (Type->TooBigToFitUnderBridge) {
        if (unknown_6cf670() && unknown_6cf9d0() == 0) {
            split = true;
        } else {
            TechnoClass *contact = Contact2(0);
            if (unknown_494 && contact && contact->Kind_Of() == 6 && ((BuildingClass *)contact)->Type->WeaponsFactory)
                split = true;
        }
    }
    int draw_adjust = 0;
    unsigned flags = 0x2800;
    switch (unknown_slot25(false, 0)) {
    case 1: flags = 0x2802; break;
    case 2:
    case 3: flags = 0x2804; break;
    case 4:
        flags = 0x280A;
        if (unknown_1bc.Value) flags = 0x280C;
        draw_adjust = unknown_6d6750();
        break;
    }
    if (unknown_slot111() || unknown_slot112()) flags |= 4;
    if (House->Unknown_004F52B0() && unknown_slot48()) flags = unknown_slot244(flags);
    Blitter *blitter = ColorSchemes[House->ColorSchemeIndex]->Converter->Select_Blitter_00485AA0(flags);
    Rect destination(unknown_unit_rect_ad0490.X + point.X - 128,
                     unknown_unit_rect_ad0490.Y + point.Y - 128,
                     unknown_unit_rect_ad0490.Width, unknown_unit_rect_ad0490.Height);
    if (split && unknown_unit_rect_ad0490.Height > 16) {
        Rect source = unknown_unit_rect_ad0490;
        destination.Height = unknown_unit_rect_ad0490.Height - 16;
        source.Height = destination.Height;
        Bit_Blit(surface, window, destination, *unknown_surface_83995c, unknown_surface_83995c->Get_Rect(), source,
                 *blitter, unknown_slot176() - 5, 0, depth, draw_adjust);
        destination.Y += destination.Height;
        source.Y += destination.Height;
        destination.Height = 16;
        source.Height = 16;
        Bit_Blit(surface, window, destination, *unknown_surface_83995c, unknown_surface_83995c->Get_Rect(), source,
                 *blitter, unknown_slot176(), 2, depth, draw_adjust);
        return;
    }
    Bit_Blit(surface, window, destination, *unknown_surface_83995c, unknown_surface_83995c->Get_Rect(), unknown_unit_rect_ad0490,
             *blitter, unknown_slot176(), unknown_slot177(), depth, draw_adjust);
}
