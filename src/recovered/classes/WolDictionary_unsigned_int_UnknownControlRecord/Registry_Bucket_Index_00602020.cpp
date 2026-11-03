// Registry dictionary bucket index00602020: unsigned HWND-value keys, records atA73640.
// Direct member specialization, as the neighboring HWND/WNDPROC copy00601C30.
#include "shared/wol_dictionary.hpp"
#include "shared/owner_draw_dialog_control.hpp"
template<> unsigned int WolDictionary<unsigned int,OwnerDraw::UnknownControlRecord>::Key_Hash(unsigned int const &key) const
{
    unsigned int hash=Hash(key);
    return ((1u<<Bits)-1)&hash;
}
