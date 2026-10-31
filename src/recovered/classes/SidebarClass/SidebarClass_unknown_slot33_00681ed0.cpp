// wchar_t const *SidebarClass::unknown_slot33(int id) (0x00681ED0, slot 33)
// Help text of a button: the power bar's and radar's first; the two scroll
// buttons (ids 200, 201) and the four tab buttons (ids 203-206) show their
// tip, marked "Disabled" when the button is off; ids 1000 and up are the
// build icons of the active strip.
#include "shared/sidebar.hpp"
// @ref ??_C@_0N@EIBO@Tip?3ScrollUp?$AA@=007f3fb4
// @ref ??_C@_0N@GEG@Tip?3Disabled?$AA@=007f3fa4
// @ref ??_C@_1BA@PMGE@?$AA?$CF?$AAs?$AA?6?$AA?$CI?$AA?$CF?$AAs?$AA?$CJ?$AA?$AA@=007f3f94
// @ref ??_C@_0P@CBME@Tip?3ScrollDown?$AA@=007f3f84
// @ref ??_C@_08EHKC@Tip?3Tab1?$AA@=007f3f78
// @ref ??_C@_08LIBL@Tip?3Tab2?$AA@=007f3f6c
// @ref ??_C@_08BCIM@Tip?3Tab3?$AA@=007f3f60
// @ref ??_C@_08EHGJ@Tip?3Tab4?$AA@=007f3f54
extern wchar_t unknown_text_ab9274[];   // 0x00AB9274
// @ref ?unknown_slot33@PowerClass@@UAEPBGH@Z=0061d1c0
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref _swprintf=00783764
// @ref ?unknown_text_ab9274@@3PAGA=00ab9274
// @ref ?unknown_button_abccc0@SidebarClass@@2VShapeButtonClass@@A=00abccc0
// @ref ?unknown_button_abcbe8@SidebarClass@@2VShapeButtonClass@@A=00abcbe8
// @ref ?unknown_buttons_ab9508@SidebarClass@@2PAVShapeButtonClass@@A=00ab9508
// @ref ?Is_Enabled@GadgetClass@@QAE_NXZ=004cf160
// @ref ?Help_Text@StripClass@SidebarClass@@QAEPBGH@Z=0067f580
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_int_83962c@@3HA=0083962c
// @ref ?unknown_int_839624@@3HA=00839624
// @ref ?unknown_abcd64@@3HA=00abcd64

wchar_t const *SidebarClass::unknown_slot33(int id)
{
    wchar_t const *text = PowerClass::unknown_slot33(id);
    if (text == 0) {
        bool disabled = false;
        if (id == 200) {
            text = StringTable::Load_String("Tip:ScrollUp", 0, "D:\\Ra2\\Sidebar.CPP", 4297);
            disabled = !unknown_button_abccc0.Is_Enabled();
        } else if (id == 201) {
            text = StringTable::Load_String("Tip:ScrollDown", 0, "D:\\Ra2\\Sidebar.CPP", 4303);
            disabled = !unknown_button_abcbe8.Is_Enabled();
        } else if (id >= 203 && id < 207) {
            int tab = id - 203;
            if (tab == 0) {
                text = StringTable::Load_String("Tip:Tab1", 0, "D:\\Ra2\\Sidebar.CPP", 4311);
            } else if (tab == 1) {
                text = StringTable::Load_String("Tip:Tab2", 0, "D:\\Ra2\\Sidebar.CPP", 4313);
            } else if (tab == 2) {
                text = StringTable::Load_String("Tip:Tab3", 0, "D:\\Ra2\\Sidebar.CPP", 4315);
            } else if (tab == 3) {
                text = StringTable::Load_String("Tip:Tab4", 0, "D:\\Ra2\\Sidebar.CPP", 4317);
            }
            disabled = !unknown_buttons_ab9508[tab].Is_Enabled();
        } else {
            int count = Unknown_006820F0();
            if (id >= 1000 && id < 1000 + count) {
                return Column[unknown_4ed8].Help_Text(id - 1000);
            }
        }
        if (disabled) {
            swprintf(unknown_text_ab9274, L"%s\n(%s)", text,
                     StringTable::Load_String("Tip:Disabled", 0, "D:\\Ra2\\Sidebar.CPP", 4336));
            return unknown_text_ab9274;
        }
    }
    return text;
}
