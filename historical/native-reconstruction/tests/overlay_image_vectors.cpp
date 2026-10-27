// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/OverlayImage.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool v){if(!v)throw std::invalid_argument("Overlay image fixture domain");}
void run(std::istream& in){
 char op;int theater,demand,theaterFlag,newFlag,initial,ownedValue,success,repeat;std::string name,tail;
 need(bool(in>>op>>theater>>demand>>theaterFlag>>newFlag>>initial>>ownedValue>>success>>repeat>>name)&&op=='I'&&theater>=-1&&theater<=2&&demand>=0&&demand<=255&&theaterFlag>=0&&theaterFlag<=255&&newFlag>=0&&newFlag<=255&&initial>=0&&initial<=1&&ownedValue>=0&&ownedValue<=255&&success>=0&&success<=1&&repeat>=1&&repeat<=3&&name.size()<=24&&!(in>>tail));
 OverlayTypeInputs type;type.imageName=name;type.demandLoad=std::uint8_t(demand);type.theater=std::uint8_t(theaterFlag);type.newTheater=std::uint8_t(newFlag);type.image=initial;std::uint8_t owned=std::uint8_t(ownedValue);std::optional<Data> image;if(initial)image=Data(Bytes(16,1));
 OverlayImageServices s;s.load=[&](const auto& file){std::cout<<"C "<<file<<" L "<<success<<' ';return success?OverlayImageResult{2,Data(Bytes(16,2))}:OverlayImageResult{};};s.finish=[] {std::cout<<"D 1 D 2 ";};s.store=[](auto off,auto n,auto v){std::cout<<"S "<<off<<' '<<n<<' '<<v<<' ';};
 for(int i=0;i<repeat;++i){const auto result=ensureOverlayImage(type,image,owned,theater,s);std::cout<<"R "<<result.handle<<' '<<type.image<<' '<<unsigned(owned)<<' '<<(result.data?unsigned(result.data->u8(0)):0)<<' ';}std::cout<<'\n';
}
void guards(){
 OverlayTypeInputs type;type.imageName="LOBRDG10";type.demandLoad=1;std::optional<Data> image;std::uint8_t owned=7;int theater=0;bool refused=false;
 try{(void)ensureOverlayImage(type,image,owned,theater,{});}catch(const std::invalid_argument&){refused=true;}need(refused&&!image&&!type.image&&owned==7);
 type.theater=1;refused=false;try{(void)ensureOverlayImage(type,image,owned,theater,{});}catch(const std::invalid_argument&){refused=true;}need(refused&&!image&&owned==7);
 OverlayImageServices s;s.load=[](const auto&){return OverlayImageResult{2,{}};};s.finish=[]{};refused=false;try{(void)ensureOverlayImage(type,image,owned,theater,s);}catch(const std::invalid_argument&){refused=true;}need(refused&&!image&&!type.image&&owned==7);
 std::string name="x";applyObjectNewTheater(name,-1);need(name=="x");refused=false;try{applyObjectNewTheater(name,0);}catch(const std::invalid_argument&){refused=true;}need(refused&&name=="x");std::cout<<"overlay image guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}need(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
