// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/UnitModels.hpp"
#include "assets/UnitModelInputs.hpp"
#include <iostream>
#include <stdexcept>
using namespace ra2;
int main(){try{
    UnitModelServices s;s.open=[](std::string_view)->ModelToken{throw std::runtime_error("Unexpected resource service");};
    const OrdinaryUnitModels initial{.image="HTNK"};
    for(int i=0;i<9;++i) {
        auto t=initial;
        switch(i) {
        case 0:t.image="";break;
        case 1:t.image=std::string(25,'X');break;
        case 2:t.image="a/b";break;
        case 3:t.image="a\\b";break;
        case 4:t.image="C:x";break;
        case 5:t.image=std::string("a\0b",3);break;
        case 6:t.turret=0;break;
        case 7:t.turretCount=1;break;
        case 8:t.turretCount=-1;break;
        }
        bool refused=false;
        try{loadOrdinaryUnitModels(t,s);}catch(const std::invalid_argument&){refused=true;}
        if(!refused)throw std::runtime_error("Unsupported model profile accepted");
    }
    auto inputs=readUnitModelInputs(Ini("[HTNK]\nTurretCount=0\n"),Ini("[HTNK]\nTurretOffset=0\n"),"HTNK");
    requireOrdinaryRhinoModelInputs(inputs);
    for(int i=0;i<5;++i) {
        auto t=inputs;
        if(i==0)t.turretCount=1;else if(i==1)t.turretCount=-1;
        else if(i==2)t.turretOffset=1;else if(i==3)t.image[0]='X';else t.image.fill('X');
        bool refused=false;try{requireOrdinaryRhinoModelInputs(t);}catch(const std::runtime_error&){refused=true;}
        catch(const std::invalid_argument&){refused=true;}
        if(!refused)throw std::runtime_error("Unsupported Rhino model input accepted");
    }
    // The rules override selects the art section; defaults follow that Image.
    const auto alias=readUnitModelInputs(Ini("[HTNK]\nImage=ALIAS\nTurretCount=2\n"),Ini("[HTNK]\nTurretOffset=9\n[ALIAS]\nTurretOffset=3\n"),"HTNK");
    if(modelImageString(alias.image)!="ALIAS"||alias.turretCount!=2||alias.turretOffset!=3)
        throw std::runtime_error("Model image/art section association changed");
    std::cout<<"Nine model path/profile guards and five stock input guards/section selection: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
