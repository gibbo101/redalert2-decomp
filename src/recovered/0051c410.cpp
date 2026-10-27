extern "C" unsigned char receiver_51c410[];
extern "C" unsigned char argument_51c410[];
extern "C" unsigned int __fastcall request_51c410(unsigned int ecx_word,unsigned int edx_word,unsigned int stackword0,unsigned int stackword1);
extern "C" void __cdecl recover_51c410() { request_51c410((unsigned int)receiver_51c410, 0, (unsigned int)argument_51c410, 0x1ac4u); }
