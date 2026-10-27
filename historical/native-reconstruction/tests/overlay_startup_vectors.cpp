// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OverlayImage.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool v){if(!v)throw std::invalid_argument("Overlay startup fixture domain");}
void run(std::istream& in){
 char op;int theater,tf,nf,arctic,inUse,initial,ownedValue,success,width,height,maximum,repeat;std::string name,tail;
 need(bool(in>>op>>theater>>tf>>nf>>arctic>>inUse>>initial>>ownedValue>>success>>width>>height>>maximum>>repeat>>name)&&op=='S'&&theater>=-1&&theater<=2&&(!tf||theater>=0)&&tf>=0&&tf<=255&&nf>=0&&nf<=255&&arctic>=0&&arctic<=255&&inUse>=0&&inUse<=255&&initial>=0&&initial<=1&&ownedValue>=0&&ownedValue<=255&&success>=0&&success<=1&&width>=-32768&&width<=32767&&height>=-32768&&height<=32767&&repeat>=1&&repeat<=3&&!(in>>tail));
 OverlayTypeInputs type;type.imageName=name;type.theater=std::uint8_t(tf);type.newTheater=std::uint8_t(nf);type.alternateArctic=std::uint8_t(arctic);type.arcticInUse=std::uint8_t(inUse);type.image=initial;type.imageMaximum=maximum;
 std::uint8_t owned=std::uint8_t(ownedValue);std::optional<Data> image;if(initial)image=Data(Bytes(16,1));
 Bytes header(16);for(unsigned i=0;i<2;++i){header[2+i]=std::uint8_t(std::uint16_t(width)>>(8*i));header[4+i]=std::uint8_t(std::uint16_t(height)>>(8*i));}
 OverlayStartupServices s;s.release=[](auto h){std::cout<<"F "<<h<<' ';};s.cachedImage=[&](const auto& file){std::cout<<"L "<<file<<' '<<success<<' ';return success?OverlayImageResult{2,Data(header)}:OverlayImageResult{};};s.store=[](auto off,auto n,auto v){std::cout<<"S "<<off<<' '<<n<<' '<<v<<' ';};
 for(int i=0;i<repeat;++i){initializeOverlayImage(type,image,owned,theater,s);std::cout<<"R "<<type.image<<' '<<unsigned(owned)<<' '<<std::uint32_t(type.imageMaximum)<<' '<<unsigned(type.arcticInUse)<<' '<<type.imageName<<' ';}std::cout<<'\n';
}
void guards(){
 OverlayTypeInputs t;t.imageName="GASAND";std::optional<Data> image;std::uint8_t owned=0;OverlayStartupServices s;s.cachedImage=[](auto&){return OverlayImageResult{};};
 for(int mode=0;mode<4;++mode){auto type=t;auto data=image;auto flag=owned;bool refused=false;int theater=0;auto services=s;
  if(mode==0)type.imageName="../X";if(mode==1)theater=3;if(mode==2){type.image=1;data=Data(Bytes(16));flag=1;}if(mode==3)services.cachedImage={};
  try{initializeOverlayImage(type,data,flag,theater,services);}catch(const std::invalid_argument&){refused=true;}need(refused&&type.arcticInUse==0&&flag==(mode==2?1:0));
 }
 std::cout<<"overlay startup guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
