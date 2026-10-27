// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/FootPermissionOverride.hpp"
#include <stdexcept>
#include <vector>
#include <iostream>
using namespace ra2;
int main(){try{
 const auto require=[](bool v){if(!v)throw std::runtime_error("Foot permission ownership/order differs");};
 std::uint8_t active=0,flag=0;const void* team=nullptr;int token=0;
 FootPermissionOverrideActor actor{active,flag,team};FootPermissionOverrideServices services;
 require(!footPermissionOverride(actor,services));
 active=1;std::vector<char> queries;
 services.typeTrainAa0=[&]{queries.push_back('T');flag=128;return std::uint8_t(0);};
 require(footPermissionOverride(actor,services)&&queries==std::vector<char>{'T'});
 flag=0;queries.clear();services.typeTrainAa0=[&]{queries.push_back('T');active=0;return std::uint8_t(0);};
 services.mission=[&]{queries.push_back('M');team=&token;return 5;};
 services.teamPredicate=[&](const void* p){queries.push_back('P');require(p==&token);return std::uint8_t(128);};
 require(footPermissionOverride(actor,services)&&queries==std::vector<char>({'T','M','P'}));
 active=1;flag=0;team=&token;services.typeTrainAa0=[] {return std::uint8_t(255);};
 services.mission={};services.teamPredicate={};require(footPermissionOverride(actor,services));
 services.typeTrainAa0=[] {return std::uint8_t(0);};services.mission=[] {return 4;};require(footPermissionOverride(actor,services));
 services.mission=[] {return -1;};bool refused=false;
 try{(void)footPermissionOverride(actor,services);}catch(const std::invalid_argument&){refused=true;}
 require(refused);team=nullptr;require(!footPermissionOverride(actor,services));
 std::cout<<"Foot permission late actor/Team reads and entered child guards PASS\n";return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
