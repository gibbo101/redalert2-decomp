// BaseNodeClass::operator!= (0x0042BF10; TibSun base.cpp): the inlined operator== negated.
#include "shared/house_nodes.hpp"

bool BaseNodeClass::operator!=(BaseNodeClass const &node)
{
    return !(*this == node);
}
