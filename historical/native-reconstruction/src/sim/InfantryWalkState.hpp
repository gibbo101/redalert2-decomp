// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/InfantryWeaponSelection.hpp"
#include "sim/WalkMovement.hpp"
#include "sim/MovementGate.hpp"
#include "sim/MissionTag.hpp"
namespace ra2 {
// Actual mutable Infantry/Foot/Walk records. Startup and type/House association
// are supplied; this is not an original constructor or a second simulation.
struct InfantryWalkObject {
    int kind=15,next=-1;
    std::uint8_t gate=0,animation18=0,animation19=0;
    std::uint8_t flags14=1; // Supplied startup; distinct from onMap/active32D.
    // The actual House owner lives once, beside the mission fields.
    UnitDiscoveryActor mission;
    int statusA8=0,lastAC=0,timerStart=0,timerPadding=0,timerRemaining=0;
};
struct InfantryWalkState {
    ActorGroundState ground;
    Facing body;
    WalkMovementState walk;
    InfantryWalkObject object;
    std::array<std::int32_t,24> route;
    TerrainCellPoint cell450;
    int currentTurret10c=-1,immobilized3fc=0,field490=0,counter53c=0,state5ac=0;
    std::array<int,3> retry530{-1,0,0},wait558{-1,0,0};
    double percentage468=0,multiplier470=1,veterancy118=0;
    const void* target494=nullptr;
    const void* effect25c=nullptr;
    const void* field1b0=nullptr; // Supplied startup; complete6D6E50 setter.
    std::uint8_t accounting324=1,accounting5c1=0; // Supplied map startup.
    std::uint32_t threat400=0;const void* controller408=nullptr; // Supplied startup; transfer null-controller path only.
    // Supplied ordinary resume startup, on the actual Foot owner. The59D writer
    // is recovered; its later clearing/constructor and destination vector are not.
    std::uint8_t resume59d=0,resume577=0;
    std::int32_t resumePending488=0,resumeSpecial4b4=-1,resumeCount4ac=0;
    std::uint32_t valueD8=0; // Supplied startup; Script50 stores the raw argument.
    const void* transport588=nullptr; // Supplied startup, guarded resident admission.
    const void* teamNext4c8=nullptr;
    // Persistent supplied startup; complete Team RemoveMember writes these.
    std::int32_t mission9c=-1;
    const void* teamLink498=nullptr;const void* teamTarget22c=nullptr;
    std::uint8_t teamFlag5a2=0,flag37d=0;
    MissionTagState* objectTag34=nullptr;
    std::int32_t teamGroup1ac=-1;std::uint8_t teamLeader579=0;
    std::uint8_t targetFlag404=0,targetFlag57e=0; // Supplied startup; original clear writes.
    const void* team4c4=nullptr; // Supplied association; nonnull Team predicate remains unjoined.
    // Supplied full-health/recruitability/radio startup on this actual owner.
    // Team admission borrows them; original Infantry construction remains open.
    std::int32_t health6c=0,radioCountD0=0;
    std::array<const void*,8> radioLinksCC{};
    std::uint8_t recruitable379=1,recruitable37a=1;
    std::uint32_t references=3;
    std::uint8_t redraw75=0,special370=0,eligible5a0=1;
    std::uint8_t onMap7d=1,flag76=0,flag7a=0,field5a1=0,field57a=0,transition57b=0;
    std::uint8_t flag5c3=0,flag32c=0,flag32d=0,disabled204=0,disabled205=0,reset5cc=0,suspended598=0;
    std::int8_t secondary574=-1;
    // Persistent supplied radar startup, on this same Infantry owner.
    std::uint8_t byte170=0,radar325=0; //325 startup supplied.
    int alternateHouse410=-1,radarTimerStart13c=-1,radarTimerRemaining144=0;
    std::uint8_t radarRegistered37b=0; // Supplied startup; recovered marker writers.
    std::int32_t radarX1a0=0,radarY1a4=0; // Supplied initial marker coordinates.
    InfantryWalkState(){object.kind=15;route.fill(-1);}
};
struct InfantryWalkType {
    std::int32_t baseCost550=0; // Supplied Rules startup; recovered virtualAC read.
    int speed5a0=0,speedType5a4=0,image598=0;
    std::int32_t accountingIndex=0;std::uint8_t accounting202=0; // Supplied Type startup.
    std::uint8_t map205=1,veteranSpeed26c=0,eliteSpeed27e=0,c0b=0,c0d=0,c00=0,jumpJetB44=0;
    std::uint8_t trainAa0=0;
    std::uint8_t guardAreaVeteran27c=0,guardAreaElite28e=0,defaultGuardAreaB00=0; // Supplied Rules initialization.
    // Supplied stock zero startup; entered special resident paths refuse.
    std::uint8_t admissionC10=0,admissionC11=0,admissionC14=0;
    InfantryWeaponSelectionType weaponSelection;
    std::uint8_t radarAA6=0,radarAA7=0,radarVeteran277=0,radarElite289=0; // Supplied type startup.
    std::uint8_t radarFlag1ff=0; // Supplied type startup; no inferred semantic name.
};
struct InfantryWalkGlobals {
    int tick=0,occupationHeight=128,bridgeHeight=416,levelHeight=104;
    int loading=0,session=1,destinationDelay=8,setPadding=0,commencePadding=0,routePadding=0,orderPadding=0;
    double routeInterval=.01,projectionScale=1,veteranSpeed=1;
    std::uint32_t references=7;
};
}
