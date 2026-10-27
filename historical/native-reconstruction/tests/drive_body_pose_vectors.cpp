// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/DriveBodyPose.hpp"
#include "render/RampGeometry.hpp"
#include "render/VoxelRampShadow.hpp"
#include "assets/Archive.hpp"
#include "assets/MovementData.hpp"
#include "assets/PreparedData.hpp"
#include <bit>
#include <cfenv>
#include <iostream>
#include <sstream>
using namespace ra2;
int main(int argc,char** argv){try{
    if(argc==2&&std::string_view(argv[1])=="--guards"){
        RasterData raster{};RampPoseData data{};std::array<Matrix,21> matrices{};
        std::array<RampQuaternion,21> quaternions{};DriveBodyInputs input{};int key=17;
        int refused=0;
        const auto check=[&]{
            try{driveBodyPose(raster,data,matrices,quaternions,input,[]{return std::uint16_t(0);},&key);}
            catch(const std::invalid_argument&){++refused;return;}
            throw std::runtime_error("Drive body accepted unsupported domain");
        };
        input.ramp.current=21;check();input.ramp.current=0;
        input.ramp.previous=-1;check();input.ramp.previous=0;
        input.rockingX=std::bit_cast<float>(0x7fc00000u);check();input.rockingX=0;
        input.rockingY=2;check();input.rockingY=0;
        input.type330=1e7;check();input.type330=0;
        input.type338=std::bit_cast<double>(0x7ff0000000000000ull);check();
        if(refused!=6||key!=17)throw std::runtime_error("Drive body guard changed key");
        try{readRampPoseData(Data(Bytes(16456)),PatchedEngineSha);}
        catch(const std::exception&){std::cout<<"Drive body domain and prepared data guards: PASS\n";return 0;}
        throw std::runtime_error("RampPose reader accepted fabricated data");
    }
    if(argc!=6)throw std::invalid_argument("Body vectors require geometry/render/raster/direction/pose data");
    const auto geometry=readRampGeometryData(readFile(argv[1]),PatchedEngineSha);
    const auto render=readRenderData(readFile(argv[2]),PatchedEngineSha);
    const auto raster=readRasterData(readFile(argv[3]),PatchedEngineSha);
    const auto direction=readDirectionData(readFile(argv[4]),PatchedEngineSha);
    const auto data=readRampPoseData(readFile(argv[5]),PatchedEngineSha);
    const auto g=stockRampGeometry(render,raster,direction,geometry);
    const auto matrices=voxelRampShadowMatrices(raster,g.axisTilt,g.diagonalTilt);
    const auto quaternions=voxelRampQuaternions(raster,render,g.axisTilt,g.diagonalTilt);
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char cmd=0;in>>cmd;
        const auto event=[&](auto... args){((std::cout<<args<<' '),...);};
        if(cmd=='Q'){
            int mode=-1;in>>mode;in>>std::ws;if(!in.eof()||mode<0||mode>3)throw std::invalid_argument("Bad quaternion fixture");
            const int modes[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};std::fesetround(modes[mode]);
            for(const auto& q:voxelRampQuaternions(raster,render,g.axisTilt,g.diagonalTilt))for(float v:q)event(std::bit_cast<std::uint32_t>(v));
            if(std::fegetround()!=modes[mode])throw std::runtime_error("Quaternion leaked FP mode");std::fesetround(FE_TONEAREST);std::cout<<'\n';continue;
        }
        int operation=0,nextRamp=0,current=0,previous=0,start=0,remaining=0,duration=0,tick=0,
            desired=0,from=0,fstart=0,fduration=0,rate=0,present=0,key=0,mode=0;
        std::uint32_t rx=0,ry=0;std::uint64_t dx=0,dy=0;
        in>>operation>>nextRamp>>current>>previous>>start>>remaining>>duration>>tick>>rx>>ry>>dx>>dy>>desired>>from>>fstart>>fduration>>rate>>present>>key>>mode;
        if(!in||cmd!='B'||operation<0||operation>2||nextRamp<0||nextRamp>20||current<0||current>20||previous<0||previous>20||
           desired<0||desired>65535||from<0||from>65535||rate<0||rate>65535||present<0||present>1||mode<0||mode>3)throw std::invalid_argument("Bad body state fixture");
        in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing body fixture");
        const int modes[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};std::fesetround(modes[mode]);
        DriveRampState state{current,previous,start,0,remaining,duration};
        const auto cell=[&]{event('C');event('C');return std::uint8_t(nextRamp);};
        if(operation==1)unlimboDriveRamp(state,cell,tick,0);
        if(operation==2)observeDriveRamp(state,cell,tick,0);
        Facing facing;facing.desired=std::uint16_t(desired);facing.start=std::uint16_t(from);facing.timerStart=fstart;facing.duration=fduration;facing.rate=std::uint16_t(rate);
        const auto getFacing=[&]{event('F');return facing.current(tick);};
        DriveBodyInputs inputs{state,tick,std::bit_cast<float>(rx),std::bit_cast<float>(ry),std::bit_cast<double>(dx),std::bit_cast<double>(dy)};
        const auto pose=driveBodyPose(raster,data,matrices,quaternions,inputs,getFacing,present?&key:nullptr,
            [&]{event('T');},[&](int v){event('K',std::uint32_t(v));});
        event('S',state.current,state.previous,state.start,state.remaining,state.duration);
        for(float v:pose)event(std::bit_cast<std::uint32_t>(v));event(std::uint32_t(key));
        if(std::fegetround()!=modes[mode])throw std::runtime_error("Body leaked FP mode");std::fesetround(FE_TONEAREST);std::cout<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
