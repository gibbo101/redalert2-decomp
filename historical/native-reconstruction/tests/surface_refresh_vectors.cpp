// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/SurfaceRefresh.hpp"
#include <iostream>
#include <sstream>
#include <string>
using namespace ra2;
namespace {
void need(bool v){if(!v)throw std::invalid_argument("Refresh fixture domain");}
void run(std::istream& in){
    std::array<std::int32_t,12> f{};char op=0;need(bool(in>>op)&&op=='R');
    for(auto& v:f)need(bool(in>>v));std::string tail;need(!(in>>tail));
    need(f[1]>=0&&f[1]<=1&&f[6]>=0&&f[6]<=6&&f[7]>=0&&f[7]<=63&&f[8]>=0&&f[8]<=3&&f[9]>=0&&f[9]<=3&&f[10]>=0&&f[10]<=1&&f[11]>=0&&f[11]<=1000);
    for(int i=2;i<6;++i)need(f[i]>=-16&&f[i]<=8);
    RefreshSurfaceVirtuals tables[2];
    RefreshSurface actors[4]={{&tables[0],f[2],f[3]},{&tables[0],f[4],f[5]},{&tables[1],3,2},{&tables[1],2,3}};
    RefreshSurface* first=&actors[0];RefreshSurface* second=&actors[f[10]?0:1];
    SurfaceRefreshScratch scratch;RefreshRect alt;
    for(int i=0;i<4;++i){scratch.source[i]=f[11]+10+i;scratch.destination[i]=f[11]+20+i;alt[i]=f[11]+30+i;}
    auto sid=[&](RefreshSurface* p){for(int i=0;i<4;++i)if(p==&actors[i])return i;throw std::invalid_argument("Foreign surface");};
    auto rid=[&](RefreshRect* p){if(!p)return 0;if(p==&scratch.source)return 1;if(p==&scratch.destination)return 2;if(p==&alt)return 3;throw std::invalid_argument("Foreign rectangle");};
    auto rect=[&](RefreshRect* p){std::cout<<rid(p)<<' ';if(p)for(auto v:*p)std::cout<<v<<' ';};
    std::int32_t mode=f[0];bool changed=false;int getters=0;
    std::function<void(int,RefreshSurface&,RefreshRect*,RefreshSurface*,RefreshRect*,std::uint32_t,std::uint32_t)> copy;
    auto mutate=[&](int stage){
        if(changed||f[6]!=stage)return;changed=true;
        if(f[7]&1)first=&actors[2];if(f[7]&2)second=&actors[3];
        if(f[7]&4)actors[0].table=&tables[1];
        if(f[7]&8)tables[0].copy8=[&](auto& a,auto* b,auto* c,auto* d,auto e,auto g){copy(2,a,b,c,d,e,g);};
        if(f[7]&16)for(auto& a:actors){a.width=4;a.height=3;}
        if(f[7]&32)mode=mode?0:1;
    };
    copy=[&](int tag,auto& a,auto* b,auto* c,auto* d,auto e,auto g){
        std::cout<<"C "<<tag<<' '<<sid(&a)<<' ';rect(b);std::cout<<sid(c)<<' ';rect(d);std::cout<<e<<' '<<g<<' ';mutate(6);
    };
    for(int t=0;t<2;++t){
        tables[t].copy8=[&,t](auto& a,auto* b,auto* c,auto* d,auto e,auto g){copy(t,a,b,c,d,e,g);};
        tables[t].rect78=[&,t](RefreshSurface& a,RefreshRect& out){
            ++getters;std::cout<<"G "<<t<<' '<<sid(&a)<<' ';rect(&out);
            RefreshRect* result;
            if(f[1])result=refreshSurfaceRect(a,out);
            else {out[2]=a.width;out[3]=a.height;auto sel=f[getters==1?8:9];result=sel==0?&out:sel==1?&alt:sel==2?(getters==1?&scratch.destination:&scratch.source):nullptr;}
            std::cout<<"O ";rect(result);mutate(getters);return result;
        };
        tables[t].width7C=[&,t](auto& a){auto v=refreshSurfaceWidth(a);std::cout<<"W "<<t<<' '<<sid(&a)<<' '<<v<<' ';mutate(3);return v;};
        tables[t].height80=[&,t](auto& a){auto v=refreshSurfaceHeight(a);std::cout<<"H "<<t<<' '<<sid(&a)<<' '<<v<<' ';mutate(4);return v;};
    }
    SurfaceRefreshServices services{mode,first,second,[&]{std::cout<<"F ";},[&](auto& point){
        std::cout<<"P ";rect(&point);mutate(5);point[0]=-99;point[1]=-98;
    }};
    refreshSurfaces(services,scratch);
    std::cout<<"R "<<mode<<' '<<sid(first)<<' '<<sid(second)<<' '<<changed<<' ';
    for(auto& a:actors)std::cout<<(a.table==&tables[1])<<' '<<a.width<<' '<<a.height<<' ';
    for(auto* p:{&scratch.source,&scratch.destination,&alt})rect(p);std::cout<<'\n';
}
void guards(){
    int mode=0;RefreshSurfaceVirtuals table;RefreshSurface surface{&table,1,1};RefreshSurface* first=&surface;RefreshSurface* second=&surface;SurfaceRefreshScratch scratch{};
    int calls=0;SurfaceRefreshServices s{mode,first,second,[&]{++calls;},[&](auto&){++calls;}};
    auto refuses=[&]{bool refused=false;try{refreshSurfaces(s,scratch);}catch(const std::invalid_argument&){refused=true;}need(refused);};
    refuses();need(calls==0);
    table.rect78=refreshSurfaceRect;table.width7C=refreshSurfaceWidth;table.height80=refreshSurfaceHeight;
    table.copy8=[](auto&,auto*,auto*,auto*,auto,auto){};refreshSurfaces(s,scratch);need(calls==1);
    mode=1;surface.width=1048577;refuses();need(calls==1);
    surface.width=0;surface.height=2147483647;refreshSurfaces(s,scratch);need(calls==1);
    first=nullptr;refuses();need(calls==1);
    first=&surface;surface.width=1;surface.height=1;s.pixel632000=[](auto&){throw std::runtime_error("unrelated");};bool propagated=false;
    try{refreshSurfaces(s,scratch);}catch(const std::runtime_error&){propagated=true;}need(propagated);
    std::cout<<"surface refresh guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
