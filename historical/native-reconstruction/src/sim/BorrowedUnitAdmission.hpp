// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/UnitAdmission.hpp"

namespace ra2 {
// Narrow field views for the same admission/gate/next-Cell policies. References
// are explicit; no numeric proxy, copied actor, or automatic refresh is involved.
struct AdmissionPointView {const std::int16_t& x;const std::int16_t& y;};
struct AdmissionGateObjectView {
    const int& kind;int& next;const int& owner;
    const std::uint8_t& gate;const std::uint8_t& animation18;const std::uint8_t& animation19;
    UnitDiscoveryActor& mission;
    int& statusA8;int& lastAC;int& timerStart;int& timerPadding;int& timerRemaining;
};
struct AdmissionGateCellView {AdmissionPointView point;int& head;};
struct AdmissionCellView {
    const std::int16_t& registry;const std::int8_t& level;const std::uint8_t& ramp;
    const std::uint32_t& flags;const std::uint32_t& occupation;const std::uint32_t& elevatedOccupation;
    const int& owner;const int& elevatedOwner;const int& land;int& elevatedHead;
};
struct AdmissionObjectView {
    const std::uint8_t& flags;const std::uint8_t& crushable;const std::uint8_t& crusher;
    const std::uint8_t& train;const std::uint8_t& building1350;
    const int& state1b8;const int& destination;
    const bool& weapon;const bool& projectile275;
    const void* const& target494;
    const std::map<const void*,int>& targetIds;
    int targetIdentity()const{
        if(!target494)return -1;
        // A Cell target is an explicit non-actor identity, never null or Unit0.
        const auto found=targetIds.find(target494);
        if(found==targetIds.end())throw std::invalid_argument("Unbound admission target identity");
        return found->second;
    }
};
struct AdmissionMotionView {
    const Coord& position;const Coord& destination;const Coord& head;const Facing& body;
    const std::uint8_t& eligibility5a0;
    const int& queueHead;const int& track;const int& index;const std::uint8_t& shortTrack;
};
struct AdmissionHouseView {const int& index;const std::uint32_t& allies;};
// Non-owning logical House lookup. The callbacks only borrow fields; they may
// not query gameplay or synchronize copies. Owners outlive every binding.
class AdmissionHouses {
    std::function<AdmissionHouseView(int)> at_;
    std::function<bool(int)> contains_;
public:
    AdmissionHouses(const std::map<int,MovementGateHouse>& owners)
        :at_([&owners](int id){const auto& h=owners.at(id);return AdmissionHouseView{h.index,h.allies};}),
         contains_([&owners](int id){return owners.contains(id);}){}
    AdmissionHouses(std::function<AdmissionHouseView(int)> at,std::function<bool(int)> contains)
        :at_(std::move(at)),contains_(std::move(contains)){}
    AdmissionHouseView at(int id)const {if(!at_)throw std::invalid_argument("Missing borrowed House lookup");return at_(id);}
    bool contains(int id)const {if(!contains_)throw std::invalid_argument("Missing borrowed House membership");return contains_(id);}
};
struct BorrowedMovementGateWorld {
    AdmissionHouses houses;
    std::map<int,AdmissionGateObjectView> objects;
    std::map<int,AdmissionGateCellView> cells;
    std::span<const int> slots;
    int fallbackCell;
    const int& tick;const int& setPadding;const int& commencePadding;
    std::function<void(char,int)> trace;
    std::function<void(int,int)> kindResult;
    std::function<void(int,int,int,std::uint32_t)> store;
    std::function<void(TerrainCellPoint)> fallbackStore;
    // Sole physical fallback forwarding. Observers above do not mutate owners.
    std::function<void(TerrainCellPoint)> forwardFallback;
    std::function<void(TerrainCellPoint)> forwardAssignedFallback;
    void storeFallbackPoint(TerrainCellPoint p){
        if(!forwardFallback)throw std::invalid_argument("Missing borrowed admission fallback forwarding");
        forwardFallback(p);
    }
};
struct BorrowedUnitAdmissionWorld {
    BorrowedMovementGateWorld gates;
    std::map<int,AdmissionCellView> cells;
    std::map<int,AdmissionObjectView> objects;
    const std::vector<std::optional<UnitAdmissionRegistry>>& registry;
    const std::array<std::uint32_t,12>& speedBits;
    const std::array<TerrainCellPoint,8>& directions;
    std::function<void(char,int,int,int)> trace;
};
struct BorrowedAdmissionMotionWorld {
    std::map<int,AdmissionMotionView> actors;
    const DriveData* data;
    const std::function<double(double)>& squareRoot;
};
}
