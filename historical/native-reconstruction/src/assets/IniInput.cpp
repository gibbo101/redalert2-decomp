// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/IniInput.hpp"
#include <algorithm>
#include <bit>
namespace ra2 {
namespace {
std::int32_t add(std::int32_t a,std::int32_t b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}
void emit(const IniInputServices& s,std::int64_t off,std::int32_t v){if(s.store)s.store(off,v);}
}
std::int32_t readIniSource(const void* source,std::span<std::uint8_t> out,std::int32_t count,const IniInputServices& s){
    if(!source)return 0;
    if(!s.sourceRead)throw std::invalid_argument("INI byte source unbound");
    return s.sourceRead(source,out,count);
}
std::int32_t readBufferedIniInput(IniBufferedInput& w,std::span<std::uint8_t> out,std::int32_t requested,const IniInputServices& s){
    if(!w.bufferC.data()||!out.data()||requested<=0)return 0;
    std::int32_t remaining=requested,total=0;
    while(true){
        const auto available=w.available1C;
        if(available>0){
            const auto copied=std::min(available,remaining);
            if(w.cursor18<0||std::uint64_t(std::uint32_t(w.cursor18))+std::uint32_t(copied)>w.bufferC.size()||std::uint64_t(std::uint32_t(total))+std::uint32_t(copied)>out.size())
                throw std::invalid_argument("INI buffered copy exceeds supplied backing");
            if(!s.copy)throw std::invalid_argument("INI memcpy child unbound");
            s.copy(out.subspan(std::uint32_t(total),std::uint32_t(copied)),w.bufferC.subspan(std::uint32_t(w.cursor18),std::uint32_t(copied)));
            // Both fields are read after the child, before either selected store.
            const auto cursor=add(w.cursor18,copied),left=add(w.available1C,-copied);
            total=add(total,copied);remaining-=copied;
            w.cursor18=cursor;emit(s,0x18,cursor);
            w.available1C=left;emit(s,0x1c,left);
        }
        if(!remaining)return total;
        const auto size=w.size10;const auto buffer=w.bufferC;
        const auto got=readIniSource(w.source4,buffer,size,s);
        w.available1C=got;emit(s,0x1c,got);
        w.cursor18=0;emit(s,0x18,0);
        if(!got)return total;
        // A negative nonzero return retries just as the original does. No new
        // arithmetic model or error clamp is imposed on the supplied source.
    }
}
std::int32_t readIniInputLine(std::span<std::uint8_t> out,std::int32_t capacity,std::uint8_t* eof,const IniLineServices& s){
    if(!capacity||!out.data())return 0;
    if(!s.readByte)throw std::invalid_argument("INI line byte reader unbound");
    std::uint32_t stored=0;
    const auto put=[&](std::uint32_t index,std::uint8_t value){
        if(index>=out.size())throw std::invalid_argument("INI line write exceeds supplied backing");
        out[index]=value;if(s.store)s.store(false,index,value);
    };
    std::uint8_t byte=0;
    while(true){
        const auto result=s.readByte(byte);
        if(result!=1){
            if(!eof)throw std::invalid_argument("Original INI EOF null store refused");
            *eof=1;if(s.store)s.store(true,0,1);
            put(stored,0);break;
        }
        if(byte==10)break;
        if(byte!=13&&std::bit_cast<std::int32_t>(stored+1)<capacity)put(stored++,byte);
    }
    put(stored,0);
    const auto end=std::find(out.begin(),out.end(),0);
    if(end==out.end())throw std::invalid_argument("INI line lost its terminator");
    return std::int32_t(end-out.begin());
}
}
