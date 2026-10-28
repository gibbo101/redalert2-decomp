// void KamikazeTrackerClass::Clear() (0x005319E0)
#include "shared/kamikaze_tracker.hpp"

void KamikazeTrackerClass::Clear()
{
    for (int index = Nodes.Count() - 1; index >= 0; index--) {
        delete Nodes[index];
    }
    DynamicVectorClass<KamikazeControl *> &nodes = Nodes;
    int length = nodes.Length();
    nodes.Clear();
    nodes.Resize(length);
    Timer = 1;
}
