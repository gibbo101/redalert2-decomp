// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MissionDefinition.hpp"
#include "assets/PreparedStringLookup.hpp"
#include "sim/MessageColor.hpp"
#include "sim/TeamScript.hpp"
#include "sim/TeamMemberRemoval.hpp"
#include "sim/TeamExpiration.hpp"
#include "sim/TechnoReferenceCleanup.hpp"
#include "sim/MissionEvent.hpp"
#include "sim/UnitDiscovery.hpp"
#include "sim/BuildingCoordinates.hpp"
#include "sim/HouseThreat.hpp"
#include "sim/CellThreatChange.hpp"
#include "platform/BootCampBuildingExpiration.hpp"
#include "platform/BootCampSightState.hpp"
#include "render/BuildingRenderBounds.hpp"
#include "render/FrameInvalidation.hpp"
#include "render/BuildingStaticScan.hpp"
#include "render/BuildingVisibility.hpp"
#include "render/TechnoSpriteDraw.hpp"
#include "render/SpriteConverterSelection.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

namespace ra2 {
struct TeamMembershipType;struct TeamMemberFoot;struct TeamMembershipServices;struct TeamConstructionRecord;
struct TeamAdmissionFoot;struct TeamAdmissionServices;
struct TeamRecruitmentServices;
struct MissionScriptAction;
class AssetStore;
class OwnedMessagePresentation;
struct BuildingFrameRegistry;
// Stable application-owned records for the first Day1 discovery objective.
// Construction binds supplied mission definitions to recovered mission kernels;
// it does not recover scenario startup or execute unrecovered action effects.
class BootCampMissionWorld {
public:
    // References into the actual stable Structure owner. Startup values and
    // foundation dimensions are supplied; no Building constructor is implied.
    struct StructureResident {
        const void* identity;
        Coord& position88;
        int& next;
        std::uint8_t& flags14;
        const std::uint8_t& alternate79;
        const std::uint8_t& eligible5a0;
        const std::uint8_t& typeMapFlag205;
        int& width;
        int& height;
    };
    struct StructureResidentState {
        Coord position88{};int next=-1,width=0,height=0;
        std::uint8_t flags14=1,alternate79=0,eligible5a0=0,typeMapFlag205=0;
        bool operator==(const StructureResidentState&)const=default;
    };
    // Explicit read-only admission against the constructed objective Team.
    // Type/TaskForce association and child services retain their supplied scope.
    bool canAdmitObjectiveFoot(TeamAdmissionFoot,const void* e1Type,std::int32_t& slot,const TeamAdmissionServices&)const;
    bool addObjectiveTeamMember(TeamMemberFoot,const TeamMembershipServices&,const std::function<void(TeamConstructionRecord&,TeamMembershipType&)>&);
    bool recruitObjectiveInfantrySlot(std::int32_t,const TeamRecruitmentServices&);
    void tickObjectiveTeamRecruitment(const std::function<void(TeamConstructionRecord&,TeamMembershipType&)>&,
        const std::function<void(std::int32_t)>&,const std::function<std::uint32_t(const void*)>&,
        const std::function<const void*(const void*)>&,const std::function<void(const void*,std::uint8_t)>&,
        const std::function<std::uint32_t(TeamConstructionRecord&)>&,
        const std::function<void(const void*)>&,const std::function<void(const void*,std::uint32_t)>&,
        const std::function<TeamScriptServices::Transfer(const void*)>& transfer={});
    void expireObjectiveTeam(MissionExpirationVector<TeamExpirationRecipient*>&,std::uint32_t);
    MissionExpirationPointerView objectiveTeamSuccessor30();
    const std::uint8_t& objectiveTeamFlags14()const;
    const std::int32_t& expirationSessionA40774()const;
    bool removeObjectiveTeamMember(const void*,const void* e1Type,const TeamRemovalServices&);
    bool regroupObjectiveTeam(const std::function<bool(TeamConstructionRecord&)>&);
    bool refreshObjectiveTeamReadiness(); // Explicit dependency seam, no Team AI schedule.
    MissionScriptAction objectiveTeamScriptAction(const void* expectedScript=nullptr)const;
    MissionScriptAction nextObjectiveTeamScriptAction()const;
    bool resetObjectiveTeamScript();
    bool advanceObjectiveTeamScript();
    bool objectiveTeamScriptHasCurrent()const;
    // Borrow actual866178 registry and Team fields synchronously; rebind on clones.
    const std::int32_t& referenceCleanupTeamCount()const;
    void bindReferenceCleanupTeams(TechnoReferenceCleanupServices&);
    const void* objectiveTeamIdentity()const;
    MissionTagState* objectiveTeamTag()const;
    // Explicit null-attacker48/29 composition on the actual constructed Team Tag.
    void notifyInfantryTag(MissionTagState*&,const void* actor,int pulse,std::uint32_t location);
    std::array<const void*,3> objectiveTeamLinks()const;
    StructureResident structureResident(int actorKey);
    const StructureResidentState& structureResidentState(int actorKey)const;
    struct StructureSightState {
        BuildingRenderBoundsState renderBounds; // Supplied initial cache on this existing owner.
        BootCampSightState sight;
        // Supplied startup on the existing Structure owner, not a constructor
        // proof. Frame predicate reads these; no new writer/schedule is implied.
        std::uint8_t marked74=1,redraw75=0;
        std::uint8_t flag76=0,enabled32d=1,onMap7d=1;
        std::int16_t cell454=0,cell456=0; // Supplied unused stock Building fields.
        std::int32_t frameE0=0,stage42c=0,frame4ec=0,frame4f0=0; // Supplied drawing startup.
        std::int32_t sprite1bc=0;std::uint32_t spriteD8=0;
        std::uint8_t sprite204=0,sprite205=0,sprite5bb=0,sprite37c=0; // Supplied sprite startup.
        std::uint8_t image5b4=0; // Supplied startup; recovered image68 selector reads it.
        std::int32_t field564=0; // Supplied startup; original writer not recovered.
        double veterancy118=0.;
        std::int32_t radarTimerStart13c=-1,radarTimerRemaining144=0; // Supplied startup.
        std::int32_t radarMode1b8=0; // Supplied startup; distinct from Mission98.
        std::uint8_t radar5bd=0,radar5b7=0; // Supplied numeric field startup.
        std::int8_t radarSecondary574=-1; // Supplied stock-field startup; writer pending.
        std::uint8_t radarRegistered37b=0; // Supplied startup; recovered marker writers.
        std::int32_t radarX1a0=0,radarY1a4=0; // Supplied marker startup.
        bool operator==(const StructureSightState&)const=default;
    };
    struct StructureSight {
        const void* identity;
        Coord& position;
        UnitDiscoveryActor& discovery;
        StructureSightState& fields;
    };
    StructureSight structureSight(int actorKey);
    const BootCampBuildingExpirationType& structureSightType(int actorKey)const;
    PixelRect structureTypeImageBounds(int actorKey,const BuildingTypeBoundsServices&);
    BuildingImageState& structureTypeImageState(int actorKey);
    // Explicit complete43BE20 on the existing Structure/Type/health/mission owners.
    std::int32_t structureAnimationFrame(int actorKey,const double& threshold1368,const double& threshold1370)const;
    // Required child effects/image/pixel services remain explicit; borrows actual
    // Type/stage/Cell-coordinate/health/mission/frame/foundation/height owners.
    void drawStructureOrdinary(int actorKey,PixelPoint&,PixelRect&,const double& threshold1368,const double& threshold1370,const BuildingOrdinaryServices&);
    // Explicit unscheduled composition. Names/flags/theater/rules are supplied
    // startup; existing read-only AssetStore/SHP decoding and host heap services.
    const void* structureImageFromAssets(int actorKey,const AssetStore&,const std::int32_t& theater,double rulesTiming);
    void drawStructureOrdinaryFromAssets(int actorKey,PixelPoint&,PixelRect&,const double& threshold1368,
        const double& threshold1370,const AssetStore&,const std::int32_t& theater,double rulesTiming,BuildingOrdinaryServices);
    // Explicit6D1510 on the same Structure/Type/SHP owners. Entered converter,
    // timer, House and final wrapper children remain required services.
    void drawStructureSprite(int actorKey,const BuildingSpriteRequest&,TechnoSpriteServices);
    // Explicit selector on actual Type/House fields; external schemes and owner
    // predicate remain borrowed. Nonnull Type override backing is unbound.
    const void* structureSpriteConverter(int actorKey,SpriteConverterSelectionServices)const;
    PixelRect structureTypeImageBoundsFromAssets(int actorKey,const AssetStore&,
        const std::int32_t& theater,double rulesTiming);
    const std::uint8_t& structureRadarTypeFlag(const void* type)const;
    const StructureSightState& structureSightState(int actorKey)const;
    // Synchronous borrowed view; obtain a fresh view from each clone. Current
    // map-key registry order/association remains supplied startup.
    BuildingFrameRegistry buildingFrameRegistry();
    // Explicit synchronous view; provider must borrow the same Renderer and
    // require supplied Type image bounds on a cache miss. Rebind after cloning.
    FrameInvalidationRegistry buildingInvalidationRegistry(
        std::function<const PixelRect&(int,Coord,BuildingRenderBoundsState&)>);
    // Shares registry, redraw and bounds with invalidation. Drawing remains an
    // explicit required service until Building+FC is recovered; no scheduling.
    BuildingStaticRegistry buildingStaticRegistry(
        std::function<const PixelRect&(int,Coord,BuildingRenderBoundsState&)>,
        std::function<void(int,PixelRect,std::int32_t,std::int32_t)>);
    // Binds actual flags and coordinate getter; coordinate service must be empty.
    // Bounds/projection and entered final drawing remain explicit services.
    bool drawStructureIfVisible(int actorKey,PixelRect&,const PixelRect& viewport,
        std::int32_t force,std::int32_t special,BuildingVisibilityServices);
    // Pure logical identity bindings supplied by the containing Walk world.
    // Clones rebind them; callbacks may only map existing fields/identities.
    void bindResidentIdentities(std::function<const void*(int)>,std::function<int(const void*)>);
    struct StructureExpirationInspection {
        const void* identity;
        const void* tagIdentity;
        const void*& expiredNext;
        UnitDiscoveryActor& actor;
        BootCampBuildingExpirationState& fields;
    };
    // Diagnostic ownership access, never an ordinary SDL command or startup proof.
    StructureExpirationInspection inspectStructureExpiration(int actorKey);
    const BootCampBuildingExpirationState& structureExpirationState(int actorKey)const;

    // The containing Walk world supplies the actual visibility owner. Clones
    // never copy this callback; standalone inspection must bind its own leaf.
    void bindWaypointReveal(std::function<std::uint8_t(std::int32_t)>);
    struct State {
        std::int32_t tagInstances=0,deferred=0;
        bool triggerDestroyed=false,tagFreed=false,triggerFreed=false;
        std::size_t taggedStructures=0;
        std::array<std::int32_t,4> registryCounts{};
        // 0922D5DC, 0922D40C, 08FABE0C and 09CA94AC, in that order.
        std::array<std::uint8_t,4> controlledEnabled{};
        std::array<MissionEventTimer,4> controlledTimers{};
        std::array<std::int32_t,4> controlledPadding{};
        // Action11, color and found-label lookup are recovered. CSF loading/
        // UTF-8/layout/startup remain supplied; insertion uses the owned list.
        std::size_t textRequests=0;
        std::string textKey,textPayload;
        std::int32_t textColorSelector=0,textColor=0,textStyle=0;
        std::uint32_t textDuration=0;
        // Action37 parent order is recovered. Value13-to-player-House lookup and
        // the final House child effects remain supplied in this bounded owner.
        std::size_t allyCalls=0;
        std::int32_t allyValue=-1;
        std::array<std::int32_t,2> allyFrom{{-1,-1}},allyTo{{-1,-1}};
        std::array<std::uint8_t,2> allyAnnounce{};
        // Action19/21 parent arguments are recovered. Token-to-index startup
        // association and both audio children/playback remain supplied.
        std::size_t soundRequests=0,speechRequests=0;
        std::string soundToken,speechToken;
        std::int32_t soundIndex=-1,soundPanning=0,speechIndex=-1,speechMode=0,speechParameter=0;
        std::uint32_t soundVolumeBits=0;
        bool soundController=false;
        // Action4, Team and Tag/Trigger/Script construction are recovered.
        // Type startup and member production remain supplied.
        std::size_t createTeamRequests=0,createTeamFactoryCalls=0,createTeamAllocations=0;
        std::uint32_t teamMemberCount=0,teamThreat=0;
        std::array<std::uint32_t,6> teamTaskCounts{};
        std::array<std::uint8_t,16> teamFlags{};
        std::int32_t teamScriptActionCount=0;
        std::int32_t teamTagInstances=0;
        bool teamConstructed=false;std::int32_t teamTypeCount=0;
        bool teamTagConstructed=false,teamTriggerConstructed=false,teamScriptConstructed=false,teamTagTriggerBound=false;
        bool teamTriggerControlBound=false;std::int32_t triggerControlCount=0;
        std::uint8_t teamTriggerEnabled=0;std::int32_t teamScriptCount=0,teamScriptCursor=-1;
        std::size_t teamTagChildRequests=0,teamScriptChildRequests=0;
        std::array<std::int32_t,4> teamRegistryCounts{};
        std::string createTeamId;
        std::int32_t createTeamArgument=-1;
        std::uint32_t teamCreationDepth=0,createTeamDepthAtCall=0;
        // Action17 forwarding is recovered. The containing Walk world binds
        // actual waypoint/map/visibility; standalone owners require a leaf.
        std::size_t revealRequests=0;
        std::size_t revealCreateTeamRequestsAtCall=0,revealSoundRequestsAtCall=0;
        std::int32_t revealWaypoint=-1,revealHouse=-1,revealObject=-1;
        bool revealTrigger=false;
        std::uint32_t revealPackedCell=0;
    };
private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
public:
    BootCampMissionWorld(const MissionDefinition&,const Ini& map,const Ini& rules,const std::int32_t& frame,std::shared_ptr<const PreparedStringLookup>,const MessageColorTable&,std::unique_ptr<OwnedMessagePresentation>);
    ~BootCampMissionWorld();
    BootCampMissionWorld(const BootCampMissionWorld&)=delete;
    BootCampMissionWorld& operator=(const BootCampMissionWorld&)=delete;
    // Stable authored storage associated with the canonical mission House.
    // Startup, score allocation/population and original heap layout are supplied.
    struct HouseThreatState {
        std::array<std::int32_t,0x4204> grid{};
        std::int32_t enemy54F0=-1,count5504=0;
        std::vector<HouseThreatScore> scores;
        std::span<HouseThreatScore> slots;
        HouseThreatState()=default;
        HouseThreatState(const HouseThreatState&)=delete;
        HouseThreatState& operator=(const HouseThreatState&)=delete;
    };
    // Explicit unscheduled476B20 composition; stencil lifetime is one call.
    void changeCellThreat(HouseThreatCell,std::int32_t owner,std::int32_t delta,std::span<const std::int32_t,18>);
    HouseThreatState& houseThreat(int);
    const HouseThreatState& houseThreat(int)const;
    const std::map<int,UnitDiscoveryHouse>& houses()const;
    UnitDiscoveryHouse& house(int);
    const UnitDiscoveryHouse& house(int)const;
    HouseCountryType& countryType(int);
    const HouseCountryType& countryType(int)const;
    const int& discoveryMode()const;
    const int& currentHouse()const;
    bool discoverInfantry(UnitDiscoveryActor&);
    bool discoverInfantry(UnitDiscoveryActor&,int discoverer);
    // Synchronous actual GI/Tag owner view; null/constructed Team Tag only.
    bool discoverInfantry(int resident,UnitDiscoveryActor&,MissionTagState*&,int discoverer);
    bool discoverStructure(int actorKey);
    void drainDeferred();
    State state() const;
    OwnedMessagePresentation& messages();
    const OwnedMessagePresentation& messages()const;
    // Host ownership adapter, not a recovered game algorithm. Reconstructs all
    // views/services against new owners, copies warm values and remaps every
    // internal pointer (including unused registry/deferred tails). Definitions
    // retain their caller-owned immutable lifetime; Ini inputs are owned copies.
    // The frame must outlive the clone; in-progress dispatch is refused.
    std::unique_ptr<BootCampMissionWorld> clone(const std::int32_t& frame,std::function<const void*(const void*)> externalRemap={}) const;
};
}
