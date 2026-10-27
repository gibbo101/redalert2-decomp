// SPDX-License-Identifier: GPL-3.0-or-later
#include "platform/OwnedUnitMovePreview.hpp"
#include "owned_world_snapshot.hpp"
#include <iostream>
using namespace ra2;
namespace {
void require(bool v,const char* m){if(!v)throw std::runtime_error(m);}
using owned_check::snapshot;
const OwnedUnitProcessesInputs inputs{5,1,0,0,8,
    std::array<OwnedUnitProcessActorInputs,2>{OwnedUnitProcessActorInputs{{19,-23},31},OwnedUnitProcessActorInputs{{-29,37},-41}}};
struct Fixture {
    std::vector<MapFinalizationCell> cells{1};std::vector<int> slots=std::vector<int>(262144,-1);
    MapCellAttributes fallback;MapFloorHeightState floor;std::array<int,16> land{};std::array<float,11> speeds{};
    ResidentCellInputs resident;Bytes b4=Bytes(64),b10=Bytes(160);
    std::shared_ptr<const DriveData> data=std::make_shared<const DriveData>();
    std::shared_ptr<const int> numeric=std::make_shared<const int>(1);
    int queries=0,stores=0,external=0;
    Fixture(){cells[0].attributes.input.position={1,1};slots[513]=0;resident.landMap=land;resident.wheelSpeeds=speeds;}
    std::unique_ptr<TerrainUnitContext> context(bool parked=true,bool turret=true){
        UnitMapSeed seed{cells,slots,fallback,floor,resident,b4,b10,2,1,104};
        GroundDriveProcessServices supplied;
        supplied.noRoute=[this]{++external;};supplied.advance.notify=[this](int){++external;};supplied.advance.postCell=[this]{++external;};
        supplied.squareRoot=[this](double n){++external;return n;};
        GroundDriveProcessState initial;initial.movement.actor.position={384,384,0};initial.movement.reached5a0=1;
        initial.movement.body.rate=1792;
        auto c=std::make_unique<TerrainUnitContext>(std::make_shared<MutableUnitMap>(seed),supplied,initial,
            [this](int,int){++stores;},[this](char,int,int,std::uint32_t){++stores;},[this](char,Coord){++queries;});
        if(parked){UnitDiscoveryActor d;d.owner=0;d.mission98=2;d.queuedA0=-1;d.queuedA4=255;
            Facing t;t.rate=1792;t.desired=t.start=30000;
            c->bindParked(initial,{},d,[this](int,int){++stores;},turret?std::optional<Facing>(t):std::nullopt);}
        return c;
    }
    OwnedUnitWorldNumerics numerics(){return {numeric,[](double n){return n;}};}
    std::unique_ptr<OwnedUnitWorld> make(){return std::make_unique<OwnedUnitWorld>(context(),data,numerics(),inputs,Facing{});}
};
}
int main(){try{
    Fixture f;auto world=f.make();OwnedUnitSchedule schedule(*world,.30000001192092896);
    OwnedUnitStepInputs in{{15,15},{7,7}};
    OwnedUnitWorldCall call;call.notify=[](int){};call.postCell=[]{ };call.noRoute=[]{ };call.failedRoute=[](int){};
    std::array<OwnedUnitWorldCall,2> calls{call,call};
    const auto initial=snapshot(*world);
    for(int test=0;test<3;++test){auto bad=calls;auto invalid=in;
        if(test==0)bad[1].notify={};if(test==1)invalid.speed[1]=-1;if(test==2)invalid.speed[1]=256;
        bool refused=false;try{schedule.step(101,invalid,bad);}catch(const std::invalid_argument&){refused=true;}
        require(refused&&snapshot(*world)==initial&&f.queries==0&&f.stores==0,"Invalid actor1 inputs entered Process0");
    }
    bool reentry=false,lateFault=false;
    try{schedule.step(101,in,calls,[&](int id,bool){
        if(id!=0)return;
        try{schedule.step(101,in,calls);}catch(const std::logic_error&){reentry=true;}
        throw std::runtime_error("observer fault");
    });}catch(const std::runtime_error& e){lateFault=std::string_view(e.what())=="observer fault";}
    require(reentry&&lateFault,"Schedule reentry/fault boundary missing");
    std::vector<int> order; schedule.step(102,in,calls,[&](int id,bool){order.push_back(id);});
    require(order==std::vector<int>({0,1}),"Schedule retained faulted scope or actor order changed");
    Bytes mask(262144,1);OwnedUnitClearance clearance(mask);mask[513]=0;
    require(clearance.allows(1,1)&&!clearance.allows(-1,1)&&!clearance.allows(512,1),"Clearance borrowed mutable bytes or lost bounds");
    bool refused=false;try{OwnedUnitClearance bad(Bytes(4));}catch(const std::invalid_argument&){refused=true;}
    require(refused,"Short mask accepted");
    std::cout<<"Schedule validates both actors before Process0, preserves explicit order, refuses reentry, clears faulted scope; clearance owns immutable bounded mask: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
