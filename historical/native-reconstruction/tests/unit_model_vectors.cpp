// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/UnitModels.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
using namespace ra2;
namespace {
int offset(ModelField f,int i) {
    switch(f) {
    case ModelField::Voxel:return 0xb0+i*8;
    case ModelField::Animation:return 0xb4+i*8;
    case ModelField::MaximumDimension:return 0x1bc;
    default:return 0x214+i*20+(int(f)-int(ModelField::CachePointer))*4;
    }
}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)) {
        std::istringstream in(line);char op;OrdinaryUnitModels t;
        int oldMask,allocMask,n;std::array<std::uint32_t,3> available;
        std::array<int,6> errors;std::uint32_t seed;
        in>>op>>t.image>>oldMask;for(auto& x:available)in>>x;
        in>>allocMask;for(auto& x:errors)in>>x;in>>n;
        if(op!='M'||n<1||n>6)throw std::invalid_argument("Invalid model input");
        std::vector<ModelSection> sections(n);
        for(auto& section:sections)for(auto& x:section.dimensions){int v;in>>v;x=std::uint8_t(v);}
        in>>t.maximumDimension>>seed;
        if(!in)throw std::invalid_argument("Missing model input");in>>std::ws;
        if(!in.eof())throw std::invalid_argument("Trailing model input");
        for(int i=0;i<3;++i)t.parts[i]={oldMask&(1<<(2*i))?ModelToken(1+2*i):0,
                                      oldMask&(1<<(2*i+1))?ModelToken(2+2*i):0};
        for(int i=0;i<4;++i)t.caches[i]={seed&(1<<i)?ModelToken(100+i):0,
                    seed+std::uint32_t(i),~seed-std::uint32_t(i),std::uint8_t(seed+i),seed^std::uint32_t(i)};
        struct File {int slot;};std::vector<File> files;int allocating=-1;
        UnitModelServices s;
        s.open=[&](std::string_view name){
            const bool hva=name.ends_with(".HVA");int part=0;
            if(name==t.image+"TUR.VXL"||name==t.image+"TUR.HVA")part=1;
            else if(name==t.image+"BARL.VXL"||name==t.image+"BARL.HVA")part=2;
            else if(name!=t.image+".VXL"&&name!=t.image+".HVA")throw std::invalid_argument("Unexpected file name");
            files.push_back({part*2+int(hva)});std::cout<<"open "<<name<<' '<<files.size()<<' ';return ModelToken(files.size());};
        s.available=[&](ModelToken f){auto slot=files.at(f-1).slot;std::cout<<"available "<<f<<' ';allocating=slot;return std::uint8_t(available[slot/2]);};
        s.close=[&](ModelToken f){std::cout<<"close "<<f<<' ';};
        s.destroy=[&](ModelKind k,ModelToken h){std::cout<<"destroy "<<int(k)<<' '<<h<<' ';};
        s.release=[&](ModelToken h){std::cout<<"free "<<h<<' ';};
        s.allocate=[&](ModelKind k){const int slot=allocating+(k==ModelKind::Animation?1:0);
            const ModelToken h=allocMask&(1<<slot)?ModelToken(7+slot):0;
            std::cout<<"allocate "<<int(k)<<' '<<h<<' ';return h;};
        s.construct=[&](ModelKind k,ModelToken h,ModelToken f){
            const auto& p=t.parts[files.at(f-1).slot/2];
            std::cout<<"construct "<<int(k)<<' '<<h<<' '<<f<<" previous "<<(k==ModelKind::Voxel?p.voxel:p.animation)<<' ';};
        s.errorByte=[&](ModelToken h){return h>=7?std::uint8_t(errors.at(h-7)):std::uint8_t(0);};
        s.sectionCount=[&](ModelToken){return n;};
        s.section=[&](ModelToken h,int i){if(!h)throw std::invalid_argument("Null voxel descriptor service");
            std::cout<<"section "<<h<<' '<<i<<' ';auto d=sections.at(i);d.animationAssociation=0x100000+std::uint32_t(h);return d;};
        s.associateAnimation=[&](ModelToken h,std::uint32_t a){std::cout<<"associate "<<h<<' '<<a<<' ';};
        s.queryKind=[] {std::cout<<"kind ";};s.queryMultipleTurrets=[] {std::cout<<"multiple ";};
        s.stored=[](ModelField f,int i,ModelToken v){std::cout<<"store "<<offset(f,i)<<' '<<(f==ModelField::CacheFlag?1:4)<<' '<<v<<' ';};
        loadOrdinaryUnitModels(t,s);std::cout<<"state ";
        for(const auto& p:t.parts)std::cout<<p.voxel<<' '<<p.animation<<' ';
        std::cout<<t.maximumDimension;
        for(const auto& c:t.caches)std::cout<<' '<<c.pointer<<' '<<c.count<<' '<<c.capacity<<' '<<int(c.flag)<<' '<<c.tail;
        std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
