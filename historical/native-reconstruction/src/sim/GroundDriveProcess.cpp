// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/GroundDriveProcess.hpp"
#include "sim/GroundDriveAdvanceAdmission.hpp"
#include "sim/OriginalMath.hpp"
#include <bit>
#include <cmath>
#include <stdexcept>
namespace ra2 {
namespace {
int add(int a,int b){return signed32(std::uint32_t(a)+std::uint32_t(b));}
std::int16_t cell(int n){return std::bit_cast<std::int16_t>(std::uint16_t(n/256));}
void write(const GroundStateStore& w,int off,int value){if(w)w(off,value);}
bool moving(const GroundDriveProcessState& s){
    const auto& m=s.movement;
    return s.destination!=Coord{}||(m.head!=Coord{}&&
        (m.head.x!=m.actor.position.x||m.head.y!=m.actor.position.y));
}
void route(GroundDriveProcessState& s,int i,int n,const GroundStateStore& w){
    s.route[std::size_t(i)]=n;write(w,0x4d0+i*4,n);
}
void consume(GroundDriveProcessState& s,int count,const GroundStateStore& w){
    for(int i=0;i<24-count;++i)route(s,i,s.route[std::size_t(i+count)],w);
    if(count==2){route(s,22,-1,w);s.crossing57b=1;write(w,0x57b,1);}
    route(s,23,-1,w);
}
// The result-2 extension binds wait state explicitly; legacy entries do not.
struct PreparationResult { const GroundDriveProcessResultServices& services;bool output=false; };
struct MovingWaitBinding { GroundDriveTimerView state;const GroundDriveMovingWaitServices& services; };
int remaining(int start,int duration,int tick){
    if(start==-1)return duration;
    const int elapsed=signed32(std::uint32_t(tick)-std::uint32_t(start));
    return elapsed>=duration?0:signed32(std::uint32_t(duration)-std::uint32_t(elapsed));
}
void prepare(GroundDriveProcessState& s,const DriveData& data,int tick,int padding,
    const GroundDriveProcessServices& svc,const GroundStateStore& w,
    const std::function<bool(std::int16_t,std::int16_t)>& gate,
    const GroundDriveAdmissionServices* admission,
    const GroundDriveResidentRetry* residentRetry=nullptr,bool preparationFlag=true,
    MovingWaitBinding* movingWait=nullptr,bool forceSingle=false,
    PreparationResult* preparationResult=nullptr){
    auto& m=s.movement;
    const auto timer=preparationResult?preparationResult->services.retry:GroundDriveTimerView{s.retryStart,s.retryPadding,s.retryRemaining};
    const GroundStateStore aw=admission?w:GroundStateStore{},dw=admission?admission->driveStore:GroundStateStore{};
    const auto clearHead=[&](bool byteLast=false){if(m.head!=Coord{}){
        m.head={};write(dw,0x40,0);write(dw,0x44,0);m.driving=false;
        if(byteLast){write(dw,0x48,0);write(dw,0x63,0);}else{write(dw,0x63,0);write(dw,0x48,0);}
    }};
    const auto retry=[&](int word){timer.start=tick;write(aw,0x530,tick);
        timer.padding=word;write(aw,0x534,word);timer.remaining=0;write(aw,0x538,0);};
    const auto* preparation=preparationResult?preparationResult->services.preparation:nullptr;
    const auto difference=[](int a,int b){return signed32(std::uint32_t(a)-std::uint32_t(b));};
    const auto magnitude=[](int n){return n<0?signed32(0u-std::uint32_t(n)):n;};
    const auto close=[&](int order,bool passengers){
        const double x=difference(m.actor.position.x,s.destination.x),
            y=difference(m.actor.position.y,s.destination.y),z=difference(m.actor.position.z,s.destination.z);
        const double squared=order==0?(x*x+y*y)+z*z:order==1?(z*z+y*y)+x*x:(x*x+z*z)+y*y;
        const double distance=svc.squareRoot(squared);
        if(!std::isfinite(distance)||distance<0||distance>2147483647.)
            throw std::invalid_argument("Preparation distance outside finite int32 profile");
        if(int(distance)>=preparation->closeEnough)return false;
        if(passengers&&preparation->passengers())return false;
        if(magnitude(difference(s.destination.z,m.actor.position.z))>=
            add(preparation->heightDivisor,preparation->heightDivisor))return false;
        return svc.cell(m.actor.position).land!=10;
    };
    const auto elevated=[&](const GroundDriveCell& c){
        if(!(preparation->flags(c)&0x100u))return std::uint8_t(0);
        const int savedZ=m.actor.position.z;
        return std::uint8_t(magnitude(difference(savedZ/preparation->heightDivisor,
            svc.liveCell(c.identity).level))>2);
    };
    if(s.route[0]==-1&&!moving(s)){
        if(preparationResult){
            preparationResult->services.flag61=0;write(dw,0x61,0);clearHead();
            if(preparationResult->services.mission()==2)preparationResult->output=preparationResult->services.finishEmptyPreparation();
        }else{m.head={};m.driving=false;}
        return;
    }
    if(s.destination==Coord{})return;
    if(s.route[0]!=-1&&preparationResult&&preparationResult->services.hasTarget()){
        const auto& child=preparationResult->services;
        if(child.targetKind()==1||child.targetKind()==15)
            throw std::invalid_argument("Process preparation actor/terrain target remains unjoined");
    }
    if(s.route[0]==-1){
        if(preparationResult&&remaining(timer.start,timer.remaining,tick)!=0)return;
        retry(padding);
        if(!preparation||!preparation->findRoute()){svc.noRoute();return;}
        // 4A2F7A..4A32C4: the successful supplied route is consumed by the
        // original caller before ordinary gate/Facing/preparation below.
        if(s.route[0]==8)return;
        if(s.route[0]<0||s.route[0]>7)throw std::invalid_argument("Successful preparation route has no direction");
        const auto [dx,dy]=directionOffset(s.route[0]&7);
        const auto x=std::bit_cast<std::int16_t>(std::uint16_t(int(cell(m.actor.position.x))+dx));
        const auto y=std::bit_cast<std::int16_t>(std::uint16_t(int(cell(m.actor.position.y))+dy));
        if(preparation->permission(x,y)){
            (void)svc.cell(m.actor.position);
            const int level=svc.cell(m.actor.position).level;
            const int direction=s.route[0];
            const int result=admission->check(svc.wordCell(x,y),direction,level);
            if(result==3)(void)gate(x,y);
            else if(result==6){
                const auto target=svc.wordCell(x,y);
                const Coord center{int(x)*256+128,int(y)*256+128,0};
                const int savedZ=m.actor.position.z;
                const int floor=svc.advance.ground.floor(center);
                const int resident=preparation->resident(target,savedZ>add(floor,add(preparation->heightDivisor,preparation->heightDivisor)));
                if(resident!=-1&&preparation->allied(resident)){
                    if(close(0,true)){
                        clearHead(true);(void)preparation->closeTarget();return;
                    }
                    preparation->scatter(target,elevated(target));
                }
            }
        }
        preparation->setCounter();
        // Do not retain the route across actual Scatter destination stores.
        if(s.route[0]==8)return;
        if(s.route[0]<0||s.route[0]>7)throw std::invalid_argument("Preparation continuation route outside domain");
    }
    const int first=s.route[0];const auto [dx,dy]=directionOffset(first);
    const Coord next{add(m.actor.position.x,dx*256),add(m.actor.position.y,dy*256),m.actor.position.z};
    const int currentLevel=svc.cell(m.actor.position).level;
    const auto crossing=svc.cell(next);
    if(preparation&&(((preparation->flags(crossing)>>8)&1u)^m.actor.bridge79)){
        s.crossing57b=1;write(aw,0x57b,1);
    }
    if(gate){if(!gate(cell(next.x),cell(next.y)))return;}
    else svc.reserve(cell(next.x),cell(next.y));
    const auto wanted=std::uint16_t(std::uint32_t(first)<<13);
    if(m.body.current(tick)!=wanted){m.body.setDesired(wanted,tick);return;}
    const auto target=svc.wordCell(cell(next.x),cell(next.y));
    svc.advance.ground.mark(0);
    int result=admission?admission->check(target,first,currentLevel):(svc.admit(target,first,currentLevel),0);
    svc.advance.ground.mark(1);
    bool candidateCrushable=false;
    if(svc.candidateOverlay){
        if(!svc.candidateOverlay->index)throw std::invalid_argument("Preparation overlay lookup unbound");
        const auto& overlay=svc.candidateOverlay->index(target.identity);
        // The original tests overlay index zero here, not overlay presence.
        if((result==4||result==5)&&svc.candidateOverlay->crusher&&overlay==0)result=0;
        if(!result&&overlay!=-1){
            if(!svc.candidateOverlay->crushable)throw std::invalid_argument("Preparation overlay type unbound");
            candidateCrushable=svc.candidateOverlay->crushable(overlay)!=0;
        }
    }
    if(result){
        if(result==6&&residentRetry){
            if(!preparationFlag){
                if(!preparation)throw std::invalid_argument("Ground Process resident scatter/close-enough outside domain");
                if(close(1,false)){
                    clearHead(true);if(preparation->closeTarget())return;
                }else{
                    const auto candidate=svc.wordCell(cell(next.x),cell(next.y));
                    std::uint8_t upper=0;
                    if(preparation->flags(candidate)&0x100u){
                        const int savedZ=m.actor.position.z;
                        const auto again=svc.wordCell(cell(next.x),cell(next.y));
                        upper=std::uint8_t(magnitude(difference(savedZ/preparation->heightDivisor,again.level))>2);
                    }
                    const auto late=svc.wordCell(cell(next.x),cell(next.y));
                    preparation->scatter(late,upper);
                }
                clearHead();s.preparation57a=0;write(aw,0x57a,0);m.track=-1;write(dw,0x58,-1);return;
            }
            // Unlike first result 7, no head clear precedes the queue/retry writes.
            route(s,0,-1,aw);retry(residentRetry->firstPadding);
            prepare(s,data,tick,padding,svc,w,gate,admission,residentRetry,false,movingWait,false,preparationResult);return;
        }
        if(result==2&&movingWait){
            clearHead();
            if(!m.reached5a1){
                m.reached5a1=1;write(aw,0x5a1,1);
                auto& wait=movingWait->state;wait.start=tick;write(aw,0x558,tick);
                wait.padding=movingWait->services.temporaryPadding;write(aw,0x55c,wait.padding);
                wait.remaining=movingWait->services.duration;write(aw,0x560,wait.remaining);
            }
            if(remaining(timer.start,timer.remaining,tick)!=0){
                s.preparation57a=0;write(aw,0x57a,0);m.track=-1;write(dw,0x58,-1);return;
            }
            const auto& wait=movingWait->state;
            const int option=m.reached5a1&&remaining(wait.start,wait.remaining,tick)==0?2:1;
            movingWait->services.failedRoute(option);return;
        }
        if(result!=3&&result!=7)throw std::invalid_argument("Ground Process admission result outside 0/3/7 domain");
        if(result==3)(void)gate(cell(next.x),cell(next.y)); // The second gate result is ignored.
        clearHead();
        if(result==7){route(s,0,-1,aw);retry(padding);prepare(s,data,tick,padding,svc,w,gate,admission,residentRetry,false,movingWait,false,preparationResult);}
        else{s.preparation57a=0;write(aw,0x57a,0);m.track=-1;write(dw,0x58,-1);}
        return;
    }
    const int delta=currentLevel-svc.wordCell(cell(next.x),cell(next.y)).level;
    int land=1,admissionLevel=currentLevel;
    if(std::abs(delta)<2){
        admissionLevel=svc.wordCell(cell(next.x),cell(next.y)).level;
        land=svc.wordCell(cell(next.x),cell(next.y)).land;
    }
    if(land<0||land>=12)throw std::invalid_argument("Ground Process land outside domain");
    double percentage=svc.trackSpeed[std::size_t(land)];
    if(percentage>1.)percentage=1.;
    const Coord center=svc.center(svc.wordCell(cell(next.x),cell(next.y)));
    const int nextFloor=svc.advance.ground.floor(center);
    const int oldFloor=svc.advance.ground.floor(m.actor.position);
    if(nextFloor>oldFloor)percentage*=svc.uphill;
    else if(nextFloor<oldFloor)percentage*=svc.downhill;
    if(percentage==0.)percentage=.5;
    s.percentage=percentage;
    svc.markNext(cell(next.x),cell(next.y));
    int second=forceSingle?first:s.route[1];
    if(second==-1){
        const auto difference=[](int a,int b){return signed32(std::uint32_t(a)-std::uint32_t(b));};
        const double x=difference(m.actor.position.x,s.destination.x),y=difference(m.actor.position.y,s.destination.y),
            z=difference(m.actor.position.z,s.destination.z);
        const double distance=svc.squareRoot((z*z+y*y)+x*x);
        if(!std::isfinite(distance)||distance<0||distance>2147483647.)
            throw std::invalid_argument("Ground Process distance outside finite int32 profile");
        if(int(distance)>512)svc.noRoute();
        second=first;
    }
    const auto [nx,ny]=directionOffset(second);
    const auto liveTarget=svc.liveCell(target.identity);
    // Actual neighbor helper calls the word lookup with wrapped word addition.
    const auto neighborX=std::bit_cast<std::int16_t>(std::uint16_t(int(liveTarget.x)+nx)),
        neighborY=std::bit_cast<std::int16_t>(std::uint16_t(int(liveTarget.y)+ny));
    std::uint8_t neighborCrushable=0;
    if(svc.ordinaryNeighbor)neighborCrushable=svc.ordinaryNeighbor(neighborX,neighborY);
    else (void)svc.wordCell(neighborX,neighborY);
    if(neighborCrushable||candidateCrushable){
        if(!preparationResult)throw std::invalid_argument("Crushable neighbor requires result-bearing preparation");
        second=first;
    }
    if(preparationResult){
        preparationResult->services.curve64=std::uint8_t(neighborCrushable!=0||candidateCrushable);
        write(dw,0x64,preparationResult->services.curve64);
        preparationResult->services.shortTrack60=0;write(dw,0x60,0);
    }
    int track=first*8+second;m.track=track;write(dw,0x58,track);
    if(!data.transitions[std::size_t(track)].rawTrack){track=first*9;m.track=track;write(dw,0x58,track);}
    Coord head=next;const int count=(data.transitions[std::size_t(track)].flags&8)?2:1;
    if(count==2){
        (void)svc.wordCell(cell(next.x),cell(next.y));
        const auto [headX,headY]=directionOffset(second);
        head.x=add(head.x,headX*256);head.y=add(head.y,headY*256);
        const auto secondCell=svc.wordCell(cell(head.x),cell(head.y));
        const int result=admission?admission->check(secondCell,second,admissionLevel):(svc.admit(secondCell,second,admissionLevel),0);
        if(result){
            if(result==6&&residentRetry){
                if(!preparationFlag){
                    if(!preparation)throw std::invalid_argument("Ground Process resident scatter/close-enough outside domain");
                    if(close(2,false)){
                        clearHead(true);if(preparation->closeTarget())return;
                    }else{
                        const auto candidate=svc.wordCell(cell(head.x),cell(head.y));
                        preparation->scatter(candidate,elevated(candidate));
                    }
                    route(s,0,-1,aw);m.track=-1;write(dw,0x58,-1);head={};
                }else{
                    route(s,0,-1,aw);retry(residentRetry->secondPadding);
                    prepare(s,data,tick,padding,svc,w,gate,admission,residentRetry,false,movingWait,false,preparationResult);return;
                }
            }
            else if(result==2&&movingWait){
                prepare(s,data,tick,padding,svc,w,gate,admission,residentRetry,preparationFlag,movingWait,true,preparationResult);return;
            }
            else if(result!=3&&result!=7)throw std::invalid_argument("Ground Process second admission outside 0/3/7 domain");
            if(result==7){route(s,0,-1,aw);retry(padding);prepare(s,data,tick,padding,svc,w,gate,admission,residentRetry,false,movingWait,false,preparationResult);return;}
            if(result==3){(void)gate(cell(head.x),cell(head.y));route(s,0,-1,aw);m.track=-1;write(dw,0x58,-1);head={};}
        }
        if(!result)consume(s,count,aw);else route(s,23,-1,aw);
    }else consume(s,count,aw);
    s.nextX=cell(head.x);s.nextY=cell(head.y);
    write(w,0x450,signed32(std::uint16_t(s.nextX)|(std::uint32_t(std::uint16_t(s.nextY))<<16)));
    s.preparation57a=0;write(aw,0x57a,0);m.index=0;write(dw,0x5c,0);
    if(admission)clearHead();
    if(head==Coord{}&&admission){m.track=-1;write(dw,0x58,-1);route(s,0,-1,aw);if(preparationResult)preparationResult->services.zeroPercentage();else s.instancePercentage=0.;return;}
    m.head=head;m.driving=true;m.track=track;
    write(dw,0x63,1);write(dw,0x40,head.x);write(dw,0x44,head.y);write(dw,0x48,head.z);
    (void)svc.cell(head);
    const auto& raw=data.tracks.at(std::size_t(data.transitions[std::size_t(track)].rawTrack-1));
    if(raw.cellIndex>m.index){
        auto p=raw.points.at(std::size_t(raw.cellIndex));const auto& t=data.transitions[std::size_t(track)];
        if(t.flags&1)std::swap(p.x,p.y);
        if(t.flags&2)p.x=signed32(0u-std::uint32_t(p.x));
        if(t.flags&4)p.y=signed32(0u-std::uint32_t(p.y));
        svc.markOccupation({add(head.x,p.x),add(head.y,p.y),m.actor.position.z});
    }
    svc.markOccupation(head);
}
bool process(GroundDriveProcessState& s,const DriveData& data,int speed,
    int tick,int padding,const GroundDriveProcessServices& svc,
    const GroundStateStore& w,const GroundStateStore& rw,
    const std::function<bool(std::int16_t,std::int16_t)>& gate,
    const GroundDriveAdmissionServices* admission=nullptr,
    const GroundDriveResidentRetry* residentRetry=nullptr,MovingWaitBinding* movingWait=nullptr,
    bool advanceDefaultAdmission=false,const GroundDriveProcessResultServices* result=nullptr){
    if(movingWait&&!movingWait->services.failedRoute)throw std::invalid_argument("Moving resident Process requires explicit failed-route service");
    if(!svc.cell||!svc.wordCell||!svc.liveCell||(!gate&&!svc.reserve)||!svc.markNext||!svc.center||(!admission&&!svc.admit)||!svc.noRoute||!svc.markOccupation||!svc.squareRoot||
       !svc.advance.ground.floor||!svc.advance.ground.mark||!svc.advance.coordinateCell||!svc.advance.wordCell||
       !svc.advance.unmarkOccupation||!svc.advance.notify||!svc.advance.postCell||
       s.movement.actor.bridge79||s.route.back()!=-1||speed<0||speed>255||(admission&&s.preparation57a))
        throw std::invalid_argument("Ground Process services/state outside domain");
    if(!std::isfinite(s.percentage)||!std::isfinite(s.instancePercentage))
        throw std::invalid_argument("Ground Process nonfinite percentage");
    bool end=false;for(int d:s.route){if(d==-1)end=true;else if((end&&!admission)||d<0||d>7)throw std::invalid_argument("Ground Process route outside domain");}
    for(float n:svc.trackSpeed)if(!std::isfinite(n))throw std::invalid_argument("Ground Process nonfinite speed");
    if(!std::isfinite(svc.uphill)||!std::isfinite(svc.downhill))throw std::invalid_argument("Ground Process nonfinite slope factor");
    OriginalRounding rounding;
    observeDriveRamp(s.ramps,[&]{(void)svc.cell(s.movement.actor.position);return svc.cell(s.movement.actor.position).ramp;},tick,padding,rw);
    auto& m=s.movement;
    auto advanceServices=svc.advance;
    advanceServices.rejectedSwitchAdmission=[&](Coord target,int direction){
        (void)svc.cell(m.actor.position);const int level=svc.cell(m.actor.position).level;
        const auto c=svc.wordCell(cell(target.x),cell(target.y));
        if(admission){const int result=admission->check(c,direction,level);
            if(result!=0&&!(movingWait&&result==2))throw UnsupportedGroundAdmission(result);}
        else svc.admit(c,direction,level);
    };
    const auto advance=[&](bool suppress,int caller){
        if(m.driving&&m.track!=-1)s.instancePercentage=std::clamp(s.percentage,0.,1.);
        if(result)return result->advance(caller,suppress);
        if(advanceDefaultAdmission){
            const GroundDriveAdvanceAdmissionServices checked{svc.cell,svc.wordCell,admission->check};
            advanceWithOrdinaryAdmission(m,data,speed,s.percentage,tick,suppress,
                svc.advance,s.route[0],checked,w);
        }else advanceOrdinaryGroundDrive(m,data,speed,s.percentage,tick,suppress,advanceServices,w,s.route[0]);
        return false;
    };
    const auto prepareNext=[&]{
        PreparationResult output{*result};
        prepare(s,data,tick,padding,svc,w,gate,admission,residentRetry,true,movingWait,false,&output);
        return output.output;
    };
    const auto prepareLegacy=[&]{prepare(s,data,tick,padding,svc,w,gate,admission,residentRetry,true,movingWait);};
    if(m.track!=-1&&m.driving){
        const bool returned=advance(false,0);
        if(result&&(returned||!result->onMap7d))return false;
        if(m.track==-1&&(moving(s)||s.route[0]!=-1)&&(!result||!result->field5b9)){
            if(result&&result->hasTarget()&&result->targetKind()==15)
                throw std::invalid_argument("Process post-Advance terrain target remains unjoined");
            if(result){if(prepareNext()||!result->onMap7d)return false;}else prepareLegacy();
            (void)advance(true,1);if(result&&!result->onMap7d)return false;
        }
    }else{
        if(result&&result->idleTarget())return false;
        if(m.body.rotating(tick)){
            s.wasRotating=true;if(result)write(svc.advance.driveStore,0x62,1);
        }else{
            if(s.wasRotating){
                s.wasRotating=false;if(result)write(svc.advance.driveStore,0x62,0);
                svc.advance.notify(0);
                if(result&&(!result->onMap7d||result->flag76||result->flag7a))return false;
            }
            bool prepareNeeded=moving(s)||s.route[0]!=-1;
            if(result){
                prepareNeeded=false;
                if(!(result->mission()==5&&!moving(s)) && result->mission()!=16){
                    if(!moving(s)&&s.route[0]==-1){if(result->hasTarget())result->moveToTarget();}
                    else prepareNeeded=true;
                }
            }
            if(prepareNeeded){
                if(result){if(prepareNext()||!result->onMap7d)return false;}else prepareLegacy();
                (void)advance(false,2);if(result&&!result->onMap7d)return false;
            }
        }
    }
    if((m.body.rotating(tick)||(moving(s)&&m.head!=Coord{}&&currentSpeed(speed,s.instancePercentage)>0))&&tick%10==0){
        (void)svc.cell(m.actor.position);(void)svc.cell(m.actor.position);
    }
    if(s.destination==Coord{}&&m.head==Coord{}&&s.route[0]==-1&&s.instancePercentage>0.){
        if(result)result->zeroPercentage();else s.instancePercentage=0.;
    }
    return moving(s);
}
}
bool processAdvanceAdmittedOrdinaryGroundDrive(GroundDriveProcessState& s,const DriveData& data,int speed,
    int tick,int padding,const GroundDriveProcessServices& svc,
    const std::function<bool(std::int16_t,std::int16_t)>& gate,const GroundDriveAdmissionServices& admission,
    const GroundDriveResidentRetry& retry,GroundDriveMovingWaitState& wait,
    const GroundDriveMovingWaitServices& services,const GroundStateStore& w,const GroundStateStore& rw){
    if(!gate||!admission.check)throw std::invalid_argument("Advance-admitted Process requires gates/admission");
    MovingWaitBinding binding{{wait.start,wait.padding,wait.remaining},services};
    return process(s,data,speed,tick,padding,svc,w,rw,gate,&admission,&retry,&binding,true);
}
bool processMovingResidentOrdinaryGroundDrive(GroundDriveProcessState& s,const DriveData& data,int speed,
    int tick,int padding,const GroundDriveProcessServices& svc,
    const std::function<bool(std::int16_t,std::int16_t)>& gate,const GroundDriveAdmissionServices& admission,
    const GroundDriveResidentRetry& retry,GroundDriveMovingWaitState& wait,
    const GroundDriveMovingWaitServices& services,const GroundStateStore& w,const GroundStateStore& rw){
    if(!gate||!admission.check)throw std::invalid_argument("Moving resident Process requires gates/admission");
    MovingWaitBinding binding{{wait.start,wait.padding,wait.remaining},services};
    return process(s,data,speed,tick,padding,svc,w,rw,gate,&admission,&retry,&binding);
}
bool processOrdinaryGroundDrive(GroundDriveProcessState& s,const DriveData& data,int speed,
    int tick,int padding,const GroundDriveProcessServices& svc,
    const GroundStateStore& w,const GroundStateStore& rw){
    return process(s,data,speed,tick,padding,svc,w,rw,{});
}
bool processGatedOrdinaryGroundDrive(GroundDriveProcessState& s,const DriveData& data,int speed,
    int tick,int padding,const GroundDriveProcessServices& svc,
    const std::function<bool(std::int16_t,std::int16_t)>& gate,
    const GroundStateStore& w,const GroundStateStore& rw){
    if(!gate)throw std::invalid_argument("Ground Process requires a result-bearing gate check");
    return process(s,data,speed,tick,padding,svc,w,rw,gate);
}
bool processAdmittedOrdinaryGroundDrive(GroundDriveProcessState& s,const DriveData& data,int speed,
    int tick,int padding,const GroundDriveProcessServices& svc,
    const std::function<bool(std::int16_t,std::int16_t)>& gate,const GroundDriveAdmissionServices& admission,
    const GroundStateStore& w,const GroundStateStore& rw){
    if(!gate||!admission.check)
        throw std::invalid_argument("Ground Process requires result-bearing admission/gates");
    return process(s,data,speed,tick,padding,svc,w,rw,gate,&admission);
}
bool processResidentOrdinaryGroundDrive(GroundDriveProcessState& s,const DriveData& data,int speed,
    int tick,int padding,const GroundDriveProcessServices& svc,
    const std::function<bool(std::int16_t,std::int16_t)>& gate,const GroundDriveAdmissionServices& admission,
    const GroundDriveResidentRetry& retry,const GroundStateStore& w,const GroundStateStore& rw){
    if(!gate||!admission.check)
        throw std::invalid_argument("Ground Process requires result-bearing resident admission/gates");
    return process(s,data,speed,tick,padding,svc,w,rw,gate,&admission,&retry);
}
bool processResultOrdinaryGroundDrive(GroundDriveProcessState& s,const DriveData& data,int speed,
    int tick,int padding,const GroundDriveProcessServices& svc,
    const std::function<bool(std::int16_t,std::int16_t)>& gate,const GroundDriveAdmissionServices& admission,
    const GroundDriveResidentRetry& retry,const GroundDriveMovingWaitServices& waiting,
    const GroundDriveProcessResultServices& result,const GroundStateStore& w,const GroundStateStore& rw){
    if(!gate||!admission.check||!result.advance||!result.idleTarget||!result.mission||
       !result.hasTarget||!result.moveToTarget||!result.zeroPercentage||!result.finishEmptyPreparation||!result.targetKind)
        throw std::invalid_argument("Result Process requires complete explicit child bindings");
    if(const auto* p=result.preparation;p && (p->heightDivisor<=0||!p->findRoute||!p->permission||
       !p->resident||!p->allied||!p->passengers||!p->flags||!p->scatter||!p->setCounter||!p->closeTarget))
        throw std::invalid_argument("Preparation requires complete explicit child bindings and height divisor");
    MovingWaitBinding binding{result.wait,waiting};
    return process(s,data,speed,tick,padding,svc,w,rw,gate,&admission,&retry,&binding,false,&result);
}
}
