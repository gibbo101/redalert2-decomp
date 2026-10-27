// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/ShadowVoxelWorld.hpp"
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
std::string digestWords(const std::vector<std::uint16_t>& v){Bytes b;for(auto n:v){b.push_back(n&255);b.push_back(n>>8);}return digest(b);}
Animation animation(int mode){Animation a;a.frames=mode==2?3:1;a.names={"fixture"};
    for(int n=0;n<a.frames;++n){auto m=voxelIdentity();if(mode==2){m[0]=.5f+.25f*n;m[5]=1.25f;m[3]=.375f*n;m[7]=-.625f*n;}a.transforms.push_back(m);}return a;}
}
int main(int argc,char** argv){try{
    if(argc!=4)return 2;
    const auto data=readRasterData(readFile(argv[1]));const auto light=readRenderData(readFile(argv[2]));const std::filesystem::path assets=argv[3];
    const std::array<VoxelModel,3> models={readVxl(readFile(assets/"htnk.vxl")),readVxl(readFile(assets/"htnktur.vxl")),readVxl(readFile(assets/"htnkbarl.vxl"))};
    VoxelSnapshotIndex index;VoxelSnapshotPool pool{Bytes(0x80000,0xa5)};
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream input(line);char op=0;input>>op;
        if(op=='O'){index={};pool={Bytes(0x80000,0xa5)};out("reset");}
        else if(op=='D'){
            int seed,part,key,available,disabled,bad,suppressed,noShadow,allow,mode,stencil,z;PixelRect dirty;ShadowVoxelWorldInputs in;
            input>>seed>>part>>key>>available>>disabled>>bad>>suppressed>>noShadow>>allow>>mode>>stencil
                 >>in.point.x>>in.point.y>>in.clip.x>>in.clip.y>>in.clip.width>>in.clip.height>>z>>dirty.x>>dirty.y>>dirty.width>>dirty.height;
            for(float& f:in.pose){std::uint32_t bits=0;input>>bits;f=std::bit_cast<float>(bits);}
            if(!input||seed<0||seed>100000||part<0||part>2||mode<0||mode>2)throw std::invalid_argument("Invalid shadow world fixture");
            in.cache={key,suppressed!=0,noShadow!=0,bad!=0,available!=0,disabled!=0,allow!=0};
            Bytes pixels(65536);for(unsigned i=0;i<65536;++i)pixels[i]=(i*3+(i/256)*7+unsigned(seed))%5<2?37:0;
            if(stencil)in.stencil={pixels,256,256,{0,0}};
            constexpr int w=160,h=144;std::vector<std::uint16_t> colors(w*h),depth(w*h);
            constexpr unsigned depths[]={0,32720,32740,32760,32768,32780,65535};
            for(unsigned i=0;i<colors.size();++i){colors[i]=std::uint16_t(i*37+unsigned(seed)*91);depth[i]=std::uint16_t(depths[(i+unsigned(seed))%7]);}
            CachedVoxelPartServices s;s.kind=[]{out("kind");};s.selectBlitter=[](auto flags){out("select",flags);};s.value2C4=[]{out("v2c4");return 2;};s.value2C0=[&]{out("v2c0");return z;};
            auto hva=animation(mode);
            const auto result=drawOrdinaryShadowVoxelToWorld(data,light,&models[std::size_t(part)],mode?&hva:nullptr,in,available?&index:nullptr,pool,s,w,h,colors,depth,dirty);
            out("draw",int(result.kind),dirty.x,dirty.y,dirty.width,dirty.height,result.raster?digest(result.raster->pixels):"-",digestWords(colors),digestWords(depth),"pool",pool.cursor,digest(pool.bytes));
            out("state",index.size(),index.capacity(),int(index.sorted()));if(index.hotKey())out(*index.hotKey());else out("None");for(auto k:index.keys())out(k);
        }else throw std::invalid_argument("Unknown shadow world operation");
        if(!input)throw std::invalid_argument("Incomplete shadow world operation");input>>std::ws;if(!input.eof())throw std::invalid_argument("Trailing shadow world operation");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
