// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/Archive.hpp"
#include "assets/Formats.hpp"
#include "assets/TerrainTypes.hpp"
#include <openssl/sha.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <set>
#include <cstdio>

static std::string digest(const ra2::Data& data) {
    unsigned char bytes[SHA256_DIGEST_LENGTH];SHA256(data.ptr(),data.size,bytes);
    std::ostringstream out;out<<std::hex<<std::setfill('0');for(auto byte:bytes)out<<std::setw(2)<<unsigned(byte);return out.str();
}
int main(int argc,char** argv) {
    try {
        if(argc!=2 && !(argc==4&&std::string(argv[2])=="--prototype-inputs")) {
            std::cerr<<"Usage: archive-inspect OWNED_DATA_DIR [--prototype-inputs MAP] < asset-names.txt\n";return 2;
        }
        ra2::AssetStore store(argv[1],ra2::AssetStore::Registration::InitialTemperate);
        const auto sources=store.sources();
        for(std::size_t i=0;i<sources.size();++i) {
            const auto& source=sources[i];const auto& mix=store.archive(i);
            std::cout<<"A "<<i<<' '<<std::quoted(source.name)<<' '<<std::quoted(source.file.string())<<' '
                <<source.offset<<' '<<source.bodyOffset<<' '<<mix.bodySize()<<' '<<mix.count();
            for(const auto& entry:mix.index())std::cout<<' '<<entry.id<<' '<<entry.offset<<' '<<entry.length;
            std::cout<<'\n';
        }
        std::vector<std::string> names;
        if(argc==4) {
            std::set<std::string> selected{"game.exe",argv[3],"rules.ini","art.ini","voxels.vpl","htnk.vxl","htnktur.vxl","htnkbarl.vxl",
                "htnk.hva","htnktur.hva","htnkbarl.hva","isotem.pal","unittem.pal","temperat.pal","temperat.ini"};
            const ra2::Ini mapSource(store.require(argv[3]).text());const auto map=ra2::readMap(mapSource);
            const ra2::Ini theater(store.require("temperat.ini").text());std::vector<std::string> tiles;
            for(int n=0;n<2048;++n) {
                char section[32];std::snprintf(section,sizeof(section),"TileSet%04d",n);
                if(theater.section(section).empty())break;
                const auto count=theater.integer(section,"TilesInSet",0);
                const auto prefix=theater.get(section,"FileName");
                if(count<0||count>10000)throw std::runtime_error("Invalid prototype tile count");
                for(int t=1;t<=count;++t) {char suffix[32];std::snprintf(suffix,sizeof(suffix),"%02d.tem",t);tiles.push_back(prefix+suffix);}
            }
            for(const auto& cell:map.cells) {
                const auto tile=(cell.tile==0xffff||cell.tile==0xffffffffu)?0:cell.tile;
                selected.insert(tiles.at(tile));
            }
            for(int n=1;n<=28;++n) {char name[32];std::snprintf(name,sizeof(name),"tree%02d.tem",n);selected.insert(name);}
            for(const auto& type:ra2::stockStaticPropTypes())selected.insert(type+".tem");
            names.assign(selected.begin(),selected.end());
        } else {std::string name;while(std::getline(std::cin,name))names.push_back(name);}
        for(const auto& name:names) {
            if(name.empty())continue;
            if(auto match=store.resolve(name)) {
                std::cout<<"Q "<<std::quoted(name)<<' '<<int(match->archive.has_value())<<' '
                    <<match->archive.value_or(0)<<' '<<std::quoted(match->file.string())<<' '
                    <<match->data.offset<<' '<<match->data.size<<' '<<digest(match->data)<<'\n';
            } else std::cout<<"M "<<std::quoted(name)<<'\n';
        }
    } catch(const std::exception& error) {std::cerr<<error.what()<<'\n';return 1;}
}
