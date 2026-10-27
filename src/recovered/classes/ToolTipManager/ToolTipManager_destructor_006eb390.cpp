// ToolTipManager::~ToolTipManager() (0x006EB390)
// Stops the timer, hides the tip being shown and frees the registered tips.
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/tool_tip.hpp"

ToolTipManager::~ToolTipManager()
{
    KillTimer(Window, 0x54544950);
    if (Current != 0) {
        // The original dispatches virtually even from the destructor (an inlined helper).
        ((ToolTipManager *)this)->Hide(&Record);
    }
    Index.Clear();
    for (int index = 0; index < Tips.Count(); index++) {
        if (Tips[index] != 0) {
            delete Tips[index];
        }
    }
    Tips.Clear();
}
