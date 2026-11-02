// Deletes every file entry and empties the list (0x0053C010).
#include "shared/map_seed.hpp"
// @ref ??3@YAXPAX@Z=00781d3b

void LoadOptionsClass::Clear_List()
{
    for (int i = 0; i < Files.Count(); ++i) {
        delete Files[i];
    }
    Files.Clear();
}
