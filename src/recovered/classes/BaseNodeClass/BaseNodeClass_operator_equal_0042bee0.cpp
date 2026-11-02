// BaseNodeClass::operator== (0x0042BEE0; TibSun base.cpp): the type and the cell.
#define RA2_BASE_NODE_MEMBER_OPERATORS
#include "shared/house_nodes.hpp"

bool BaseNodeClass::operator==(BaseNodeClass const &node)
{
    return Type == node.Type && Cell == node.Cell;
}
