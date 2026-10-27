// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/StaticLight.hpp"
#include <openssl/evp.h>
#include <iostream>
#include <iomanip>
#include <sstream>
std::string hash(const std::vector<int>& values) {
    ra2::Bytes bytes;for(auto v:values)for(int shift=0;shift<32;shift+=8)bytes.push_back(std::uint8_t(std::uint32_t(v)>>shift));
    unsigned char h[EVP_MAX_MD_SIZE];unsigned size=0;EVP_Digest(bytes.data(),bytes.size(),h,&size,EVP_sha256(),nullptr);
    std::ostringstream out;for(unsigned i=0;i<size;++i)out<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(h[i]);return out.str();
}
void sourceFields(const ra2::LightSource& s) {
    std::cout<<s.intensity;for(int c:s.tint)std::cout<<' '<<c;
    std::cout<<' '<<s.minimumDetail<<' '<<s.x<<' '<<s.y<<' '<<s.z<<' '<<s.radius<<' '<<s.active;
}
int main(int argc,char** argv) {
 try {
    if(argc!=2)return 2;const auto data=ra2::readRenderData(ra2::readFile(argv[1]));std::string op;
    while(std::cin>>op) {
        if(op=="Q") {
            int radius;double intensity;std::array<double,3> tint;std::cin>>radius>>intensity>>tint[0]>>tint[1]>>tint[2];
            const auto t=ra2::lightTypeInputs(radius,intensity,tint);std::cout<<t.radius<<' '<<t.intensity;for(int c:t.tint)std::cout<<' '<<c;
        } else if(op=="K") {
            int detail;std::array<int,3> tint;std::cin>>detail>>tint[0]>>tint[1]>>tint[2];
            const auto c=ra2::terrainConverterInputs(tint,detail);for(int v:c.tint)std::cout<<v<<' ';std::cout<<c.shades;
        } else if(op=="C"||op=="A"||op=="P") {
            ra2::LightTypeInputs t;int x,y,z;std::cin>>t.radius>>t.intensity>>t.tint[0]>>t.tint[1]>>t.tint[2]>>x>>y>>z;
            auto source=ra2::makeStaticLight(t,x,y,z);
            if(op=="C")sourceFields(source);
            else {
                ra2::MapLightSettings settings;bool initial,active,enabled;int detail,n;
                std::cin>>settings.ambient>>settings.tint[0]>>settings.tint[1]>>settings.tint[2]>>settings.ground>>settings.level>>initial>>active>>detail>>enabled>>n;
                if(n<0||n>15000)return 4;std::vector<ra2::MapCell> cells(n);
                for(auto& c:cells){int elevation;std::cin>>c.x>>c.y>>elevation;if(elevation<0||elevation>31)return 5;c.z=std::uint8_t(elevation);}
                const bool absent=op=="P"&&t.intensity==0;
                source.active=op=="P"?false:initial;
                std::vector<std::size_t> visits;
                if(absent)source={0,0,0,0,0,{},false,0};
                else if(ra2::changeLightActive(source,op=="P"?true:active))visits=ra2::affectedLightCells(data,source,cells,detail,enabled);
                std::vector<ra2::CellLight> lights(n);std::vector<int> trace;
                for(auto i:visits) {
                    const auto& c=cells[i];trace.push_back(c.x);trace.push_back(c.y);
                    lights[i]=ra2::cellLight(data,settings,c.x,c.y,c.z,std::span(&source,1),detail);
                }
                std::vector<int> fields;
                for(const auto& l:lights) {
                    fields.push_back(l.scale);
                    for(int v:{l.sourceIntensity,l.ambient,l.terrain,l.bridge,l.tint[0],l.tint[1],l.tint[2]})fields.push_back(std::int16_t(std::uint16_t(v)));
                }
                sourceFields(source);std::cout<<' '<<visits.size()<<' '<<hash(trace)<<' '<<hash(fields);
            }
        } else return 3;
        if(!std::cin)return 6;std::cout<<'\n';
    }
 }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
