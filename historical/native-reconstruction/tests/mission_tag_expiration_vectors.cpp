// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MissionTagExpiration.hpp"
#include <array>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
using namespace ra2;
namespace {
void require(bool ok){if(!ok)throw std::invalid_argument("Tag expiration fixture outside domain");}
void run(std::istream& in) {
    std::array<std::int32_t,2> instances{},persistence{};
    int global0,global1,mode,selection,n;require(bool(in>>instances[0]>>instances[1]>>global0>>global1>>mode>>selection>>n));
    require(n>=0&&n<=4&&mode>=0&&mode<=5);
    std::array<std::uint8_t,2> executing{};std::array<MissionTagType,2> types{{{persistence[0]},{persistence[1]}}};
    std::array<MissionTagType*,2> type{&types[0],&types[1]};std::array<MissionTagTrigger*,2> first{};
    std::array<MissionTagState,2> tags{{{type[0],first[0],instances[0],executing[0]},{type[1],first[1],instances[1],executing[1]}}};
    auto tag=[&](int id)->MissionTagState*{require(id>=0&&id<=2);return id?&tags[std::size_t(id-1)]:nullptr;};
    const void* g0=tag(global0);const void* g1=tag(global1);int globalsIdentity[2]{},content=0,vectorIdentity[4]{};
    struct Cell {std::uint32_t point=0;MissionTagState* tag=nullptr;const void* a=nullptr;const void* b=nullptr;const void* content=nullptr;std::unique_ptr<MissionExpirationCell> view;};
    std::array<Cell,5> cells;std::vector<MissionExpirationCell*> table(262144,nullptr);
    for(int i=0;i<=n;++i) {
        auto& c=cells[std::size_t(i)];int slot=-1,t,a,b,has;
        require(bool(in>>c.point));if(i<n)require(bool(in>>slot));require(bool(in>>t>>a>>b>>has));
        c.tag=tag(t);c.a=tag(a);c.b=tag(b);c.content=has?&content:nullptr;
        c.view=std::make_unique<MissionExpirationCell>(c.point,c.tag,c.a,c.b,c.content,&c);
        require(slot>=-1&&slot<262144);if(slot>=0)table[std::size_t(slot)]=c.view.get();
    }
    std::array<std::uint32_t,32> pointBuffer{};std::array<const void*,32> mapBuffer{},logicBuffer{};
    std::array<MissionTagExpirationRecipient,3> recipients;std::array<MissionTagExpirationRecipient*,32> recipientBuffer{},alternate{};
    std::span<std::uint32_t> points=pointBuffer;std::span<const void*> maps=mapBuffer,logic=logicBuffer;
    std::span<MissionTagExpirationRecipient*> listeners=recipientBuffer;
    int pointCount,mapCount,logicCount,recipientCount;
    auto read=[&](int& count,auto set){require(bool(in>>count)&&count>=0&&count<=16);for(int j=0;j<count;++j){std::uint32_t v;require(bool(in>>v));set(j,v);}};
    read(pointCount,[&](int j,auto v){pointBuffer[std::size_t(j)]=v;});
    read(mapCount,[&](int j,auto v){mapBuffer[std::size_t(j)]=tag(int(v));});
    read(logicCount,[&](int j,auto v){logicBuffer[std::size_t(j)]=tag(int(v));});
    read(recipientCount,[&](int j,auto v){require(v>=1&&v<=3);recipientBuffer[std::size_t(j)]=&recipients[v-1];});
    auto id=[&](const void* p)->int{
        if(!p)return 0;for(int i=0;i<2;++i){if(p==&tags[std::size_t(i)])return 10+i;if(p==&globalsIdentity[i])return 50+i;}
        for(int i=0;i<=n;++i)if(p==&cells[std::size_t(i)]||p==&cells[std::size_t(i)].tag)return i==n?39:30+i;
        for(int i=0;i<4;++i)if(p==&vectorIdentity[i])return 40+i;
        for(int i=0;i<3;++i)if(p==&recipients[std::size_t(i)])return 60+i;
        if(p==&g0)return 50;if(p==&g1)return 51;throw std::invalid_argument("Unknown expiration identity");
    };
    MissionTagStore store=[&](const void* p,auto off,auto value,const void* ptr){std::cout<<"W "<<id(p)<<' '<<off<<' '<<(ptr?std::uint32_t(id(ptr)):value)<<' ';};
    MissionExpirationVector<std::uint32_t> pointVector{pointCount,points,&vectorIdentity[0]};
    MissionExpirationVector<const void*> mapVector{mapCount,maps,&vectorIdentity[1]},logicVector{logicCount,logic,&vectorIdentity[2]};
    MissionExpirationVector<MissionTagExpirationRecipient*> listenerVector{recipientCount,listeners,&vectorIdentity[3]};
    MissionTagExpirationMap map{pointVector,mapVector,table,*cells[std::size_t(n)].view,store};
    bool changed=false;
    for(int i=0;i<3;++i){auto& r=recipients[std::size_t(i)];r.identity=&r;r.expired=[&,i](auto& subject,auto removed){
        std::cout<<"C "<<i+1<<' '<<id(&subject)<<' '<<removed<<' ';
        if(changed)return;changed=true;
        if(mode==1)recipientCount=0;
        if(mode==2){alternate[0]=&recipients[2];alternate[1]=&recipients[1];alternate[2]=&recipients[0];listeners=alternate;recipientCount=3;}
        if(mode==3)recipientBuffer[1]=&recipients[2];
        if(mode==4){if(n)cells[0].tag=&tags[1];cells[std::size_t(n)].tag=&subject;}
        if(mode==5)pointCount=0;
    };}
    MissionTagExpirationServices services{g0,g1,listenerVector,map,logicVector};services.store=store;
    services.clearMapSelection=[&]{std::cout<<"S ";if(selection){g0=&tags[1];g1=&tags[0];}};
    services.abstractType=[&](auto& t){std::cout<<"D "<<id(&t)<<' ';return false;};
    int count;require(bool(in>>count)&&count>0&&count<=16);
    for(int i=0;i<count;++i) {
        int root,subject;std::uint32_t removed;require(bool(in>>root>>subject>>removed));std::cout<<"O "<<root<<' ';
        if(root==0)broadcastMissionTagExpiration(*tag(subject),removed,services);
        else if(root==1)expireMissionMapTag(*tag(subject),map);
        else if(root==2)expireMissionLogicTag(tag(subject),logicVector,store);
        else if(root==3){require(subject>=0&&subject<=n);expireMissionCellTag(*cells[std::size_t(subject)].view,tags[0],pointVector,store);}
        else if(root==4)expireMissionLogicTag(nullptr,logicVector,store);
        else require(false);
        std::cout<<"R ";
    }
    std::string extra;require(!(in>>extra));
    std::cout<<"state "<<instances[0]<<' '<<instances[1]<<' '<<id(g0)<<' '<<id(g1)<<' '<<changed<<' ';
    for(int i=0;i<=n;++i){const auto& c=cells[std::size_t(i)];std::cout<<c.point<<' '<<id(c.tag)<<' '<<id(c.a)<<' '<<id(c.b)<<' '<<bool(c.content)<<' ';}
    std::cout<<pointCount<<' '<<mapCount<<' '<<logicCount<<' '<<recipientCount<<' '<<(listeners.data()==alternate.data())<<' ';
    for(auto p:pointBuffer)std::cout<<p<<' ';for(auto p:mapBuffer)std::cout<<id(p)<<' ';for(auto p:logicBuffer)std::cout<<id(p)<<' ';
    for(auto p:recipientBuffer)std::cout<<id(p)<<' ';for(auto p:alternate)std::cout<<id(p)<<' ';std::cout<<'\n';
}
void guards(){
    std::uint32_t packedPoint=0x8001ffffu;std::int16_t wordX=-1,wordY=-32767;
    MissionExpirationPointView packedView{packedPoint},wordsView{wordX,wordY};
    require(std::uint32_t(packedView)==std::uint32_t(wordsView));
    wordsView=0x7fff8000u;require(wordX==-32768&&wordY==32767);
    wordX=123;wordY=-2;require(std::uint32_t(wordsView)==0xfffe007bu);
    packedView=std::uint32_t(wordsView);require(packedPoint==0xfffe007bu);

    int count=1,identity=0;std::array<const void*,1> backing{&identity};std::span<const void*> slots=backing;
    MissionExpirationVector<const void*> v{count,slots,&v};bool refused=false;
    try{(void)missionExpirationSlot(v,1);}catch(const std::invalid_argument&){refused=true;}require(refused&&count==1);
    eraseMissionExpiration(v,-1);require(count==1);expireMissionLogicTag(nullptr,v);require(count==1);
    refused=false;try{eraseMissionExpiration(v,-2);}catch(const std::invalid_argument&){refused=true;}require(refused&&count==1);
    int persistence=0,instances=0;std::uint8_t executing=0;MissionTagType type{persistence};auto* typePointer=&type;MissionTagTrigger* first=nullptr;
    MissionTagState tag{typePointer,first,instances,executing};MissionTagState* cellTag=&tag;std::uint32_t point=0;const void* a=&tag;const void* b=&identity;const void* content=&identity;
    MissionExpirationCell cell{point,cellTag,a,b,content,&cellTag};
    int pointsCount=0;std::array<std::uint32_t,1> pb{};std::span<std::uint32_t> ps=pb;MissionExpirationVector<std::uint32_t> points{pointsCount,ps,&points};
    expireMissionCellTag(cell,tag,points);require(!cellTag&&!a&&b==&identity&&instances==-1);
    std::array<MissionExpirationCell*,1> table{nullptr};MissionTagExpirationMap map{points,v,table,cell,{}};
    require(&missionExpirationCell(0xffffffffu,map)==&cell&&point==0xffffffffu);
    refused=false;try{(void)missionExpirationCell(1,map);}catch(const std::invalid_argument&){refused=true;}require(refused);
    const void* g0=nullptr;const void* g1=nullptr;int rc=0;std::span<MissionTagExpirationRecipient*> recipients;
    MissionExpirationVector<MissionTagExpirationRecipient*> rv{rc,recipients,&rc};MissionTagExpirationServices s{g0,g1,rv,map,v};
    refused=false;try{broadcastMissionTagExpiration(tag,1,s);}catch(const std::invalid_argument&){refused=true;}require(refused);
    s.abstractType=[](auto&){return true;};refused=false;try{broadcastMissionTagExpiration(tag,1,s);}catch(const std::invalid_argument&){refused=true;}require(refused);
    s.abstractType=[](auto&){return false;};g1=&tag;refused=false;try{broadcastMissionTagExpiration(tag,1,s);}catch(const std::invalid_argument&){refused=true;}require(refused&&!g1);
    s.clearMapSelection=[]{};rc=1;refused=false;try{broadcastMissionTagExpiration(tag,1,s);}catch(const std::invalid_argument&){refused=true;}require(refused);
    bool fault=false;s.abstractType=[&](auto&)->bool{fault=true;throw std::runtime_error("supplied fault");};
    try{broadcastMissionTagExpiration(tag,1,s);}catch(const std::runtime_error&){}require(fault);
    std::cout<<"guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);char op;require(bool(in>>op)&&op=='X');run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
