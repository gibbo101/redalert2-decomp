// void WolDictionary<unsigned int, OwnerDraw::UnknownControlRecord>::Shrink_Table() (0x006027E0): the
// control registry 0x00A73640 (nodes of 0x208 bytes; called from 0x00601C50, 0x005EC360 and 0x005F8740).
// The out-of-line shrink() (wlib Dictionary::shrink) of one of ownrdraw.cpp's dictionaries. Written as an
// explicit specialization that forwards to the template's inline body (Shrink_Buckets, the body the registry's
// atexit destructor 0x005DEE00 expands; RA2_WOL_DICTIONARY_SHRINK_ACCESSORS): its out-of-line callers
// (0x00601C50 and two window procedures, unrecovered) are what emit the implicit instance in the original;
// when they land, drop this specialization and let the template instantiate.
#include "shared/wol_dictionary.hpp"
#include "shared/owner_draw_dialog_control.hpp"

template<> void WolDictionary<unsigned int, OwnerDraw::UnknownControlRecord>::Shrink_Table()
{
    Shrink_Buckets();
}
