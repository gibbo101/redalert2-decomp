class Target_5d1d20 { public: virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual unsigned int target(unsigned int p0); };extern "C" unsigned int global_5d1d20_b25bb0;
class Leaf_5d1d20 {public: unsigned int get(unsigned int a1);};
unsigned int Leaf_5d1d20::get(unsigned int a1) {return ((Target_5d1d20*)(global_5d1d20_b25bb0))->target((unsigned int)(a1));}
