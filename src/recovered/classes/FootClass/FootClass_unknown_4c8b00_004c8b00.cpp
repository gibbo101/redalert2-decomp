// void FootClass::unknown_4c8b00() (0x004C8B00)
// With nothing at +0x494: takes the first entry of the +0x49C queue as the
// new destination (slot 260), removes it, and re-queues it at the end when
// the queue loops (+0x59B).
#include "shared/foot.hpp"

void FootClass::unknown_4c8b00()
{
    if (unknown_494 == 0 && unknown_49c.Count() != 0) {
        AbstractClass *next = unknown_49c[0];
        if (next != 0) {
            unknown_slot260(next, true);
            unknown_49c.Delete(0);
            if (unknown_59b) {
                unknown_49c.Add(next);
            }
        }
    }
}
