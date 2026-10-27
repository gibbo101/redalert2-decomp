// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Formats.hpp"
#include <array>

namespace ra2 {
// Authored, bounded content reader. These are immutable mission definitions,
// not initialized runtime actors, a trigger scheduler or recovered INI loading.
struct MissionEventDefinition {
    std::int32_t kind=0,mode=0;
    std::string argument;
};
struct MissionActionDefinition {
    std::int32_t kind=0,mode=0;
    // Keep every field, including the separately encoded waypoint token.
    std::array<std::string,6> arguments;
};
struct MissionTriggerDefinition {
    std::string id,house,linked,name;
    std::array<std::int32_t,5> flags{};
    std::vector<MissionEventDefinition> events;
    std::vector<MissionActionDefinition> actions;
};
struct MissionTagDefinition {std::int32_t persistence=0;std::string name,trigger;};
enum class MissionActorKind {Infantry,Unit,Structure};
struct MissionActorDefinition {
    MissionActorKind kind;
    int key=0;
    std::string house,type,mission,tag;
    std::int32_t health=0,x=0,y=0,facing=0;
    // Original tokens, including infantry subcell and all unknown tail fields.
    // No defaults are substituted for their runtime initialization.
    std::vector<std::string> fields;
};
struct MissionVariableDefinition {std::string name;std::int32_t initial=0;};
struct MissionDefinition {
    std::string player,briefing,nextScenario;
    int homeWaypoint=0;
    std::map<int,std::string> houses;
    std::vector<MissionActorDefinition> actors; // section order, then numeric key
    std::map<std::string,MissionTriggerDefinition> triggers;
    std::map<std::string,MissionTagDefinition> tags;
    std::map<std::pair<int,int>,std::string> cellTags;
    std::map<int,MissionVariableDefinition> variables;
};
MissionDefinition readMissionDefinition(const Ini&);
}
