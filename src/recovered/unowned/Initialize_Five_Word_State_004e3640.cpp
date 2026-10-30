// Original004E3640: initializes five32-bit state words and returns their base pointer.
// ABI hypothesis: ECX points at writable state, EAX returns that pointer, no stack arguments.
// No original incoming references are known; class ownership/constructor identity remains unknown.
extern "C" int *__fastcall Initialize_Five_Word_State_004e3640(int *state)
{
    state[0]=0;
    state[1]=1;
    state[2]=0;
    state[3]=0;
    state[4]=0;
    return state;
}
