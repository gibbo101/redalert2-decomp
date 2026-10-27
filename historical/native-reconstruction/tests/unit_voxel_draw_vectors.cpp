// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitVoxelDraw.hpp"
#include "assets/Archive.hpp"
#include <bit>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
void rect(PixelRect r){std::cout<<r.x<<' '<<r.y<<' '<<r.width<<' '<<r.height<<' ';}
void matrix(const Matrix& m){for(auto v:m)std::cout<<std::bit_cast<std::uint32_t>(v)<<' ';}
int model(UnitVoxelPart p){return p==UnitVoxelPart::Body?0xb0:p==UnitVoxelPart::Turret?0xb8:0xc0;}
int cache(UnitVoxelPart p){return p==UnitVoxelPart::Body?0x214:p==UnitVoxelPart::Turret?0x228:0x250;}
}
int main(int argc,char** argv){try {
    if(argc!=2)return 2;
    const auto data=readRasterData(readFile(argv[1]));std::string line;
    while(std::getline(std::cin,line)){
        std::istringstream input(line);char op;UnitVoxelDrawInputs in;unsigned body,turret,gate;
        int warm,barrel,result,predicate,camera;Coord coords;
        input>>op>>body>>turret>>in.animationFrame>>in.bodyFrames>>gate>>warm>>barrel
             >>in.point.x>>in.point.y>>in.clip.x>>in.clip.y>>in.clip.width>>in.clip.height
             >>in.brightness>>result>>predicate>>camera>>coords.x>>coords.y>>coords.z;
        unsigned pitch=16384;
        if(op=='B')input>>pitch;
        if(!input||(op!='V'&&op!='B'))throw std::runtime_error("Incomplete Unit voxel command");
        input>>std::ws;if(!input.eof())throw std::runtime_error("Trailing Unit voxel input");
        const int warmMask=op=='V'?(warm?3:0):warm;
        if(warmMask<0||warmMask>3)throw std::runtime_error("Invalid part cache mask");
        in.bodyHeading=std::uint16_t(body);in.turretHeading=std::uint16_t(turret);in.keyGate=std::uint8_t(gate);
        in.barrelHeading=std::uint16_t(pitch);
        in.barrelModel=barrel!=0;in.turretCacheHasEntries=(warmMask&1)!=0;
        if(camera)in.camera={0.5f,0.25f,-0.5f,0.125f,-0.25f,0.5f,0.25f,-0.25f,0.25f,-0.5f,0.5f,0.5f};
        in.emptyDirty={9,11,13,15};UnitVoxelDrawState state;state.dirty={-7,-9,-11,-13};int count=0;
        UnitVoxelDrawServices s;
        s.originalTypeVisible=[]{std::cout<<"visible ";};s.stagingBounds=[]{std::cout<<"bounds ";return PixelRect{0,0,256,256};};
        s.bodyPose=[]{std::cout<<"body_pose ";};s.multipleTurretQuery=[]{std::cout<<"multi ";};
        s.cachedImage=[&](auto p,int key){std::cout<<"cache "<<cache(p)<<' '<<key<<' ';return (warmMask&(p==UnitVoxelPart::Turret?1:2))!=0;};
        s.drawOffset=[]{std::cout<<"offset ";return driveLitDrawOffset();};
        s.lit=[&](const FootLitRequest& r){
            std::cout<<"lit "<<model(UnitVoxelPart(r.model))<<' '<<r.frame<<' '<<r.key<<' '<<cache(UnitVoxelPart(r.cache))<<' ';
            rect(r.clip);std::cout<<r.point.x<<' '<<r.point.y<<' '<<r.brightness<<' '<<r.flags<<' ';matrix(r.pose);
            ++count;state.dirty={70,80,2*count,3*count};
        };
        s.finalBrightness=[&](int b){std::cout<<"brightness "<<b<<' ';return result;};
        s.status=[]{std::cout<<"status ";};
        s.finalDraw=[](PixelPoint p,PixelRect r,int b){std::cout<<"final 1 "<<p.x<<' '<<p.y<<' ';rect(r);std::cout<<b<<' ';};
        s.shadowPose=[]{std::cout<<"shadow_pose ";};s.cell=[&]{std::cout<<"cell "<<coords.x<<' '<<coords.y<<' '<<coords.z<<' ';};
        s.height=[]{std::cout<<"height ";};s.predicate=[&]{std::cout<<"predicate ";return std::uint8_t(predicate);};
        s.shadow=[](const UnitVoxelShadowRequest& r){
            std::cout<<"shadow 176 0 "<<r.key<<" 572 ";rect(r.clip);std::cout<<r.point.x<<' '<<r.point.y<<' ';matrix(r.pose);
            std::cout<<"1 "<<int(r.useStagingStencil)<<" 0 0 ";
        };
        s.clearStaging=[](PixelRect r){std::cout<<"fill ";rect(r);};
        drawHealthyUnitVoxel(data,in,state,s,[](char k,int v){
            if(k=='s')std::cout<<"surface "<<v<<' ';
            else if(k=='f')std::cout<<"staging "<<v<<' ';
            else std::cout<<"dirty "<<k-'0'<<' '<<v<<' ';
        });
        if(state.staging||state.stagingSurface)throw std::runtime_error("Unit voxel state not restored");
        std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
