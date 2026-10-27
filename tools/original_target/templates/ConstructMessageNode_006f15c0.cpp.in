// Original 0x006f15c0: 91 body bytes plus 5 independently frozen NOP bytes.
// Exact target e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f.
// A13 first real-constructor/member-initializer recipe; concrete class names unknown.
#include "shared/message_gadget_layout.hpp"

extern "C" unsigned char message_node_dispatch_006f15c0[];

#pragma auto_inline(off)
MessageNode_006f15c0::MessageNode_006f15c0(
    const unsigned short* initial_text, int x, int y,
    int color_selector, unsigned int style_flags)
    : GadgetState_004cefe0(x, y, 1, 1, 0, 0),
      expires(0), identifier(0), flags(style_flags), text(initial_text),
      color(color_selector), maximum_width(-1), scroll(0),
      field_0x40(0), field_0x41(0), reveal_count(0), last_tick(0)
{
    // The inherited constructor is the actual same-owner base call at 0x004cefe0.
    // unknown_0x42 alignment bytes remain untouched; insertion supplies style bit15.
    dispatch_table = message_node_dispatch_006f15c0;
}
#pragma auto_inline(on)
