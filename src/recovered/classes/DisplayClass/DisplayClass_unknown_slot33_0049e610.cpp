// wchar_t const *DisplayClass::unknown_slot33(int id) (0x0049E610, slot 33)
// Help text for the tactical area (ids 500..900, not while scrolling): the
// cell position when the cursor position display is on, the shadow text
// over unmapped cells, nothing for hidden enemy technos, otherwise the name
// of the object under the cursor (the cell's tiberium for non-technos)
// (TibSun DisplayClass::Help_Text).
#include "shared/display.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/house_screen.hpp"
#include "shared/mouse.hpp"
#include "shared/string_table.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_show_cursor_position_a416bc@@3_NA=00a416bc
// @ref ?unknown_b263d8@@3HA=00b263d8
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref _swprintf=00783764
// @ref ?unknown_47a200@CellClass@@QBEPBGXZ=0047a200
// @ref ?unknown_47c2e0@CellClass@@QBE_NH@Z=0047c2e0
// @ref ??_C@_0BD@GHCE@D?3?2Ra2?2Display?4CPP?$AA@=007d5e58
// @ref ??_C@_0L@NALF@TXT_SHADOW?$AA@=007d5e4c
// @ref ??_C@_1BA@DJFG@?$AA?$CI?$AA?$CF?$AAd?$AA?0?$AA?$CF?$AAd?$AA?$CJ?$AA?$AA@=007d5e6c
// @ref _?_buffer@?1??unknown_slot33@DisplayClass@@UAEPBGH@Z@4PAGA=00852848

wchar_t const *DisplayClass::unknown_slot33(int id)
{
    static wchar_t _buffer[100];        // 0x00852848 (size a hypothesis)

    if (id < 500 || id > 900 || unknown_slot26()) {
        return 0;
    }

    Cell cell;
    CoordStruct coord;
    ObjectClass *object;
    bool fog, shadow;

    int left = unknown_rect_839630.X;
    int top = unknown_rect_839630.Y;
    Point2D xy = WWMouse->Get_Mouse_XY();
    Point2D point(xy.X - left, xy.Y - top);
    Map.Unknown_00669650(point, cell, coord, object, fog, shadow);

    if (unknown_show_cursor_position_a416bc) {
        swprintf(_buffer, L"(%d,%d)", coord.X / 256, coord.Y / 256);
        return _buffer;
    }

    if (!(Map[coord].unknown_12c & 8) && unknown_b263d8) {
        return StringTable::Load_String("TXT_SHADOW", 0, "D:\\Ra2\\Display.CPP", 4976);
    }

    if (object == 0) {
        return 0;
    }
    TechnoClass *techno = object != 0 && object->AbstractFlags.IsTechno ? (TechnoClass *)object : 0;
    if (techno != 0) {
        if (!techno->unknown_372) {
            if (techno->unknown_1b8 == 2 && !Map[techno->Center_Coord()].unknown_47c2e0(unknown_player_a35db4->ArrayIndex)) {
                return 0;
            }
            if (techno->unknown_slot32()->Invisible) {
                return 0;
            }
        }
    }

    if (object != 0) {
        wchar_t const *text = object->unknown_slot35();
        if (techno == 0) {
            text = (*this)[cell].unknown_47a200();
        }
        return text;
    }

    return 0;
}
