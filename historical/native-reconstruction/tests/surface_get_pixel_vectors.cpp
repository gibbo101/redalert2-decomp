// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/SurfacePixel.hpp"
#include "assets/PreparedData.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
void need(bool v){if(!v)throw std::invalid_argument("Pixel fixture domain");}
void run(std::istream& in){
 char op=0;std::int32_t width=0,height=0,bpp=0,lock=0,x=0,y=0;std::uint32_t offset=0,color=0;int allocation=0,words=0;
 need(bool(in>>op>>width>>height>>bpp>>offset>>lock>>x>>y>>color>>allocation>>words)&&op=='G');std::string tail;need(!(in>>tail));need(((width>=-16&&width<=16)||width==2147483647)&&height>=-16&&height<=16&&bpp>=-3&&bpp<=4&&offset<=259&&allocation>=0&&allocation<=1&&words>=0&&words<=1);
 Bytes pixels(2048);for(unsigned i=0;i<pixels.size();++i)pixels[i]=std::uint8_t(i*29+0x34);std::vector<std::uint16_t> backing(1024);for(unsigned i=0;i<backing.size();++i)backing[i]=std::uint16_t(pixels[2*i]|std::uint16_t(pixels[2*i+1])<<8);
 auto trace=[](auto at,auto n,auto v){std::cout<<"S "<<at<<' '<<n<<' '<<v<<' ';};auto locks=[](auto depth){std::cout<<"L "<<depth<<' ';};
 SurfacePixelView view{width,lock,bpp,offset,words?std::span<std::uint8_t>{}:std::span<std::uint8_t>{pixels},words?std::span<std::uint16_t>{backing}:std::span<std::uint16_t>{},bool(allocation)};
 const auto result=getSurfacePixel(view,x,y,{},locks);
 if(words)for(unsigned i=0;i<pixels.size();++i)pixels[i]=std::uint8_t(backing[i/2]>>(8*(i&1)));
 std::cout<<"R "<<result<<' '<<lock<<' '<<assetSha256(Data(pixels))<<'\n';
}
void guards(){
 FillSurface s;std::array<std::uint8_t,8> bytes{0x34,0x12,0x78,0x56};s.width=2;s.bytesPerPixel=2;s.storage=bytes;
 need(getSurfacePixel(surfacePixelView(s),0,0)==0x1234&&s.lockLevel==0);
 s.bytesPerPixel=3;need(getSurfacePixel(surfacePixelView(s),0,0)==0x34&&s.lockLevel==0);
 bool refused=false;try{getSurfacePixel(surfacePixelView(s),10,0);}catch(const std::invalid_argument&){refused=true;}need(refused&&s.lockLevel==1);
 s.lockLevel=0;auto view=surfacePixelView(s);view.allocationPresent=false;need(getSurfacePixel(view,0,0)==0&&s.lockLevel==1);
 s.lockLevel=0;bool propagated=false;try{getSurfacePixel(surfacePixelView(s),0,0,[]()->std::int32_t{throw std::runtime_error("width fault");});}catch(const std::runtime_error&){propagated=true;}need(propagated&&s.lockLevel==1);
 s.lockLevel=0;s.bytesPerPixel=2;bool changed=false;auto value=getSurfacePixel(surfacePixelView(s),0,0,{},[&](auto depth){if(depth==0){bytes[0]=0xff;changed=true;}});need(value==0x1234&&changed);
 std::cout<<"surface get pixel guards PASS\n";

}
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
