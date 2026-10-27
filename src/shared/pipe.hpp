// Pipe: a push-style data stream (Westwood's Pipe).
//
// Name from RTTI (vtable 0x0079EA20); methods in Pipe.cpp (0x0060EA60+).
// A pipe passes the data put into it on to the pipe it is connected to
// (ChainTo); derived pipes transform it on the way. Flush pushes buffered
// data onward; End finishes the stream.
#ifndef RA2_SHARED_PIPE_HPP
#define RA2_SHARED_PIPE_HPP

class Pipe {
public:
    Pipe() : ChainTo(0), ChainFrom(0) {}
    virtual ~Pipe();                                    // slot 0
    virtual int Flush();                                // slot 1
    virtual int End() { return Flush(); }               // slot 2 (code shared at 0x0046CB80)
    virtual void Put_To(Pipe *pipe);                    // slot 3
    void Put_To(Pipe &pipe) { Put_To(&pipe); }
    virtual int Put(void const *source, int length);    // slot 4

    Pipe *ChainTo;      // +0x04 pipe data is passed to
    Pipe *ChainFrom;    // +0x08 pipe passing data to this one
};

#endif
