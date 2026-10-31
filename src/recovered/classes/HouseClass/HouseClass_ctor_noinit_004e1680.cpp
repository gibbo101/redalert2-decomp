// House screen operations used by this population; full screen providers live in their own units.
#define RA2_HOUSE_SCREEN_AI
#include "shared/map.hpp"
// HouseClass::HouseClass(NoInitClass const &noinit) (0x004E1680)
// The constructor used when loading: the lists, the +0x1C8 timer, the
// counters and the base records are constructed empty; everything else is
// restored by Load.
#include "shared/building_class.hpp"

HouseClass::HouseClass(NoInitClass const &noinit)
    : AbstractClass(noinit),
      unknown_1d4(noinit),
      unknown_1e0(noinit),
      unknown_1ec(noinit),
      unknown_1f8(noinit),
      Tiberium(noinit),
      unknown_254(noinit),
      unknown_268(noinit),
      unknown_a70(noinit),
      unknown_1278(noinit),
      unknown_1a80(noinit),
      unknown_2288(noinit),
      unknown_2a90(noinit),
      unknown_3298(noinit),
      unknown_3aa0(noinit),
      unknown_42a8(noinit),
      unknown_4ab0(noinit),
      unknown_54e0(noinit),
      unknown_5524(noinit),
      unknown_5530(noinit),
      unknown_55e9(noinit),
      unknown_55ec(noinit),
      unknown_55f0(noinit),
      unknown_5678(noinit),
      unknown_5684(noinit),
      unknown_5690(noinit),
      unknown_569c(noinit),
      unknown_56a8(noinit),
      unknown_56b4(noinit),
      unknown_56c0(noinit),
      IniName(noinit),
      unknown_15ef5(noinit)
{
}
