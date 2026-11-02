#include "shared/tab.hpp"
void TabClass::Unknown_006A1880()
{
    for (int index=0; index<25; index++) Buttons[index].Set_Shape(0,0,0);
    Rect area = *unknown_rect_ac1208;
    int right=area.X+area.Width;
    for (int slot=0;slot<25;slot++) {
        ShapeButtonClass *button=Unknown_006A0600(slot);
        if (button) {
            Rect box=*unknown_rect_ac120c;
            int x = SlotButton[slot]*unknown_int_abe388 + box.X;
            int y = unknown_int_abe374;
            if (box.Width+x<=right) {
                button->ID=slot+0xd6;
                button->unknown_50=unknown_drawer_8323cc;
                button->IsOn=false;
                button->ToggleType=0;
                button->Set_Flags(5);
                button->Set_Position(x,y);
                button->Set_Shape(ButtonShapes[slot],0,0);
            }
        }
    }
    ShapeButtonClass *planning=Unknown_006A0600(unknown_int_abe36c);
    if (planning) {
        planning->ToggleType=1;
        planning->unknown_40=true;
    }
    for (int team_slot=unknown_int_abe370;team_slot<=unknown_int_abe468;team_slot++) {
        ShapeButtonClass *button=Unknown_006A0600(team_slot);
        if (button) button->Set_Flags(0x55);
    }
}
