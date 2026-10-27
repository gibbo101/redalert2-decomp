// Straw: a pull-style data stream (Westwood's Straw).
//
// Name from RTTI (vtable 0x0079E9F8); methods in Straw.cpp (0x0069B010+).
// A straw draws data from the straw it is connected to (ChainTo); derived
// straws transform the data on the way (file, compression, encryption...).
// Connections are kept two-way so either end can disconnect cleanly.
#ifndef RA2_SHARED_STRAW_HPP
#define RA2_SHARED_STRAW_HPP

class Straw {
public:
    Straw() : ChainTo(0), ChainFrom(0) {}
    virtual ~Straw();                                   // slot 0
    virtual void Get_From(Straw *straw);                // slot 1
    void Get_From(Straw &straw) { Get_From(&straw); }
    virtual int Get(void *buffer, int length);          // slot 2

    Straw *ChainTo;     // +0x04 straw data is drawn from
    Straw *ChainFrom;   // +0x08 straw drawing from this one
};

#endif
