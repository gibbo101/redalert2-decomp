// WonlineStringDialogControl: original RTTI/vtable 0x007AF934.
// Its constructor 0x00765AA0 builds the SimpleWonline base and owned Text at+C.
#ifndef RA2_SHARED_WONLINE_STRING_DIALOG_CONTROL_HPP
#define RA2_SHARED_WONLINE_STRING_DIALOG_CONTROL_HPP
#include "shared/wonline_dialog_control.hpp"
#include "shared/wstring.hpp"
class WonlineStringDialogControl : public SimpleWonlineDialogControl {
public:
#ifdef RA2_WONLINE_STRING_CTOR_SOURCE
    WonlineStringDialogControl();
#else
    WonlineStringDialogControl() {}
#endif
    virtual ~WonlineStringDialogControl() {}
    Wstring Text;
};
#endif
