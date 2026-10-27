// void RadarClass::unknown_slot34() (0x006306D0, slot 34)
// After the display's, places the radar's buttons (shifted right by the
// tactical width when the sidebar is on the right, 0x00A40B30), and
// registers their tooltips (briefing or diplomacy, options).
#include "shared/radar.hpp"
#include "shared/tool_tip.hpp"
// @ref ?unknown_slot34@DisplayClass@@UAEXXZ=0049e7d0
// @ref ?ToolTips@@3PAVCCToolTip@@A=008399b0
// @ref ?Remove@ToolTipManager@@QAEXI@Z=006eba10
// @ref ?Add@ToolTipManager@@QAE_NABVToolTip@@@Z=006eb860
// @ref ??_C@_0BD@JOIH@Tip?3BriefingButton?$AA@=007ee234
// @ref ??_C@_0BE@NGLC@Tip?3DiplomacyButton?$AA@=007ee220
// @ref ??_C@_0BC@IPID@Tip?3OptionsButton?$AA@=007ee20c

void RadarClass::unknown_slot34()
{
    DisplayClass::unknown_slot34();
    int offset = unknown_flag_a40b30 ? unknown_int_839638 : 0;
    unknown_button_ab63e8.OffsetX = -offset;
    unknown_button_ab63e8.Set_Position(unknown_int_ab6468 + offset, unknown_int_ab646c);
    unknown_button_ab63e8.Flag_To_Redraw();
    unknown_button_ab6380.OffsetX = -offset;
    unknown_button_ab6380.Set_Position(unknown_int_ab6338 + offset, unknown_int_ab633c);
    unknown_button_ab6380.Flag_To_Redraw();
    RadarButton.Set_Position(unknown_11ec + offset, unknown_11f0);
    RadarButton.Flag_To_Redraw();

    ToolTip tip;
    tip.ID = 0xF2;
    tip.Label = "Tip:BriefingButton";
    if (unknown_game_mode_a3d298) {
        tip.Label = "Tip:DiplomacyButton";
    }
    tip.Region.X = unknown_button_ab63e8.X;
    tip.Region.Y = unknown_button_ab63e8.Y;
    tip.Region.Width = unknown_button_ab63e8.Width;
    tip.Region.Height = unknown_button_ab63e8.Height;
    ToolTips->Remove(0xF2);
    ToolTips->Add(tip);
    tip.ID = 0xF3;
    tip.Label = "Tip:OptionsButton";
    tip.Region.X = unknown_button_ab6380.X;
    tip.Region.Y = unknown_button_ab6380.Y;
    tip.Region.Width = unknown_button_ab6380.Width;
    tip.Region.Height = unknown_button_ab6380.Height;
    ToolTips->Remove(0xF3);
    ToolTips->Add(tip);
    unknown_14d6 = true;
}
