// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/TeamObserverInputs.hpp"
#include "assets/UnitModelInputs.hpp"
#include <algorithm>
#include <bit>
#include <cmath>
namespace ra2 {
namespace {
template<class F> const F& child(const F& f){if(!f)throw std::invalid_argument("Observer input child unbound");return f;}
std::string_view text(std::span<const std::uint8_t> b){auto end=std::find(b.begin(),b.end(),0);if(end==b.end())throw std::invalid_argument("Observer text lacks terminator");return {reinterpret_cast<const char*>(b.data()),std::size_t(end-b.begin())};}
std::string identifier(std::string_view token){
    // Original24-byte strncpy overwrites byte23 with NUL, then6EEF10. Reuse
    // byte-copy/trim kernel, including its live old-first-nonblank guard.
    std::array<std::uint8_t,24> bytes{};readIniStringBuffer(bytes,24,token,std::nullopt);return std::string(text(bytes));
}
class CommaTokens {
    std::span<std::uint8_t> buffer;std::size_t cursor=0,last=0;
public:
    explicit CommaTokens(std::span<std::uint8_t> v):buffer(v){}
    std::uint8_t byte(std::size_t i)const{if(i>=buffer.size())throw std::invalid_argument("Observer token read exceeds supplied scratch");return buffer[i];}
    std::size_t lastPosition()const{return last;}
    std::optional<std::string_view> next(){
        while(byte(cursor)==',')++cursor;
        if(!byte(cursor))return {};
        const auto first=cursor;while(byte(cursor)&&byte(cursor)!=',')++cursor;
        const auto size=cursor-first;
        if(byte(cursor)==','){buffer[cursor]=0;++cursor;}
        last=first;
        return std::string_view(reinterpret_cast<const char*>(buffer.data()+first),size);
    }
};
std::uint32_t ftolLow(double value){
    // Actual77F110 signed64 indefinite has low0. Its caller zero-extends EAX
    // before FILD64, so -1 becomes4294967295 rather than a negative double.
    if(!std::isfinite(value)||value<-0x1p63||value>=0x1p63)return 0;
    return std::uint32_t(std::int64_t(value));
}
}
bool loadTeamObserverInputs(TeamObserverType& r,const TeamObserverInputServices& s){
    const auto value=child(s.value)(text(r.identifier24));
    std::array<std::uint8_t,512> buffer{};
    if(!readIniStringBuffer(buffer,512,value?std::optional<std::string_view>(*value):std::nullopt,std::string_view{}))return false;
    CommaTokens tokens(buffer);
    const auto put=[&](std::int64_t off,std::uint32_t n,std::uint64_t bits=0,const void* pointer=nullptr){if(s.store)s.store(&r,off,n,bits,pointer);};
    const auto pointer=[&](const void*& field,std::int64_t off,const void* p){field=p;put(off,4,0,p);};
    const auto boolean=[&](unsigned index,std::string_view token){r.flagsD0[index]=child(s.integer)(token)!=0;put(0xd0+index,1,r.flagsD0[index]);};
    auto token=tokens.next();if(!token)return false;
    std::array<std::uint8_t,49> display{};
    const auto size=std::min<std::size_t>(48,token->size());std::copy_n(token->begin(),size,display.begin());
    for(unsigned i=0;i<12;++i){std::uint32_t word=0;for(unsigned j=0;j<4;++j){r.name64[4*i+j]=display[4*i+j];word|=std::uint32_t(display[4*i+j])<<(8*j);}put(0x64+4*i,4,word);}
    r.name64[48]=0;put(0x94,1);
    token=tokens.next();if(!token)return false;
    auto name=identifier(*token);pointer(r.teamDC,0xdc,nullptr);
    if(child(s.compare)(name,"<none>"))pointer(r.teamDC,0xdc,child(s.teamType)(name));
    token=tokens.next();if(!token)return false;
    name=identifier(*token);r.valueA0=0;put(0xa0,4);r.valueA8=-1;put(0xa8,4,0xffffffffu);
    if(!child(s.compare)(name,"<all>")){r.valueA0=2;put(0xa0,4,2);}
    else if(child(s.compare)(name,"<none>")){
        r.valueA8=child(s.countryIndex)(name);put(0xa8,4,std::uint32_t(r.valueA8));
        if(r.valueA8!=-1){r.valueA0=1;put(0xa0,4,1);}
    }
    if(!tokens.next())return false; // required, but discarded, tech-level token
    r.valueB0=0;put(0xb0,4);
    token=tokens.next();if(!token)return false;
    r.condition98=child(s.integer)(*token);put(0x98,4,std::uint32_t(r.condition98));
    token=tokens.next();if(!token)return false;
    name=identifier(*token);const void* object=nullptr;
    for(unsigned kind=0;kind<4;++kind){
        const auto index=child(s.objectIndex[kind])(name);
        if(index==-1)continue;
        const auto slots=child(s.objectSlots[kind])();
        if(index<0||std::size_t(index)>=slots.size())throw std::invalid_argument("Observer object index outside backing");
        object=slots[std::size_t(index)];break;
    }
    pointer(r.objectD8,0xd8,object);
    token=tokens.next();if(!token)return false;
    std::size_t cursor=tokens.lastPosition();unsigned index=0;
    while(tokens.byte(cursor)){
        // The original scans the mutable strtok backing. A whitespace suffix
        // can advance to the token NUL, consume the following field's first
        // byte as the pair's second byte, then continue into later raw fields.
        if(child(s.space)(std::bit_cast<std::int8_t>(tokens.byte(cursor)))){
            do{++cursor;}while(child(s.space)(std::bit_cast<std::int8_t>(tokens.byte(cursor))));
        }
        const auto first=tokens.byte(cursor),second=tokens.byte(cursor+1);++cursor;
        if(second)++cursor;
        if(index>=32)break; // the33rd pair is scanned before this check
        const std::array<char,2> pair{char(first),char(second)};
        const auto size=first?(second?2u:1u):0u;
        const auto byte=std::uint8_t(child(s.hexPair)(std::string_view(pair.data(),size)));
        auto& word=r.conditionsE4[index/4];const unsigned shift=8*(index%4);
        word=(word&~(0xffu<<shift))|(std::uint32_t(byte)<<shift);put(0xe4+index,1,byte);++index;
    }
    for(auto [field,off]:{std::pair{&r.weightB8,0xb8},std::pair{&r.minimumC0,0xc0},std::pair{&r.maximumC8,0xc8}}){
        token=tokens.next();if(token){*field=double(ftolLow(child(s.number)(*token)));put(off,8,std::bit_cast<std::uint64_t>(*field));}
    }
    token=tokens.next();if(token)boolean(0,*token);
    tokens.next(); // required position is intentionally ignored even if present
    token=tokens.next();if(token){r.valueAC=std::uint32_t(child(s.integer)(*token));put(0xac,4,r.valueAC);}
    token=tokens.next();if(token)boolean(1,*token);
    token=tokens.next();if(token){name=identifier(*token);pointer(r.teamE0,0xe0,nullptr);if(child(s.compare)(name,"<none>"))pointer(r.teamE0,0xe0,child(s.teamType)(name));}
    for(unsigned i=2;i<5;++i){token=tokens.next();if(token)boolean(i,*token);}
    const auto adjust=[&](const void* const& team){
        if(!team)return;
        const auto saved=std::bit_cast<std::int32_t>(r.valueB0);
        const auto first=child(s.taskForceTech)(team);
        const auto result=saved>first?saved:child(s.taskForceTech)(team);
        r.valueB0=std::uint32_t(result);put(0xb0,4,r.valueB0);
    };
    adjust(r.teamDC);adjust(r.teamE0);return true;
}
}
