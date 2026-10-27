// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/ArchiveSequence.hpp"
#include <array>
#include <iomanip>
#include <iostream>
#include <algorithm>

int main() {
    using namespace ra2;
    try {
        char command;
        while(std::cin>>command) {
            if(command=='T') {
                unsigned theater;int previous;std::cin>>theater>>previous;
                auto names=theaterMixRequests(theater,previous);
                std::cout<<names.size();for(const auto& name:names) std::cout<<' '<<name;std::cout<<'\n';
            } else if(command=='S') {
                unsigned enumerate,media,count;std::cin>>enumerate>>media;
                std::array<std::vector<std::string>,3> names;
                for(auto& group:names){std::cin>>count;for(unsigned i=0;i<count;++i){std::string name;std::cin>>std::quoted(name);group.push_back(name);}}
                auto requests=startupMixRequests(enumerate!=0,media,names[1],names[2],
                    [&](const std::string& name){return std::find(names[0].begin(),names[0].end(),name)!=names[0].end();});
                std::cout<<requests.success<<' '<<requests.names.size();for(const auto& name:requests.names) std::cout<<' '<<name;std::cout<<'\n';
            } else throw std::runtime_error("Unknown sequence command");
            if(!std::cin) throw std::runtime_error("Malformed sequence input");
        }
    } catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
