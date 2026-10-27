// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
// Explicit test services for the ordinary movement boundary, bound to the same
// finalized map owned by the complete drawing fixture. No route finding or Mark
// implementation is inferred by this test adapter.
struct MovingUnitFixture {
    prepared_fixture::Map& map;
    GroundDriveProcessState state;
    GroundDriveProcessServices services;
    std::unique_ptr<PreparedDriveTerrain> terrain;
    int tick=0,speed=0,mode=0;
    float rockingX=0,rockingY=0;
    static void actorStore(int off,int n){out('A',off,std::uint32_t(n));}
    static void rampStore(int off,int n){out('L',off+4,std::uint32_t(n));}
    MovingUnitFixture(prepared_fixture::Map& map_,const RenderData& light,int height,std::istringstream& in):map(map_){
        auto& m=state.movement;Coord at;int heading=0,rot=0,marked=0,effect=0,present=0,key=0,steps=0;
        in>>at.x>>at.y>>at.z>>state.destination.x>>state.destination.y>>state.destination.z>>heading>>rot>>speed>>tick>>steps>>marked>>effect>>mode>>present>>key;
        for(auto& d:state.route)in>>d;
        std::array<std::uint64_t,4> raw;for(auto& n:raw)in>>n;
        if(!in||heading<0||heading>65535||rot<1||rot>127||speed<0||speed>255||steps<1||steps>256||marked<0||marked>255||
            effect<0||effect>1||mode<0||mode>3||present!=1||key!=0)throw std::invalid_argument("Moving Unit command outside domain");
        bool end=false;for(int d:state.route){if(d==-1)end=true;else if(end||d<0||d>7)throw std::invalid_argument("Invalid moving Unit route");}
        if(state.route.back()!=-1)throw std::invalid_argument("Unterminated moving Unit route");
        std::array<double,4> numbers;for(unsigned i=0;i<4;++i){numbers[i]=std::bit_cast<double>(raw[i]);if(!std::isfinite(numbers[i]))throw std::invalid_argument("Nonfinite movement input");}
        m.actor={at,std::uint8_t(marked),0};m.reached5a0=7;m.reached5a1=9;
        m.body.desired=m.body.start=std::uint16_t(heading);m.body.rate=std::uint16_t(rot*256);
        state.percentage=numbers[0];state.retryPadding=7;
        services.advance.ground.mark=[this,effect](int kind){auto& actor=state.movement.actor;
            out('M',kind,actor.position.x,actor.position.y,actor.position.z,unsigned(actor.bridge79),unsigned(actor.marked74));
            if(effect)actor.marked74=std::uint8_t(kind);};
        services.advance.unmarkOccupation=[](Coord p){out('U',p.x,p.y,p.z);};services.advance.notify=[](int n){out('N',n);};services.advance.postCell=[]{out('P');};
        services.reserve=[](auto x,auto y){out('R',x,y);};services.markNext=[](auto x,auto y){out('K',x,y);};services.markOccupation=[](Coord p){out('E',p.x,p.y,p.z);};
        services.admit=[](const GroundDriveCell& c,int d,int level){out('D',c.x,c.y,d,level);};services.noRoute=[]{out('B','J','V',0,1);};services.squareRoot=[&light](double n){return tableSqrt(light,n);};
        for(int i=0;i<12;++i)services.trackSpeed[std::size_t(i)]=float(numbers[1]*(1.-i/16.));services.uphill=numbers[2];services.downhill=numbers[3];
        const auto check=[this](const MapCellInput& c){
            if(&c==&map.fallback.input){if(map.fallback.overlay!=-1)throw std::invalid_argument("Overlay fallback");return;}
            const auto slot=std::size_t(std::uint16_t(c.position.y))*512+std::uint16_t(c.position.x);
            if(slot>=map.slots.size()||map.slots[slot]<0||map.table[slot]!=&c||map.cells[std::size_t(map.slots[slot])].attributes.overlay!=-1)
                throw std::invalid_argument("Moving Unit profile refuses overlay/noncanonical Cells");
        };
        const auto query=[](char c,Coord p){out(c,p.x,p.y);if(c=='C'||c=='F')out(p.z);};
        terrain=std::make_unique<PreparedDriveTerrain>(map.floorState,height,MapFloorHeightWorld{map.table,&map.fallback.input,{}},check,query);
        services=terrain->bind(services);
        const int old=std::fegetround();const int modes[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};std::fesetround(modes[mode]);
        setActorRelativeHeight(m.actor,0,416,services.advance.ground,actorStore);
        unlimboDriveRamp(state.ramps,[&]{(void)services.cell(m.actor.position);return services.cell(m.actor.position).ramp;},tick,7,rampStore);
        std::fesetround(old);initialSteps=steps;
    }
    int initialSteps=0;
    void advance(const DriveData& drive,int steps,bool first=false){
        if(steps<1||steps>256)throw std::invalid_argument("Moving Unit tick count outside domain");
        const int old=std::fegetround();const int modes[]={FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};std::fesetround(modes[mode]);
        for(int j=0;j<steps;++j){if(!first||j)tick=signed32(std::uint32_t(tick)+1u);
            (void)processOrdinaryGroundDrive(state,drive,speed,tick,7,services,actorStore,rampStore);
            const auto& m=state.movement;
            out('S',m.actor.position.x,m.actor.position.y,m.actor.position.z,m.head.x,m.head.y,m.head.z,m.track,m.index,m.accumulator,m.driving,
                unsigned(m.actor.marked74),unsigned(m.reached5a0),unsigned(m.reached5a1),m.body.desired,m.body.start,m.body.timerStart,m.body.duration,m.body.rate,
                state.wasRotating,std::uint16_t(state.nextX)|(std::uint32_t(std::uint16_t(state.nextY))<<16),unsigned(state.crossing57b),
                std::bit_cast<std::uint64_t>(state.percentage),std::bit_cast<std::uint64_t>(state.instancePercentage),state.ramps.current,state.ramps.previous,
                state.ramps.start,state.ramps.padding,state.ramps.remaining,state.ramps.duration,state.retryStart,state.retryPadding,state.retryRemaining);
            for(int d:state.route)out(d);
            if(std::fegetround()!=modes[mode])throw std::runtime_error("Moving Unit leaked FP mode");
        }
        std::fesetround(old);
    }
};
