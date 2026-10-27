// SPDX-License-Identifier: GPL-3.0-or-later
#include "radar_cell_color_fixture.hpp"
void run(std::istream& in){
 char op;int seed,alias;if(!(in>>op>>seed>>alias)||(op!='K'&&op!='L'&&op!='M'&&op!='R')||seed<0||seed>255||alias<0||alias>1)throw std::invalid_argument("Cell color fixture prefix");
 CellColorProfile profile;profile.read(in);CellColorFixture fixture(profile,seed);fixture.recoveredOverlay=op!='K';fixture.recoveredDemand=op=='M'||op=='R';fixture.recoveredResource=op=='R';if(op=='R')fixture.readResources(in);
 std::string tail;if(in>>tail)throw std::invalid_argument("Trailing color input");ra2::MapCellAttributes cell;cell.input.position={1,3};fixture.initialize(cell);
 ra2::RadarRGB a{9,8,7},b{6,5,4};fixture.colors(cell,a,alias?a:b,[&](auto& target,auto off,auto n,auto v){std::cout<<"F "<<(&target==&a?1:2)<<' '<<off<<' '<<n<<' '<<v<<' ';});
 std::cout<<"R ";for(auto v:a)std::cout<<unsigned(v)<<' ';for(auto v:b)std::cout<<unsigned(v)<<' ';for(auto& t:fixture.types)std::cout<<int(bool(t.image))<<' ';std::cout<<'\n';
}
void guards(){
 ra2::MapCellAttributes cell;ra2::RadarRGB a{9,8,7},b{6,5,4};int clear=1;bool refused=false;
 try{ra2::cellRadarColors(cell,clear,a,b,{});}catch(const std::invalid_argument&){refused=true;}
 if(!refused||a!=ra2::RadarRGB{9,8,7}||b!=ra2::RadarRGB{6,5,4})throw std::runtime_error("Color refusal mutated output");
 const int before=std::fegetround();std::string baseline;
 for(auto mode:{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO}){
  if(std::fesetround(mode))throw std::runtime_error("Rounding mode unavailable");std::ostringstream output;auto* saved=std::cout.rdbuf(output.rdbuf());
  try{std::istringstream input("K 37 0 0 0 0 -1 0 2 3 5 0 0 0 0 -1 1 1060320051");run(input);}catch(...){std::cout.rdbuf(saved);std::fesetround(before);throw;}
  std::cout.rdbuf(saved);if(std::fegetround()!=mode)throw std::runtime_error("Color FP mode leaked");
  if(baseline.empty())baseline=output.str();else if(output.str()!=baseline)throw std::runtime_error("Color inherited caller rounding");
 }
 std::fesetround(before);std::cout<<"cell radar color guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}if(argc!=1)throw std::invalid_argument("Color arguments");std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
