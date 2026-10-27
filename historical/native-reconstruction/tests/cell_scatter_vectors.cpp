// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/CellScatter.hpp"
#include <bit>
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
template<class T>T read(std::istream& in){T v{};if(!(in>>v))throw std::invalid_argument("Missing Cell scatter input");return v;}
int main(){try{
    std::string line;
    while(std::getline(std::cin,line)){
        std::istringstream in(line);if(read<char>(in)!='C')return 2;
        CellScatterWorld w;const int n=read<int>(in);
        if(n<0||n>32)throw std::invalid_argument("Cell scatter member count");
        w.cells[0]={read<int>(in),read<int>(in)};
        const int flag=read<int>(in);if(flag<0||flag>255)throw std::invalid_argument("Cell scatter rule byte");
        w.rules1431=std::uint8_t(flag);w.rules10b4=read<int>(in);
        for(int i:{0,1}){const int a=read<int>(in),b=read<int>(in);if(a<0||a>255||b<0||b>255)throw std::invalid_argument("Cell scatter ability byte");w.types[i]={std::uint8_t(a),std::uint8_t(b)};}
        for(int i:{0,1})w.house194[i]=read<int>(in);
        for(int id=0;id<n;++id){CellScatterMember a;
            a.kind=read<int>(in);a.next=read<int>(in);a.type=read<int>(in);a.owner=read<int>(in);a.veterancy=std::bit_cast<double>(read<std::uint64_t>(in));
            if((a.kind!=1&&a.kind!=6&&a.kind!=36)||a.next< -1||a.next>=n||a.type<0||a.type>1||a.owner<0||a.owner>1)throw std::invalid_argument("Cell scatter member association");
            w.members[id]=a;
        }
        Coord at{read<int>(in),read<int>(in),read<int>(in)};
        const int m=read<int>(in),d=read<int>(in),layer=read<int>(in),mutation=read<int>(in),count=read<int>(in);
        if(m<0||m>255||d<0||d>255||layer<0||layer>255||mutation<0||mutation>5||count<1||count>8)throw std::invalid_argument("Cell scatter call domain");
        std::vector<std::uint32_t> results;for(int i=0;i<count;++i)results.push_back(read<std::uint32_t>(in));
        std::string extra;if(in>>extra)throw std::invalid_argument("Extra Cell scatter input");
        if(w.cells[0].primary< -1||w.cells[0].primary>=n||w.cells[0].elevated< -1||w.cells[0].elevated>=n)throw std::invalid_argument("Cell scatter head association");
        const auto event=[](auto... values){((std::cout<<values<<' '),...);};
        w.trace=[&](char op,int id,int v){event(op,id,v);};
        int grows=0,scatters=0;
        CellScatterServices services;
        services.grow=[&](int capacity){const auto result=results[std::size_t(grows)%results.size()];event('G',capacity,result);
            if(mutation==3&&grows==0){const int first=layer?w.cells[0].elevated:w.cells[0].primary;if(first!=-1){w.members.at(first).next=-1;event('d',3,first);}}
            if(mutation==5&&grows==0&&n){w.members.at(n-1).veterancy=2.0;event('d',5,n-1);}
            ++grows;return result;};
        services.release=[&](int capacity){event('F',capacity,0);};
        services.scatter=[&](int id,const Coord& point,std::uint8_t im,std::uint8_t dest){
            if(&point!=&at)throw std::runtime_error("Scatter lost borrowed coordinate identity");
            event('S',id,point.x,point.y,point.z,int(im),int(dest));
            if(scatters++==0){
                if(mutation==1){w.cells[0]={-1,-1};for(auto& [key,a]:w.members){(void)key;a.next=-1;}event('d',1,id);}
                if(mutation==2){w.rules1431=0;w.house194[0]=-2147483647-1;w.house194[1]=2147483647;w.types[0]={0,0};if(n){w.members[n-1].owner=0;w.members[n-1].veterancy=0;}event('d',2,id);}
                if(mutation==4){at={-2147483647-1,2147483647,-17};event('d',4,id);}
            }
        };
        scatterCellResidents(0,at,std::uint8_t(m),std::uint8_t(d),std::uint8_t(layer),w,services);
        event("state",int(w.rules1431),w.rules10b4,w.cells[0].primary,w.cells[0].elevated,at.x,at.y,at.z);
        for(const auto& [id,a]:w.members)event(id,a.kind,a.next,a.type,a.owner,std::bit_cast<std::uint64_t>(a.veterancy));
        for(const auto& [id,t]:w.types)event(id,int(t.veteranAbility3),int(t.eliteAbility3));
        for(const auto& [id,value]:w.house194)event(id,value);
        std::cout<<'\n';
    }
    return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
