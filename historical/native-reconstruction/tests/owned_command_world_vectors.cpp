// SPDX-License-Identifier: GPL-3.0-or-later
// Authored fixture adapted from owned_unit_world_vectors.cpp. This separate
// runner actually owns/steps/draws through OwnedUnitWorld; legacy runners retain
// their source identity and their own binding. Original protocol is unchanged.
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
#include "assets/OwnedUnitDrawingMap.hpp"
#include "assets/OwnedUnitProcesses.hpp"
#include "platform/OwnedUnitWorld.hpp"
#include "owned_advance_checks.hpp"
#include <algorithm>
#include "platform/TerrainUnitContext.hpp"
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
    const bool advanceAdmission=argc==11&&std::string_view(argv[10])=="--advance-admission";
    const bool twoProcesses=(argc==10||advanceAdmission)&&std::string_view(argv[9])=="--two-processes";
    if(!twoProcesses)return 2;
    const auto driveData=twoProcesses?readDriveData(readFile(argv[8]),readFile(argv[6])):readDriveData(readFile(argv[8]));
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
    const OwnedUnitProcessesInputs ownershipInputs{5,1,0,0,8,
        std::array<OwnedUnitProcessActorInputs,2>{OwnedUnitProcessActorInputs{{19,-23},31},OwnedUnitProcessActorInputs{{-29,37},-41}},
        advanceAdmission?OwnedUnitAdvancePolicy::ordinaryAdmission:OwnedUnitAdvancePolicy::guarded};
    int identityGuards=0,warmCloneGuards=0,refusalCloneGuards=0,unknownActorGuards=0,advancePreviewGuards=0;
    std::unique_ptr<OwnedUnitWorld> world;
    int pm=0,seed=0;bool reset=false;std::unique_ptr<prepared_fixture::Map> map;
    constexpr int w=160,h=144;std::vector<std::uint16_t> colors(w*h),depth(w*h),alpha(w*h);std::vector<Palette16> palettes(53);
    std::shared_ptr<MutableUnitMap> owned;std::unique_ptr<TerrainUnitContext> initialContext;TerrainUnitContext* context=nullptr;bool drawing=false;std::function<void(MapInputPosition)> fallbackObserver;int tick=0,speed=0;
    const auto snapshot=[&]{
        auto& m=*context->unit;
        for(int id:{0,1}){
            const auto& a=id?context->parked->state:context->state;const auto& v=a.movement;
            const auto& mark=id?context->parked->marking:m.marking;const auto& d=id?context->parked->discovery:m.discovery;
            const auto& turret=id?context->parked->drawingTurret():Facing{};
            out("actor-state",id,v.actor.position.x,v.actor.position.y,v.actor.position.z,a.destination.x,a.destination.y,a.destination.z,
                v.head.x,v.head.y,v.head.z,v.track,v.index,v.accumulator,v.driving,unsigned(v.actor.marked74),unsigned(v.reached5a0),unsigned(v.reached5a1),
                v.body.desired,v.body.start,v.body.timerStart,v.body.duration,v.body.rate,a.wasRotating,
                std::uint16_t(a.nextX)|(std::uint32_t(std::uint16_t(a.nextY))<<16),unsigned(a.preparation57a),unsigned(a.crossing57b),
                std::bit_cast<std::uint64_t>(a.percentage),std::bit_cast<std::uint64_t>(a.instancePercentage),
                a.ramps.current,a.ramps.previous,a.ramps.start,a.ramps.padding,a.ramps.remaining,a.ramps.duration,
                a.retryStart,a.retryPadding,a.retryRemaining);
            for(int n:a.route)out(n);
            out(std::uint32_t(m.membership.actors.at(id).next),unsigned(mark.needsRedraw),unsigned(d.current373),unsigned(d.other374),
                d.mission98,d.queuedA0,unsigned(d.queuedA4));
            if(id)out(turret.desired,turret.start,turret.timerStart,turret.duration,turret.rate);
            else if(world){const auto& t=world->actor(0).turret;out(t.desired,t.start,t.timerStart,t.duration,t.rate);}
            else out(actors[0].turret,actors[0].turret,0,0,v.body.rate);
        }
        std::vector<std::uint32_t> selected;
        for(std::size_t i=0;i<m.occupation.size();++i){
            const auto& c=i==owned->cells.size()?owned->fallback:owned->cells[i].attributes;const auto& v=c.input;
            const auto& o=m.occupation[i];const auto& cell=m.cellMembership(i);const auto& vis=m.visibilityCells[i];
            selected.insert(selected.end(),{prepared_fixture::packed(v.position),std::uint32_t(v.tile),std::uint32_t(v.land),std::uint32_t(v.subTile),std::uint8_t(v.level),v.slope,
                c.extraHeight,std::uint32_t(c.passability),std::uint32_t(cell.head),std::uint32_t(cell.alternateHead),o.ground,o.elevated,vis.flags12c,vis.flags140});
        }
        const auto& f=m.membership.foundation;const auto& house=m.houses.houses.at(0);
        out("owned-map",digest(selected),digest(owned->buffer4),digest(owned->buffer10),"foundation",unsigned(f.objectFlag),prepared_fixture::packed({f.fallback.x,f.fallback.y}),unsigned(f.unitFlag),
            prepared_fixture::packed({f.unit[0].x,f.unit[0].y}),prepared_fixture::packed({f.unit[1].x,f.unit[1].y}),"House",unsigned(house.human134),unsigned(house.control135),unsigned(house.discovered13c),unsigned(house.field13d),unsigned(house.field5668),unsigned(house.field5669),"redraw",int(context->redraw.tactical));
        Bytes lazy{owned->floor.flags};const auto append=[&](double n){const auto bits=std::bit_cast<std::uint64_t>(n);for(unsigned i=0;i<8;++i)lazy.push_back(std::uint8_t(bits>>(i*8)));};
        append(owned->floor.height);append(owned->floor.scale);for(const auto& p:owned->floor.planes)for(double n:{p.x,p.y,p.offset,p.limit,p.add})append(n);
        out("lazy",digest(lazy));
        if(world)for(int id:{0,1}){const auto& v=world->actor(id).wait;out("wait-state",id,v.start,v.padding,v.remaining);}
    };
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream input(line);char op=0;input>>op;
        if(op=='P'){
            reset=false;world.reset();initialContext.reset();context=nullptr;owned.reset();
            map=std::make_unique<prepared_fixture::Map>();map->prepare(input,light);
            if(map->levelHeight!=stock.levelHeight)throw std::invalid_argument("Ground profile requires stock Cell level height");
        }else if(op=='O'){
            input>>pm>>seed;if(!map||reset||pm!=0||seed<0||seed>100000)throw std::invalid_argument("Fresh prepared map and normal remap required");
            world.reset();initialContext.reset();context=nullptr;owned.reset();state={};type={};actors={};state.pool={Bytes(0x80000,0xa5)};reset=true;
            for(unsigned i=0;i<65536;++i)state.image.pixels[i]=std::uint8_t(i*37+seed*19);
            constexpr unsigned depths[]={0,32720,32740,32760,32768,32780,65535};
            for(unsigned i=0;i<colors.size();++i){colors[i]=std::uint16_t(i*37+unsigned(seed)*91);depth[i]=std::uint16_t(depths[(i+unsigned(seed))%7]);alpha[i]=std::uint16_t((i*17+unsigned(seed)*11)&255);}
            for(unsigned row=0;row<53;++row)for(unsigned i=0;i<256;++i)palettes[row][i]=std::uint16_t(unsigned(seed)*257+row*599+i*131);
            out("reset");
        }else if(op=='I'){
            if(!map||!reset||context)throw std::invalid_argument("Prepared reset required");
            Coord at,dest,parkedAt;int heading,rot,start,steps,marked,effect,mode,present,key,crusher,parkedHeading,first,second,order;
            input>>at.x>>at.y>>at.z>>dest.x>>dest.y>>dest.z>>heading>>rot>>speed>>start>>steps>>marked>>effect>>mode>>present>>key;
            std::array<int,24> route;for(auto& n:route)input>>n;
            std::array<std::uint64_t,4> bits;for(auto& n:bits)input>>n;
            input>>crusher>>parkedAt.x>>parkedAt.y>>parkedAt.z>>parkedHeading>>first>>second>>order;
            unsigned t0,t1;input>>t0>>t1;
            if(!input||t0>65535||t1>65535||mode!=0||order!=0||marked!=0||effect!=1||present!=1||key!=0||crusher!=1||rot<1||rot>127||speed<0||speed>255||heading<0||heading>65535||parkedHeading<0||parkedHeading>65535||steps!=1)throw std::invalid_argument("Owned initialization outside domain");
            std::array<double,4> numbers;for(unsigned i=0;i<4;++i){numbers[i]=std::bit_cast<double>(bits[i]);if(!std::isfinite(numbers[i]))throw std::invalid_argument("Nonfinite owned numeric input");}
            for(int d:route)if(d<-1||d>7)throw std::invalid_argument("Invalid owned route");
            if(route.back()!=-1)throw std::invalid_argument("Unterminated owned route");
            owned=std::make_shared<MutableUnitMap>(UnitMapSeed{map->cells,map->slots,map->fallback,map->floorState,map->membershipResident,map->buffer4,map->buffer10,map->width,map->height,map->levelHeight});
            GroundDriveProcessState initial;initial.movement.actor={at,0,0};initial.movement.reached5a0=1;
            initial.movement.body.desired=initial.movement.body.start=std::uint16_t(heading);initial.movement.body.rate=std::uint16_t(rot*256);
            initial.destination=dest;initial.route=route;initial.percentage=numbers[0];initial.retryPadding=7;
            GroundDriveProcessServices supplied;
            supplied.advance.notify=[](int n){out('N',n);};supplied.advance.postCell=[]{out('P');};
            supplied.noRoute=[]{out('B','J','V',0,1);};supplied.squareRoot=[&](double n){return tableSqrt(light,n);};
            for(unsigned i=0;i<12;++i)supplied.trackSpeed[i]=float(numbers[1]*(1.-i/16.));supplied.uphill=numbers[2];supplied.downhill=numbers[3];
            const auto actorStore=[](int off,int n){out('A',off,std::uint32_t(n));};
            initialContext=std::make_unique<TerrainUnitContext>(owned,std::move(supplied),initial,actorStore,
                [&](char k,int id,int off,std::uint32_t v){if(!drawing)out('w',k,id,off,v);else if(k=='c'&&off==0x24&&fallbackObserver)fallbackObserver(owned->fallback.input.position);},
                [&](char k,Coord p){if(!drawing){out(k,p.x,p.y);if(k=='C'||k=='F')out(p.z);}});
            context=initialContext.get();
            GroundDriveProcessState parked;parked.movement.actor={parkedAt,0,0};parked.movement.reached5a0=1;
            parked.movement.body.desired=parked.movement.body.start=std::uint16_t(parkedHeading);parked.movement.body.rate=std::uint16_t(rot*256);
            UnitDiscoveryActor discovery;discovery.owner=0;discovery.mission98=2;discovery.queuedA0=-1;discovery.queuedA4=255;
            Facing turret;turret.desired=turret.start=std::uint16_t(t1);turret.rate=std::uint16_t(rot*256);
            context->bindParked(parked,{},discovery,[](int off,int n){out('r','A',off,std::uint32_t(n));},{turret});
            if(!twoProcesses)context->enableAdmission({std::uint8_t(crusher),0,0,true,{first,second}},
                [&](char k,Coord p){if(!drawing){out(k,p.x,p.y);if(k=='C'||k=='F')out(p.z);}},
                [](char k,int a,int b,int c){out('a',k,a,b,c);},[](int off,int n){out('a','L',off,std::uint32_t(n));});
            tick=start;
            for(int id:{1,0}){
                auto& actor=id?context->parked->state:context->state;const auto& services=id?context->parked->services:context->services;
                const GroundStateStore stores=id?GroundStateStore{[](int off,int n){out('r','A',off,std::uint32_t(n));}}:GroundStateStore{actorStore};
                setActorRelativeHeight(actor.movement.actor,0,416,services.advance.ground,stores);
                unlimboDriveRamp(actor.ramps,[&]{(void)services.cell(actor.movement.actor.position);return services.cell(actor.movement.actor.position).ramp;},tick,7,
                    [id](int off,int n){if(id)out('r','L',off+4,std::uint32_t(n));else out('L',off+4,std::uint32_t(n));});
                services.advance.ground.mark(1);
            }
            for(unsigned id=0;id<2;++id){actors[id].turret=std::uint16_t(id?t1:t0);actors[id].pitch=14336;actors[id].ready=true;}
            if(twoProcesses){
            auto immutable=std::make_shared<const RenderData>(light);
            Facing turret0;turret0.desired=turret0.start=std::uint16_t(t0);turret0.rate=std::uint16_t(rot*256);
            world=std::make_unique<OwnedUnitWorld>(std::move(initialContext),driveData,
                OwnedUnitWorldNumerics{immutable,[immutable](double n){return tableSqrt(*immutable,n);}},ownershipInputs,turret0);
            // Rejected associations must not query or mutate the live owners.
            for(int test=0;test<(advanceAdmission?7:6);++test){
                auto records=std::array<GroundDriveProcessState*,2>{&context->state,&context->parked->state};
                auto services=std::array<GroundDriveProcessServices,2>{context->services,context->parked->services};
                if(test==0)records[1]=records[0];
                if(test==1)records[0]=nullptr;
                if(test==2)services[1].trackSpeed[0]=std::nextafter(services[0].trackSpeed[0],100.0f);
                int queries=0;bool refused=false;
                auto foreign=owned->clone();auto binding=context->map->input();
                std::vector<int> alteredSlots(binding.slots.begin(),binding.slots.end());
                if(test==5){
                    auto selected=std::find_if(alteredSlots.begin(),alteredSlots.end(),[](int n){return n>=0;});
                    if(selected==alteredSlots.end())throw std::runtime_error("No canonical Cell index for guard");
                    *selected=-1;
                }
                PreparedMembershipMap badMap{binding.cells,test==5?std::span<const int>(alteredSlots):binding.slots,
                    test==4?foreign->fallback:binding.fallback,binding.floor,binding.resident,
                    binding.buffer4,binding.buffer10,binding.width,binding.height,binding.levelHeight};
                auto inputs=ownershipInputs;
                if(test==6)inputs.advancePolicy=static_cast<OwnedUnitAdvancePolicy>(99);
                try{OwnedUnitProcesses bad(test==3?foreign->input():badMap,*context->unit,records,services,*driveData,inputs,
                    [&](char,Coord){++queries;});}
                catch(const std::invalid_argument&){refused=true;}
                if(!refused||queries)throw std::runtime_error("Owned Process association guard failed");
                ++identityGuards;
            }
            for(int id:{0,1})world->actor(id).wait={0,0,0};
            bool refused=false;
            try{OwnedUnitWorldCall call;call.failedRoute=[](int){};call.notify=[](int){};call.postCell=[]{ };call.noRoute=[]{ };world->process(2,speed,tick,7,call);}
            catch(const std::invalid_argument&){refused=true;}
            if(!refused)throw std::runtime_error("Unknown owned actor was accepted");
            ++unknownActorGuards;
            }
        }else if(op=='J'){
            if(!twoProcesses)throw std::invalid_argument("Two-Process mode required");
            if(!world)throw std::invalid_argument("Owned Process initialization required");
            auto& a=context->parked->state;auto next=a;
            input>>next.destination.x>>next.destination.y>>next.destination.z;
            for(auto& n:next.route)input>>n;
            input>>next.retryStart>>next.retryPadding>>next.retryRemaining;
            if(!input||next.route.back()!=-1||std::any_of(next.route.begin(),next.route.end(),[](int n){return n<-1||n>7;}))
                throw std::invalid_argument("Invalid owned actor1 route/timer input");
            a=next;
            for(int id:{0,1})world->actor(id).wait={0,0,0};
        }else if(op=='X'){
            int id=-1,when=0;input>>id>>when;
            if(!advanceAdmission||!world||!input||id<0||id>1)
                throw std::invalid_argument("Owned Advance preview initialization required");
            advancePreviewGuards+=owned_advance_check::check(*world,driveData,light,ownershipInputs,id,when,speed,[&]{
                std::ostringstream capture;
                capture<<int(actors[0].stage.staging)<<' '<<int(actors[1].stage.staging)<<' '
                    <<state.stagingSurface<<' '<<state.image.dirty.x<<' '<<state.image.dirty.y<<' '
                    <<state.image.dirty.width<<' '<<state.image.dirty.height<<' '<<digest(state.image.pixels)<<' '
                    <<state.pool.cursor<<' '<<digest(state.pool.bytes)<<' '
                    <<digestWords(colors)<<' '<<digestWords(depth)<<' '<<digestWords(alpha);
                for(const auto* index:std::array<const VoxelSnapshotIndex*,4>{&type.lit.parts[0],&type.lit.parts[1],&type.lit.parts[2],&type.shadow}){
                    capture<<' '<<index->size()<<' '<<index->capacity()<<' '<<index->sorted()<<' '<<index->hotKey().has_value()<<' '<<index->hotKey().value_or(0);
                    auto diagnostic=*index;
                    for(auto key:index->keys())capture<<' '<<key<<' '<<diagnostic.find(key).value();
                }
                return capture.str();
            });
        }else if(op=='K'){
            // Authored initial Drive inputs only. Initial location and actual
            // Mark/membership are retained; no Cell list is supplied here.
            int id=-1,track=-1,index=-1,acc=0,driving=-1;Coord head;
            input>>id>>head.x>>head.y>>head.z>>track>>index>>acc>>driving;
            if(!advanceAdmission||!world||!input||id<0||id>1||track<0||track>=64||
               index<0||index>=128||driving<0||driving>1)
                throw std::invalid_argument("Invalid initial owned Advance Drive input");
            auto& v=world->actor(id).state.movement;
            v.head=head;v.track=track;v.index=index;v.accumulator=acc;v.driving=driving!=0;
        }else if(op=='T'){
            if(twoProcesses){
            int id=-1;input>>id>>tick;if(!context||!world||!input)throw std::invalid_argument("Owned initialization required");
            if(!advanceAdmission&&id==1&&tick==117&&context->parked->state.destination.y==3968){
                const auto capture=[&]{
                    std::ostringstream stream;auto* saved=std::cout.rdbuf(stream.rdbuf());
                    try{snapshot();}catch(...){std::cout.rdbuf(saved);throw;}
                    std::cout.rdbuf(saved);return stream.str();
                };
                const auto before=capture();
                for(int wanted:{6,7}){
                    auto copy=world->clone();
                    if(wanted==6){
                        auto& other=copy->actor(0).state;auto& movement=other.movement;
                        const auto settled=movement.body.current(tick);
                        movement.body.desired=movement.body.start=settled;movement.body.duration=0;
                        other.destination={};movement.head={};
                    }else{
                        // Explicitly supplied zero-speed type on an isolated
                        // copy; this is not a mutation of the live shared type.
                        auto base=copy->context().clone();
                        auto owner=std::unique_ptr<TerrainUnitContext>(static_cast<TerrainUnitContext*>(base.release()));
                        owner->services.trackSpeed.fill(0.0f);owner->parked->services.trackSpeed.fill(0.0f);
                        auto immutable=std::make_shared<const RenderData>(light);
                        const auto wait0=copy->actor(0).wait,wait1=copy->actor(1).wait;
                        copy=std::make_unique<OwnedUnitWorld>(std::move(owner),driveData,
                            OwnedUnitWorldNumerics{immutable,[immutable](double n){return tableSqrt(*immutable,n);}},ownershipInputs,copy->actor(0).turret);
                        copy->actor(0).wait=wait0;copy->actor(1).wait=wait1;
                    }
                    int lastAdmission=-1;bool refused=false;
                    try{OwnedUnitWorldCall call;call.failedRoute=[](int){};call.notify=[](int){};call.postCell=[]{ };call.noRoute=[]{ };
                        call.decision=[&](char kind,int result){if(kind=='D')lastAdmission=result;};
                        copy->process(1,speed,tick,7,call);}
                    catch(const UnsupportedGroundAdmission& failure){
                        if(failure.result!=wanted||lastAdmission!=wanted)throw;
                        refused=true;
                    }
                    if(!refused||capture()!=before)throw std::runtime_error("Joined refusal clone isolation failed");
                    ++refusalCloneGuards;
                }
            }
            OwnedUnitWorldCall call;
            call.notify=[](int n){out('N',n);};call.postCell=[]{out('P');};call.noRoute=[]{out('B','J','V',0,1);};
            call.query=[](char k,Coord p){out(k,p.x,p.y);if(k=='C'||k=='F')out(p.z);};
            call.actorStore=[id](int off,int value){if(id)out('r','A',off,std::uint32_t(value));else out('A',off,std::uint32_t(value));};
            call.rampStore=[id](int off,int value){out("o",'L',id,off+4,std::uint32_t(value));};
            call.driveStore=[id](int off,int value){out("o",'L',id,off,std::uint32_t(value));};
            call.failedRoute=[id](int option){out("o",'B',id,option);};
            call.decision=[id](char kind,int result){out("o",kind,id,result);};
            const auto result=world->process(id,speed,tick,7,call);
            out("o",'R',id,int(result));
            if(id==0&&tick==116){
                const auto capture=[&]{
                    std::ostringstream stream;auto* saved=std::cout.rdbuf(stream.rdbuf());
                    try{snapshot();}catch(...){std::cout.rdbuf(saved);throw;}
                    std::cout.rdbuf(saved);return stream.str();
                };
                const auto before=capture();
                auto copy=world->clone();
                if(copy->context().map.get()==context->map.get()||!copy->context().parked)
                    throw std::runtime_error("Owned world warm clone owner missing");
                OwnedUnitWorldCall silent;silent.failedRoute=[](int){};silent.notify=[](int){};silent.postCell=[]{ };silent.noRoute=[]{ };
                for(int actor:{0,1})copy->process(actor,speed,tick+1,7,silent);
                if(capture()!=before)throw std::runtime_error("Owned Process warm clone modified source owners");
                ++warmCloneGuards;
            }
            }else{
            input>>tick;if(!context||!input)throw std::invalid_argument("Owned initialization required");
            const auto actorStore=[](int off,int n){out('A',off,std::uint32_t(n));};
            const auto rampStore=[](int off,int n){out('L',off+4,std::uint32_t(n));};
            const auto result=context->process(*driveData,speed,tick,7,actorStore,rampStore);
            const auto& a=context->state;out('S',result,a.movement.actor.position.x,a.movement.actor.position.y,a.movement.actor.position.z,
                a.ramps.current,a.ramps.previous,a.ramps.start,a.ramps.padding,a.ramps.remaining,a.ramps.duration);
            }
        }else if(op=='D'){

            if(!map)throw std::invalid_argument("Map must be prepared before Unit draw");
            PreparedFootDepthInputs prepared;std::uint64_t scale=0;
            int id=-1;input>>id>>scale;
            if(!reset||id<0||id>1||!actors[0].ready||!actors[1].ready)throw std::invalid_argument("Both supplied shared actors required");
            auto& actor=actors[std::size_t(id)];
            if(!context)throw std::invalid_argument("Owned initialization required");
            const auto& live=id?context->parked->state:context->state;
            actor.at=live.movement.actor.position;actor.body=live.movement.body.current(tick);actor.pose.ramp=live.ramps;actor.pose.tick=tick;
            actor.pose.type330=30.5;actor.pose.type338=24.25;
            actor.turret=world->actor(id).turret.current(tick);
            OwnedUnitDrawingMap drawMap(*owned,*context->unit);drawing=true;
            prepared.unit.location=actor.at;
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
            if(seed<0||seed>100000||contact!=0)throw std::invalid_argument("Owned contact association must remain empty");
            prepared.unit.facing={};prepared.unit.facing.desired=prepared.unit.facing.start=std::uint16_t(body);
            std::vector<std::uint32_t> queries;
            const auto event=[&](std::initializer_list<std::uint32_t> v){queries.insert(queries.end(),v);};
            const auto fallbackStore=[&](MapInputPosition p){event({0xffffffffu,0,prepared_fixture::packed(p)});};fallbackObserver=fallbackStore;
            PreparedFootDepthWorld binding;binding.unit.tiles=map->tiles;binding.unit.overlays=map->overlays;
            binding.unit.cell=[&](MapInputPosition p)->const MapCellAttributes&{
                event({304,prepared_fixture::packed(p)});return drawMap.cell(p);
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
                return drawMap.coordinate(p);
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
                event({502});const int h=drawMap.relative(prepared.unit.location);
                event({503,unsigned(h)});return h;
            };
            ground.point=[&]{event({507});return PixelPoint{0,heightPixels(prepared.unit.heightScale,ground.relativeHeight())};};
            ground.observeShadow=[&](const UnitVoxelShadowRequest&,PixelPoint p){event({508,unsigned(p.x),unsigned(p.y)});};
            const auto location=prepared.unit.location;
            if(location.x<0||location.y<0||location.x>=512*256||location.y>=512*256||
               !owned->table[std::size_t(location.y/256)*512+std::size_t(location.x/256)])
                throw std::invalid_argument("Ground draw requires a resident current Cell");
            queries.clear(); // Fixture preflight is outside the original draw trace.
            s.cell=[&]{const auto p=prepared.unit.location;event({405,unsigned(p.x),unsigned(p.y),unsigned(p.z)});
                drawMap.coordinate(p);};
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
            out("queries",prepared_fixture::packed(owned->fallback.input.position),digest(queries));
            Bytes floorBytes{owned->floor.flags};
            const auto append=[&](double v){const auto n=std::bit_cast<std::uint64_t>(v);for(unsigned i=0;i<8;++i)floorBytes.push_back(std::uint8_t(n>>(i*8)));};
            append(owned->floor.height);append(owned->floor.scale);
            for(const auto& plane:owned->floor.planes)for(double v:{plane.x,plane.y,plane.offset,plane.limit,plane.add})append(v);
            out("floor",digest(floorBytes));drawing=false;
        }else throw std::invalid_argument("Unknown owned world command");
        if(context) snapshot();
        if(!input)throw std::invalid_argument("Incomplete owned world command");input>>std::ws;if(!input.eof())throw std::invalid_argument("Trailing owned world command");std::cout<<'\n';
    }
    if(twoProcesses){std::cerr<<"Owned world guards: "<<identityGuards<<"; unknown actor: "<<unknownActorGuards
        <<"; warm clone pairs: "<<warmCloneGuards<<"; actual Advance6/7 clone refusals: "<<refusalCloneGuards;
        if(advanceAdmission)std::cerr<<"; Advance preview checks: "<<advancePreviewGuards;
        std::cerr<<": PASS\n";}
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
