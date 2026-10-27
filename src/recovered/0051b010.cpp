extern "C" unsigned char receiver_51b010[];
extern "C" unsigned char argument_51b010[];
extern "C" unsigned int __fastcall request_51b010(unsigned int ecx_word,unsigned int edx_word,unsigned int stackword0,unsigned int stackword1);
extern "C" void __cdecl recover_51b010() { request_51b010((unsigned int)receiver_51b010, 0, (unsigned int)argument_51b010, 0x172fu); }
