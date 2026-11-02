// void LineTrail::AI() (0x00539530)
// Starts a new point at full intensity when the owner has moved since the newest point, then fades
// every point by Decrement (not below zero), newest first. The slot step goes through a reference
// (`slot`), which makes VC6 reload ActiveSlot instead of reusing the compare's load.
#include "shared/line_trail.hpp"
#include "shared/object.hpp"

void LineTrail::AI()
{
    if (Owner != 0) {
        CoordStruct coord = Owner->Coord;
        if (coord != Trails[ActiveSlot].Position) {
            int &slot = ActiveSlot;     // newest slot steps back, wrapping to 31
            if (--slot < 0) {
                slot = 31;
            }
            LineTrailNode &node = Trails[ActiveSlot];
            node.Position = coord;
            node.Value = 255;
        }
    }

    int index = ActiveSlot;
    do {
        LineTrailNode &node = Trails[index];
        node.Value -= Decrement;
        if (node.Value < 0) {
            node.Value = 0;
        }
        index++;
        if (index >= 32) {
            index = 0;
        }
    } while (index != ActiveSlot);
}
