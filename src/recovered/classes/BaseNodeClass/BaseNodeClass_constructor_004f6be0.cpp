// BaseNodeClass::BaseNodeClass(int type, Cell const &cell) (0x004F6BE0)
// A base plan node for building type `type` at `cell`, not yet built and with no attempts. The base
// planner 0x004F5D30 inlines it until its /Ob2 budget runs out and calls this copy for the last three
// corners of a wall ring.
#include "shared/house_nodes.hpp"
BaseNodeClass::BaseNodeClass(int type, ::Cell const &cell)
{
    Type = type;
    Cell = cell;
    unknown_08 = false;
    unknown_0c = 0;
}
