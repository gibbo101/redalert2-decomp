// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OverlayTypeInputs.hpp"
#include <openssl/evp.h>
#include <algorithm>
#include <array>
#include <bit>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace ra2;
namespace {
using Words=std::vector<std::uint32_t>;
std::string digest(const Words& words){
    std::vector<unsigned char> bytes;for(auto v:words)for(int i=0;i<4;++i)bytes.push_back(static_cast<unsigned char>(v>>(i*8)));
    unsigned char result[EVP_MAX_MD_SIZE];unsigned size=0;
    if(!EVP_Digest(bytes.data(),bytes.size(),result,&size,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream out;for(unsigned i=0;i<size;++i)out<<std::hex<<std::setfill('0')<<std::setw(2)<<unsigned(result[i]);return out.str();
}
void string(Words& words,std::string_view s){words.push_back(unsigned(s.size()));for(unsigned char c:s)words.push_back(c);}
std::string decode(std::string s){return s=="-"?"":s;}
std::string folded(std::string_view s){std::string out(s);for(char& c:out)if(c>='A'&&c<='Z')c=char(c-'A'+'a');return out;}
// Synthetic base and initial fields; these are not original default values.
OverlayTypeInputs initial(unsigned seed,unsigned handle){
    OverlayTypeInputs t;const unsigned v=(handle+1)*2654435761u+seed*2246822519u;
    t.id="Existing"+std::to_string(handle);t.imageName="Art"+std::to_string(handle);
    t.index=std::bit_cast<std::int32_t>(v);t.land=std::bit_cast<std::int32_t>(v^0x12345678u);
    t.cellAnim=v^0x87654321u;t.damageLevels=std::bit_cast<std::int32_t>(v+1);t.strength=std::bit_cast<std::int32_t>(v+2);
    t.armor=std::bit_cast<std::int32_t>(v+3);t.image=v+4;
    unsigned i=0;for(auto* f:{&t.theater,&t.crushable,&t.radarInvisible,&t.selectable,&t.insignificant,&t.flag205,
        &t.wall,&t.tiberium,&t.crate,&t.crateTrigger,&t.noUseTileLandType,&t.veinhole,&t.veins,&t.demandLoad,
        &t.explodes,&t.chainReaction,&t.overrides,&t.drawFlat,&t.rubble,&t.rock})*f=std::uint8_t(v+(i++)*37);
    return t;
}
Words projection(const OverlayTypeInputs& t){return {unsigned(t.index),unsigned(t.land),t.cellAnim,unsigned(t.damageLevels),unsigned(t.strength),
    unsigned(t.armor),t.image,t.theater,t.crushable,t.radarInvisible,t.selectable,t.insignificant,t.flag205,
    t.wall,t.tiberium,t.crate,t.crateTrigger,t.noUseTileLandType,t.veinhole,t.veins,t.demandLoad,t.explodes,
    t.chainReaction,t.overrides,t.drawFlat,t.rubble,t.rock};}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;unsigned seed=0;in>>op>>seed;
        std::array<OverlayTypeInputs,512> objects;for(unsigned i=0;i<objects.size();++i)objects[i]=initial(seed,i);
        Words events;std::vector<unsigned> used;
        const auto handle=[&](const OverlayTypeInputs* t){if(!t)return 0xffffffffu;return unsigned(t-objects.data());};
        const auto event=[&](std::initializer_list<unsigned> v){events.insert(events.end(),v.begin(),v.end());};
        const auto store=[&](OverlayTypeInputs& t,unsigned off,unsigned n,unsigned value){event({20,handle(&t),off,n,value});};
        unsigned result=0;OverlayTypeRegistry r;
        if(op=='I'){
            int base=0;unsigned mask=0,animation=0,image=0;std::array<unsigned,3> integers{};std::array<unsigned,14> flags{};
            unsigned theater=0,crushable=0;int length=0;std::string text;
            in>>base>>mask>>theater>>crushable;for(auto& v:integers)in>>v;for(auto& v:flags)in>>v;
            in>>length>>text>>animation>>image;text=decode(text);
            auto& t=objects[0];t.theater=std::uint8_t(theater);t.crushable=std::uint8_t(crushable);used.push_back(0);
            OverlayIniServices s;
            s.store=[&](auto off,auto n,auto v){store(t,off,n,v);};
            s.base=[&](auto&){event({10,0,unsigned(base)});return std::uint8_t(base)!=0;};
            s.integer=[&](bool art,auto section,auto key,int def){
                if(section!=(art?t.imageName:t.id))throw std::runtime_error("INI section mismatch");
                const int index=key=="Land"?0:key=="Strength"?1:2;
                const unsigned value=(mask&(1u<<index))?integers[std::size_t(index)]:unsigned(def);
                event({11,unsigned(art)});string(events,key);event({unsigned(def),value});return std::bit_cast<std::int32_t>(value);
            };
            constexpr std::array<const char*,14> keys{"Wall","Tiberium","Crate","CrateTrigger","Explodes","Overrides","DemandLoad",
                "NoUseTileLandType","IsVeinholeMonster","IsVeins","ChainReaction","DrawFlat","IsARock","IsRubble"};
            s.boolean=[&](bool art,auto section,auto key,std::uint8_t def){
                if(section!=(art?t.imageName:t.id))throw std::runtime_error("INI section mismatch");
                const auto found=std::find(keys.begin(),keys.end(),key);if(found==keys.end())throw std::runtime_error("INI key mismatch");
                const unsigned index=unsigned(found-keys.begin()),value=(mask&(1u<<(index+3)))?flags[index]:def;
                event({12,unsigned(art)});string(events,key);event({def,value});return std::bit_cast<std::int32_t>(value);
            };
            s.cellAnimation=[&](auto section){if(section!=t.id)throw std::runtime_error("Animation section mismatch");event({13,unsigned(length)});string(events,text);return std::pair{length,text};};
            s.resolveAnimation=[&](auto name){event({14});string(events,name);event({animation});return animation;};
            s.loadImage=[&](auto name){event({16});string(events,name);event({image});return image;};
            result=readOverlayTypeIni(t,s);
        }else if(op=='C'||op=='L'){
            unsigned capacity=0,owns=0;int success=0,fail=-1;in>>capacity>>owns>>r.growth>>success>>fail>>r.count;
            if(capacity>512||r.count<0||unsigned(r.count)>capacity)throw std::invalid_argument("Registry fixture too large");
            r.owns=std::uint8_t(owns);r.slots.resize(capacity);
            for(int i=0;i<r.count;++i){unsigned h=0;in>>h;if(h>=8)throw std::invalid_argument("Initial handle too large");r.slots[std::size_t(i)]=&objects[h];if(std::find(used.begin(),used.end(),h)==used.end())used.push_back(h);}
            unsigned attempts=0;OverlayConstructionServices s;
            s.base=[&](auto& t,auto id){event({0,handle(&t)});string(events,id);t.id=id;t.imageName=std::string(id).substr(0,24);};
            s.store=store;
            s.registryStore=[&](unsigned tag,unsigned v){event({21,tag,v});if(tag==1)event({handle(r.slots[v])});};
            s.grow=[&](int n){event({2,unsigned(n),unsigned(success)});if(std::uint8_t(success))r.slots.resize(std::size_t(n));return std::uint8_t(success)!=0;};
            s.equal=[&](auto a,auto b){const bool equal=folded(a)==folded(b);event({3});string(events,a);string(events,b);event({unsigned(equal)});return equal;};
            s.allocate=[&](){const unsigned h=8+attempts;const bool ok=int(attempts++)!=fail;event({1,0x288,ok?h:0xffffffffu});if(!ok)return static_cast<OverlayTypeInputs*>(nullptr);if(h>=objects.size())throw std::invalid_argument("Too many overlay allocations");used.push_back(h);return &objects[h];};
            if(op=='C'){
                unsigned h=0;std::string id;in>>h>>id;if(h>=8)throw std::invalid_argument("Constructor handle too large");
                if(std::find(used.begin(),used.end(),h)==used.end())used.push_back(h);
                constructOverlayType(objects[h],decode(id),r,s);result=h;
            }else{
                int count=0;in>>count;if(count>400)throw std::invalid_argument("Overlay list too large");
                event({4,unsigned(count)});
                result=readOverlayTypeList(count,[&](int index){int length=0;std::string text;in>>length>>text;text=decode(text);event({5,unsigned(index),unsigned(length)});string(events,text);return std::pair{length,text};},r,s);
            }
        }else throw std::invalid_argument("Unknown overlay type command");
        if(!in)throw std::invalid_argument("Incomplete overlay type command");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing overlay type command");
        std::sort(used.begin(),used.end());Words state{unsigned(r.count),unsigned(r.slots.size())};
        for(auto* t:r.slots)state.push_back(handle(t));
        for(unsigned h:used){state.push_back(h);auto row=projection(objects[h]);state.insert(state.end(),row.begin(),row.end());string(state,objects[h].id);string(state,objects[h].imageName);}
        std::cout<<result<<' '<<digest(state)<<' '<<digest(events)<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
