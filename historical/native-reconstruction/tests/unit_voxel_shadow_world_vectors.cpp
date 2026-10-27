// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitVoxelShadowWorld.hpp"
#include "foot_depth_fixture.hpp"
#include "assets/Archive.hpp"
#include <openssl/evp.h>
#include <bit>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
template<class... T>void out(T... v){((std::cout<<v<<' '),...);}
void rect(PixelRect r){out(r.x,r.y,r.width,r.height);}
std::string digestWords(const std::vector<std::uint16_t>& v);
std::string digest(const Bytes& b){unsigned char h[EVP_MAX_MD_SIZE];unsigned n=0;if(!EVP_Digest(b.data(),b.size(),h,&n,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(h[i]);return s.str();}
std::string digestWords(const std::vector<std::uint16_t>& v){Bytes b;for(auto n:v){b.push_back(n&255);b.push_back(n>>8);}return digest(b);}

}
int main(int argc,char** argv){try{
    if(argc!=5)return 2;
    const auto data=readRasterData(readFile(argv[1]));const auto light=readRenderData(readFile(argv[2]));
    const std::filesystem::path assets=argv[3];const auto vpl=readVpl(readFile(assets/"voxels.vpl"));
    const std::array<VoxelModel,3> models={readVxl(readFile(assets/"htnk.vxl")),readVxl(readFile(assets/"htnktur.vxl")),readVxl(readFile(assets/"htnkbarl.vxl"))};
    const auto palette=readPalette(readFile(argv[4]));const Palette black{};
    const std::array<IndexRemap,2> maps={stagingRemap(palette,palette),stagingRemap(black,black)};
    Animation hva;hva.frames=1;hva.names={"fixture"};hva.transforms={voxelIdentity()};
    UnitVoxelShadowWorldState joined;auto& state=joined.unit;int pm=0;
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream input(line);char op=0;input>>op;
        if(op=='O'){
            unsigned seed=0;input>>pm>>seed;if(pm<0||pm>1||seed>100000)throw std::invalid_argument("Invalid Unit reset");
            joined={};state.pool={Bytes(0x80000,0xa5)};
            for(unsigned i=0;i<65536;++i)state.image.pixels[i]=std::uint8_t(i*37+seed*19);
            out("reset");
        }else if(op=='D'){
            int seed=0,mapMode=0,contact=0,noShadow=0,disableShadow=0;input>>seed>>mapMode>>contact>>noShadow>>disableShadow;
            UnitVoxelDrawInputs in;unsigned body=0,turret=0,pitch=0,gate=0;
            int disabled=0,valid=0,barrel=0,predicate=0,camera=0,empty=0;
            input>>body>>turret>>pitch>>gate>>disabled>>valid>>barrel>>in.animationFrame>>in.brightness>>predicate>>camera>>empty
                 >>in.point.x>>in.point.y>>in.clip.x>>in.clip.y>>in.clip.width>>in.clip.height;
            if(!input||gate>255||valid<0||valid>7||empty<0||empty>2||state.pool.bytes.empty())throw std::invalid_argument("Invalid Unit staging draw");
            in.bodyHeading=std::uint16_t(body);in.turretHeading=std::uint16_t(turret);in.barrelHeading=std::uint16_t(pitch);in.keyGate=std::uint8_t(gate);
            in.barrelModel=barrel!=0&&(valid&4)!=0;
            in.emptyDirty=std::array<PixelRect,3>{{{0,0,0,0},{9,11,13,15},{248,249,24,23}}}[std::size_t(empty)];
            if(camera)in.camera={.5f,.25f,-.5f,.125f,-.25f,.5f,.25f,-.25f,.25f,-.5f,.5f,.5f};
            std::array<const VoxelModel*,3> selected{};for(unsigned i=0;i<3;++i)if(valid&(1<<i))selected[i]=&models[i];
            if(!barrel)selected[2]=nullptr;
            UnitVoxelWorldServices services;auto& s=services.actor;s.originalTypeVisible=s.bodyPose=s.multipleTurretQuery=s.shadowPose=s.status=s.height=s.cell=[]{};
            s.finalBrightness=[](int b){return b;};s.predicate=[&]{return std::uint8_t(predicate);};
            s.part.flag204=s.part.flag205=s.part.house=s.part.predicateC0=[]{return std::uint8_t(0);};s.part.kind=[]{};
            s.part.value2C4=[]{return 2;};s.part.value2C0=[]{return -1;};s.part.selectBlitter=[](auto){};
            auto stage=[&]{rect(state.draw.dirty);out(digest(state.image.pixels));};
            s.shadow=[&](const UnitVoxelShadowRequest& r){
                if(state.draw.staging||state.draw.stagingSurface)throw std::runtime_error("Unit shadow state was not restored");
                out("shadow",r.key);rect(r.clip);out(r.point.x,r.point.y);for(float f:r.pose)out(std::bit_cast<std::uint32_t>(f));
                out(int(r.useStagingStencil));stage();
            };
            if(seed<0||seed>100000||mapMode<0||mapMode>4||(contact!=0&&contact!=1))throw std::invalid_argument("Invalid Unit world fixture");
            DepthFixture f;f.x=2560;f.y=2816;f.logging=false;f.prepare();
            auto cell=[&](int x,int y)->FootDepthCell&{for(auto& c:f.cells)if(c.position==UnitLightCell{std::int16_t(x),std::int16_t(y)})return c;throw std::runtime_error("Missing fixture cell");};
            if(mapMode==1||mapMode==4){cell(10,11).flags=0x100;for(auto p:std::array<PixelPoint,3>{{{10,12},{11,11},{11,12}}})cell(p.x,p.y).tile=6;}
            if(mapMode==2||mapMode==4)for(auto& c:f.cells){c.field116=0;c.fieldEC=10;}
            if(mapMode==3||mapMode==4){cell(11,12).level=5;cell(12,13).level=10;}
            services.map=f.world();services.metadata={10,8,13,0,1};services.baseDepth=[&]{return flatUnitDepthAdjust(worldHeightScale(data,light),0);};
            services.actor494=std::uint32_t(contact);services.contact.firstContact=[&]{return contact!=0;};
            services.contact.contactKind=[]{return 6;};services.contact.contactType1357=[]{return std::uint8_t(1);};
            services.surface=[&](const UnitSurfaceRequest& r){out("surface");rect(r.destination);rect(r.sourceBounds);rect(r.source);rect(r.clip);out(r.blitter,r.depth,r.gradient,r.brightness,r.extra);stage();};
            constexpr int w=160,h=144;std::vector<std::uint16_t> colors(w*h),depth(w*h),alpha(w*h);std::vector<Palette16> palettes(53);
            constexpr unsigned depths[]={0,32720,32740,32760,32768,32780,65535};
            for(unsigned i=0;i<colors.size();++i){colors[i]=std::uint16_t(i*37+unsigned(seed)*91);depth[i]=std::uint16_t(depths[(i+unsigned(seed))%7]);alpha[i]=std::uint16_t((i*17+unsigned(seed)*11)&255);}
            for(unsigned row=0;row<53;++row)for(unsigned i=0;i<256;++i)palettes[row][i]=std::uint16_t(unsigned(seed)*257+row*599+i*131);
            drawHealthyUnitVoxelAndShadowToWorld(data,light,selected,{&hva,&hva,&hva},vpl,in,disabled!=0,noShadow!=0,disableShadow!=0,joined,services,maps[std::size_t(pm)],{w,h,colors,depth,alpha,palettes});
            out("after");stage();out("pool",state.pool.cursor,digest(state.pool.bytes));
            for(const auto* ip:std::array<const VoxelSnapshotIndex*,4>{&state.indexes[0],&state.indexes[1],&state.indexes[2],&joined.shadow}){const auto& index=*ip;out("index",index.size(),index.capacity(),int(index.sorted()));if(index.hotKey())out(*index.hotKey());else out("None");for(auto k:index.keys())out(k);}
            out("world",digestWords(colors),digestWords(depth),digestWords(alpha));
        }else throw std::invalid_argument("Unknown Unit staging command");
        if(!input)throw std::invalid_argument("Incomplete Unit staging command");input>>std::ws;if(!input.eof())throw std::invalid_argument("Trailing Unit staging command");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
