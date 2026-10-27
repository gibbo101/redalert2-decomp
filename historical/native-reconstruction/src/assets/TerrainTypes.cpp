// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/TerrainTypes.hpp"
#include <array>
#include <stdexcept>
namespace ra2 {
const std::vector<std::string>& stockStaticPropTypes() {
    static const std::vector<std::string> types{"hdstn01","lt_gen01","lt_gen02","lt_gen03","lt_gen04",
        "lt_sgn01","lt_sgn02","lt_sgn03","lt_sgn04","lt_eur01","lt_eur02","pole01","pole02",
        "sign01","sign02","sign03","sign04","sign05","sign06","trff01","trff02","trff03","trff04"};
    return types;
}
int terrainStrengthDefault(int current,int rulesTreeStrength) {
    return current==-1?rulesTreeStrength:current;
}
std::optional<TerrainImageReload> terrainImageReload(const std::string& id,bool theaterImage,
    bool ownsImage,std::uint32_t image,bool force,int requested,int previous) {
    if(requested<0||requested>2)throw std::invalid_argument("Unsupported base terrain theater");
    if((!force&&requested==previous)||!theaterImage)return {};
    if(id.empty()||id.size()>24||id.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_")!=std::string::npos)
        throw std::invalid_argument("Terrain identifier outside bounded profile");
    static constexpr std::array<const char*,3> extensions{"TEM","SNO","URB"};
    // Original _makepath, null drive/directory, ID and theater extension.
    return TerrainImageReload{id+"."+extensions[std::size_t(requested)],ownsImage&&image!=0};
}
}
