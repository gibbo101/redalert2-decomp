#pragma once
#include "shared/link_prefix_layout.hpp"

// Observed base gadget and message-node layouts; original C++ names remain unknown.
// Constructors, admission, focus and nonzero-argument dispatch have accepted source.
// Draw/flag-refresh declarations retain inspected interfaces; their bodies remain
// unrecovered. This header does not claim complete class recovery.
// The message constructor directly calls 0x004cefe0 with this same base receiver.
// Link pointers name the inspected prefix without claiming a new inheritance chain.
// Explicit dispatch words retain the original tables; no C++ virtual methods added.
class GadgetState_004cefe0 {
protected:
    unsigned char* dispatch_table;
    LinkPrefix_00539040* next;
    LinkPrefix_00539040* previous;
    int x;
    int y;
    int width;
    int height;
    unsigned char dirty;
    unsigned char sticky;
    unsigned char unknown_0x1e;
    unsigned char unknown_0x1f;
    unsigned int gadget_flags;
public:
    GadgetState_004cefe0(int initial_x, int initial_y, int initial_width,
        int initial_height, unsigned int flags, unsigned char sticky_byte);
    int AdmitDirtyOrForcedDraw_004cf240(unsigned int force);
    int ClearFlagAndRefresh_004cf140();
    int SetFlagAndRefresh_004cf150();
    int DispatchNonzeroArgument_004cf220(unsigned int argument, unsigned int unused);
};
typedef char GadgetState_004cefe0_size_check[(sizeof(GadgetState_004cefe0) == 0x24) ? 1 : -1];

class MessageNode_006f15c0 : private GadgetState_004cefe0 {
    unsigned int expires;
    unsigned int identifier;
    unsigned int flags;
    const unsigned short* text; // 0x30: actual original UTF16 pointer, not native slot index.
    int color;
    int maximum_width;
    unsigned int scroll;
    unsigned char field_0x40;
    unsigned char field_0x41;
    unsigned char unknown_0x42[2];
    unsigned int reveal_count;
    unsigned int last_tick;
public:
    MessageNode_006f15c0(const unsigned short* initial_text, int x, int y,
        int color_selector, unsigned int style_flags);
    bool IsFocusedMessageNode_004cf630() const;
    int DrawMessageNode_006f1620(unsigned int force);
};
typedef char MessageNode_006f15c0_size_check[(sizeof(MessageNode_006f15c0) == 0x4c) ? 1 : -1];
