// int __fastcall House_Facing_Score(HouseClass *, Cell const &, int, int) (0x004F02E0)
// A placement score callback that HouseClass 0x004F03C0 calls (0x004F1190
// passes it): the score plus 1000 per point of the cell's value (+0x15F44,
// over the base plan's area) times 128, plus, for a facing other than -1,
// how far the direction from the base plan's cell is from that 8-way facing
// (0..128 of 256). Name hypothesis.
#include "shared/house.hpp"
#include "shared/base.hpp"
#include "shared/rect.hpp"
#include "shared/facing.hpp"
#include "shared/fast_math.hpp"
#include "shared/crt_memory.hpp"


inline UnknownFacingDir Offset_Direction(int x, int y)
{
    return UnknownFacingDir((unsigned short)((Fast_Atan2(y, x) - 1.5707963267948966) * -10430.060040584269));
}

int __fastcall House_Facing_Score(HouseClass *house, Cell const &cell, int score, int facing)
{
    BaseClass &base = house->unknown_55f0;
    int value = house->unknown_15f44[cell.X - base.unknown_54.X + (cell.Y - base.unknown_54.Y) * base.unknown_54.Width];
    int diff = 0;
    if (facing != -1) {
        Point2D d;
        d.X = cell.X - base.unknown_50.X;
        d.Y = cell.Y - base.unknown_50.Y;
        UnknownFacingDir dir = Offset_Direction(d.X, -d.Y);
        diff = abs(facing * 32 - Dir_To_256(dir));
        if (diff >= 128) {
            diff = 255 - diff;
        }
    }
    return score + (value * 128 + diff) * 1000;
}
