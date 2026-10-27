// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MovementData.hpp"
#include "assets/PreparedData.hpp"
#include <bit>

namespace ra2 {
DirectionData readDirectionData(const Data& data,std::string_view expectedSource) {
    validatePreparedData(data,16464,"26cad37f9cab1e7fe290113a2c9322968637489a9c2aad65aa0150ae548f29e6",
        "41d862df192849730d7ccec27f31cd8fe344ec6ade4f15ef7324a4e9243cd38a",expectedSource);
    DirectionData direction;
    for(std::size_t i=0;i<direction.atan.size();++i) direction.atan[i]=data.f32(40+i*4);
    constexpr std::size_t fields=40+4097*4;
    direction.slopeStep=data.f32(fields);
    direction.positiveHalfPi=data.f32(fields+4);
    direction.negativeHalfPi=data.f32(fields+8);
    auto number=[&](std::size_t p) {return std::bit_cast<double>(std::uint64_t(data.u32(p))|(std::uint64_t(data.u32(p+4))<<32));};
    direction.pi=number(fields+12);direction.halfPi=number(fields+20);direction.angleScale=number(fields+28);
    return direction;
}
std::shared_ptr<const DriveData> readDriveData(const Data& exe,const Data& directionData) {
    const auto source=verifiedEngineDataSource(exe);
    const bool patched=source==PatchedEngineSha;
    const std::uint32_t transitions=patched?0x7a0180:0x78b188,descriptors=patched?0x7a00a0:0x78b0a8,
                        stopAddress=patched?0x79ea48:0x789a50;
    const auto pe=exe.u32(0x3c);
    const auto sections=exe.u16(pe+6),optional=exe.u16(pe+20);
    if(exe.u32(pe)!=0x4550||exe.u16(pe+4)!=0x14c||exe.u32(pe+52)!=0x400000)
        throw std::runtime_error("Unexpected PE layout");
    auto at=[&](std::uint32_t va,std::size_t bytes) {
        const auto rva=va-0x400000;
        for(unsigned i=0;i<sections;++i) {
            const auto p=pe+24+optional+40*i;
            const auto start=exe.u32(p+12),rawSize=exe.u32(p+16),offset=exe.u32(p+20);
            if(rva>=start && rva-start<=rawSize && bytes<=rawSize-(rva-start))
                return exe.slice(offset+rva-start,bytes);
        }
        throw std::runtime_error("Drive table outside PE section");
    };
    auto data=std::make_shared<DriveData>();
    for(int d=0;d<64;++d) {
        const auto entry=at(transitions+12*d,12);
        data->transitions[d]={entry.u8(0),entry.i32(8),entry.i32(4),entry.u8(1)};
        if(entry.u8(0)>6||entry.u8(1)>10||(entry.i32(8)&~15)||entry.i32(4)<0||entry.i32(4)>255)
            throw std::runtime_error("Unexpected ordinary drive descriptor");
    }
    for(int t=0;t<6;++t) {
        const auto descriptor=at(descriptors+16*(t+1),16);
        const auto address=descriptor.u32(0);
        auto& track=data->tracks[t];
        track.jumpIndex=descriptor.i32(4);track.entryIndex=descriptor.i32(8);track.cellIndex=descriptor.i32(12);
        for(unsigned i=0;i<128;++i) {
            const auto entry=at(address+12*i,12);
            const TrackPoint point{entry.i32(0),entry.i32(4),entry.i32(8)};
            data->tracks[t].points.push_back(point);
            if(i>0&&point.x==0&&point.y==0) break;
            if(i==127) throw std::runtime_error("Unterminated original drive track");
        }
    }
    for(const auto& track:data->tracks) {
        const int count=int(track.points.size());
        if(track.jumpIndex<-1||track.jumpIndex>=count||track.entryIndex<0||track.entryIndex>=count||track.cellIndex<-1||track.cellIndex>=count)
            throw std::runtime_error("Invalid original drive transition indices");
    }
    const auto stop=at(stopAddress,8);
    data->stopScale=std::bit_cast<double>(std::uint64_t(stop.u32(0))|(std::uint64_t(stop.u32(4))<<32));
    if(directionData.storage) data->directionsToTargets=readDirectionData(directionData,source);
    return data;
}
}
