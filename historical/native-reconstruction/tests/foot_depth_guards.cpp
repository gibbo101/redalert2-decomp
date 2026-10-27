// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/FootDepth.hpp"
#include <stdexcept>
int main(){
    ra2::FootDepthWorld w;ra2::FootDepthCell neighbor;
    w.coordinates=[]{return ra2::UnitLightCell{};};
    w.cell=[&](ra2::UnitLightCell p)->const ra2::FootDepthCell*{return p==ra2::UnitLightCell{}?nullptr:&neighbor;};
    w.cellPredicate=[](const auto&){return false;};
    try{ra2::footDepthPredicate1(w);return 1;}catch(const std::invalid_argument&){}
    try{ra2::footDepthPredicate2(w);return 2;}catch(const std::invalid_argument&){}
    return 0;
}
