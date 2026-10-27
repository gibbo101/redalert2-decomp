#include "shared/word_sequence_views.hpp"

// Original VA 0x006742a0, target e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f.
// Return the first equal 32-bit word's index, or -1 for signed-count exhaustion.
// The count is at +0x10. Preserve signed tests and reference argument semantics;
// original scan inputs can reside in registers. Class/element roles unknown.
class Loop_6742a0 {
    WordSequenceCountAt16View32 view;

public:
    int FindFirstWordIndex_006742a0(const unsigned int& sought_word) const;
};

int Loop_6742a0::FindFirstWordIndex_006742a0(const unsigned int& sought_word) const
{
    for (int index = 0; index < view.count; ++index) {
        if (view.items[index] == sought_word) {
            return index;
        }
    }
    return -1;
}
