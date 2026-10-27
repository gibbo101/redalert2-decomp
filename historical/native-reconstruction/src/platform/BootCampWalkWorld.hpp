// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/GameAssets.hpp"
#include "assets/MissionDefinition.hpp"
#include "assets/PreparedInfantryWalk.hpp"
#include "platform/BootCampMissionWorld.hpp"
#include "platform/BootCampVisibilityWorld.hpp"
#include "sim/TechnoSightRemoval.hpp"
#include "sim/MissionControl.hpp"
#include "sim/InfantrySightSchedule.hpp"
#include "sim/InfantryUpdatePositionE1.hpp"
#include "sim/CellDirtyEffect.hpp"
#include "platform/BootCampFootExpiration.hpp"
#include "sim/TeamExpiration.hpp"
#include "render/RadarMapNotification.hpp"
#include <set>
namespace ra2 {
class RadarStorage;
// Bounded Day1 host association/startup and direct-route policy. Original Walk
// algorithms and mutable owners stay in PreparedInfantryWalk. First-objective
// mission records are owned but no scheduler/action effects invoke them in play;
// no original startup/pathfinding claim.
class BootCampWalkWorld {
    friend class BootCampRadarActors; // Pure borrowed render views on these owners.
    friend struct BootCampWalkWorldInspection; // Private-data ownership regression checks only.
public:
    // Persistent supplied actor fields not yet consumed by other production
    // subsystems. Existing placement/on-map/32D fields are borrowed, never copied.
    struct PositionState {
        const void* alternate228=nullptr;const void* effect208=nullptr;const void* target34=nullptr;
        std::int32_t mode1b8=0,animation418=-1;
        std::int16_t footprintX454=0,footprintY456=0;
        std::uint8_t flag77=0,state59a=0x5a,state59c=0x5c;
    };
private:
    const GameAssets& assets_;
    const MissionDefinition& mission_;
    const Ini& source_;
    const Ini& rules_;
    const Ini& art_;
    InfantrySubcellData subcells_;
    WalkMovementNumerics numbers_;
    InfantryWalkType type_;
    MissionControlTable missionControl_; // Persistent table; INI parsing/layer startup supplied.
    struct House {float speed=1;};
    std::map<int,House> houseInputs_;
    std::vector<std::optional<UnitAdmissionRegistry>> registry_;
    std::array<std::uint32_t,108> speeds_{};
    std::shared_ptr<PreparedTerrainMap> prepared_;
    std::unique_ptr<MutableUnitMap> map_;
    std::vector<InfantryMembershipCell> cells_;
    std::map<int,InfantryWalkState> actors_;
    using SightState=BootCampSightState;
    std::map<int,SightState> sight_;
    std::vector<const void*> sightRegistry_;
    std::span<const void*> sightSlots_;
    std::int32_t sightCount_=0;
    std::map<int,PositionState> positions_;
    // Supplied null228 startup on map Foot actors without a Walk owner. These
    // persistent fields participate in reference cleanup, not movement or sight.
    struct PassiveFootReferences {
        const void* target228=nullptr;const void* next30=nullptr;
        MissionTagState* tag34=nullptr;UnitDiscoveryActor mission;
        const void* field1B0=nullptr;const void* target22C=nullptr;const void* effect25C=nullptr;const void* service208=nullptr;
        const void* team4C4=nullptr;const void* next4C8=nullptr;const void* link498=nullptr;const void* target494=nullptr;
        std::int32_t kind=0,numeric490=0,statusA8=0,radioCountD0=0,count4AC=0,count488=0,health6C=0;
        std::array<const void*,8> radioCC{};std::uint8_t byte170=0;
    };
    std::map<int,PassiveFootReferences> passiveFeet_;
    std::vector<const void*> footRegistry_;
    std::int32_t footCount_=0;
    std::map<int,BootCampFootExpirationState> footExpirations_;
    std::map<std::string,std::unique_ptr<BootCampFootTagOwner>> passiveTags_;
    std::map<std::string,std::uint8_t> passiveTypes_; // Supplied TypeC08 startup.
    std::map<int,TeamExpirationRecipient> teamFootRecipients_;
    std::vector<TeamExpirationRecipient*> teamFootBacking_;
    std::span<TeamExpirationRecipient*> teamFootSlots_;
    std::int32_t teamFootCount_=0;int teamFootRegistryIdentity_=0;
    std::int32_t footExpirationScratch_=0; // Supplied caller-local input; distinct from movement padding.
    std::uint8_t footExpirationGlobalA40D04_=0; // Distinct supplied startup.
    void expireFootRecipient(int,const MissionTeamExpiredAbstract&,std::uint32_t);
    MissionExpirationPointerView expirationNext30(const void*);
    const void* expirationResident(int)const;
    int expirationResidentId(const void*)const;

    void clearReferencesOwned(const void*);
    std::int32_t positionScratch_=0x12345678,positionTypeFootprint_=0;
    std::uint8_t positionTypeSpecial_=0;
    std::uint8_t veteranSight_=0,eliteSight_=0;
    std::int32_t threat598_=0; // Supplied ThreatPosed association, not recovered INI initialization.
    std::uint8_t sightType534_=0,sightTypeADD_=0; // Supplied zero startup, not recovered type defaults.
    std::int32_t sightRange_=0,sightHeightDivisor_=104;
    double veteranSightMultiplier_=1.;
    std::map<int,std::size_t> definitions_;
    UnitFoundationState foundation_;
    InfantryWalkGlobals globals_;
    OriginalRandomState random_;
    CellResidentKind6State residentSearch_;
    std::set<std::pair<int,int>> blocked_;
    std::unique_ptr<BootCampMissionWorld> missionWorld_;
    std::unique_ptr<PreparedInfantryWalk> walking_;
    std::unique_ptr<BootCampVisibilityWorld> visibilityWorld_;
    void bindWorld(bool initialize,const BootCampVisibilityWorld* visibilitySource=nullptr);
    std::uint32_t infantryCost(const void* type,const void* house)const;
    // Discarded clone only. Completes bounded ordinary E1 transfer; no live Team/SDL adoption.
    void resumeInfantryOwned(int id,const void* first,std::uint32_t second);
    bool attemptHouseTransferOwned(int id,int nextHouse,RadarStorage&,std::span<const std::int32_t,18>);
    CellDirtyEffectExit dirtyCell(int cellId);
    CellClosestResidentServices residentServices(int cellId);
    bool discoverResident(int,int house);
    bool clear(int x,int y,int level) const;
    std::vector<int> directRoute(int,Coord) const;
    void removeSight(int,std::uint32_t,std::uint32_t,std::uint32_t,std::uint32_t);
    void addSight(int,std::uint32_t,std::uint32_t,std::uint32_t,std::uint32_t);
    int sightActorId(const void*)const;
    TechnoSightActor sightActor(int);
    TechnoSightType sightType(int);
    void dispatchSight(int,int,std::uint32_t,std::uint32_t,std::uint32_t,const void*);
public:
    struct PositionCompositionResult {
        bool permissionSuccessContinuation=false;
        int initialState59a=0,initialState59c=0,finalState59a=0,finalState59c=0;
        std::int32_t initialScratch=0,finalScratch=0;
        std::uintptr_t currentCell=0,targetCell=0;
        int missionQueries=0,parentCellQueries=0,currentCellGetters=0,currentCellMapQueries=0,cellValueQueries=0;
        int residentSearches=0,kindQueries=0,nextReads=0;
        int kind2Queries=0,kind1Queries=0,targetKindQueries=0,targetCoordinateQueries=0;
        int locomotorQueries=0,sightMissionCalls=0,sightRemoveCalls=0,sightAddCalls=0,sightPostCalls=0;
        int sightRevealAreas=0,sightReveals=0,sightRemovals=0,sightMaskCalls=0,sightRedraws=0;
        int sightFinalRange=0,sightFinalActive=0;
        int alternateQueries=0,alternateTypeQueries=0,alternateMissionQueries=0,alternateResult=-1;
        int effectCellPointQueries=0,effectCellQueries=0;
        int permissionQueries=0,scratchStores=0,positionChildCalls=0,mapAssociationCalls=0,dirtyCalls=0;
        int tailActiveStore=0,discoveryCalls=0,initialDiscovered=0,finalDiscovered=0;
        std::uint8_t finalOwner5668=0,finalOwner5669=0,finalOwner13c=0;
        int arrivalNotifications=0,arrivalKind=-1,arrivalProcessCalls=0;
        Coord arrivalPosition{};
        std::uintptr_t positionCell=0;
        int positionCloakExit=-1,positionCloakPredicateQueries=0;
        std::uintptr_t dirtyCell=0;
        int dirtyPrefixExit=-1;
        // Discarded owner diagnostics: requests are not completed game effects.
        std::size_t finalMissionTextRequests=0,finalMissionMessageLines=0;
        std::int32_t finalMissionDeferred=0,finalMissionTagInstances=0;
    };
private:
    PositionCompositionResult composeUpdatePositionPreviewOwned(int);
public:
    BootCampWalkWorld(const GameAssets&,const MissionDefinition&,const Ini& map,const Ini& rules,const Ini& art);
    BootCampWalkWorld(const BootCampWalkWorld&)=delete;
    BootCampWalkWorld& operator=(const BootCampWalkWorld&)=delete;
    // Independent warm host snapshot; caller-owned immutable inputs outlive both.
    // Rebuilds all bindings and refuses unsupported external pointer owners.
    std::unique_ptr<BootCampWalkWorld> clone() const;
    const std::map<int,InfantryWalkState>& actors()const{return actors_;}
    const InfantryWalkState& actor(int id)const{return actors_.at(id);}
    // Explicit read-only Team admission seam; never called by step()/SDL.
    bool canAdmitToObjectiveTeam(int id,std::int32_t& slot)const;
    bool addToObjectiveTeam(int id); // Explicit composition, never step()/SDL.
    bool regroupObjectiveTeam(); // Explicit borrowed-owner child check.
    // Explicit whole existing-map-Foot broadcast; does not destroy/unlink Team.
    void composeObjectiveTeamExpiration(std::uint32_t removed=1);
    bool removeFromObjectiveTeam(int id); // Explicit complete unlink, unscheduled.
    // Explicit bounded recruitment/activation/Script50/20 tick, unscheduled.
    // Transfer requires borrowed radar and all18 threat-table inputs.
    void tickObjectiveTeamRecruitment(RadarStorage* radar=nullptr,std::span<const std::int32_t> threatTables={});
    bool recruitObjectiveTeamSlot(std::int32_t slot); // Original candidate choice; unscheduled.
    bool regroupObjectiveTeam(TeamConstructionRecord&);
    void selectObjectiveTeamAnchor(TeamConstructionRecord&,TeamMembershipType&);
    const MissionActorDefinition& definition(int id)const{return mission_.actors.at(definitions_.at(id));}
    const MutableUnitMap& map()const{return *map_;}
    BootCampMissionWorld& missionWorld(){return *missionWorld_;}
    const BootCampMissionWorld& missionWorld()const{return *missionWorld_;}
    BootCampVisibilityWorld& visibilityWorld(){return *visibilityWorld_;}
    const BootCampVisibilityWorld& visibilityWorld()const{return *visibilityWorld_;}
    int tick()const{return globals_.tick;}
    const int& tickOwner()const{return globals_.tick;}
    int residentHead(TerrainCellPoint,bool elevated=false)const;
    int composeClosestResident(Coord cellPoint,int x=0,int y=0,bool elevated=false,int ignore=-1){
        const auto identity=walking_->cellIdentity(cellPoint);
        const int cell=walking_->membership().cellId(reinterpret_cast<const void*>(identity));
        return closestCellResident(x,y,elevated,ignore,residentServices(cell==int(map_->cells.size())?-1:cell));
    }

    const PositionState& positionState(int id)const{return positions_.at(id);}
    std::int32_t positionScratch()const{return positionScratch_;}
    const CellResidentKind6State& residentSearchState()const{return residentSearch_;}
    InfantryKind6Search composeKind6ResidentSearch(Coord point){return walking_->findKind6(walking_->cellIdentity(point),residentSearch_);}
    PositionCompositionResult composeUpdatePositionPreview(int id);
    std::vector<PositionCompositionResult> composeUpdatePositionPreviewSequence(int id,int notifications);
    bool player(int id)const;
    bool move(int id,int x,int y,std::string& status);
    bool stop(int id,std::string& status);
    void step();
    // Explicit composition seams for verification. Production arrival remains
    // unwired pending live Cell-field/effect integration and SDL acceptance.
    void composeSight(int id);
    void composePostSight(int id);
    void composeArrivalSight(int id);
    // Complete map scan over the seven currently owned Techno actors. Registry
    // association/startup are supplied; runtime/MakeAlly do not schedule it yet.
    std::int32_t composeActorThreat(int actorId,const std::int32_t& rulesBE8);
    // Explicit unscheduled grid composition; caller borrows private research
    // stencil inputs for this call only. No executable or file read is added.
    void composeHouseThreatGrid(int houseId,std::span<const std::int32_t,18> tables,const std::int32_t& rulesBE8,TerrainCellPoint invalidCell);
    void composeHouseMapSight(bool addition,std::uint8_t skipBuildings=0,std::int32_t argument=0);
};
}
