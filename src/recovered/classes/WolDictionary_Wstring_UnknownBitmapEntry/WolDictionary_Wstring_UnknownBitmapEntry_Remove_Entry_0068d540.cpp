// WolDictionary<Wstring, UnknownBitmapEntry>::Remove_Entry (0x0068D540): the image dictionary's template
// member, emitted at the end of this unit for the replacing load of Load_Image_0068c600.
// Layout and behaviour: shared/wol_dictionary.hpp.
#include "shared/pcx_cache.hpp"

template bool WolDictionary<Wstring, UnknownBitmapEntry>::Remove_Entry(Wstring const &key, UnknownBitmapEntry *old_value);
