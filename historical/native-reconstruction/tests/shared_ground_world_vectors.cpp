// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/SharedGroundUnitVoxelWorld.hpp"
#include "render/DriveBodyPose.hpp"
#include "render/DriveShadowPose.hpp"
#include "render/RampGeometry.hpp"
#include "render/VoxelRampShadow.hpp"
#include "assets/MovementData.hpp"
#include "assets/PreparedData.hpp"
#include <map>
#include "render/PreparedUnitDepth.hpp"
#include "assets/MapCoordinateCell.hpp"
#include "assets/Archive.hpp"
#include <openssl/evp.h>
#include <bit>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <memory>
using namespace ra2;
namespace {
template<class... T>void out(T... v){((std::cout<<v<<' '),...);}
void rect(PixelRect r){out(r.x,r.y,r.width,r.height);}
std::string digestWords(const std::vector<std::uint16_t>& v);
std::string digest(const Bytes& b){unsigned char h[EVP_MAX_MD_SIZE];unsigned n=0;if(!EVP_Digest(b.data(),b.size(),h,&n,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(h[i]);return s.str();}
std::string digestWords(const std::vector<std::uint16_t>& v){Bytes b(v.size()*2);for(std::size_t i=0;i<v.size();++i){b[i*2]=std::uint8_t(v[i]);b[i*2+1]=std::uint8_t(v[i]>>8);}return digest(b);}
std::string digest(const std::uint8_t* p,std::size_t n){return digest(Bytes(p,p+n));}
std::string digest(const std::vector<std::uint32_t>& v){Bytes b(v.size()*4);for(std::size_t i=0;i<v.size();++i)for(unsigned j=0;j<4;++j)b[i*4+j]=std::uint8_t(v[i]>>(j*8));return digest(b);}

}
#include "prepared_map_fixture.hpp"
int main(int argc,char** argv){try{
    if(argc!=8)return 2;
    const auto data=readRasterData(readFile(argv[1]),PatchedEngineSha);const auto light=readRenderData(readFile(argv[2]),PatchedEngineSha);
    const std::filesystem::path assets=argv[3];const auto vpl=readVpl(readFile(assets/"voxels.vpl"));
    const std::array<VoxelModel,3> models={readVxl(readFile(assets/"htnk.vxl")),readVxl(readFile(assets/"htnktur.vxl")),readVxl(readFile(assets/"htnkbarl.vxl"))};
    const auto palette=readPalette(readFile(argv[4]));const Palette black{};
    const std::array<IndexRemap,2> maps={stagingRemap(palette,palette),stagingRemap(black,black)};
    Animation hva;hva.frames=1;hva.names={"fixture"};hva.transforms={voxelIdentity()};
    const auto rampData=readRampGeometryData(readFile(argv[5]),PatchedEngineSha);
    const auto directions=readDirectionData(readFile(argv[6]),PatchedEngineSha);
    const auto stock=stockRampGeometry(light,data,directions,rampData);
    const auto ramps=voxelRampShadowMatrices(data,stock.axisTilt,stock.diagonalTilt);
    const auto poseData=readRampPoseData(readFile(argv[7]),PatchedEngineSha);
    const auto quaternions=voxelRampQuaternions(data,light,stock.axisTilt,stock.diagonalTilt);
    struct Actor {Coord at;std::uint16_t body=0,turret=0,pitch=0;DriveBodyInputs pose;UnitVoxelActorStage stage;bool ready=false;};
    std::array<Actor,2> actors;SharedUnitVoxelStage state;UnitVoxelWorldTypeIndexes type;
    int pm=0,seed=0;bool reset=false;std::unique_ptr<prepared_fixture::Map> map;
    constexpr int w=160,h=144;std::vector<std::uint16_t> colors(w*h),depth(w*h),alpha(w*h);std::vector<Palette16> palettes(53);
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream input(line);char op=0;input>>op;
        if(op=='P'){
            reset=false;
            map=std::make_unique<prepared_fixture::Map>();map->prepare(input,light);
            if(map->levelHeight!=stock.levelHeight)throw std::invalid_argument("Ground profile requires stock Cell level height");
        }else if(op=='O'){
            input>>pm>>seed;if(!map||pm<0||pm>1||seed<0||seed>100000)throw std::invalid_argument("Invalid Unit reset");
            state={};type={};actors={};state.pool={Bytes(0x80000,0xa5)};reset=true;
            for(unsigned i=0;i<65536;++i)state.image.pixels[i]=std::uint8_t(i*37+seed*19);
            constexpr unsigned depths[]={0,32720,32740,32760,32768,32780,65535};
            for(unsigned i=0;i<colors.size();++i){colors[i]=std::uint16_t(i*37+unsigned(seed)*91);depth[i]=std::uint16_t(depths[(i+unsigned(seed))%7]);alpha[i]=std::uint16_t((i*17+unsigned(seed)*11)&255);}
            for(unsigned row=0;row<53;++row)for(unsigned i=0;i<256;++i)palettes[row][i]=std::uint16_t(unsigned(seed)*257+row*599+i*131);
            out("reset");
        }else if(op=='S'){
            int id=-1;Coord at;unsigned body=0,turret=0,pitch=0;DriveBodyInputs pose;std::uint32_t rx=0,ry=0;
            input>>id>>at.x>>at.y>>at.z>>body>>turret>>pitch>>pose.tick>>pose.ramp.current>>pose.ramp.previous
                >>pose.ramp.start>>pose.ramp.padding>>pose.ramp.remaining>>pose.ramp.duration>>rx>>ry;
            if(!input||!map||!reset||id<0||id>1||body>65535||turret>65535||pitch>65535||at.x<0||at.y<0||at.x>=512*256||at.y>=512*256||at.z<-1048576||at.z>1048576||
               !map->table[std::size_t(at.y/256)*512+std::size_t(at.x/256)]||pose.ramp.current<0||pose.ramp.current>20||pose.ramp.previous<0||pose.ramp.previous>20)
                throw std::invalid_argument("Invalid supplied shared ground actor");
            pose.rockingX=std::bit_cast<float>(rx);pose.rockingY=std::bit_cast<float>(ry);pose.type330=30.5;pose.type338=24.25;
            if(!std::isfinite(pose.rockingX)||!std::isfinite(pose.rockingY)||std::abs(pose.rockingX)>1||std::abs(pose.rockingY)>1)
                throw std::invalid_argument("Invalid supplied shared rocking");
            auto& a=actors[std::size_t(id)];a.at=at;a.body=std::uint16_t(body);a.turret=std::uint16_t(turret);a.pitch=std::uint16_t(pitch);a.pose=pose;a.ready=true;
            out("set");
         }else if(op=='D'){
            if(!map)throw std::invalid_argument("Map must be prepared before Unit draw");
            PreparedFootDepthInputs prepared;std::uint64_t scale=0;
            int id=-1;input>>id>>scale;
            if(!reset||id<0||id>1||!actors[0].ready||!actors[1].ready)throw std::invalid_argument("Both supplied shared actors required");
            auto& actor=actors[std::size_t(id)];prepared.unit.location=actor.at;
            out("actor",id);
            prepared.unit.heightScale=std::bit_cast<double>(scale);prepared.invalid={-32768,-32768};
            if(!std::isfinite(prepared.unit.heightScale)||prepared.unit.heightScale<=0||prepared.unit.heightScale>1)
                throw std::invalid_argument("Invalid shared height scale");
            int contact=0,noShadow=0,disableShadow=0;input>>contact>>noShadow>>disableShadow;
            UnitVoxelDrawInputs in;unsigned body=actor.body,turret=actor.turret,pitch=actor.pitch,gate=0;
            int disabled=0,valid=0,barrel=0,predicate=0,camera=0,empty=0;
            input>>gate>>disabled>>valid>>barrel>>in.animationFrame>>in.brightness>>predicate>>camera>>empty
                 >>in.point.x>>in.point.y>>in.clip.x>>in.clip.y>>in.clip.width>>in.clip.height;
            if(!input||body>65535||turret>65535||pitch>65535||gate>255||valid<1||valid>7||!(valid&1)||
               disabled<0||disabled>1||barrel<0||barrel>1||predicate<0||predicate>1||camera<0||camera>1||
               noShadow<0||noShadow>1||disableShadow<0||disableShadow>1||empty<0||empty>2||state.pool.bytes.empty())throw std::invalid_argument("Invalid Unit staging draw");
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
            auto stage=[&]{rect(state.image.dirty);out(digest(state.image.pixels));};
            s.shadow=[&](const UnitVoxelShadowRequest& r){
                if(actor.stage.staging||state.stagingSurface)throw std::runtime_error("Unit shadow state was not restored");
                out("shadow",r.key);rect(r.clip);out(r.point.x,r.point.y);for(float f:r.pose)out(std::bit_cast<std::uint32_t>(f));
                out(int(r.useStagingStencil));stage();
            };
            if(seed<0||seed>100000||(contact!=0&&contact!=1))throw std::invalid_argument("Invalid prepared Unit world fixture");
            prepared.unit.facing={};prepared.unit.facing.desired=prepared.unit.facing.start=std::uint16_t(body);
            std::vector<std::uint32_t> queries;
            const auto event=[&](std::initializer_list<std::uint32_t> v){queries.insert(queries.end(),v);};
            const auto fallbackStore=[&](MapInputPosition p){event({0xffffffffu,0,prepared_fixture::packed(p)});};
            MapAttributeLookup attr{map->table,&map->fallback.input,[&](MapInputPosition p){event({304,prepared_fixture::packed(p)});},fallbackStore};
            PreparedFootDepthWorld binding;binding.unit.tiles=map->tiles;binding.unit.overlays=map->overlays;
            binding.unit.cell=[&](MapInputPosition p)->const MapCellAttributes&{
                const auto& found=mapAttributeCell(p,attr);if(&found==&map->fallback.input)return map->fallback;
                const auto index=std::size_t(int(p.y)*512+int(p.x));return map->cells[std::size_t(map->slots[index])].attributes;
            };
            binding.unit.dimensions=[&](int tile,int sub){
                if(tile<0||std::size_t(tile)>=map->tiles.size()||!map->tiles[std::size_t(tile)].image)
                    throw std::invalid_argument("Ground depth requires an available TMP image");
                event({404,unsigned(tile),unsigned(sub)});
            };
            // New ground profile binds the same stable prepared records without
            // lifting the old PreparedUnitDepth flat-current-Cell guard.
            std::map<const MapCellAttributes*,FootDepthCell> views;
            services.map.tileBase=prepared.tileBase;services.map.invalid=prepared.invalid;
            services.map.coordinates=[&]{return footDepthCoordinates(prepared.unit.location.x,prepared.unit.location.y);};
            services.map.cell=[&](UnitLightCell p)->const FootDepthCell*{
                const auto& cell=binding.unit.cell({p.x,p.y});const auto& v=cell.input;
                auto& view=views[&cell];view={{v.position.x,v.position.y},v.flags,v.tile,v.land,v.tube,v.level};return &view;
            };
            services.map.cellPredicate=[](const FootDepthCell& c){return footDepthCellPredicate(c,0);};
            services.baseDepth=[&]{return ordinaryUnitBaseDepth(prepared.unit,binding.unit).depth;};
            const auto locate=[&](Coord p)->const MapCellInput&{
                event({405,unsigned(p.x),unsigned(p.y),unsigned(p.z)});
                return mapCoordinateCell(p,{map->table,&map->fallback.input,fallbackStore},262144);
            };
            GroundUnitShadowServices ground;
            ground.pose=[&](std::int32_t* key){
                event({500});DriveShadowInputs v;v.position=prepared.unit.location;
                v.tick=actor.pose.tick;v.slopeStart=actor.pose.ramp.start;v.slopeRemaining=actor.pose.ramp.remaining;v.slopeDuration=actor.pose.ramp.duration;
                v.rockingX=actor.pose.rockingX;v.rockingY=actor.pose.rockingY;
                DriveShadowServices g;g.currentRamp=[&](Coord p){return locate(p).slope;};g.bodyFacing=[&]{return in.bodyHeading;};
                return driveShadowPose(data,ramps,v,g,key);
            };
            ground.relativeHeight=[&]{
                event({502});const int h=relativeMapHeight(map->floorState,stock.levelHeight,prepared.unit.location,0,0,{map->table,&map->fallback.input,fallbackStore});
                event({503,unsigned(h)});return h;
            };
            ground.point=[&]{event({507});return PixelPoint{0,heightPixels(prepared.unit.heightScale,ground.relativeHeight())};};
            ground.observeShadow=[&](const UnitVoxelShadowRequest&,PixelPoint p){event({508,unsigned(p.x),unsigned(p.y)});};
            const auto location=prepared.unit.location;
            if(location.x<0||location.y<0||location.x>=512*256||location.y>=512*256||
               !map->table[std::size_t(location.y/256)*512+std::size_t(location.x/256)])
                throw std::invalid_argument("Ground draw requires a resident current Cell");
            queries.clear(); // Fixture preflight is outside the original draw trace.
            s.cell=[&]{const auto p=prepared.unit.location;event({405,unsigned(p.x),unsigned(p.y),unsigned(p.z)});
                mapCoordinateCell(p,{map->table,&map->fallback.input,fallbackStore},262144);};
            services.metadata={10,8,13,0,1};
            services.actor494=std::uint32_t(contact);services.contact.firstContact=[&]{return contact!=0;};
            services.contact.contactKind=[]{return 6;};services.contact.contactType1357=[]{return std::uint8_t(1);};
            services.surface=[&](const UnitSurfaceRequest& r){out("surface");rect(r.destination);rect(r.sourceBounds);rect(r.source);rect(r.clip);out(r.blitter,r.depth,r.gradient,r.brightness,r.extra);stage();};
            GroundUnitBodyServices bodyServices;
            bodyServices.pose=[&](std::int32_t* key){
                event({501});const auto pose=driveBodyPose(data,poseData,ramps,quaternions,actor.pose,[&]{return actor.body;},key);
                out("body");for(float f:pose)out(std::bit_cast<std::uint32_t>(f));out(std::uint32_t(*key));return pose;
            };
            bodyServices.observePart=[](UnitVoxelPart p,int key,const Matrix& m){out("part",int(p),key);for(float f:m)out(std::bit_cast<std::uint32_t>(f));};
            drawSharedPosedGroundUnitVoxelToWorld(data,light,selected,{&hva,&hva,&hva},vpl,in,disabled!=0,noShadow!=0,disableShadow!=0,
                state,type,actor.stage,services,bodyServices,ground,maps[std::size_t(pm)],{w,h,colors,depth,alpha,palettes},[](char k,int n){out('w',k,n);});
            out("after");stage();out("actors",int(actors[0].stage.staging),int(actors[1].stage.staging));out("pool",state.pool.cursor,digest(state.pool.bytes));
            for(const auto* ip:std::array<const VoxelSnapshotIndex*,4>{&type.lit.parts[0],&type.lit.parts[1],&type.lit.parts[2],&type.shadow}){const auto& index=*ip;out("index",index.size(),index.capacity(),int(index.sorted()));if(index.hotKey())out(*index.hotKey());else out("None");for(auto k:index.keys())out(k);}
            out("world",digestWords(colors),digestWords(depth),digestWords(alpha));
            out("queries",prepared_fixture::packed(map->fallback.input.position),digest(queries));
            Bytes floorBytes{map->floorState.flags};
            const auto append=[&](double v){const auto n=std::bit_cast<std::uint64_t>(v);for(unsigned i=0;i<8;++i)floorBytes.push_back(std::uint8_t(n>>(i*8)));};
            append(map->floorState.height);append(map->floorState.scale);
            for(const auto& plane:map->floorState.planes)for(double v:{plane.x,plane.y,plane.offset,plane.limit,plane.add})append(v);
            out("floor",digest(floorBytes));
        }else throw std::invalid_argument("Unknown Unit staging command");
        if(!input)throw std::invalid_argument("Incomplete Unit staging command");input>>std::ws;if(!input.eof())throw std::invalid_argument("Trailing Unit staging command");std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
