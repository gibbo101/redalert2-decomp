// MouseClass::MouseClass() (0x0059F020)
// Constructs the scroll layer and clears the mouse state.
#include "shared/mouse_class.hpp"
// @ref ??0ScrollClass@@QAE@XZ=006695e0
// @ref ??_7MouseClass@@6BSidebarClass@@@=0079a954
// @ref ??_7MouseClass@@6BINoticeSink@@@=0079a94c

MouseClass::MouseClass() : IsSmall(false), CurrentMouseShape(0), NormalMouseShape(0), Frame(0)
{
}
