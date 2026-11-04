// @ref _?iffsize@?1??VQA_LoadFrame_Internal@@YIJPAUVQAHandleP@@J@Z@4KA=00b2af90
// VQA_LoadFrame_Internal00778950: stream chunks into the current frame, including loop rewinds.
#include "shared/vqa_player.hpp"
#include "shared/vqa_iff.hpp"
static long Load_CBF0(VQAHandleP *, unsigned long);
static long Load_CPL0(VQAHandleP *, unsigned long);
static long Load_VPT0(VQAHandleP *, unsigned long);
static long Load_VPTZ(VQAHandleP *, unsigned long);
long __fastcall Load_VQF(VQAHandleP *, unsigned long, char);
static long Load_SN2J(VQAHandleP *, unsigned long);

static long VQA_LoadLoop(VQAHandleP *vqap, long frame)
{
    long result=-1;
    bool skipcodebook=false;
    VQALoader *loader=&vqap->Loader;
    VQAHeader *header=&vqap->Header;
    VQAConfig *config=&vqap->Config;
    if(loader->CurFrame->Flags&VQAFRMF_LOADED) return -9;
    if(frame>=vqap->StopFrame || vqap->Foff==0) return -6;
    if((config->OptionFlags&VQAOPTF_AUDIO) && !(header->Flags&8)) return -6;
    if(header->ColorMode==0 && !VQA_IsFrameStartOfLoop(vqap,frame)) result=VQA_ReloadPalette(vqap,frame,1);
    if(result==-1) result=VQA_SeekGroup(vqap,frame,header->Groupsize,false,false,skipcodebook);
    loader->CurFrameNum=frame;
    if(result==-1) {
        long flags=0x20;
        if(skipcodebook) flags|=0x10;
        result=VQA_LoadFrame(vqap,flags);
    }
    return result;
}

static long VQA_MFCIIndexFromChunkID(VQAHandleP *vqap,unsigned long id)
{
    VQAMFCInfo::TABLE *table=vqap->MFCInfo.Table;
    unsigned long count=vqap->MFCInfo.Header.Count;
    for(unsigned long i=0;i<count;i++) { if(id==table[i].ChunkID) return i; }
    return -1;
}
static long VQA_MFCIReadData(VQAHandleP *vqap,unsigned long size,long index)
{
    VQALoader *loader=&vqap->Loader;
    VQAConfig *config=&vqap->Config;
    unsigned long padded=PADSIZE(size);
    VQAChunkCache *cache=&vqap->MFCInfo.Data2[index];
    unsigned long write_index=cache->WriteIndex;
    void *buffer=cache->Data[write_index].Buffer;
    cache->Data[write_index].Size=size;
    cache->Data[write_index].Frame=loader->CurFrameNum;
    ++write_index;
    if(write_index>=cache->Count) write_index=0;
    cache->WriteIndex=write_index;
    if(config->StreamHandler((VQAHandle *)vqap,VQACMD_READ,(int)buffer,padded)) return -4;
    loader->CurFrame->Flags|=VQAFRMF_CHUNKS;
    return -1;
}

static long VQA_MSCIIndexFromChunkID(VQAHandleP *vqap,unsigned long id)
{
    VQAMSCInfo::TABLE *table=vqap->MSCInfo.Table;
    unsigned long count=vqap->MSCInfo.Header.Count;
    for(unsigned long i=0;i<count;i++) { if(id==table[i].ChunkID) return i; }
    return -1;
}
static long VQA_MSCIReadData(VQAHandleP *vqap,unsigned long size,long index)
{
    VQALoader *loader=&vqap->Loader;
    VQAConfig *config=&vqap->Config;
    unsigned long padded=PADSIZE(size);
    VQAChunkCache *cache=&vqap->MSCInfo.Data2[index];
    unsigned long write_index=cache->WriteIndex;
    void *buffer=cache->Data[write_index].Buffer;
    cache->Data[write_index].Size=size;
    cache->Data[write_index].Frame=loader->CurFrameNum;
    ++write_index;
    if(write_index>=cache->Count) write_index=0;
    cache->WriteIndex=write_index;
    if(config->StreamHandler((VQAHandle *)vqap,VQACMD_READ,(int)buffer,padded)) return -4;
    loader->CurFrame->Flags|=VQAFRMF_CHUNKS;
    return -1;
}

long __fastcall VQA_LoadFrame_Internal(VQAHandleP *vqap,long flags)
{
    VQAConfig *config=&vqap->Config;
    VQALoader *loader=&vqap->Loader;
    VQADrawer *drawer=&vqap->Drawer;
    VQAFrameNode *curframe;
    VQAChunkHeader *chunk=&loader->CurChunkHdr;
    static unsigned long iffsize;
    int frame_loaded=0;
    bool loop_loaded=false;
    curframe=loader->CurFrame;
    long result;
    if(config->OptionFlags&VQAOPTF_LOOPS) {
        if(vqap->LoopIterations>0 || vqap->LoopIterations==-1) {
            if(loader->CurFrameNum>vqap->LoopEndFrameMode2) {
                long jump=vqap->LoopEndFrameJump;
                long old_end=vqap->LoopEndFrameMode2;
                long stopframe=vqap->StopFrame;
                if(jump!=-1) {
                    vqap->LoopEndFrameMode2=jump;
                    vqap->LoopEndFrameJump=-1;
                    vqap->StopFrame=jump;
                }
                if(loader->CurFrameNum!=vqap->LoopStartFrame0) {
                    loader->CurFrameNum=vqap->LoopStartFrame0;
                    result=VQA_LoadLoop(vqap,vqap->LoopStartFrame0);
                } else result=-1;
                if(result==-1 || result==-11) {
                    vqap->Flags|=VQADATF_LOOPED;
                    if(jump==-1) {
                        curframe->Flags|=VQAFRMF_LOOPED;
                        if(vqap->LoopIterations!=-1) vqap->LoopIterations--;
                    } else {
                        curframe->Flags|=VQAFRMF_LOOPJMP;
                        vqap->LoopEndFrame2=old_end;
                        vqap->LoopIterations=vqap->LoopIterationsJump;
                        vqap->LoopIterationsJump=-1;
                        vqap->Flags|=VQADATF_LOOPJMP;
                    }
                } else {
                    vqap->LoopEndFrameMode2=old_end;
                    vqap->LoopEndFrameJump=jump;
                    vqap->StopFrame=stopframe;
                    loader->CurFrameNum=vqap->LoopEndFrameMode2+1;
                }
                return result;
            }
        }
    }
    if(loader->CurFrameNum>vqap->StopFrame) {
        if(!(flags&2) && (config->OptionFlags&VQAOPTF_AUDIO) && !(config->OptionFlags&VQAOPTF_ALTAUDIO)) {
            if(CopyAudio(vqap)==-11) { vqap->Flags|=1; return -11; }
            vqap->Flags&=~1;
            vqap->Audio.Flags|=VQAAUDF_ISENDOFFILE;
        }
        return -2;
    }
    int skip;
    if((curframe->Flags&VQAFRMF_LOADED) && !(curframe->Flags&VQAFRMF_11)) { loader->WaitsOnDrawer++; return -9; }
    if(!(vqap->Flags&1)) {
        loader->FrameSize=0;
        curframe->Codebook=loader->FullCB;
    }
    while(frame_loaded==0) {
        if(!(vqap->Flags&1)) {
            if(config->StreamHandler((VQAHandle *)vqap,VQACMD_READ,(int)chunk,8)) return -2;
            iffsize=REVERSE_LONG(chunk->Size);
            loader->FrameSize+=iffsize;
        }
        skip=true;
        switch(chunk->ID) {
        case ID_VQFR:
            if((flags&0x1d)!=0x1d) {
                if(Load_VQF(vqap,iffsize,flags)!=-1) return -4;
                skip=false;
            }
            frame_loaded=true;
            break;
        case ID_VQFK:
            if((flags&0x1d)!=0x1d) {
                if(Load_VQF(vqap,iffsize,flags)!=-1) return -4;
                curframe->Flags|=VQAFRMF_KEY;
                skip=false;
            }
            frame_loaded=true;
            break;
        case ID_VQFL:
            if(!(flags&0x20)) {
                if(Load_VQF(vqap,iffsize,flags)!=-1) return -4;
                skip=false;
                loop_loaded=true;
                if((vqap->Header.Flags&0x10) && (flags&4)) frame_loaded=true;
            }
            break;
        case ID_CBF0:
            if(!(flags&16)) {
                if(Load_CBF0(vqap,iffsize)!=-1) return -4;
                
                skip=false;
            }
            break;
        case ID_CBFZ:
            if(!(flags&16)) {
                if(Load_CBFZ(vqap,iffsize)!=-1) return -4;
                
                skip=false;
            }
            break;
        case ID_CBP0:
            if(!(flags&8)) {
                if(Load_CBP0(vqap,iffsize)!=-1) return -4;
                
                skip=false;
            }
            break;
        case ID_CBPZ:
            if(!(flags&8)) {
                if(Load_CBPZ(vqap,iffsize)!=-1) return -4;
                
                skip=false;
            }
            break;
        case ID_CPL0:
            if(!(flags&1)) {
                if(Load_CPL0(vqap,iffsize)!=-1) return -4;
                curframe->Flags|=VQAFRMF_PALETTE;
                skip=false;
            }
            break;
        case ID_CPLZ:
            if(!(flags&1)) {
                if(Load_CPLZ(vqap,iffsize)!=-1) return -4;
                curframe->Flags|=VQAFRMF_PALETTE;
                skip=false;
            }
            break;
        case ID_VPT0:
        case ID_VPTD:
            if(!(flags&4)) {
                if(Load_VPT0(vqap,iffsize)!=-1) return -4;
                skip=false;
                
            }
            frame_loaded=true;
            break;
        case ID_VPKZ:
            if(!(flags&4)) {
                if(Load_VPTZ(vqap,iffsize)!=-1) return -4;
                skip=false;
                curframe->Flags|=VQAFRMF_KEY;
            }
            frame_loaded=true;
            break;
        case ID_VPTK:
            if(!(flags&4)) {
                if(Load_VPT0(vqap,iffsize)!=-1) return -4;
                skip=false;
                curframe->Flags|=VQAFRMF_KEY;
            }
            frame_loaded=true;
            break;
        case ID_VPTR:
            if(!(flags&4)) {
                if(Load_VPT0(vqap,iffsize)!=-1) return -4;
                skip=false;
                curframe->Flags|=VQAFRMF_RSDCOMP;
            }
            frame_loaded=true;
            break;
        case ID_VPRZ:
            if(!(flags&4)) {
                if(Load_VPTZ(vqap,iffsize)!=-1) return -4;
                skip=false;
                curframe->Flags|=VQAFRMF_RSDCOMP;
            }
            frame_loaded=true;
            break;
        case ID_VPTZ:
        case ID_VPDZ:
            if(!(flags&4)) {
                if(Load_VPTZ(vqap,iffsize)!=-1) return -4;
                skip=false;
                
            }
            frame_loaded=true;
            break;
        case ID_SND0:
            if(!(flags&2)) {
                if((config->OptionFlags&VQAOPTF_AUDIO) && !(config->OptionFlags&VQAOPTF_ALTAUDIO)) {
                    if(CopyAudio(vqap)==-11) { vqap->Flags|=1; return -11; }
                    else vqap->Flags&=~1;
                    if(Load_SND0(vqap,iffsize)!=-1) return -4;
                    skip=false;
                }
            }
            break;
        case ID_SNA0:
            if(!(flags&2)) {
                if((config->OptionFlags&VQAOPTF_AUDIO) && (config->OptionFlags&VQAOPTF_ALTAUDIO)) {
                    if(CopyAudio(vqap)==-11) { vqap->Flags|=1; return -11; }
                    else vqap->Flags&=~1;
                    if(Load_SND0(vqap,iffsize)!=-1) return -4;
                    skip=false;
                }
            }
            break;
        case ID_SND1:
            if(!(flags&2)) {
                if((config->OptionFlags&VQAOPTF_AUDIO) && !(config->OptionFlags&VQAOPTF_ALTAUDIO)) {
                    if(CopyAudio(vqap)==-11) { vqap->Flags|=1; return -11; }
                    else vqap->Flags&=~1;
                    if(Load_SND1(vqap,iffsize)!=-1) return -4;
                    skip=false;
                }
            }
            break;
        case ID_SNA1:
            if(!(flags&2)) {
                if((config->OptionFlags&VQAOPTF_AUDIO) && (config->OptionFlags&VQAOPTF_ALTAUDIO)) {
                    if(CopyAudio(vqap)==-11) { vqap->Flags|=1; return -11; }
                    else vqap->Flags&=~1;
                    if(Load_SND1(vqap,iffsize)!=-1) return -4;
                    skip=false;
                }
            }
            break;
        case ID_SND2:
            if(!(flags&2)) {
                if((config->OptionFlags&VQAOPTF_AUDIO) && !(config->OptionFlags&VQAOPTF_ALTAUDIO)) {
                    if(CopyAudio(vqap)==-11) { vqap->Flags|=1; return -11; }
                    else vqap->Flags&=~1;
                    if(Load_SND2(vqap,iffsize)!=-1) return -4;
                    skip=false;
                }
            }
            break;
        case ID_SNA2:
            if(!(flags&2)) {
                if((config->OptionFlags&VQAOPTF_AUDIO) && (config->OptionFlags&VQAOPTF_ALTAUDIO)) {
                    if(CopyAudio(vqap)==-11) { vqap->Flags|=1; return -11; }
                    else vqap->Flags&=~1;
                    if(Load_SND2(vqap,iffsize)!=-1) return -4;
                    skip=false;
                }
            }
            break;
        case ID_SN2J:
            if(!(flags&2)) {
                if((config->OptionFlags&VQAOPTF_AUDIO) && !(config->OptionFlags&VQAOPTF_ALTAUDIO)) {
                    if(Load_SN2J(vqap,iffsize)!=-1) return -4;
                    skip=false;
                }
            }
            break;
        default: {
            long index=VQA_MFCIIndexFromChunkID(vqap,chunk->ID);
            if(index>=0) {
                if(VQA_MFCIReadData(vqap,iffsize,index)!=-1) return -4;
                skip=false;
                break;
            }
            index=VQA_MSCIIndexFromChunkID(vqap,chunk->ID);
            if(index>=0) {
                if(VQA_MSCIReadData(vqap,iffsize,index)!=-1) return -4;
                skip=false;
                break;
            }
            break;
        }
        }
        if(skip==true) {
            if(config->StreamHandler((VQAHandle *)vqap,VQACMD_SEEK,1,PADSIZE(iffsize))) return -6;
        }
    }
    if(loader->CurFrameNum>0 && loader->FrameSize>loader->MaxFrameSize) loader->MaxFrameSize=loader->FrameSize;
    if(VQA_IsFrameStartOfLoop(vqap,loader->CurFrameNum) && !(flags&0x20) && !loop_loaded) {
        loader->FullCB=loader->CurCB->Prev;
        curframe->Codebook=loader->FullCB;
    }
    if(!(flags&4)) {
        curframe->FrameNum=loader->CurFrameNum;
        loader->LastFrameNum=loader->CurFrameNum;
        loader->PrevCB=curframe->Codebook;
        curframe->Flags|=VQAFRMF_LOADED;
        loader->CurFrame=curframe->Next;
    }
    loader->CurFrameNum++;
    return -1;
}

static long Load_SN2J(VQAHandleP *vqap,unsigned long size)
{
    VQAAudio *audio=&vqap->Audio;
    VQAConfig *config=&vqap->Config;
    unsigned long padded=PADSIZE(size);
#pragma pack(push,1)
    struct JumpState { unsigned short index; unsigned long predicted; unsigned short index2; unsigned long predicted2; } data;
#pragma pack(pop)
    if(!(config->OptionFlags&VQAOPTF_AUDIO) || audio->Buffer==0) {
        if(config->StreamHandler((VQAHandle *)vqap,VQACMD_SEEK,1,padded)) return -6;
        return -1;
    }
    if(padded<=sizeof(data)) {
        if(config->StreamHandler((VQAHandle *)vqap,VQACMD_READ,(int)&data,padded)) return -4;
    } else return -4;
    audio->ADPCM_Info.Predicted=data.predicted;
    audio->ADPCM_Info.Index=data.index;
    if(vqap->Channels==2) {
        audio->ADPCM_Info.Predicted2=data.predicted2;
        audio->ADPCM_Info.Index2=data.index2;
    }
    return -1;
}
