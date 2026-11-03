// WOnline's owner-draw dialog controls (RTTI: SimpleWonlineDialogControl, vtable 0x007AF6F4,
// and WonlineStringDialogControl, vtable 0x007AF934, both OwnerDraw::SimpleDialogControl).
#ifndef RA2_SHARED_WONLINE_DIALOG_CONTROL_HPP
#define RA2_SHARED_WONLINE_DIALOG_CONTROL_HPP

#include "shared/owner_draw_dialog_control.hpp"

class SimpleWonlineDialogControl : public OwnerDraw::SimpleDialogControl {
public:
#ifdef RA2_SIMPLE_WONLINE_CTOR_INLINE
    SimpleWonlineDialogControl() {}
#else
    SimpleWonlineDialogControl();               // 0x0073C000
#endif
    virtual ~SimpleWonlineDialogControl();      // 0x0073C020 (scalar deleting destructor 0x0075D0A0)
    virtual bool unknown_slot4();               // 0x0073C030
};

#endif
