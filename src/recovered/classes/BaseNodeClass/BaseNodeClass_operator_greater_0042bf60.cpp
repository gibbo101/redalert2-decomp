// BaseNodeClass::operator> (0x0042BF60; TibSun base.cpp): always true.
#include "shared/house_nodes.hpp"

bool BaseNodeClass::operator>(BaseNodeClass const &)
{
    return true;
}
