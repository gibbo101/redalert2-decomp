extern "C" unsigned char receiver_51c780[];
extern "C" unsigned char argument_51c780[];
extern "C" unsigned int __fastcall request_51c780(unsigned int ecx_word,unsigned int edx_word,unsigned int stackword0,unsigned int stackword1);
extern "C" void __cdecl recover_51c780() { request_51c780((unsigned int)receiver_51c780, 0, (unsigned int)argument_51c780, 0x1bc1u); }
