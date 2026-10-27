// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/CellRedraw.hpp"
#include <iostream>
#include <sstream>
using namespace ra2;
void need(bool b){if(!b)throw std::runtime_error("Cell redraw guard");}
int main(int argc,char**){
 if(argc>1){
  CellRedrawQueue q;CellRedrawView v;int frame=1,last=0;std::uint32_t flags=8;std::uint8_t dirty=1;
  bool refused=false;try{requestCellRedraw({7,last,flags,dirty},frame,v,q,{});}catch(const std::invalid_argument&){refused=true;}
  need(refused&&last==1&&dirty==1&&q.countE0==0); // Original frame store precedes child.
  v.loading8324EC=1;last=0;requestCellRedraw({7,last,flags,dirty},frame,v,q,{});need(last==0);
  std::cout<<"Cell redraw guards PASS\n";return 0;
 }
 std::string line;while(std::getline(std::cin,line))try{
  std::istringstream in(line);std::array<std::int64_t,17> f{};for(auto& n:f)need(bool(in>>n));std::string extra;need(!(in>>extra));
  CellRedrawView v{int(f[0]),int(f[9]),int(f[10]),int(f[11]),int(f[12]),int(f[13]),int(f[14])};
  int frame=int(f[1]),last=int(f[2]);std::uint32_t flags=std::uint32_t(f[3]);std::uint8_t dirty=std::uint8_t(f[4]);
  CellRedrawQueue q;q.countE0=int(f[15]);q.dirtyD7D=std::uint8_t(f[16]);for(int i=0;i<800;++i)q.cells[i]=1000+i;
  CellRedrawServices s;s.center475D60=[&]{std::cout<<"C "<<f[5]<<' '<<f[6]<<' '<<f[7]<<' ';return Coord{int(f[5]),int(f[6]),int(f[7])};};
  s.height6A2970=[&](auto z){std::cout<<"H "<<z<<' ';return int(f[8]);};
  s.store=[](char k,auto a,auto b){std::cout<<k<<' '<<a<<' ';if(k=='Q')std::cout<<b<<' ';};
  requestCellRedraw({7,last,flags,dirty},frame,v,q,s);
  std::cout<<"Z "<<last<<' '<<unsigned(dirty)<<' '<<q.countE0<<' '<<unsigned(q.dirtyD7D);for(auto n:q.cells)std::cout<<' '<<n;std::cout<<'\n';
 }catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 2;}
}
