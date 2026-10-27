#include "shared/word_sequence_views.hpp"

// Original VA 0x0042ae90, target e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f.
// Return the unsigned wrapped address-minus-base shifted right by 1 when
// the raw gate byte is nonzero; otherwise return zero. No alignment/bounds check.
// Concrete class, gate purpose and address-space identity remain unknown.
class WordOffset_42ae90 {
    GuardedAddressOffsetView32 view;

public:
    unsigned int GetGuardedScaledOffset_0042ae90(unsigned int address_word) const;
};

unsigned int WordOffset_42ae90::GetGuardedScaledOffset_0042ae90(unsigned int address_word) const
{
    if (!view.offset_gate) {
        return 0;
    }
    return (address_word - view.base_address_word) >> 1;
}
