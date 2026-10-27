// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/Lighting.hpp"
#include "assets/Archive.hpp"
#include <fstream>
#include <iostream>
#include <string>
int main(int argc,char** argv) {
    try {
        if(argc==4&&std::string(argv[1])=="--export-vpl") {
            const auto root=std::filesystem::weakly_canonical(argv[2]),output=std::filesystem::weakly_canonical(argv[3]);
            for(auto parent=output;!parent.empty();) {
                if(parent==root)throw std::runtime_error("Use output outside the source installation");
                const auto next=parent.parent_path();if(next==parent)break;parent=next;
            }
            const auto data=ra2::AssetStore(root).require("voxels.vpl");(void)ra2::readVpl(data);
            if(std::filesystem::exists(output)) {
                const auto old=ra2::readFile(output);
                if(old.size!=data.size||!std::equal(old.ptr(),old.ptr()+old.size,data.ptr()))throw std::runtime_error("Refusing to overwrite different VPL data");
            } else {
                std::filesystem::create_directories(output.parent_path());std::ofstream stream(output,std::ios::binary);
                stream.write(reinterpret_cast<const char*>(data.ptr()),std::streamsize(data.size));
                if(!stream)throw std::runtime_error("Cannot write private VPL research data");
            }
            return 0;
        }
        if(argc!=3)return 2;
        const auto data=ra2::readRenderData(ra2::readFile(argv[1]));
        const auto vpl=ra2::readVpl(ra2::readFile(argv[2]));
        std::string op;
        while(std::cin>>op) {
            if(op=="L") {
                int type,single;ra2::Vec3 light,view;float intensity;
                std::cin>>type>>single>>light.x>>light.y>>light.z>>view.x>>view.y>>view.z>>intensity;
                for(auto v:ra2::voxelShades(data,type,light,view,intensity,single))std::cout<<unsigned(v)<<' ';
            } else if(op=="P") {
                int shades;std::array<int,3> tint;ra2::Palette p;std::array<std::uint8_t,256> mask;
                std::cin>>shades>>tint[0]>>tint[1]>>tint[2];
                for(auto& c:p){unsigned r,g,b;std::cin>>r>>g>>b;c={std::uint8_t(r),std::uint8_t(g),std::uint8_t(b)};}
                for(auto& v:mask){unsigned x;std::cin>>x;v=std::uint8_t(x);}
                for(const auto& row:ra2::lightPalette(data,p,tint,shades,mask))for(auto v:row)std::cout<<v<<' ';
            } else if(op=="V") {
                unsigned color,shade;std::cin>>color>>shade;std::cout<<unsigned(vpl.lookup(std::uint8_t(color),std::uint8_t(shade)));
            } else if(op=="Z") {
                int candidate;std::size_t count,size,start;std::cin>>candidate>>count>>size>>start;
                if(count>4096||size>4096)return 5;
                ra2::Palette16 palette;for(auto& v:palette)std::cin>>v;
                std::vector<std::uint8_t> source(count);for(auto& v:source){unsigned x;std::cin>>x;v=std::uint8_t(x);}
                std::vector<std::uint16_t> destination(count),depth(size);
                for(auto& v:destination)std::cin>>v;for(auto& v:depth)std::cin>>v;
                ra2::depthSpan(source,candidate,palette,destination,depth,start);
                for(auto v:destination)std::cout<<v<<' ';for(auto v:depth)std::cout<<v<<' ';
            } else return 3;
            if(!std::cin)return 4;std::cout<<'\n';
        }
    } catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 1;}
}
