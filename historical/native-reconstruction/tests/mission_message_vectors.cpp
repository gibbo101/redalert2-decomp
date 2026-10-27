// SPDX-License-Identifier: GPL-3.0-or-later
#include "platform/MissionMessagePresentation.hpp"
#include "sim/StringLookup.hpp"
#include "sim/MessageColor.hpp"
#include "assets/PreparedData.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
void require(bool v){if(!v)throw std::invalid_argument("Mission message fixture outside domain");}
template<class T>T take(std::istream& s){T v{};require(bool(s>>v));return v;}
std::string decode(const std::string& text){if(text=="-")return {};require(text.size()%2==0);std::string out;for(std::size_t i=0;i<text.size();i+=2){std::size_t n=0;auto v=std::stoul(text.substr(i,2),&n,16);require(n==2);out+=char(v);}return out;}
std::string snapshot(const OwnedMessagePresentation& o){
    const auto& l=o.list();const auto& g=o.globals();const auto& f=o.font();std::vector<const MessageNode*> nodes;
    for(auto* p=l.head;p;p=p->next){require(nodes.size()<256);nodes.push_back(p);}
    const auto id=[&](const MessageNode* p){if(!p)return 0u;for(unsigned i=0;i<nodes.size();++i)if(nodes[i]==p)return i+1;throw std::invalid_argument("Foreign live message identity");};
    std::ostringstream s;s<<"H "<<nodes.size()<<" U";for(auto v:l.available)s<<' '<<v;
    Bytes slots;for(const auto& slot:l.text)for(auto v:slot){slots.push_back(std::uint8_t(v));slots.push_back(std::uint8_t(v>>8));}s<<" B "<<assetSha256(Data(slots))<<" G";for(auto* p:g.focused)s<<' '<<id(p);
    for(auto* p:nodes)s<<" O "<<id(p->next)<<' '<<id(p->previous)<<' '<<p->x<<' '<<p->y<<' '<<p->width<<' '<<p->height<<' '<<unsigned(p->dirty)<<' '<<unsigned(p->sticky)<<' '<<unsigned(p->field1e)<<' '<<unsigned(p->padding1f)<<' '<<p->gadgetFlags<<' '<<p->expires<<' '<<p->identifier<<' '<<p->flags<<' '<<p->slot<<' '<<p->color<<' '<<p->maximumWidth<<' '<<p->field3c<<' '<<unsigned(p->field40)<<' '<<unsigned(p->field41)<<' '<<p->padding42<<' '<<p->field44<<' '<<p->field48;
    s<<" L "<<l.x<<' '<<l.y<<' '<<l.width<<' '<<l.lineStep<<' '<<l.maximumLines<<' '<<unsigned(l.reserved19)<<' '<<unsigned(l.reserved1a)<<' '<<g.mode<<' '<<unsigned(g.mode3Enabled)<<' '<<unsigned(g.mode4Enabled)<<' '<<g.clockStart<<' '<<g.clockAccumulated<<' '<<g.sound;
    s<<" S "<<f.color<<' '<<f.pitch<<' '<<f.origin<<' '<<!f.surface.empty();for(auto v:f.clip)s<<' '<<v;s<<' '<<f.clipping;
    Bytes pixels;for(auto v:o.pixels()){pixels.push_back(std::uint8_t(v));pixels.push_back(std::uint8_t(v>>8));}s<<" P "<<assetSha256(Data(pixels));
    for(const auto& r:o.sounds())s<<" A "<<r.sound<<' '<<r.flags<<' '<<std::bit_cast<std::uint32_t>(r.volume)<<' '<<r.extra;
    for(const auto& r:o.fills())s<<" B "<<r.box.x<<' '<<r.box.y<<' '<<r.box.width<<' '<<r.box.height<<' '<<r.value;
    require(o.lines().empty());const auto text=s.str();return assetSha256(Data(Bytes(text.begin(),text.end())));
}
void run(std::istream& s,std::shared_ptr<const GameFont> font){
    require(take<char>(s)=='W');MessagePresentationConfig c;c.surfaceWidth=32;c.surfaceHeight=24;c.x=1;c.y=1;c.lineStep=5;
    c.maximumLines=take<std::int32_t>(s);c.width=take<std::int32_t>(s);c.mode=take<std::int32_t>(s);c.mode3=take<unsigned>(s);c.mode4=take<unsigned>(s);c.clockStart=take<std::uint32_t>(s);c.clockAccumulated=take<std::uint32_t>(s);auto ms=take<std::uint32_t>(s);
    c.insertSound=-7;c.drawSound=-9;c.colors={{0,255,255},{137,211,239}};c.packing={{11,3,0,3,5,2},{255,255,255}};
#ifdef RA2_MESSAGE_SOFTWARE_FILL
    c.fillPolicy=MessageFillPolicy::softwareDisplay;
#endif
    MessageColorTable table;for(auto& v:table){auto n=take<int>(s);require(n>=-128&&n<=127);v=std::int8_t(n);}
    auto n=take<unsigned>(s);require(n<=16);std::vector<std::string> keys,payloads;std::vector<StringLookupLabel> labels;std::vector<std::uint32_t> words;keys.reserve(n);payloads.reserve(n);
    for(unsigned i=0;i<n;++i){keys.push_back(decode(take<std::string>(s)));auto index=take<unsigned>(s);require(index<n);labels.push_back({keys.back(),index});payloads.push_back(decode(take<std::string>(s)));words.push_back(i);}
    OwnedMessagePresentation owner(std::move(font),c);owner.setMilliseconds(ms);std::vector<std::uint16_t> pixels(768);for(unsigned i=0;i<768;++i)pixels[i]=std::uint16_t(i*29+0x1234);owner.replacePixels(pixels);
    const auto actions=take<unsigned>(s);require(actions<=64);std::cout<<"R "<<actions;
    for(unsigned i=0;i<actions;++i){const auto op=take<char>(s);unsigned result=0;
        if(op=='M'){
            const auto alternate=take<unsigned>(s);require(alternate<=255);const auto bits=take<std::uint64_t>(s);const auto key=decode(take<std::string>(s));
            MissionTextServices services;services.color=[&](auto selector){return messageColor(selector,table);};
            services.localize=[&](std::string_view query)->std::string_view{auto index=lookupString(query,nullptr,{true,labels,n,words,{},0});return payloads.at(index);};
            services.display=[&](const auto& request){insertMissionMessage(owner,request);};
            result=executeMissionTextAction(key,std::uint8_t(alternate),std::bit_cast<double>(bits),services);
        }else if(op=='D')owner.draw();else if(op=='E')result=owner.expire();else if(op=='T')owner.setMilliseconds(take<std::uint32_t>(s));else throw std::invalid_argument("Unknown mission message operation");
        std::cout<<' '<<result<<' '<<snapshot(owner);
    }
    std::string tail;require(!(s>>tail));std::cout<<'\n';
}
void guards(){
    require(missionMessageUtf16("a\xc3\xa9\xf0\x9f\x98\x80")==u"a\u00e9\U0001f600");
    for(const auto text:{std::string("\xc0\x80"),std::string("\xed\xa0\x80"),std::string("\xf4\x90\x80\x80"),std::string("\xe2\x82"),std::string("\x80")}){bool refused=false;try{missionMessageUtf16(text);}catch(const std::invalid_argument&){refused=true;}require(refused);}
    require(missionMessageUtf16(std::string("a\0b",3)).size()==3);
    std::cout<<"mission message guards PASS\n";
}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==2);auto font=std::make_shared<const GameFont>(readFile(argv[1]));std::string line;while(std::getline(std::cin,line)){std::istringstream s(line);run(s,font);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
