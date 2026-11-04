// RA2-specific dialog/control rectangle selection, independently bounded005E6450.
#include "shared/owner_draw_dialog_control.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/id_source.hpp"
#include "shared/rect.hpp"
namespace OwnerDraw {
bool __fastcall Select_Control_Rect_005e6450(HWND dialog,HWND control,Rect *bounds)
{
    UnknownControlRecord *record = Get_Record(dialog);
    int kind = record ? record->unknown_6c : 0;
    int id = GetDlgCtrlID(control);
    Rect *selected = 0;
    if (kind == 0x94) {
        if (unknown_8523e0 < unknown_screen_widths_7add68[1]) return false;
        if (id == 0x6ea) selected = new Rect(0x1e,0x1a,0x23a,0x87);
        else if (id == 0x6eb) selected = new Rect(0x52,0xbb,0x1d4,0x6c);
        else if (id == 0x6ec) selected = new Rect(0x62,0x12a,0x1bc,0x95);
        else if (id == 0x50f) selected = new Rect(0xb1,0x1fd,0x110,0x15);
        else if (id == 0x71e) selected = new Rect(0xb1,0x1dc,0x8d,0x14);
        else if (id == 0x670) selected = new Rect(0x135,0x1dc,0x8d,0x14);
        else return false;
    }
    else if (kind == 0x103) {
        if (id != 0x72b) return false;
        if (unknown_8523e0 >= unknown_screen_widths_7add68[1]) {
            if (unknown_id_source_a3d290->unknown_2239) selected = new Rect(0x68,0x8e,0x1a8,0xdc);
            else selected = new Rect(0x67,0x82,0x1a8,0xe6);
        } else {
            if (unknown_id_source_a3d290->unknown_2239) selected = new Rect(0x18,0x8e,0x1a8,0xdc);
            else selected = new Rect(0x17,0x82,0x1a8,0xe6);
        }
    }
    else if (kind == 0xbc7) {
        if (id != 0x72b) return false;
        if (unknown_8523e0 >= unknown_screen_widths_7add68[1]) {
            if (unknown_id_source_a3d290->unknown_2239) selected = new Rect(0x68,0x8e,0x1a8,0xdc);
            else selected = new Rect(0x67,0x82,0x1a8,0xe6);
        } else {
            if (unknown_id_source_a3d290->unknown_2239) selected = new Rect(0x18,0x8e,0x1a8,0xdc);
            else selected = new Rect(0x17,0x82,0x1a8,0xe6);
        }
    }
    else if (kind == 0xbc) {
        if (id != 0x72f) return false;
        if (unknown_8523e0 == unknown_screen_widths_7add68[0]) selected = new Rect(0x34,0x4e,0x18c,0x8f);
        else if (unknown_8523e0 == unknown_screen_widths_7add68[1] || unknown_8523e0 == unknown_screen_widths_7add68[2]) selected = new Rect(0x84,0x8a,0x18c,0x8f);
        else return false;
    }
    else if (kind == 0xbd) {
        if (id != 0x72f) return false;
        if (unknown_8523e0 == unknown_screen_widths_7add68[0]) selected = new Rect(0x34,0x4e,0x18c,0x8f);
        else if (unknown_8523e0 == unknown_screen_widths_7add68[1] || unknown_8523e0 == unknown_screen_widths_7add68[2]) selected = new Rect(0x84,0x8a,0x18c,0x8f);
        else return false;
    }
    else if (kind == 0xc2) {
        if (id != 0x72f) return false;
        if (unknown_8523e0 == unknown_screen_widths_7add68[0]) selected = new Rect(0x34,0x4e,0x18c,0x8f);
        else if (unknown_8523e0 == unknown_screen_widths_7add68[1] || unknown_8523e0 == unknown_screen_widths_7add68[2]) selected = new Rect(0x84,0x8a,0x18c,0x8f);
        else return false;
    }
    else if (kind == 0xc9) {
        if (id != 0x72f) return false;
        if (unknown_8523e0 == unknown_screen_widths_7add68[0]) selected = new Rect(0x34,0x4e,0x18c,0x8f);
        else if (unknown_8523e0 == unknown_screen_widths_7add68[1] || unknown_8523e0 == unknown_screen_widths_7add68[2]) selected = new Rect(0x84,0x8a,0x18c,0x8f);
        else return false;
    }
    else return false;
    if (!selected) return false;
    *bounds = *selected;
    delete selected;
    return true;
}
}
