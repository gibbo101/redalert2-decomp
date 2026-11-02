#pragma once
#include "shared/link_prefix_layout.hpp"

// Observed base gadget layout; original C++ names remain unknown (the message node is
// TextLabelClass, shared/text_label.hpp).
// Constructors, admission, focus and nonzero-argument dispatch have accepted source.
// Draw/flag-refresh declarations retain inspected interfaces; their bodies remain
// unrecovered. This header does not claim complete class recovery.
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

