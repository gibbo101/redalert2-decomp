// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/OverlayRadarColor.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool v){if(!v)throw std::invalid_argument("Overlay color fixture domain");}
void run(std::istream& in){
 char op;int seed,primary,alternate,animation,frames,altFrames,mutate;std::int32_t index,lateIndex;std::uint32_t frame;
 need(bool(in>>op>>seed>>index>>frame>>primary>>alternate>>animation>>frames>>altFrames>>mutate>>lateIndex)&&op=='O'&&seed>=0&&seed<=255&&primary>=0&&primary<=1&&alternate>=0&&alternate<=1&&animation>=0&&animation<=1&&frames>=-32768&&frames<=32767&&altFrames>=-32768&&altFrames<=32767&&mutate>=0&&mutate<=3);
 // Negative counts admit small frame indexes, as in the original. Wild pointer
 // arithmetic is outside the safely backed fixture domain.
 need(frame<=7||frame==0xffffffffu||frame==0xfffffffeu||frame==0x80000000u);
 std::string tail;need(!(in>>tail));
 const auto make=[&](int count,int id){Bytes b(20+8*24+3,0);b[6]=std::uint8_t(count);b[7]=std::uint8_t(count>>8);for(int i=0;i<8;++i)for(int k=0;k<3;++k)b[20+i*24+k]=std::uint8_t(seed+id*71+i*23+k*19);return Data(std::move(b));};
 Data first=make(frames,0),second=make(altFrames,1);OverlayTypeInputs type;type.index=index;type.cellAnim=alternate?17u:0u;
 OverlayRadarColorServices s;s.primaryImage=[&]()->const Data*{std::cout<<"I ";if(mutate&1)type.index=lateIndex;if(mutate&2)type.cellAnim=type.cellAnim?0u:17u;return primary?&first:nullptr;};
 s.animationImage=[&](auto id)->const Data*{need(id==17);std::cout<<"A "<<id<<' ';return animation?&second:nullptr;};
 s.store=[](auto at,auto n,auto value){std::cout<<"S "<<at<<' '<<n<<' '<<value<<' ';};
 RadarRGB color{9,8,7};overlayRadarColor(type,frame,color,s);std::cout<<"R ";for(auto c:color)std::cout<<unsigned(c)<<' ';std::cout<<type.index<<' '<<type.cellAnim<<'\n';
}
void guards(){
 OverlayTypeInputs type;RadarRGB out{9,8,7};bool refused=false;
 try{overlayRadarColor(type,0,out,{});}catch(const std::invalid_argument&){refused=true;}need(refused&&out==RadarRGB{9,8,7});
 OverlayRadarColorServices s;s.primaryImage=[]()->const Data*{return nullptr;};overlayRadarColor(type,0,out,s);need(out==RadarRGB{});
 type.cellAnim=1;out={9,8,7};refused=false;try{overlayRadarColor(type,0,out,s);}catch(const std::invalid_argument&){refused=true;}need(refused&&out==RadarRGB{9,8,7});
 Bytes b(8,0);b[6]=1;Data image(std::move(b));s.primaryImage=[&]{return &image;};refused=false;try{overlayRadarColor(type,0,out,s);}catch(const std::invalid_argument&){refused=true;}need(refused&&out==RadarRGB{9,8,7});
 std::cout<<"overlay radar color guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
