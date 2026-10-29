// Releases each owned file entry, clears the list and destroys its vector storage.
// Original0053B130,96body/no outerpadding; no direct free of this.
#include "shared/map_seed.hpp"
// @ref ??_7LoadOptionsClass@@6B@=007a581c
// @ref ??_7?$VectorClass@PAVFileEntryClass@@@@6B@=007a5864
// @ref ??3@YAXPAX@Z=00781d3b

LoadOptionsClass::~LoadOptionsClass()
{
    for (int i = 0; i < Files.Count(); ++i) {
        delete Files[i];
    }
    Files.Clear();
}
