// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/IniInput.hpp"
#include <array>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
using namespace ra2;
void require(bool b){if(!b)throw std::invalid_argument("INI input fixture differs");}
std::string decode(const std::string& s){if(s=="-")return {};require(s.size()%2==0);std::string r;for(std::size_t i=0;i<s.size();i+=2)r.push_back(char(std::stoul(s.substr(i,2),nullptr,16)));return r;}
void run(std::istream& in){
 std::string raw;std::array<int,10> f;require(bool(in>>raw));for(auto& v:f)require(bool(in>>v));std::string tail;require(!(in>>tail));
 require(f[0]>=0&&f[0]<4&&f[2]>=-2&&f[2]<=64&&f[3]>0&&f[3]<=64&&f[4]>=0&&f[4]<64&&f[5]>=0&&f[5]<=64&&f[4]+f[5]<=64&&f[6]>=-3&&f[6]<=255&&f[7]>=0&&f[7]<4&&f[8]>=0&&f[8]<7&&f[9]>=1&&f[9]<=3);
 const auto data=decode(raw);std::array<std::uint8_t,520> out;out.fill(0xa5);std::array<std::uint8_t,64> buffer,alt;
 for(unsigned i=0;i<64;++i){buffer[i]=std::uint8_t(0x40+i);alt[i]=std::uint8_t(0xd0+i);}
 std::uint8_t eof=std::uint8_t(f[6]);auto* eofPointer=f[6]==-1?nullptr:f[6]==-2?&out[0]:f[6]==-3?&out[519]:&eof;
 int sourceIds[2]{};const void* source=&sourceIds[0];std::span<std::uint8_t> backing(buffer);int size=f[2],cursor=f[4],available=f[5];IniBufferedInput w{source,backing,size,cursor,available};
 unsigned position=0,calls=0,mutated=0;bool copying=false;std::vector<std::uint64_t> trace;
 const auto event=[&](std::uint64_t k,std::uint64_t a=0,std::uint64_t b=0,std::uint64_t c=0){trace.insert(trace.end(),{k,a,b,c});};
 const auto srcId=[&](){return source==&sourceIds[0]?1u:source==&sourceIds[1]?2u:0u;};
 const auto mutate=[&](int where){if(mutated||f[8]!=where)return;mutated=1;event(5,where);
  if(where==1)source=&sourceIds[1];if(where==2)backing=alt;if(where==3){cursor=2;available=3;}if(where==4)available=99;if(where==5)cursor=3;if(where==6)size=2;};
 IniInputServices services;
 services.sourceRead=[&](const void* p,std::span<std::uint8_t> destination,int requested){
  require(p==&sourceIds[0]||p==&sourceIds[1]);copying=false;++calls;
  int count=requested<=0?0:std::min({unsigned(requested),unsigned(f[3]),unsigned(data.size()-position)});int returned=count;
  if(calls==1&&f[7]==1){count=0;returned=-1;}else if(calls==1&&f[7]==2)returned=2;else if(f[7]==3){count=0;returned=0;}
  require(unsigned(count)<=destination.size());for(int i=0;i<count;++i)destination[i]=std::uint8_t(data[position++]);event(1,p==&sourceIds[0]?1:2,std::uint32_t(requested),std::uint32_t(returned));
  mutate(1);mutate(2);mutate(3);mutate(6);return returned;
 };
 services.copy=[&](auto destination,auto bytes){
  unsigned sourceOffset=0;bool found=false;for(unsigned i=0;i<64;++i){if(bytes.data()==&buffer[i]){sourceOffset=100+i;found=true;}if(bytes.data()==&alt[i]){sourceOffset=200+i;found=true;}}require(found);
  unsigned offset=1000;for(unsigned i=0;i<out.size();++i)if(destination.data()==&out[i])offset=i;
  event(2,offset,sourceOffset,bytes.size());std::copy(bytes.begin(),bytes.end(),destination.begin());copying=true;
 };
 services.store=[&](auto off,int value){event(3,off,std::uint32_t(value));if(off==0x18&&copying)mutate(4);if(off==0x1c&&!copying)mutate(5);};
 IniLineServices line;line.readByte=[&](std::uint8_t& b){if(f[0]==0)return readIniSource(source,{&b,1},1,services);return readBufferedIniInput(w,{&b,1},1,services);};
 line.store=[&](bool flag,std::size_t offset,std::uint8_t value){event(4,flag,offset,value);};
 for(int i=0;i<f[9];++i){int result=0;if(f[0]<=1)result=readIniInputLine(out,f[1],eofPointer,line);else if(f[0]==2)result=readBufferedIniInput(w,out,f[1],services);else result=readIniSource(source,out,f[1],services);event(6,std::uint32_t(result));}
 for(auto v:trace)std::cout<<v<<' ';std::cout<<"F "<<mutated<<' '<<srcId()<<' '<<(backing.data()==buffer.data()?1:2)<<' '<<std::uint32_t(size)<<' '<<std::uint32_t(cursor)<<' '<<std::uint32_t(available)<<' '<<position<<' '<<calls<<' '<<(eofPointer?unsigned(*eofPointer):256)<<' ';
 for(auto v:out)std::cout<<unsigned(v)<<' ';for(auto v:buffer)std::cout<<unsigned(v)<<' ';for(auto v:alt)std::cout<<unsigned(v)<<' ';std::cout<<'\n';
}
void guards(){
 IniLineServices line;require(readIniInputLine({},1,nullptr,line)==0);std::uint8_t byte=3;require(readIniInputLine({&byte,1},0,nullptr,line)==0&&byte==3);
 line.readByte=[](auto&){return 0;};bool refused=false;try{readIniInputLine({&byte,1},1,nullptr,line);}catch(const std::invalid_argument&){refused=true;}require(refused);
 require(readIniSource(nullptr,{},-1,{})==0);std::cout<<"ini input guards PASS\n";
}
int main(int argc,char** argv){try{if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}require(argc==1);std::string line;while(std::getline(std::cin,line)){std::istringstream in(line);run(in);}return 0;}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
