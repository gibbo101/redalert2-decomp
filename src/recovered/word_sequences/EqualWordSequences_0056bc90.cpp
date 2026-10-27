#include "shared/word_sequence_views.hpp"

// Original VA 0x0056bc90, target e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f.
// Compare signed counts, then corresponding 32-bit words in original load order.
// Equal nonpositive counts succeed without element reads. The accepted member
// expression pattern is retained; this does not imply per-iteration reloads.
// No snapshot, memcmp or new alias assumption is introduced.
// Concrete class, element meanings and original developer names remain unknown.
class Loop_56bc90 {
    CountedWordSequenceView32 view;

public:
    bool EqualWordSequences_0056bc90(const Loop_56bc90& other) const;
};

bool Loop_56bc90::EqualWordSequences_0056bc90(const Loop_56bc90& other) const
{
    if (view.count == other.view.count) {
        for (int index = 0; index < view.count; ++index) {
            if (view.items[index] != other.view.items[index]) {
                return false;
            }
        }
        return true;
    }
    return false;
}
