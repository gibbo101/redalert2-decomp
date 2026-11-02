// Native dictionary bucket index;29 complete body bytes +3 padding.
#include "shared/win32_api.hpp"
#include "shared/wol_dictionary.hpp"
#include "shared/owner_draw_dialog_control.hpp"
template<> unsigned int WolDictionary<HWND, WNDPROC>::Key_Hash(HWND const &key) const
{
    unsigned int hash = Hash(key);
    return ((1u << Bits) - 1) & hash;
}
