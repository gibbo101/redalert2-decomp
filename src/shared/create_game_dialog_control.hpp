// CreateGameDialogControl (RTTI COL 0x007C6490, vtable 0x007AF94C): the WOL create game dialog's control.
#ifndef RA2_SHARED_CREATE_GAME_DIALOG_CONTROL_HPP
#define RA2_SHARED_CREATE_GAME_DIALOG_CONTROL_HPP
#include "shared/wonline_string_dialog_control.hpp"
class CreateGameDialogControl : public WonlineStringDialogControl {
public:
    CreateGameDialogControl(bool unknown_12_value,bool unknown_13_value)
        : unknown_10(false),unknown_11(false),unknown_12(unknown_12_value),unknown_13(unknown_13_value) {}
    virtual ~CreateGameDialogControl() {}
    bool unknown_10,unknown_11,unknown_12,unknown_13;
};
#endif
