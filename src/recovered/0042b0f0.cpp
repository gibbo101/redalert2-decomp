class Append_42b0f0 {
 virtual void slot0(); virtual void slot1(); virtual unsigned char grow(int,unsigned int*);
 unsigned int* items; int capacity; unsigned char reserved12; unsigned char owns; unsigned int count; int growth;
 public: unsigned char get(const unsigned int* value);
};
unsigned char Append_42b0f0::get(const unsigned int* value) {
 if((int)count >= capacity) {
  if((!owns && capacity!=0) || growth<=0 || !grow((int)((unsigned int)capacity+(unsigned int)growth),0)) return 0;
 }
 unsigned int old=count;
 unsigned int* target=items;
 count=old+1u;
 target[old]=*value;
 return 1;
}
