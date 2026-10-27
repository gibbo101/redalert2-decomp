// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/ResidentMapFloor.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace ra2;
int main(){try{
 MapFinalizationCell cell;auto& a=cell.attributes;a.input.position={1,2};a.input.tile=0;a.input.slope=1;a.input.flags=0xffffffffu;a.overlay=0;a.passability=17;cell.field30=91;cell.wallOwner=41;
 MapCellAttributes fallback;fallback.input.tile=65535;fallback.input.position={-1,-1};
 std::vector<int> slots(262144,-1);std::vector<MapCellInput*> table(262144);slots[1025]=0;table[1025]=&a.input;
 std::array<MapOverlayType,1> types;types[0].land=4;types[0].wall=types[0].tiberium=types[0].noUseTileLandType=1;
 std::array<MapResourceType,1> resources;resources[0].numImages=1;resources[0].numFrames=1;resources[0].value=std::numeric_limits<int>::max();
 MapTileImageInput image;image.columns=image.rows=1;image.width=60;image.height=30;image.subTiles={MapSubTileInput{0,1,false,0,0}};
 std::array<MapTileAttributes,1> tiles;tiles[0].image=&image;std::array<int,16> mapping{};std::array<float,11> speeds;speeds.fill(1);std::array<std::uint8_t,9> frames{};
 ResidentCellInputs resident;resident.world={table,&fallback.input,{},{}};resident.tiles=tiles;resident.landMap=mapping;resident.overlays=types;resident.resources=resources;resident.wheelSpeeds=speeds;resident.permission={2,0,0,2,2};resident.lat.fill(-1);
 MapFinalizationInputs input{2,2,slots,resident,frames,{}};Bytes b4(100),b10(250);unsigned observations=0;MapFinalizationServices s;
 s.initializeLighting=[](int){};s.beforeOwner=[](int){throw std::runtime_error("Cleared wall still queried owner");};
 s.attributeStore=[&](int,MapAttributeField f,unsigned n){if(f==MapAttributeField::Overlay&&std::uint32_t(a.overlay)!=n)throw std::runtime_error("Stale overlay observer");if(f==MapAttributeField::OverlayData&&a.overlayData!=n)throw std::runtime_error("Stale data observer");++observations;};
 s.passabilityStore=[&](int,int n){if(a.passability!=n)throw std::runtime_error("Stale passability observer");++observations;};
 const auto result=finalizeResidentMap(input,std::span(&cell,1),fallback,b4,b10,s);
 if(result.resourceTotal!=2147483647u||a.overlay!=-1||cell.wallOwner!=41||cell.field30||a.input.flags!=0xFFCDFFFFu||!observations)throw std::runtime_error("Parent return/store/post-recalculation owner order differs");
 types[0].tiberium=0;a.overlay=0;s.beforeOwner={};s.ownerStore=[&](int,int n){if(n!=-1||cell.wallOwner!=-1)throw std::runtime_error("Stale owner observer");++observations;};
 const auto zero=finalizeResidentMap(input,std::span(&cell,1),fallback,b4,b10,s);if(zero.resourceTotal||cell.wallOwner!=-1)throw std::runtime_error("Nonresource wall/empty registry differs");
 cell.field30=91;bool refused=false;table[1025]=&fallback.input;
 try{finalizeResidentMap(input,std::span(&cell,1),fallback,b4,b10,s);}catch(const std::invalid_argument&){refused=true;}
 if(!refused||cell.field30!=91)throw std::runtime_error("Inconsistent canonical table was used");
 table[1025]=&a.input;cell.attachedTag=true;refused=false;
 try{finalizeResidentMap(input,std::span(&cell,1),fallback,b4,b10,s);}catch(const std::invalid_argument&){refused=true;}
 if(!refused||cell.field30!=91)throw std::runtime_error("Unrecovered tag was used");
 cell.attachedTag=false;s.ownerStore={};a.overlay=0;types[0].tiberium=0;
 a.input.level=4;a.input.slope=20;MapFloorHeightState floorState;floorState.planes[0].x=1;
 std::array<WallOwnerBuilding,2> candidates{{{1,1,1},{1,1,1}}};input.buildings=candidates;
 std::array<MapWallBuildingPosition,2> positions{{{{384,640,0},1,1},{{384,640,832},1,1}}};
 unsigned floorCalls=0;s.buildingOwner=[](int,std::size_t b){return b?9:7;};
 // Squared distance is a diagnostic monotone service in this guard only; exact
 // numerical fidelity is established by the private original-table oracle.
 MapFinalizationFloor floor{floorState,104,positions,[](double n){return n;},{},
  [&](int id,Coord p){if(id||p.x!=384||p.y!=640||a.input.slope!=1||a.input.level!=4)throw std::runtime_error("Height saw stale Cell");++floorCalls;},{}};
 finalizeResidentMapWithFloor(input,std::span(&cell,1),fallback,b4,b10,s,floor);
 if(cell.wallOwner!=9||floorCalls!=2||floorState.flags!=7)throw std::runtime_error("Actual floor binding ignored post-recalculation ramp");
 types[0].tiberium=1;a.overlay=0;floorCalls=0;floorState.flags=0;
 finalizeResidentMapWithFloor(input,std::span(&cell,1),fallback,b4,b10,s,floor);
 if(a.overlay!=-1||floorCalls||floorState.flags)throw std::runtime_error("Cleared wall initialized floor state");
 cell.field30=91;auto invalidFloor=floor;invalidFloor.buildings={};refused=false;
 try{finalizeResidentMapWithFloor(input,std::span(&cell,1),fallback,b4,b10,s,invalidFloor);}catch(const std::invalid_argument&){refused=true;}
 if(!refused||cell.field30!=91)throw std::runtime_error("Candidate association guard changed parent");
 s.buildingDistance=[](int,std::size_t){return 0;};refused=false;
 try{finalizeResidentMapWithFloor(input,std::span(&cell,1),fallback,b4,b10,s,floor);}catch(const std::invalid_argument&){refused=true;}
 if(!refused||cell.field30!=91)throw std::runtime_error("Supplied distance leaked into floor profile");
 std::cout<<"Map finalization canonical stores/post-recalculation wall selection/return guards: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
