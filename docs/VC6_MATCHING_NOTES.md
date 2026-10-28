# VC6 matching notes

Practical rules learned while matching readable source against the original
with `diff_candidate.py`. Each was confirmed by a byte-exact result; they are
starting points for the next class, not guarantees.

## Types

- Westwood flags such as `opened` are `int`, not `bool` (`mov dword ptr` vs
  `mov byte ptr` stores). Class members that are flags are `bool`.
- A predicate whose callers test `al` returns `bool` (`Is_Open`,
  `Is_Available`); one whose callers test `eax` returns `int`.
- Stack bytes in `ret N` fix the parameter list; doubles and 64-bit values
  take 8 bytes.

## Expressions and statement order

- `x = c ? a : b` evaluates `a` first, then compares and conditionally loads
  `b`. Pick the operand order that reproduces the original's first load:
  `size >= room ? room : size` gives `mov edi, room; cmp size, room; jge`.
- Comparison operand order follows the source (`a > b` vs `b < a`).
- Assignment order is kept: `buffer += n; size -= n;` and the reverse
  compile differently. So does declaration-with-initializer order of locals.
- A value returned from two branches that ends in one register is often a
  parameter reused as the result (`size = total; ... return size;`).

## Control flow

- `if (c) { A } else { B }` lays out A first. When the original jumps far
  for the common case, the source tested the opposite condition first
  (`if (UseBuffer) { ... } return RawFileClass::Seek(...)`).

## Inlining and translation units

- `/Ob2` inlines across functions of one translation unit, including
  functions defined later in it (`RawFileClass::Close` into `Is_Available`)
  and `inline` helpers with no out-of-line copy (`Raw_Seek`). Accept a class's
  methods as one plan so they compile as one unit, in address order.
- A qualified call (`RawFileClass::Open(...)`) is a direct, devirtualized
  call; an unqualified call on `this` stays virtual.
- An inlined base-class accessor (`RawFileClass::Is_Open` inside a derived
  method) appears as a direct member test; write the member test when the
  accessor has a separate accepted copy.
- A compiler-generated function (scalar deleting destructor) is emitted in
  every object file that needs the vtable; the linker kept the first copy.
  When the kept copy calls the destructor instead of inlining it, it came from
  another file; `#pragma auto_inline(off)` around the destructor reproduces
  it in the class's own unit (Straw, Pipe).
- Whether `/Ob2` expands a function defined later in the unit varies: it
  does in wwmous.cpp and MPMath (`mp_quo_digit`), but XSurface's 7-argument
  `Copy_From` (into 0x774F00) and DSurface's `Restore_Check` (into Lock and
  Unlock) only expand when declared `inline`. Marking a function `inline`
  can also suppress an out-of-line copy the original kept (wwmous.cpp
  `Unblock_Mouse`); an explicit trailing `return;` kept `Calc_Confining_Rect`
  from being expanded into the constructor.
- Inline header members are emitted at the end of the unit; non-virtual
  accessors the original emits mid-unit were defined in the .cpp.
- `/Ob2` gives each caller one cumulative inline budget. The budget is
  max(floor, k x the caller's own size): plain statements, init-list entries
  and out-of-line calls in the caller all raise it. With 60 equal callees,
  24 + 0.73 per extra arithmetic statement are inlined; a simple store adds
  about 0.27 and an out-of-line call about 0.18. Small functions sit at the
  floor, so their own size does not matter. Later statements count as much as
  earlier ones (the size is the whole function's). Each site inlines when its
  cost still fits; it is not "stop at the first miss".
- **Direct sites first, nested sites after.** VC6 decides every direct call
  in the caller (in source order) before any call that appears inside an
  expansion. Then it decides the depth-2 calls in source order, and so on. So
  any extra direct site pushes nested expansions out of line, even one placed
  after them in the source. Examples: a DynamicVectorClass member's
  VectorClass base constructor, a helper's own callees, ToolTip() inside an
  inlined Tab helper. Examples:
  - FootClass ctor 0x4C2930 is byte-exact with one extra empty direct inline
    call anywhere in the body, at the start or after the two Adds (no natural
    source found yet). The same draft also has to drop `unknown_424(0)`.
  - A helper that wraps a call turns that call into a nested site. This is
    why MouseClass Load's `New_Cell_Table()` keeps the template ctor out of
    line. The helper works the same whether it is defined before or after the
    caller; VC6 does not "compile it first".
  - Swizzle_Pointer wrappers are direct sites. They spend budget that the
    nested sites would otherwise get.
- What costs budget: any direct call to an inline function, including an
  empty one; an empty constructor or destructor of a *local* object; a
  member constructor that has code. Empty *member* constructors (`Cell()
  {}`, `E() {}`, `~E() {}` members) cost nothing. A local with an empty
  destructor costs about as much as an empty call. A member array of a class
  with an empty constructor (`Point2D InlinePoints[6]`) is expensive: once
  the budget runs out, it becomes a `??_H` vector-constructor-iterator call
  that no original has.
- Individual size cap: a non-template function without `inline` is
  auto-inlined only while it is small: about 5 "statement + if" pairs in the
  lab. Writing `inline`, defining the function in its class, or making it any
  template member (in-class, out-of-class, with or without `inline`) lifts
  the cap to about 60-120 pairs. Spelling does not change the per-site cost.
  The definition's position (before or after the caller) changes neither the
  cap nor the cost. The earlier "a later-defined function only expands when
  declared inline" cases are this size cap.
- `#pragma inline_depth(1)` stops every nested expansion: FrameTimerClass
  `operator long` and VectorClass::Length become calls. It cannot explain a
  unit in which some nested sites inline.
  (Lab and the status of the open cases: `build/class-work/Inline17/`.)
- RA2's object `Load` functions fix
  up each pointer through an inline wrapper,
  `template<class T> inline HRESULT Swizzle_Pointer(T *&p) { return
  SwizzleManager.Swizzle((void **)&p); }`, one expansion per pointer; that
  pushes `IndexClass::Search_For_Node`/`Increase_Table_Size` out of line in
  Load while the constructor still inlines them (UnitClass::Load 47 → 98).
  The number of extra sites needed differs per Load (TerrainClass needs
  exactly one more, through an inline `Add_Object_Index` wrapper over
  `Add_Index`; FactoryClass needed only the swizzle wrapper). Empty member
  constructors do not count. Register choice is separate: a trailing real use
  of `this` changes which register holds it, empty inline calls do not.
- A bit read into a dead argument's stack slot (`mov dl,[esi+0x14]; and dl,1;
  mov [esp+arg],dl`) instead of `test byte ptr [esi+0x14],1` comes from a
  `bool` local declared *before* the condition and assigned inside it
  (`bool active; if (p) active = p->bit; if (!p || !active ...)`); a `bool`
  initialized inside a block does not reproduce it (AircraftClass slot 101).
  When the bit belongs to a member pointer, copy the pointer into a local
  first, inside the enclosing test (InfantryClass slot 219).
- Stack-slot assignment follows scope nesting, not declaration order:
  BuildingClass::Load only matches with its body inside `if
  (SUCCEEDED(result)) { int count; ... } return result;`.
- Access members through the real class, not a cast view of another type
  (`House_View(House)->...`): the extra cast changes register allocation.
- Call arguments are evaluated right to left; an inline helper's argument
  order decides which expression is computed first.
- A `bool` comparison result returned with a bare `setcc al` comes from
  `return x <= 0 ? true : false;`; the branchless "object if it is a
  building, else null" (`sub; neg; sbb; not; and`) from an early null return
  followed by a ternary (SidebarClass StripClass sort and filters).
- In an additive chain a ternary operand is evaluated first; a local assigned
  by `if/else` keeps the source order. SidebarClass's strip row count only
  matches as `int extra; if (flag) extra = 26; else extra = 18; return (y +
  height - top - extra - 7) / 50;` (13 functions fell to this one rule).
- With a local object that has a destructor (a COM smart pointer), the
  budget pressure that pushes its helper expansions out of line comes only
  from direct inline calls made while that object is alive, a second named
  local with a destructor (even an empty one), or an extra `return` path in
  its scope. Plain calls, temporaries, calls nested inside other inline
  functions and inline calls made before the object exists do not count. One
  or two extra sites push one expansion out of line, three or four push two
  (micro-tests in build/class-work/ComPtr/w/micro). The kind of pressure
  decides which expansion goes first: a second named local with a destructor
  pushes out a query's failure-path release, while extra inline calls, extra
  returns and dead comparisons push out the success path. The locomotor Saves
  behave as if one such local exists, InfantryClass slot 288 as if two do;
  no natural source for them is known yet (open).
- Under `__fastcall` a `float` parameter is never passed in a register, so
  the next integer parameter takes `edx`; with right-to-left evaluation the
  `mov edx, imm` then lands between the stack pushes. The sound call 0x713DB0
  is `void __fastcall (int sound, float volume, int priority, void *object)`;
  declaring the int before the float moves `mov edx` after both pushes.
- A two-dimensional table indexed as `table[row][col]` (`[][4]`) gives
  `lea eax,[edx+ecx*4]; mov eax,[eax*4+base]`; a flattened index gives a shift.
- `test` then `jbe` comes from an unsigned `> 0` test, not `!= 0`.
- A `__fastcall` argument passed through untouched keeps the original's `ecx`;
  many seeds miss that parameter entirely.
- `return value += v;` with a `float` return gives `fst` instead of `fstp`.
- A by-reference argument whose temporary is stored *after* `push &temp`
  comes from an rvalue argument (`List.ID(this)` inside a member, `&*node`);
  a named local or a plain parameter stores the temporary before the push.
- The order of the terms in a packed-pixel expression sets the order of the
  channel loads; try all six permutations when a pixel build misses.
- A function out of line at every call site in its unit but compiled in that
  unit is an ordinary non-`inline` function at its own address position; VC6
  still inlines it where its budget allows. `#pragma auto_inline(off)` is only
  for a function the original never inlines anywhere in the unit.
- Keep a local copy of a pointer passed by reference to a call
  (`T *pointer = item; list.Delete(pointer); delete item;`) to keep `item` in
  a callee-saved register across the call.
- 64-bit values stored as two halves (`unsigned __int64` local) reproduce the
  original's split store order; a tail `jmp` into a `this`-taking callee needs
  the callee declared `__fastcall` rather than as a member.
- A counter the original reloads around an increment (load, inc, store, and
  sometimes a reload after a test) is `volatile`.
- `return field = -1;` gives `or eax,-1` then the store.
- Evaluate a lookup into a local before a multi-argument `__fastcall` call,
  or it is evaluated after the stack arguments are pushed.
- Copy-initialize from an explicit temporary (`CellStruct spot =
  CellStruct(...)`) to get the original's build-a-temporary-then-copy
  pattern; direct construction or member assignment does not.
- Split chained constant multiplications (`x *= a; x *= b;`) to keep two
  `fmul`s; one expression folds the constants.
- An init-style function starting with `mov eax,ecx` is a constructor that
  returns `this`; `while (index--)` gives `mov esi,eax; dec esi; test eax`.
- Small functions defined *later* in the unit are still expanded inline
  (XSurface Copy_From, RadSiteClass::AI → Update_Light, Matrix3D Translate).
  Splitting a body into later-defined helpers keeps both the inline
  expansions and the out-of-line copies.
- Switch statements place their jump table and byte index table directly
  after the code; accept such a function with a plan `body_bytes` covering
  code and tables.
- Some out-of-line functions are never called (inlined everywhere): they have
  no entry references and are accepted with alignment-bounded entry evidence.

- A small helper written as an inline function and the same helper written as
  a `#define` macro compile differently: SHA's rotate only matches as an
  inline function.
- Pass-by-value structs change argument passing: RLE_Blit only matches when
  its last parameter is an 8-byte struct with a constructor (`BlitPair`), not
  two ints, an `__int64` or a 12-byte struct.
- A template member that the original implements in hand-written assembly is
  still instantiated generically by VC6 even when the specialization is only
  declared; the generic COMDAT is recorded as kept elsewhere (bound to the
  assembly entry).
- String literals are verified against the original bytes at their bound
  address; a literal whose text differs is refused even when the code matches
  (`"?:"`, not `"CD"`, in CDFileClass::Set_Search_Drives).

## Classes and virtual tables

- Overloaded virtual functions share the vtable position of the first
  overload, in reverse declaration order: declare each overload set
  last-slot-first (Surface).
- A class with an implicit destructor does not store its own vptr in the
  scalar deleting destructor; a user-declared empty `~Class() {}` does
  (BSurface).
- Westwood nests per-class control enums (`LCWPipe::CompControl`); the nesting
  is visible in constructor manglings.
- `memset` is an intrinsic (`rep stosd`) only when declared and listed in
  `#pragma intrinsic` (`shared/crt_string.hpp`, `shared/crt_memory.hpp`).

## Libraries and imports

- Win32 calls go through `__declspec(dllimport)` (`shared/win32_api.hpp`).
- `strcmp` is an intrinsic at `/O2` (expanded inline); `memmove` is a call.
- `operator new`, `operator delete`, `_strdup`, `free` and `memmove` are bound
  through `manifests/symbols.json`.

## Register allocation

Derived from controlled experiments with the real compiler (Regalloc27,
2026-10-27; lab tools in the ignored build/class-work/Regalloc27/).

- VC6 colours def-use webs (not source variables) greedily by priority; each
  takes the first of esi, edi, ebx, ebp not held by an interfering web already
  coloured, else a stack slot (reloaded into eax at each use inside a loop).
  Values not live across a call use eax/ecx/edx. Reusing a variable for
  disjoint values gives separate webs; a dead store is dropped.
- Priority is the reference count: a def or use is 1, `x += y` / `++x` is 1 in
  total, a use inside an if is about 0.5 (nested ifs do not compound), a use
  inside a loop about 1.4 (depth 1), 2.5 (depth 2), 5 (depth 3). The
  instruction length of the range does not count.
- Ties go to the web spanning fewer basic blocks, then to the one *assigned*
  first. Declaration order and scope nesting alone change nothing; reordering
  independent initialisations does.
- Parameters are live from their first use, not from entry; `this` is defined
  at entry (`mov esi, ecx`) and wins ties. Copying a parameter into a local at
  entry moves its start earlier.
- `char`/`bool` locals live across calls can only use ebx (bl); a second one
  goes to the stack even with esi/edi free. `short` can use any register.
- A copy whose source dies is coalesced with it and their counts add
  (`for (int c = x; ...)` versus looping on `x` changes coalescing). A loop
  index unused in the body becomes a low-priority countdown temporary.
- Constant 0 is cached in a register only if an already-saved callee-saved
  register is free (it never causes a new push); its range runs to the last 0
  it could serve, including byte compares, so it can push a pointer out of ebx.
- A global esi/edi permutation means two long webs are tied or near-tied; a
  statement reorder that changes coalescing can flip all of it.
- Legitimate knobs: order of independent initialisations, a separate copy
  variable versus the variable itself, reading a field into a local once versus
  re-reading, conditional versus unconditional uses, char/bool versus int.
  Dummy uses, volatile, `register`, dead code and allocation-only casts are
  steering and are refused.

## Call-argument scheduling

Derived from controlled experiments with the real compiler (Sched29, 2026-10-27; lab in
the ignored build/class-work/Sched29/).

- Without scheduling (/G6) VC6 pushes arguments right to left, computes each address
  (`lea eax, local`) just before its push and loads ecx (this) last. /G5 moves an address
  `lea` up by one push to pair it and hoists argument memory loads; /G3, /G4, /GB and no
  /G schedule identically.
- In a `__fastcall` function (free or static member), after a callee-pops call (thiscall,
  virtual, stdcall or fastcall, even without arguments) the next call's register setups
  (`lea ecx, object`, `lea eax, &local`, `mov ecx/edx, imm`) come before all of its pushes:
  `call; lea ecx, file; push "ART.INI"; call ctor`; `lea eax, file; mov ecx, ArtINI;
  push 0; push 0; push eax`; `mov edx, flag; lea ecx, result; push getter; call Create`.
  Other callers push first. An `add esp` after a cdecl call has the same effect in every
  caller; a cdecl call without arguments does not. The convention of the function being
  compiled decides, not the callee's or an inlined function's.
- So a register-first setup in a free or static function without parameters (whose call
  sites cannot show the convention) is evidence that it is `__fastcall` (Read_Art_INI,
  Coop_Camp_Unique_ID, 0x6525F0, Conflict::Init_Options).
- A temporary built by an out-of-line constructor and passed to a `T const &` parameter is
  pushed as the constructor's return value (`push eax`) when the source casts explicitly
  (`Add(T(x))`) and as a fresh `lea` of the temporary when the conversion is implicit
  (`Add(x)`). The implicit form also enlarges the caller (more inline budget).
- Independent global stores are sunk towards the next call (between `mov ecx` and `call`);
  their source position before a call does not show in the order.

## Free and charged inline callees, block placement (Study37)

- Free and charged callees (Study37). A callee whose body is at most two plain stores, or a
  single call statement whose result is unused, is expanded at every site and costs no
  budget (it goes out of line only at the caller's absolute size cap). Anything larger is
  charged its whole size, not the excess: one more node (a discarded read, a discarded
  returned reference such as `{ Set(x, y); }` with `Cell &Set`) turns a free two-store
  constructor into one that runs out after 78% of a table. Three stores (CoordStruct, Rect)
  are always charged. An original out-of-line call to a tiny constructor means the original
  constructor was charged (Cell 0x0042AD30: Map tables 288/369, 241/309, 8/40, 7/42, and
  DynamicVectorClass<ZoneConnectionClass>::Resize 0x0056B330 calling it for To).
- The budget is proportional to the caller's size (a fixed fraction of equal sites inlines for
  any table length) up to an absolute cap past which the inlined count falls as the caller
  grows. A callee's cost is its own unexpanded IL; nested sites are decided after all direct
  ones and get only what is left, except free callees, which always expand.
- A dynamic initializer is `_$E(n+1): jmp _$E(n)` for large objects; small ones are expanded
  into the .CRT$XCU entry itself, which makes their constructor calls depth-2 sites with only
  the entry's floor budget (Map 0x0055B520: 8 of 40 constructions inline).
- Commutative operand order (an addition's operands, two virtual calls in an inlined
  `a * f() + b * g()`) and some schedules are tie-breaks that move when an earlier inline
  expansion in the same function creates more or fewer temporaries (a nested call's
  parameters). A shared inline-header change can therefore alter accepted functions that
  never use the changed path; check it with a whole-tree compile (Study37 w/impact.py).
- In an additive chain every if/else spelling of a conditional term gives the same canonical
  order `(a - c) - extra`; a ternary gives `(a - extra) - c`, and a ternary in a `for`
  condition makes VC6 rotate the loop (condition copied to the bottom).


- An early return guarded by one test stays inline (`jne cont; epilogue`); one guarded by a
  short-circuit chain (`if (p == 0 || !p->flag) return x;`) is laid out after the following
  code. The original's single inline return block reached by both tests (`test p; je R;
  ...; jne cont; R: epilogue`) comes from evaluating the condition into a bool first:
  `bool ok = p != 0 && p->flag; if (!ok) return x;` or `ok = false; if (p) ok = p->flag;
  if (!ok) return x;` (jump threading). TechnoClass 0x6D4180, slot 175 0x6C15D0.
- `return 0` right after a `test eax,eax` branch reuses eax instead of `xor eax,eax` unless the
  return block is shared: identical return blocks are tail-merged, and the shared copy keeps
  the xor.

## Stack frame layout (Study42)

Derived from controlled experiments with the real compiler (Study42, 2026-10-27; lab in
the ignored build/class-work/Study42/, `f.sh` prints a function's frame map).

- Frame variables (address-taken locals, objects, temporaries, spilled webs) are sorted by
  size ascending, then by the number of instructions referencing them in the final code (a
  loop does not weigh more), then (usually, not always) by whose last reference comes
  first. Each takes the first
  compatible slot: dead argument slots in the order the arguments died (objects of at most
  4 bytes; an 8-byte object only a dead double argument), then existing local slots newest
  first, else a new slot. 1-byte objects never share a local slot with wider ones. Local
  slots are laid out from the top of the frame down in reverse creation order; the frame
  is rounded to 4 with the padding at the bottom.
- An argument slot dies at its last read (a load into a register frees it; a copy
  `int t = a;` is forwarded to its use); a never-read argument's slot is never reused.
  No argument slot is reused at all when the local frame would be 112 bytes or more
  (corpus: 161 such functions, none reuses one).
- A variable whose address reaches a real call is live from the first call in its block (a
  temporary: in its statement) to the last one; every call counts as a use and a
  definition. So `g(a); g(b); int x, y; use2(&x, &y);` reuses only a's slot (b is read
  after the function's first call) while `g(a); g(b); { int x, y; ... }` reuses both.
  Other frame variables use exact liveness.
- Empty-class temporaries (`NoInitClass()`) are 1 byte: they are placed first and take the
  first-dead argument slot. HouseClass::Load matches only with BuildingClass::Load's
  `if (SUCCEEDED(result)) { int count; new (this) HouseClass(NoInitClass()); ... } return
  result;`: count's block then contains the temporary and count takes the stream slot.
- Fix a frame-only miss with block placement of declarations, statement boundaries and
  statement order (which argument dies first, which variable is referenced last), not with
  dummy references.
- Open: an original slot that is allocated but never referenced (0x712300's top slot;
  MapSizeGameOption::Describe leaving the dead territory slot unused and putting its
  operator+ temporary in a new slot) is a variable that existed at layout time and lost its
  references afterwards; no source form found yet.

## Block-wide scheduler state (Big49)

  placement miss late in a long block (a `mov ecx, reg` before or after the pushes, an `fstp`
  around them) can come from earlier statements whose code already matches. A value passed
  through a named local (`double v = x * 0.01; f(v);`) emits the same code as the inline
  argument but shifts that state; try locals for a run of similar statements (Write_Basic
  0x6625B0: all twelve [Lighting] values). Dummy statements that move it are steering.


## Named locals and the inline budget (Big49)

- Named locals count in the caller's inline budget though they emit nothing:
  `int value = ini.Get_Int(...); Field = value;` and `Field = ini.Get_Int(...);` compile to the
  same statement, but the first enlarges the caller. When a long reader (RulesClass::AI,
  Combat_Damage) inlines slightly fewer helpers than the original, put one kind of read
  (ints and leptons there) through locals; the band is narrow, so try per-kind sets, not
  arbitrary subsets. Apply one rule per function (every read of a kind), never individual
  statements picked to hit a count (owner ruling 2026-10-27, landed 5ccf5f93).
- VC6 numbers a unit's header-static initializers (`_$E`n) in order of first inclusion,
  so include order inside a unit with header statics is part of the match.

## Macro clamps and member accessors (Big51)

- VC6 compiles a parenthesized member `(x)` in a ternary differently from bare `x`: `x = (x) < c ?
  (x) : c` keeps a copy of the stored value (`fld st(0); fcomp`) and a `je/jmp` pair over the false arm,
  where `x = x < c ? x : c` gives `fcom` and an inverted branch. Westwood clamps are macros
  (`#define Min(a, b) ((a) < (b) ? (a) : (b))`); write them as the macro (Read_Basic 0x00661980,
  RulesClass::General DropPodAngle).
- An accessor that stands in for a member (`T &List() { return *(T *)((char *)this + 0x2270); }`) is
  a direct inline site at every use and spends the caller's budget; the original had a member. Declare
  container members with their real types (shared/vector_class_decl.hpp, shared/type_list_decl.hpp
  give the class declarations without the member definitions) (UnknownIDSource::Read_Basic).

## Switch layout and cross-jumping (Study50)

Derived from controlled experiments with the real compiler (Study50, 2026-10-27; lab in the
ignored build/class-work/Study50/, `lay.py` prints a listing's block layout with the cases
reaching each block).

- Dispatch: up to 3 case labels compile to an ascending compare chain (`dec eax; je`,
  `sub eax, delta; je`) with the default inline after it and the case blocks in descending value
  order whatever the source order. From 4 labels a jump table; it is two-level (byte index table
  plus target table) exactly when 3R > 4n + 12 (R = value range, n = case labels without
  default). Very sparse switches split at the median value. The target table of a two-level
  switch lists targets by smallest case value, default last.
- Jump-table case blocks follow source order; the default block goes after all of them wherever
  it stands; the code after the switch follows the last case (in source order) that breaks to it,
  and cases that return come after it. Partial common tails (`add esp, 4`, `call f`) are sunk into
  the block that falls into the join.
- Identical blocks (identical final code: a different scratch register prevents it, and scratch
  registers rotate after a block with fewer temporaries) are merged into one copy; the copy
  entered by fall-through stays (the first case after a dispatch counts as entered by
  fall-through); otherwise the later copy stays within one switch, and across two switches the
  later copy stays only when the block's tail matches the tail of the block that falls into the
  exit (else the earlier copy stays). Runs of identical consecutive blocks move together. The
  surviving block keeps the deleted copy's label.
- Which identical return a duplicate merges into depends on the other paths: TechnoClass slot
  175 0x6C15D0 sends case 6's `return -1` to the guard's return only with
  `case 0: if (c) return -1; return 0;` (with `break` to the shared `return 0` it joins case 0's).
- Two tests of the same values fold when they read the same variables (`if (s == 3 && t == 1)
  return; if (s != 1 ...)` loses `cmp t, 1`); through inline accessors (`Map.Closing() ||
  !Map.Active()`) both compares stay and the known constant is reused as a register
  (`cmp ecx, eax`). Rereading members folds too and leaves a dead load. (RTacticalClass::Action
  0x62FE30 with RadarClass 0x6331C0 and 0x633110 inline.)
- `d = d - limit + 1` becomes `mov r, 1; sub r, limit; add d, r` in every spelling; recomputing
  from the operands (`d = x - y - limit + 1` after `d = x - y`) gives `sub d, limit; inc d`. A
  named sum (`d = x + y; if (d > h) d -= h;`) gives `add; cmp; sub`; the recomputed
  `if (x + y > h) d = x + y - h;` can become `lea t, [y + x]; ...; sub y, h; add y, x`.
- Commutative operand order (which register an `add` writes) is a function-wide tie-break that
  unrelated temporaries move (0x62FE30's step-4 sum flips only when the slot-48
  `CoordStruct(cell.X * 256 + 128, ...)` temporary is removed); spelling, casts and local copies
  do not change it.
- A virtual call on a member of a named global object (`Map.List.Clear()`) is bound statically and
  inlined; through `this` or a reference it stays virtual. An original virtual call on a global's member
  comes from an inline member of the owner (`Map.Clear_Cells()` with `{ List.Clear(); }`), which also
  spends the caller's budget like the original (Read_Scenario_INI 0x0065EB40) (Big51).
- A no-argument function's convention shows only in its callers: in a `__fastcall` caller, the call
  after it loads ecx before the pushes only if it is callee-pops (`__fastcall`/thiscall) (Big51 ren2).
- Assignment through an inline `operator=(char const *)` evaluates the destination first; the original's
  temporary-first order comes from `x = FixedString<21>("...")`. Parallel arrays indexed from one base
  pointer (`[ebx-0x20]`, `[ebx]`, `[ebx+0x20]`) are members of one object (Assign_Houses 0x0065FBB0) (Big51).

## Small observations (Near48)

- A call that leaves ECX holding the caller's `this` (no `mov ecx` before it) is a free function, not a
  member: a stale ECX is not an argument (0x0051FC50).
- Repeating a member expression through a global pointer (`MissionTimer.Value()` twice) re-reads the
  fields; a reference local lets VC6 reuse them (0x006B0B20).
- Compares on a local int are jump-threaded (a passed test jumps straight to the call); the same member
  read repeated in each test is CSE'd but not threaded (0x006B1F10).

## Out-of-line helpers and global timers (Loco54, Scen55)

- Helpers the original keeps out of line but never calls (DriveClass Start_Driver, Stop_Driver, Hover/Fly
  Start_Drift, ...) are ordinary non-inline members defined in the unit: /Ob2 expands them at every use,
  and the standalone copy is emitted at its own address (Loco54).
- Functions returning a Matrix3D through a pointer keep the pointer form: `*matrix = transform; return
  matrix;`. Taking a base result as `Matrix3D m(*Base(&t, key))` reproduces the original's call of the
  copy constructor 0x0058FE10 (Locomotion Draw_Matrix family).
- Calling an inline timer member directly on a global (`FrameTimer.Value()`) lets VC6 drop the redundant
  -1 test inside it; a reference local (`CDTimerClass<..> &timer = FrameTimer; ...`) keeps it, as the
  original does (Post_Load_Game 0x0065D2C0).

## Members and temporaries (Loco56, Scen57)

- A zero-initialised `double` member is stored as two dword stores, which the scheduler reorders
  independently; a constructor whose init-list store order is off often has a member that is really a
  double (Fly +0x40, Rocket +0x48, Jumpjet +0x68/+0x70/+0x80 constructors).
- A `float` local holding a function result (`float ratio = Slope_Ratio();`) keeps the unfolded
  `fld 1.0; jmp; fcomp` comparison the original has (Drive Is_Level 0x0049FFC0).
- A virtual call on a temporary (`CD().Force_Available(...)`) is emitted as `call [vtable]`, not bound
  statically (Scen57).
