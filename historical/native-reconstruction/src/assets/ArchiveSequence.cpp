// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/ArchiveSequence.hpp"
#include <array>
#include <cstdio>
#include <stdexcept>

namespace ra2 {
ArchiveRequests startupMixRequests(bool enumerate, unsigned mediaIndex,
    const std::vector<std::string>& maps, const std::vector<std::string>& movies,
    const std::function<bool(const std::string&)>& exists) {
    if(mediaIndex>1) throw std::runtime_error("Only base RA2 media indexes 0/1 are verified");
    ArchiveRequests result;
    auto request=[&](const std::string& name){if(!exists(name)) return false;result.names.push_back(name);return true;};
    if(!request("conquer.mix")||!request("cameo.mix")) return result;
    auto family=[&](const char* format,const std::vector<std::string>& names){
        if(enumerate) {for(const auto& name:names) result.names.push_back(name);return !names.empty();}
        char name[32];std::snprintf(name,sizeof(name),format,mediaIndex+1);return request(name);
    };
    if(!family("maps%02u.mix",maps)||!request("multi.mix")) return result;
    request("theme.mix");
    result.success=family("movies%02u.mix",movies);
    return result;
}
std::vector<std::string> theaterMixRequests(unsigned theater,int previousTheater) {
    if(theater>2 || previousTheater < -1 || previousTheater>2)
        throw std::runtime_error("Only base temperate/snow/urban archive requests are verified");
    std::vector<std::string> names;
    if(theater!=1 && (previousTheater==1 || previousTheater==-1)) names.emplace_back("generic.mix");
    if(int(theater)==previousTheater) return names;
    constexpr std::array<const char*,3> main{"temperat.mix","snow.mix","urban.mix"};
    constexpr std::array<const char*,3> iso{"isotemp.mix","isosnow.mix","isourb.mix"};
    constexpr std::array<const char*,3> suffix{"tem.mix","sno.mix","urb.mix"};
    for(const char* name:{main[theater],suffix[theater],iso[theater],"isogen.mix"}) names.emplace_back(name);
    return names;
}
}
