// SPDX-License-Identifier: GPL-3.0-or-later
#include "platform/BootCampMissionWorld.hpp"
#include "assets/Archive.hpp"
#include "render/BuildingFrameRedraw.hpp"
#include "render/BuildingImageSelection.hpp"
#include "platform/MissionMessagePresentation.hpp"
#include "sim/MissionAllyAction.hpp"
#include "sim/MissionAudioAction.hpp"
#include "sim/MissionCreateTeamAction.hpp"
#include "sim/TeamCreation.hpp"
#include "sim/TeamConstruction.hpp"
#include "sim/TeamAdmission.hpp"
#include "sim/TeamMembership.hpp"
#include "sim/TeamRecruitment.hpp"
#include "sim/TeamReadiness.hpp"
#include "sim/TeamRecruitmentSchedule.hpp"
#include "sim/TeamCohesion.hpp"
#include "sim/TeamScript.hpp"
#include "sim/HouseAlliance.hpp"
#include "sim/MissionScriptState.hpp"
#include "sim/MissionConstruction.hpp"
#include "sim/MissionRevealAction.hpp"
#include "sim/MissionTagObjectExpiration.hpp"
#include "sim/MissionTextAction.hpp"
#include "sim/MissionTriggerControl.hpp"
#include "sim/MissionTriggerDestruction.hpp"
#include "sim/UnitDiscovery.hpp"
#include "sim/BuildingDiscovery.hpp"
#include "sim/WaypointTaggedDiscovery.hpp"
#include <algorithm>
#include <array>
#include <charconv>
#include <map>
#include <span>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <utility>
#include <vector>

namespace ra2 {
namespace {
// Synchronous host adapter shared by demand selection and Type bounds. It owns
// no extra image cache: immutable backing stays on the existing Type owner.
struct BuildingAssetImages {
    BootCampBuildingExpirationType& type;
    const AssetStore& assets;
    double rulesTiming;
    std::array<std::string,2> files;
    BuildingImageServices io;
    ShpBoundsView resolve(const void* p)const{
        if(!p)return {};
        for(const auto& backing:type.imageBacking)if(backing.get()==p)return shpBoundsView(*backing);
        throw std::invalid_argument("Unowned Building SHP identity");
    }
    BuildingAssetImages(BootCampBuildingExpirationType& t,const AssetStore& a,double timing):type(t),assets(a),rulesTiming(timing){
        io.construct=[this](int slot,const std::string& name){files.at(slot)=name;};
        io.cache=[](int,int){}; // Supplied host policy, not original File code.
        io.load=[this](int slot)->const void*{
            auto bytes=assets.find(files.at(slot));if(!bytes)return nullptr;
            auto image=std::make_shared<const ShpImage>(readShp(*bytes));const auto* p=image.get();
            type.imageBacking.push_back(std::move(image));return p;
        };
        io.finish=[this](int slot,int phase){if(phase==2)files.at(slot).clear();};
        io.frameCount=[this](const void* p){return resolve(p).count();};
        io.timing1178=[this]{return rulesTiming;};
    }
    BuildingAssetImages(const BuildingAssetImages&)=delete;
    BuildingAssetImages& operator=(const BuildingAssetImages&)=delete;
};
constexpr const char* ObjectiveTag="043bd15c";
constexpr const char* ObjectiveTrigger="043b011c";
constexpr std::array<const char*,4> ControlledTriggers{"0922d5dc","0922d40c","08fabe0c","09ca94ac"};
constexpr std::array<std::int32_t,4> ControlledTimerValues{220,100,85,38};
constexpr std::array<std::array<std::int32_t,4>,4> ControlledActionKinds{{
    {{11,55,41,-1}},{{11,55,41,-1}},{{55,21,11,41}},{{11,55,53,53}}
}};
std::int32_t integer(const std::string& text) {
    std::int32_t value=0;const auto [end,error]=std::from_chars(text.data(),text.data()+text.size(),value);
    if(error!=std::errc{}||end!=text.data()+text.size())throw std::invalid_argument("Invalid Boot Camp mission integer");
    return value;
}
int houseIndex(const MissionDefinition& mission,const std::string& name) {
    const auto normalized=[](std::string value){value=lower(value);constexpr std::string_view suffix=" house";
        if(value.size()>suffix.size()&&value.ends_with(suffix))value.resize(value.size()-suffix.size());return value;};
    for(const auto& [id,candidate]:mission.houses)if(normalized(candidate)==normalized(name))return id;
    throw std::invalid_argument("Missing Boot Camp mission House association");
}
int controlledTriggerHouseIndex(const MissionDefinition& mission,const std::string& name) {
    if(lower(name)=="americans")return houseIndex(mission,mission.player);
    return houseIndex(mission,name);
}
struct EventOwner {
    std::int32_t kind=0,value=0;MissionTriggerEvent* next=nullptr;MissionTriggerEvent view;
    EventOwner(std::int32_t k,std::int32_t v):kind(k),value(v),view{kind,value,next}{}
};
struct ActionOwner {
    MissionTriggerAction* next=nullptr;MissionTriggerAction view;const MissionActionDefinition& definition;
    explicit ActionOwner(const MissionActionDefinition& d):view{next},definition(d){}
};
struct TriggerOwner {
    MissionConstructionBase base;
    std::int32_t countryIndex=0;MissionTriggerCountry country;MissionTriggerCountry* countryPointer=nullptr;
    MissionTriggerEvent* eventPointer=nullptr;MissionTriggerAction* actionPointer=nullptr;MissionTriggerType type;
    MissionTriggerType* typePointer=nullptr;std::uint8_t destroyed=0,enabled=1,suppress=0;
    std::array<std::uint8_t,3> difficultyAllowed{};
    MissionEventTimer timer{};std::int32_t timerPadding=0;std::uint32_t occurred=0;
    MissionTriggerServices services;MissionTriggerState state;MissionTagTrigger* next=nullptr;MissionTagTrigger view;
    TriggerOwner(std::int32_t house,MissionTriggerEvent* event,MissionTriggerAction* action,const std::int32_t& frame,
                 std::uint8_t initialEnabled,std::array<std::uint8_t,3> allowed):
        countryIndex(house),country{countryIndex},countryPointer(&country),eventPointer(event),actionPointer(action),
        type{countryPointer,eventPointer,actionPointer},typePointer(&type),enabled(initialEnabled),difficultyAllowed(allowed),services{frame,suppress},
        state{typePointer,destroyed,enabled,timer,timerPadding,occurred},view{state,services,next}{}
};
struct ControlledTriggerOwner {
    const MissionTriggerDefinition& definition;
    std::vector<std::unique_ptr<EventOwner>> events;
    std::vector<std::unique_ptr<ActionOwner>> actions;
    std::unique_ptr<TriggerOwner> trigger;
    std::unique_ptr<MissionTriggerControlRecord> control;
    std::int32_t timerScratch=0;
    ControlledTriggerOwner(const MissionDefinition& mission,const MissionTriggerDefinition& d,
                           const std::int32_t& frame,std::int32_t expectedTimer,
                           const std::array<std::int32_t,4>& expectedActions):definition(d) {
        if(d.linked!="<none>"||d.flags!=std::array<std::int32_t,5>{1,1,1,1,0}||d.events.size()!=1||
           d.events[0].kind!=13||d.events[0].mode!=0||integer(d.events[0].argument)!=expectedTimer)
            throw std::invalid_argument("Unsupported Day1 controlled Trigger record");
        const auto expectedCount=std::size_t(expectedActions[3]<0?3:4);
        if(d.actions.size()!=expectedCount)throw std::invalid_argument("Unsupported Day1 controlled Trigger actions");
        for(std::size_t i=0;i<expectedCount;++i)if(d.actions[i].kind!=expectedActions[i])
            throw std::invalid_argument("Unsupported Day1 controlled Trigger action kind");
        for(const auto& source:d.events)events.push_back(std::make_unique<EventOwner>(source.kind,integer(source.argument)));
        for(std::size_t i=0;i+1<events.size();++i)events[i]->next=&events[i+1]->view;
        for(const auto& source:d.actions)actions.push_back(std::make_unique<ActionOwner>(source));
        for(std::size_t i=0;i+1<actions.size();++i)actions[i]->next=&actions[i+1]->view;
        trigger=std::make_unique<TriggerOwner>(controlledTriggerHouseIndex(mission,d.house),&events.front()->view,&actions.front()->view,frame,
            std::uint8_t(!d.flags[0]),std::array<std::uint8_t,3>{std::uint8_t(d.flags[1]),std::uint8_t(d.flags[2]),std::uint8_t(d.flags[3])});
        trigger->services.resetPadding=[this]{return timerScratch;};
        control=std::make_unique<MissionTriggerControlRecord>(MissionTriggerControlRecord{
            trigger->state,trigger->services,trigger->difficultyAllowed,&trigger->view});
    }
};
struct TagOwner {
    MissionConstructionBase base;const void* link30=nullptr;
    std::int32_t persistence=0,instances=0;std::uint8_t executing=0,destroyed=0;
    MissionTagType type;MissionTagType* typePointer=nullptr;MissionTagTrigger* first=nullptr;MissionTagState view;
    explicit TagOwner(std::int32_t policy):persistence(policy),type{persistence},typePointer(&type),view{typePointer,first,instances,executing}{}
};
struct StructureOwner {
    int actorKey=0,house=0;MissionTagState* tag=nullptr;
    // Supplied startup association from the numeric rules declaration. Original
    // BuildingType registry construction/INI order is not yet reconstructed.
    BootCampBuildingExpiration expiration;
    BootCampMissionWorld::StructureResidentState resident;
    BootCampMissionWorld::StructureSightState sight;
    UnitDiscoveryActor discovery{};std::unique_ptr<MissionTagExpirationRecipient> recipient;
};
}

struct BootCampMissionWorld::Impl {
    const MissionDefinition& mission;
    const Ini source;
    const Ini rules;
    std::shared_ptr<const PreparedStringLookup> strings;
    const MessageColorTable colors;
    std::unique_ptr<OwnedMessagePresentation> messages;
    const std::int32_t& frame;
    const MissionTriggerDefinition& triggerDefinition;
    TagOwner tag;
    std::unique_ptr<EventOwner> event;
    std::vector<std::unique_ptr<ActionOwner>> actions;
    std::unique_ptr<TriggerOwner> trigger;
    std::unique_ptr<MissionTriggerControlRecord> objectiveControl;
    std::array<std::unique_ptr<ControlledTriggerOwner>,4> controlled;
    std::int32_t difficulty=0;
    std::span<MissionTriggerControlRecord*> controlProjection;
    std::unique_ptr<MissionTriggerControlRegistry> controlRegistry;
    std::map<int,std::unique_ptr<StructureOwner>> structures;
    UnitDiscoveryWorld discovery;
    std::map<std::string,std::unique_ptr<HouseCountryType>> countryTypes;
    std::array<HouseCountryType*,64> countryBacking{};
    std::int32_t countryCount=0,countryCapacity=64,countryIncrement=10;
    std::uint8_t countryAllocated=1; // Supplied bounded registry startup.
    std::map<int,HouseThreatState> threatHouses;
    // Persistent physical House slots. Numeric scenario order/count are supplied startup.
    std::vector<const void*> houseBacking;
    std::span<const void*> houseSlots;
    std::int32_t houseCount=0;
    std::map<std::string,std::unique_ptr<BootCampBuildingExpirationType>> buildingTypes;
    std::function<const void*(int)> externalResident;
    std::function<int(const void*)> externalResidentId;
    std::function<std::uint8_t(std::int32_t)> waypointReveal;
    std::int32_t expirationSession=0,expirationRetryPadding=0;
    const std::uint8_t expirationTagFlags=0; // Actual Tag profile, supplied startup.

    StructureOwner* activeObject=nullptr;
    double messageDelay=0;
    std::uint8_t alternateTextColor=0; // Supplied scenario startup value.
    std::size_t textRequests=0;
    std::string textKey,textPayload;
    std::int32_t textColorSelector=0,textColor=0,textStyle=0;
    std::uint32_t textDuration=0;
    std::size_t allyCalls=0;
    std::int32_t allyValue=-1;
    std::array<std::int32_t,2> allyFrom{{-1,-1}},allyTo{{-1,-1}};
    std::array<std::uint8_t,2> allyAnnounce{};
    std::size_t soundRequests=0,speechRequests=0;
    std::string soundToken,speechToken;
    std::int32_t soundIndex=-1,soundPanning=0,speechIndex=-1,speechMode=0,speechParameter=0;
    std::uint32_t soundVolumeBits=0;bool soundController=false;
    int createTeamIdentity=0;std::uint32_t teamCreationDepth=0,createTeamDepthAtCall=0;
    std::size_t createTeamRequests=0,createTeamFactoryCalls=0,createTeamAllocations=0;
    TeamConstructionRecord createdTeam;
    bool teamConstructed=false;
    std::uint8_t teamHouseFlag=0; // Supplied unset startup field; not an INI-loader proof.
    std::int32_t teamTypeCount=0;
    int teamScriptTypeIdentity=0;
    const void* teamTagType=nullptr;const void* teamScriptType=&teamScriptTypeIdentity;
    std::unique_ptr<TagOwner> teamTag;
    std::unique_ptr<TriggerOwner> teamTrigger;
    std::unique_ptr<MissionTriggerControlRecord> teamTriggerControl;
    std::vector<std::unique_ptr<EventOwner>> teamEvents;
    std::vector<std::unique_ptr<ActionOwner>> teamActions;
    std::array<std::uint8_t,4> teamTriggerPermissions{};
    MissionTriggerConstructionType* teamTriggerNext=nullptr;
    MissionTriggerConstructionType* teamFirstType=nullptr;
    std::unique_ptr<MissionTriggerConstructionType> teamTriggerConstructionType;
    std::unique_ptr<MissionTriggerConstructionView> teamTriggerConstruction;
    std::unique_ptr<MissionTagConstructionType> teamTagConstructionType;
    MissionScriptConstructionRecord teamScript;
    std::vector<MissionScriptAction> teamScriptActions;
    std::int32_t teamScriptActionCount=0;
    bool teamTagConstructed=false,teamTriggerConstructed=false,teamScriptConstructed=false;
    std::int32_t scriptCount=0,scriptCapacity=8,scriptIncrement=10;std::uint8_t scriptAllocated=1;
    std::array<const void*,8> scriptBacking{};std::span<const void*> scriptSlots{scriptBacking};
    TeamConstructionType teamType{&createTeamIdentity,teamHouseFlag,teamTypeCount,teamTagType,teamScriptType};
    std::uint32_t teamHouseCount=0;TeamConstructionHouse teamHouse{nullptr,teamHouseCount};
    std::size_t teamTagChildRequests=0,teamScriptChildRequests=0;
    // Supplied native registry startup for the three additional physical owners:
    // Team866178, genericAC0D60, AC0D30. SharedAC0CB0 and recipientAC0C58
    // below borrow the already-live mission owners, including their counts.
    std::array<std::int32_t,3> teamRegistryCount{};
    std::array<std::array<const void*,8>,3> teamRegistryBacking{};
    std::array<std::span<const void*>,3> teamRegistrySlots{teamRegistryBacking[0],teamRegistryBacking[1],teamRegistryBacking[2]};
    MissionTagExpirationRecipient teamRecipient;
    std::string createTeamId;std::int32_t createTeamArgument=-1;
    std::size_t revealRequests=0,revealCreateTeamRequestsAtCall=0,revealSoundRequestsAtCall=0;
    std::int32_t revealWaypoint=-1,revealHouse=-1,revealObject=-1;
    bool revealTrigger=false;std::uint32_t revealPackedCell=0;

    std::int32_t deferredCapacity=8,deferredCount=0,deferredGrowth=2;std::uint8_t deferredOwns=1;
    std::array<const void*,8> deferredBacking{};std::span<const void*> deferredSlots{deferredBacking};
    MissionDeferredDelete deferred{deferredCapacity,deferredOwns,deferredCount,deferredGrowth,deferredSlots,{}};

    std::array<std::int32_t,4> registryCount{};
    std::array<std::array<const void*,16>,4> registryBacking{};
    std::array<std::int32_t,4> registryCapacity{16,16,16,16},registryIncrement{10,10,10,10};
    std::array<std::uint8_t,4> registryAllocated{1,1,1,1};
    std::array<std::span<const void*>,4> registrySlots{registryBacking[0],registryBacking[1],registryBacking[2],registryBacking[3]};
    std::array<int,4> registryIdentity{};
    std::array<std::unique_ptr<MissionExpirationVector<const void*>>,4> registries;

    std::int32_t recipientCount=0;std::array<MissionTagExpirationRecipient*,4> recipientBacking{};
    std::span<MissionTagExpirationRecipient*> recipientSlots{recipientBacking};int recipientIdentity=0;
    std::unique_ptr<MissionExpirationVector<MissionTagExpirationRecipient*>> recipients;
    const void* tagLink30=nullptr;std::unique_ptr<MissionTagExpiredAbstract> expiredTag;
    std::int32_t pointCount=0;std::array<std::uint32_t,1> pointBacking{};std::span<std::uint32_t> pointSlots{pointBacking};int pointIdentity=0;
    std::unique_ptr<MissionExpirationVector<std::uint32_t>> points;
    std::uint32_t fallbackPoint=0;MissionTagState* fallbackTag=nullptr;const void* fallback2c=nullptr;const void* fallback30=nullptr;const void* fallbackContent=nullptr;int fallbackIdentity=0;
    std::unique_ptr<MissionExpirationCell> fallback;std::span<MissionExpirationCell* const> noCells;
    std::unique_ptr<MissionTagExpirationMap> expirationMap;
    const void* global680=nullptr;const void* global684=nullptr;
    std::unique_ptr<MissionTagExpirationServices> expiration;

    std::uint32_t emptyCell=0x7fff7fff;std::uint8_t sessionActive=0;
    std::unique_ptr<MissionTagServices> tagServices;
    std::unique_ptr<MissionTriggerDestructionServices> triggerDestruction;
    std::unique_ptr<MissionTagDestructionServices> tagDestruction;
    MissionDeferredCleanupRecord triggerRecord{},tagRecord{};
    std::unique_ptr<MissionDeferredCleanupServices> cleanup;
    bool triggerBase=false,triggerFreed=false,tagBase=false,tagFreed=false;

    const void* residentIdentity(int id)const {
        if(id==-1)return nullptr;
        if(id==-2)return &tag.view; // Diagnostic Abstract link, never an admitted resident.
        const auto found=structures.find(id);if(found!=structures.end())return found->second.get();
        if(externalResident)return externalResident(id);
        throw std::invalid_argument("Foreign Boot Camp resident identity");
    }
    int residentId(const void* p)const {
        if(!p)return -1;if(p==&tag.view)return -2;
        for(const auto& [id,a]:structures)if(p==a.get())return id;
        if(externalResidentId)return externalResidentId(p);
        throw std::invalid_argument("Foreign Boot Camp resident pointer");
    }
    MissionExpirationPointerView residentNext(StructureOwner& a){
        return {[this,&a]{return residentIdentity(a.resident.next);},[this,&a](const void* p){a.resident.next=residentId(p);}};
    }
    BootCampBuildingExpirationType& buildingType(const void* p){
        for(auto& [name,type]:buildingTypes)if(type.get()==p)return *type;
        throw std::invalid_argument("Foreign BuildingType identity");
    }
    const BootCampBuildingExpirationType& buildingType(const void* p)const{
        for(const auto& [name,t]:buildingTypes)if(p==t.get())return *t;
        throw std::invalid_argument("Foreign Boot Camp BuildingType");
    }
    Impl(const MissionDefinition& m,const Ini& source,const Ini& rules,const std::int32_t& f,std::shared_ptr<const PreparedStringLookup> s,const MessageColorTable& c,std::unique_ptr<OwnedMessagePresentation> presentation):mission(m),source(source),rules(rules),strings(std::move(s)),colors(c),messages(std::move(presentation)),frame(f),
        triggerDefinition(m.triggers.at(ObjectiveTrigger)),tag(m.tags.at(ObjectiveTag).persistence) {
        if(!messages)throw std::invalid_argument("Boot Camp mission requires owned messages");
        if(!strings)throw std::invalid_argument("Boot Camp mission requires supplied CSF lookup owners");
        const auto& tagDefinition=mission.tags.at(ObjectiveTag);
        if(tagDefinition.trigger!=ObjectiveTrigger||tagDefinition.persistence!=0||triggerDefinition.id!=ObjectiveTrigger||
           triggerDefinition.linked!="<none>"||triggerDefinition.flags!=std::array<std::int32_t,5>{0,1,1,1,0}||
           triggerDefinition.events.size()!=1||triggerDefinition.events[0].kind!=4||triggerDefinition.events[0].mode!=0||integer(triggerDefinition.events[0].argument)!=0||
           triggerDefinition.actions.size()!=10)
            throw std::invalid_argument("Unsupported Day1 objective mission records");
        constexpr std::array<std::int32_t,10> actionKinds{11,4,17,19,37,54,53,21,54,53};
        for(std::size_t i=0;i<actionKinds.size();++i)if(triggerDefinition.actions[i].kind!=actionKinds[i])
            throw std::invalid_argument("Unsupported Day1 objective action records");
        const auto& textDefinition=triggerDefinition.actions.front();
        if(textDefinition.mode!=4||textDefinition.arguments!=std::array<std::string,6>{"MISSION:Objective1","0","0","0","0","A"})
            throw std::invalid_argument("Unsupported Day1 objective text action");
        if(rules.get("AudioVisual","MessageDelay").empty())throw std::invalid_argument("Boot Camp MessageDelay is required");
        messageDelay=rules.number("AudioVisual","MessageDelay");
        const auto& createDefinition=triggerDefinition.actions[1];
        if(createDefinition.mode!=1||createDefinition.arguments!=std::array<std::string,6>{"0B197B7C","0","0","0","0","A"}||
           lower(source.get("0B197B7C","Name"))!="4 gis"||lower(source.get("0B197B7C","House"))!="other2"||
           std::none_of(source.section("TeamTypes").begin(),source.section("TeamTypes").end(),[](const auto& item){return lower(item.second)=="0b197b7c";}))
            throw std::invalid_argument("Unsupported Day1 objective Create Team record");
        const auto& revealDefinition=triggerDefinition.actions[2];
        if(revealDefinition.mode!=0||revealDefinition.arguments!=std::array<std::string,6>{"6","0","0","0","0","G"})
            throw std::invalid_argument("Unsupported Day1 objective Reveal Around Waypoint record");
        event=std::make_unique<EventOwner>(4,0);
        actions.reserve(triggerDefinition.actions.size());
        for(const auto& definition:triggerDefinition.actions)actions.push_back(std::make_unique<ActionOwner>(definition));
        for(std::size_t i=0;i+1<actions.size();++i)actions[i]->next=&actions[i+1]->view;
        trigger=std::make_unique<TriggerOwner>(houseIndex(mission,triggerDefinition.house),&event->view,&actions.front()->view,frame,
            std::uint8_t(!triggerDefinition.flags[0]),std::array<std::uint8_t,3>{std::uint8_t(triggerDefinition.flags[1]),std::uint8_t(triggerDefinition.flags[2]),std::uint8_t(triggerDefinition.flags[3])});
        tag.first=&trigger->view;
        trigger->services.resolveHouse=[this](std::int32_t id)->const void*{return &discovery.houses.at(id);};
        trigger->services.resetPadding=[] {throw std::invalid_argument("Objective discovery does not reset a timer");return 0;};
        trigger->services.executeAction=[this](MissionTriggerAction& action,const void* actionHouse,const void* actionObject,MissionTriggerState& actionTrigger,std::uint32_t& packedCell){
            for(const auto& owner:actions)if(&owner->view==&action) {
                const auto& definition=owner->definition;
                if(definition.kind==11) {
                    MissionTextServices text;
                    text.color=[this](std::int32_t selector){
                        textColorSelector=selector;
                        textColor=messageColor(selector,colors);
                        return textColor;
                    };
                    text.localize=[this](std::string_view key)->std::string_view{return strings->text(key);};
                    text.display=[this,&definition](const MissionTextRequest& request){
                        if(request.text!=strings->text(definition.arguments[0]))throw std::invalid_argument("Supplied Boot Camp localization payload differs");
                        insertMissionMessage(*messages,request);
                        ++textRequests;textKey=definition.arguments[0];textPayload=request.text;textColor=request.color;
                        textStyle=request.style;textDuration=request.duration;
                    };
                    return std::uint8_t(executeMissionTextAction(definition.arguments[0],alternateTextColor,messageDelay,text));
                }
                if(definition.kind==37) {
                    if(definition.mode!=0||definition.arguments!=std::array<std::string,6>{"13","0","0","0","0","A"})
                        throw std::invalid_argument("Unsupported Boot Camp Make Ally action");
                    const auto houseId=[this](const void* identity){
                        for(const auto& [id,house]:discovery.houses)if(identity==&house)return id;
                        throw std::invalid_argument("Foreign Boot Camp Make Ally House");
                    };
                    MissionAllyServices ally;
                    ally.resolveHouse=[this](std::int32_t value)->const void*{
                        if(value!=13)throw std::invalid_argument("Unsupported Boot Camp Make Ally lookup");
                        allyValue=value;return &discovery.houses.at(discovery.currentHouse);
                    };
                    ally.makeAlly=[this,houseId](const void* from,const void* to,std::uint8_t announce){
                        if(allyCalls>=allyFrom.size())throw std::invalid_argument("Unexpected Boot Camp Make Ally call");
                        allyFrom[allyCalls]=houseId(from);allyTo[allyCalls]=houseId(to);allyAnnounce[allyCalls]=announce;++allyCalls;
                    };
                    return std::uint8_t(executeMissionAllyAction(integer(definition.arguments[0]),actionHouse,ally));
                }
                if(definition.kind==4) {
                    if(definition.mode!=1||definition.arguments!=std::array<std::string,6>{"0B197B7C","0","0","0","0","A"})
                        throw std::invalid_argument("Unsupported Boot Camp Create Team action");
                    MissionCreateTeamServices team{teamCreationDepth,{}};
                    team.createTeam=[this,&definition](const void* identity,std::int32_t argument){
                        if(identity!=&createTeamIdentity)throw std::invalid_argument("Foreign Boot Camp TeamType identity");
                        if(argument)throw std::invalid_argument("Unsupported Boot Camp explicit Team House");
                        ++createTeamFactoryCalls;
                        // Supplied map-to-Type/House association. The recovered constructor
                        // below initializes the Team and children; membership remains pending.
                        const auto* house=&discovery.houses.at(houseIndex(mission,this->source.get("0B197B7C","House")));
                        const auto maximum=this->source.integer("0B197B7C","Max",-1);const std::int32_t count=0;
                        const auto name=this->source.get("0B197B7C","Name");const std::int32_t sessionMode=0;
                        TeamCreationServices factory{teamCreationDepth,sessionMode};
                        factory.logBegin=[]{};factory.logName=[](auto){}; // Diagnostic logging host adapter.
                        factory.houseCount4f35f0=[](auto,auto)->std::int32_t{throw std::invalid_argument("Boot Camp Team House count branch unbound");};
                        factory.allocate=[this](std::uint32_t size)->void*{
                            if(size!=156)throw std::invalid_argument("Team allocation size differs");
                            ++createTeamAllocations;return &createdTeam;
                        };
                        factory.construct6b7430=[this,&definition,house](void* record,const void* type,const void* owner,std::int32_t zero)->const void*{
                            if(record!=&createdTeam||type!=&createTeamIdentity||owner!=house||zero)
                                throw std::invalid_argument("Boot Camp Team constructor arguments differ");
                            ++createTeamRequests;createTeamId=definition.arguments[0];createTeamArgument=zero;
                            createTeamDepthAtCall=teamCreationDepth;
                            constructObjectiveTeam(owner);
                            return record; // Actual Tag/Trigger/Script construction; membership remains separate.
                        };
                        (void)createTeamFromType({identity,house,maximum,count,name},nullptr,factory);
                    };
                    return std::uint8_t(executeMissionCreateTeamAction(&createTeamIdentity,team));
                }
                if(definition.kind==17) {
                    if(definition.mode!=0||definition.arguments!=std::array<std::string,6>{"6","0","0","0","0","G"})
                        throw std::invalid_argument("Unsupported Boot Camp Reveal Around Waypoint action");
                    MissionRevealActionServices reveal;
                    reveal.revealAroundWaypoint=[this,&action,&definition](const void* actionIdentity,const void* house,const void* object,const void* triggerIdentity,const void* packed){
                        if(actionIdentity!=&action||object!=activeObject||triggerIdentity!=&trigger->state||!packed)
                            throw std::invalid_argument("Foreign Boot Camp Reveal Around Waypoint identity");
                        const auto houseId=[this](const void* identity){for(const auto& [id,item]:discovery.houses)if(identity==&item)return id;throw std::invalid_argument("Foreign Boot Camp Reveal House");};
                        ++revealRequests;revealWaypoint=integer(definition.arguments[0]);revealHouse=houseId(house);
                        revealObject=activeObject->actorKey;revealTrigger=true;revealPackedCell=*static_cast<const std::uint32_t*>(packed);
                        revealCreateTeamRequestsAtCall=createTeamRequests;revealSoundRequestsAtCall=soundRequests;
                        if(!waypointReveal)throw std::invalid_argument("Boot Camp waypoint reveal owner is unbound");
                        return std::uint32_t(waypointReveal(revealWaypoint));
                    };
                    return executeMissionRevealAroundWaypointAction(&action,actionHouse,{actionObject,1},&actionTrigger,&packedCell,reveal);
                }
                if(definition.kind==19) {
                    if(definition.mode!=7||definition.arguments!=std::array<std::string,6>{"HealCrate","0","0","0","0","A"})
                        throw std::invalid_argument("Unsupported Boot Camp sound action");
                    MissionAudioServices audio;
                    audio.playSound=[this,&definition](std::int32_t index,std::int32_t panning,std::uint32_t volume,const void* controller){
                        ++soundRequests;soundToken=definition.arguments[0];soundIndex=index;soundPanning=panning;
                        soundVolumeBits=volume;soundController=controller!=nullptr;
                    };
                    // Zero-based position in the supplied base sound.ini SoundList.
                    return std::uint8_t(executeMissionSoundAction(292,audio));
                }
                if(definition.kind==21) {
                    if(definition.mode!=6||definition.arguments!=std::array<std::string,6>{"Mis_T1_DrillSearg03","0","0","0","0","A"})
                        throw std::invalid_argument("Unsupported Boot Camp speech action");
                    MissionAudioServices audio;
                    audio.playSpeech=[this,&definition](std::int32_t index,std::int32_t mode,std::int32_t parameter){
                        ++speechRequests;speechToken=definition.arguments[0];speechIndex=index;speechMode=mode;speechParameter=parameter;
                    };
                    // Zero-based position in the supplied base eva.ini DialogList.
                    return std::uint8_t(executeMissionSpeechAction(247,audio));
                }
                if(definition.kind==53||definition.kind==54) {
                    if(definition.mode!=2)throw std::invalid_argument("Unsupported Boot Camp Trigger control mode");
                    const auto target=lower(definition.arguments[0]);
                    const auto found=std::find_if(controlled.begin(),controlled.end(),[&](const auto& item){return item&&item->definition.id==target;});
                    if(found==controlled.end())throw std::invalid_argument("Boot Camp Trigger control target is not owned");
                    auto* type=(*found)->trigger->typePointer;
                    return std::uint8_t(setMissionTriggerTypeEnabled(type,definition.kind==53,difficulty,*controlRegistry));
                }
                throw std::invalid_argument("Unsupported Boot Camp objective action");
            }
            throw std::invalid_argument("Foreign Boot Camp objective action");
        };
        for(std::size_t i=0;i<controlled.size();++i) {
            const auto& definition=mission.triggers.at(ControlledTriggers[i]);
            controlled[i]=std::make_unique<ControlledTriggerOwner>(mission,definition,frame,ControlledTimerValues[i],ControlledActionKinds[i]);
            controlled[i]->trigger->services.resolveHouse=[this](std::int32_t id)->const void*{return &discovery.houses.at(id);};
        }
        objectiveControl=std::make_unique<MissionTriggerControlRecord>(MissionTriggerControlRecord{
            trigger->state,trigger->services,trigger->difficultyAllowed,&trigger->view});
        controlRegistry=std::make_unique<MissionTriggerControlRegistry>(MissionTriggerControlRegistry{registryCount[0],controlProjection,
            [this](std::int32_t index)->MissionTriggerControlRecord*{
                const auto* identity=missionExpirationSlot(*registries[0],index);
                if(identity==&trigger->view)return objectiveControl.get();
                for(auto& owner:controlled)if(identity==&owner->trigger->view)return owner->control.get();
                if(teamTriggerConstructed&&identity==&teamTrigger->view)return teamTriggerControl.get();
                throw std::invalid_argument("Foreign actual Trigger in control registry");
            }});
        // Supplied startup list policy: numeric Rules order, then new map names
        // in numeric order. This is not recovered INI merging/inheritance.
        // The recovered registration suffix assigns B8; House30 stays separate.
        for(const auto* ini:{&rules,&source}){
            std::map<int,std::string> ordered;
            for(const auto& [key,name]:ini->section("Countries"))ordered.emplace(integer(key),name);
            int expected=0;
            for(const auto& [key,name]:ordered){
                if(key!=expected++||name.empty())throw std::invalid_argument("Unsupported supplied country list order");
                const auto normalized=lower(name);if(countryTypes.contains(normalized))continue;
                auto type=std::make_unique<HouseCountryType>();type->name=name;
                std::span<HouseCountryType*> slots{countryBacking};
                HouseCountryRegistration registry{&countryCount,countryCount,countryCapacity,countryAllocated,countryIncrement,slots};
                registerHouseCountryType(*type,registry);
                countryTypes.emplace(normalized,std::move(type));
            }
        }
        for(const auto& [id,name]:mission.houses) {
            auto& h=discovery.houses[id];h.human134=std::uint8_t(lower(name)==lower(mission.player));
            const auto country=countryTypes.find(lower(source.get(name,"Country")));
            if(country==countryTypes.end())throw std::invalid_argument("Missing supplied House country Type");
            h.countryType34=country->second.get();
            h.control135=std::uint8_t(source.boolean(name,"PlayerControl"));
            if(id<0||id>=32)throw std::invalid_argument("Boot Camp House index outside supplied association");
            std::uint32_t allies=0;std::istringstream names(source.get(name,"Allies"));std::string token;
            while(std::getline(names,token,',')){
                const auto first=token.find_first_not_of(" \t\r\n");if(first==std::string::npos)continue;
                token=lower(token.substr(first,token.find_last_not_of(" \t\r\n")-first+1));
                for(const auto& [other,otherName]:mission.houses)if(token==lower(otherName))allies|=1u<<unsigned(other);
            }
            h.indexAlliance={id,id,allies};threatHouses.try_emplace(id);
        }
        for(const auto& [id,h]:discovery.houses)houseBacking.push_back(&h);
        houseSlots=houseBacking;houseCount=std::int32_t(houseBacking.size());
        // Supplied map-to-House bookkeeping startup, not original constructors.
        // Seed the same owners used by discovery, Team and future transfer.
        std::map<std::string,int> infantryIndexes;int infantryCapacity=0;
        for(const auto& [index,name]:rules.section("InfantryTypes")){
            const int i=integer(index);if(i<0||i>=512)throw std::invalid_argument("InfantryType accounting outside bounded backing");
            if(!infantryIndexes.emplace(lower(name),i).second)throw std::invalid_argument("Duplicate InfantryType accounting name");
            infantryCapacity=std::max(infantryCapacity,i+1);
        }
        for(auto& [id,house]:discovery.houses){
            auto& counts=house.infantryAccounting;counts.activeCapacity=counts.registeredCapacity=infantryCapacity;
            counts.active5440.resize(std::size_t(infantryCapacity));counts.registered5480.resize(std::size_t(infantryCapacity));
        }
        for(const auto& actor:mission.actors)if(actor.kind==MissionActorKind::Infantry){
            const auto found=infantryIndexes.find(lower(actor.type));if(found==infantryIndexes.end())throw std::invalid_argument("Missing map InfantryType accounting");
            auto& counts=discovery.houses.at(houseIndex(mission,actor.house)).infantryAccounting;const auto i=std::size_t(found->second);
            ++counts.count234;++counts.active5440.at(i);++counts.registered5480.at(i);++counts.historyA70.at(i);
        }
        discovery.currentHouse=houseIndex(mission,mission.player);
        // Supplied AC0148/ABFE28 startup association: packed empty Cell, not force.
        discovery.tagContext=std::bit_cast<std::int32_t>(emptyCell);
        for(const auto& definition:mission.actors)if(definition.kind==MissionActorKind::Structure&&definition.tag==ObjectiveTag) {
            if(definition.key!=1019675&&definition.key!=1019676)throw std::invalid_argument("Unexpected first-objective structure identity");
            const bool first=definition.key==1019675;
            if(lower(definition.type)!=(first?"caarmy04":"caarmy01")||definition.x!=(first?71:69)||definition.y!=(first?92:96)||definition.health!=256)
                throw std::invalid_argument("Unexpected first-objective structure record");
            auto owner=std::make_unique<StructureOwner>();owner->actorKey=definition.key;owner->house=houseIndex(mission,definition.house);
            const auto typeName=lower(definition.type);auto& type=buildingTypes[typeName];
            if(!type){
                type=std::make_unique<BootCampBuildingExpirationType>();bool foundType=false;
                for(const auto& [index,name]:rules.section("BuildingTypes"))if(lower(name)==typeName){
                    if(foundType)throw std::invalid_argument("Repeated supplied objective BuildingType");
                    type->indexB90=integer(index);foundType=true;
                }
                if(!foundType)throw std::invalid_argument("Missing supplied objective BuildingType");
                type->strengthA0=integer(rules.get(definition.type,"Strength"));
                if(type->strengthA0<=0)throw std::invalid_argument("Unsupported objective Building Strength");
                type->threat598=rules.integer(definition.type,"ThreatPosed",0);
                type->sight530=rules.integer(definition.type,"Sight",0);
                if(type->sight530<0)throw std::invalid_argument("Unsupported objective Building Sight");
                // These stock objective types have no promoted sight abilities.
                // Do not silently admit an override without its ability loader.
                if(!rules.get(definition.type,"VeteranAbilities").empty()||!rules.get(definition.type,"EliteAbilities").empty())
                    throw std::invalid_argument("Unbound objective Building promoted abilities");
            }
            // Full authored health256 is admitted; original scenario construction
            // and the remaining zero-valued startup fields are not recovered.
            owner->expiration.state.type418=type.get();owner->expiration.state.health6C=type->strengthA0;
            owner->discovery.owner=owner->house;owner->discovery.mission98=-1;owner->discovery.queuedA0=-1;owner->discovery.hasTag=true;
            (void)setMissionObjectTag({owner->tag,owner.get()},&tag.view);
            structures.emplace(owner->actorKey,std::move(owner));
        }
        if(structures.size()!=2||tag.instances!=2)throw std::invalid_argument("Day1 objective structure ownership differs");

        registryBacking[0][0]=&trigger->view;registryBacking[1][0]=&trigger->view;registryBacking[2][0]=&trigger->view;
        for(std::size_t i=0;i<controlled.size();++i)for(std::size_t r=0;r<3;++r)registryBacking[r][i+1]=&controlled[i]->trigger->view;
        registryCount[0]=5;
        registryBacking[1][5]=&tag.view;registryCount[1]=6;
        registryBacking[2][5]=&tag.view;registryCount[2]=6;
        registryBacking[3][0]=&tag.view;registryCount[3]=1;
        for(std::size_t i=0;i<registries.size();++i)registries[i]=std::make_unique<MissionExpirationVector<const void*>>(MissionExpirationVector<const void*>{registryCount[i],registrySlots[i],&registryIdentity[i]});
        expiredTag=std::make_unique<MissionTagExpiredAbstract>(MissionTagExpiredAbstract{tag.view,&tag.view,tagLink30});
        for(auto& [key,owner]:structures) {
            auto* actor=owner.get();
            MissionExpirationOwnerView house{[this,actor]()->const void*{return actor->discovery.owner==-1?nullptr:&discovery.houses.at(actor->discovery.owner);},
                [this,actor](const void* p){if(!p){actor->discovery.owner=-1;return;}for(auto& [id,h]:discovery.houses)if(p==&h){actor->discovery.owner=id;return;}throw std::invalid_argument("Foreign expiration House");}};
            auto next=[this](const void* p)->MissionExpirationPointerView{
                if(p==&tag.view)return tagLink30;
                for(auto& [id,a]:structures)if(p==a.get())return residentNext(*a);
                throw std::invalid_argument("Unowned expiration passenger Next");
            };
            owner->recipient=std::make_unique<MissionTagExpirationRecipient>(owner->expiration.bind(actor,owner->tag,residentNext(*owner),owner->discovery,house,*expiredTag,
                expirationTagFlags,frame,expirationSession,expirationRetryPadding,next,[this](const void* p)->const BootCampBuildingExpirationType&{return buildingType(p);}));
            recipientBacking[std::size_t(recipientCount++)]=owner->recipient.get();
        }
        teamRecipient.identity=&createdTeam;
        teamRecipient.expired=[this](MissionTagState& subject,std::uint32_t removed){
            expireMemberTeamTag(createdTeam,&subject,removed,{});
        };
        recipients=std::make_unique<MissionExpirationVector<MissionTagExpirationRecipient*>>(MissionExpirationVector<MissionTagExpirationRecipient*>{recipientCount,recipientSlots,&recipientIdentity});
        points=std::make_unique<MissionExpirationVector<std::uint32_t>>(MissionExpirationVector<std::uint32_t>{pointCount,pointSlots,&pointIdentity});
        fallback=std::make_unique<MissionExpirationCell>(MissionExpirationCell{fallbackPoint,fallbackTag,fallback2c,fallback30,fallbackContent,&fallbackIdentity});
        expirationMap=std::make_unique<MissionTagExpirationMap>(MissionTagExpirationMap{*points,*registries[1],noCells,*fallback,{}});
        expiration=std::make_unique<MissionTagExpirationServices>(MissionTagExpirationServices{global680,global684,*recipients,*expirationMap,*registries[2]});
        expiration->abstractType=[](MissionTagState&){return false;};
        tagServices=std::make_unique<MissionTagServices>(MissionTagServices{deferred,emptyCell});
        tagServices->cellTag=[](std::uint32_t)->MissionTagState*&{throw std::invalid_argument("Objective discovery has no Cell Tag");};
        tagServices->notifyExpired=[this](MissionTagState& subject,std::uint8_t removed){broadcastMissionTagExpiration(subject,removed,*expiration);};

        triggerDestruction=std::make_unique<MissionTriggerDestructionServices>(MissionTriggerDestructionServices{{registries[0].get(),registries[1].get(),registries[2].get()}});
        MissionTagPointerReferences pointerOwner{tag.view,tag.typePointer,tag.first,tag.destroyed,&tag.view};
        MissionExpiredTriggerReference expiredTrigger{&trigger->view,trigger->next};
        triggerDestruction->expire=[this,pointerOwner,expiredTrigger](MissionTagTrigger&,std::uint32_t removed) mutable {expireMissionTagPointerReferences(pointerOwner,expiredTrigger,removed,deferred);
            if(teamTagConstructed){
                MissionTagPointerReferences child{teamTag->view,teamTag->typePointer,teamTag->first,teamTag->destroyed,&teamTag->view};
                expireMissionTagPointerReferences(child,expiredTrigger,removed,deferred);
            }
        };
        triggerDestruction->destroyBase=[this](MissionTagTrigger&){triggerBase=true;};
        triggerDestruction->freeRecord=[this](MissionTagTrigger&){triggerFreed=true;};
        tagDestruction=std::make_unique<MissionTagDestructionServices>(MissionTagDestructionServices{deferred,{registries[1].get(),registries[2].get(),registries[3].get()},{},{},{},{},sessionActive});
        tagDestruction->expire=[this](MissionTagState& subject,std::uint32_t removed){broadcastMissionTagExpiration(subject,removed,*expiration);};
        tagDestruction->destroyBase=[this](MissionTagState&){tagBase=true;};
        tagDestruction->freeRecord=[this](MissionTagState&){tagFreed=true;};
        triggerRecord=bindMissionTriggerDestruction(trigger->view,*triggerDestruction);
        tagRecord=bindMissionTagDestruction(tag.view,*tagDestruction);
        cleanup=std::make_unique<MissionDeferredCleanupServices>(MissionDeferredCleanupServices{deferred});
        cleanup->resolve=[this](const void* identity)->MissionDeferredCleanupRecord&{
            if(identity==&trigger->view)return triggerRecord;if(identity==&tag.view)return tagRecord;
            throw std::invalid_argument("Foreign Boot Camp deferred mission record");
        };
        const auto& childTag=mission.tags.at("07caba4c");
        const auto& childTrigger=mission.triggers.at("07caa20c");
        if(childTag.trigger!="07caa20c"||childTrigger.linked!="<none>"||childTrigger.events.size()!=1||
           childTrigger.events[0].kind!=7||childTrigger.events[0].mode!=0||integer(childTrigger.events[0].argument)!=1||
           childTrigger.actions.size()!=1||childTrigger.actions[0].kind!=2)
            throw std::invalid_argument("Unsupported first Team Tag/Trigger records");
        teamTag=std::make_unique<TagOwner>(childTag.persistence);
        for(const auto& d:childTrigger.events)teamEvents.push_back(std::make_unique<EventOwner>(d.kind,integer(d.argument)));
        for(const auto& d:childTrigger.actions)teamActions.push_back(std::make_unique<ActionOwner>(d));
        teamTrigger=std::make_unique<TriggerOwner>(houseIndex(mission,childTrigger.house),&teamEvents[0]->view,&teamActions[0]->view,frame,1,
            std::array<std::uint8_t,3>{std::uint8_t(childTrigger.flags[1]),std::uint8_t(childTrigger.flags[2]),std::uint8_t(childTrigger.flags[3])});
        teamTrigger->services.resetPadding=[] {return 0;}; // Supplied scratch; event7 does not consume it.
        teamTrigger->services.resolveHouse=trigger->services.resolveHouse;
        teamTrigger->services.executeAction=[](auto&,auto,auto,auto&,auto&)->std::uint8_t{
            throw std::invalid_argument("Friendly Fire action execution not joined");
        };
        teamTriggerControl=std::make_unique<MissionTriggerControlRecord>(MissionTriggerControlRecord{
            teamTrigger->state,teamTrigger->services,teamTrigger->difficultyAllowed,&teamTrigger->view});
        teamTriggerPermissions={std::uint8_t(childTrigger.flags[1]),std::uint8_t(childTrigger.flags[2]),std::uint8_t(childTrigger.flags[3]),std::uint8_t(!childTrigger.flags[0])};
        teamTriggerConstructionType=std::make_unique<MissionTriggerConstructionType>(MissionTriggerConstructionType{&teamTrigger->type,teamTriggerPermissions,teamTriggerNext});
        teamFirstType=teamTriggerConstructionType.get();
        teamTriggerConstruction=std::make_unique<MissionTriggerConstructionView>(MissionTriggerConstructionView{teamTrigger->base,teamTrigger->view,teamTrigger->typePointer,teamTrigger->next});
        teamTagConstructionType=std::make_unique<MissionTagConstructionType>(MissionTagConstructionType{&teamTag->type,teamFirstType});
        teamTagType=&teamTag->type;
        // Supplied map-to-ScriptType startup, separate from recovered cursor algorithms.
        for(std::size_t i=0;i<source.section("07B0C37C").size();++i){
            const auto entry=source.get("07B0C37C",std::to_string(i));if(entry.empty())break;
            const auto comma=entry.find(',');if(comma==std::string::npos)throw std::invalid_argument("Malformed actual Team Script entry");
            teamScriptActions.push_back({integer(entry.substr(0,comma)),integer(entry.substr(comma+1))});
        }
        if(teamScriptActions.empty())throw std::invalid_argument("Actual Team Script commands required");
        teamScriptActionCount=std::int32_t(teamScriptActions.size());
    }
    MissionScriptTypeState scriptTypeState(const void* identity)const{
        if(identity!=&teamScriptTypeIdentity)throw std::invalid_argument("Foreign actual Script Type");
        return {teamScriptActionCount,teamScriptActions};
    }
    void requireObjectiveScript(const void* expected=nullptr)const{
        if(!teamConstructed||!teamScriptConstructed||createdTeam.script28!=&teamScript||(expected&&expected!=&teamScript))
            throw std::invalid_argument("Actual objective Script owner required");
    }
    void constructObjectiveTeam(const void* house){
        if(teamConstructed)throw std::invalid_argument("Repeated Objective1 Team construction unsupported");
        if(source.get("0B197B7C","Tag")!="07CABA4C"||source.get("0B197B7C","Script")!="07B0C37C"||
           source.integer("0B197B7C","Waypoint",-1)!=-1)
            throw std::invalid_argument("Unsupported Objective1 Team associations");
        teamHouse.identity=house;
        std::array<std::int32_t,5> capacities{8,8,4,8,8},increments{10,10,10,10,10};
        std::array<std::uint8_t,5> allocated{1,1,1,1,1};
        std::span<const void*> recipientProjection;
        TeamConstructionRegistry primary{{teamRegistryCount[0],teamRegistrySlots[0],&teamRegistryCount[0]},capacities[0],allocated[0],increments[0],{},{}};
        TeamConstructionRegistry shared{*registries[1],registryCapacity[1],registryAllocated[1],registryIncrement[1],{},{}};
        TeamConstructionRegistry recipient{{recipientCount,recipientProjection,&recipientIdentity},capacities[2],allocated[2],increments[2],{},
            [this](std::int32_t index,const void* pointer){
                if(pointer!=&createdTeam||index<0||std::size_t(index)>=recipientBacking.size())
                    throw std::invalid_argument("Team recipient append outside actual owner");
                recipientBacking[std::size_t(index)]=&teamRecipient;
            }};
        TeamConstructionRegistry generic{{teamRegistryCount[1],teamRegistrySlots[1],&teamRegistryCount[1]},capacities[3],allocated[3],increments[3],{},{}};
        TeamConstructionRegistry other{{teamRegistryCount[2],teamRegistrySlots[2],&teamRegistryCount[2]},capacities[4],allocated[4],increments[4],{},{}};
        TeamConstructionServices services{frame,emptyCell,{&primary,&shared,&recipient,&generic,&other}};
        // Supplied absent-Waypoint/default-Cell association. The map lookup
        // branch is not entered by this actual TeamType and stays unbound.
        services.waypoint6BFA90=[this](const auto& type){
            if(type.identity!=&createTeamIdentity)throw std::invalid_argument("Foreign Team waypoint Type");
            return emptyCell;
        };
        std::array<TeamConstructionRegistry,4> missionRegistries{{
            {*registries[0],registryCapacity[0],registryAllocated[0],registryIncrement[0],{},{}},
            {*registries[1],registryCapacity[1],registryAllocated[1],registryIncrement[1],{},{}},
            {*registries[2],registryCapacity[2],registryAllocated[2],registryIncrement[2],{},{}},
            {*registries[3],registryCapacity[3],registryAllocated[3],registryIncrement[3],{},{}}
        }};
        TeamConstructionRegistry scriptRegistry{{scriptCount,scriptSlots,&scriptCount},scriptCapacity,scriptAllocated,scriptIncrement,{},{}};
        MissionConstructionServices children{frame,difficulty,tagLink30,
            {&missionRegistries[3],&missionRegistries[1],&missionRegistries[2]},
            {&missionRegistries[1],&missionRegistries[2],&missionRegistries[0]},&scriptRegistry};
        children.resolveTriggerType=[this](MissionTriggerType* type)->const MissionTriggerConstructionType&{
            if(type!=&teamTrigger->type)throw std::invalid_argument("Foreign constructed Trigger Type");
            return *teamTriggerConstructionType;
        };
        children.allocate=[this](std::uint32_t size)->void*{
            if(size!=68||teamTriggerConstructed)throw std::invalid_argument("Unsupported Team Trigger allocation");
            return &teamTrigger->view; // Supplied typed host heap, not original allocation.
        };
        children.constructTrigger=[this,&children](void* storage,MissionTriggerConstructionType& type)->MissionTriggerConstructionView*{
            if(storage!=&teamTrigger->view||&type!=teamTriggerConstructionType.get())throw std::invalid_argument("Foreign Team Trigger constructor arguments");
            constructMissionTrigger(*teamTriggerConstruction,&type,children);teamTriggerConstructed=true;
            return teamTriggerConstruction.get();
        };
        services.allocate=[this](std::uint32_t size)->void*{
            if(size==56)return &teamTag->view;if(size==48)return &teamScript;
            throw std::invalid_argument("Unsupported Team child allocation");
        };
        services.constructTag6B3870=[this,&children](void* storage,const void* type)->const void*{
            if(storage!=&teamTag->view||type!=&teamTag->type||teamTagConstructed)throw std::invalid_argument("Foreign Team Tag request");
            ++teamTagChildRequests;
            MissionTagConstructionView record{teamTag->base,teamTag->view,teamTag->typePointer,teamTag->first,teamTag->link30,teamTag->destroyed};
            const auto* result=constructMissionTag(record,teamTagConstructionType.get(),children);teamTagConstructed=true;return result;
        };
        services.constructScript668730=[this,&children](void* storage,const void* type)->const void*{
            if(storage!=&teamScript||type!=&teamScriptTypeIdentity||teamScriptConstructed)throw std::invalid_argument("Foreign Team Script request");
            ++teamScriptChildRequests;
            const auto* result=constructMissionScript(teamScript,type,children);teamScriptConstructed=true;return result;
        };
        constructTeam(createdTeam,&teamType,&teamHouse,0,services);teamConstructed=true;
    }

    void copyWarmTo(Impl& out,const std::function<const void*(const void*)>& externalRemap) const {
        if(activeObject||tag.executing||discovery.tagEvent)
            throw std::invalid_argument("Cannot clone an in-progress Boot Camp mission dispatch");
        // Never copy a reference view or std::function. The fresh constructor
        // has already bound each of those to out and its independent frame.
        std::map<const void*,void*> identities;
        const auto bind=[&](const auto* from,auto* to){
            if(!identities.emplace(from,to).second)
                throw std::logic_error("Duplicate Boot Camp mission clone identity");
        };
        const auto pointer=[&]<class T>(T* from)->T*{
            if(!from)return nullptr;
            const auto found=identities.find(from);
            if(found==identities.end()){
                if(externalRemap)if(const auto* mapped=externalRemap(from))return static_cast<T*>(const_cast<void*>(mapped));
                throw std::invalid_argument("Foreign Boot Camp mission clone pointer");
            }
            return static_cast<T*>(found->second);
        };
        const auto bindTrigger=[&](const TriggerOwner& a,TriggerOwner& b){
            bind(&a.country,&b.country);bind(&a.type,&b.type);
            bind(&a.state,&b.state);bind(&a.view,&b.view);
        };
        bind(&tag.type,&out.tag.type);bind(&tag.view,&out.tag.view);
        bind(&event->view,&out.event->view);bindTrigger(*trigger,*out.trigger);
        bind(objectiveControl.get(),out.objectiveControl.get());
        for(std::size_t i=0;i<actions.size();++i)bind(&actions[i]->view,&out.actions.at(i)->view);
        for(std::size_t i=0;i<controlled.size();++i){
            const auto& a=*controlled[i];auto& b=*out.controlled[i];
            bindTrigger(*a.trigger,*b.trigger);bind(a.control.get(),b.control.get());
            for(std::size_t j=0;j<a.events.size();++j)bind(&a.events[j]->view,&b.events.at(j)->view);
            for(std::size_t j=0;j<a.actions.size();++j)bind(&a.actions[j]->view,&b.actions.at(j)->view);
        }
        for(const auto& [id,house]:discovery.houses)bind(&house,&out.discovery.houses.at(id));
        for(const auto& [name,type]:countryTypes)bind(type.get(),out.countryTypes.at(name).get());
        for(const auto& [name,t]:buildingTypes)bind(t.get(),out.buildingTypes.at(name).get());
        for(const auto& [id,a]:structures){
            auto& b=*out.structures.at(id);bind(a.get(),&b);bind(a->recipient.get(),b.recipient.get());
        }
        bind(&createTeamIdentity,&out.createTeamIdentity);
        bind(&createdTeam,&out.createdTeam);bind(&teamType,&out.teamType);bind(&teamHouse,&out.teamHouse);
        bind(&teamRecipient,&out.teamRecipient);
        bind(&teamScriptTypeIdentity,&out.teamScriptTypeIdentity);bind(&teamScript,&out.teamScript);
        bind(&teamTag->type,&out.teamTag->type);bind(&teamTag->view,&out.teamTag->view);
        bindTrigger(*teamTrigger,*out.teamTrigger);
        bind(teamTriggerConstructionType.get(),out.teamTriggerConstructionType.get());
        bind(teamTriggerControl.get(),out.teamTriggerControl.get());
        for(std::size_t i=0;i<teamEvents.size();++i)bind(&teamEvents[i]->view,&out.teamEvents[i]->view);
        for(std::size_t i=0;i<teamActions.size();++i)bind(&teamActions[i]->view,&out.teamActions[i]->view);
        bind(&recipientIdentity,&out.recipientIdentity);bind(&pointIdentity,&out.pointIdentity);
        bind(&fallbackIdentity,&out.fallbackIdentity);
        for(std::size_t i=0;i<registryIdentity.size();++i)bind(&registryIdentity[i],&out.registryIdentity[i]);
        const auto copyTrigger=[&](const TriggerOwner& a,TriggerOwner& b){
            b.base=a.base;
            b.countryIndex=a.countryIndex;b.countryPointer=pointer(a.countryPointer);
            b.eventPointer=pointer(a.eventPointer);b.actionPointer=pointer(a.actionPointer);
            b.typePointer=pointer(a.typePointer);b.next=pointer(a.next);
            b.destroyed=a.destroyed;b.enabled=a.enabled;b.suppress=a.suppress;
            b.difficultyAllowed=a.difficultyAllowed;b.timer=a.timer;
            b.timerPadding=a.timerPadding;b.occurred=a.occurred;
        };
        const auto copyEvent=[&](const EventOwner& a,EventOwner& b){b.kind=a.kind;b.value=a.value;b.next=pointer(a.next);};
        copyEvent(*event,*out.event);copyTrigger(*trigger,*out.trigger);
        for(std::size_t i=0;i<actions.size();++i)out.actions[i]->next=pointer(actions[i]->next);
        for(std::size_t i=0;i<controlled.size();++i){
            const auto& a=*controlled[i];auto& b=*out.controlled[i];
            copyTrigger(*a.trigger,*b.trigger);b.timerScratch=a.timerScratch;
            for(std::size_t j=0;j<a.events.size();++j)copyEvent(*a.events[j],*b.events[j]);
            for(std::size_t j=0;j<a.actions.size();++j)b.actions[j]->next=pointer(a.actions[j]->next);
        }
        out.tag.persistence=tag.persistence;out.tag.instances=tag.instances;
        out.tag.executing=tag.executing;out.tag.destroyed=tag.destroyed;
        out.tag.typePointer=pointer(tag.typePointer);out.tag.first=pointer(tag.first);
        for(const auto& [id,a]:structures){auto& b=*out.structures.at(id);
            b.actorKey=a->actorKey;b.house=a->house;b.tag=pointer(a->tag);
            b.resident=a->resident;b.discovery=a->discovery;b.sight=a->sight;
            b.expiration.state=a->expiration.state;
            b.expiration.state.remapPointers([&](const void* p){return pointer(p);});
        }
        for(const auto& [name,t]:buildingTypes)*out.buildingTypes.at(name)=*t;
        for(const auto& [name,type]:countryTypes)*out.countryTypes.at(name)=*type;
        out.countryCount=countryCount;out.countryCapacity=countryCapacity;
        out.countryAllocated=countryAllocated;out.countryIncrement=countryIncrement;
        for(std::size_t i=0;i<countryBacking.size();++i)out.countryBacking[i]=pointer(countryBacking[i]);
        if(houseSlots.data()!=houseBacking.data()||houseSlots.size()!=houseBacking.size())
            throw std::invalid_argument("Foreign Boot Camp House registry backing");
        out.houseBacking.clear();out.houseBacking.reserve(houseBacking.size());
        for(auto p:houseBacking){
            if(p){bool known=false;for(const auto& [id,h]:discovery.houses)if(p==&h){known=true;break;}
                if(!known)throw std::invalid_argument("Foreign Boot Camp House registry identity");}
            out.houseBacking.push_back(pointer(p));
        }
        out.houseSlots=out.houseBacking;out.houseCount=houseCount;
        for(const auto& [id,h]:discovery.houses){
            auto& copied=out.discovery.houses.at(id);copied=h;copied.countryType34=pointer(h.countryType34);
        }
        for(const auto& [id,state]:threatHouses){
            if(state.slots.data()!=state.scores.data()||state.slots.size()!=state.scores.size())
                throw std::invalid_argument("Foreign Boot Camp House score backing");
            auto& target=out.threatHouses.at(id);target.grid=state.grid;
            target.enemy54F0=state.enemy54F0;target.count5504=state.count5504;
            target.scores.clear();target.scores.reserve(state.scores.size());
            for(const auto& entry:state.scores){
                const void* identity=nullptr;
                if(entry.house){
                    bool found=false;for(const auto& [other,h]:discovery.houses)if(entry.house==&h.indexAlliance){identity=&out.discovery.houses.at(other).indexAlliance;found=true;break;}
                    if(!found)throw std::invalid_argument("Foreign Boot Camp House score identity");
                }
                target.scores.push_back({identity,entry.value});
            }
            target.slots=target.scores;
        }
        out.expirationSession=expirationSession;out.expirationRetryPadding=expirationRetryPadding;
        out.discovery.currentHouse=discovery.currentHouse;out.discovery.mode=discovery.mode;
        out.discovery.loading=discovery.loading;out.discovery.tagContext=discovery.tagContext;
        if(discovery.store||discovery.trace)
            throw std::invalid_argument("Boot Camp clone cannot copy external discovery observers");
        out.difficulty=difficulty;
        out.messageDelay=messageDelay;
        out.alternateTextColor=alternateTextColor;
        out.textRequests=textRequests;
        out.textKey=textKey;out.textPayload=textPayload;
        out.textColorSelector=textColorSelector;
        out.textColor=textColor;
        out.textStyle=textStyle;
        out.textDuration=textDuration;
        out.allyCalls=allyCalls;
        out.allyValue=allyValue;
        out.allyFrom=allyFrom;
        out.allyTo=allyTo;
        out.allyAnnounce=allyAnnounce;
        out.soundRequests=soundRequests;
        out.speechRequests=speechRequests;
        out.soundToken=soundToken;
        out.speechToken=speechToken;
        out.soundIndex=soundIndex;
        out.soundPanning=soundPanning;
        out.speechIndex=speechIndex;
        out.speechMode=speechMode;
        out.speechParameter=speechParameter;
        out.soundVolumeBits=soundVolumeBits;
        out.soundController=soundController;
        out.teamCreationDepth=teamCreationDepth;
        out.createTeamDepthAtCall=createTeamDepthAtCall;
        out.createTeamRequests=createTeamRequests;
        out.createTeamFactoryCalls=createTeamFactoryCalls;out.createTeamAllocations=createTeamAllocations;
        out.teamTagConstructed=teamTagConstructed;out.teamTriggerConstructed=teamTriggerConstructed;out.teamScriptConstructed=teamScriptConstructed;
        out.teamTag->base=teamTag->base;out.teamTag->typePointer=pointer(teamTag->typePointer);out.teamTag->first=pointer(teamTag->first);
        out.teamTag->instances=teamTag->instances;out.teamTag->executing=teamTag->executing;out.teamTag->destroyed=teamTag->destroyed;out.teamTag->link30=pointer(teamTag->link30);
        copyTrigger(*teamTrigger,*out.teamTrigger);
        for(std::size_t i=0;i<teamEvents.size();++i)copyEvent(*teamEvents[i],*out.teamEvents[i]);
        for(std::size_t i=0;i<teamActions.size();++i)out.teamActions[i]->next=pointer(teamActions[i]->next);
        out.teamTriggerPermissions=teamTriggerPermissions;out.teamTriggerNext=pointer(teamTriggerNext);out.teamFirstType=pointer(teamFirstType);
        out.teamScript=teamScript;out.teamScript.type24=pointer(teamScript.type24);
        out.teamScriptActions=teamScriptActions;out.teamScriptActionCount=teamScriptActionCount;
        out.scriptCount=scriptCount;out.scriptCapacity=scriptCapacity;out.scriptAllocated=scriptAllocated;out.scriptIncrement=scriptIncrement;
        for(std::size_t i=0;i<scriptBacking.size();++i)out.scriptBacking[i]=pointer(scriptBacking[i]);
        out.teamConstructed=teamConstructed;out.teamTypeCount=teamTypeCount;out.teamHouseFlag=teamHouseFlag;
        out.teamHouseCount=teamHouseCount;out.teamHouse.identity=pointer(teamHouse.identity);
        out.teamTagType=pointer(teamTagType);out.teamScriptType=pointer(teamScriptType);
        out.teamTagChildRequests=teamTagChildRequests;out.teamScriptChildRequests=teamScriptChildRequests;
        out.createdTeam=createdTeam;
        out.createdTeam.value3C=pointer(createdTeam.value3C);out.createdTeam.value40=pointer(createdTeam.value40);
        out.createdTeam.type24=pointer(createdTeam.type24);out.createdTeam.house2C=pointer(createdTeam.house2C);
        out.createdTeam.tag70=pointer(createdTeam.tag70);out.createdTeam.script28=pointer(createdTeam.script28);
        out.createdTeam.cell34=pointer(createdTeam.cell34);
        out.createdTeam.value38=pointer(createdTeam.value38);out.createdTeam.value54=pointer(createdTeam.value54);
        out.teamRegistryCount=teamRegistryCount;
        for(std::size_t r=0;r<teamRegistryBacking.size();++r)
            for(std::size_t i=0;i<teamRegistryBacking[r].size();++i)out.teamRegistryBacking[r][i]=pointer(teamRegistryBacking[r][i]);
        out.createTeamId=createTeamId;
        out.createTeamArgument=createTeamArgument;
        out.revealRequests=revealRequests;
        out.revealCreateTeamRequestsAtCall=revealCreateTeamRequestsAtCall;
        out.revealSoundRequestsAtCall=revealSoundRequestsAtCall;
        out.revealWaypoint=revealWaypoint;
        out.revealHouse=revealHouse;
        out.revealObject=revealObject;
        out.revealTrigger=revealTrigger;
        out.revealPackedCell=revealPackedCell;
        out.deferredCapacity=deferredCapacity;
        out.deferredCount=deferredCount;
        out.deferredGrowth=deferredGrowth;
        out.deferredOwns=deferredOwns;
        out.registryCount=registryCount;out.registryCapacity=registryCapacity;out.registryIncrement=registryIncrement;out.registryAllocated=registryAllocated;
        out.recipientCount=recipientCount;
        out.pointCount=pointCount;
        out.pointBacking=pointBacking;
        out.fallbackPoint=fallbackPoint;
        out.emptyCell=emptyCell;
        out.sessionActive=sessionActive;
        out.triggerBase=triggerBase;
        out.triggerFreed=triggerFreed;
        out.tagBase=tagBase;
        out.tagFreed=tagFreed;
        // Copy full backing arrays, not merely active prefixes: erase helpers
        // retain tails which later diagnostics and operations may still inspect.
        for(std::size_t i=0;i<deferredBacking.size();++i)out.deferredBacking[i]=pointer(deferredBacking[i]);
        for(std::size_t r=0;r<registryBacking.size();++r)
            for(std::size_t i=0;i<registryBacking[r].size();++i)out.registryBacking[r][i]=pointer(registryBacking[r][i]);
        for(std::size_t i=0;i<recipientBacking.size();++i)out.recipientBacking[i]=pointer(recipientBacking[i]);
        out.tagLink30=pointer(tagLink30);out.fallbackTag=pointer(fallbackTag);
        out.fallback2c=pointer(fallback2c);out.fallback30=pointer(fallback30);out.fallbackContent=pointer(fallbackContent);
        out.global680=pointer(global680);out.global684=pointer(global684);
    }
    bool discover(int actorKey) {
        auto& object=*structures.at(actorKey);object.discovery.hasTag=object.tag!=nullptr;
        auto* previousObject=activeObject;activeObject=&object;
        if(std::uint32_t(discovery.tagContext)!=emptyCell){activeObject=previousObject;
            throw std::invalid_argument("Boot Camp discovery requires its supplied empty Cell association");}
        BuildingDiscoveryServices services;
        services.typeIndexB90=[this,&object]{return buildingType(object.expiration.state.type418).indexB90;};
        services.radioLinks=[&object]{return buildingHasRadioPointerLinks(object.expiration.state.counts[0],std::span<const void* const>(object.expiration.state.backing[0]));};
        // No activation stub: entered4426D0 remains an explicit refusal.
        const WaypointTaggedDiscoveryBinding binding{{actorKey,&object.discovery,&services},object.tag,&object};
        try {const bool result=discoverWaypointTaggedResident(actorKey,discovery.currentHouse,discovery,std::span(&binding,1),*tagServices);activeObject=previousObject;return result;}
        catch(...) {activeObject=previousObject;throw;}

    }
};

BootCampMissionWorld::BootCampMissionWorld(const MissionDefinition& mission,const Ini& source,const Ini& rules,const std::int32_t& frame,std::shared_ptr<const PreparedStringLookup> strings,const MessageColorTable& colors,std::unique_ptr<OwnedMessagePresentation> messages):impl_(std::make_unique<Impl>(mission,source,rules,frame,std::move(strings),colors,std::move(messages))){}
std::unique_ptr<BootCampMissionWorld> BootCampMissionWorld::clone(const std::int32_t& frame,std::function<const void*(const void*)> externalRemap)const{
    auto result=std::make_unique<BootCampMissionWorld>(impl_->mission,impl_->source,impl_->rules,frame,impl_->strings,impl_->colors,impl_->messages->clone());
    impl_->copyWarmTo(*result->impl_,externalRemap);
    return result;
}
BootCampMissionWorld::~BootCampMissionWorld()=default;
OwnedMessagePresentation& BootCampMissionWorld::messages(){return *impl_->messages;}
const OwnedMessagePresentation& BootCampMissionWorld::messages()const{return *impl_->messages;}
BootCampMissionWorld::StructureResident BootCampMissionWorld::structureResident(int actorKey){
    auto& a=*impl_->structures.at(actorKey);auto& r=a.resident;
    return {&a,r.position88,r.next,r.flags14,r.alternate79,r.eligible5a0,r.typeMapFlag205,r.width,r.height};
}
BootCampMissionWorld::StructureSight BootCampMissionWorld::structureSight(int key){
    auto& a=*impl_->structures.at(key);
    return {&a,a.resident.position88,a.discovery,a.sight};
}
const BootCampBuildingExpirationType& BootCampMissionWorld::structureSightType(int key)const{
    return impl_->buildingType(impl_->structures.at(key)->expiration.state.type418);
}
const std::uint8_t& BootCampMissionWorld::structureRadarTypeFlag(const void* type)const{
    return impl_->buildingType(type).radarFlag1ff;
}
PixelRect BootCampMissionWorld::structureTypeImageBounds(int key,const BuildingTypeBoundsServices& services){
    const auto* identity=impl_->structures.at(key)->expiration.state.type418;
    for(auto& [name,type]:impl_->buildingTypes)if(type.get()==identity)
        return buildingTypeBounds(type->imageBounds,{},services); // Supplied zero sentinel/startup.
    throw std::invalid_argument("Foreign BuildingType bounds owner");
}
BuildingImageState& BootCampMissionWorld::structureTypeImageState(int key){
    const auto* identity=impl_->structures.at(key)->expiration.state.type418;
    for(auto& [name,type]:impl_->buildingTypes)if(type.get()==identity)return type->images;
    throw std::invalid_argument("Foreign BuildingType image owner");
}
std::int32_t BootCampMissionWorld::structureAnimationFrame(int key,const double& threshold,const double& alternate)const{
    const auto& a=*impl_->structures.at(key);const auto& f=a.sight;
    BuildingFrameServices s;
    s.type=[&]{const auto& t=impl_->buildingType(a.expiration.state.type418);return BuildingFrameType{t.images,t.frameSelection};};
    s.mission16c=[&]{return unitDiscoveryMission(a.discovery);};
    s.healthRatio5d4540=[&]{return missionExpirationHealthRatio(a.expiration.state.health6C,[&]()->const std::int32_t&{
        return impl_->buildingType(a.expiration.state.type418).strengthA0;});};
    s.threshold1368=[&]{return threshold;};s.threshold1370=[&]{return alternate;};
    return buildingAnimationFrame({f.frameE0,f.stage42c,f.frame4ec,f.frame4f0,f.field564},s);
}
void BootCampMissionWorld::drawStructureOrdinary(int key,PixelPoint& point,PixelRect& clip,
        const double& threshold,const double& alternate,const BuildingOrdinaryServices& children){
    if(children.cell1a0||children.kind2c||children.mission16c||children.type||children.stage42c||children.animation454||
            children.healthRatio5d4540||children.threshold1368||children.foundationHeight458940||children.foundationWidth458930||
            children.frame43be20||children.height1b8)
        throw std::invalid_argument("Building ordinary competing owner service");
    auto& a=*impl_->structures.at(key);auto s=children;const auto* foundationType=a.expiration.state.type418;
    s.cell1a0=[&]{return buildingDrawCell(a.resident.position88);};
    s.kind2c=[]{return 6;};
    s.mission16c=[&]{return unitDiscoveryMission(a.discovery);};
    s.type=[&]{const auto& t=impl_->buildingType(a.expiration.state.type418);return BuildingOrdinaryType{t.ordinaryDraw,t.images,t.imageBounds};};
    s.stage42c=[&]{return a.sight.stage42c;};
    // Original454 animation-pointer association overlaps the old supplied
    // Cell-word view. No fabricated array: entered activation still refuses.
    s.healthRatio5d4540=[&]{return missionExpirationHealthRatio(a.expiration.state.health6C,[&]()->const std::int32_t&{
        return impl_->buildingType(a.expiration.state.type418).strengthA0;});};
    s.threshold1368=[&]{return threshold;};
    const auto foundation=[&]{if(a.expiration.state.type418!=foundationType)
        throw std::invalid_argument("Building ordinary foundation Type association changed");};
    s.foundationHeight458940=[&]{foundation();return a.resident.height;};
    s.foundationWidth458930=[&]{foundation();return a.resident.width;};
    s.frame43be20=[&]{return structureAnimationFrame(key,threshold,alternate);};
    s.height1b8=[&]{return a.resident.position88.z;};
    drawBuildingOrdinary(point,clip,s);
}
const void* BootCampMissionWorld::structureImageFromAssets(int key,const AssetStore& assets,
        const std::int32_t& theater,double rulesTiming){
    auto& a=*impl_->structures.at(key);
    return buildingImageSelection({[&]{return a.sight.stage42c;},[&]{return a.sight.image5b4;},[&]{
        auto& type=impl_->buildingType(a.expiration.state.type418);
        return BuildingImageSelectionType{[&type,&assets,rulesTiming]{
            BuildingAssetImages loader(type,assets,rulesTiming);return ensureBuildingPrimaryImage(type.images,loader.io);
        },[&type,&assets,&theater,rulesTiming]{
            BuildingAssetImages loader(type,assets,rulesTiming);return ensureBuildingSecondaryImage(type.images,type.imageBounds,theater,loader.io);
        }};
    }});
}
void BootCampMissionWorld::drawStructureOrdinaryFromAssets(int key,PixelPoint& point,PixelRect& clip,
        const double& threshold,const double& alternate,const AssetStore& assets,
        const std::int32_t& theater,double rulesTiming,BuildingOrdinaryServices children){
    if(children.image68||children.imageCount)throw std::invalid_argument("Building ordinary competing asset image service");
    children.image68=[&]{return structureImageFromAssets(key,assets,theater,rulesTiming);};
    children.imageCount=[&](const void* image){
        // The saved image can precede a late Type change. Read its header by
        // identity, without inventing another actor-Type query here.
        for(const auto& [name,type]:impl_->buildingTypes)
            for(const auto& backing:type->imageBacking)if(backing.get()==image)return shpBoundsView(*backing).count();
        throw std::invalid_argument("Unowned Building ordinary image count");
    };
    drawStructureOrdinary(key,point,clip,threshold,alternate,children);
}
const void* BootCampMissionWorld::structureSpriteConverter(int key,SpriteConverterSelectionServices s)const{
    if(s.type80||s.owner1b4||s.schemesB8c||s.index15f40||s.houseCC||s.currentHouseA35db4)
        throw std::invalid_argument("Building sprite selector competing owner service");
    const auto& a=*impl_->structures.at(key);
    s.type80=[&]{return a.expiration.state.type418;};
    s.owner1b4=[&]()->const void*{return a.discovery.owner==-1?nullptr:&impl_->discovery.houses.at(a.discovery.owner);};
    s.schemesB8c=[&](const void* p)->const void*{
        const auto table=impl_->buildingType(p).spriteSchemeTableB8c;
        if(table)throw std::invalid_argument("Building sprite Type scheme table backing unbound");
        return table;
    };
    s.index15f40=[&](const void* p){
        for(const auto& [id,h]:impl_->discovery.houses)if(p==&h)return h.radarScheme15f40;
        throw std::invalid_argument("Building sprite selector foreign/null House");
    };
    s.currentHouseA35db4=[&]()->const void*{return &impl_->discovery.houses.at(impl_->discovery.currentHouse);};
    // Actual Building41B2E0 returns null, ret4. No alternate owner fabricated.
    s.houseCC=[](std::int32_t arg)->const void*{if(arg!=1)throw std::invalid_argument("Building CC argument");return nullptr;};
    return selectSpriteConverter(s);
}
void BootCampMissionWorld::drawStructureSprite(int key,const BuildingSpriteRequest& request,TechnoSpriteServices s){
    if(s.kind2c||s.building1386||s.typeB48||s.coordinates48||s.height1b8||s.predicate1bc||s.predicate1c0||
            s.predicateC0||s.brightness3f8||s.image||s.objectC8||s.houseCC||s.objectKind2c)
        throw std::invalid_argument("Building sprite competing owner service");
    auto& a=*impl_->structures.at(key);const auto* foundationType=a.expiration.state.type418;
    s.kind2c=[]{return 6;};
    s.building1386=[&]{return impl_->buildingType(a.expiration.state.type418).ordinaryDraw.flag1386;};
    s.typeB48=[&]{return impl_->buildingType(a.expiration.state.type418).ordinaryDraw.flagB48;};
    s.coordinates48=[&]{
        const auto foundation=[&]{if(a.expiration.state.type418!=foundationType)
            throw std::invalid_argument("Building sprite foundation Type association changed");};
        return buildingCoordinates({[&](std::uint8_t extra){foundation();if(extra)throw std::invalid_argument("Building sprite extra foundation unsupported");return a.resident.height;},
            [&]{foundation();return a.resident.width;},[&]{return a.resident.position88;}});
    };
    s.height1b8=[&]{return a.resident.position88.z;};
    s.predicate1bc=[&]{return a.sight.sprite204;};s.predicate1c0=[&]{return a.sight.sprite205;};
    s.predicateC0=[&]{return missionTargetDisguisedC0(a.expiration.state.byte170);};
    s.brightness3f8=[&](std::int32_t light){return buildingSpriteBrightness(a.sight.spriteD8,light);};
    s.image=[&](const void* image){
        for(const auto& [name,type]:impl_->buildingTypes)
            for(const auto& backing:type->imageBacking)if(backing.get()==image)return shpBoundsView(*backing);
        throw std::invalid_argument("Unowned Building sprite image");
    };
    // Actual Building C8/CC return null. The parent's entered null-object RTTI
    // path has no supported owner; do not substitute a fabricated Object/House.
    s.objectC8=[](std::int32_t)->const void*{throw std::invalid_argument("Building sprite owner-predicate false path unsupported");};
    drawTechnoSprite({a.sight.sprite1bc,a.sight.sprite5bb,a.sight.sprite37c},request,s);
}
PixelRect BootCampMissionWorld::structureTypeImageBoundsFromAssets(int key,const AssetStore& assets,
        const std::int32_t& theater,double rulesTiming){
    const auto* identity=impl_->structures.at(key)->expiration.state.type418;
    BootCampBuildingExpirationType* type=nullptr;
    for(auto& [name,candidate]:impl_->buildingTypes)if(candidate.get()==identity)type=candidate.get();
    if(!type)throw std::invalid_argument("Foreign BuildingType image owner");
    BuildingAssetImages loader(*type,assets,rulesTiming);auto& io=loader.io;
    auto resolve=[&](const void* p){return loader.resolve(p);};
    BuildingTypeBoundsServices bounds;
    bounds.primary9c=[&]{return resolve(ensureBuildingPrimaryImage(type->images,io));};
    bounds.secondaryC0=[&]{return resolve(ensureBuildingSecondaryImage(type->images,type->imageBounds,theater,io));};
    bounds.auxiliary=resolve;
    bounds.freeImage=[&](const void* p){
        auto& backing=type->imageBacking;
        const auto entry=std::find_if(backing.begin(),backing.end(),[&](const auto& v){return v.get()==p;});
        if(entry==backing.end())throw std::invalid_argument("Unowned Building SHP release");
        backing.erase(entry); // Clone references retain their own shared backing.
    };
    return buildingTypeBounds(type->imageBounds,{},bounds);
}
const BootCampMissionWorld::StructureSightState& BootCampMissionWorld::structureSightState(int key)const{return impl_->structures.at(key)->sight;}
BuildingFrameRegistry BootCampMissionWorld::buildingFrameRegistry(){
    auto* owner=impl_.get();
    return {[owner]{return std::int32_t(owner->structures.size());},[owner](std::int32_t index){
        if(index<0||std::size_t(index)>=owner->structures.size())throw std::invalid_argument("Foreign Building frame registry slot");
        auto entry=owner->structures.begin();std::advance(entry,index);auto* a=entry->second.get();
        return BuildingFrameFields{a->sight.onMap7d,a->sight.redraw75,a->sight.marked74,
            [a]{return buildingRenderCoordinates(a->resident.position88);},{}};
    }};
}
FrameInvalidationRegistry BootCampMissionWorld::buildingInvalidationRegistry(
        std::function<const PixelRect&(int,Coord,BuildingRenderBoundsState&)> bounds){
    auto* owner=impl_.get();
    return {[owner]{return std::int32_t(owner->structures.size());},[owner,bounds](std::int32_t index){
        if(index<0||std::size_t(index)>=owner->structures.size())throw std::invalid_argument("Foreign Building invalidation slot");
        auto entry=owner->structures.begin();std::advance(entry,index);auto* a=entry->second.get();const auto key=entry->first;
        return FrameInvalidationObject{[]{return 6;},a->sight.redraw75,[a,key,bounds]()->const PixelRect&{
            if(!bounds)throw std::invalid_argument("Building invalidation bounds provider unbound");
            return bounds(key,a->resident.position88,a->sight.renderBounds);
        },{}};
    }};
}
BuildingStaticRegistry BootCampMissionWorld::buildingStaticRegistry(
        std::function<const PixelRect&(int,Coord,BuildingRenderBoundsState&)> bounds,
        std::function<void(int,PixelRect,std::int32_t,std::int32_t)> draw){
    const auto frame=buildingInvalidationRegistry(std::move(bounds));auto* owner=impl_.get();
    return {frame.count,[owner,frame,draw](std::int32_t index){
        auto object=frame.at(index);auto entry=owner->structures.begin();std::advance(entry,index);
        const int key=entry->first;auto* a=entry->second.get();
        return BuildingStaticObject{std::move(object),a->sight.radar5b7,[draw,key](PixelRect clip,int force,int zero){
            if(!draw)throw std::invalid_argument("Building static drawing provider unbound");
            draw(key,clip,force,zero);
        }};
    }};
}
bool BootCampMissionWorld::drawStructureIfVisible(int key,PixelRect& clip,const PixelRect& viewport,
        std::int32_t force,std::int32_t special,BuildingVisibilityServices services){
    if(services.coordinatesA8)throw std::invalid_argument("Building visibility must borrow its actual coordinate owner");
    auto* a=impl_->structures.at(key).get();auto& fields=a->sight;
    services.coordinatesA8=[a]{return buildingRenderCoordinates(a->resident.position88);};
    return drawBuildingIfVisible({fields.marked74,fields.redraw75,fields.flag76,fields.radar5b7},
        clip,viewport,force,special,services);
}
void BootCampMissionWorld::bindWaypointReveal(std::function<std::uint8_t(std::int32_t)> reveal){
    if(!reveal)throw std::invalid_argument("Missing Boot Camp waypoint reveal owner");
    impl_->waypointReveal=std::move(reveal);
}
void BootCampMissionWorld::bindResidentIdentities(std::function<const void*(int)> resolve,std::function<int(const void*)> identify){
    if(!resolve||!identify)throw std::invalid_argument("Missing resident identity bindings");
    impl_->externalResident=std::move(resolve);impl_->externalResidentId=std::move(identify);
}
BootCampMissionWorld::StructureExpirationInspection BootCampMissionWorld::inspectStructureExpiration(int key){
    auto& a=*impl_->structures.at(key);return {&a,&impl_->tag.view,impl_->tagLink30,a.discovery,a.expiration.state};
}
const BootCampBuildingExpirationState& BootCampMissionWorld::structureExpirationState(int key)const{return impl_->structures.at(key)->expiration.state;}
const BootCampMissionWorld::StructureResidentState& BootCampMissionWorld::structureResidentState(int actorKey)const{
    return impl_->structures.at(actorKey)->resident;
}
void BootCampMissionWorld::changeCellThreat(HouseThreatCell cell,std::int32_t owner,std::int32_t delta,std::span<const std::int32_t,18> tables){
    CellThreatWorld world{impl_->discovery.mode,impl_->houseCount,impl_->houseSlots,tables.first<9>(),tables.last<9>(),{}, {}};
    world.house=[this](const void* p)->HouseThreatHouse{
        for(auto& [id,h]:impl_->discovery.houses)if(p==&h){auto& state=impl_->threatHouses.at(id);
            return {p,h.indexAlliance.countryIndex,h.field13d,h.human134,h.control135,h.indexAlliance.allianceMask,
                state.enemy54F0,state.count5504,state.slots,state.grid};}
        throw std::invalid_argument("Foreign Boot Camp Cell threat House");
    };
    ra2::changeCellThreat(cell,owner,delta,world);
}
BootCampMissionWorld::HouseThreatState& BootCampMissionWorld::houseThreat(int id){return impl_->threatHouses.at(id);}
const BootCampMissionWorld::HouseThreatState& BootCampMissionWorld::houseThreat(int id)const{return impl_->threatHouses.at(id);}
const std::map<int,UnitDiscoveryHouse>& BootCampMissionWorld::houses()const{return impl_->discovery.houses;}
UnitDiscoveryHouse& BootCampMissionWorld::house(int id){return impl_->discovery.houses.at(id);}
const UnitDiscoveryHouse& BootCampMissionWorld::house(int id)const{return impl_->discovery.houses.at(id);}
const HouseCountryType& BootCampMissionWorld::countryType(int id)const{
    const auto* p=house(id).countryType34;
    for(const auto& [name,type]:impl_->countryTypes)if(p==type.get())return *p;
    throw std::invalid_argument("House country Type is outside owned registry");
}
HouseCountryType& BootCampMissionWorld::countryType(int id){
    return const_cast<HouseCountryType&>(static_cast<const BootCampMissionWorld&>(*this).countryType(id));
}
const int& BootCampMissionWorld::discoveryMode()const{return impl_->discovery.mode;}
const int& BootCampMissionWorld::currentHouse()const{return impl_->discovery.currentHouse;}
bool BootCampMissionWorld::discoverInfantry(UnitDiscoveryActor& actor){
    return discoverInfantry(actor,impl_->discovery.currentHouse);
}
bool BootCampMissionWorld::discoverInfantry(UnitDiscoveryActor& actor,int discoverer){
    if(actor.hasTag)throw std::invalid_argument("Boot Camp Infantry discovery requires coherent null Tag");
    if(discoverer!=-1&&!impl_->discovery.houses.contains(discoverer))
        throw std::invalid_argument("Foreign Infantry discovery House");
    return discoverUnit(actor,discoverer,impl_->discovery);
}
bool BootCampMissionWorld::discoverInfantry(int resident,UnitDiscoveryActor& actor,MissionTagState*& tag,int discoverer){
    auto& w=*impl_;
    if(actor.hasTag!=bool(tag)||(tag&&(!w.teamTagConstructed||tag!=&w.teamTag->view)))
        throw std::invalid_argument("Infantry discovery requires coherent owned Tag");
    if(discoverer!=-1&&!w.discovery.houses.contains(discoverer))throw std::invalid_argument("Foreign Infantry discovery House");
    if(std::uint32_t(w.discovery.tagContext)!=w.emptyCell||!w.externalResident||resident<0)
        throw std::invalid_argument("Infantry discovery requires actual resident and empty Cell context");
    const auto object=w.externalResident(resident);
    if(!object||!w.externalResidentId||w.externalResidentId(object)!=resident)
        throw std::invalid_argument("Infantry discovery lost resident identity");
    const WaypointTaggedDiscoveryBinding binding{{resident,&actor,nullptr},tag,object};
    return discoverWaypointTaggedResident(resident,discoverer,w.discovery,std::span(&binding,1),*w.tagServices);
}
bool BootCampMissionWorld::discoverStructure(int actorKey){return impl_->discover(actorKey);}
void BootCampMissionWorld::drainDeferred(){drainMissionDeferredCleanup(*impl_->cleanup);}
bool BootCampMissionWorld::canAdmitObjectiveFoot(TeamAdmissionFoot foot,const void* e1Type,
        std::int32_t& slot,const TeamAdmissionServices& services)const{
    auto& w=*impl_;
    if(!w.teamConstructed||!e1Type)throw std::invalid_argument("Objective Team admission requires constructed actual Team/Type");
    if(w.createdTeam.type24!=&w.teamType||!w.createdTeam.house2C)
        throw std::invalid_argument("Unsupported actual objective Team association");
    const auto taskId=w.source.get("0B197B7C","TaskForce");
    std::vector<TeamAdmissionEntry> entries;
    for(int index=0;index<6;++index){
        const auto entry=w.source.get(taskId,std::to_string(index));if(entry.empty())break;
        const auto comma=entry.find(',');
        if(comma==std::string::npos||lower(entry.substr(comma+1))!="e1")
            throw std::invalid_argument("Unsupported first Team TaskForce type association");
        entries.push_back({integer(entry.substr(0,comma)),e1Type});
    }
    if(!w.source.get(taskId,"6").empty())throw std::invalid_argument("Team TaskForce outside six actual count fields");
    const std::int32_t count=std::int32_t(entries.size()),priority=w.source.integer("0B197B7C","Priority",-1);
    const std::uint8_t typeA9=0; // Supplied startup; not a recovered Type/INI initializer.
    TeamAdmissionTaskForce task{count,entries};auto* taskPointer=&task;
    TeamAdmissionType type{typeA9,priority,taskPointer};
    TeamAdmissionTeam team{&w.createdTeam,[&]()->auto&{
            if(w.createdTeam.type24!=&w.teamType)throw std::invalid_argument("Foreign live objective Team Type");return type;},
        w.createdTeam.script28,[&]()->const void*{
            if(!w.createdTeam.house2C)throw std::invalid_argument("Unbound live Team House");return w.createdTeam.house2C->identity;},w.createdTeam.values84};
    auto bound=services;
    if(!bound.script668870)bound.script668870=[&](const void* script){
        w.requireObjectiveScript(script);
        return currentMissionScriptAction(w.teamScript,[&](const void* type){return w.scriptTypeState(type);}).action;
    };
    return canAdmitTeamFoot(team,foot,slot,bound);
}
void BootCampMissionWorld::bindReferenceCleanupTeams(TechnoReferenceCleanupServices& services){
    services.teamSlot=[this](std::int32_t index){
        const auto& slots=impl_->teamRegistrySlots[0];
        if(index<0||std::size_t(index)>=slots.size()||slots[index]!=&impl_->createdTeam||!impl_->teamConstructed)
            throw std::invalid_argument("Reference cleanup requires owned Team registry slot");
        auto& t=impl_->createdTeam;return TechnoReferenceTeam{&t,t.value3C,t.value40};
    };
}
const std::int32_t& BootCampMissionWorld::referenceCleanupTeamCount()const{return impl_->teamRegistryCount[0];}
const void* BootCampMissionWorld::objectiveTeamIdentity()const{return &impl_->createdTeam;}
void BootCampMissionWorld::tickObjectiveTeamRecruitment(
        const std::function<void(TeamConstructionRecord&,TeamMembershipType&)>& anchor,
        const std::function<void(std::int32_t)>& recruit,const std::function<std::uint32_t(const void*)>& member,
        const std::function<const void*(const void*)>& next,const std::function<void(const void*,std::uint8_t)>& leader,
        const std::function<std::uint32_t(TeamConstructionRecord&)>& cohesion,
        const std::function<void(const void*)>& clearField1B0,const std::function<void(const void*,std::uint32_t)>& fieldD8,
        const std::function<TeamScriptServices::Transfer(const void*)>& transfer){
    auto& w=*impl_;
    if(!w.teamConstructed||w.createdTeam.type24!=&w.teamType||!w.createdTeam.house2C)
        throw std::invalid_argument("Actual Team AI owner required");
    std::vector<TeamAdmissionEntry> entries;const auto taskId=w.source.get("0B197B7C","TaskForce");
    for(int i=0;i<6;++i){const auto text=w.source.get(taskId,std::to_string(i));if(text.empty())break;
        const auto comma=text.find(',');if(comma==std::string::npos)throw std::invalid_argument("Malformed actual Team AI TaskForce");
        entries.push_back({integer(text.substr(0,comma)),nullptr});
    }
    const auto count=std::int32_t(entries.size());TeamAdmissionTaskForce task{count,entries};
    // Preflight the entered supported state before writes. Script50 and
    // pending-full activation execute through their separately verified paths.
    const auto& t=w.createdTeam;
    if((!t.flags74[11]&&(t.flags74[5]||t.flags74[3]))||t.value3C||t.value40)
        throw std::invalid_argument("Actual Team AI activation/target path unjoined");
    const auto group=w.source.integer("0B197B7C","Group",-1),taskGroup=w.source.integer(taskId,"Group",-1);
    const std::uint8_t zero=0;TeamMembershipType type{group,&taskGroup,zero,zero,zero};
    if(t.flags74[11]){
        // Read-only supported-domain preflight; execution below uses the actual
        // original Script children in order. No speculative original stores.
        const auto candidate=t.flags74[12]?nextObjectiveTeamScriptAction():objectiveTeamScriptAction();
        if((candidate.action!=50&&(candidate.action!=20||!transfer))||t.flags74[14]||t.flags74[6]||t.flags74[7]||!t.value54)
            throw std::invalid_argument("Actual active Team Script path unjoined");
        TeamScriptServices script{std::size_t(t.value48),zero,zero}; // Supplied TypeAB/EC startup.
        script.readiness6B8BB0=[&]{return refreshObjectiveTeamReadiness();};
        script.anchor6B9610=[&]{if(!anchor)throw std::invalid_argument("Actual Script anchor unbound");anchor(w.createdTeam,type);};
        script.member1C0=member;script.next4C8=next;
        script.advance668920=[&]{(void)advanceObjectiveTeamScript();};
        script.hasCurrent668940=[&]{return objectiveTeamScriptHasCurrent();};
        script.current668870=[&]{return objectiveTeamScriptAction();};
        script.clear6D6E50=clearField1B0;script.valueD8=fieldD8;
        script.member378=transfer;
        script.house4ED760=[&](std::int32_t country){
            return findHouseAllianceCountry(country,w.houseCount,w.houseSlots,[&](const void* p){
                for(const auto& [id,h]:w.discovery.houses)if(p==&h)return countryType(id).countryB8;
                throw std::invalid_argument("Foreign actual Script House lookup record");
            });
        };
        tickTeamScript(w.createdTeam,script);return;
    }
    if(t.flags74[9]&&std::bit_cast<std::int32_t>(t.value48)>0&&std::bit_cast<std::int32_t>(t.value48)==teamRequiredQuantity(task)){
        if(t.flags74[14]||!t.flags74[6])throw std::invalid_argument("Actual activation timer/unchanged7A path unjoined");
        TeamActivationServices activation{std::size_t(t.value48)};
        activation.readiness6B8BB0=[&]{return refreshObjectiveTeamReadiness();};
        activation.next4C8=next;activation.leader579=leader;
        activation.reset668900=[&]{(void)resetObjectiveTeamScript();};
        activation.anchor6B9610=[&]{if(!anchor)throw std::invalid_argument("Actual activation anchor unbound");anchor(w.createdTeam,type);};
        activation.member1C0=member;
        activation.cohesion6B9F40=[&]{if(!cohesion)throw std::invalid_argument("Actual Team cohesion unbound");return cohesion(w.createdTeam);};
        activateRecruitedTeam(w.createdTeam,activation);return;
    }
    const int timeout=0; // Unentered supplied scratch: current scenario mode0 bypasses empty timeout.
    TeamRecruitmentScheduleServices services{w.frame,w.discovery.mode,timeout};
    services.readiness6B8BB0=[&]{return refreshObjectiveTeamReadiness();};
    services.anchor6B9610=[&]{if(!anchor)throw std::invalid_argument("Actual Team AI anchor unbound");anchor(w.createdTeam,type);};
    services.house4F52F0=[&]()->std::uint32_t{
        for(const auto& [id,house]:w.discovery.houses)if(w.createdTeam.house2C->identity==&house)
            return discoveryHouseControlled(house,w.discovery.mode);
        throw std::invalid_argument("Foreign actual Team AI House");
    };
    services.taskForceDC=[&]{if(w.createdTeam.type24!=&w.teamType)throw std::invalid_argument("Foreign actual Team AI Type");return task;};
    services.recruit6B91C0=recruit;services.member1C0=member;
    services.continuation6BA1A0=[&]{continueUntargetedTeam(w.createdTeam);};
    tickRecruitingTeam(w.createdTeam,services);
}
const std::int32_t& BootCampMissionWorld::expirationSessionA40774()const{return impl_->expirationSession;}
const std::uint8_t& BootCampMissionWorld::objectiveTeamFlags14()const{return impl_->createdTeam.flags14;}
MissionExpirationPointerView BootCampMissionWorld::objectiveTeamSuccessor30(){
    return {[this]()->const void*{
        if(impl_->createdTeam.value30)throw std::invalid_argument("Nonnull actual Team30 identity remains unbound");
        return nullptr;
    },[](const void*){throw std::invalid_argument("Actual Team30 pointer writer remains unbound");}};
}
void BootCampMissionWorld::expireObjectiveTeam(MissionExpirationVector<TeamExpirationRecipient*>& recipients,std::uint32_t removed){
    auto& w=*impl_;if(!w.teamConstructed)throw std::invalid_argument("Actual expiration requires constructed Team");
    MissionTeamExpiredAbstract subject{&w.createdTeam,objectiveTeamSuccessor30()};
    TeamExpirationServices services{w.global680,w.global684,recipients,{},{},{}};
    services.abstractType=[&](const void* p){if(p!=&w.createdTeam)throw std::invalid_argument("Foreign Team RTTI identity");return false;};
    // Selection clearing remains absent. Entering it refuses, after the original
    // preceding stores, rather than silently substituting an empty UI effect.
    broadcastTeamExpiration(subject,w.createdTeam.flags14,removed,services);
}
bool BootCampMissionWorld::removeObjectiveTeamMember(const void* member,const void* e1Type,const TeamRemovalServices& input){
    auto& w=*impl_;
    if(!w.teamConstructed||w.createdTeam.type24!=&w.teamType||!e1Type)
        throw std::invalid_argument("Actual removal requires constructed Team and E1 Type");
    std::array<const void*,6> entries{};std::int32_t count=0;
    const auto task=w.source.get("0B197B7C","TaskForce");
    for(int i=0;i<6;++i){const auto text=w.source.get(task,std::to_string(i));if(text.empty())break;
        const auto comma=text.find(',');
        if(comma==std::string::npos||lower(text.substr(comma+1))!="e1")throw std::invalid_argument("Actual removal supports owned E1 TaskForce entries");
        entries[std::size_t(count++)]=e1Type;
    }
    auto services=input;
    services.task=[&]()->std::optional<TeamRemovalTask>{
        if(!w.createdTeam.type24)return {};
        if(w.createdTeam.type24!=&w.teamType)throw std::invalid_argument("Foreign actual removal Type");
        return TeamRemovalTask{count,entries};
    };
    return removeTeamMember(w.createdTeam,member,-1,0,services);
}
bool BootCampMissionWorld::regroupObjectiveTeam(const std::function<bool(TeamConstructionRecord&)>& regroup){
    if(!impl_->teamConstructed||!regroup)throw std::invalid_argument("Actual regroup Team/child required");
    return regroup(impl_->createdTeam);
}
bool BootCampMissionWorld::refreshObjectiveTeamReadiness(){
    auto& w=*impl_;if(!w.teamConstructed||w.createdTeam.type24!=&w.teamType)throw std::invalid_argument("Actual readiness Team required");
    std::vector<TeamAdmissionEntry> entries;const auto taskId=w.source.get("0B197B7C","TaskForce");
    for(int i=0;i<6;++i){const auto entry=w.source.get(taskId,std::to_string(i));if(entry.empty())break;
        const auto comma=entry.find(',');if(comma==std::string::npos)throw std::invalid_argument("Malformed actual TaskForce count");
        entries.push_back({integer(entry.substr(0,comma)),nullptr});
    }
    const auto count=std::int32_t(entries.size());TeamAdmissionTaskForce task{count,entries};
    const std::uint8_t ab=0,a7=0;TeamReadinessType type{ab,a7,task}; // Supplied original-Type startup fields.
    TeamReadinessServices services{{},{},{},{},{},w.emptyCell,{}};
    services.type24=[&]()->auto&{return type;};
    // Scenario Tag866164 notification and Team deleting destructor are not bound.
    // Their entered paths refuse rather than adopting empty recipients/no-op free.
    return refreshTeamReadiness(w.createdTeam,services);
}
MissionScriptAction BootCampMissionWorld::objectiveTeamScriptAction(const void* expected)const{
    const auto& w=*impl_;w.requireObjectiveScript(expected);
    return currentMissionScriptAction(w.teamScript,[&](const void* type){return w.scriptTypeState(type);});
}
MissionScriptAction BootCampMissionWorld::nextObjectiveTeamScriptAction()const{
    const auto& w=*impl_;w.requireObjectiveScript();
    return nextMissionScriptAction(w.teamScript,[&](const void* type){return w.scriptTypeState(type);});
}
bool BootCampMissionWorld::resetObjectiveTeamScript(){impl_->requireObjectiveScript();return resetMissionScript(impl_->teamScript);}
bool BootCampMissionWorld::advanceObjectiveTeamScript(){
    auto& w=*impl_;w.requireObjectiveScript();return advanceMissionScript(w.teamScript,[&](const void* type){return w.scriptTypeState(type);});
}
bool BootCampMissionWorld::objectiveTeamScriptHasCurrent()const{
    const auto& w=*impl_;w.requireObjectiveScript();return missionScriptHasCurrent(w.teamScript,[&](const void* type){return w.scriptTypeState(type);});
}
bool BootCampMissionWorld::recruitObjectiveInfantrySlot(std::int32_t slot,const TeamRecruitmentServices& input){
    auto& w=*impl_;
    if(!w.teamConstructed||w.createdTeam.type24!=&w.teamType||slot<0||slot>=6)
        throw std::invalid_argument("Actual objective recruitment Team/slot required");
    auto services=input;
    services.currentCount84=[&](int index){return std::bit_cast<std::int32_t>(w.createdTeam.values84.at(std::size_t(index)));};
    services.requiredCountA4=[&](int index){
        const auto entry=w.source.get(w.source.get("0B197B7C","TaskForce"),std::to_string(index));
        const auto comma=entry.find(',');
        if(comma==std::string::npos||lower(entry.substr(comma+1))!="e1")throw std::invalid_argument("Unsupported actual recruitment TaskForce slot");
        return integer(entry.substr(0,comma));
    };
    services.waypoint6BFA90=[&]{return w.emptyCell;}; // Existing supplied absent Waypoint association.
    const auto group=w.source.integer("0B197B7C","Group",-1);
    const auto taskGroup=w.source.integer(w.source.get("0B197B7C","TaskForce"),"Group",-1);
    const std::uint8_t flag=0;TeamMembershipType type{group,&taskGroup,flag,flag,flag};
    services.group6BFA60=[&]{return teamMembershipGroup(type);};
    services.requiredKind2C=[] {return 16;}; // Actual map entry is E1; Type construction supplied.
    services.typeA8=[] {return std::uint8_t(0);}; // Supplied Type startup, bypassed by Group=-2.
    return recruitInfantryTeamSlot(slot,services);
}
void BootCampMissionWorld::notifyInfantryTag(MissionTagState*& tag,const void* actor,int pulse,std::uint32_t location){
    auto& w=*impl_;
    if(!actor||!w.teamTagConstructed||tag!=&w.teamTag->view||
       (pulse!=48&&pulse!=29)||location!=w.emptyCell)
        throw std::invalid_argument("Foreign Infantry notification Tag/actor/pulse/location");
    MissionTagOwner owner{tag,actor};
    (void)raiseMissionTagEvent(*tag,{pulse,actor,0,0,nullptr},&owner,location,*w.tagServices);
}
MissionTagState* BootCampMissionWorld::objectiveTeamTag()const{return &impl_->teamTag->view;}
std::array<const void*,3> BootCampMissionWorld::objectiveTeamLinks()const{
    return {impl_->createdTeam.value54,impl_->createdTeam.cell34,impl_->createdTeam.value38};
}
bool BootCampMissionWorld::addObjectiveTeamMember(TeamMemberFoot foot,const TeamMembershipServices& input,const std::function<void(TeamConstructionRecord&,TeamMembershipType&)>& anchor){
    auto& w=*impl_;if(!w.teamConstructed||!w.teamTagConstructed)throw std::invalid_argument("Actual Team children required for membership");
    const auto group=w.source.integer("0B197B7C","Group",-1);
    const auto taskGroup=w.source.integer(w.source.get("0B197B7C","TaskForce"),"Group",-1);
    const std::uint8_t b3=0,ed=0,a7=0; // Supplied original-Type startup associations.
    TeamMembershipType type{group,&taskGroup,b3,ed,a7};auto services=input;
    services.type24=[&]()->auto&{if(w.createdTeam.type24!=&w.teamType)throw std::invalid_argument("Foreign live Team Type");return type;};
    services.setTag5D4430=[&](TeamMemberFoot& member,const void* tag){
        if(tag!=&w.teamTag->view)throw std::invalid_argument("Unbound Team Tag owner");
        (void)setMissionObjectTag({member.tag34,member.identity},&w.teamTag->view);
    };
    services.anchor6B9610=[&]{if(!anchor)throw std::invalid_argument("Actual Team anchor unbound");anchor(w.createdTeam,type);};
    return addTeamMember(w.createdTeam,&foot,services);
}
BootCampMissionWorld::State BootCampMissionWorld::state()const{
    State out;out.tagInstances=impl_->tag.instances;out.deferred=impl_->deferredCount;out.triggerDestroyed=impl_->trigger->destroyed;
    out.tagFreed=impl_->tagFreed;out.triggerFreed=impl_->triggerFreed;
    out.taggedStructures=std::count_if(impl_->structures.begin(),impl_->structures.end(),[](const auto& item){return item.second->tag!=nullptr;});
    out.registryCounts=impl_->registryCount;
    for(std::size_t i=0;i<impl_->controlled.size();++i) {
        const auto& owner=*impl_->controlled[i]->trigger;out.controlledEnabled[i]=owner.enabled;
        out.controlledTimers[i]=owner.timer;out.controlledPadding[i]=owner.timerPadding;
    }
    out.textRequests=impl_->textRequests;out.textKey=impl_->textKey;out.textPayload=impl_->textPayload;out.textColorSelector=impl_->textColorSelector;
    out.textColor=impl_->textColor;out.textStyle=impl_->textStyle;out.textDuration=impl_->textDuration;
    out.allyCalls=impl_->allyCalls;out.allyValue=impl_->allyValue;out.allyFrom=impl_->allyFrom;
    out.allyTo=impl_->allyTo;out.allyAnnounce=impl_->allyAnnounce;
    out.soundRequests=impl_->soundRequests;out.soundToken=impl_->soundToken;out.soundIndex=impl_->soundIndex;
    out.soundPanning=impl_->soundPanning;out.soundVolumeBits=impl_->soundVolumeBits;out.soundController=impl_->soundController;
    out.speechRequests=impl_->speechRequests;out.speechToken=impl_->speechToken;out.speechIndex=impl_->speechIndex;
    out.speechMode=impl_->speechMode;out.speechParameter=impl_->speechParameter;
    out.createTeamFactoryCalls=impl_->createTeamFactoryCalls;out.createTeamAllocations=impl_->createTeamAllocations;
    out.teamTagConstructed=impl_->teamTagConstructed;out.teamTriggerConstructed=impl_->teamTriggerConstructed;out.teamScriptConstructed=impl_->teamScriptConstructed;
    out.teamScriptCount=impl_->scriptCount;out.teamScriptCursor=impl_->teamScript.cursor2C;
    out.teamTagTriggerBound=impl_->teamTagConstructed&&impl_->teamTag->first==&impl_->teamTrigger->view;
    out.teamTriggerEnabled=impl_->teamTrigger->enabled;
    out.triggerControlCount=impl_->controlRegistry->count;
    if(impl_->teamTriggerConstructed)for(std::int32_t i=0;i<impl_->controlRegistry->count;++i)
        if(&missionTriggerControlSlot(*impl_->controlRegistry,i)==impl_->teamTriggerControl.get())out.teamTriggerControlBound=true;
    out.teamMemberCount=impl_->createdTeam.value48;out.teamThreat=impl_->createdTeam.value4C;
    out.teamTaskCounts=impl_->createdTeam.values84;out.teamTagInstances=impl_->teamTag->instances;
    out.teamFlags=impl_->createdTeam.flags74;out.teamScriptActionCount=impl_->teamScriptActionCount;
    out.teamConstructed=impl_->teamConstructed;out.teamTypeCount=impl_->teamTypeCount;
    out.teamTagChildRequests=impl_->teamTagChildRequests;out.teamScriptChildRequests=impl_->teamScriptChildRequests;
    out.teamRegistryCounts={impl_->teamRegistryCount[0],impl_->recipientCount,impl_->teamRegistryCount[1],impl_->teamRegistryCount[2]};
    out.createTeamRequests=impl_->createTeamRequests;out.createTeamId=impl_->createTeamId;
    out.createTeamArgument=impl_->createTeamArgument;out.teamCreationDepth=impl_->teamCreationDepth;
    out.createTeamDepthAtCall=impl_->createTeamDepthAtCall;
    out.revealRequests=impl_->revealRequests;out.revealWaypoint=impl_->revealWaypoint;
    out.revealCreateTeamRequestsAtCall=impl_->revealCreateTeamRequestsAtCall;
    out.revealSoundRequestsAtCall=impl_->revealSoundRequestsAtCall;
    out.revealHouse=impl_->revealHouse;out.revealObject=impl_->revealObject;
    out.revealTrigger=impl_->revealTrigger;out.revealPackedCell=impl_->revealPackedCell;
    return out;
}
}
