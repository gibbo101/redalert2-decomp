// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/InfantrySubcellData.hpp"
#include "assets/PreparedData.hpp"
namespace ra2 {
InfantrySubcellData readInfantrySubcellData(const Data& data,std::string_view expectedSource){
    validatePreparedData(data,76,"","c07781069e8a5cf104401f698288c28e276e7fe3711af70b4ffb35396446dd67",expectedSource);
    InfantrySubcellData result;std::size_t p=40;
    for(auto& row:result.orders)for(auto& v:row)v=data.u8(p++);
    return result;
}
}
