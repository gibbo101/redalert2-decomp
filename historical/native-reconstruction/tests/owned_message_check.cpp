// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/OwnedMessagePresentation.hpp"
#include "render/MessageFrame.hpp"
#include "message_presentation_inspection.hpp"
#include <iostream>
#include <sstream>
#include <type_traits>
#include <source_location>
using namespace ra2;
namespace {
void require(bool v,const std::source_location& where=std::source_location::current()){if(!v)throw std::runtime_error("Owned message check failed at line "+std::to_string(where.line()));}
Data synthetic(std::uint32_t rows=3,std::uint32_t columns=3,bool presentX=true){
    Bytes b(28+131072+33*3);const auto put=[&](std::size_t o,std::uint32_t v){for(unsigned i=0;i<4;++i)b[o+i]=std::uint8_t(v>>(8*i));};
    put(0,0x546e6f66);const std::array<unsigned,6> fields{0,columns,rows,4,3,33};
    for(unsigned i=0;i<6;++i)put(4+i*4,fields[i]);
    for(auto c:{u'a',u'b',u'X',u' ',u':',u'?'}){if(c==u'X'&&!presentX)continue;b[28+unsigned(c)*2]=std::uint8_t(c==u'b'?2:1);}
    for(unsigned n=0;n<3;++n){const auto p=28+131072+n*33;b[p]=5+n;for(unsigned i=1;i<33;++i)b[p+i]=std::uint8_t(0x81+(i*13)%126);}
    return Data(std::move(b));
}
MessagePresentationConfig config(){
    MessagePresentationConfig c;c.surfaceWidth=160;c.surfaceHeight=96;c.x=2;c.y=2;c.width=148;c.maximumLines=3;c.lineStep=16;
    c.mode=1;c.clockStart=0;c.insertSound=-7;c.drawSound=-9;c.colors={{0,0,255},{137,211,239}};
    c.packing={{11,3,0,3,5,2},{255,255,255}};return c;
}
const MessageNode* insert(OwnedMessagePresentation& owner,std::u16string_view text,std::int32_t lifetime=-1,bool silent=false){
    MessageInsertRequest request;request.body=&text;request.lifetime=lifetime;request.color=1;request.silent=silent;return owner.insert(request);
}
// Address-independent observable state: compare independent continuations, not
// a second implementation of the recovered insertion/layout/raster algorithms.
std::string state(const OwnedMessagePresentation& o){
    std::ostringstream s;s<<o.allocatedNodes()<<':'<<o.globals().clockStart<<':'<<o.globals().clockAccumulated;
    for(auto w:o.list().available)s<<','<<w;
    for(const auto& slot:o.list().text)for(auto c:slot)s<<','<<unsigned(c);
    unsigned focus=0,n=0;
    for(auto* p=o.list().head;p;p=p->next){++n;if(p==o.globals().focused[2])focus=n;s<<"N"<<p->slot<<','<<p->x<<','<<p->y<<','<<p->expires<<','<<unsigned(p->dirty)<<','<<p->field44<<','<<p->field48<<','<<p->field3c<<','<<p->gadgetFlags;}
    s<<"F"<<focus;for(auto p:o.pixels())s<<','<<p;
    s<<"G"<<o.font().color<<','<<o.font().pitch<<','<<o.font().origin<<','<<o.font().clipping<<','<<o.font().surface.size();for(auto v:o.font().clip)s<<','<<v;
    s<<"I"<<o.text().compositionLength<<','<<o.text().compositionCursor<<','<<o.text().cursorSuppression;
    for(const auto& r:o.sounds())s<<"A"<<r.sound<<','<<r.flags<<','<<r.volume<<','<<r.extra;
    for(const auto& r:o.fills())s<<"B"<<r.box.x<<','<<r.box.y<<','<<r.box.width<<','<<r.box.height<<','<<r.value;
    for(const auto& r:o.lines())s<<"C"<<r.x<<','<<r.y<<','<<r.bottom<<','<<r.color<<','<<r.alpha;
    return s.str();
}
void run(std::shared_ptr<const GameFont> font,MessageFillPolicy policy){
    static_assert(!std::is_move_constructible_v<OwnedMessagePresentation>);
    auto c=config();c.fillPolicy=policy;
    auto source=std::make_unique<OwnedMessagePresentation>(font,c);
    std::vector<std::uint16_t> backing(160*96,0x1234);source->replacePixels(backing);
    source->setMilliseconds(16);const auto* first=insert(*source,u"ab X",1);require(first);
    {std::u16string temporary=u"X ab";require(insert(*source,temporary,-1));}
    source->focus(first);source->draw();
    require(!source->fills().empty()&&!source->sounds().empty()&&!source->lines().empty());
    require(std::any_of(source->pixels().begin(),source->pixels().end(),[](auto v){return v!=0x1234;}));
    if(policy==MessageFillPolicy::softwareDisplay)require(std::any_of(source->pixels().begin(),source->pixels().end(),[](auto v){return v==0;}));
    const auto saved=state(*source);auto preview=source->clone();
    require(state(*preview)==saved&&preview->pixels().data()!=source->pixels().data());
    require(preview->asset()==source->asset());
    require(preview->globals().selectedFont!=source->globals().selectedFont);
    require(preview->list().head!=source->list().head&&preview->list().head->next!=source->list().head->next);
    require(preview->globals().focused[2]==preview->list().head);
    require(preview->list().head->next->previous==preview->list().head);
    require(preview->font().primary==source->font().primary);
    preview->setMilliseconds(256);require(preview->expire());require(!preview->globals().focused[2]);
    require(insert(*preview,u"later",-1));preview->draw();preview->clearRequests();
    require(state(*source)==saved); // all mutations/drawing/logs stayed in clone
    bool refused=false;try{preview->focus(first);}catch(const std::invalid_argument&){refused=true;}require(refused);
    // Two independently rebound warm clones must outlive both original source
    // and external asset references, then allocate/expire/draw independently.
    auto control=source->clone();auto survivor=source->clone();source.reset();font.reset();
    const auto continueWith=[](OwnedMessagePresentation& p){
        p.clearRequests();p.setMilliseconds(256);require(p.expire());
        for(unsigned i=0;i<24;++i){require(insert(p,u"ab X",-1));p.draw();}
        p.focus(p.list().head);p.draw();
    };
    continueWith(*control);continueWith(*survivor);require(state(*control)==state(*survivor));
    require(control->allocatedNodes()<=4&&survivor->allocatedNodes()<=4);
    auto isolated=survivor->clone();const auto before=state(*survivor);
    isolated->replacePixels(backing);isolated->clearRequests();isolated->focus(nullptr);isolated->setMilliseconds(0xffffffff);isolated->expire();isolated->draw();require(state(*survivor)==before);
    // No retained source callback/pixel/font owner after the surviving clone
    // becomes the only owner. ASan checks accesses in this continuation.
    control.reset();survivor.reset();preview.reset();isolated->draw();require(insert(*isolated,u"X"));isolated->draw();
}
void refusedDrawClone(){
    // Deliberately enter the existing glyph byte-backing refusal after surface binding.
    // The failed clone owns its partial state; no rollback is asserted.
    auto c=config();c.fillPolicy=MessageFillPolicy::softwareDisplay;
    auto p=std::make_unique<OwnedMessagePresentation>(std::make_shared<const GameFont>(synthetic(3,100,false)),c);
    require(insert(*p,u"a",-1,true));bool refused=false;
    try{p->draw();}catch(const std::runtime_error& e){refused=std::string(e.what())=="Truncated or invalid asset range";}require(refused);
    require(p->font().surface.data()==p->pixels().data());
    const auto before=state(*p);auto q=p->clone();require(state(*q)==before);
    require(q->font().surface.data()==q->pixels().data()&&q->font().surface.data()!=p->font().surface.data());
    refused=false;try{q->draw();}catch(const std::runtime_error& e){refused=std::string(e.what())=="Truncated or invalid asset range";}require(refused);
    require(state(*p)==before);p.reset();
    auto r=q->clone();q.reset();refused=false;
    try{r->draw();}catch(const std::runtime_error& e){refused=std::string(e.what())=="Truncated or invalid asset range";}require(refused);
    MessageNode foreign;refused=false;try{r->focus(&foreign);}catch(const std::invalid_argument&){refused=true;}require(refused);
}
void frameCheck(const std::shared_ptr<const GameFont>& font){
    auto c=config();c.fillPolicy=MessageFillPolicy::softwareDisplay;
    auto p=std::make_unique<OwnedMessagePresentation>(font,c);
    const std::vector<std::uint32_t> terrain(160*96,0xff123456);auto frame=terrain;
    require(!composeMessageFrame(*p,frame,160,96,0).pixelStores&&frame==terrain);
    require(insert(*p,u"ab X",1,true));
    const auto drawn=composeMessageFrame(*p,frame,160,96,16); // Strict expiry equality retains.
    require(!drawn.expired&&drawn.glyphStores&&drawn.fillStores&&frame.back()==terrain.back());
    require(std::any_of(frame.begin(),frame.end(),[](auto v){return v==0xff000000;}));
    require(std::any_of(frame.begin(),frame.end(),[](auto v){return v!=0xff000000&&v!=0xff123456;}));
    const auto warm=MessagePresentationInspection::snapshot(*p);auto preview=p->clone();auto discarded=terrain;
    require(composeMessageFrame(*preview,discarded,160,96,32).expired);
    require(discarded==terrain&&MessagePresentationInspection::snapshot(*p)==warm);
    frame=terrain;require(composeMessageFrame(*p,frame,160,96,32).expired&&frame==terrain);
    require(insert(*p,u"X ab",-1,true));p->focus(p->list().head);
    const auto before=MessagePresentationInspection::snapshot(*p);bool refused=false;
    try{composeMessageFrame(*p,frame,160,96,1000);}catch(const std::invalid_argument&){refused=true;}
    require(refused&&MessagePresentationInspection::snapshot(*p)==before&&frame==terrain);p->focus(nullptr);
    // A failed observer must never survive its stack frame or enter a clone.
    bool failed=false;try{p->draw([](char kind,auto,auto){if(kind=='W')throw std::runtime_error("observer failure");});}
    catch(const std::runtime_error& e){failed=std::string(e.what())=="observer failure";}require(failed);
    auto survivor=p->clone();p.reset();frame=terrain;
    require(composeMessageFrame(*survivor,frame,160,96,256).glyphStores&&frame!=terrain);
    const auto valid=MessagePresentationInspection::snapshot(*survivor);refused=false;
    try{composeMessageFrame(*survivor,frame,159,96,1000);}catch(const std::invalid_argument&){refused=true;}
    require(refused&&MessagePresentationInspection::snapshot(*survivor)==valid);
}
}
int main(int argc,char** argv){try{
    require(argc==1||argc==2);auto font=std::make_shared<const GameFont>(argc==2?readFile(argv[1]):synthetic());
    frameCheck(font);run(font,MessageFillPolicy::requestsOnly);run(std::move(font),MessageFillPolicy::softwareDisplay);refusedDrawClone();
    bool refused=false;try{OwnedMessagePresentation bad(nullptr,config());}catch(const std::invalid_argument&){refused=true;}require(refused);
    auto c=config();c.surfaceWidth=0;refused=false;try{OwnedMessagePresentation bad(std::make_shared<const GameFont>(synthetic()),c);}catch(const std::invalid_argument&){refused=true;}require(refused);
    std::cout<<"Owned message warm clone/source destruction/isolation PASS\n";return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
