// int BaseClass::unknown_42cb70(BaseNodeClass *node) (0x0042CB70)
// Counts on the node's +0x0C (0 without a node).
#include "shared/base.hpp"

int BaseClass::unknown_42cb70(BaseNodeClass *node)
{
    if (node == 0) {
        return 0;
    }
    return ++node->unknown_0c;
}
