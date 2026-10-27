// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/VisibilityData.hpp"
#include "assets/PreparedData.hpp"
#include <iostream>
#include <stdexcept>
using namespace ra2;
int main(){try{for(auto size:{std::size_t(0),std::size_t(295),std::size_t(296),std::size_t(297)}){bool refused=false;try{(void)readVisibilityData(Data(Bytes(size,0)),PatchedEngineSha);}catch(const std::exception&){refused=true;}if(!refused)throw std::runtime_error("Invalid visibility data accepted");}std::cout<<"Visibility data guards PASS\n";}catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}}
