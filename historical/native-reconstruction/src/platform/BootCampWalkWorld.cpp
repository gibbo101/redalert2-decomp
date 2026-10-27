// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TechnoThreat.hpp"
#include "sim/TechnoHouseTransfer.hpp"
#include "sim/ObjectGroundQueries.hpp"
#include "sim/InfantryMissionResume.hpp"
#include "sim/WalkMissionResume.hpp"
#include "sim/TechnoAbility.hpp"
#include "sim/TechnoNullNotification.hpp"
#include "sim/TechnoTypeCost.hpp"
#include "sim/TeamAdmission.hpp"
#include "sim/TeamCohesion.hpp"
#include "sim/TeamScript.hpp"
#include "assets/MapWallOwner.hpp"
#include "sim/TeamMembership.hpp"
#include "sim/TeamRecruitment.hpp"
#include "sim/MissionScriptState.hpp"
#include "sim/BuildingDiscovery.hpp"
#include "sim/HouseActorThreatCells.hpp"
#include "assets/MapCoordinateCell.hpp"
#include "platform/BootCampWalkWorld.hpp"
#include "platform/BootCampRadarActors.hpp"
#include "platform/BootCampMessages.hpp"
#include "assets/PreparedData.hpp"
#include "assets/VisibilityData.hpp"
#include "assets/InfantrySubcellData.hpp"
#include "assets/MessageColorData.hpp"
#include "render/Lighting.hpp"
#include "render/VoxelRaster.hpp"
#include "assets/MapCellChildren.hpp"
#include "sim/CellDirtyEffect.hpp"
#include "sim/PositionCloakEffect.hpp"
#include "sim/HouseMapRefresh.hpp"
#include "render/UnitTypeVisibility.hpp"
#include <bit>
#include <cmath>
#include <optional>
#include <sstream>
#include <tuple>
namespace ra2 {
namespace {
bool hasAbility(const std::string& value,const char* wanted){
    std::istringstream in(value);std::string token;
    while(std::getline(in,token,',')){
        const auto first=token.find_first_not_of(" \t\r\n");if(first==std::string::npos)continue;
        token=token.substr(first,token.find_last_not_of(" \t\r\n")-first+1);
        if(lower(token)==lower(wanted))return true;
    }
    return false;
}
}
BootCampWalkWorld::BootCampWalkWorld(const GameAssets& assets,const MissionDefinition& mission,
    const Ini& source,const Ini& rules,const Ini& art):assets_(assets),mission_(mission),source_(source),rules_(rules),art_(art),
    subcells_(readInfantrySubcellData(readFile(preparedDataPath(assets.engineDataSource,"infantry-subcell-data.bin")),assets.engineDataSource)),
    numbers_{assets.driveData->directionsToTargets,0,[&assets](double v){return tableSqrt(assets.renderData,v);},
        [&assets](double v){return tableSine(assets.rasterData,v);},[&assets](double v){return tableCosine(assets.rasterData,v);}} {
    if(assets.engineDataSource!=PatchedEngineSha||assets.mapName!="trn01t.map")throw std::invalid_argument("Walking requires supplied base Day1");
    // Complete constructor/INI parents, using the existing authored parser as
    // a supplied service. General Rules/map layering is not reconstructed here.
    // Refuse nonempty map overrides rather than guessing their precedence.
    for(const auto name:missionControlNames)if(!source.section(std::string(name)).empty())
        throw std::invalid_argument("Boot Camp mission-control map overrides remain unjoined");
    for(auto& record:missionControl_)initializeMissionControl(record);
    MissionControlIniServices missionIni;
    missionIni.hasSection=[&](auto name){return std::uint32_t(rules.hasSection(std::string(name)));};
    missionIni.boolean=[&](auto name,auto key,auto fallback){return rules.boolean(std::string(name),std::string(key),fallback);};
    missionIni.number=[&](auto name,auto key,double fallback){return rules.number(std::string(name),std::string(key),fallback);};
    // Inspected6524F2..65250D assigns each index immediately before its child.
    for(int i=0;i<30;++i){storeMissionControl(missionControl_[i],0,4,i);readMissionControl(missionControl_[i],missionIni);}
    initializeCellResidentKind6(residentSearch_);
    OriginalRounding rounding;numbers_.radiansPerFacing=assets.driveData->directionsToTargets.pi/-32767.;
    if(lower(rules.get("E1","Image"))!="gi"||lower(rules.get("E1","Locomotor"))!="{4a582744-9839-11d1-b709-00a024ddafd1}"||
       !source.section("E1").empty()||!source.section("GI").empty()||!rules.get("E1","SpeedType").empty()||
       rules.boolean("E1","JumpJet")||rules.integer("E1","Speed",-1)!=4||art.get("GI","Sequence").empty())
        throw std::invalid_argument("Only stock ordinary E1 Walk inputs are currently associated");
    bool accountingType=false;
    for(const auto& [index,name]:rules.section("InfantryTypes"))if(lower(name)=="e1"){
        if(accountingType)throw std::invalid_argument("Repeated E1 InfantryType index");
        type_.accountingIndex=std::stoi(index);accountingType=true;
    }
    if(!accountingType||type_.accountingIndex<0||type_.accountingIndex>=512)
        throw std::invalid_argument("Missing bounded E1 InfantryType index");
    type_.speed5a0=internalSpeed(rules.integer("E1","Speed"));type_.speedType5a4=0; // Explicit supplied Foot type association.
    type_.baseCost550=rules.integer("E1","Cost",-1);
    if(type_.baseCost550<0)throw std::invalid_argument("Missing supplied stock E1 cost");
    // This scene supplies country114=1. General country initialization and
    // inheritance remain unjoined; refuse entered overrides rather than ignore.
    for(const auto& [id,name]:mission.houses){
        const auto country=source.get(name,"Country");
        const auto parent=source.get(country,"ParentCountry",rules.get(country,"ParentCountry"));
        if(country.empty())throw std::invalid_argument("Missing supplied House country for cost");
        for(const auto& section:{country,parent})if(!section.empty()&&
            (!source.get(section,"CostInfantryMult").empty()||!rules.get(section,"CostInfantryMult").empty()))
            throw std::invalid_argument("Nonstock country cost startup requires recovery");
    }
    // Supplied Rules-to-Type initialization; inspected ability index16/keyB00.
    type_.guardAreaVeteran27c=hasAbility(rules.get("E1","VeteranAbilities"),"GUARD_AREA");
    type_.guardAreaElite28e=hasAbility(rules.get("E1","EliteAbilities"),"GUARD_AREA");
    type_.defaultGuardAreaB00=rules.boolean("E1","DefaultToGuardArea",0);
    type_.image598=0; // Shared valid image identity; actual image loading/constructor not recovered.
    if(rules.get("E1","Primary")!="M60"||rules.get("E1","Secondary")!="Para"||
       rules.get("E1","ElitePrimary")!="M60E"||rules.get("E1","EliteSecondary")!="ParaE"||
       rules.integer("E1","TurretCount",0)!=0)
        throw std::invalid_argument("Only stock E1 weapon-selection inputs are currently associated");
    auto weapon=[&](InfantryWeaponSelectionWeapon& slot,const std::string& name){
        if(rules.section(name).empty())throw std::invalid_argument("Missing stock E1 weapon record");
        slot.identity=&slot;slot.neverUse112=rules.boolean(name,"NeverUse");slot.areaFire126=rules.boolean(name,"AreaFire");
    };
    weapon(type_.weaponSelection.weapons[0],"M60");weapon(type_.weaponSelection.weapons[1],"Para");
    weapon(type_.weaponSelection.eliteWeapons[0],"M60E");weapon(type_.weaponSelection.eliteWeapons[1],"ParaE");
    threat598_=rules.integer("E1","ThreatPosed",0);
    sightRange_=rules.integer("E1","Sight",-1);
    veteranSight_=hasAbility(rules.get("E1","VeteranAbilities"),"SIGHT");
    eliteSight_=hasAbility(rules.get("E1","EliteAbilities"),"SIGHT");
    sightHeightDivisor_=104;veteranSightMultiplier_=rules.number("General","VeteranSight",1.);
    if(sightRange_<=0||!std::isfinite(veteranSightMultiplier_))throw std::invalid_argument("Unsupported E1 sight inputs");
    globals_.routeInterval=rules.number("AI","PathDelay",.01);globals_.veteranSpeed=rules.number("General","VeteranSpeed",1.2);
    prepared_=std::make_shared<PreparedTerrainMap>(assets.store,source,
        readMapRuntimeData(readFile(preparedDataPath(assets.engineDataSource,"map-runtime-data.bin"))),104,416,PreparedTerrainMapPolicy{.deferCellTags=true,.resourceValueOverrides=true});
    map_=std::make_unique<MutableUnitMap>(prepared_->unitSeed(),prepared_);cells_.resize(map_->cells.size()+1);
    for(unsigned l=0;l<12;++l){for(unsigned s=0;s<8;++s)speeds_[l*9+s]=std::bit_cast<std::uint32_t>(prepared_->land[l].speed[s]);
        speeds_[l*9+8]=prepared_->land[l].buildable;}
    for(const auto& [id,name]:mission.houses){
        if(id<0||id>=32)throw std::invalid_argument("Boot Camp House index outside supplied association");
        houseInputs_[id]={1};
    }
    std::map<int,std::pair<int,int>> structureSizes;
    const auto offsets=initialInfantrySubcellOffsets();std::uint32_t seed=0x71e220;
    random_.next2=103;for(auto& x:random_.table){seed=seed*1664525u+1013904223u;x=seed;}
    // Seed/record defaults/single-actor-per-Process scheduling are host startup.
    for(std::size_t i=0;i<mission.actors.size();++i){const auto& d=mission.actors[i];
        if(d.kind!=MissionActorKind::Infantry||lower(d.type)!="e1"){
            if(d.kind!=MissionActorKind::Structure){
                auto& foot=passiveFeet_[int(i)];footRegistry_.push_back(&foot);
                bool found=false;for(const auto& [h,name]:mission.houses)if(lower(name)==lower(d.house)){foot.mission.owner=h;found=true;break;}
                if(!found||d.health!=256)throw std::invalid_argument("Passive Foot startup outside full-health owner scope");
                if(!d.tag.empty()&&lower(d.tag)!="none"&&lower(d.tag)!="<none>"){
                    auto& tag=passiveTags_[lower(d.tag)];
                    if(!tag){tag=std::make_unique<BootCampFootTagOwner>();tag->persistence=mission.tags.at(lower(d.tag)).persistence;
                        for(const auto& actor:mission.actors)if(lower(actor.tag)==lower(d.tag))++tag->instances;}
                    foot.tag34=&tag->view;foot.mission.hasTag=true;
                }
                const auto mission=lower(d.mission);
                foot.mission.mission98=-1;
                for(std::size_t m=0;m<missionControlNames.size();++m)if(lower(std::string(missionControlNames[m]))==mission)foot.mission.mission98=int(m);
                if(foot.mission.mission98==-1)throw std::invalid_argument("Passive Foot mission startup unbound");
                foot.kind=d.kind==MissionActorKind::Infantry?15:1;
                if(foot.kind==1){bool foundType=false;for(const auto& [key,value]:rules.section("VehicleTypes"))if(lower(value)==lower(d.type))foundType=true;
                    if(!foundType)throw std::invalid_argument("Passive Units entry lacks supplied VehicleTypes association");}
                foot.health6C=rules.integer(d.type,"Strength",-1);
                if(foot.health6C<=0)throw std::invalid_argument("Missing passive Foot health startup");
                auto& type=passiveTypes_[lower(d.type)];auto& expiration=footExpirations_[int(i)];
                if(d.kind==MissionActorKind::Infantry)expiration.passiveType5A8=&type;
                else expiration.derivedType=&type;
            }
            if(d.kind==MissionActorKind::Structure){
                // Host rectangular clearance from authored art dimensions;
                // not recovered building construction or collision membership.
                const auto image=rules.get(d.type,"Image",d.type),shape=lower(art.get(image,"Foundation"));
                const auto separator=shape.find('x');
                if(separator==std::string::npos)throw std::invalid_argument("Unsupported building clearance foundation");
                std::size_t a=0,b=0;const int width=std::stoi(shape.substr(0,separator),&a),height=std::stoi(shape.substr(separator+1),&b);
                if(a!=separator||b!=shape.size()-separator-1||width<1||height<1||width>8||height>8)
                    throw std::invalid_argument("Unsupported building clearance dimensions");
                structureSizes.emplace(d.key,std::pair{width,height});
                for(int x=0;x<width;++x)for(int y=0;y<height;++y)blocked_.emplace(d.x+x,d.y+y);
            }else for(int x=-1;x<=1;++x)for(int y=-1;y<=1;++y)blocked_.emplace(d.x+x,d.y+y);
            continue;
        }
        if(d.health!=256||d.facing<0||d.facing>255)throw std::invalid_argument("Unsupported Day1 Infantry startup record");
        const int id=int(i),sub=std::stoi(d.fields.at(5));if(sub<0||sub>=int(offsets.size()))throw std::invalid_argument("Unsupported Infantry subcell");
        const auto* c=prepared_->find(d.x,d.y);if(!c||c->input.slope||(c->input.flags&0x100u))throw std::invalid_argument("Unsupported initial GI floor");
        auto& a=actors_[id];a.ground.position={d.x*256+offsets[std::size_t(sub)].x,d.y*256+offsets[std::size_t(sub)].y,c->input.level*104};
        a.cell450={std::int16_t(d.x),std::int16_t(d.y)};a.body.setCurrent(std::uint16_t(d.facing<<8),0);
        bool owner=false;for(const auto& [h,name]:mission.houses)if(lower(name)==lower(d.house)){a.object.mission.owner=h;owner=true;break;}
        if(!owner)throw std::invalid_argument("Missing GI House association");
        const auto m=lower(d.mission);if(m!="guard"&&m!="return")throw std::invalid_argument("Unsupported GI initial mission");
        a.object.mission.mission98=m=="guard"?5:12;definitions_[id]=i;sight_.emplace(id,SightState{});
        positions_.emplace(id,PositionState{});footExpirations_.emplace(id,BootCampFootExpirationState{});footRegistry_.push_back(&a);
        a.health6c=rules.integer("E1","Strength",-1); // Supplied full-health map256 association.
        if(a.health6c<=0)throw std::invalid_argument("Missing GI full-health association");
        a.flag32d=1; // Supplied startup byte shared by sight, position and admission.
    }
    footCount_=std::int32_t(footRegistry_.size());
    for(const auto& s:assets.scenery)blocked_.emplace(s.x,s.y);
    missionWorld_=std::make_unique<BootCampMissionWorld>(mission_,source,rules,globals_.tick,std::make_shared<PreparedStringLookup>(assets.store.require("ra2.csf")),
        readMessageColorData(readFile(preparedDataPath(assets.engineDataSource,"message-color-data.bin")),assets.engineDataSource),makeBootCampMessages(assets));
    for(const auto& d:mission_.actors)if(d.kind==MissionActorKind::Structure&&lower(d.tag)=="043bd15c"){
        auto a=missionWorld_->structureResident(d.key);const auto size=structureSizes.at(d.key);
        const auto* input=map_->table.at(std::size_t(d.y*512+d.x));
        if(!input)throw std::invalid_argument("Objective structure outside actual resident Cells");
        a.position88={d.x*256+128,d.y*256+128,int(input->level)*map_->levelHeight};a.width=size.first;a.height=size.second;
    }
    bindWorld(true);
}
void BootCampWalkWorld::bindWorld(bool initialize,const BootCampVisibilityWorld* visibilitySource){
    std::map<int,InfantryWalkBinding> bindings;
    for(auto& [id,a]:actors_){const int owner=a.object.mission.owner;auto& h=houseInputs_.at(owner);auto& discoveryHouse=missionWorld_->house(owner);
        bindings.emplace(id,InfantryWalkBinding{a,type_,missionWorld_->house(owner).indexAlliance.countryIndex,h.speed,discoveryHouse.human134,discoveryHouse.control135});}
    AdmissionHouses houses{[this](int id){const auto& h=missionWorld_->house(id).indexAlliance;
            return AdmissionHouseView{h.countryIndex,h.allianceMask};},
        [this](int id){return missionWorld_->houses().contains(id);}};
    walking_=std::make_unique<PreparedInfantryWalk>(*map_,cells_,std::move(bindings),foundation_,houses,registry_,globals_,subcells_,random_,numbers_,speeds_);
    missionWorld_->bindResidentIdentities([this](int id)->const void*{return &actors_.at(id);},[this](const void* p){for(const auto& [id,a]:actors_)if(p==&a)return id;throw std::invalid_argument("Foreign Walk resident pointer");});
    auto& membership=walking_->membership();auto& m=membership.world();
    // Supplied anchor-Cell placement of the two objective structures. The
    // records/Next belong to the same mission owner, not a visibility copy.
    for(const auto& d:mission_.actors)if(d.kind==MissionActorKind::Structure&&lower(d.tag)=="043bd15c"){
        auto a=missionWorld_->structureResident(d.key);
        const int index=d.y*512+d.x;
        if(index<0||std::size_t(index)>=map_->slots.size()||map_->slots[std::size_t(index)]<0)
            throw std::invalid_argument("Objective structure outside actual resident Cells");
        const int cellId=map_->slots[std::size_t(index)];
        walking_->registerBuildingResident(d.key,a.identity,{a.position88,a.next,a.alternate79,a.eligible5a0,a.typeMapFlag205,6});
        if(initialize){auto& head=cells_.at(std::size_t(cellId)).head;a.next=head;head=d.key;}
    }
    // Cell recalculation joins actual lists/buffers. Other named effects and
    // startup visibility remain supplied until the visibility owner exists.
    m.services.visible=[](const Coord&){return 1;};m.services.visibleSecondary=[](const Coord&){return 1;};
    m.services.liveVisibilityGate=[this]{return missionWorld_->discoveryMode();};
    m.services.liveNotificationArgument=[this]{return missionWorld_->currentHouse();};
    m.services.notify=[this](int id,int house){auto& a=actors_.at(id);
        (void)missionWorld_->discoverInfantry(id,a.object.mission,a.objectTag34,house);
    };
    m.services.recalculate=[this](int id,int level){walking_->membership().recalculate(id,level);};
    membership.redrawMap=[this]{visibilityWorld_->requestMapRedraw();};membership.specialEvent=[](int,int){};
    walking_->arrivalNotification=[](int,int){};
    walking_->dirty=[this](int cell){(void)dirtyCell(cell);};
    walking_->animation=[](int,int,int,int){throw std::invalid_argument("Boot Camp Infantry animation4DC effect unjoined");};
    walking_->targetIdentity=[this](const void* p){
        for(std::size_t id=0;id<map_->cells.size();++id)
            if(p==&map_->cells[id].attributes.input)return int(id)+1;
        throw std::invalid_argument("Foreign GI Cell target");
    };
    walking_->targetCoordinates=[this](const void* p){
        for(auto& cell:map_->cells)if(p==&cell.attributes.input)
            return mapCellCenterHeight(map_->floor,map_->levelHeight,cell.attributes.input);
        throw std::invalid_argument("Foreign GI Cell target coordinates");
    };
    walking_->route=[this](int id,TerrainCellPoint point,int,int){auto& a=actors_.at(id);const auto route=directRoute(id,{point.x*256+128,point.y*256+128,0});
        if(route.empty())return std::uint8_t(0);a.route.fill(-1);std::copy(route.begin(),route.end(),a.route.begin());return std::uint8_t(1);};
    auto residents=[this](int cell){return residentServices(cell);};
    auto discovered=[this](int actor,int house){return discoverResident(actor,house);};
    if(visibilitySource)visibilityWorld_=visibilitySource->clone(*map_,*missionWorld_,residents,discovered,numbers_.squareRoot);
    else visibilityWorld_=std::make_unique<BootCampVisibilityWorld>(mission_,source_,rules_,*map_,*missionWorld_,
        readVisibilityData(readFile(preparedDataPath(assets_.engineDataSource,"visibility-data.bin")),assets_.engineDataSource),
        actors_.size()+2,residents,discovered,numbers_.squareRoot);
    // Visibility construction does not query residents. Keep startup's supplied
    // visibility services until after Mark, but give its redraw the actual owner.
    if(initialize)for(auto& [id,a]:actors_){walking_->mark(id,1);membership.occupy(id,a.ground.position);}
    missionWorld_->bindWaypointReveal([this](std::int32_t index){return visibilityWorld_->revealWaypoint(index);});
    sightRegistry_.clear();
    // Scenario order is a supplied bounded association, not original logic-list
    // construction. Only currently owned actors enter this explicit registry.
    for(std::size_t i=0;i<mission_.actors.size();++i){const auto& d=mission_.actors[i];
        if(actors_.contains(int(i)))sightRegistry_.push_back(&actors_.at(int(i)));
        else if(d.kind==MissionActorKind::Structure&&lower(d.tag)=="043bd15c")
            sightRegistry_.push_back(missionWorld_->structureResident(d.key).identity);
    }
    sightSlots_=sightRegistry_;sightCount_=std::int32_t(sightRegistry_.size());
    m.services.visible=[this](const Coord& p){return visibilityWorld_->visible(p,false);};
    m.services.visibleSecondary=[this](const Coord& p){return visibilityWorld_->visible(p,true);};
    // Distinct AC0C18 projection over all currently owned map Foot records.
    // Startup order/no other constructed recipient kinds is supplied host scope,
    // not a claim about original scenario or Neuron construction.
    teamFootRecipients_.clear();teamFootBacking_.clear();
    for(std::size_t i=0;i<mission_.actors.size();++i)if(actors_.contains(int(i))||passiveFeet_.contains(int(i))){
        const int id=int(i);const void* identity=actors_.contains(id)?static_cast<const void*>(&actors_.at(id)):&passiveFeet_.at(id);
        auto& recipient=teamFootRecipients_[id];recipient={identity,[this,id](const MissionTeamExpiredAbstract& team,std::uint32_t removed){expireFootRecipient(id,team,removed);}};
        teamFootBacking_.push_back(&recipient);
    }
    teamFootSlots_=teamFootBacking_;teamFootCount_=std::int32_t(teamFootBacking_.size());

}
const void* BootCampWalkWorld::expirationResident(int id)const{
    if(id==-1)return nullptr;
    if(actors_.contains(id))return &actors_.at(id);
    if(passiveFeet_.contains(id))return &passiveFeet_.at(id);
    return missionWorld_->structureResident(id).identity;
}
int BootCampWalkWorld::expirationResidentId(const void* p)const{
    if(!p)return -1;
    for(const auto& [id,a]:actors_)if(p==&a)return id;
    for(const auto& [id,a]:passiveFeet_)if(p==&a)return id;
    for(const auto& d:mission_.actors)if(d.kind==MissionActorKind::Structure&&lower(d.tag)=="043bd15c"&&p==missionWorld_->structureResident(d.key).identity)return d.key;
    throw std::invalid_argument("Foreign Foot expiration Next identity");
}
MissionExpirationPointerView BootCampWalkWorld::expirationNext30(const void* p){
    for(auto& [id,a]:actors_)if(p==&a)return {[this,&a]{return expirationResident(a.object.next);},[this,&a](const void* value){a.object.next=expirationResidentId(value);}};
    for(auto& [id,a]:passiveFeet_)if(p==&a)return a.next30;
    if(p==missionWorld_->objectiveTeamIdentity())return missionWorld_->objectiveTeamSuccessor30();
    throw std::invalid_argument("Foot expiration passenger Next owner unbound");
}
void BootCampWalkWorld::expireFootRecipient(int id,const MissionTeamExpiredAbstract& subject,std::uint32_t removed){
    if(subject.identity!=missionWorld_->objectiveTeamIdentity())throw std::invalid_argument("Foreign actual Foot expiration Team");
    const bool gi=actors_.contains(id);auto& r=footExpirations_.at(id);
    auto* a=gi?&actors_.at(id):nullptr;auto* p=gi?nullptr:&passiveFeet_.at(id);
    const void* identity=gi?static_cast<const void*>(a):p;
    if(teamFootRecipients_.at(id).identity!=identity)throw std::invalid_argument("Split actual Team expiration recipient identity");
    auto& mission=gi?a->object.mission:p->mission;
    auto& tag=gi?a->objectTag34:p->tag34;
    auto& countRadio=gi?a->radioCountD0:p->radioCountD0;
    auto& radioBacking=gi?a->radioLinksCC:p->radioCC;
    auto& count4AC=gi?a->resumeCount4ac:p->count4AC;
    auto& count488=gi?a->resumePending488:p->count488;
    std::array<std::span<const void*>,6> spans{radioBacking,r.backing[0],r.backing[1],r.backing[2],r.backing[3],r.backing[4]};
    std::array<MissionExpirationVector<const void*>,6> vectors{{{countRadio,spans[0],&countRadio},
        {r.counts[0],spans[1],&r.counts[0]},{r.counts[1],spans[2],&r.counts[1]},
        {r.counts[2],spans[3],&r.counts[2]},{count4AC,spans[4],&count4AC},{count488,spans[5],&count488}}};
    MissionExpirationOwnerView house{[this,&mission]()->const void*{return mission.owner==-1?nullptr:&missionWorld_->house(mission.owner);},
        [this,&mission](const void* value){if(!value){mission.owner=-1;return;}for(const auto& [id,h]:missionWorld_->houses())if(value==&h){mission.owner=id;return;}throw std::invalid_argument("Foreign Foot expiration House");}};
    MissionRadioTagExpiration radio{{tag,expirationNext30(identity),identity},vectors[0]};
    MissionExpirationChain chain{r.headFC,&r.headFC,[this](const void* value){return expirationNext30(value);},footRegistry_.size()+1};
    auto& field1B0=gi?a->field1b0:p->field1B0;
    auto& target228=gi?positions_.at(id).alternate228:p->target228;
    auto& target22C=gi?a->teamTarget22c:p->target22C;
    auto& attached25C=gi?a->effect25c:p->effect25C;
    MissionTechnoTagExpiration techno{radio,chain,r.link108,field1B0,house,
        gi?positions_.at(id).effect208:p->service208,r.link20C,target228,target22C,r.control230,r.service238,r.link23C,
        {attached25C,r.links260},r.link27C,r.link384,r.link3F8,r.timer148,r.timer14C,r.timer150,mission.mission98,
        gi?a->object.statusA8:p->statusA8,mission.field372,r.byte5BA,vectors[1],vectors[2],vectors[3]};
    auto& numeric490=gi?a->field490:p->numeric490;
    MissionExpirationZeroField field490{numeric490};
    // Existing GI Type association is shared by Walk/radar/resume. It is never
    // mirrored into a second pointer. A matching foreign Team-as-Type refuses.
    MissionExpirationPointerView type=gi?MissionExpirationPointerView{
        [this]()->const void*{return &type_;},[](const void*){throw std::invalid_argument("GI Type association mutation unbound");}}:
        MissionExpirationPointerView{r.passiveType5A8};
    MissionFootTagExpiration foot{techno,gi?a->team4c4:p->team4C4,r.slave580,
        gi?a->teamNext4c8:p->next4C8,gi?a->teamLink498:p->link498,field490,
        gi?a->target494:p->target494,r.destination4BC,r.cell4B8,type,mission.queuedA0,vectors[4],vectors[5]};
    MissionTechnoTagExpirationServices services{globals_.tick,missionWorld_->expirationSessionA40774(),footExpirationScratch_};
    if(gi)services.setTarget370=[&,id](const void* target){
        if(target)throw std::invalid_argument("Nonnull Infantry expiration target unbound");
        clearInfantryRecruitTarget(positions_.at(id).alternate228,a->state5ac,a->route[0],a->targetFlag404,a->targetFlag57e);
    };
    // Target pending/resume, disguised CC and service effects remain absent;
    // entering them refuses instead of replacing a complete child with no-op.
    services.predicateC0=[&]{return missionTargetDisguisedC0(gi?a->byte170:p->byte170);};
    const int kind=gi?a->object.kind:p->kind;
    if(kind!=15&&kind!=1&&kind!=2)throw std::invalid_argument("Actual Foot expiration kind outside recovered recipient domain");
    services.kind2C=[kind]{return kind;};
    if(kind==2)services.queryCC=[](std::int32_t n){return missionBuildingQueryCC(std::uint32_t(n));};
    MissionFootTagExpirationServices children{footExpirationGlobalA40D04_};
    children.clear1B0=[&](const void* value){setTechnoField1B0(identity,field1B0,value);};
    children.record=[&](const void* value)->MissionExpirationRecord{
        // Actual positive record/coordinate/slave-manager associations remain
        // guarded. The Team must not be queried through a Foot record layout.
        if(value!=subject.identity)throw std::invalid_argument("Foot expiration record association unbound");
        throw std::invalid_argument("Team-as-Foot record layout is not a valid association");
    };
    //4C8 is a Foot list link. A Team cannot be its successor-owner record.
    // Exact Team-subject kernel allows that synthetic fixture, actual owners
    // refuse it rather than reading a Team with a fabricated Foot layout.
    if(foot.link4C8==subject.identity&&std::uint8_t(removed))
        throw std::invalid_argument("Actual Team cannot occupy a Foot next4C8 association");
    if(kind==15)expireMissionInfantryTag(foot,subject,missionWorld_->objectiveTeamFlags14(),removed,services,children);
    else if(kind==1)expireMissionUnitTag({foot,r.derivedType,r.derived5AC},subject,missionWorld_->objectiveTeamFlags14(),removed,services,children);
    else expireMissionAircraftTag({foot,r.derivedType,r.derived5AC},subject,missionWorld_->objectiveTeamFlags14(),removed,services,children);
}
void BootCampWalkWorld::composeObjectiveTeamExpiration(std::uint32_t removed){
    MissionExpirationVector<TeamExpirationRecipient*> recipients{teamFootCount_,teamFootSlots_,&teamFootRegistryIdentity_};
    missionWorld_->expireObjectiveTeam(recipients,removed);
}
CellDirtyEffectExit BootCampWalkWorld::dirtyCell(int cell){
    const auto& attributes=walking_->membership().attributes(cell);
    return applyCellDirtyEffectPrefix({attributes.overlay,attributes.overlayData,
        attributes.input.slope,attributes.input.flags,cells_.at(std::size_t(cell)).head!=-1});
}
std::unique_ptr<BootCampWalkWorld> BootCampWalkWorld::clone()const{
    // A snapshot must not silently canonicalize split source associations or
    // discard source observers. These bindings are fixed in the bounded owner.
    const auto& lookup=map_->resident.world;
    if(map_->table.size()!=map_->slots.size()||map_->attributes.size()!=map_->cells.size()||
       lookup.cells.data()!=map_->table.data()||lookup.cells.size()!=map_->table.size()||
       lookup.fallback!=&map_->fallback.input||lookup.query||lookup.fallbackStore)
        throw std::invalid_argument("Boot Camp preview requires canonical map associations and unbound observers");
    for(std::size_t i=0;i<map_->cells.size();++i)if(map_->attributes[i]!=&map_->cells[i].attributes)
        throw std::invalid_argument("Boot Camp preview has split map attribute associations");
    for(std::size_t i=0;i<map_->slots.size();++i){const int cell=map_->slots[i];
        if(cell< -1||cell>=int(map_->cells.size())||
           map_->table[i]!=(cell<0?nullptr:&map_->cells[std::size_t(cell)].attributes.input))
            throw std::invalid_argument("Boot Camp preview has split map slot associations");
    }
    for(const auto& [id,a]:actors_)if(a.walk.piggyback38)
        throw std::invalid_argument("Boot Camp Walk retained locomotor clone remains unjoined");
    auto out=std::make_unique<BootCampWalkWorld>(assets_,mission_,source_,rules_,art_);
    // Discard the fresh startup bindings before replacing any borrowed owners.
    out->visibilityWorld_.reset();out->walking_.reset();out->missionWorld_.reset();
    out->map_=map_->clone();out->actors_=actors_;out->passiveFeet_=passiveFeet_;out->passiveTypes_=passiveTypes_;
    if(out->passiveTags_.size()!=passiveTags_.size())throw std::invalid_argument("Passive map Tag association mismatch");
    for(const auto& [name,tag]:passiveTags_){
        if(tag->typePointer!=&tag->type||tag->first)throw std::invalid_argument("Passive map Tag Trigger/type association unbound");
        auto& copy=*out->passiveTags_.at(name);copy.persistence=tag->persistence;copy.instances=tag->instances;copy.executing=tag->executing;
    }
    const auto external=[&](const void* p)->const void*{
        for(const auto& [id,a]:actors_)if(p==&a)return &out->actors_.at(id);
        for(const auto& [id,a]:passiveFeet_)if(p==&a)return &out->passiveFeet_.at(id);
        for(std::size_t i=0;i<map_->cells.size();++i)if(p==&map_->cells[i].attributes.input)return &out->map_->cells[i].attributes.input;
        if(p==&map_->fallback.input)return &out->map_->fallback.input;
        return nullptr;
    };
    out->missionWorld_=missionWorld_->clone(out->globals_.tick,external);
    out->prepared_=prepared_; // Immutable terrain/type backing, never a mutable Cell owner.
    // Keep the actor nodes stable after the mission clone borrows their addresses.
    out->cells_=cells_;out->sight_=sight_;out->positions_=positions_;
    out->houseInputs_=houseInputs_;out->registry_=registry_;
    out->missionControl_=missionControl_;out->footExpirationGlobalA40D04_=footExpirationGlobalA40D04_;out->footExpirationScratch_=footExpirationScratch_;
    out->type_=type_;out->speeds_=speeds_;out->subcells_=subcells_;
    out->foundation_=foundation_;out->globals_=globals_;out->random_=random_;
    out->residentSearch_=residentSearch_;out->blocked_=blocked_;out->definitions_=definitions_;
    out->positionScratch_=positionScratch_;out->positionTypeFootprint_=positionTypeFootprint_;
    out->positionTypeSpecial_=positionTypeSpecial_;out->veteranSight_=veteranSight_;out->eliteSight_=eliteSight_;
    out->sightRange_=sightRange_;out->sightHeightDivisor_=sightHeightDivisor_;
    out->threat598_=threat598_;
    out->sightType534_=sightType534_;out->sightTypeADD_=sightTypeADD_;
    out->veteranSightMultiplier_=veteranSightMultiplier_;
    // Numeric services remain the fresh immutable-asset bindings. No source
    // std::function is copied, including services nested in walking/visibility.
    out->numbers_.radiansPerFacing=numbers_.radiansPerFacing;
    const auto weapon=[](const auto& from,auto& to){
        if(from.identity!=&from)throw std::invalid_argument("Foreign Boot Camp preview weapon identity");
        to.identity=&to;
    };
    for(std::size_t i=0;i<type_.weaponSelection.weapons.size();++i){
        weapon(type_.weaponSelection.weapons[i],out->type_.weaponSelection.weapons[i]);
        weapon(type_.weaponSelection.eliteWeapons[i],out->type_.weaponSelection.eliteWeapons[i]);
    }
    const auto cell=[&](const void* target)->const void*{
        if(!target)return nullptr;
        for(std::size_t i=0;i<map_->cells.size();++i)if(target==&map_->cells[i].attributes.input)
            return &out->map_->cells[i].attributes.input;
        if(target==&map_->fallback.input)return &out->map_->fallback.input;
        throw std::invalid_argument("Foreign Boot Camp preview Cell target");
    };
    const auto expirationPointer=[&](const void* p)->const void*{
        if(!p)return nullptr;if(const auto mapped=external(p))return mapped;
        if(p==&type_)return &out->type_;
        if(p==missionWorld_->objectiveTeamIdentity())return out->missionWorld_->objectiveTeamIdentity();
        if(p==missionWorld_->objectiveTeamTag())return out->missionWorld_->objectiveTeamTag();
        for(const auto& [name,t]:passiveTypes_)if(p==&t)return &out->passiveTypes_.at(name);
        for(const auto& [name,t]:passiveTags_)if(p==&t->view)return &out->passiveTags_.at(name)->view;
        for(const auto& [id,h]:missionWorld_->houses())if(p==&h)return &out->missionWorld_->house(id);
        for(const auto& d:mission_.actors)if(d.kind==MissionActorKind::Structure&&lower(d.tag)=="043bd15c"&&p==missionWorld_->structureResident(d.key).identity)
            return out->missionWorld_->structureResident(d.key).identity;
        throw std::invalid_argument("Foreign cloned Foot expiration reference");
    };
    for(auto& [id,a]:out->actors_){
        if(a.walk.inProcessing35||a.effect25c||a.transport588||a.controller408)
            throw std::invalid_argument("Boot Camp preview requires idle dispatch and owned effect/Team bindings");
        if(a.team4c4){
            if(a.team4c4!=missionWorld_->objectiveTeamIdentity())throw std::invalid_argument("Foreign cloned GI Team");
            a.team4c4=out->missionWorld_->objectiveTeamIdentity();
        }
        if(a.teamNext4c8){const auto* mapped=external(a.teamNext4c8);if(!mapped)throw std::invalid_argument("Foreign cloned Team member link");a.teamNext4c8=mapped;}
        if(a.objectTag34){
            if(a.objectTag34!=missionWorld_->objectiveTeamTag())throw std::invalid_argument("Foreign cloned GI Tag");
            a.objectTag34=out->missionWorld_->objectiveTeamTag();
        }
        const auto reference=[&](const void* value,const char* error)->const void*{
            if(!value)return nullptr;if(const auto mapped=external(value))return mapped;
            if(value==missionWorld_->objectiveTeamIdentity())return out->missionWorld_->objectiveTeamIdentity();
            throw std::invalid_argument(error);
        };
        a.field1b0=reference(a.field1b0,"Foreign cloned GI field1B0");
        a.teamLink498=reference(a.teamLink498,"Foreign cloned GI link498");
        a.teamTarget22c=reference(a.teamTarget22c,"Foreign cloned GI target22C");
        a.target494=cell(a.target494);
        auto& p=out->positions_.at(id);
        if(p.alternate228){const auto mapped=external(p.alternate228);if(!mapped)throw std::invalid_argument("Foreign cloned Foot reference228");p.alternate228=mapped;}
        if(p.effect208||p.target34)
            throw std::invalid_argument("Boot Camp preview position pointer requires an owned binding");
    }
    for(auto& [id,a]:out->passiveFeet_)if(a.target228){
        const auto mapped=external(a.target228);if(!mapped)throw std::invalid_argument("Foreign cloned passive Foot reference228");a.target228=mapped;
    }
    out->footExpirations_=footExpirations_;
    for(auto& [id,state]:out->footExpirations_)state.remapPointers(expirationPointer);
    for(auto& [id,a]:out->passiveFeet_){
        a.next30=expirationPointer(a.next30);a.tag34=static_cast<MissionTagState*>(const_cast<void*>(expirationPointer(a.tag34)));
        for(auto* p:std::array{&a.field1B0,&a.target22C,&a.effect25C,&a.team4C4,&a.next4C8,&a.link498,&a.target494,&a.service208})*p=expirationPointer(*p);
        for(auto& p:a.radioCC)p=expirationPointer(p);
    }
    for(auto& [id,a]:out->actors_)for(auto& p:a.radioLinksCC)p=expirationPointer(p);
    out->footRegistry_.clear();out->footCount_=footCount_;
    for(const auto p:footRegistry_){const auto mapped=external(p);if(!mapped)throw std::invalid_argument("Foreign cloned Foot registry identity");out->footRegistry_.push_back(mapped);}
    out->bindWorld(false,visibilityWorld_.get());
    if(teamFootSlots_.data()!=teamFootBacking_.data()||teamFootSlots_.size()!=teamFootBacking_.size())
        throw std::invalid_argument("Foreign Team expiration registry backing");
    out->teamFootBacking_.clear();out->teamFootCount_=teamFootCount_;
    for(const auto* recipient:teamFootBacking_){
        if(!recipient){out->teamFootBacking_.push_back(nullptr);continue;}
        bool found=false;for(const auto& [id,r]:teamFootRecipients_)if(recipient==&r){
            if(!r.expired)throw std::invalid_argument("Unbound cloned Team expiration recipient");
            if(r.identity!=(actors_.contains(id)?static_cast<const void*>(&actors_.at(id)):&passiveFeet_.at(id)))
                throw std::invalid_argument("Split Team expiration recipient identity");
            out->teamFootBacking_.push_back(&out->teamFootRecipients_.at(id));found=true;break;
        }
        if(!found)throw std::invalid_argument("Foreign cloned Team expiration recipient");
    }
    out->teamFootSlots_=out->teamFootBacking_;

    if(sightSlots_.data()!=sightRegistry_.data()||sightSlots_.size()!=sightRegistry_.size())
        throw std::invalid_argument("Foreign Boot Camp sight registry backing");
    out->sightRegistry_.clear();
    for(const auto* p:sightRegistry_){
        if(!p){out->sightRegistry_.push_back(nullptr);continue;}
        const int id=sightActorId(p);
        out->sightRegistry_.push_back(actors_.contains(id)?static_cast<const void*>(&out->actors_.at(id)):out->missionWorld_->structureResident(id).identity);
    }
    out->sightSlots_=out->sightRegistry_;out->sightCount_=sightCount_;
    return out;
}
int BootCampWalkWorld::residentHead(TerrainCellPoint point,bool elevated)const{
    const int slot=int(point.y)*512+int(point.x);
    int cell=int(map_->cells.size());
    if(slot>=0&&std::size_t(slot)<map_->slots.size()&&map_->slots[std::size_t(slot)]>=0)cell=map_->slots[std::size_t(slot)];
    const auto& c=cells_.at(std::size_t(cell));return elevated?c.alternateHead:c.head;
}
CellClosestResidentServices BootCampWalkWorld::residentServices(int cellId){
    const int cell=cellId==-1?int(map_->cells.size()):cellId;
    if(cell<0||std::size_t(cell)>=cells_.size())throw std::invalid_argument("Foreign visibility membership Cell");
    CellClosestResidentServices out;
    out.head=[this,cell](bool elevated){const auto& c=cells_.at(std::size_t(cell));return elevated?c.alternateHead:c.head;};
    out.flags=[this](int id){const auto a=actors_.find(id);return a==actors_.end()?missionWorld_->structureResident(id).flags14:a->second.object.flags14;};
    out.next=[this](int id){const auto a=actors_.find(id);return a==actors_.end()?missionWorld_->structureResident(id).next:a->second.object.next;};
    out.coordinates=[this](int id){const auto a=actors_.find(id);if(a!=actors_.end())return a->second.ground.position;
        auto building=missionWorld_->structureResident(id);
        return buildingCoordinates({[building](auto arg){if(arg)throw std::logic_error("Building coordinate height must receive zero");return building.height;},
            [building]{return building.width;},[building]{return building.position88;}});
    };
    out.squareRoot=[](double value){return std::sqrt(value);};out.memberLimit=actors_.size()+2;return out;
}
bool BootCampWalkWorld::discoverResident(int id,int house){
    if(house!=visibilityWorld_->currentHouse())throw std::invalid_argument("Foreign resident discovery House");
    const auto a=actors_.find(id);
    return a==actors_.end()?missionWorld_->discoverStructure(id):missionWorld_->discoverInfantry(a->second.object.mission);
}
bool BootCampWalkWorld::player(int id)const{return actors_.at(id).object.mission.owner==missionWorld_->currentHouse();}
bool BootCampWalkWorld::clear(int x,int y,int level)const{
    const auto* c=prepared_->find(x,y);if(!c||blocked_.contains({x,y})||c->overlay!=-1||c->input.tube!=-1||c->input.slope||
        (c->input.flags&0x100u)||c->input.level!=level||c->input.land<0||c->input.land>=12||prepared_->land[unsigned(c->input.land)].speed[0]==0)return false;
    for(const auto& [id,a]:actors_)if(a.ground.position.x/256==x&&a.ground.position.y/256==y)return false;
    const double u=(x-y+assets_.map.width-1)*.5,v=(x+y-assets_.map.width-1)*.5;const auto& b=assets_.map.local;
    return u>=b[0]&&v>=b[1]&&u<b[0]+b[2]&&v<b[1]+b[3];
}
std::vector<int> BootCampWalkWorld::directRoute(int id,Coord target)const{
    const auto& a=actors_.at(id);int x=a.ground.position.x/256,y=a.ground.position.y/256;
    const auto* c=prepared_->find(x,y);std::vector<int> result;if(!c)return result;
    const int tx=target.x/256,ty=target.y/256;if(std::max(std::abs(tx-x),std::abs(ty-y))>23)return result;
    while(x!=tx||y!=ty){const int dx=(tx>x)-(tx<x),dy=(ty>y)-(ty<y);x+=dx;y+=dy;
        if(!clear(x,y,c->input.level))return {};
        for(int d=0;d<8;++d)if(directionOffset(d)==std::pair{dx,dy}){result.push_back(d);break;}
    }return result;
}
bool BootCampWalkWorld::move(int id,int x,int y,std::string& status){
    auto& a=actors_.at(id);if(!player(id)){status="Select the player GI.";return false;}
    if(a.walk.moving34){status="Moving retarget is pending recovery; S stops at the committed subcell.";return false;}
    if(x<0||x>=512||y<0||y>=512){status="Destination outside map.";return false;}
    const Coord destination{x*256+128,y*256+128,0};
    if(directRoute(id,destination).empty()){
        status="Direct flat route blocked or unsupported (maximum 23 Cells); pathfinding is pending.";return false;}
    auto target=walking_->membership().walkMap().coordinate(destination);
    auto& targetOwner=walking_->membership().walkMap().attributes(target).input;
    walking_->order(id,&targetOwner);status="Walking using original Infantry/Walk algorithms; direct route and presentation remain supplied.";return true;
}
bool BootCampWalkWorld::stop(int id,std::string& status){if(!player(id))return false;walking_->order(id,nullptr);status="Stop issued; the committed head finishes.";return true;}
bool BootCampWalkWorld::canAdmitToObjectiveTeam(int id,std::int32_t& slot)const{
    const auto& a=actors_.at(id);
    if(a.object.kind!=15)throw std::invalid_argument("Objective admission requires actual E1 Infantry");
    const std::uint8_t noAircraft=0;const std::uint32_t noTarget=0;
    TeamAdmissionFoot foot{&a,a.team4c4,a.onMap7d,a.health6c,a.flag76,
        [&]()->const void*{return &missionWorld_->house(a.object.mission.owner);},
        a.recruitable379,a.recruitable37a,noAircraft,noTarget};
    TeamAdmissionServices services{globals_.loading};
    services.radio636F10=[&]{return std::uint32_t(buildingHasRadioPointerLinks(a.radioCountD0,a.radioLinksCC));};
    services.kind2C=[&]{return std::uint32_t(a.object.kind);};
    services.mission16C=[&]{return unitDiscoveryMission(a.object.mission);};
    services.mission594DB0=[&](std::int32_t mission)->std::uint32_t{
        return missionRecruitable(missionControl_,mission);
    };
    services.type84=[&]()->const void*{return &type_;};
    services.teamPriorityB4=[](const void*)->std::int32_t{
        throw std::invalid_argument("Existing GI Team priority requires an actual bound owner");
    };
    return missionWorld_->canAdmitObjectiveFoot(foot,&type_,slot,services);
}
bool BootCampWalkWorld::addToObjectiveTeam(int id){
    auto& a=actors_.at(id);if(a.object.kind!=15)throw std::invalid_argument("Actual E1 membership required");
    TeamMemberFoot foot{&a,a.team4c4,a.teamNext4c8,a.teamLeader579,a.teamGroup1ac,a.recruitable37a,a.objectTag34};
    TeamMembershipServices services;
    services.admission6B8DC0=[&](TeamMemberFoot&,std::int32_t& slot){return std::uint32_t(canAdmitToObjectiveTeam(id,slot));};
    services.remove6B8FB0=[](const void*,auto&,int,std::uint32_t){throw std::invalid_argument("Existing Team member unlink unjoined");};
    services.threat2A0=[&](auto&){
        TechnoThreatServices t{[&]()->const void*{return &type_;},[&]{return a.object.kind;},[&](const void*)->const std::int32_t&{return threat598_;}};
        const std::int32_t zero=0;return technoThreat(zero,zero,t);
    };
    const bool added=missionWorld_->addObjectiveTeamMember(foot,services,
        [&](TeamConstructionRecord& team,TeamMembershipType& type){selectObjectiveTeamAnchor(team,type);});
    a.object.mission.hasTag=bool(a.objectTag34);return added;
}
bool BootCampWalkWorld::removeFromObjectiveTeam(int id){
    const auto idOf=[&](const void* p){for(const auto& [key,a]:actors_)if(p==&a)return key;throw std::invalid_argument("Foreign actual Team removal member");};
    TeamRemovalServices services{globals_.loading,actors_.size()};
    services.foot=[&](const void* p){auto& a=actors_.at(idOf(p));return TeamRemovalFoot{p,a.team4c4,a.teamNext4c8,a.teamFlag5a2,
        a.mission9c,a.teamLink498,a.teamTarget22c,a.teamLeader579,a.onMap7d,a.flag37d,a.flag76};};
    services.tag34=[&](const void* p)->const void*{return actors_.at(idOf(p)).objectTag34;};
    services.house1B4=[&](const void* p)->const void*{return &missionWorld_->house(actors_.at(idOf(p)).object.mission.owner);};
    services.controlled4F52F0=[&](const void* p){
        for(const auto& [key,h]:missionWorld_->houses())if(p==&h)return std::uint32_t(discoveryHouseControlled(h,missionWorld_->discoveryMode()));
        throw std::invalid_argument("Foreign actual Team removal House");
    };
    services.clearTag5D4430=[&](const void* p){auto& a=actors_.at(idOf(p));setMissionObjectTag({a.objectTag34,p},nullptr);a.object.mission.hasTag=bool(a.objectTag34);};
    services.type84=[&](const void* p)->const void*{(void)idOf(p);return &type_;}; // Supplied E1 Type association.
    services.threat2A0=[&](const void* p){const std::int32_t unused=0;return std::uint32_t(composeActorThreat(idOf(p),unused));};
    services.resume414=[&](const void* p,const void* first,std::uint32_t second){resumeInfantryOwned(idOf(p),first,second);};
    return missionWorld_->removeObjectiveTeamMember(&actors_.at(id),&type_,services);
}
void BootCampWalkWorld::selectObjectiveTeamAnchor(TeamConstructionRecord& team,TeamMembershipType& type){
    if(team.value40)throw std::invalid_argument("Nonempty Team target association unjoined");
    const auto actor=[&](const void* p)->const InfantryWalkState&{
        for(const auto& [id,a]:actors_)if(p==&a)return a;throw std::invalid_argument("Foreign actual Team member");
    };
    const auto actorId=[&](const void* p){for(const auto& [id,a]:actors_)if(p==&a)return id;throw std::invalid_argument("Foreign actual Team permission member");};
    TeamAnchorServices services{globals_.loading,actors_.size()};
    services.type24=[&]()->auto&{return type;};
    services.script668870=[&](const void* script){return missionWorld_->objectiveTeamScriptAction(script).action;};
    services.foot=[&](const void* p){const auto& a=actor(p);return TeamAnchorFoot{p,a.teamNext4c8,a.onMap7d,a.health6c,a.flag76,a.teamLeader579,a.flag32d,a.ground.position};};
    services.kind2C=[&](const void* p){return actor(p).object.kind;};
    services.type80Count52C=[](const void*){return 0;}; // Supplied E1 Type field startup.
    services.distance5D4DA0=[](const void*,const void* target){if(target)throw std::invalid_argument("Nonempty Team distance target unjoined");return 0;}; // Inspected original null-target branch.
    services.map548000=[&](Coord p)->const void*{return walking_->membership().walkMap().coordinate(p).identity;};
    services.permission194=[&](const void* member,const void* cell,int direction,int level,int previous,int consult){
        return walking_->admission(actorId(member),cell,direction,level,previous,consult);
    };
    selectTeamMemberAnchor(team,services);
}
std::uint32_t BootCampWalkWorld::infantryCost(const void* type,const void* house)const{
    if(type!=&type_)throw std::invalid_argument("Cost requires actual E1 Type");
    TechnoTypeCostServices s;
    s.kind2C=[&](const void* p){if(p!=&type_)throw std::invalid_argument("Foreign cost Type kind");return 16;};
    s.baseCostAC=[&](const void* p){if(p!=&type_)throw std::invalid_argument("Foreign cost Type base");return type_.baseCost550;};
    s.countryFactor=[&](const void* p,std::int64_t off){
        if(off!=0x114)throw std::invalid_argument("Only E1 country cost field is owned");
        for(const auto& [id,h]:missionWorld_->houses())if(p==&h)return missionWorld_->countryType(id).costInfantry114;
        throw std::invalid_argument("Cost requires actual mission House");
    };
    return technoTypeCost(type,house,s);
}
bool BootCampWalkWorld::attemptHouseTransferOwned(int id,int nextHouse,RadarStorage& radar,std::span<const std::int32_t,18> tables){
    // This method is private and used only on a discarded diagnostic clone.
    // Also bound by the explicit unscheduled Team20 seam; never step()/SDL.
    const auto mapNotification=radar.notificationView();
    auto& a=actors_.at(id);auto& old=missionWorld_->house(a.object.mission.owner);
    auto& next=missionWorld_->house(nextHouse);const void* local=&missionWorld_->house(missionWorld_->currentHouse());
    TechnoHouseTransferActor actor{&a,a.flag76,a.object.flags14,a.ground.position,a.threat400,a.object.mission.field372,
        [&]()->const void*{return &missionWorld_->house(a.object.mission.owner);},
        [&](const void* p){if(p!=&next)throw std::invalid_argument("Foreign transfer House");
            walking_->rebindHouse(id,nextHouse,next.indexAlliance.countryIndex,houseInputs_.at(nextHouse).speed,next.human134,next.control135);}};
    TechnoHouseTransferServices services{local};
    services.clear370=[&](const void* p){
        if(p)throw std::invalid_argument("Transfer clear target must be null");
        clearInfantryRecruitTarget(positions_.at(id).alternate228,a.state5ac,a.route[0],a.targetFlag404,a.targetFlag57e);
    };
    services.destination410=[&](const void* p,std::uint32_t arg){walking_->order(id,p,std::uint8_t(arg));};
    services.detach6155E0=[&]{detachNullTechnoController(a.controller408);};
    services.remove4ED440=[&](const void* p,std::uint32_t arg){
        if(p!=&old||arg)throw std::invalid_argument("Transfer removal lost actual House or argument");
        HouseInfantryActor member{&a,a.accounting324,a.accounting5c1,
            [&]{return HouseInfantryType{type_.accounting202,[&]{return type_.accountingIndex;}};},
            [&]{return std::uint32_t(a.object.kind);}};
        withHouseInfantryAccounting(old.infantryAccounting,&old,[&](auto& owner){
            removeRegisteredHouseInfantry(owner,member,[]{
                // Sidebar4EE1=0 remains a supplied diagnostic startup input.
                checkHouseTransferMapRemoval(0);
            });
        });
    };
    services.notifyDC=[&](const void* attacker){
        if(attacker)throw std::invalid_argument("Only null-attacker Infantry notification is recovered");
        TechnoNullNotificationActor member{&a,a.onMap7d,[&]()->const void*{return a.objectTag34;},
            [&]()->const void*{return &missionWorld_->house(a.object.mission.owner);}};
        const std::uint32_t empty=0x7fff7fff; // Existing mission's supplied empty-Cell association.
        TechnoNullNotificationServices children{empty};
        children.type80=[&]()->const void*{return &type_;};
        children.cost84=[&](const void* type,const void* house){
            if(type!=&type_||house!=&missionWorld_->house(a.object.mission.owner))
                throw std::invalid_argument("Notification lost actual Type/House identity");
            return infantryCost(type,house);
        };
        children.kind2C=[&]{return a.object.kind;};
        children.raiseTag=[&](const void* tag,int pulse,const void* actor,std::uint32_t location){
            if(tag!=a.objectTag34||actor!=&a)throw std::invalid_argument("Notification lost actual GI Tag");
            missionWorld_->notifyInfantryTag(a.objectTag34,actor,pulse,location);
        };
        children.house5360=[&](const void* p)->std::uint32_t&{
            for(const auto& [id,house]:missionWorld_->houses())if(p==&house)return missionWorld_->house(id).notification5360;
            throw std::invalid_argument("Notification lost actual old House");
        };
        children.map6331A0=[&]{return std::uint32_t(radarMapNotificationMode(mapNotification));};
        children.map6331E0=[&](auto argument){requestRadarMapNotification(mapNotification,argument);};
        notifyTechnoNullAttacker(member,children);
    };
    services.type80=[&]()->const void*{return &type_;};
    services.cost84=[&](const void* type,const void* house){return infantryCost(type,house);};
    services.house=[&](const void* p)->TechnoHouseTransferHouse{
        for(const auto& [id,h]:missionWorld_->houses())if(p==&h){
            auto& house=missionWorld_->house(id);const auto& type=missionWorld_->countryType(id);
            return {house.transferValue5418,house.transfersFrom5310,house.lastCountry53B8,type.countryB8};
        }
        throw std::invalid_argument("Foreign transfer ledger House");
    };
    const auto active=[&](const void* p,bool add){
        for(const auto& [id,h]:missionWorld_->houses())if(p==&h){
            auto& house=missionWorld_->house(id);
            HouseInfantryActor member{&a,a.accounting324,a.accounting5c1,
                [&]{return HouseInfantryType{type_.accounting202,[&]{return type_.accountingIndex;}};},
                [&]{return std::uint32_t(a.object.kind);}};
            withHouseInfantryAccounting(house.infantryAccounting,&house,[&](auto& owner){
                if(add)addActiveHouseInfantry(owner,member);else removeActiveHouseInfantry(owner,member);
            });return;
        }
        throw std::invalid_argument("Foreign transfer active-accounting House");
    };
    services.remove4EA800=[&](const void* p){active(p,false);};
    services.add4EA970=[&](const void* p){active(p,true);};
    services.kind2C=[&]{return a.object.kind;};
    services.country38=[&]{return missionWorld_->house(a.object.mission.owner).indexAlliance.countryIndex;};
    services.draw11C=[&](std::int32_t mode){walking_->mark(id,mode);};
    services.clearReferences6D7C80=[&]{clearReferencesOwned(&a);};
    services.coordinate548000=[&](Coord point)->const void*{
        MapFloorHeightWorld world{map_->table,&map_->fallback.input,{}};
        return &mapCoordinateCell(point,world,int(map_->table.size()));
    };
    services.threat476B20=[&](const void* p,std::int32_t owner,std::uint32_t delta){
        // Resolve only actual map Cell identities, including the shared fallback.
        const MapCellInput* cell=nullptr;
        if(p==&map_->fallback.input)cell=&map_->fallback.input;
        for(const auto& item:map_->cells)if(p==&item.attributes.input){cell=&item.attributes.input;break;}
        if(!cell)throw std::invalid_argument("Foreign transfer Cell threat identity");
        missionWorld_->changeCellThreat({cell->position.x,cell->position.y},owner,std::bit_cast<std::int32_t>(delta),tables);
    };
    services.threat2A0=[&]{
        if(a.object.kind!=15)throw std::invalid_argument("House transfer threat requires actual E1 kind15");
        const std::int32_t unused=0; // Stock Infantry never reads Building field564/rulesBE8.
        return std::uint32_t(composeActorThreat(id,unused));
    };
    services.add4ED610=[&](const void* p,std::uint32_t arg){
        if(p!=&next||arg!=1)throw std::invalid_argument("Transfer registration lost new House/argument");
        HouseInfantryActor member{&a,a.accounting324,a.accounting5c1,
            [&]{return HouseInfantryType{type_.accounting202,[&]{return type_.accountingIndex;}};},
            [&]{return std::uint32_t(a.object.kind);}};
        withHouseInfantryAccounting(next.infantryAccounting,&next,[&](auto& owner){addRegisteredHouseInfantry(owner,member);});
    };
    services.radio636E10=[&](std::int32_t slot){return houseTransferRadioSlot(a.radioLinksCC,slot);};
    services.sight414=[&](const void* first,std::uint32_t second){resumeInfantryOwned(id,first,second);};
    services.sight424=[&]{BootCampRadarActors::updateMarker(*this,radar,&a,RadarActorMarkerOperation::remove);};
    services.sight420=[&]{BootCampRadarActors::updateMarker(*this,radar,&a,RadarActorMarkerOperation::insert);};
    // Complete bounded wrapper borrows actual ground/floor/packed-Cell fields.
    // This discarded diagnostic is not adopted by Team, arrival or SDL.
    return transferInfantryHouse(&next,1,{[&](const void* p,std::uint32_t arg){
        if(p!=&next||arg!=1)throw std::invalid_argument("Infantry transfer forwarding differs");
        return std::uint32_t(transferTechnoHouse(actor,p,services));
    },[&]{
        return std::uint32_t(objectAboveGround(a.ground.marked74,globals_.levelHeight,[&]{
            return relativeObjectGroundHeight(a.ground,globals_.bridgeHeight,[&](Coord p){
                return walking_->membership().walkMap().floor(p);
            });
        }));
    },[&]{
        const auto p=terrainCellPoint(a.ground.position);
        return std::uint32_t(std::uint16_t(p.x))|(std::uint32_t(std::uint16_t(p.y))<<16);
    },[&](std::uint32_t value){
        auto& p=positions_.at(id);
        p.footprintX454=std::bit_cast<std::int16_t>(std::uint16_t(value));
        p.footprintY456=std::bit_cast<std::int16_t>(std::uint16_t(value>>16));
    }});
}
void BootCampWalkWorld::resumeInfantryOwned(int id,const void* first,std::uint32_t second){
    auto& a=actors_.at(id);
        InfantryMissionResumeServices resume;
        resume.foot4c6f10=[&](const void* p,std::uint32_t arg){
            FootMissionResumeServices foot;
            foot.techno6d48f0=[&](const void*,std::uint32_t){
                TechnoMissionResumeServices techno;
                techno.special45c=[&]()->std::uint32_t{
                    if(a.resumeSpecial4b4==29)throw std::invalid_argument("Foot resume45C special mission remains unjoined");
                    return 0; // Complete4CDD70 ordinary non29 branch.
                };
                techno.predicate3c8=[]{return 1u;}; // Complete E1 virtual6D1460.
                techno.controller615360=[&]()->std::uint32_t{
                    if(a.controller408)throw std::invalid_argument("Foot resume controller615360 effects remain unjoined");
                    return 0; // Complete-to-return615360 null408 ->6D1430.
                };
                (void)resumeTechnoMission(techno);
            };
            foot.percentage4c8=[&](int lo,int hi){
                if(lo||hi)throw std::invalid_argument("Foot resume requires positive-zero percentage");
                zeroFootResumePercentage(a.percentage468);
            };
            return resumeWalkFootMission({a.resume59d,a.resume577,a.resumePending488,
                a.object.mission.mission98,a.object.statusA8,positions_.at(id).animation418,a.field1b0},
                a.walk,{globals_.references,a.references},p,arg,foot);
        };
        resume.special438=[&]{return std::uint32_t(a.resumeSpecial4b4!=-1);};
        resume.mission16c=[&]{return std::uint32_t(unitDiscoveryMission(a.object.mission));};
        resume.queue1d0=[&](int mission,int flag){
            if(flag)throw std::invalid_argument("Resume QueueMission flag differs");
            queueUnitDiscoveryMission(a.object.mission,mission);
        };
        resume.refill4c8b00=[&]{refillEmptyFootResumeDestination(a.target494,a.resumeCount4ac);};
        resume.missionControl=[&](int offset){return missionControlFlag(missionControl_,a.object.mission.mission98,offset);};
        resume.controlled4f52f0=[&]{return discoveryHouseControlled(missionWorld_->house(a.object.mission.owner),missionWorld_->discoveryMode());};
        resume.house194=[]()->std::int32_t{throw std::invalid_argument("Infantry resume House194 remains unjoined");};
        resume.ability6d7910=[&](int index)->std::uint32_t{
            TechnoAbilityServices ability;
            ability.type80=[&]()->const void*{return &type_;};
            ability.typeByte=[&](const void* type,std::uint32_t offset){
                if(type!=&type_)throw std::invalid_argument("Resume ability lost saved actual Type");
                if(offset==0x27c)return type_.guardAreaVeteran27c;
                if(offset==0x28e)return type_.guardAreaElite28e;
                throw std::invalid_argument("Resume ability outside bound Type fields");
            };
            return technoHasAbility(a.veterancy118,index,ability);
        };
        resume.typeByte=[&](int offset){
            if(offset==0xb00)return type_.defaultGuardAreaB00;
            if(offset==0xc11)return type_.admissionC11;
            if(offset==0xc14)return type_.admissionC14;
            throw std::invalid_argument("Resume outside bound actual Type fields");
        };
        (void)resumeInfantryMission({a.object.mission.mission98,positions_.at(id).alternate228,
            a.target494,a.team4c4},first,second,resume);
}
void BootCampWalkWorld::clearReferencesOwned(const void* subject){
    TechnoReferenceCleanupServices services{footCount_,missionWorld_->referenceCleanupTeamCount()};
    services.footSlot=[&](int i)->const void*{
        if(i<0||std::size_t(i)>=footRegistry_.size())throw std::invalid_argument("Reference cleanup outside owned Foot backing");
        const auto p=footRegistry_[i];
        for(const auto& [id,a]:actors_)if(p==&a)return p;
        for(const auto& [id,a]:passiveFeet_)if(p==&a)return p;
        throw std::invalid_argument("Reference cleanup foreign Foot slot");
    };
    services.target228=[&](const void* p)->const void*{
        for(const auto& [id,a]:actors_)if(p==&a)return positions_.at(id).alternate228;
        for(const auto& [id,a]:passiveFeet_)if(p==&a)return a.target228;
        throw std::invalid_argument("Reference cleanup foreign Foot reference");
    };
    services.action1E0=[](const void*){throw std::invalid_argument("Reference cleanup matching Foot1E0 effects remain unjoined");};
    missionWorld_->bindReferenceCleanupTeams(services);
    clearTechnoReferences(subject,services);
}
bool BootCampWalkWorld::regroupObjectiveTeam(TeamConstructionRecord& team){
    // Supplied stock Rules initialization. Exact key/field loads are inspected,
    // but the general original INI conversion/default initialization is unjoined.
    if(rules_.number("General","Stray")!=2.0||rules_.number("General","RelaxedStray")!=3.0)
        throw std::invalid_argument("Only supplied stock Team regroup ranges are bound");
    const auto idOf=[&](const void* p){for(const auto& [id,a]:actors_)if(p==&a)return id;throw std::invalid_argument("Foreign actual regroup member");};
    TeamCohesionServices services{globals_.loading,actors_.size()};
    services.foot=[&](const void* p){auto& a=actors_.at(idOf(p));return TeamCohesionFoot{p,a.teamNext4c8,a.onMap7d,a.health6c,a.flag76,a.teamLeader579,a.target494,positions_.at(idOf(p)).alternate228};};
    services.script668870=[&]{return missionWorld_->objectiveTeamScriptAction().action;};
    services.range=[](bool relaxed){return relaxed?768:512;};
    services.distance5D4C00=[&](const void* p,const void* target){
        if(!target)return 0; // Complete original null-target return.
        // Keep the already verified nonbuilding Cell-target numeric kernel;
        // no host sqrt or distance-to-synthetic-objective replacement.
        return wallOwnerCellDistance(actors_.at(idOf(p)).ground.position,walking_->targetCoordinates(target),numbers_.squareRoot);
    };
    services.kind2C=[&](const void* p){return actors_.at(idOf(p)).object.kind;};
    services.mission16C=[&](const void* p){return unitDiscoveryMission(actors_.at(idOf(p)).object.mission);};
    services.queue1D0=[&](const void* p,int mission,int flag){if(flag)throw std::invalid_argument("Immediate regroup mission unjoined");queueUnitDiscoveryMission(actors_.at(idOf(p)).object.mission,mission);};
    services.target370=[&](const void* p,const void* target){
        if(target)throw std::invalid_argument("Nonnull regroup combat target unjoined");const auto id=idOf(p);auto& a=actors_.at(id);
        clearInfantryRecruitTarget(positions_.at(id).alternate228,a.state5ac,a.route[0],a.targetFlag404,a.targetFlag57e);
    };
    services.destination410=[&](const void* p,const void* target,int flag){walking_->order(idOf(p),target,std::uint8_t(flag));};
    // Far-side nearby4C8AF0/map548070 are intentionally unbound. Their entered
    // branches refuse; existing supported near-side commands use actual owners.
    return regroupTeamMembers(team,services);
}
bool BootCampWalkWorld::regroupObjectiveTeam(){return missionWorld_->regroupObjectiveTeam([&](TeamConstructionRecord& team){return regroupObjectiveTeam(team);});}
void BootCampWalkWorld::tickObjectiveTeamRecruitment(RadarStorage* radar,std::span<const std::int32_t> threatTables){
    if((radar&&threatTables.size()!=18)||(!radar&&!threatTables.empty()))
        throw std::invalid_argument("Actual Script transfer requires radar and18 threat inputs");
    std::function<TeamScriptServices::Transfer(const void*)> transfer;
    if(radar)transfer=[&](const void* p)->TeamScriptServices::Transfer{
        int actor=-1;for(const auto& [id,a]:actors_)if(p==&a){actor=id;break;}
        if(actor<0)throw std::invalid_argument("Foreign actual Script transfer member");
        return [&,actor](const void* house,std::uint32_t arg)->std::uint32_t{
            if(arg!=1)throw std::invalid_argument("Actual Script transfer requires literal1");
            for(const auto& [id,h]:missionWorld_->houses())if(house==&h)
                return std::uint32_t(attemptHouseTransferOwned(actor,id,*radar,threatTables.first<18>()));
            throw std::invalid_argument("Actual Script transfer requires owned nonnull House");
        };
    };
    missionWorld_->tickObjectiveTeamRecruitment(
        [&](TeamConstructionRecord& team,TeamMembershipType& type){selectObjectiveTeamAnchor(team,type);},
        [&](std::int32_t slot){(void)recruitObjectiveTeamSlot(slot);},
        [&](const void* member)->std::uint32_t{
            for(const auto& [id,a]:actors_)if(member==&a)return a.disabled205; // Complete E1 virtual1C0 ->6D6E00.
            throw std::invalid_argument("Foreign actual Team AI member");
        },[&](const void* p)->const void*{
            for(const auto& [id,a]:actors_)if(p==&a)return a.teamNext4c8;
            throw std::invalid_argument("Foreign actual activation member");
        },[&](const void* p,std::uint8_t value){
            for(auto& [id,a]:actors_)if(p==&a){a.teamLeader579=value;return;}
            throw std::invalid_argument("Foreign actual activation leader");
        },[&](TeamConstructionRecord& team){return std::uint32_t(regroupObjectiveTeam(team));},
        [&](const void* p){for(auto& [id,a]:actors_)if(p==&a){setTechnoField1B0(p,a.field1b0,nullptr);return;}throw std::invalid_argument("Foreign actual Script field1B0 member");},
        [&](const void* p,std::uint32_t value){for(auto& [id,a]:actors_)if(p==&a){a.valueD8=value;return;}throw std::invalid_argument("Foreign actual Script D8 member");},transfer);
}
bool BootCampWalkWorld::recruitObjectiveTeamSlot(std::int32_t slot){
    const auto idOf=[&](const void* pointer){for(const auto& [id,a]:actors_)if(pointer==&a)return id;throw std::invalid_argument("Foreign actual recruiting GI");};
    const auto links=missionWorld_->objectiveTeamLinks();const void* anchor=links[1];
    // Existing supplied global/startup adapters; no original global initialization claim.
    const Coord empty{};const std::uint32_t emptyCell=0x7fff7fff;
    TeamRecruitmentServices services{anchor,empty,emptyCell};
    services.coordinates48=[&](const void* p){
        for(const auto& [id,a]:actors_)if(p==&a)return a.ground.position;
        return walking_->targetCoordinates(p);
    };
    // Supplied startup registry order over the existing mutable actors. Children
    // do not construct/destroy/reorder actors in this admitted native domain.
    services.infantryCount=[&]{return std::int32_t(actors_.size());};
    services.infantrySlot=[&](int index)->const void*{
        if(index<0||std::size_t(index)>=actors_.size())throw std::invalid_argument("Recruitment outside actual Infantry backing");
        auto it=actors_.begin();std::advance(it,index);return &it->second;
    };
    services.footGroup1AC=[&](const void* p){return actors_.at(idOf(p)).teamGroup1ac;};
    services.admission6B8DC0=[&](const void* p,int& output){return std::uint32_t(canAdmitToObjectiveTeam(idOf(p),output));};
    services.clearTarget370=[&](const void* p){
        const auto id=idOf(p);auto& a=actors_.at(id);
        clearInfantryRecruitTarget(positions_.at(id).alternate228,a.state5ac,a.route[0],a.targetFlag404,a.targetFlag57e);
    };
    services.addMember6B8CC0=[&](const void* p){return addToObjectiveTeam(idOf(p));};
    return missionWorld_->recruitObjectiveInfantrySlot(slot,services);
}
void BootCampWalkWorld::step(){for(auto& [id,a]:actors_)walking_->process(id);globals_.tick=signed32(std::uint32_t(globals_.tick)+1u);}
BootCampWalkWorld::PositionCompositionResult BootCampWalkWorld::composeUpdatePositionPreview(int id){
    return composeUpdatePositionPreviewSequence(id,1).front();
}
std::vector<BootCampWalkWorld::PositionCompositionResult> BootCampWalkWorld::composeUpdatePositionPreviewSequence(int id,int notifications){
    if(notifications<1||notifications>16)throw std::invalid_argument("Boot Camp arrival preview count outside bound");
    if(!player(id))throw std::invalid_argument("Boot Camp update-position preview supports only the player GI");
    const auto& sourceActor=actors_.at(id);if(!sourceActor.target494)throw std::invalid_argument("Boot Camp update-position preview requires an actual Cell target");
    std::size_t targetIndex=map_->cells.size();
    for(std::size_t i=0;i<map_->cells.size();++i)if(sourceActor.target494==&map_->cells[i].attributes.input){targetIndex=i;break;}
    if(targetIndex==map_->cells.size())throw std::invalid_argument("Boot Camp update-position preview target is not an actual Cell");
    auto owner=clone();auto& preview=*owner;
    std::vector<PositionCompositionResult> scheduled;
    int processCalls=0;
    preview.walking_->arrivalNotification=[&](int arrived,int kind){
        if(arrived!=id||kind!=2||int(scheduled.size())>=notifications)throw std::logic_error("Boot Camp scheduled update-position dispatch differs");
        auto result=preview.composeUpdatePositionPreviewOwned(id);
        result.arrivalNotifications=1;result.arrivalKind=kind;result.arrivalProcessCalls=processCalls;
        result.arrivalPosition=preview.actors_.at(id).ground.position;scheduled.push_back(std::move(result));
    };
    while(int(scheduled.size())<notifications&&processCalls<4096){++processCalls;preview.walking_->process(id);
        preview.globals_.tick=signed32(std::uint32_t(preview.globals_.tick)+1u);}
    if(int(scheduled.size())!=notifications)throw std::logic_error("Boot Camp scheduled update-position preview did not reach selected-head arrivals");
    const auto translate=[this,&preview](std::uintptr_t identity){
        for(std::size_t i=0;i<preview.map_->cells.size();++i)
            if(identity==reinterpret_cast<std::uintptr_t>(&preview.map_->cells[i].attributes.input))
                return reinterpret_cast<std::uintptr_t>(&map_->cells[i].attributes.input);
        if(identity==reinterpret_cast<std::uintptr_t>(&preview.map_->fallback.input))
            return reinterpret_cast<std::uintptr_t>(&map_->fallback.input);
        throw std::logic_error("Discarded Boot Camp preview returned a foreign Cell identity");
    };
    for(auto& result:scheduled){
        result.currentCell=translate(result.currentCell);result.targetCell=translate(result.targetCell);
        result.positionCell=translate(result.positionCell);result.dirtyCell=translate(result.dirtyCell);
    }
    return scheduled;
}
BootCampWalkWorld::PositionCompositionResult BootCampWalkWorld::composeUpdatePositionPreviewOwned(int id){
    auto& a=actors_.at(id);auto& sight=sight_.at(id);
    PositionCompositionResult result;
    auto& position=positions_.at(id);
    result.initialDiscovered=a.object.mission.current373;
    result.initialState59a=position.state59a;result.initialState59c=position.state59c;result.initialScratch=positionScratch_;
    const void* locomotor=&a.walk; // Stable actual Walk owner, not a token or a copied record.
    const auto resident=[this,&result](std::uintptr_t cell){
        ++result.residentSearches;const auto found=walking_->findKind6(cell,residentSearch_);
        result.kindQueries+=found.kindQueries;result.nextReads+=found.nextReads;return found.resident;
    };
    const auto mission=[&]{++result.missionQueries;return unitDiscoveryMission(a.object.mission);};
    InfantryUpdatePositionE1Services parent;
    parent.mission=mission;
    parent.cell=[this,&result](const Coord& point){
        ++result.parentCellQueries;const auto cell=walking_->cellIdentity(point);
        if(result.parentCellQueries==1)result.currentCell=cell;else if(result.parentCellQueries==2)result.targetCell=cell;
        return cell;
    };
    parent.currentCell=[this,&result,&a]{
        ++result.currentCellGetters;
        ++result.currentCellMapQueries;const auto first=walking_->cellIdentity(a.ground.position);
        ++result.currentCellMapQueries;const auto second=walking_->cellIdentity(a.ground.position);
        if(first!=second||first!=result.currentCell)throw std::logic_error("Boot Camp current-Cell getter identity changed");
        return second;
    };
    parent.cellValue=[&](std::uintptr_t){++result.cellValueQueries;return 7;}; // Supplied +EC association.
    parent.findKind6=resident;
    parent.findKind2=[&](std::uintptr_t,bool){++result.kind2Queries;return nullptr;};
    parent.findKind1=[&](std::uintptr_t,bool){++result.kind1Queries;return nullptr;};
    parent.targetKind=[this,&result](const void* target){
        ++result.targetKindQueries;const int cell=walking_->membership().cellId(target);
        if(cell<0||std::size_t(cell)>=map_->cells.size())throw std::invalid_argument("Boot Camp update-position target is not an actual Cell");
        return 11;
    };
    parent.targetCoordinates=[this,&result](const void* target){++result.targetCoordinateQueries;return walking_->targetCoordinates(target);};
    parent.locomotorPredicate=[&](const void* owner){++result.locomotorQueries;return owner==locomotor&&a.walk.moving34!=0;};
    const auto visibilityBefore=visibilityWorld_->state();
    parent.sight.missionTransition=[this,id,&result]{++result.sightMissionCalls;(void)walking_->commence(id);};
    parent.sight.removeSight=[this,id,&result](auto first,auto second,auto explicitOnly,auto explicitHouse){
        ++result.sightRemoveCalls;removeSight(id,first,second,explicitOnly,explicitHouse);};
    parent.sight.addSight=[this,id,&result](auto first,auto second,auto explicitOnly,auto explicitHouse){
        ++result.sightAddCalls;addSight(id,first,second,explicitOnly,explicitHouse);};
    parent.sight.postSight=[this,&result](Coord coordinates,auto inner,auto outer,auto disabled){
        ++result.sightPostCalls;visibilityWorld_->refreshPostSight(coordinates,inner,outer,disabled);};

    InfantryPositionEffectsE1Services effects;
    effects.alternateQuery=[&](const void* target){
        ++result.alternateQueries;InfantryWeaponSelectionServices selection;
        selection.type=[&]() -> const auto& {++result.alternateTypeQueries;return type_.weaponSelection;};
        selection.mission=[&]{++result.alternateMissionQueries;return unitDiscoveryMission(a.object.mission);};
        result.alternateResult=selectInfantryWeaponForNullTarget(
            {a.state5ac,a.currentTurret10c,a.veterancy118,a.object.kind},target,selection);
        return result.alternateResult;
    };effects.mission=mission;
    effects.cellPoint=[&]{++result.effectCellPointQueries;const auto word=[](int value){return std::bit_cast<std::int16_t>(std::uint16_t(value/256));};return TerrainCellPoint{word(a.ground.position.x),word(a.ground.position.y)};};
    effects.cell=[this,&result](TerrainCellPoint point){++result.effectCellQueries;if(result.effectCellQueries>1)++result.mapAssociationCalls;auto& cell=walking_->cellInput(point);
        return InfantryPositionEffectsE1Cell{reinterpret_cast<std::uintptr_t>(&cell),point,cell.flags,std::uint8_t(visibilityWorld_->at(point).flags12c),nullptr};};
    effects.findKind6=resident;
    effects.permission=[this,&result](TerrainCellPoint point,bool high){++result.permissionQueries;
        return mapCellPermitted({point.x,point.y},high,map_->resident.permission,{map_->table,&map_->fallback.input,{},{}});};
    effects.positionChild3b8=[this,&result,&a]{
        ++result.positionChildCalls;
        PositionCloakEffectServices cloak;
        cloak.cell=[this,&result](TerrainCellPoint point){
            auto view=walking_->membership().walkMap().word(point);
            auto& attributes=walking_->membership().walkMap().attributes(view);
            result.positionCell=reinterpret_cast<std::uintptr_t>(view.identity);
            return PositionCloakEffectCell{result.positionCell,point,attributes.cloakedByHouses};
        };
        cloak.actorPredicate280=[&result]{++result.positionCloakPredicateQueries;return false;};
        result.positionCloakExit=int(applyPositionCloakEffectPrefix(
            {a.ground.position,a.object.mission.owner},cloak));
    };
    effects.dirty=[this,&result](std::uintptr_t identity){
        ++result.dirtyCalls;const int cell=walking_->membership().cellId(reinterpret_cast<const void*>(identity));
        result.dirtyCell=identity;
        result.dirtyPrefixExit=int(dirtyCell(cell));
    };
    effects.discover=[this,&result,&a,&position]{
        if(position.target34||a.object.mission.hasTag)throw std::invalid_argument("Boot Camp position discovery requires actual null actor34/Tag");
        ++result.discoveryCalls;(void)missionWorld_->discoverInfantry(a.object.mission);
    };
    effects.scratchStore=[&](std::int32_t value){++result.scratchStores;positionScratch_=value;};

    updateInfantryPositionE1WithEffects(
        {a.ground.position,a.object.mission.queuedA0,a.target494,position.alternate228,locomotor,
         sight_.at(id).lastRange1f4,a.ground.bridge79,a.onMap7d,a.special370,positionTypeSpecial_},
        {a.ground.position,position.alternate228,position.effect208,position.target34,position.mode1b8,position.animation418,
         position.footprintX454,position.footprintY456,a.ground.bridge79,a.onMap7d,position.flag77,a.flag32d,
         a.object.mission.current373,position.state59a,position.state59c,positionTypeFootprint_},2,parent,effects);
    result.permissionSuccessContinuation=true;
    const auto missionAfter=missionWorld_->state();result.finalMissionTextRequests=missionAfter.textRequests;
    for(auto* node=missionWorld_->messages().list().head;node;node=node->next)++result.finalMissionMessageLines;
    result.finalMissionDeferred=missionAfter.deferred;result.finalMissionTagInstances=missionAfter.tagInstances;
    result.tailActiveStore=a.flag32d;result.finalDiscovered=a.object.mission.current373;
    const auto& house=missionWorld_->house(a.object.mission.owner);
    result.finalOwner5668=house.field5668;result.finalOwner5669=house.field5669;result.finalOwner13c=house.discovered13c;
    result.finalState59a=position.state59a;result.finalState59c=position.state59c;result.finalScratch=positionScratch_;
    const auto visibilityAfter=visibilityWorld_->state();
    result.sightRevealAreas=int(visibilityAfter.revealAreas-visibilityBefore.revealAreas);
    result.sightReveals=int(visibilityAfter.sightAdds-visibilityBefore.sightAdds);
    result.sightRemovals=int(visibilityAfter.sightRemovals-visibilityBefore.sightRemovals);
    result.sightMaskCalls=int(visibilityAfter.maskCalls-visibilityBefore.maskCalls);
    result.sightRedraws=int(visibilityAfter.redraws-visibilityBefore.redraws);
    result.sightFinalRange=sight.lastRange1f4;result.sightFinalActive=sight.active1e4;
    if(position.state59a||position.state59c||positionScratch_||a.flag32d!=1)throw std::logic_error("Boot Camp discarded position preview stores differ");
    return result;
}
int BootCampWalkWorld::sightActorId(const void* p)const{
    for(const auto& [id,a]:actors_)if(p==&a)return id;
    for(int id:{1019675,1019676})if(p==missionWorld_->structureResident(id).identity)return id;
    throw std::invalid_argument("Foreign Boot Camp sight actor");
}
TechnoSightActor BootCampWalkWorld::sightActor(int id){
    if(actors_.contains(id)){
        auto& a=actors_.at(id);auto& s=sight_.at(id);
        return {a.flag32d,s.ownerCountryFlag1a6,a.ground.position,a.veterancy118,s.heightIncrease378,
            s.active1e4,s.lastCoordinates1e8,s.lastRange1f4,
            a.flag32d&&!s.ownerCountryFlag1a6?visibilityWorld_->house(a.object.mission.owner):nullptr};
    }
    auto a=missionWorld_->structureSight(id);auto& s=a.fields.sight;
    return {a.fields.enabled32d,s.ownerCountryFlag1a6,a.position,a.fields.veterancy118,s.heightIncrease378,
        s.active1e4,s.lastCoordinates1e8,s.lastRange1f4,
        a.fields.enabled32d&&!s.ownerCountryFlag1a6?visibilityWorld_->house(a.discovery.owner):nullptr};
}
TechnoSightType BootCampWalkWorld::sightType(int id){
    if(actors_.contains(id))return {veteranSight_,eliteSight_,sightRange_};
    const auto& t=missionWorld_->structureSightType(id);return {t.veteranSight271,t.eliteSight283,t.sight530};
}
void BootCampWalkWorld::dispatchSight(int id,int slot,std::uint32_t first,std::uint32_t second,
        std::uint32_t explicitOnly,const void* explicitHouse){
    const auto actor=sightActor(id);
    if(slot==0x41c){
        TechnoSightRemovalServices removal;removal.revealArea=[this](const TechnoSightRequest& r){visibilityWorld_->revealSight(r);};
        removeTechnoSight({actor.enabled32d,actor.ownerCountryFlag1a6,actor.sightActive1e4,
            actor.lastSightCoordinates1e8,actor.lastSightRange1f4,actor.owner},first,second,explicitOnly,explicitHouse,removal);
    }else if(slot==0x418){
        TechnoSightServices update;update.type=[this,id]{return sightType(id);};
        update.heightDivisor1324=[this]()->const std::int32_t&{return sightHeightDivisor_;};
        update.veteranSight5a0=[this]()->const double&{return veteranSightMultiplier_;};
        update.revealArea=[this](const TechnoSightRequest& r){visibilityWorld_->revealSight(r);};
        updateTechnoSight(actor,first,second,explicitOnly,explicitHouse,update);
    }else throw std::invalid_argument("Unknown stock sight slot");
}
void BootCampWalkWorld::removeSight(int id,std::uint32_t a,std::uint32_t b,std::uint32_t c,std::uint32_t d){
    if(a||b||c||d)throw std::invalid_argument("Boot Camp arrival sight supports only exact zero child arguments");
    dispatchSight(id,0x41c,0,0,0,nullptr);
}
void BootCampWalkWorld::addSight(int id,std::uint32_t a,std::uint32_t b,std::uint32_t c,std::uint32_t d){
    if(a||b||c||d)throw std::invalid_argument("Boot Camp arrival sight supports only exact zero child arguments");
    dispatchSight(id,0x418,0,0,0,nullptr);
}
std::int32_t BootCampWalkWorld::composeActorThreat(int id,const std::int32_t& rulesBE8){
    const bool infantry=actors_.contains(id);
    const std::int32_t unused564=0; // This field is never entered for stock Infantry kind15.
    const auto& field564=infantry?unused564:missionWorld_->structureSight(id).fields.field564;
    TechnoThreatServices services;
    services.type80=[this,id,infantry]()->const void*{
        return infantry?static_cast<const void*>(&threat598_):&missionWorld_->structureSightType(id);
    };
    services.kind2C=[infantry]{return infantry?15:6;};
    services.value598=[this,id,infantry](const void* p)->const std::int32_t&{
        if(infantry){if(p!=&threat598_)throw std::invalid_argument("Foreign Boot Camp Infantry threat type");return threat598_;}
        const auto& type=missionWorld_->structureSightType(id);
        if(p!=&type)throw std::invalid_argument("Foreign Boot Camp Building threat type");return type.threat598;
    };
    return technoThreat(field564,rulesBE8,services);
}
void BootCampWalkWorld::composeHouseThreatGrid(int houseId,std::span<const std::int32_t,18> tables,const std::int32_t& rulesBE8,TerrainCellPoint invalidCell){
    // Validate the requested owner before any grid clear or map query.
    const auto current=visibilityWorld_->house(houseId);
    if(!current)throw std::invalid_argument("Missing Boot Camp threat House");
    const auto houseKey=[this](const void* p){
        for(const auto& [id,h]:missionWorld_->houses())if(p==&h.indexAlliance)return id;
        throw std::invalid_argument("Foreign Boot Camp threat House");
    };
    HouseThreatWorld grid{missionWorld_->discoveryMode(),sightCount_,sightSlots_,{invalidCell.x,invalidCell.y},tables.first<9>(),tables.last<9>()};
    grid.house=[this,houseKey](const void* p){
        const int id=houseKey(p);auto& h=missionWorld_->house(id);auto& state=missionWorld_->houseThreat(id);
        return HouseThreatHouse{p,h.indexAlliance.countryIndex,h.field13d,h.human134,h.control135,h.indexAlliance.allianceMask,
            state.enemy54F0,state.count5504,state.slots,state.grid};
    };
    grid.actor=[this](const void* p)->HouseThreatActor{
        const int id=sightActorId(p);
        const auto owner=[this,id]()->const void*{
            const int key=actors_.contains(id)?actors_.at(id).object.mission.owner:missionWorld_->structureSight(id).discovery.owner;
            return key==-1?nullptr:visibilityWorld_->house(key);
        };
        if(actors_.contains(id)){const auto& a=actors_.at(id);const auto& position=positions_.at(id);
            return {a.flag76,a.onMap7d,HouseThreatOwner{std::function<const void*()>(owner)},{position.footprintX454,position.footprintY456}};}
        const auto& a=missionWorld_->structureSightState(id);
        return {a.flag76,a.onMap7d,HouseThreatOwner{std::function<const void*()>(owner)},{a.cell454,a.cell456}};
    };
    grid.threat2A0=[this,&rulesBE8](const void* p){return composeActorThreat(sightActorId(p),rulesBE8);};
    grid.kind2C=[this](const void* p){return actors_.contains(sightActorId(p))?15:6;};
    HouseActorThreatCellServices cells;
    cells.position88=[this](const void* p)->const Coord&{
        const int id=sightActorId(p);return actors_.contains(id)?actors_.at(id).ground.position:missionWorld_->structureSight(id).position;
    };
    cells.coordinateCell=[this](Coord point){
        // Borrow actual mutable table/Cells and forward misses to its one fallback.
        MapFloorHeightWorld world{map_->table,&map_->fallback.input,{}};
        const auto& cell=mapCoordinateCell(point,world,int(map_->table.size()));
        return HouseThreatCell{cell.position.x,cell.position.y};
    };
    HouseActorThreatCells binding(grid,cells);rebuildHouseThreatGrid(current,grid);
}
void BootCampWalkWorld::composeHouseMapSight(bool addition,std::uint8_t skipBuildings,std::int32_t argument){
    const auto houseId=[this](const void* p){
        for(const auto& [id,h]:missionWorld_->houses())if(p==visibilityWorld_->house(id))return id;
        throw std::invalid_argument("Foreign Boot Camp map-sight House");
    };
    const auto current=[this]()->const void*{return visibilityWorld_->house(missionWorld_->currentHouse());};
    HouseMapRefreshWorld world{sightCount_,sightSlots_,HouseMapRefreshOwner{std::function<const void*()>(current)},visibilityWorld_->alliedVision()};
    world.actor=[this](const void* p)->HouseMapRefreshActor{
        const int id=sightActorId(p);
        const auto owner=[this,id]()->const void*{
            const int h=actors_.contains(id)?actors_.at(id).object.mission.owner:missionWorld_->structureSight(id).discovery.owner;
            return visibilityWorld_->house(h);
        };
        if(actors_.contains(id)){const auto& a=actors_.at(id);const auto& s=sight_.at(id);const auto& point=a.ground.position;
            return {a.flag76,a.object.mission.current373,HouseMapRefreshOwner{std::function<const void*()>(owner)},s.lastRange1f4,point.x,point.y,point.z};}
        const auto a=missionWorld_->structureSight(id);const auto& point=a.position;
        return {a.fields.flag76,a.discovery.current373,HouseMapRefreshOwner{std::function<const void*()>(owner)},a.fields.sight.lastRange1f4,point.x,point.y,point.z};
    };
    world.localHouse=[this,houseId,current](const void* p){const auto& h=missionWorld_->house(houseId(p));
        return unitOwnerTypeVisible(missionWorld_->discoveryMode(),h.human134,h.control135,p==current());};
    world.allied=[houseId,this](const void* p,const void* q){
        (void)houseId(p);(void)houseId(q);const auto& a=*static_cast<const RevealAreaHouse*>(p);const auto& b=*static_cast<const RevealAreaHouse*>(q);
        return unitOwnerAlliedToCurrent(true,p==q,a.countryIndex,b.countryIndex,a.allianceMask);
    };
    world.kind2C=[this](const void* p){return actors_.contains(sightActorId(p))?15:6;};
    world.type80=[this](const void* p)->HouseMapRefreshType{
        const int id=sightActorId(p);if(actors_.contains(id))return {sightType534_,sightTypeADD_};
        const auto& t=missionWorld_->structureSightType(id);return {t.flag534,t.flagADD};
    };
    world.sight=[this](const void* p,int slot,int a,int b,int c,const void* h){dispatchSight(sightActorId(p),slot,std::uint32_t(a),std::uint32_t(b),std::uint32_t(c),h);};
    world.image=[](const void*,int){throw std::invalid_argument("Boot Camp map-sight image effect is unbound");};
    world.postSight=[this](std::array<std::int32_t,3> p,int inner,int outer,std::uint32_t disabled){visibilityWorld_->refreshPostSight({p[0],p[1],p[2]},inner,outer,disabled);};
    refreshHouseMapSight(addition,skipBuildings,argument,world);
}
void BootCampWalkWorld::composeSight(int id){
    if(!player(id))throw std::invalid_argument("Boot Camp sight composition supports only the player GI");
    removeSight(id,0,0,0,0);addSight(id,0,0,0,0);
}
void BootCampWalkWorld::composePostSight(int id){
    if(!player(id))throw std::invalid_argument("Boot Camp post-sight composition supports only the player GI");
    const auto& actor=actors_.at(id);const auto& sight=sight_.at(id);
    visibilityWorld_->refreshPostSight(actor.ground.position,0,
        signed32(std::uint32_t(sight.lastRange1f4)+3u),0);
}
void BootCampWalkWorld::composeArrivalSight(int id){
    if(!player(id))throw std::invalid_argument("Boot Camp arrival-sight composition supports only the player GI");
    auto& actor=actors_.at(id);auto& sight=sight_.at(id);InfantrySightScheduleServices services;
    services.missionTransition=[this,id]{walking_->commence(id);};
    services.removeSight=[this,id](auto a,auto b,auto c,auto d){removeSight(id,a,b,c,d);};
    services.addSight=[this,id](auto a,auto b,auto c,auto d){addSight(id,a,b,c,d);};
    services.postSight=[this](Coord p,auto inner,std::int32_t outer,auto disabled){
        if(inner||disabled)throw std::invalid_argument("Boot Camp arrival post-sight supports only exact zero fixed arguments");
        visibilityWorld_->refreshPostSight(p,0,outer,0);
    };
    scheduleInfantryArrivalSight({actor.ground.position,sight.lastRange1f4},services);
}
}
