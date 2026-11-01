// UnknownTab4EEC::Unknown_00494650(bool forced) (0x00494650): TibSun's CreditClass::AI.

void UnknownTab4EEC::Unknown_00494650(bool forced)
{
    static int _last = 0;

    _last = Frame;

    unknown_00 = unknown_player_a35db4->As_IHouse()->Available_Money();
    unknown_00 = unknown_00 > 0 ? unknown_00 : 0;

    if (unknown_id_source_a3d290->MissionTimer.Is_Active() || unknown_id_source_a3d290->MissionTimer) {
        unknown_08 = true;
        Map.Flag_To_Redraw();
    }

    if (unknown_04 == unknown_00) return;

    if (forced) {
        unknown_0a = false;
        unknown_04 = unknown_00;
    } else {
        if (unknown_0c) unknown_0c--;

        int adder = unknown_00 - unknown_04;

        if (adder > 0) {
            unknown_0c = 1;
        } else {
            unknown_0c = 3;
        }

        adder = abs(adder);
        adder >>= 3;
        if (adder < 1) {
            adder = 1;
        } else if (adder > 71+72) {
            adder = 71+72;
        }
        if (unknown_04 > unknown_00) adder = -adder;
        unknown_04 += adder;
        if (unknown_04 - adder != unknown_04) {
            unknown_0a = true;
            unknown_09 = (adder > 0);
        }
    }
    unknown_08 = true;
    Map.Flag_To_Redraw();
    Map.unknown_4ee4 = true;
}
// @ref _?_last@?1??Unknown_00494650@UnknownTab4EEC@@QAEX_N@Z@4HA=00851ca4
// @ref ?Flag_To_Redraw@GScreenClass@@UAEXH@Z=004e09a0
// @ref ?Frame@@3HA=00a40d2c
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
