// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/TechnoReferenceCleanup.hpp"
#include <array>
#include <iostream>
#include <sstream>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("Reference cleanup fixture differs");}
void run(std::istream& in){
 std::array<int,10> f{};for(auto& x:f)require(bool(in>>x));std::string tail;require(!(in>>tail));
 require(f[0]>=-2&&f[0]<=4&&f[1]>=-2&&f[1]<=4&&f[2]>=0&&f[2]<=1&&f[3]>=0&&f[3]<=15&&f[4]>=0&&f[4]<=15&&f[5]>=0&&f[5]<=15&&f[6]>=0&&f[6]<=5&&f[7]>=0&&f[7]<=1&&f[8]>=0&&f[8]<=255&&f[9]>=0&&f[9]<=1);
 struct Foot {const void* target;int kind,mission;std::uint32_t a8=0x89abcdefu;std::uint8_t b=128;};
 struct Team {const void* a;const void* b;};
 int subjectToken,otherToken;const void* subject=f[2]?&subjectToken:nullptr;const void* other=&otherToken;
 std::array<Foot,4> feet;std::array<Team,4> teams;std::array<const void*,4> slots,alt;
 for(int i=0;i<4;++i){feet[i]={(f[3]>>i&1)?subject:other,(f[4]>>i&1)?2:15,(f[5]>>i&1)?25:5};teams[i]={(f[8]>>(2*i)&1)?subject:other,(f[8]>>(2*i+1)&1)?subject:other};slots[i]=&feet[f[7]?i%2:i];alt[i]=&feet[3-i];}
 int count=f[0],teamCount=f[1];bool replaced=false;
 const auto pid=[&](const void* p){if(!p)return 0;if(p==&subjectToken)return 1;if(p==other)return 2;for(int i=0;i<4;++i){if(p==&feet[i])return 10+i;if(p==&teams[i])return 20+i;}throw std::invalid_argument("Foreign fixture identity");};
 const auto event=[&](int k,std::uint32_t a=0,std::uint32_t b=0,std::uint32_t c=0,std::uint32_t d=0){std::cout<<k<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<' ';};
 const auto foot=[&](const void* p)->Foot&{for(auto& a:feet)if(p==&a)return a;throw std::invalid_argument("Foreign Foot");};
 TechnoReferenceCleanupServices s{count,teamCount};
 s.footSlot=[&](int i){require(i>=0&&i<4);auto p=(replaced?alt:slots)[i];event(6,i,pid(p));return p;};
 s.target228=[&](const void* p){auto target=foot(p).target;event(5,pid(p),pid(target));return target;};
 s.action1E0=[&](const void* p){event(2,pid(p));auto& a=foot(p);if(f[6]==1)a.target=nullptr;if(f[6]==2){a.kind=2;a.mission=25;}if(f[6]==3){replaced=true;count=0;teamCount=2;}if(f[6]==4)a.target=other;if(f[6]==5)teamCount=-1;};
 s.kind2C=[&](const void* p){event(3,pid(p),foot(p).kind);return foot(p).kind;};
 s.mission98=[&](const void* p){event(8,pid(p),foot(p).mission);return foot(p).mission;};
 s.aircraft=[&](const void* p){auto& a=foot(p);return TechnoReferenceAircraft{a.a8,a.b};};
 s.target370=[&](const void* p,const void* q){require(!q);event(4,pid(p));foot(p).target=nullptr;};
 s.teamSlot=[&](int i){require(i>=0&&i<4);auto& t=teams[f[9]?i%2:i];event(7,i,pid(&t));return TechnoReferenceTeam{&t,t.a,t.b};};
 s.store=[&](const void* p,std::int64_t off,std::uint32_t v,const void* q){require(!q&&!v);event(1,pid(p),std::uint32_t(off));};
 clearTechnoReferences(subject,s);
 std::cout<<"F "<<std::uint32_t(count)<<' '<<std::uint32_t(teamCount)<<' '<<replaced<<' ';
 for(auto& a:feet)std::cout<<pid(a.target)<<' '<<a.kind<<' '<<a.mission<<' '<<a.a8<<' '<<unsigned(a.b)<<' ';
 for(auto& t:teams)std::cout<<pid(t.a)<<' '<<pid(t.b)<<' ';std::cout<<'\n';
}
void guards(){int n=1,t=0,id;TechnoReferenceCleanupServices s{n,t};bool refused=false;try{clearTechnoReferences(&id,s);}catch(const std::invalid_argument&){refused=true;}require(refused);s.footSlot=[](int)->const void*{return nullptr;};refused=false;try{clearTechnoReferences(nullptr,s);}catch(const std::invalid_argument&){refused=true;}require(refused);n=0;t=1;refused=false;try{clearTechnoReferences(&id,s);}catch(const std::invalid_argument&){refused=true;}require(refused);n=INT32_MIN;t=0;s.footSlot=[](int i)->const void*{require(i>=0&&i<4);return nullptr;};refused=false;try{clearTechnoReferences(&id,s);}catch(const std::invalid_argument&){refused=true;}require(refused);n=-2;t=-1;clearTechnoReferences(nullptr,s);std::cout<<"Reference cleanup guards PASS\n";}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
