// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/Archive.hpp"
#include <iomanip>
#include <iostream>
#include <array>

int main() {
    using namespace ra2;
    try {
        char command;
        while(std::cin>>command) {
            std::string name;
            if(command=='H') {
                std::cin>>std::quoted(name);std::cout<<mixHash(name)<<'\n';continue;
            }
            if(command=='B') {
                std::array<bool,100> expansions{};unsigned count;std::cin>>count;
                for(unsigned i=0;i<count;++i){unsigned value;std::cin>>value;if(value>=100) throw std::runtime_error("Expansion number");expansions[value]=true;}
                for(const auto& item:baseMixBootstrapNames(expansions)) std::cout<<item<<' ';
                std::cout<<'\n';continue;
            }
            if(command=='M') {
                std::string path;std::uint32_t origin;std::cin>>std::quoted(path)>>origin;
                Mix mix{readFile(path)};
                std::cout<<1<<' '<<mix.count()<<' '<<mix.bodySize()<<' '<<std::uint32_t(origin+mix.bodyOffset())
                         <<' '<<mix.hasChecksum()<<' '<<mix.isEncrypted()<<' '<<0;
                for(const auto& entry:mix.index()) std::cout<<' '<<entry.id<<' '<<entry.offset<<' '<<entry.length;
                std::cout<<'\n';continue;
            }
            if(command!='L') throw std::runtime_error("Unknown archive command");
            unsigned mask, count, isNull;
            std::cin>>mask>>isNull>>std::quoted(name)>>count;
            struct Archive {std::uint32_t origin, cached;std::vector<MixEntry> entries;};
            std::vector<Archive> archives(count);
            for(auto& archive:archives) {
                unsigned size;std::cin>>archive.origin>>archive.cached>>size;
                archive.entries.resize(size);
                for(auto& entry:archive.entries) std::cin>>entry.id>>entry.offset>>entry.length;
            }
            std::array<std::uint32_t,4> outputs{0xa1a1a1a1,0xb2b2b2b2,0xc3c3c3c3,0xd4d4d4d4};
            std::vector<std::uint32_t> writes;
            auto write=[&](unsigned index,std::uint32_t value){if(mask&(1u<<index)){outputs[index]=value;writes.push_back(index);writes.push_back(value);}};
            bool found=false;
            if(!isNull) for(unsigned i=0;i<archives.size();++i) {
                const auto& archive=archives[i];
                if(const auto* entry=findMixEntry(archive.entries,mixHash(name))) {
                    found=true;write(1,i);write(3,entry->length);write(0,0);write(2,entry->offset);
                    if(archive.cached) write(0,archive.cached+entry->offset);
                    else if(mask&4) write(2,outputs[2]+archive.origin);
                    break;
                }
            }
            std::cout<<found;
            for(auto value:outputs) std::cout<<' '<<value;
            for(auto value:writes) std::cout<<' '<<value;
            std::cout<<'\n';
            if(!std::cin) throw std::runtime_error("Malformed archive vector");
        }
    } catch(const std::exception& error) {std::cerr<<error.what()<<'\n';return 1;}
}
