// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/ResidentMapFloor.hpp"
#include "render/UnitBaseDepth.hpp"
#include "render/PreparedFootDepth.hpp"
#include "render/MapLighting.hpp"
#include <openssl/evp.h>
#include <bit>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
using Words=std::vector<std::uint32_t>;
std::string digest(const std::uint8_t* p,std::size_t size){unsigned char h[32];unsigned n=0;if(!EVP_Digest(p,size,h,&n,EVP_sha256(),nullptr)||n!=32)throw std::runtime_error("Digest failed");std::ostringstream s;for(auto b:h)s<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(b);return s.str();}
std::string digest(const Words& v){Bytes b;for(auto n:v)for(unsigned i=0;i<4;++i)b.push_back(std::uint8_t(n>>(i*8)));return digest(b.data(),b.size());}
unsigned packed(MapInputPosition p){return std::uint16_t(p.x)|(unsigned(std::uint16_t(p.y))<<16);}
struct Building {WallOwnerBuilding flags;int owner=0,foundation=0,width=0,height=0;Coord point;};
}
int main(int argc,char** argv){try{
 if(argc!=2)throw std::invalid_argument("Supply private render-data.bin");const auto render=readRenderData(readFile(argv[1]));
 std::string line;while(std::getline(std::cin,line)){
  std::istringstream in(line);char op=0;int width=0,height=0,hole=-1;unsigned seed=0,cliff=0;MapLightSettings light;
  std::array<int,16> mapping;MapLATSettings lat;std::array<MapInputPosition,8> directions;std::array<float,11> speeds;
  MapFloorHeightState floorState;int levelHeight=0;
  in>>op;
  if(op=='F'||op=='D'||op=='E'){
   unsigned flags=0;std::uint64_t bits=0;in>>flags>>bits;floorState.flags=std::uint8_t(flags);floorState.height=std::bit_cast<double>(bits);
   in>>bits;floorState.scale=std::bit_cast<double>(bits);
   for(auto& plane:floorState.planes)for(double* v:{&plane.x,&plane.y,&plane.offset,&plane.limit,&plane.add}){in>>bits;*v=std::bit_cast<double>(bits);}
   in>>levelHeight;if(flags>255)throw std::invalid_argument("Invalid floor flags");
  }
  in>>width>>height>>seed>>hole>>cliff>>light.ambient>>light.tint[0]>>light.tint[1]>>light.tint[2]>>light.ground>>light.level;
  if((op!='G'&&op!='F'&&op!='D'&&op!='E')||width<2||height<1||width+height>256||cliff>2)throw std::invalid_argument("Unsupported finalization profile");
  for(auto& n:mapping)in>>n;for(auto& n:lat)in>>n;for(auto& d:directions){unsigned n=0;in>>n;d={std::bit_cast<std::int16_t>(std::uint16_t(n)),std::bit_cast<std::int16_t>(std::uint16_t(n>>16))};}
  for(auto& f:speeds){unsigned n=0;in>>n;f=std::bit_cast<float>(std::uint32_t(n));}
  MapPermissionShape shape;in>>shape.dimension0>>shape.originX>>shape.originY>>shape.width>>shape.height;
  unsigned count=0;in>>count;if(count<1||count>1024)throw std::invalid_argument("Invalid type count");
  std::vector<MapTileImageInput> images(count);std::vector<MapTileAttributes> tiles(count);
  for(unsigned i=0;i<count;++i){auto& image=images[i];int present=0;in>>present>>image.columns>>image.rows>>image.width>>image.height;
   if((present!=0&&present!=1)||image.columns<1||image.rows<1||image.columns*std::int64_t(image.rows)>60)throw std::invalid_argument("Bad TMP profile");
   for(int j=0;j<image.columns*image.rows;++j){int valid=0,land=0,ramp=0,extra=0;MapSubTileInput sub;in>>valid>>land>>ramp>>sub.y>>sub.extraY>>extra;
    if((valid!=0&&valid!=1)||land<0||land>15||ramp<0||ramp>255||(extra!=0&&extra!=1))throw std::invalid_argument("Bad subtile");sub.land=std::uint8_t(land);sub.ramp=std::uint8_t(ramp);sub.extra=extra;image.subTiles.push_back(valid?std::optional{sub}:std::nullopt);}
   if(present)tiles[i].image=&image;
  }
  in>>count;if(count>16384)throw std::invalid_argument("Too many Cells");std::vector<MapFinalizationCell> cells(count);std::vector<int> cellHeights(count),slots(262144,-1);std::vector<MapCellInput*> table(262144);
  for(unsigned i=0;i<count;++i){auto& c=cells[i];auto& v=c.attributes.input;int x=0,y=0,sub=0,level=0,slope=0,extra=0,data=0,ice=0;
   in>>x>>y>>v.tile>>sub>>level>>v.flags>>v.tube>>v.land>>slope>>extra>>data>>ice>>c.attributes.passability>>c.field30>>c.attributes.overlay>>c.wallOwner>>cellHeights[i];
   if((op=='F'||op=='D'||op=='E')&&cellHeights[i]!=0)throw std::invalid_argument("F profile cannot supply Cell heights");
   if(x<0||x>=512||y<0||y>=512||slots[std::size_t(y)*512+x]!=-1||level<0||level>31)throw std::invalid_argument("Invalid Cell association");
   v.position={std::int16_t(x),std::int16_t(y)};v.subTile=std::uint8_t(sub);v.level=std::int8_t(level);v.slope=std::uint8_t(slope);v.ice=std::uint8_t(ice);c.attributes.extraHeight=std::uint8_t(extra);c.attributes.overlayData=std::uint8_t(data);slots[std::size_t(y)*512+x]=int(i);table[std::size_t(y)*512+x]=&v;
  }
  if(hole>=0){if(std::size_t(hole)>=cells.size())throw std::invalid_argument("Missing hole");auto p=cells[std::size_t(hole)].attributes.input.position;slots[std::size_t(p.y)*512+p.x]=-1;table[std::size_t(p.y)*512+p.x]=nullptr;}
  in>>count;if(count>255)throw std::invalid_argument("Too many overlays");std::vector<MapOverlayType> overlays(count);
  for(auto& t:overlays){int crush=0,wall=0,tib=0,noUse=0,rubble=0,rock=0;in>>t.land>>crush>>wall>>tib>>noUse>>rubble>>rock;t.flag1FD=std::uint8_t(crush);t.wall=std::uint8_t(wall);t.tiberium=std::uint8_t(tib);t.noUseTileLandType=std::uint8_t(noUse);t.rubble=std::uint8_t(rubble);t.rock=std::uint8_t(rock);}
  in>>count;if(count>8)throw std::invalid_argument("Too many resources");std::vector<MapResourceType> resources(count);for(auto& r:resources)in>>r.index>>r.imageIndex>>r.numImages>>r.numSlopes>>r.numFrames>>r.value;
  std::array<std::uint8_t,9> frames;for(auto& f:frames){unsigned n=0;in>>n;f=std::uint8_t(n);}
  in>>count;if(count>64)throw std::invalid_argument("Too many buildings");std::vector<Building> buildings(count);std::vector<WallOwnerBuilding> flags;
  for(auto& b:buildings){int active=0,onMap=0,wall=0;in>>active>>onMap>>wall>>b.owner>>b.foundation>>b.width>>b.height>>b.point.x>>b.point.y>>b.point.z;b.flags={std::uint8_t(active),std::uint8_t(onMap),std::uint8_t(wall)};flags.push_back(b.flags);}
  std::vector<UnitBaseDepthInputs> depthQueries;
  std::vector<PreparedFootDepthInputs> footQueries;
  if(op=='D'||op=='E'){
   char separator=0;unsigned queries=0;in>>separator>>queries;if(separator!='|'||queries<1||queries>4096)throw std::invalid_argument("Invalid base-depth query count");
   depthQueries.resize(queries);footQueries.resize(queries);unsigned qi=0;
   for(auto& q:depthQueries){unsigned desired=0,start=0,rate=0;std::uint64_t scale=0;
    in>>q.location.x>>q.location.y>>q.location.z>>desired>>start>>q.facing.timerStart>>q.facing.duration>>rate>>q.tick>>scale
      >>q.currentRamp>>q.neighborRamp>>q.rock>>q.dimensionHeight>>q.defaultTile;
    if(desired>65535||start>65535||rate>65535)throw std::invalid_argument("Invalid base-depth Facing");
    q.facing.desired=std::uint16_t(desired);q.facing.start=std::uint16_t(start);q.facing.rate=std::uint16_t(rate);q.heightScale=std::bit_cast<double>(scale);
    if(op=='E'){
     auto& f=footQueries[qi++];int drive=0,x=0,y=0;in>>drive>>f.tileBase>>x>>y>>f.type.b60>>f.type.b64>>f.type.b5c>>f.type.b68;
     if(q.dimensionHeight!=0||(drive!=0&&drive!=1)||x<-32768||x>32767||y<-32768||y>32767)throw std::invalid_argument("Invalid prepared Foot inputs");
     f.unit=q;f.drive=drive;f.invalid={std::int16_t(x),std::int16_t(y)};
    }
   }
  }
  if(!in)throw std::invalid_argument("Incomplete finalization fixture");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing finalization fixture");
  Words events,visits;const auto event=[&](std::initializer_list<std::uint32_t> v){events.insert(events.end(),v);};
  MapCellAttributes fallback;fallback.input.tile=65535;fallback.input.tube=-1;fallback.input.position={-1,-1};
  ResidentCellInputs resident;resident.world={table,&fallback.input,[&](auto p){event({304,packed(p)});},[&](auto p){event({0xffffffffu,0,packed(p)});}};
  resident.tiles=tiles;resident.landMap=mapping;resident.overlays=overlays;resident.resources=resources;resident.wheelSpeeds=speeds;resident.lat=lat;resident.directions=directions;resident.permission=shape;resident.cliffMode=std::uint8_t(cliff);
  MapFinalizationInputs input{width,height,slots,resident,frames,flags};const auto capacity=std::size_t(width+height+1)*(width+height+1);Bytes b4(capacity*4,0xa5),b10(capacity*10,0xa5);
  std::vector<std::array<unsigned,9>> lights(cells.size());for(auto& l:lights){l.fill(0xa5a5u);l[0]=0;l[1]=0xa5a5a5a5u;}
  MapFinalizationServices s;s.visit=[&](int id){visits.push_back(unsigned(id));};
  s.parentStore=[&](int id,auto f,unsigned n){event({unsigned(id),f==MapPreparationField::Field30?8u:9u,n});};
  s.initializeLighting=[&](int id){event({301,unsigned(id)});const auto& v=cells[std::size_t(id)].attributes.input;const auto l=cellLight(render,light,v.position.x,v.position.y,v.level);auto& out=lights[std::size_t(id)];out={0,unsigned(l.scale),std::uint16_t(l.sourceIntensity),std::uint16_t(l.ambient),std::uint16_t(l.terrain),std::uint16_t(l.bridge),std::uint16_t(l.tint[0]),std::uint16_t(l.tint[1]),std::uint16_t(l.tint[2])};for(unsigned j=0;j<out.size();++j)event({unsigned(id),10+j,out[j]});};
  s.beforeResource=[&](int id){event({302,unsigned(id)});};s.afterResource=[&](int id,int n){event({310,unsigned(id),unsigned(n)});};s.beforeRecalculation=[&](int id){event({303,unsigned(id)});};s.beforeOwner=[&](int id){event({311,unsigned(id)});};
  const auto attributes=[&](int id,const MapCellAttributes& a,unsigned entry){const auto& v=a.input;event({entry,unsigned(id),unsigned(v.tile),unsigned(v.land),v.slope,std::uint8_t(v.level),a.extraHeight,unsigned(a.passability)});};
  s.beforeLAT=[&](int id,const auto& a){attributes(id,a,305);};s.beforePassability=[&](int id,const auto& a){attributes(id,a,306);};
  s.classifyQuery=[&](int n){event({312,unsigned(n)});};s.missingResource=[&](int n){event({313,unsigned(n)});};s.passabilityStore=[&](int id,int n){event({unsigned(id),7,unsigned(n)});};s.ownerStore=[&](int id,int n){event({unsigned(id),21,unsigned(n)});};
  s.attributeStore=[&](int id,MapAttributeField f,unsigned n){const unsigned fields[]={1,2,3,4,5,6,0,0,19,20};const auto index=std::size_t(mapAttributeBufferIndex(cells[std::size_t(id)].attributes.input.position,width,height,int(capacity)));if(f==MapAttributeField::Buffer4)event({0xfffffffeu,unsigned(index*4+(n>>8)),n&255});else if(f==MapAttributeField::Buffer10)event({0xfffffffdu,unsigned(index*10+(n>>8)),n&255});else event({unsigned(id),fields[unsigned(f)],n});};
  s.buildingDistance=[&](int id,std::size_t b){event({314,unsigned(b)});const auto& c=cells[std::size_t(id)].attributes.input;const auto target=wallOwnerCellCoordinates(c.position,cellHeights[std::size_t(id)]);event({317,unsigned(id),unsigned(target.x),unsigned(target.y)});const auto& building=buildings[b];const auto source=wallOwnerBuildingCoordinates(building.point,building.width,building.height);const int n=wallOwnerCellDistance(source,target,[&](double v){return tableSqrt(render,v);});event({315,unsigned(n)});return n;};
  s.buildingOwner=[&](int,std::size_t b){event({316,unsigned(b)});return buildings[b].owner;};
  MapFinalizationResult result;
  if(op=='F'||op=='D'||op=='E'){
   s.buildingDistance={};std::vector<MapWallBuildingPosition> positions;
   for(const auto& b:buildings)positions.push_back({b.point,b.width,b.height});
   MapFinalizationFloor floor{floorState,levelHeight,positions,[&](double v){return tableSqrt(render,v);},
    [&](int,std::size_t b){event({314,unsigned(b)});},
    [&](int id,Coord p){event({317,unsigned(id),unsigned(p.x),unsigned(p.y)});},
    [&](int n){event({315,unsigned(n)});}};
   result=finalizeResidentMapWithFloor(input,cells,fallback,b4,b10,s,floor);
  }else result=finalizeResidentMap(input,cells,fallback,b4,b10,s);
  Words state;
  for(std::size_t i=0;i<cells.size();++i){const auto& c=cells[i];const auto& a=c.attributes;const auto& v=a.input;state.insert(state.end(),{packed(v.position),unsigned(v.tile),unsigned(v.land),std::uint16_t(v.tube),v.subTile,std::uint8_t(v.level),v.slope,v.flags,a.extraHeight,a.overlayData,v.ice,unsigned(a.passability),c.field30});state.insert(state.end(),lights[i].begin(),lights[i].end());state.insert(state.end(),{unsigned(a.overlay),unsigned(c.wallOwner)});}
  const auto& cursor=result.cursor;std::cout<<digest(state)<<' '<<digest(events)<<' '<<digest(visits)<<' '<<digest(b4.data(),b4.size())<<' '<<digest(b10.data(),b10.size())<<' '<<digest(Words{unsigned(cursor.x),unsigned(cursor.y),unsigned(cursor.remaining),cursor.index,packed(fallback.input.position)})<<' '<<result.resourceTotal;
  if(op=='F'||op=='D'||op=='E'){
   Bytes floorBytes{floorState.flags};
   const auto append=[&](double v){const auto bits=std::bit_cast<std::uint64_t>(v);for(unsigned i=0;i<8;++i)floorBytes.push_back(std::uint8_t(bits>>(i*8)));};
   append(floorState.height);append(floorState.scale);for(const auto& p:floorState.planes)for(double v:{p.x,p.y,p.offset,p.limit,p.add})append(v);
   std::cout<<' '<<digest(floorBytes.data(),floorBytes.size());
  }
  if(op=='D'||op=='E'){
   UnitBaseDepthWorld world;world.tiles=tiles;world.overlays=overlays;
   world.cell=[&](MapInputPosition p)->const MapCellAttributes&{
    const auto& found=mapAttributeCell(p,resident.world);if(&found==&fallback.input)return fallback;
    const auto slot=std::size_t(int(p.y)*512+int(p.x));return cells[std::size_t(slots[slot])].attributes;
   };
   world.query=[&](int kind){event({401u+unsigned(kind)});};
   world.dimensions=[&](int tile,int sub){event({404,unsigned(tile),unsigned(sub)});};
   if(op=='E'){
    PreparedFootDepthWorld foot;foot.unit=world;foot.trace=[&](int n){event({unsigned(n)});};
    foot.cellPredicate=[&](UnitLightCell p){event({423,packed({p.x,p.y})});};
    for(const auto& q:footQueries){const auto value=preparedFootDepth(q,foot);std::cout<<' '<<std::uint32_t(value.depth)<<' '<<std::uint32_t(value.gradient)<<' '<<packed(fallback.input.position)<<' '<<digest(events);}
   }else for(const auto& q:depthQueries){
    const auto value=ordinaryUnitBaseDepth(q,world);
    std::cout<<' '<<std::uint32_t(value.depth)<<' '<<std::uint32_t(value.dimensionHeight)<<' '<<packed(fallback.input.position)<<' '<<digest(events);
   }
  }
  std::cout<<'\n';
 }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
