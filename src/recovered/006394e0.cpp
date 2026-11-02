// rc_ptr_base::rc_ptr_base() (0x006394E0): a null pointer.
// The rc_ptr/readline unit 0x006394E0-0x0063976F: rc_ptr_base members, Tiberian Sun readline.cpp, then
// ReferenceCounted (its scalar deleting destructor 0x00639750 is emitted with the vtable). The rc_ptr_base copy
// constructor is declared for this unit only (RA2_RC_PTR_UNIT).
#define RA2_RC_PTR_UNIT
#include "shared/reference_counted.hpp"
// @ref ??_7rc_ptr_base@@6B@=007a8d0c

rc_ptr_base::rc_ptr_base() : Pointer(0)
{
}
