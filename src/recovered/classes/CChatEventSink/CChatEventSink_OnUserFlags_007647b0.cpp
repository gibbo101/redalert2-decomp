// HRESULT __stdcall CChatEventSink::OnUserFlags(HRESULT result, char const *name, unsigned int flags, unsigned int mask) (0x007647B0, slot 30)
// Updates the flags of the named user in the user list (keeping the bits in mask, adding flags),
// re-sorting the entry, then refreshes the user list display.
#include "shared/wol_sink.hpp"
// @ref ?unknown_users_b2a728@@3VWolUserArray@@A=00b2a728
// @ref ?Compare_Users_007416d0@@YIHABUUser@WOL@@0@Z=007416d0
// @ref ?Shrink_00766f00@WolUserArray@@QAE_NXZ=00766f00
// @ref Unknown_0073FEE0=0073fee0

HRESULT __stdcall CChatEventSink::OnUserFlags(HRESULT result, char const *name, unsigned int flags, unsigned int mask)
{
    if (result == 0) {
        for (int i = 0; i < unknown_users_b2a728.Count; ++i) {
            WOL::User user;
            if (unknown_users_b2a728.Get_Copy(user, i) && !_stricmp(user.name, name)) {
                user.flags = (user.flags & mask) | flags;
                unknown_users_b2a728.Remove(i);
                unknown_users_b2a728.Add_Sorted(user);
            }
        }
        Unknown_0073FEE0(0, false);
    }
    return S_OK;
}
