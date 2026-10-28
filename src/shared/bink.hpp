// The Bink SDK entry points the game imports from binkw32.dll (RAD Game
// Tools; stdcall C functions bound through the IAT, manifests/imports.json).
// Parameter types are those of the public SDK header, simplified.
#ifndef RA2_SHARED_BINK_HPP
#define RA2_SHARED_BINK_HPP

struct BinkHandleSize;

#define BINK_IMPORT extern "C" __declspec(dllimport)

BINK_IMPORT int __stdcall BinkSetSoundSystem(void *open, unsigned long param);
BINK_IMPORT void *__stdcall BinkOpenDirectSound(unsigned long param);
BINK_IMPORT char *__stdcall BinkGetError();
BINK_IMPORT BinkHandleSize *__stdcall BinkOpen(char const *name, unsigned flags);
BINK_IMPORT void __stdcall BinkSetVolume(BinkHandleSize *bink, int volume);
BINK_IMPORT void __stdcall BinkClose(BinkHandleSize *bink);
BINK_IMPORT unsigned __stdcall BinkDDSurfaceType(void *surface);
BINK_IMPORT void __stdcall BinkGoto(BinkHandleSize *bink, unsigned frame, int flags);
BINK_IMPORT int __stdcall BinkPause(BinkHandleSize *bink, int pause);
BINK_IMPORT void __stdcall BinkNextFrame(BinkHandleSize *bink);
BINK_IMPORT int __stdcall BinkCopyToBuffer(BinkHandleSize *bink, void *dest, int destpitch, unsigned destheight,
                                           unsigned destx, unsigned desty, unsigned flags);
BINK_IMPORT int __stdcall BinkDoFrame(BinkHandleSize *bink);
BINK_IMPORT int __stdcall BinkWait(BinkHandleSize *bink);

#endif
