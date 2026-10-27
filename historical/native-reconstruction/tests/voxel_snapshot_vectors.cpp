// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/VoxelSnapshot.hpp"
#include "render/VoxelPartStaging.hpp"
#include "assets/Archive.hpp"
#include <openssl/evp.h>
#include <bit>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
template<class... T>void out(T... v){((std::cout<<v<<' '),...);}
std::string digest(const Bytes& b){unsigned char h[EVP_MAX_MD_SIZE];unsigned n=0;if(!EVP_Digest(b.data(),b.size(),h,&n,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(h[i]);return s.str();}
std::string hex(const Bytes& b){std::ostringstream s;for(auto v:b)s<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(v);return b.empty()?"-":s.str();}
Bytes unhex(const std::string& s){if(s.size()%2)throw std::invalid_argument("Invalid hex row");Bytes b;for(std::size_t i=0;i<s.size();i+=2)b.push_back(std::uint8_t(std::stoul(s.substr(i,2),nullptr,16)));return b;}
Bytes pixels(unsigned seed,int mode,int w,int h){Bytes b(std::size_t(w)*h);for(unsigned i=0;i<b.size();++i){unsigned v=0;
    if(mode==0)v=(i*37+seed*19)%255+1;
    else if(mode==2)v=(i%unsigned(w)<unsigned(std::min(w,7))||int(i%unsigned(w))>=w-3)?0:(i*13+seed)%255+1;
    else if(mode==3)v=i%257==256?93:0;
    else if(mode!=1)throw std::invalid_argument("Invalid snapshot mode");b[i]=std::uint8_t(v);}
    b.push_back(std::uint8_t(seed));b.push_back(std::uint8_t(seed*3));return b;}
void draw(std::istream& input,const Bytes& pool,std::size_t snap,const IndexRemap& remap){
    unsigned seed;PixelPoint at;PixelRect clip,dirty;std::uint32_t flags;int brightness;
    input>>seed>>at.x>>at.y>>clip.x>>clip.y>>clip.width>>clip.height>>dirty.x>>dirty.y>>dirty.width>>dirty.height>>flags>>brightness;
    if(!input||seed>100000)throw std::invalid_argument("Invalid cached draw command");
    Bytes stage(65536);for(unsigned i=0;i<stage.size();++i)stage[i]=std::uint8_t(i*37+seed*19);
    CachedVoxelPartServices s;s.kind=[]{out("kind");};s.selectBlitter=[](std::uint32_t v){out("select",v);};
    s.value2C4=[]{out("v2c4");return 2;};s.value2C0=[]{out("v2c0");return -1;};
    drawOrdinaryCachedVoxelPart(pool,snap,at,clip,flags,brightness,s,remap,stage,dirty);
    out("draw",dirty.x,dirty.y,dirty.width,dirty.height,digest(stage));
}
std::optional<std::size_t> snapshot(const Bytes& source,int w,int h,const std::array<int,6>& crop,int capacity,int cursor,Bytes& pool){
    if(capacity<0||capacity>65536||cursor<0||cursor>capacity)throw std::invalid_argument("Invalid snapshot pool command");
    pool=Bytes(std::size_t(capacity),0xa5);auto end=std::size_t(cursor);auto result=appendVoxelSnapshot(pool,end,source,w,h,crop);
    out("snapshot",int(bool(result)),end,digest(pool));return result;
}
}
int main(int argc,char** argv){try{
    if(argc!=5)return 2;
    const auto data=readRasterData(readFile(argv[1]));const auto light=readRenderData(readFile(argv[2]));
    const std::filesystem::path assets=argv[3];const auto vpl=readVpl(readFile(assets/"voxels.vpl"));
    const std::array<VoxelModel,3> models={readVxl(readFile(assets/"htnk.vxl")),readVxl(readFile(assets/"htnktur.vxl")),readVxl(readFile(assets/"htnkbarl.vxl"))};
    const auto palette=readPalette(readFile(argv[4]));const Palette black{};const std::array<IndexRemap,2> maps={stagingRemap(palette,palette),stagingRemap(black,black)};
    std::string line;while(std::getline(std::cin,line)){std::istringstream input(line);char op;input>>op;
        if(op=='R'){int w;std::string raw;input>>w>>raw;const auto b=unhex(raw);const auto e=encodeVoxelRow(b,w),d=decodeVoxelRow(e);out("row",e.size(),hex(e),d.size(),hex(d));}
        else if(op=='S'){int pm,mode,w,h,capacity,cursor;unsigned seed;std::array<int,6> crop{};
            input>>pm>>seed>>mode>>w>>h;for(auto& v:crop)input>>v;input>>capacity>>cursor;
            if(!input||pm<0||pm>1||w<1||w>256||h<1||h>256||seed>100000)throw std::invalid_argument("Invalid snapshot command");
            const auto source=pixels(seed,mode,w,h);Bytes pool;const auto snap=snapshot(source,w,h,crop,capacity,cursor,pool);
            if(snap)draw(input,pool,*snap,maps[std::size_t(pm)]);
        }else if(op=='B'){int pm,part;unsigned seed;Matrix pose{};input>>pm>>seed>>part;for(auto& v:pose){std::uint32_t word;input>>word;v=std::bit_cast<float>(word);}
            if(!input||pm<0||pm>1||part<0||part>2||seed>100000)throw std::invalid_argument("Invalid raster snapshot command");
            StagedVoxelPartInputs in;in.pose=pose;in.flags=0;in.brightness=1312;StagedVoxelPartServices s;
            s.flag204=s.flag205=s.house=s.predicateC0=[]{return std::uint8_t(0);};s.kind=[]{};s.value2C0=[]{return -1;};s.value2C4=[]{return 2;};
            Animation hva;hva.frames=1;hva.names={"fixture"};hva.transforms={voxelIdentity()};Bytes stage(65536);
            for(unsigned i=0;i<stage.size();++i)stage[i]=std::uint8_t(i*37+seed*19);
            auto frame=drawOrdinaryVoxelPartIntoStaging(data,light,models[std::size_t(part)],&hva,vpl,in,s,maps[std::size_t(pm)],stage);
            out("raster",digest(frame.pixels),digest(stage));frame.pixels.push_back(std::uint8_t(seed));frame.pixels.push_back(std::uint8_t(seed*3));
            Bytes pool;const auto snap=snapshot(frame.pixels,256,256,frame.rectangle,65536,7,pool);if(!snap)throw std::runtime_error("Stock snapshot pool exhausted");
            draw(input,pool,*snap,maps[std::size_t(pm)]);
        }else throw std::invalid_argument("Unknown voxel snapshot command");
        if(!input)throw std::invalid_argument("Incomplete voxel snapshot command");input>>std::ws;if(!input.eof())throw std::invalid_argument("Trailing voxel snapshot command");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
