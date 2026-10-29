// WWMessageBox, the main-screen message box object (0x005B46B0; the dialog code is
// in shared/ms_message_box.hpp). Its own header so that units without the dialog
// headers' statics (Queue.CPP) can show a message box.
#ifndef RA2_SHARED_WW_MESSAGE_BOX_HPP
#define RA2_SHARED_WW_MESSAGE_BOX_HPP

// The message box object holds only its caption (Do_Lose builds it as a temporary with
// L" "); Process ignores this (YR's WWMessageBox, name hypothesis).
class WWMessageBox {
public:
    WWMessageBox(unsigned short const *caption) : Caption(caption) {}
    int Process(unsigned short const *text, unsigned short const *button1,
                unsigned short const *button2, unsigned short const *button3, bool unknown5);  // 0x005B46B0
    unsigned short const *Caption;
};

#endif
