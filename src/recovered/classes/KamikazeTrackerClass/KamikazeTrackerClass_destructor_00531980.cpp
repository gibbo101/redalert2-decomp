// KamikazeTrackerClass::~KamikazeTrackerClass() (0x00531980)
#include "shared/kamikaze_tracker.hpp"

KamikazeTrackerClass::~KamikazeTrackerClass()
{
    for (int index = Nodes.Count() - 1; index >= 0; index--) {
        delete Nodes[index];
    }
    DynamicVectorClass<KamikazeControl *> &nodes = Nodes;
    int length = nodes.Length();
    nodes.Clear();
    nodes.Resize(length);
}
