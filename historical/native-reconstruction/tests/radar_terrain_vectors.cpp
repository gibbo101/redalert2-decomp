// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/RadarTerrain.hpp"
#include "radar_cell_color_fixture.hpp"
#include "render/RadarProjection.hpp"
#include "render/SurfacePixel.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool v){if(!v)throw std::invalid_argument("Radar terrain fixture domain");}
std::uint64_t digest(std::span<const std::uint8_t> b){std::uint64_t h=14695981039346656037ull;for(auto v:b){h^=v;h*=1099511628211ull;}return h;}
void run(std::istream& in){
 char op;int joined,width,origin,minimum,sw,sh,seed,hole,count;FillRect region;
 need(bool(in>>op>>joined>>width>>origin>>minimum>>sw>>sh>>region[0]>>region[1]>>region[2]>>region[3]>>seed>>hole>>count)&&(op=='T'||op=='C'||op=='B'||op=='D'||op=='E')&&(joined==0||joined==1)&&width>=2&&width<=8&&origin>=-32&&origin<=32&&minimum>=-64&&minimum<=64&&sw>=1&&sw<=32&&sh>=1&&sh<=32&&region[0]>=0&&region[1]>=0&&region[2]>=0&&region[3]>=0&&region[0]+region[2]<=sw&&region[1]+region[3]<=sh&&seed>=0&&seed<=255&&count>=0&&count<=64&&hole>=-1&&hole<count);
 std::vector<int> slots(512*512,-1);std::vector<MapCellAttributes> cells(count);std::vector<bool> seen(slots.size(),false);
 for(int i=0;i<count;++i){int slot,x,y;need(bool(in>>slot>>x>>y)&&slot>=0&&slot<512*512&&!seen[slot]&&x>=-32768&&x<=32767&&y>=-32768&&y<=32767);seen[slot]=true;cells[i].input.position={std::int16_t(x),std::int16_t(y)};if(i!=hole)slots[slot]=i;}
 CellColorProfile profile;if(op!='T')profile.read(in);CellColorFixture cellColors(profile,seed);cellColors.recoveredOverlay=op=='B'||op=='D'||op=='E';cellColors.recoveredDemand=op=='D'||op=='E';cellColors.recoveredResource=op=='E';if(op=='E')cellColors.readResources(in);if(op!='T')for(auto& c:cells)cellColors.initialize(c);
 std::string tail;need(!(in>>tail));
 std::vector<std::uint8_t> rgb(3072,0xa5),pixels(32768,0xa5),bits(4096,0xa5);
 for(int i=0;i<sw*sh*3;++i)rgb[i]=std::uint8_t(i*29+seed);
 std::span<std::uint8_t> colors=rgb,bitmap=bits;TileSweepCursor cursor{};FillRect source{0,0,sw,sh},out{9,8,7,6};
 RadarTerrainServices terrain;
 terrain.position=[&](int id)->const MapInputPosition&{need(id>=0&&id<count);return cells[id].input.position;};
 terrain.colors4712C0=[&](int id,RadarRGB& a,RadarRGB& b){std::cout<<"Q "<<id<<' ';if(op!='T'){cellColors.colors(cells[id],a,b,[&](auto& target,auto off,auto n,auto v){std::cout<<"F "<<(&target==&a?1:2)<<' '<<off<<' '<<n<<' '<<v<<' ';});return;}for(int k=0;k<3;++k){a[k]=std::uint8_t(id*37+seed+k*29);b[k]=std::uint8_t(id*53+seed+101+k*17);}};
 terrain.visit=[](auto id,const auto& c){std::cout<<"V "<<id<<' '<<c.x<<' '<<c.y<<' '<<c.remaining<<' '<<c.index<<' ';};
 terrain.store=[](auto at,auto n,auto v){std::cout<<"C "<<at<<' '<<n<<' '<<v<<' ';};
 const auto update=[&]{std::cout<<"U ";updateRadarTerrain(source,region,{width,origin,minimum,cursor,slots,colors},terrain);};
 RefreshSurfaceVirtuals table;table.width7C=[](auto& s){std::cout<<"W "<<s.width<<' ';return s.width;};table.height80=[](auto& s){std::cout<<"H "<<s.height<<' ';return s.height;};RefreshSurface surface{&table,7,5};auto* second=&surface;float scale=.5f;int cw=sw,ch=sh,lock=0,bpp=2;std::uint32_t offset=0;std::array<std::int32_t,6> shifts{11,3,0,3,5,2};
 if(!joined)update();
 else{
  RadarProjectionServices projection;projection.colors631250=[&](auto& a,auto& b){need(&a==&source&&&b==&region);update();};
  const auto view=[&]{return SurfacePixelView{surface.width,lock,bpp,offset,pixels,{},true};};
  const auto store=[](auto at,auto n,auto v){std::cout<<"S "<<at<<' '<<n<<' '<<v<<' ';};
  projection.lock=[&](auto&,auto x,auto y){std::cout<<"K "<<x<<' '<<y<<' ';need(lockSurfacePixels(view(),x,y,[&]{return table.width7C(surface);},[&](auto v){store(12,4,std::uint32_t(v));})==0);return std::span<std::uint8_t>(pixels);};
  projection.unlock=[&](auto&){std::cout<<"N ";unlockSurfacePixels(view(),[&](auto v){store(12,4,std::uint32_t(v));});};
  projection.bufferStore=[](auto kind,auto at,auto n,auto v){std::cout<<kind<<' '<<at<<' '<<n<<' '<<v<<' ';};
  buildRadarProjection(out,source,region,1,{second,colors,cw,ch,bitmap,scale,shifts},projection);
 }
 std::cout<<"R ";for(auto v:out)std::cout<<v<<' ';for(auto v:region)std::cout<<v<<' ';std::cout<<cursor.x<<' '<<cursor.y<<' '<<cursor.remaining<<' '<<cursor.index<<' '<<lock<<' '<<digest(rgb)<<' '<<digest(pixels)<<' '<<digest(bits)<<'\n';
}
void guards(){
 int w=2,o=0,m=0;TileSweepCursor c{};std::vector<int> slots(512*512,-1);std::span<std::uint8_t> rgb;FillRect r{0,0,1,1};RadarTerrainServices services;
 bool refused=false;try{updateRadarTerrain(r,r,{w,o,m,c,slots,rgb},services);}catch(const std::invalid_argument&){refused=true;}need(refused);
 services.position=[](int)->const MapInputPosition&{throw std::invalid_argument("Missing Cell");};
 // An empty map legitimately calls no color child or storage service.
 updateRadarTerrain(r,r,{w,o,m,c,slots,rgb},services);need(c.x==2&&c.y==1&&c.remaining==0);
 slots[w*512+1]=0;refused=false;try{updateRadarTerrain(r,r,{w,o,m,c,slots,rgb},services);}catch(const std::invalid_argument&){refused=true;}need(refused);
 MapCellInput cell;cell.position={1,2};services.position=[&](int)->const MapInputPosition&{return cell.position;};
 FillRect source{0,0,2,4};refused=false;
 try{updateRadarTerrain(source,source,{w,o,m,c,slots,rgb},services);}catch(const std::invalid_argument&){refused=true;}need(refused); // Missing entered color child.
 std::array<std::uint8_t,24> bytes;bytes.fill(0xa5);rgb=std::span<std::uint8_t>(bytes).first(23);
 services.colors4712C0=[](int,RadarRGB& a,RadarRGB& b){a={17,18,19};b={31,32,33};};refused=false;
 try{updateRadarTerrain(source,source,{w,o,m,c,slots,rgb},services);}catch(const std::invalid_argument&){refused=true;}
 // Safety refusal retains earlier original-ordered effects; no rollback claim.
 need(refused&&bytes[18]==17&&bytes[19]==18&&bytes[20]==19&&bytes[21]==0xa5);
 rgb=bytes;updateRadarTerrain(source,source,{w,o,m,c,slots,rgb},services);need(bytes[21]==31&&bytes[22]==32&&bytes[23]==33);
 std::cout<<"radar terrain guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
