extern "C" unsigned char receiver_51c040[];
extern "C" unsigned char argument_51c040[];
extern "C" unsigned int __fastcall request_51c040(unsigned int ecx_word,unsigned int edx_word,unsigned int stackword0,unsigned int stackword1);
extern "C" void __cdecl recover_51c040() { request_51c040((unsigned int)receiver_51c040, 0, (unsigned int)argument_51c040, 0x1a4cu); }
