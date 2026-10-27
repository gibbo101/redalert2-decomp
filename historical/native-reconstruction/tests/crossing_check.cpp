// SPDX-License-Identifier: GPL-3.0-or-later
#include "platform/CrossingScenario.hpp"
#include <iostream>
int main(int argc,char** argv){try{
    if(argc<2||argc>4||(argc==4&&std::string(argv[3])!="--light")){std::cerr<<"Usage: crossing-check OWNED_INSTALL [PRIVATE_OUTPUT_DIR [--light]]\n";return 2;}
    ra2::GameAssets assets(argv[1],"mp03t4.map");ra2::prepareStaticScenery(assets);
    ra2::CrossingScenario scenario(assets);auto sim=scenario.initial(assets);
    ra2::Renderer view(assets,1024,720);scenario.center(view);
    if(argc==4)view.addLightDemo(ra2::CrossingScenario::lightX,ra2::CrossingScenario::lightY);
    ra2::CrossingRegression regression(assets,view,argc>=3?argv[2]:"");
    view.draw(sim);regression.sample(sim,view);
    if(!sim.move(scenario.destination,[&](int x,int y,int z){return assets.clearCell(x,y,z);}))
        throw std::runtime_error("Crossing direct route was refused");
    for(int step=0;sim.moving&&step<200;++step){sim.step();view.draw(sim);regression.sample(sim,view);}
    regression.finish(sim,view);
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
