// rc_ptr<MapSizeGameOption> __fastcall WorldDominationTour::MapSizeGameOption::Create(int flag) (0x00728A60)
// @ref ??_7?$rc_ptr@VMapSizeGameOption@WorldDominationTour@@@@6B@=007af0f8
// @ref ??_7MapSizeGameOption@WorldDominationTour@@6B@=007af16c
#include "shared/wdt_game_options.hpp"

namespace WorldDominationTour {

rc_ptr<MapSizeGameOption> __fastcall MapSizeGameOption::Create(int flag)
{
    return rc_ptr<MapSizeGameOption>(new MapSizeGameOption(flag));
}

}
