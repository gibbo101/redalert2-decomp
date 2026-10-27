// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
// Research fixture storage only; no production actor or world abstraction.
#include "sim/MissionBuildingTarget.hpp"
#include "sim/RevealArea.hpp"
#include "sim/UnitDiscovery.hpp"
#include <memory>
#include <iostream>
#include <limits>
#include <type_traits>
#include <cmath>
struct WaypointBuildingServicesFixture {
    WaypointBuildingServicesFixture()=default;
    WaypointBuildingServicesFixture(const WaypointBuildingServicesFixture&)=delete;
    WaypointBuildingServicesFixture& operator=(const WaypointBuildingServicesFixture&)=delete;
    WaypointBuildingServicesFixture(WaypointBuildingServicesFixture&&)=delete;
    WaypointBuildingServicesFixture& operator=(WaypointBuildingServicesFixture&&)=delete;
    static constexpr std::array<int,14> offsets{0xfc,0x108,0x1b0,0x208,0x20c,0x228,0x22c,0x230,0x238,0x23c,0x27c,0x384,0x3f8,0xa8};
    static constexpr std::array<int,17> typedOffsets{0x418,0x41c,0x438,0x440,0x474,0x490,0x494,0x498,0x4b8,0x4bc,0x4c0,0x4c4,0x4c8,0x4d4,0x4e8,0x580,0x5a8};
    struct Row {
        std::array<const void*,14> links{};
        std::array<const void*,17> typed{};
        std::array<const void*,8> weapons{};
        std::array<std::array<const void*,4>,7> backing{};
        std::array<std::span<const void*>,7> slots{};
        std::array<std::int32_t,7> counts{};
        std::array<int,7> identities{};
        std::array<std::unique_ptr<ra2::MissionExpirationVector<const void*>>,7> vectors;
        std::int32_t start=-1,padding=-91,duration=20,wordA8=123,health=50;
        std::uint8_t byte5BA=255,byte530=1,byte59C=1,byte404=255,byte170=0;
        std::int32_t pending9C=-1,word3FC=0,word310=0;
    };
    std::array<Row,34> rows{};
    std::array<int,3> houses{};
    int type=0,serviceIdentity=0,controllerIdentity=0,mode=0;
    std::uint8_t type1217=1,type11FE=1,type1206=0;
    std::int32_t typeC6C=1;
    double power=0.;

    const std::int32_t strength=100,zeroHealth=0;
    std::int32_t frame=0,session=0,padding=-91,tagHealth=1;
    std::uint8_t tagFlags=0,byte7D=1,typeC08=1,global=1;
    double threshold=.5;
    const void* nullPointer=nullptr;
    const void* recipient=this;
    ra2::Coord emptyCoordinates{}; // Live839CA8/AC/B0 globals, not Tag+88.
    bool radioHasLinks(int id)const {
        const auto& r=rows.at(std::size_t(id));
        for(int i=0;i<r.counts[0];++i)if(r.backing[0].at(std::size_t(i)))return true;
        return false;
    }
    template<class Actors> void bind(std::array<ra2::UnitDiscoveryActor,34>& discovered,
            Actors& actors,std::array<ra2::MissionTagState*,34>& objectTags,
            const ra2::MissionTagExpiredAbstract& expired,const void*& expiredNext,ra2::RevealAreaWorld& world,
            int seed,std::array<ra2::MissionTagExpirationRecipient,34>& recipients,
            const ra2::MissionTagStore& inheritedStore) {
        if(mode<0||mode>4)throw std::invalid_argument("Building service mode differs");
        type1206=std::uint8_t(mode&1);
        power=mode==0?0.:mode==1?1.:mode==2?std::numeric_limits<double>::quiet_NaN():mode==3?std::numeric_limits<double>::infinity():std::nextafter(1.,0.);
        frame=seed;session=seed%2;tagHealth=(seed&4)?0:1;
        emptyCoordinates={5120+128,5120+128,0};
        if(&expiredNext!=&expired.link30)throw std::invalid_argument("Tag link owner differs");
        // The closures own no copied Owner or Mission values.
        for(int id=0;id<34;++id) {
            auto& r=rows[std::size_t(id)];
            for(int j=0;j<14;++j)r.links[std::size_t(j)]=(j==3||j==7||j==8||j==13)?nullptr:expired.identity;
            r.links[0]=(id%3==0)?expired.identity:nullptr;
            r.health=50+id;r.weapons.fill(expired.identity);
            r.typed.fill(expired.identity);r.typed[0]=&type;r.typed[8]=nullptr;
            r.typed[15]=(id%3==0)?expired.identity:nullptr;r.typed[16]=&type;
            for(int v=0;v<7;++v) {
                r.backing[std::size_t(v)]={expired.identity,nullptr,expired.identity,nullptr};
                r.counts[std::size_t(v)]=v==0?(id%3==0?2:id%3==1?0:-1):3;
                r.slots[std::size_t(v)]=r.backing[std::size_t(v)];
                r.vectors[std::size_t(v)]=std::make_unique<ra2::MissionExpirationVector<const void*>>(ra2::MissionExpirationVector<const void*>{r.counts[std::size_t(v)],r.slots[std::size_t(v)],&r.identities[std::size_t(v)]});
            }
        }
        for(int id=0;id<34;++id){auto& r=rows[std::size_t(id)];
            r.pending9C=id%3==0?-1:id%4==1?19:0;r.word310=90+id;
            r.byte170=std::uint8_t(id%3==0?255:0);r.byte530=std::uint8_t(id%3!=0);r.byte59C=std::uint8_t(id%3!=1);r.word3FC=id%5==0?1:0;
            if(id&1){r.links[6]=nullptr;r.links[8]=&serviceIdentity;r.weapons[0]=&controllerIdentity;r.counts[6]=1+id%3;}
        }
        ra2::MissionTagStore store=[this,&discovered,&expired,inheritedStore,&world](const void* owner,std::int64_t off,std::uint32_t value,const void* pointer) {
            auto pointerId=[&](const void* p)->int{if(!p)return 0;if(p==expired.identity)return 2;if(p==&type)return 9;if(p==&controllerIdentity)return 10;if(p==&serviceIdentity)return 11;for(int i=1;i<3;++i)if(p==&houses[std::size_t(i)])return 20+i;for(auto* cell:world.primaryCells)if(cell&&p==cell)return 200+cell->identity;if(p==world.fallback)return 216;for(int i=0;i<34;++i)if(p==&discovered[std::size_t(i)])return 100+i;throw std::invalid_argument("Unknown typed pointer");};
            for(int id=0;id<34;++id) {
                auto& row=rows[std::size_t(id)];
                for(int v=0;v<7;++v)if(owner==&row.identities[std::size_t(v)]){std::cout<<" XW "<<id<<' '<<v<<' '<<off<<' '<<(pointer?std::uint32_t(pointerId(pointer)):value)<<' ';return;}
                if(owner==&row.links[0]){std::cout<<" XW "<<id<<" 7 252 "<<pointerId(pointer)<<' ';return;}
                if(owner==&discovered[std::size_t(id)]&&off!=0x34&&off!=0x30){std::cout<<" XW "<<id<<" 8 "<<off<<' '<<(pointer?std::uint32_t(pointerId(pointer)):value)<<' ';return;}
            }
            inheritedStore(owner,off,value,pointer);
        };
        for(int id=0;id<34;++id) {
            auto& row=rows[std::size_t(id)];auto& actor=discovered[std::size_t(id)];
            ra2::MissionRadioTagExpiration radio{{objectTags[std::size_t(id)],actors[std::size_t(id)].next,&actor},*row.vectors[0]};
            ra2::MissionExpirationChain passengers{row.links[0],&row.links[0],[&expired,&expiredNext](const void* p)->const void*&{if(p!=expired.identity)throw std::invalid_argument("Foreign passenger");return expiredNext;},4};
            ra2::MissionExpirationOwnerView owner{[&,id]()->const void*{const auto n=discovered[std::size_t(id)].owner;return n?&houses.at(std::size_t(n)):nullptr;},[&,id](const void* p){int n=0;for(int i=1;i<3;++i)if(p==&houses[std::size_t(i)])n=i;if(p&&!n)throw std::invalid_argument("Foreign discovery Owner");discovered[std::size_t(id)].owner=n;}};
            ra2::MissionTechnoTagExpiration techno{radio,passengers,row.links[1],row.links[2],owner,row.links[3],row.links[4],row.links[5],row.links[6],row.links[7],row.links[8],row.links[9],row.weapons,row.links[10],row.links[11],row.links[12],row.start,row.padding,row.duration,actor.mission98,row.wordA8,actor.field372,row.byte5BA,*row.vectors[1],*row.vectors[2],*row.vectors[3]};
            ra2::MissionTechnoTagExpirationServices services{frame,session,padding};
            services.setTarget370=[&,id](const void* p){if(p)throw std::invalid_argument("Non-null target");std::cout<<" XS target "<<id<<' ';rows[std::size_t(id)].links[5]=nullptr;};
            services.retryRange=[this,id](int a,int b){if(a!=4||b!=8)throw std::invalid_argument("Retry range differs");std::cout<<" XS range "<<id<<' ';return 4+id%5;};
            services.predicate1E4=[id]{std::cout<<" XS p1 "<<id<<' ';return std::uint8_t(0);};
            services.predicateC0=[id]{std::cout<<" XS pc "<<id<<' ';return std::uint8_t(0);};
            services.kind2C=[id]{std::cout<<" XS kind "<<id<<' ';return id&1?6:15;};
            ra2::MissionFootTagExpiration foot{techno,row.typed[11],row.typed[15],row.typed[12],row.typed[7],row.typed[5],row.typed[6],row.typed[9],row.typed[8],row.typed[16],actor.queuedA0,*row.vectors[4],*row.vectors[5]};
            ra2::MissionFootTagExpirationServices footServices{global};
            footServices.missionRead=[]{std::cout<<"D g 0 ";};
            footServices.record=[this,&expired](const void* p)->ra2::MissionExpirationRecord{if(p==expired.identity)return {tagHealth,tagFlags,byte7D,typeC08,nullPointer,recipient};if(p==&type)return {zeroHealth,tagFlags,tagFlags,typeC08,nullPointer,nullPointer};throw std::invalid_argument("Foreign expiration record");};
            footServices.nestedExpiration28=[&,id](const void* p,const void* subject,std::uint32_t raw){if(p!=this||subject!=expired.identity||raw!=1)throw std::invalid_argument("Nested arguments differ");std::cout<<" XS nested "<<id<<' ';rows[std::size_t(id)].typed[16]=expired.identity;};
            footServices.coordinates48=[this,&expired](const void* p){if(p!=expired.identity)throw std::invalid_argument("Tag point differs");std::cout<<" XTCOORD ";return emptyCoordinates;};
            footServices.cell548070=[&world](ra2::TerrainCellPoint p)->const void*{return &ra2::revealAreaMapCell(p,world);};
            ra2::MissionBuildingTagExpiration building{techno,row.typed[2],row.typed[3],row.typed[1],row.typed[13],row.typed[14],row.typed[4],row.typed[0],std::span(row.typed).subspan(10,3),row.health,*row.vectors[6]};
            ra2::MissionBuildingTagExpirationServices buildingServices{threshold};
            buildingServices.strength84=[this,id]()->const std::int32_t&{std::cout<<" XS strength "<<id<<' ';return strength;};
            buildingServices.animationFirstByte=[](const void*,int){return std::uint8_t(1);};
            buildingServices.animation44CA60=[id](const void*,int off,int damaged){std::cout<<" XS animation "<<id<<' '<<off<<' '<<damaged<<' ';};
            if(id&1){
                ra2::MissionBuildingTarget target{&actor,row.health,actor.mission98,row.pending9C,actor.queuedA4,row.byte530,row.counts[6],row.word3FC,row.typed[0],owner,row.byte59C,row.byte404,row.links[5],row.links[8],row.word310,row.weapons[0],row.links[6]};
                ra2::MissionBuildingTargetServices effects;
                effects.type=[this](const void* p)->ra2::MissionBuildingTargetType{if(p!=&type)throw std::invalid_argument("Foreign Building type");return {type1217,typeC6C,type11FE,type1206};};
                effects.housePower4E8330=[this,id](const void* p){int house=0;for(int i=1;i<3;++i)if(p==&houses[std::size_t(i)])house=i;if(!house)throw std::invalid_argument("Foreign Building power Owner");std::cout<<" BS power "<<id<<' '<<house<<' ';if(mode==1){rows[std::size_t(id)].pending9C=19;rows[std::size_t(id)].counts[6]=2;}return power;};
                effects.clear68A490=[this,id,&expired](const void* p,const void* q){if(p!=&serviceIdentity||q)throw std::invalid_argument("Building service arguments differ");std::cout<<" BS clear "<<id<<' ';if(mode==2)rows[std::size_t(id)].links[5]=expired.identity;};
                effects.weaponIndex2B8=[this,id](const void* p){if(p)throw std::invalid_argument("Nonnull weapon target");std::cout<<" BS index "<<id<<' ';if(mode==3)rows[std::size_t(id)].counts[6]=1;return -id;};
                effects.weapon350=[id](const void* p,std::int32_t index){if(p||index!=-id)throw std::invalid_argument("Weapon permission arguments differ");std::cout<<" BS permission "<<id<<' '<<index<<' ';return std::uint8_t((id/2)%3==0?0:id%4==1?256:257);};
                effects.releaseF0=[this,id](const void* p){if(p!=&controllerIdentity)throw std::invalid_argument("Foreign attachment");std::cout<<" BS release "<<id<<' ';if(mode==4)rows[std::size_t(id)].weapons[0]=&controllerIdentity;};
                services.setTarget370=[target,effects,store](const void* p){ra2::setMissionBuildingNullTarget(target,p,effects,store);};
                services.predicate1E4=[target]{return ra2::missionTargetPending1E4(target.pending9C);};
                services.action1E0=[target,effects,store]{(void)ra2::resumeMissionBuildingNullTarget(target,effects,store);};
                services.predicateC0=[this,id]{return ra2::missionTargetDisguisedC0(rows[std::size_t(id)].byte170);};
                services.service68A560=[this,id,&expired](const void* p,const void* subject){if(p!=&serviceIdentity||subject!=expired.identity)throw std::invalid_argument("Expiration service arguments differ");std::cout<<" BS expiration "<<id<<' ';};
                services.queryCC=[](std::int32_t n){return ra2::missionBuildingQueryCC(std::uint32_t(n));};
                buildingServices.strength84=[this,target]()->const std::int32_t&{if(ra2::missionBuildingType84(target.type418)!=&type)throw std::invalid_argument("Foreign strength type");return strength;};
            }
            recipients[std::size_t(id)]=id&1?ra2::bindMissionBuildingTagExpiration(building,expired,tagFlags,services,buildingServices,store):ra2::bindMissionInfantryTagExpiration(foot,expired,tagFlags,services,footServices,store);
        }
    }
    static void guards() {
        int h1=0,h2=0;int owner=1;
        ra2::MissionExpirationOwnerView view{[&]()->const void*{return owner==1?&h1:owner==2?&h2:nullptr;},[&](const void* p){owner=p==&h1?1:p==&h2?2:0;}};
        auto copy=view;owner=2;if(static_cast<const void*>(copy)!=&h2)throw std::invalid_argument("Mirrored Owner read");copy=nullptr;if(owner)throw std::invalid_argument("Mirrored Owner write");
        const void* pointer=&h1;ra2::MissionExpirationOwnerView pointerView(pointer);pointer=&h2;if(static_cast<const void*>(pointerView)!=&h2)throw std::invalid_argument("Pointer Owner snapshot");pointerView=nullptr;if(pointer)throw std::invalid_argument("Pointer Owner store");
        bool refused=false;try{ra2::MissionExpirationOwnerView bad({},{});}catch(const std::invalid_argument&){refused=true;}if(!refused)throw std::invalid_argument("Missing Owner accessors admitted");
        WaypointBuildingServicesFixture fixture;std::array<ra2::UnitDiscoveryActor,34> actors{};
        struct Resident{const void* next=nullptr;};std::array<Resident,34> residents{};
        std::array<ra2::MissionTagState*,34> tags{};std::int32_t persistence=0,instances=10;std::uint8_t executing=0;
        ra2::MissionTagType type{persistence};auto* typePtr=&type;ra2::MissionTagTrigger* first=nullptr;
        ra2::MissionTagState tag{typePtr,first,instances,executing},foreign{typePtr,first,instances,executing};
        const void* next=nullptr;ra2::MissionTagExpiredAbstract expired{tag,&tag,next};
        std::vector<ra2::RevealAreaCell*> table(262144);ra2::RevealAreaCell fallback{};ra2::RevealAreaWorld world{0,0,table,table,&fallback};
        std::array<ra2::MissionTagExpirationRecipient,34> recipients{};int stores=0,queries=0;
        world.query=[&](char,ra2::TerrainCellPoint,int){++queries;};
        for(auto& actor:actors)actor.owner=1;
        fixture.bind(actors,residents,tags,expired,next,world,0,recipients,[&](const void*,std::int64_t,std::uint32_t,const void*){++stores;});
        if(stores||queries||instances!=10)throw std::invalid_argument("Binding mutated owners");
        fixture.tagFlags=1;refused=false;try{recipients[0].expired(tag,1);}catch(const std::invalid_argument&){refused=true;}if(!refused||stores||queries)throw std::invalid_argument("Live Tag flag refusal failed");
        fixture.tagFlags=0;refused=false;try{recipients[1].expired(foreign,1);}catch(const std::invalid_argument&){refused=true;}if(!refused||stores||queries)throw std::invalid_argument("Foreign Tag refusal failed");
        const auto otherCount=fixture.rows[3].counts[6];const auto other404=fixture.rows[3].byte404;
        actors[1].owner=2;recipients[1].expired(tag,1);
        if(actors[1].owner!=2||fixture.rows[1].typed[2]||fixture.rows[1].links[5]||instances!=10)throw std::invalid_argument("Returned binding lost live owners");
        const auto& row=fixture.rows[1];
        if(actors[1].mission98!=19||actors[1].queuedA4||row.pending9C!=-1||row.byte404||row.word310||row.weapons[0]||row.counts[6]!=1||queries)
            throw std::invalid_argument("Returned Building services lost actual mission/queue/count owners");
        if(fixture.rows[3].counts[6]!=otherCount||fixture.rows[3].byte404!=other404)
            throw std::invalid_argument("Building services wrote another actor");
    }
    template<class Actors> void printServices(const Actors& actors)const {
        std::cout<<" SERVICES";for(int id=0;id<34;++id){const auto& r=rows[std::size_t(id)];std::cout<<' '<<actors[std::size_t(id)].mission98<<' '<<r.pending9C<<' '<<unsigned(r.byte404)<<' '<<r.word310<<' '<<unsigned(r.byte170)<<' '<<unsigned(actors[std::size_t(id)].queuedA4);}
    }
    void print()const {
        std::cout<<" TYPED";
        for(const auto& r:rows){for(int j=0;j<14;++j)if(j!=13)std::cout<<' '<<(r.links[std::size_t(j)]?2:0);for(auto p:r.typed)std::cout<<' '<<(p==&type?9:p?2:0);for(auto p:r.weapons)std::cout<<' '<<(p?2:0);std::cout<<' '<<r.start<<' '<<r.padding<<' '<<r.duration<<' '<<r.health<<' '<<unsigned(r.byte5BA);for(auto n:r.counts)std::cout<<' '<<n;for(const auto& b:r.backing)for(auto p:b)std::cout<<' '<<(p?2:0);}
    }
};
static_assert(!std::is_move_constructible_v<WaypointBuildingServicesFixture>);
static_assert(!std::is_copy_constructible_v<WaypointBuildingServicesFixture>);
