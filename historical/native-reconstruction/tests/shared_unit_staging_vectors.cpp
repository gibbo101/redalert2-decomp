// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/SharedUnitVoxelStaging.hpp"
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
std::string digest(const Bytes& b){unsigned char h[EVP_MAX_MD_SIZE];unsigned n=0;
    if(!EVP_Digest(b.data(),b.size(),h,&n,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(h[i]);return s.str();}
struct Actor {UnitVoxelActorStage stage;std::uint16_t body=0,turret=0,pitch=0;Coord location;bool ready=false;};
}
int main(int argc,char** argv){try{
    if(argc!=5)return 2;
    const auto data=readRasterData(readFile(argv[1]));const auto light=readRenderData(readFile(argv[2]));
    const std::filesystem::path assets=argv[3];const auto vpl=readVpl(readFile(assets/"voxels.vpl"));
    const std::array<VoxelModel,3> models={readVxl(readFile(assets/"htnk.vxl")),readVxl(readFile(assets/"htnktur.vxl")),readVxl(readFile(assets/"htnkbarl.vxl"))};
    const auto palette=readPalette(readFile(argv[4]));const Palette black{};
    const std::array<IndexRemap,2> maps={stagingRemap(palette,palette),stagingRemap(black,black)};
    Animation hva;hva.frames=1;hva.names={"fixture"};hva.transforms={voxelIdentity()};
    SharedUnitVoxelStage stage;UnitVoxelTypeIndexes type;std::array<Actor,2> actors;int pm=0;bool ready=false;
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream input(line);char op=0;input>>op;
        if(op=='O'){
            unsigned seed=0;input>>pm>>seed;if(!input||pm<0||pm>1||seed>100000)throw std::invalid_argument("Invalid shared reset");
            stage={};type={};actors={};stage.pool.bytes=Bytes(0x80000,0xa5);
            for(unsigned i=0;i<65536;++i)stage.image.pixels[i]=std::uint8_t(i*37+seed*19);
            ready=true;out("reset");
        }else if(op=='S'){
            int id=-1;unsigned body=0,turret=0,pitch=0;Coord at;input>>id>>body>>turret>>pitch>>at.x>>at.y>>at.z;
            if(!input||!ready||id<0||id>1||body>65535||turret>65535||pitch>65535||at.z!=0)
                throw std::invalid_argument("Invalid supplied shared actor");
            auto& a=actors[std::size_t(id)];a.body=std::uint16_t(body);a.turret=std::uint16_t(turret);a.pitch=std::uint16_t(pitch);a.location=at;a.ready=true;out("set");
        }else if(op=='D'){
            int id=-1,gate=0,disabled=0,valid=0,barrel=0,predicate=0,camera=0,empty=0;UnitVoxelDrawInputs in;
            input>>id>>gate>>disabled>>valid>>barrel>>in.animationFrame>>in.brightness>>predicate>>camera>>empty
                >>in.point.x>>in.point.y>>in.clip.x>>in.clip.y>>in.clip.width>>in.clip.height;
            if(!input||!ready||!actors[0].ready||!actors[1].ready||id<0||id>1||gate<0||gate>255||disabled<0||disabled>1||valid<0||valid>7||
               barrel<0||barrel>1||predicate<0||predicate>255||camera<0||camera>1||empty<0||empty>2)
                throw std::invalid_argument("Invalid shared Unit draw");
            const auto& a=actors[std::size_t(id)];in.bodyHeading=a.body;in.turretHeading=a.turret;in.barrelHeading=a.pitch;in.keyGate=std::uint8_t(gate);
            in.emptyDirty=std::array<PixelRect,3>{{{0,0,0,0},{9,11,13,15},{248,249,24,23}}}[std::size_t(empty)];
            if(camera)in.camera={.5f,.25f,-.5f,.125f,-.25f,.5f,.25f,-.25f,.25f,-.5f,.5f,.5f};
            std::array<const VoxelModel*,3> selected{};for(unsigned i=0;i<3;++i)if(valid&(1<<i))selected[i]=&models[i];if(!barrel)selected[2]=nullptr;
            const auto q=[&](char k){out('q',k,id);};const auto image=[&]{rect(stage.image.dirty);out(digest(stage.image.pixels));};
            UnitVoxelStagingServices s;s.originalTypeVisible=[&]{q('V');};s.bodyPose=[&]{q('B');};s.multipleTurretQuery=[&]{q('M');};
            s.shadowPose=[&]{q('S');};s.status=[&]{q('T');};s.height=[&]{q('H');};s.cell=[&]{q('C');out(a.location.x,a.location.y,a.location.z);};
            s.finalBrightness=[&](int b){q('L');return b;};s.predicate=[&]{q('P');return std::uint8_t(predicate);};
            s.part.flag204=s.part.flag205=s.part.house=s.part.predicateC0=[]{return std::uint8_t(0);};s.part.kind=[]{};
            s.part.value2C4=[]{return 2;};s.part.value2C0=[]{return -1;};s.part.selectBlitter=[](auto){};
            s.finalDraw=[&](PixelPoint p,PixelRect clip,int brightness){out("final",id,p.x,p.y);rect(clip);out(brightness);image();};
            s.shadow=[&](const UnitVoxelShadowRequest& r){
                if(stage.stagingSurface||actors[std::size_t(id)].stage.staging)throw std::runtime_error("Shared staging flags not restored");
                out("shadow",id,r.key);rect(r.clip);out(r.point.x,r.point.y);for(float f:r.pose)out(std::bit_cast<std::uint32_t>(f));out(int(r.useStagingStencil));image();};
            SharedUnitVoxelObservers observe;observe.store=[](char k,int n){out('w',k,n);};
            observe.part=[&](const FootLitRequest& r){out("part",id,r.model,r.key);for(float f:r.pose)out(std::bit_cast<std::uint32_t>(f));};
            drawSharedUnitVoxelIntoStaging(data,light,selected,{&hva,&hva,&hva},vpl,in,disabled!=0,stage,type,actors[std::size_t(id)].stage,s,maps[std::size_t(pm)],observe);
            out("after");image();out("actors",int(actors[0].stage.staging),int(actors[1].stage.staging),"pool",stage.pool.cursor,digest(stage.pool.bytes));
            for(const auto& index:type.parts){out("index",index.size(),index.capacity(),int(index.sorted()));if(index.hotKey())out(*index.hotKey());else out("None");for(auto k:index.keys())out(k);}
        }else throw std::invalid_argument("Unknown shared Unit staging command");
        if(!input)throw std::invalid_argument("Incomplete shared Unit staging command");input>>std::ws;if(!input.eof())throw std::invalid_argument("Trailing shared Unit staging command");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
