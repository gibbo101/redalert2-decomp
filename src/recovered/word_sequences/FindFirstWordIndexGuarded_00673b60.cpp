#include "shared/word_sequence_views.hpp"

// Original VA 0x00673b60, target e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f.
// If the raw search gate is zero, return zero (not the exhausted-search -1).
// Otherwise return the first equal 32-bit word's index, or -1 when exhausted.
// Preserve signed count tests and the reference-valued search argument; original
// code holds scan inputs in registers after the gate/count checks. The argument
// can alias sequence storage. Concrete class and gate meaning remain unknown.
class Loop_673b60 {
    GuardedWordSequenceView32 view;

public:
    int FindFirstWordIndexGuarded_00673b60(const unsigned int& sought_word) const;
};

int Loop_673b60::FindFirstWordIndexGuarded_00673b60(const unsigned int& sought_word) const
{
    if (!view.search_gate) {
        return 0;
    }
    for (int index = 0; index < view.count; ++index) {
        if (view.items[index] == sought_word) {
            return index;
        }
    }
    return -1;
}
