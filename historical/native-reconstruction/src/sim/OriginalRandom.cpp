// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/OriginalRandom.hpp"
#include <stdexcept>
namespace ra2 {
std::uint32_t nextOriginalRandom(OriginalRandomState& state){
    if(state.disabled)return 0;
    if(state.next1<0||state.next1>=250||state.next2<0||state.next2>=250)
        throw std::invalid_argument("Original random indices outside supported state");
    auto& word=state.table[std::size_t(state.next1)];word^=state.table[std::size_t(state.next2)];const auto result=word;
    ++state.next1;++state.next2;
    if(state.next1>=250)state.next1=0;
    if(state.next2>=250)state.next2=0;
    return result;
}
}
