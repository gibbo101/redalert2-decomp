// bool BaseClass::unknown_42c080(int index) const (0x0042C080)
// The node's +0x08 flag.
#include "shared/base.hpp"

bool BaseClass::unknown_42c080(int index) const
{
    return Nodes[index].unknown_08;
}
