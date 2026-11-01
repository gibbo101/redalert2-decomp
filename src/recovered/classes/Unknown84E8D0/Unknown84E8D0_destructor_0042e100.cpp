// Unknown84E8D0::~Unknown84E8D0 (0x0042E100): deletes every beacon (0x0042E150 expanded). Out of line
// here; the exit thunk of unknown_object_84e8d0 (0x0042D990) expands it.
#include "shared/beacon.hpp"

Unknown84E8D0::~Unknown84E8D0()
{
    Unknown_0042E150();
}
