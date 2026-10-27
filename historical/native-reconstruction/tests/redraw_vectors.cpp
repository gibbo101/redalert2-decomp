// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/Redraw.hpp"
#include <iostream>
#include <string>
using namespace ra2;
static PixelRect rect(){PixelRect r;std::cin>>r.x>>r.y>>r.width>>r.height;return r;}
static DirtyRegion region(){auto b=rect();unsigned f;std::cin>>f;return {b,std::uint8_t(f)};}
static void output(PixelRect r){std::cout<<r.x<<' '<<r.y<<' '<<r.width<<' '<<r.height<<' ';}
int main(){try{
    char command;
    while(std::cin>>command){
        std::string events;
        auto trace=[&](RedrawEvent e){events+=' ';events+=e.kind;events+=' ';events+=std::to_string(e.index);
            events+=' ';events+=std::to_string(e.field);events+=' ';events+=std::to_string(e.value);};
        if(command=='I'){
            DirtyRegionQueue q;std::cout<<q.count<<' '<<q.slots.size()<<' '<<q.growth<<' '<<q.ownsAllocation<<'\n';
        }else if(command=='M'||command=='O'){
            RedrawState s;int present,tc,counter,redraw,mode;
            std::cin>>s.mapMode>>counter>>tc>>present>>redraw>>mode;
            s.counter=std::uint8_t(counter);s.tactical=std::uint8_t(tc);s.tacticalPresent=present;
            auto needs=std::uint8_t(redraw);
            if(command=='M')requestMapRedraw(s,mode,trace);else requestObjectRedraw(needs,s,trace);
            std::cout<<s.mapMode<<' '<<unsigned(s.counter)<<' '<<unsigned(s.tactical)<<' '<<unsigned(needs)<<events<<'\n';
        }else if(command=='U'){
            const auto a=rect(),b=rect();output(unionDirtyBounds(a,b));std::cout<<'\n';
        }else if(command=='Q'){
            DirtyRegionQueue q;int capacity,owns,success;std::cin>>q.count>>capacity>>q.growth>>owns>>success;
            q.ownsAllocation=owns;for(int i=0;i<capacity;++i)q.slots.push_back(region());
            const auto incoming=region();
            auto grow=[&](DirtyRegionQueue& queue,int requested){
                trace({'g',-1,-1,requested});
                if(success){queue.slots.resize(requested,{{90,91,92,93},94});trace({'a',-1,-1,requested});}
                return success!=0;
            };
            registerDirtyRegion(q,incoming,grow,trace);
            if(!std::cin)throw std::invalid_argument("Incomplete redraw vector");
            std::cout<<q.count<<' '<<q.slots.size();
            for(const auto& slot:q.slots){std::cout<<' ';output(slot.bounds);std::cout<<unsigned(slot.flag);}
            std::cout<<events<<'\n';
        }else throw std::invalid_argument("Unknown redraw vector");
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
