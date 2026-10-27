// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/Archive.hpp"
#include "assets/MissionDefinition.hpp"
#include "assets/StringTable.hpp"
#include <iostream>
#include <iomanip>
int main(int argc,char** argv){try {
    if(argc<2||argc>3){std::cerr<<"Usage: mission-inspect OWNED_DATA_DIR [MAP]\n";return 2;}
    ra2::AssetStore store(argv[1],ra2::AssetStore::Registration::InitialTemperate);
    const std::string name=argc==3?argv[2]:"trn01t.map";
    const ra2::Ini source(store.require(name).text());const auto map=ra2::readMap(source);
    const auto mission=ra2::readMissionDefinition(source);const auto strings=ra2::readStringTable(store.require("ra2.csf"));
    std::size_t textActions=0;
    for(const auto& [id,trigger]:mission.triggers)for(const auto& action:trigger.actions)
        if(action.kind==11){(void)ra2::localizedText(strings,action.arguments[0]);++textActions;}
    std::cout<<"Map "<<name<<" cells "<<map.cells.size()<<" triggers "<<mission.triggers.size()<<" tags "<<mission.tags.size()<<" cell-tags "<<mission.cellTags.size()<<" actors "<<mission.actors.size()<<'\n';
    std::cout<<"Player "<<std::quoted(mission.player)<<" home-waypoint "<<mission.homeWaypoint<<" CSF-labels "<<strings.size()<<" resolved-text-actions "<<textActions<<'\n';
    std::cout<<"Briefing "<<std::quoted(ra2::localizedText(strings,mission.briefing))<<'\n';
    for(const auto& actor:mission.actors)if(ra2::lower(actor.house)==ra2::lower(mission.player))
        std::cout<<"Player-actor "<<actor.key<<' '<<actor.type<<' '<<actor.x<<','<<actor.y<<" facing "<<actor.facing<<" tag "<<actor.tag<<'\n';
    std::cout<<"Content inspection only; no initialized actors, event/action execution, objectives or campaign progression.\n";
    return 0;
}catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}}
