// Node reset, original004F6BE0;28body+4padding.
// Actual class follows original House node insertion callers and the four-field node layout.
// EAX returns this; constructor identity is not assumed.
#include "shared/house_nodes.hpp"
BaseNodeClass *BaseNodeClass::unknown_4f6be0(int type, ::Cell const &cell)
{
    Type=type;
    Cell=cell;
    unknown_08=false;
    unknown_0c=0;
    return this;
}
