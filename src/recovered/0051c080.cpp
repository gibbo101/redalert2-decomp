extern "C" unsigned char receiver_51c080[];
extern "C" unsigned char argument_51c080[];
extern "C" unsigned int __fastcall request_51c080(unsigned int ecx_word,unsigned int edx_word,unsigned int stackword0,unsigned int stackword1);
extern "C" void __cdecl recover_51c080() { request_51c080((unsigned int)receiver_51c080, 0, (unsigned int)argument_51c080, 0x1a50u); }
