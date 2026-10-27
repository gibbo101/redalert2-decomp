// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/RadarActorMarkers.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool v){if(!v)throw std::invalid_argument("Actor marker fixture domain");}
void run(std::istream& in){
 char tag;int op,index,count,x,y,reg,mutation;need(bool(in>>tag>>op>>index>>count>>x>>y>>reg>>mutation)&&tag=='A');
 need(op>=0&&op<6&&index>=0&&index<22&&count>=-1&&count<=8&&reg>=0&&reg<=255&&mutation>=0&&mutation<=5);
 std::string extra;need(!(in>>extra));
 std::uint8_t registered=std::uint8_t(reg);std::array<RadarShapeVector,22> shapes{};
 std::array<RadarShapePoint,8> points{},other{};for(int i=0;i<8;++i){points[unsigned(i)]={i-2,3-i};other[unsigned(i)]={20+i,-20-i};}
 auto& shape=shapes[unsigned(index)];shape.items=points;shape.count=count;int calls=0;int actor=0;
 const auto mutate=[&]{if(++calls!=1||!mutation)return;std::cout<<"M "<<mutation<<' ';
  switch(mutation){case 1:x=INT32_MAX;y=INT32_MIN;break;case 2:shape.count=0;break;
   case 3:shape.items=other;shape.count=4;break;case 4:index=(index+1)%22;break;case 5:registered=254;break;}
 };
 RadarActorMarkerServices s;
 s.insert631910=[&](auto p,auto a,auto b){need(p==&actor);std::cout<<"I "<<a<<' '<<b<<' '<<unsigned(registered)<<' ';mutate();};
 s.remove631AF0=[&](auto p,auto a,auto b){need(p==&actor);std::cout<<"D "<<a<<' '<<b<<' '<<unsigned(registered)<<' ';mutate();};
 s.dirty632620=[&](auto point){const bool alias=&point.x==&x&&&point.y==&y;need(alias==(op==2));
  std::cout<<"Q "<<alias<<' '<<point.x<<' '<<point.y<<' '<<unsigned(registered)<<' ';mutate();std::cout<<"L "<<point.x<<' '<<point.y<<' ';};
 s.shape6328D0=[&](auto p)->const RadarShapeVector&{need(p==&actor);std::cout<<"S "<<index<<' ';return radarActorFootprint(shapes,index);};
 s.registrationStore=[](auto v){std::cout<<"W "<<unsigned(v)<<' ';};
 const auto action=RadarActorMarkerOperation(op%3);RadarActorMarkerFields fields{x,y,registered};
 if(op<3)infantryRadarMarker(action,&actor,fields,s);else buildingRadarMarker(action,&actor,fields,s);
 std::cout<<"R "<<x<<' '<<y<<' '<<unsigned(registered)<<' '<<shape.count<<' '<<(shape.items.data()==other.data())<<' '<<index<<'\n';
}
void guards(){
 std::array<RadarShapeVector,22> shapes{};for(int i:{-1,22,INT32_MIN,INT32_MAX}){
  bool refused=false;try{radarActorFootprint(shapes,i);}catch(const std::invalid_argument&){refused=true;}need(refused);
 }
 int actor=0,x=0,y=0;std::uint8_t reg=77;RadarActorMarkerServices s;bool refused=false;
 try{infantryRadarMarker(RadarActorMarkerOperation::insert,&actor,{x,y,reg},s);}catch(const std::invalid_argument&){refused=true;}need(refused&&reg==77);
 s.shape6328D0=[&](auto)->const RadarShapeVector&{return shapes[0];};shapes[0].count=1;refused=false;
 try{buildingRadarMarker(RadarActorMarkerOperation::insert,&actor,{x,y,reg},s);}catch(const std::invalid_argument&){refused=true;}need(refused&&reg==77);
 // Borrow through the complete Infantry wrapper into the existing dirty kernel.
 // Width callbacks mutate actual actor fields before the later reloads.
 RefreshSurfaceVirtuals table;RefreshSurface surface{&table,8,8};auto* first=&surface;
 std::array<std::uint8_t,8> bits{};SurfaceMarkBitmap bitmap{bits,0};auto* bitmapOwner=&bitmap;
 std::array<RadarShapePoint,2> backing{};RadarShapeVector queue{backing,2,0,10,1,0};std::uint8_t dirty=0;
 table.width7C=[&](auto&){x=2;y=3;return 8;};table.height80=[](auto&){return 8;};
 s.dirty632620=[&](auto point){queueRadarDirtyPoint(point,{first,bitmapOwner,queue,dirty},{});};
 infantryRadarMarker(RadarActorMarkerOperation::dirty,&actor,{x,y,reg},s);
 need(queue.count==1&&queue.items[0].x==2&&queue.items[0].y==3&&bits[3]==4&&dirty==1&&reg==77);
 std::cout<<"Actor marker guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
 std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}}
 catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}return 0;}
