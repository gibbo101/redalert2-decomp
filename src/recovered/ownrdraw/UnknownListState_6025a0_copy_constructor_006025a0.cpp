// UnknownListState_6025a0::UnknownListState_6025a0(UnknownListState_6025a0 const &) (0x006025A0): copies two
// words and the 24-byte element list through wlib's ArrayList copy constructor (empty list, then operator=:
// clear, then get/add each element through a default-constructed temporary). Struct and field names are
// hypotheses; no other user of this layout is known yet.
// @ref ?Grow_Vector@?$WolArrayList@UUnknownListEntry_6017c0@@@@QAE_NXZ=006017c0
#include "shared/wide_string.hpp"
#include "shared/wol_array_list.hpp"

struct UnknownListState_6025a0 {
    int unknown_00;
    int unknown_04;
    WolArrayList<UnknownListEntry_6017c0> List;
    UnknownListState_6025a0(UnknownListState_6025a0 const &other);
};

UnknownListState_6025a0::UnknownListState_6025a0(UnknownListState_6025a0 const &other)
    : unknown_00(other.unknown_00), unknown_04(other.unknown_04), List(other.List)
{
}
