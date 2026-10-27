// rc_ptr<FlagGameOption> __fastcall WorldDominationTour::FlagGameOption::Create(int flag, Wstring off_label, int off_value, Wstring on_label, int on_value) (0x007287D0)
#include "shared/wdt_game_options.hpp"

namespace WorldDominationTour {

rc_ptr<FlagGameOption> __fastcall FlagGameOption::Create(int flag, Wstring off_label, int off_value, Wstring on_label,
                                                         int on_value)
{
    return rc_ptr<FlagGameOption>(new FlagGameOption(flag, off_label, off_value, on_label, on_value));
}

}
