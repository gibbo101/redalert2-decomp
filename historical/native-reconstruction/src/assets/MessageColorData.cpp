// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MessageColorData.hpp"
#include "assets/PreparedData.hpp"
#include <bit>
namespace ra2 {
MessageColorTable readMessageColorData(const Data& data,std::string_view expectedSource){
    validatePreparedData(data,49,"","d9c06c89ff6070c9e2eb18773503b1a43a12bc69a90e140530c30706780c8272",expectedSource);
    MessageColorTable out;
    for(std::size_t i=0;i<out.size();++i)out[i]=std::bit_cast<std::int8_t>(data.u8(40+i));
    return out;
}
}
