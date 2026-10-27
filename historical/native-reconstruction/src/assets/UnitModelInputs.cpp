// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/UnitModelInputs.hpp"
#include <algorithm>
#include <stdexcept>
namespace ra2 {
std::size_t readIniStringBuffer(std::span<std::uint8_t> output,int capacity,
    std::optional<std::string_view> value,std::optional<std::string_view> fallback,bool names) {
    if(capacity<2 || !names || !output.data())return 0;
    if(std::size_t(capacity)>output.size())throw std::invalid_argument("INI string capacity exceeds supplied storage");
    const auto out=output.first(std::size_t(capacity));
    const auto source=value?value:fallback;
    if(!source){out[0]=0;return 0;}
    const auto length=std::min(source->find('\0'),source->size());
    for(std::size_t i=0;i<out.size();++i)out[i]=i<length?std::uint8_t((*source)[i]):0;
    out.back()=0;
    // Original byte trim uses <=32, then retains its original first-nonblank
    // pointer as a live trailing-loop guard after moving the string down.
    std::size_t first=0;
    while(out[first] && out[first]<=32)++first;
    auto end=first;while(out[end])++end;
    if(first)for(std::size_t i=0;i<=end-first;++i)out[i]=out[first+i];
    end=0;while(out[end])++end;
    for(std::size_t i=end;i>0 && out[first] && out[i-1]<=32;--i)out[i-1]=0;
    end=0;while(out[end])++end;return end;
}
UnitModelInputs initializeUnitModelInputs(const ModelImageName& typeId) {
    return {typeId,0,0};
}
std::string modelImageString(const ModelImageName& image) {
    const auto end=std::find(image.begin(),image.end(),std::uint8_t(0));
    if(end==image.end())throw std::invalid_argument("Model image must be terminated within 25 bytes");
    return {image.begin(),end};
}
UnitModelInputs updateUnitModelInputs(UnitModelInputs t,const std::string& typeId,const UnitModelInputServices& s) {
    // The original copies the fallback to separate stack storage before ReadString.
    const auto fallback=t.image;s.image(typeId,fallback,t.image);
    t.turretCount=s.rulesInteger(typeId,"TurretCount",t.turretCount);
    t.turretOffset=s.artInteger(modelImageString(t.image),"TurretOffset",t.turretOffset);
    return t;
}
UnitModelInputs readUnitModelInputs(const Ini& rules,const Ini& art,const std::string& id) {
    if(id.empty() || id.size()>24 || id.find('\0')!=std::string::npos)
        throw std::invalid_argument("Unit type ID must contain one through 24 bytes");
    ModelImageName name{};std::copy(id.begin(),id.end(),name.begin());
    UnitModelInputServices s;
    s.image=[&](std::string_view section,const ModelImageName& fallback,ModelImageName& out){
        const auto& entries=rules.section(std::string(section));const auto it=entries.find("image");
        readIniStringBuffer(out,25,it==entries.end()?std::nullopt:std::optional<std::string_view>(it->second),
                            modelImageString(fallback));};
    s.rulesInteger=[&](std::string_view section,std::string_view key,int d){return rules.integer(std::string(section),std::string(key),d);};
    s.artInteger=[&](std::string_view section,std::string_view key,int d){return art.integer(std::string(section),std::string(key),d);};
    return updateUnitModelInputs(initializeUnitModelInputs(name),id,s);
}
void requireOrdinaryRhinoModelInputs(const UnitModelInputs& t) {
    if(lower(modelImageString(t.image))!="htnk" || t.turretCount!=0 || t.turretOffset!=0)
        throw std::runtime_error("Only stock HTNK image, zero TurretCount and zero TurretOffset are supported");
}
}
