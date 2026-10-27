// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Bytes.hpp"
#include "assets/OverlayTypeInputs.hpp"
#include <algorithm>
#include <array>
#include <optional>

namespace ra2 {
// Complete5D7BD0 in the base three-theater domain. -1 is an unconditional no-op.
// The original reads two bytes; short host strings refuse before mutation.
inline void applyObjectNewTheater(std::string& name,int theater){
    if(theater==-1)return;
    if(name.size()<2)throw std::invalid_argument("NewTheater filename shorter than two bytes");
    const auto asciiLower=[](unsigned char c){return c>='A'&&c<='Z'?unsigned(c+32):unsigned(c);};
    const auto first=asciiLower(name[0]),second=asciiLower(name[1]);
    if((first!='g'&&first!='n'&&first!='c')||(second!='a'&&second!='t'))return;
    if(theater<0||theater>2)throw std::invalid_argument("Unsupported base image theater");
    constexpr std::array<char,3> letters{'T','A','U'};name[1]=letters[std::size_t(theater)];
}
struct OverlayImageResult {std::uint32_t handle=0;std::optional<Data> data;};
struct OverlayImageServices {
    std::function<OverlayImageResult(const std::string&)> load;
    // Native file/cache lifetime services, after the image/owned stores. These
    // replace original temporary file-object storage, not game code execution.
    std::function<void()> finish;
    std::function<void(unsigned,unsigned,std::uint32_t)> store;
};
struct OverlayStartupServices {
    std::function<void(std::uint32_t)> release;
    std::function<OverlayImageResult(const std::string&)> cachedImage;
    std::function<void(unsigned,unsigned,std::uint32_t)> store;
};
// Complete5D7630 policy. Portable cache/release services replace original IO and
// heap storage. Calling this explicitly does not recover the startup schedule.
inline void initializeOverlayImage(OverlayTypeInputs& type,
        std::optional<Data>& resident,std::uint8_t& owned,int theater,
        const OverlayStartupServices& services){
    if(bool(type.image)!=bool(resident))throw std::invalid_argument("Overlay startup handle/data mismatch");
    if(type.imageName.empty()||type.imageName.size()>24||type.imageName.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_")!=std::string::npos)
        throw std::invalid_argument("Overlay startup name outside supported domain");
    if(theater< -1||theater>2||(type.theater&&theater<0))throw std::invalid_argument("Unsupported overlay startup theater");
    if(!services.cachedImage||(owned&&type.image&&!services.release))throw std::invalid_argument("Overlay startup service unbound");
    const auto store=[&](unsigned off,unsigned n,std::uint32_t v){if(services.store)services.store(off,n,v);};
    if(type.alternateArctic&&theater==1&&!owned){
        if(!type.arcticInUse){
            type.imageName=(type.imageName+"A").substr(0,24);
            // Original fixed field copy: six dwords then the terminating byte.
            std::array<std::uint8_t,25> bytes{};std::copy(type.imageName.begin(),type.imageName.end(),bytes.begin());
            for(unsigned i=0;i<24;i+=4)store(0x1c8+i,4,std::uint32_t(bytes[i])|(std::uint32_t(bytes[i+1])<<8)|(std::uint32_t(bytes[i+2])<<16)|(std::uint32_t(bytes[i+3])<<24));
            store(0x1e0,1,0);type.arcticInUse=1;store(0x1e2,1,1);
        }
    }else{type.arcticInUse=0;store(0x1e2,1,0);}
    std::string filename=type.imageName+".SHP";
    if(type.theater){constexpr std::array<const char*,3> extensions{"TEM","SNO","URB"};filename=type.imageName+"."+extensions[std::size_t(theater)];}
    else if(type.newTheater)applyObjectNewTheater(filename,theater);
    if(owned&&type.image)services.release(type.image);
    type.image=0;resident.reset();store(0xa4,4,0);owned=0;store(0xa8,1,0);
    auto result=services.cachedImage(filename);
    if(bool(result.handle)!=bool(result.data))throw std::invalid_argument("Overlay startup cache handle/data mismatch");
    type.image=result.handle;resident=std::move(result.data);store(0xa4,4,type.image);
    if(resident){
        const auto width=std::bit_cast<std::int16_t>(resident->u16(2)),height=std::bit_cast<std::int16_t>(resident->u16(4));
        type.imageMaximum=std::max(8,std::max(int(width),int(height)));store(0x1bc,4,std::uint32_t(type.imageMaximum));
    }
}
// Complete5DD150 policy, supported image names/base theaters and known filename
// branches. Original neither-Theater-nor-NewTheater demand paths use an
// uninitialized stack filename and are refused. Construction/file/cache/heap
// services remain explicit; Data uses immutable portable file bytes.
inline OverlayImageResult ensureOverlayImage(OverlayTypeInputs& type,
        std::optional<Data>& resident,std::uint8_t& owned,const int& theater,
        const OverlayImageServices& services){
    if(bool(type.image)!=bool(resident))throw std::invalid_argument("Overlay image binding differs from type handle");
    if(type.image||!type.demandLoad)return {type.image,resident};
    if(type.imageName.empty()||type.imageName.size()>24||type.imageName.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_")!=std::string::npos)
        throw std::invalid_argument("Overlay image filename outside supported domain");
    std::string filename;
    if(type.theater){
        if(theater<0||theater>2)throw std::invalid_argument("Unsupported base image theater");
        constexpr std::array<const char*,3> extensions{"TEM","SNO","URB"};filename=type.imageName+"."+extensions[std::size_t(theater)];
    }else if(type.newTheater){filename=type.imageName+".SHP";applyObjectNewTheater(filename,theater);}
    else throw std::invalid_argument("Uninitialized original overlay demand filename");
    if(!services.load||!services.finish)throw std::invalid_argument("Overlay image loader/lifetime service unbound");
    auto result=services.load(filename);
    if(bool(result.handle)!=bool(result.data))throw std::invalid_argument("Overlay loader returned inconsistent handle/data");
    type.image=result.handle;resident=result.data;
    if(services.store)services.store(0xa4,4,type.image);
    if(result.handle){owned=1;if(services.store)services.store(0xa8,1,1);}
    services.finish();return result;
}
}
