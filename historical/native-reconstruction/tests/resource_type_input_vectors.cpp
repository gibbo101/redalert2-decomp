// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/ResourceTypeInputs.hpp"
#include <openssl/evp.h>
#include <algorithm>
#include <bit>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
using Words=std::vector<std::uint32_t>;
int signedWord(unsigned v){return std::bit_cast<std::int32_t>(v);}
void text(Words& out,std::string_view s){out.push_back(unsigned(s.size()));for(unsigned char c:s)out.push_back(c);}
std::string decode(std::string s){return s=="-"?"":s;}
std::string digest(const Words& words){
    std::vector<unsigned char> b;for(auto v:words)for(int i=0;i<4;++i)b.push_back(static_cast<unsigned char>(v>>(i*8)));
    unsigned char result[EVP_MAX_MD_SIZE];unsigned n=0;if(!EVP_Digest(b.data(),b.size(),result,&n,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream out;for(unsigned i=0;i<n;++i)out<<std::hex<<std::setfill('0')<<std::setw(2)<<unsigned(result[i]);return out.str();
}
struct Profile {unsigned base=0,mask=0;std::array<unsigned,6> ints{};std::array<unsigned,4> reals{};unsigned length=0;std::string debris;};
Profile profile(std::istream& in){Profile p;in>>p.base>>p.mask;for(auto& v:p.ints)in>>v;for(auto& v:p.reals)in>>v;in>>p.length>>p.debris;p.debris=decode(p.debris);return p;}
ResourceTypeInputs initial(unsigned seed,unsigned h,std::span<const OverlayTypeInputs> overlays){
    ResourceTypeInputs t;const unsigned v=(h+1)*2654435761u+seed*2246822519u;t.id="Existing"+std::to_string(h);
    t.index=signedWord(v);t.spread=signedWord(v^0x12345678u);t.growth=signedWord(v^0x87654321u);
    t.spreadPercentage=std::bit_cast<double>((std::uint64_t(0x3fd00000+h%3)<<32)|v);
    t.growthPercentage=std::bit_cast<double>((std::uint64_t(0xbfe00000+h%3)<<32)|v);
    t.value=signedWord(v+1);t.power=signedWord(v+2);t.color=signedWord(v+3);
    t.debris={h*3+3,4,2,v,v^0xabcdef01u,std::uint8_t(h&1),{h+11,h+22}};
    t.image=&overlays[(h+153)%256];t.numFrames=signedWord(v+4);t.numImages=signedWord(v+5);t.numSlopes=signedWord(v+6);
    for(unsigned i=0;i<14;++i)t.logic[i]=v+i*37;return t;
}
}
int main(int argc,char** argv){try{
    const bool trace=argc==2&&std::string_view(argv[1])=="--trace";
    if(argc!=1&&!trace)throw std::invalid_argument("Usage: resource-type-input-vectors [--trace]");
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;unsigned seed=0;in>>op>>seed;
        std::array<OverlayTypeInputs,256> overlays;for(unsigned i=0;i<overlays.size();++i)overlays[i].index=int(i);
        std::array<ResourceTypeInputs,512> objects;for(unsigned h=0;h<objects.size();++h)objects[h]=initial(seed,h,overlays);
        Words events;std::vector<unsigned> used;const auto event=[&](std::initializer_list<unsigned> v){events.insert(events.end(),v.begin(),v.end());};
        const auto handle=[&](const ResourceTypeInputs* p){return p?unsigned(p-objects.data()):0xffffffffu;};
        const auto vectorEvent=[&](unsigned tag,unsigned h,const ResourceDebrisInputs& v){event({tag,h,v.buffer,v.capacity,v.owns,v.count,v.growth,v.extra,unsigned(v.items.size())});events.insert(events.end(),v.items.begin(),v.items.end());};
        const auto store=[&](auto& t,unsigned off,unsigned n,std::uint64_t v){event({20,handle(&t),off,n,unsigned(v),unsigned(v>>32)});};
        Profile config;unsigned current=0;std::vector<std::string> tokens;unsigned tokenIndex=0;
        ResourceIniServices ini;ini.overlays=overlays;ini.store=store;
        ini.base=[&](auto& t){current=handle(&t);event({10,current,config.base});return std::uint8_t(config.base)!=0;};
        const auto section=[&](std::string_view id){if(id!=objects[current].id)throw std::runtime_error("Resource INI section differs");};
        constexpr std::array<std::string_view,6> keys{"Spread","Growth","Value","Power","Color","Image"};
        const auto integer=[&](std::string_view id,std::string_view key,int def){
            section(id);const auto found=std::find(keys.begin(),keys.end(),key);if(found==keys.end())throw std::runtime_error("Resource INI key differs");
            const unsigned index=unsigned(found-keys.begin()),value=config.mask&(1u<<index)?config.ints[index]:unsigned(def);
            event({11,current});text(events,key);event({unsigned(def),value});return signedWord(value);
        };
        ini.integer=integer;ini.color=[&](auto id,int def){return integer(id,"Color",def);};
        ini.real=[&](auto id,auto key,double def){
            section(id);const unsigned index=key=="SpreadPercentage"?0:1;const auto before=std::bit_cast<std::uint64_t>(def);
            const auto bits=config.mask&(1u<<(6+index))?std::uint64_t(config.reals[index*2])|(std::uint64_t(config.reals[index*2+1])<<32):before;
            event({12,current});text(events,key);event({unsigned(before),unsigned(before>>32),unsigned(bits),unsigned(bits>>32)});return std::bit_cast<double>(bits);
        };
        ini.debrisText=[&](auto id){section(id);event({13,current,config.length});text(events,config.debris);return std::pair{signedWord(config.length),config.debris};};
        ini.beginDebris=[&](){ResourceDebrisInputs v{current*3+1,4,0,3,9,1,{}};vectorEvent(14,current,v);return v;};
        ini.nextDebris=[&](bool first,auto input)->std::optional<std::string>{
            if(first){tokens.clear();tokenIndex=0;std::istringstream parts{std::string(input)};std::string part;while(std::getline(parts,part,','))if(!part.empty())tokens.push_back(part);}
            const bool has=tokenIndex<tokens.size();event({15,current,unsigned(first),unsigned(has)});
            if(!has)return {};auto result=tokens[tokenIndex++];text(events,result);return result;
        };
        ini.resolveDebris=[&](auto token){unsigned value=0;if(token!="MISSING"){for(unsigned char c:token)value+=c;value=value*17+seed;}event({16,current});text(events,token);event({value});return value;};
        ini.appendDebris=[&](auto& v,unsigned item){event({17,current,item});v.items.push_back(item);++v.count;v.capacity=std::max(v.capacity,v.count);};
        ini.copyDebris=[&](const auto& v){vectorEvent(18,current,v);auto copy=v;copy.buffer=v.capacity?current*3+2:0;copy.owns=1;return copy;};
        ini.destroyDebris=[&](auto& v){event({19,current,v.buffer});};
        ini.assignDebris=[&](auto& target,const auto& v){vectorEvent(22,current,v);target.buffer=v.buffer?current*3+3:0;target.capacity=v.capacity;target.owns=1;target.items=v.items;};
        ini.releaseDebris=[&](auto& v){event({23,current,v.buffer});};
        std::array<ResourceTypeRegistry,2> registries;std::array<unsigned,2> success{};
        ResourceConstructionServices construction;construction.currentFrame=seed;construction.store=store;
        construction.base=[&](auto& t,auto id){const auto h=handle(&t);current=h;used.push_back(h);event({0,h});text(events,id);t.id=id;};
        construction.constructDebris=[&](auto& v){event({2,current});v={0,0,0,0,0,1,{}};};
        construction.clearDebris=[&](auto& v){event({3,current});v.count=0;v.items.clear();};
        construction.grow=[&](unsigned role,int amount){event({4,role,unsigned(amount),success[role-1]});if(std::uint8_t(success[role-1]))registries[role-1].slots.resize(unsigned(amount));return signedWord(success[role-1]);};
        construction.registryStore=[&](unsigned role,unsigned slot,unsigned value){event({21,role,slot,slot?handle(registries[role-1].slots[slot-1]):value});};
        unsigned result=0;
        if(op=='I'){
            config=profile(in);current=0;used.push_back(0);result=readResourceTypeIni(objects[0],ini);
        }else if(op=='C'||op=='L'){
            for(unsigned role=0;role<2;++role){
                auto& r=registries[role];unsigned capacity=0,owns=0;in>>capacity>>owns>>r.growth>>success[role]>>r.count;
                if(capacity>512||r.count<0||unsigned(r.count)>capacity||owns>255)throw std::invalid_argument("Resource registry fixture domain");
                r.slots.resize(capacity);r.owns=std::uint8_t(owns);
                for(int i=0;i<r.count;++i){unsigned h=0;in>>h;if(h>=8)throw std::invalid_argument("Resource registry fixture handle");r.slots[unsigned(i)]=&objects[h];used.push_back(h);}
            }
            if(op=='C'){
                unsigned h=0;std::string id;in>>h>>id;if(h>=8)throw std::invalid_argument("Resource constructor fixture handle");current=h;used.push_back(h);
                constructResourceType(objects[h],decode(id),registries[0],registries[1],construction);result=h;
            }else{
                int count=0;in>>count;if(count>400)throw std::invalid_argument("Too many resource entries");
                struct Entry{ResourceListEntry row;int index=0;Profile config;};std::vector<Entry> entries;
                for(int i=0;i<count;++i){Entry e;unsigned index=0,length=0;in>>e.row.key>>index>>length>>e.row.value;e.row.value=decode(e.row.value);e.index=signedWord(index);e.row.length=signedWord(length);e.config=profile(in);entries.push_back(e);}
                unsigned selected=0,attempts=0;ResourceListServices list;list.construction=construction;
                list.entry=[&](int i){selected=unsigned(i);auto& e=entries[selected];config=e.config;event({6,selected});text(events,e.row.key);event({8,selected,unsigned(e.row.length)});text(events,e.row.value);return e.row;};
                list.numericKey=[&](auto key){const auto& e=entries[selected];event({7});text(events,key);event({unsigned(e.index)});return e.index;};
                list.allocate=[&](){const unsigned h=8+attempts++;if(h>=objects.size())throw std::invalid_argument("Too many resource allocations");current=h;used.push_back(h);event({9,h});return &objects[h];};
                list.readIni=[&](auto& t){current=handle(&t);return readResourceTypeIni(t,ini);};
                event({5,unsigned(count)});result=readResourceTypeList(count,registries[0],registries[1],list);
            }
        }else throw std::invalid_argument("Unknown resource command");
        if(!in)throw std::invalid_argument("Incomplete resource command");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing resource command");
        Words state;
        for(const auto& r:registries){state.insert(state.end(),{unsigned(r.count),unsigned(r.slots.size()),r.owns});for(auto* p:r.slots)state.push_back(handle(p));}
        std::sort(used.begin(),used.end());used.erase(std::unique(used.begin(),used.end()),used.end());
        for(unsigned h:used){
            state.push_back(h);const auto& t=objects[h];const auto image=t.image?unsigned(t.image-overlays.data())+1:0;
            const auto add=[&](std::uint64_t v){state.insert(state.end(),{unsigned(v),unsigned(v>>32)});};
            add(unsigned(t.index));add(unsigned(t.spread));add(std::bit_cast<std::uint64_t>(t.spreadPercentage));add(unsigned(t.growth));add(std::bit_cast<std::uint64_t>(t.growthPercentage));
            for(unsigned v:{unsigned(t.value),unsigned(t.power),unsigned(t.color),t.debris.buffer,t.debris.capacity,unsigned(t.debris.owns),t.debris.count,t.debris.growth,t.debris.extra,image,unsigned(t.numFrames),unsigned(t.numImages),unsigned(t.numSlopes)})add(v);
            for(auto v:t.logic)add(v);text(state,t.id);state.push_back(unsigned(t.debris.items.size()));state.insert(state.end(),t.debris.items.begin(),t.debris.items.end());
        }
        if(trace){std::cerr<<"STATE";for(auto v:state)std::cerr<<' '<<v;std::cerr<<"\nEVENTS";for(auto v:events)std::cerr<<' '<<v;std::cerr<<'\n';}
        std::cout<<result<<' '<<digest(state)<<' '<<digest(events)<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
