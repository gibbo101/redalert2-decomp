// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MissionDefinition.hpp"
#include <charconv>
#include <algorithm>
#include <limits>

namespace ra2 {
namespace {
std::vector<std::string> fields(const std::string& value) {
    std::vector<std::string> out;
    std::size_t start=0;
    do {
        const auto end=value.find(',',start);
        auto part=value.substr(start,end==std::string::npos?end:end-start);
        const auto first=part.find_first_not_of(" \t\r\n");
        out.push_back(first==std::string::npos?"":part.substr(first,part.find_last_not_of(" \t\r\n")-first+1));
        if(end==std::string::npos)break;
        start=end+1;
    }while(true);
    return out;
}
std::int32_t number(const std::string& value) {
    std::int32_t result=0;
    const auto [end,error]=std::from_chars(value.data(),value.data()+value.size(),result);
    if(error!=std::errc{}||end!=value.data()+value.size())throw std::invalid_argument("Invalid mission integer: "+value);
    return result;
}
void size(const std::vector<std::string>& value,std::size_t count) {
    if(value.size()!=count)throw std::invalid_argument("Unsupported mission record width: expected "+std::to_string(count)+", got "+std::to_string(value.size()));
}
bool absent(const std::string& id){return id.empty()||lower(id)=="none"||lower(id)=="<none>";}
template<class F>void counted(const std::string& value,std::size_t width,F append) {
    auto tokens=fields(value);const auto count=number(tokens.front());
    if(count<0||count>1024||tokens.size()!=1+width*std::size_t(count))
        throw std::invalid_argument("Unsupported mission event/action record width");
    for(int i=0;i<count;++i)append(tokens,1+std::size_t(i)*width);
}
}
MissionDefinition readMissionDefinition(const Ini& ini) {
    if(ini.integer("Basic","NewINIFormat",-1)!=4)throw std::invalid_argument("Mission requires base NewINIFormat=4");
    MissionDefinition out;
    out.player=ini.get("Basic","Player");out.briefing=ini.get("Basic","Briefing");
    out.nextScenario=ini.get("Basic","NextScenario");out.homeWaypoint=ini.integer("Basic","HomeCell",98);
    for(const auto& [key,value]:ini.section("Houses")) {
        const auto index=number(key);if(index<0||!out.houses.emplace(index,value).second)throw std::invalid_argument("Duplicate/negative mission House key");
    }
    for(const auto& [key,value]:ini.section("Triggers")) {
        const auto row=fields(value);size(row,8);
        MissionTriggerDefinition trigger;trigger.id=key;trigger.house=row[0];trigger.linked=lower(row[1]);trigger.name=row[2];
        for(int i=0;i<5;++i)trigger.flags[i]=number(row[i+3]);
        if(!ini.section("Events").contains(key)||!ini.section("Actions").contains(key))throw std::invalid_argument("Mission trigger missing event/action list: "+key);
        counted(ini.get("Events",key),3,[&](const auto& tokens,std::size_t at){trigger.events.push_back({number(tokens[at]),number(tokens[at+1]),tokens[at+2]});});
        counted(ini.get("Actions",key),8,[&](const auto& tokens,std::size_t at){
            MissionActionDefinition action;action.kind=number(tokens[at]);action.mode=number(tokens[at+1]);
            std::copy_n(tokens.begin()+at+2,6,action.arguments.begin());trigger.actions.push_back(std::move(action));
        });
        out.triggers.emplace(key,std::move(trigger));
    }
    for(const auto* section:{"Events","Actions"})for(const auto& [key,value]:ini.section(section))
        if(!out.triggers.contains(key))throw std::invalid_argument("Orphan mission event/action list: "+key);
    for(const auto& [key,trigger]:out.triggers)
        if(!absent(trigger.linked)&&!out.triggers.contains(trigger.linked))throw std::invalid_argument("Missing linked mission trigger");
    for(const auto& [key,value]:ini.section("Tags")) {
        const auto row=fields(value);size(row,3);const auto target=lower(row[2]);
        if(!out.triggers.contains(target))throw std::invalid_argument("Missing tagged mission trigger");
        out.tags.emplace(key,MissionTagDefinition{number(row[0]),row[1],target});
    }
    for(const auto& [key,value]:ini.section("CellTags")) {
        const auto position=number(key);const auto tag=lower(value);
        if(position<0||!out.tags.contains(tag)||!out.cellTags.emplace(std::pair{position%1000,position/1000},tag).second)
            throw std::invalid_argument("Invalid mission Cell tag");
    }
    for(const auto& [key,value]:ini.section("VariableNames")) {
        const auto row=fields(value);size(row,2);const auto index=number(key);
        if(index<0||!out.variables.emplace(index,MissionVariableDefinition{row[0],number(row[1])}).second)throw std::invalid_argument("Invalid mission variable key");
    }
    for(const auto [section,kind]:{std::pair{"Infantry",MissionActorKind::Infantry},std::pair{"Units",MissionActorKind::Unit},std::pair{"Structures",MissionActorKind::Structure}}) {
        std::map<int,MissionActorDefinition> actors;
        for(const auto& [key,value]:ini.section(section)) {
            auto row=fields(value);
            const auto needed=kind==MissionActorKind::Structure?std::size_t(17):std::size_t(14);size(row,needed);
            const auto index=number(key);
            MissionActorDefinition actor{kind,index,row[0],row[1],"",lower(row[kind==MissionActorKind::Infantry?8:kind==MissionActorKind::Unit?7:6]),number(row[2]),number(row[3]),number(row[4]),number(row[kind==MissionActorKind::Infantry?7:5]),row};
            if(kind!=MissionActorKind::Structure)actor.mission=row[6];
            if(index<0||(!absent(actor.tag)&&!out.tags.contains(actor.tag))||!actors.emplace(index,std::move(actor)).second)
                throw std::invalid_argument("Invalid mission actor key/tag");
        }
        for(auto& [key,actor]:actors)out.actors.push_back(std::move(actor));
    }
    return out;
}
}
