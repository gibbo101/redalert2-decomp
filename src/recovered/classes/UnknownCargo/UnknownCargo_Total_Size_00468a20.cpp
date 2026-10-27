// Cargo total size00468A20, complete77+3. Private current diagnostic; not accepted.
// OwnerR489scope approved2026-10-26T0210Z. CapturedCount, per-passenger int truncation.
#include "shared/foot.hpp"

int UnknownCargo::Unknown_00468A20() const
{
    int limit = Count;
    int total_size = 0;
    ObjectClass *first = Object;
    if (first) {
        FootClass *passenger = static_cast<FootClass *>(unknown_468a10());
        if (passenger) {
            for (int index = 0; index < limit && passenger; ++index) {
                total_size = (int)(total_size + passenger->unknown_slot32()->Size);
                passenger = static_cast<FootClass *>(passenger->unknown_30);
            }
        }
    }
    return total_size;
}
