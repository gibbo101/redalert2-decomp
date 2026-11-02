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
- A loop whose condition contains a ternary (directly or through an inline
  helper) is rotated: VC6 copies the condition to the bottom. An original that
  re-evaluates such a condition at the top with a `jmp` back was
  `while (true) { if (!cond) break; ... }`; `for`, `while (cond)` and
  `for (;; i++)` with an if-break all rotate (SidebarClass::Draw_It 0x0067CF80
  with the inline ternary StripClass::Max_Visible_Rows; the out-of-line
  0x006820A0 is an if/else).
- Two branch blocks ending in the same virtual call, with its vptr temporary in
  the same register where the eax/edx source-order rotation would alternate,
  were one shared trailing statement that VC6 tail-duplicated into each branch,
  not two calls (AircraftClass Enter 0x004193D0).

## Inlining and translation units

- Two out-of-line functions with identical bodies called from one inline
  expansion (or from the two element loops of one template) are two levels of
  one constructor chain: a wrapper and the constructor it forwards to
  (`D(x, y, z) : Base(x, y, z) {}`). Call sites that read the returned `this`
  to copy a temporary call the inner constructor directly; an inline-expanded
  constructor leaves an inner call whose result is ignored.
- In DynamicVectorClass<T>::Resize the placement `new (array) T[n]` loop
  expands one constructor level more than the heap `new T[n]` loop, whatever
  their source order. A one-level element constructor is called by the heap
  loop and expanded by the placement loop (ZoneConnectionClass 0x0056B330); a
  two-level chain gives an outer call in the heap loop and an inner call in the
  placement loop (WaypointClass 0x007256C0: 0x00434820, then 0x0041B630).
  VectorClass<T>::Resize compiled alone (0x007254F0) expands both levels.

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
- **Depth-first, and a nested site pays for the sites still waiting above
  it** (Study152; replaces Inline17's "direct sites first"). VC6 decides call
  sites in source order; when it expands one it decides the sites inside that
  body next, before the caller's later sites. A direct site (depth 1) inlines
  when `cost <= remaining budget`. A site at depth d >= 2 inlines only when
  `cost * (1 + W) <= remaining budget`, where W counts the inline-candidate
  sites not yet decided in the enclosing bodies: a later direct site counts
  d-1 times, a later site in the parent body d-2 times, later siblings in the
  same body 0. Empty inline calls and inline calls that will be rejected as
  too large count in W; out-of-line, virtual and over-the-cap non-inline calls
  do not. Only accepted sites consume their cost, and free callees (Study37:
  at most two plain stores or one call) cost 0. So an empty call before the
  nested sites changes nothing (`E(); B();` = `B();`), one after takes the full
  penalty (`B(); E();`), and a large nested callee (a template constructor,
  Intersect) is pushed out by one or two later inline calls while a small one
  is not. Lab: `build/class-work/Study152/lab/` (a 3/6/12/24-store callee loses
  about its own cost per pending empty call; depth 3 pays 2x, depth 4 3x).
  Examples: WorldDominationTour::Map ctor 0x729330 (exact only with three
  member objects with inline constructors after Territories, which push the
  VectorClass<rc_ptr<Territory>> ctor 0x72BB10 out while Palettes' small
  vector ctor, decided last, stays inline); a DynamicVectorClass member's
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
  grows. A callee's cost is its own unexpanded IL; nested sites are decided depth-first and
  pay for the sites still pending above them (Study152, above), except free callees, which always expand.
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

## Constants, negations and temporaries (Big75)

- A constant cached in a callee-saved register (`mov ebx, 1`, later `mov eax, ebx`, `cmp eax, ebx`)
  comes from a variable initialised to it: `int players = 1; if (...) players = list.Count();`. The
  equivalent ternary loads the constant inline and never caches it (0x0065C7D0).
- `sete al; test al, al; sete al` for a negated comparison passed as a bool is a bool local negated at
  the use (`bool campaign = mode == 0; f(!campaign)`); `mode != 0`, `!(mode == 0)`, `!!mode` and
  casts all fold to one `setne` (0x0065C7D0).
- A named pointer local (`char *extension = &name[strlen(name) - 4];`) computes its value at its
  statement and moves a cached constant's live range; the same expression inline in a later call
  evaluates late (0x0065C7D0).
- Inline helpers fix the evaluation order of their arguments: `Cell operator-` built through the
  constructor computes Y before X, and a length helper that converts Y then X reproduces a distance sum
  whose inline spelling changes the register webs of the whole function (Create_Units 0x00660320).
- A zero-initialised accumulator declared before an inline `Clear()` gets its own register; declared
  after it, it shares the cached zero's register (Create_Units).
- `f(&CoordStruct(...))` builds the temporary after the later arguments are pushed; a named local
  built before the call stores ahead of the pushes.
- `volatile` is steering when it only moves registers. It is the original's source when the original
  performs the memory accesses only volatile semantics keep: `volatile int zero = 0; zero = 1 / zero;`
  stores the zero, reloads it, divides and stores the quotient (a deliberate fault,
  SwizzleManagerClass::Process_Tables 0x0069FC30; owner ruling 2026-10-28).
- A container method called through a pointer to its owner (`Rules->BaseUnit.ID(x)`) stays a virtual
  call (only a named global's member is devirtualised). An original that scans the container inline
  there used a non-virtual inline helper (`TypeList::Is_Present`).
- A CDTimerClass test through `operator long` leaves `Value()` out of line; `.Value()` inlines it
  (SpawnManagerClass::AI 0x00689C90, with the tail-duplicated trailing-call rule: 84.5 to exact).
- In a long compare-list function, the last `if (list) return X;` of each group stays inline in the
  original only when written `bool b = list; if (b) return X;` (applied to every group); otherwise VC6
  lays the return after the following code and cross-jumps equal returns. Equal single-value returns
  were one `||` list (OwnerDraw 0x005E0010, 0x005E0760).
- The bool-first rule extends to if/else: an if/else whose condition is a `||` list lays the else
  first unless the condition is a bool local. A bool `return a || b || ...` shares one `mov eax, 1`
  block across all lists (Big80).
- VC6 delays a callee-saved push until the register's first use, and saves it only around an if-body
  when that is its only use.
- A return the original sends to the function's final return block was an else-part return:
  `if (id != X) { ... } else return V;` (OwnerDraw 0x005DEFB0).
- For a parameterless function, `__fastcall` versus cdecl moves where the epilogue's `pop` is
  scheduled (Delete_All_Objects 0x00519960 is `__fastcall`).
- Separate stack slots for several temporaries mean they belong to one statement (MapClass 0x0055DEF0's
  redraw is one statement with an inline `Rect - TPoint2D`).
- A separate-unit plan cannot include headers that carry header statics; such functions go in their
  real unit.

## Lobby rules (Netshare183)

- VC6 strength-reduces two arrays onto one induction pointer only when both are members of one object; read
  both through that object (0x5CA540: AIColor at session +0x84 and the slot table at +0x2800).
- When /Ob2 inlines too much in a large body, write its repeated parts as file-static helpers; the budget then
  reproduces the original's inline set (0x5CA000 41-63 as one function, exact with helpers).
- A parameterless function declared `__fastcall` schedules a fastcall callee's ecx/edx loads before the pushes
  (0x5C86E0, 0x5C3040, accepted 0x4D1EA0); it did not help 0x5C67C0 or 0x5C34F0.
- A WideString temporary destroyed before the return copy is a block-scoped local (0x5CCF50).

## Westwood source idioms (published Westwood sources, 2026-10-28)

The published Red Alert and Renegade sources ([WESTWOOD_SOURCES.md](WESTWOOD_SOURCES.md))
show how the original code was written, which is what the rules above are reverse
engineering. Read them for shape; GPL code is never copied, and every shape is still
verified on the target.

- The recovered library headers already reproduce the wwlib text: VectorClass,
  IndexClass, GenericList, Straw/Pipe, Pick_Random_Number, TRect/TPoint2D and the
  timers match member for member. When a lane needs a container or library member it
  has not met, read the wwlib header first; its names and statement order are the
  original's. The RA2-only differences are listed in WESTWOOD_SOURCES.md.
- `wwlib/always.h` is included by every library unit. It defines
  `WWINLINE` as `__forceinline` under MSVC and uses it on `VectorClass<T>::operator[]`,
  `Length()`, the NoInit constructor and `RefCountClass::Add_Ref`/`Release_Ref`; it
  pulls in `visualc.h`, which sets `#pragma inline_depth(255)` (VC6's default is 8) and
  disables warnings 4514, 4244, 4056, 4710, 4355, 4097, 4505, 4711, 4511, 4512, 4100
  and 4786; it defines `NOMINMAX`, `MIN`/`MAX` as the usual double-evaluating macros
  beside template `min`/`max`, and `ARRAY_SIZE`. `bound.h` has the `Bound<T>` template
  (two ifs, not a nested ternary), `swap.h` a `swap<T>` with a default-constructed
  temporary, `incdec.h` the enum `++`/`--` operator templates. Tested (Study158): neither
  idiom changes any open case. `#pragma inline_depth(n)` only caps nesting (default 8,
  the 9th level is called); 255 leaves budget, W thresholds and whole-unit objects
  identical at depth 8 or less (MultiplayerGameMode and BuildingLight units compared byte
  for byte). `__forceinline` expands its site past the budget and its own W, costs no
  budget, still counts as a pending site in W for earlier nested sites, and does not lift
  the depth cap. Plain VectorClass `operator[]`/`Length()` and the empty NoInit
  constructor are already free callees (cost 0, counted in W the same way), so `WWINLINE`
  on them gives the same code as `inline`: no ruling is needed and `__forceinline` stays
  banned. Side observation: free one-call wrapper levels do not multiply W by depth (an
  X under 1, 4 or 7 free wrappers goes out at the same budget); Study152's per-depth
  multiplier was measured with costed levels.
- The MIN/MAX macro under "Macro clamps and member accessors" is wwlib's spelling
  (`MIN(a,b)`, `MAX(a,b)` in always.h); Red Alert's JSHELL.H had template `min`/`max`
  and `Bound` instead.
- Game-code idioms from Red Alert that the class lanes keep meeting: NoInit constructors
  pass `x` to every base and member that has one
  (`AircraftClass(NoInitClass const & x) : FootClass(x), Class(x), SightTimer(x) {}`);
  `Is_Infantry()`-style tests are inline RTTI compares in the header; each object class
  has `static void Init(void)`, an out-of-line pool `operator new(size_t)` beside an
  inline placement `operator new(size_t, void * ptr) {return(ptr);}` and a
  `Read_INI(CCINIClass &)`; nested constants are `enum {FLIGHT_LEVEL=256};`;
  parameter lists are `(void)` and accessors `const`; 1996 flags are
  `unsigned IsX:1` bitfields where RA2's are `int` members and `bool` returns (see
  Types). `Percent_Chance`, `Random_Pick` and `Sim_Random_Pick` are inline wrappers in
  INLINE.H over the scenario and simulation generators.

## Dialog chains (Modem185)

- Chat chain: write the leaf (Show_Chat), a caller with text (Send_Chat(text) calls Show_Chat) and the parameterless
  wrapper (Send_Chat() calls Send_Chat(text)); the dialog proc only gets the original's inline set in that form.
- A helper the original keeps out of line stays out when written with an explicit if/else into a local, while the
  same logic through a small inline accessor gets auto-inlined (Read_Color 0x597xxx vs Player_Color_RGB).
- Each checksum test written as clearing a `match` flag then `if (!match)` reproduces the original's branch layout.

## rc_ptr operator-> (RcPtr192)

- `rc_ptr<T>::operator->` carries an empty null test before the load (`if (Pointer == 0) {} return (T *)Pointer;`,
  a release-empty debug check). It keeps a second-level chain's `this` in a register (`add eax,8; mov ecx,[eax+4]`
  instead of a folded `[eax+0xC]`), keeps the dead `lea` of `(*cursor)->f()`, and charges inline budget, which is
  why operator-> COMDAT copies exist. Get() keeps the plain body; code the original compiles without the test reads
  through Get() (State ctor 0x730830). WDTSel unit: 17/19 drafts exact with it, 11/19 without.

## Out-of-line base vector constructors (Session200)

- When the original expands TypeList/DynamicVectorClass constructors inline but calls the VectorClass base
  constructor out of line, declare the VectorClass constructor without a definition in scope and define only the
  derived constructors inline as explicit specializations; any generic definition in scope (even after the caller)
  makes VC6 inline it. The out-of-line copy is its own row (0x674AF0 VectorClass<Wstring>).

## Waiting sites decide nested expansion (UICmnds206)

- Which depth-2 calls the original inlines is decided by the inline sites still pending later in the caller (W in
  the Study152 rule), not by definition order. UICmnds.cpp commands call the list rebuild 0x6F79C0 (depth 1, inlined);
  its builder calls (depth 2) stay calls only because the command's loop reads the list through
  DynamicVectorClass accessors (Count(), operator[]), each a pending site. Reading raw fields removes those sites and
  the builders expand. The out-of-line 0x6F79C0, with nothing pending, inlines both builders. One accessor too many
  pushes out a later expansion that must stay. Score such functions in the whole-population TU (UICmnds206 ws.py),
  never in a prefix compile.

## Local DynamicVectorClass vtables outside their home population (House208)

- A local `DynamicVectorClass<TechnoTypeClass *>` (vtables 0x7A0F44/0x7A0F64; RTTI says `T const *`) or
  `<BuildingTypeClass *>` (0x7A2F28/0x7A2F08) compiled outside the Factory population fails with "Unsupported
  allocatable data section" and its slot names bind to another copy. @ref both vtables and every slot name to the
  original vtable dwords (House208 refs.py generates the lines; refs_tt.txt, refs_bt.txt).

- (UICmnds210) A function called through a function-pointer type inlines through the constant pointer only when
  the parameter count matches the pointer type; return type and pointee type differences do not block it.

## _$E initializer numbering counts static data members (Session209)

- VC6 advances a unit's `_$E` initializer counter once per class static data member declaration the unit sees
  (static member functions and inline virtual destructors do not count). A header that pulls a class with static
  data (e.g. CDFileClass's search-list statics via cc_file_class.hpp) into a widely included header renumbers every
  unit's `_$E` symbols and the build fails "Function symbol ambiguous/missing: _$EN". Keep such includes out of
  shared headers that units include for unrelated declarations.

- (TAction211) A coordinate built through an inline `XYZ_Coord(x, y, z)` evaluates its arguments right to left
  (Z, Y, X) like any call; that, with `Cell spot = waypoint - Cell(size / 2, size / 2)`, reproduces the original's
  "Cell temporary" order in the reveal actions.

## Static over-the-cap functions count as pending sites (Queue220)

- In the Study152 budget, a later `static` function in the unit whose size is over the auto-inline cap still counts
  in W (a pending candidate site) at its call; an external function of any size does not, and a small external one
  is simply inlined. Queue_AI 0x623770 is exact only with Queue_AI_Multiplayer 0x623B00 defined `static` in the unit
  (as in Red Alert's QUEUE.CPP): land them together.

- Tail calls: after callee-saved pushes VC6 turns a final call into `pop; jmp` only when the callee is `__fastcall`; a
  cdecl or stdcall callee keeps `call; pop; ret` (Prog_End 0x6909E0 -> Kill_Mouse_Thread, Startup226).
- An `extern` declaration of a global placed after its dynamically initialised definition in the same unit makes VC6
  emit the initializer twice; include the declaring header before the definition (Startup226 header statics).
- String literals outside a unit's own pool (shared "%s", "INTRO", registry paths) need @ref lines: diff_candidate
  shows them resolved, but acceptance refuses the population with "Unsupported allocatable data section .data"; read the
  mangled names from the compiled object (Wonline239, Queue225).
- A class template member's out-of-line copy (e.g. WolDictionary<WideString,bool>::Shrink_Table 0x5CD9A0) is emitted only
  when the member is defined outside the class and some caller in the unit keeps a call to it; the accepted row source
  is an explicit instantiation (`template void X<...>::F();`), as for 0x51E760 (Netshare243).

## /Ob2 inline decision rule (Inline248, read from C2.DLL's P2 inline routine 0x1072D288 and confirmed in lab units)

- Every function has an IL size `s` (its own unexpanded body, call nodes included; lab: a constant global store ~6,
  an empty body ~12; a caller's S ~18 plus its statements).
- Root budget = max(1000, 2*S(caller)); a running total starting at S stops all further inlining past 35000.
- Sites are decided in evaluation order. N_i = inline-candidate sites in the same body from this one to the end,
  itself included (calls with IL available, including empty or later-rejected ones; not virtual or declared-only).
- Reject when s > 40 and s > budget (also depth limit, argument-count mismatch, the 35000 cap). Callees with s <= 40
  are free: always expanded, never charged.
- On accept: if s > 40 subtract s from the budget; then decide the callee's own body with budget / N_i (integer) at
  depth+1 and subtract what it consumed. The division compounds per level (Study152's cost*(1+W) was a linear
  approximation; the "waiting sites" rule is N_i).
- Practical: a tiny charged ctor out of line inside an inlined chain means the budget reaching that level was tiny;
  pending extra sites only divide one level, while each charged inline helper level subtracts its size and divides
  again. Out-of-line probe calls only raise S (the root budget). Measured sizes: CoordStruct ctor 41-52,
  CoordStruct::operator- 71-88. Lab tools: build/class-work/Inline248/lab/.
- Stack packing: wrapping a function's main part in a scope block (an if/else or a guarding if) decides VC6's frame
  slot sharing; a unit's .data must reproduce the original exactly, including statics between used ones (Scroll250).
- Auto-inline size cap (Inline252, lab with real CL): a function NOT declared inline is never auto-inlined above about
  175 IL units (27 constant stores expand, 28 do not; 23/24 with parameter stores), whatever the caller's budget; an
  `inline` function of 252 units still expands. So a callee the original keeps out of line with budget to spare is
  probably wordier in its source than ours. Unit sizes measured in a caller: global store 6, out-of-line call
  statement 4, explicit pointer cast 1; `T *x = new X; Add(x);` is 2 smaller than `Add(new X)` when Add takes T const&.
- Type-count sensitivity (Hdr306; replaces "header hygiene", Span268): a few functions pick between equal-cost
  instruction orders by VC6's internal allocation order, so any new declared type earlier in their unit (a new function
  signature, member or free, or a new function-pointer typedef; not comments, names or a reused signature) can flip them,
  non-monotonically (1-2 new types flipped 0x428370 at 7d270e22, 3-4 did not). Known victims: 0x428370 (path estimator,
  until 29d3eb48), BaseClass::Read_INI 0x42C460. The full-build refusal now names the victim row and first differing
  offset; reproduce by scoring that row in its concatenated population. Fixes, in order: land the header when the victim
  is exact with it (other landings move the count); give the victim's unit the real declarations its own code needs; a
  unit-local declaration in the one population that needs it. Never pad a header with dummy declarations (steering).
- Union members vs pointer casts (Event274): reading an event payload as `*(long*)&Data.Bytes[n]` instead of a union
  member (`Data.LongsCell.Long1`) adds indirect memory expressions that change operand order and scheduling much later
  in the same function (EventClass::Execute's TIMING sum). If a late expression resists every local rewrite, look at
  how earlier code in the function accesses memory.
- Dead stores (Tactical287): VC6 keeps two stores to an address-taken local when the second goes through an inline
  member (`rect.Y = a; rect += Point2D(0, b);`) but merges plain field writes; a "dead store" in the original points
  at an inline member operator. `Rect rect = Rect(x, y, 60, 30)` stores the constants through a register.
- Score in file context (OwnrDraw286): a draft scored as the first function of its file can allocate registers
  differently from the same draft after any other function; always score inside the population file in address order.
- MAX macro (Scenario289, Session275): Westwood's MAX(a,b) expansion repeats the expression (`a > b ? a : b`); a local or
  a template max compiles differently and does not match.
- __fastcall argument scheduling (Scenario291): in a __fastcall function, the register-argument setups after a
  callee-pops call are scheduled before the pushes; "/G5 scheduling ties" around calls in a free function often mean it
  is __fastcall. Also: a single new global `extern` in tag.hpp/id_source.hpp shifts a load pair in BaseClass::Read_INI
  0x42C460, while new function/member declarations do not - put new extern objects in a unit-local header.
- Measured IL sizes (Inline293 lab sweep): CoordStruct(int,int,int) 47-52; UnknownCoord434820(x,y,z) 41-46 (with inner
  ctor 89-94); XYZ_Coord 41-46; Cell_Center 47-52; old Coord_Snap 53-58; Union<Rect> 275-280 (Westwood's int() casts +6);
  TibSun Rect::Size() <= 40 (free). Arguments are decided before the call they feed (Cell_Center before Coord_Snap).
  Coord_Snap is the UnknownCoord434820 wrapper (out-of-line pair 0x434820 over 0x41B630), which puts the CoordStruct
  ctor one charged level deeper - that, plus TibSun's `pixel = f(coord); pixel -= Point2D(...)`, matches all six
  Tactical Render passes.

## Dead byte spill of an object flag (Cell351, 2026-10-31)
A spilled byte of an object's bit-0 flag that is tested once and then dead comes from `bool is_x; if (object != 0)
is_x = object->flag_bit0; if (object != 0 && is_x ...)`, not from register pressure. Seen in Cell 0x471660/0x47BB30,
TechnoClass Detach 0x6D2D10, 0x6F69F0; still open at 0x477B55, 0x477C87, 0x477EF8, 0x47805B, 0x47842A, 0x49B76B,
0x62A8A6, 0x62AB79, 0x6D70AF.

## Element loop versus memset (Cell360, 2026-10-31)
VC6 turns `for (i = 0; i < N; i++) a[i] = 0;` into `lea edi,a / mov ecx,N / rep stosd` (lea first), while memset emits
mov ecx first. When the original clears an array with lea edi before mov ecx, write the element loop.

## Calling convention of a no-argument callee (Netshare383, 2026-10-31)
Declaring a no-argument callee `__fastcall` changes the caller's scheduling even though the callee's bytes do not
change: after the call, a following tail call's register arguments are set before the epilogue pops, and the callee's
result is copied to its callee-saved register at once. Probe by overlaying the callee's declaration as __fastcall: a
shape-100 result whose only miss is the unresolved mangling means a rename spec to __fastcall fixes the caller. Fixed
netshare 0x5CB560 (98.97 over three lanes) and 0x5C34F0 (97.37). Other "scheduling tie around a call" plateaus may fall to it.

## A global read twice, through eax (Netshare390, 2026-10-31)
When the original loads a global HWND/pointer into eax, pushes a call's arguments and then copies eax into a callee-saved
register, the source is `local = global;` followed by an inline call that reads the same global itself (or a first call
that takes the global directly and later calls that take the local). VC6 merges the two loads into eax. Fixed netshare
0x5C67C0 and 0x5C71F0 (87.67, and its inventory bound was short). Stack-frame sharing follows the 2x rule (Netshare387):
VC6 reuses a slot for a non-overlapping object only when it is at most twice the slot's current size, so a frame that is
too large can need an earlier, larger buffer (0x5C7570: `char name[128]`, any 125-200 matches).

## Inline helper with a const-reference argument (Netshare390, 2026-10-31)
Eight repeated add-row/set-item-data pairs in 0x5CA6C0 come from one file-static inline helper. Passing the node pointer
by value scored 97.00; passing it as `NodeNameType * const &` is exact (the reference keeps the caller's load order).

## Calling-convention probe order (NearMiss392, 2026-10-31)
The __fastcall lever also applies to the function itself. When a free function's only miss is register-argument setup
(mov ecx/edx, lea ecx) after the pushes, or a push/mov ecx tie right after a call, probe before rewriting statements:
(1) the function's own convention as __fastcall; (2) each no-argument callee just before the tie as __fastcall; (3) a
free "object pointer" callee as a member (thiscall). Five of about twelve probes hit: 0x711E60 (callee 0x428AC0),
0x519E70 (TechnoTypeClass::Load_Palettes static __fastcall), 0x516E70 and 0x768C70 (self; 82 -> shape 100), 0x542460
(self plus 0x5DA360 as OptionsClass member). Missing @refs for string literals look like a convention miss on scores.
Follow-up (NearMiss395): four more self-__fastcall hits, all free no-argument functions (0x718060 voxel matrices,
0x6F5B10, 0x5C84E0 with its callee 0x5C8420, 0x683BF0). Ghidra cannot tell a no-argument __fastcall from __cdecl,
so every unaccepted no-argument free function is a candidate: probe the convention before anything else.

## Fragile 0x73FEE0 is $L-label renumbering (ConvSweep396, 2026-10-31)
Refresh_Wonline_Players 0x73FEE0 breaks (refused at +0x10A2) because a new declaration in a header it includes
renumbers its compiler `$L` labels: measured lobby.hpp +2, pcx_cache.hpp +7, owner_draw_dialog_control.hpp +1. Put
new declarations for those areas in new headers or behind a guard macro (pcx_cache.hpp PCX_CACHE_DECLARE_LOADS).
Also: populations marked separate_units (1640, 1643, 2179, 2795) need that flag in the plan or the composite compile
reports "accepted 0"; a joined unit cannot take a VECTOR_IMPLEMENT_*/guard macro defined after the header was first
included (move such functions to a separate-units bag); every string literal needs its own @ref in the plan.
The no-argument __fastcall lever pays on recorded near misses (8 of ~20), not on raw seeds (1 of 292).

## Inline budget in practice (InlineLab398, 2026-10-31)
- The Inline248 rule holds in every lab here; two corrections to lane folklore: (1) "small" callees are often
  charged, not free: the HEAD Cell(short,short) ctor is 41-42 IL units, the one-line 0x54FAF0 index 49-50, XY_Cell
  53-54, so a `<= 40` free callee is rarer than it looks; (2) s is the callee's unexpanded size, so a wrapper that
  only calls one large inline stays free and its callee is decided one level deeper.
- Measure before reshaping: lab/g2.py (Spend = k stores + b calls: 2-unit resolution) for callee sizes; in place,
  replace the callee by k stores (the "fk" sweep) to read the nested budget at each site, and add m empty inline
  calls before the final return to read N_i (the flip m gives R_i and N_i from two callees of known size).
- When the original keeps a charged callee out of line at early sites and expands it at a late one, the early
  sites see (R - s_parent)/N_i with a large N_i: the natural fix is one more charged level above it (a small
  inline accessor wrapping the call), not a wordier callee (0x565EB0: `Cell_Subzone(cell, layer)` around the
  clamped index; the callee would otherwise need ~120 units).
- When one of several identical statements has a different inline pattern, first write them all the same way:
  the budget alone often produces the difference (0x5629D0's fourth Get_Height_GL).
- Westwood's Cell is TibSun's `Cell : TPoint2D<short>` with `Cell(int x, int y) : BASECLASS(x, y) {}` and
  TPoint2D member operators returning `TPoint2D<T> const` built with `T(...)` casts: an operator then costs ~64 with
  a free nested base ctor, while the HEAD forms cost 80 or ~60 + a charged Cell ctor. This model makes
  Destroy_Low_Bridge_Span 0x556BF0 and the COMDAT 0x56AA40 byte-exact; adopting it needs ten accepted re-shapes
  (InlineLab398 NOTES "Whole-tree check").

## Auto-inline size cap versus budget (Map405, 2026-10-31)
A callee that is expanded although the original calls it may simply be under VC6's auto-inline size cap: the cap
applies to the callee's unexpanded IL, independent of the caller's budget (padding the callee with k 6-unit stores
flips it at a fixed k however many calls the caller gains) and of where the callee is defined. The natural fix is the
original's wordier body: Spring_Low_Bridge_Destroyed_EW 0x55EA50 goes out of line when its walk writes TibSun's
Is_Low_Bridge test out (`CellClass *cellptr = &Map[tmp]; overlay = cellptr->OverlayIndex; ... while (overlay >= 0x4a
&& overlay <= 0x65)`) instead of calling the bridge predicate. A hand-written `tmp + AdjacentCell[f]` costs ~16-20 IL
more than an Adjacent_Cell call; by-value vs reference, enum vs int, `!= 0` and early declarations cost nothing.
(macOS `seq 0 -1` prints "0 -1": guard k=0 in probe scripts.)

## Function-local statics in a shared .rdata (Iso416, 2026-11-01)
VC6 puts a function-local `static float const` into the unit's .rdata together with the header-static constants, so
one data section holds symbols the original placed apart. The audit verifies such a section per symbol (each bound by
@ref, tiling the section, bytes equal at its own original address) since 53f108001; bind every symbol, including the
local static's decorated `_?_name@?M@??func@Class@@...` name.

## Frame order in very large frames (Iso420, 2026-11-01)
The size-ascending slot order does not hold near esp: the most-referenced objects go first (in the disp8 range)
whatever their size (`ini`, 80 bytes / 93 refs, sits among the scalars in Read_Control_File 0x529870). Beyond that,
ties among equal-weight spills are unstable: independent of declaration order and names, but sensitive to which
temporaries are in the sort (removing one CDTimerClass temporary moves the other). Tools: Iso420 t2/fas.py, fcmp.py,
fref.py compare every frame variable's offset against the original.

## Macros versus inlined calls (Span427, 2026-11-01)
When a header expresses a helper as a macro, check whether the original was a function VC6 inlined: the audio event
code (0x403EB0-0x4068F0) is ordinary /Ob2 C calling Audio_Events_Clear / Audio_Event_Stop / Free_Stopped, which match
byte-exact as calls; the audio_event.hpp macros are not the original shape and their expansion is too big to inline
where the original does (Handle_Stop_Loop needs Stop written as Detach + Release_Samples calls).

## Join reload order follows definition order (Reinf437, 2026-11-01)
At a join, VC6 reloads spilled values in the order the variables were *defined*, latest first: Do_Reinforcements
0x639970 matched when `bool atwaypoint = false;` was defined before `bool drop_pod` and assigned later
(`atwaypoint = wp != -1;`); moving only the declaration changed nothing. Also: `while (true)` stays unrotated where
`for (;;)` gets rotated; a BN_CLICKED test written `(unsigned short)(wparam >> 16) == 0` gives `shr reg,16; jne`.

## "Handwritten assembly" claims need re-checking (Scout444, 2026-11-01)
Two functions our headers labelled handwritten assembly, LCW_Uncomp 0x534B50 and AnimFile::Decode_Frame 0x4249F0,
are Westwood C that compiled exact almost at once from the TibSun/Westwood source (`__fastcall` LCW decoder; TibSun
animfile.cpp). Before parking a row as assembly, compile the TibSun/Westwood C; only genuine inline-asm bodies
(LCW_Comp 0x534D40, XSurface::Fill_Rect 0x7743C0, BlitForward 0x4861C0/0x487080) stay out.

## Boolean conditional forms and bitfield order (Cell450, 2026-11-01)

- `flag = (x == 0) ? true : false;` and `flag = (x == 0);` are not the same to VC6. The plain comparison kept `x`
  live in a register and shifted every spill slot (Set_Under_Bridge 0x4732D0: 76.95 against exact with the
  conditional form).
- Consecutive bitfield assignments hoist their shift/mask temporaries in statement order: match the original's
  store order first.
- A member defined later in the same file still inlines into earlier callers (CellClass::Adjacent_Cell 0x476AC0
  into the bridge functions); do not move definitions to force or prevent it.

## if/else nesting changes stack packing (Mech459, 2026-11-01)

Early returns and the equivalent nested `if/else` blocks do not give the same frame. In Mech Movement_AI 0x5919A0,
wrapping TibSun's "no destination" case and the head-to-set path in `else` blocks cut VC6's locals from 0x6c to the
original 0x5c (+4.7 points). Keep the reference source's nesting before trying declaration-order changes. Also:
TibSun inline.h Direction written as `int x1 = coord1.X; int x2 = coord2.X;` reproduces the original's X-only stack
copies exactly.

## Float-returning helpers, switch-table bounds (Mix462, 2026-11-01)

- An inlined helper's return type moves FP-store scheduling even when no float store appears: Percent_Value 0x7200C0
  returns float (TibSun _Parse_Percentage), and only that gives WarheadTypeClass::Read_INI's fstp-after-pushes order.
- New rows that end in switch tables need `body_bytes` in the plan item; diff_candidate's score counts the candidate's
  tables as extra instructions, so judge such functions by their code lines. diff_candidate's default length is the
  inventory row: pass `--length` with the true extent before calling a function a miss (Loco276's "Ratio member breaks
  0x6F0530 (76.19)" was only a short bound; with --length 255 it is exact).

## Locomotor shapes (Teleport464, 2026-11-01)

- Two vtable calls in an if/else (`if (x != zero) slot59(x); else slot59(Object_Coord(LinkedTo));`) get the
  original's tail-merged `push; call [vtbl]`; a ternary argument does not.
- Named locals fix frame layout in long locomotor bodies: `CoordStruct target = center + offset;` before a member
  store, `Cell where = Coord_Cell(...); CellClass *cell = &Map[where];`, separately scoped pointer locals per block.
- The FootClass flag idiom `bool foot; if (o) foot = o->flag; ...` reproduces the byte spill `mov [esp+N], al`.
- (Egos466) An inline helper's body form changes the caller's branch layout when inlined, even if both forms are
  exact out of line: TibSun's `Y -= amount; if (Y < -20) return true; else return false;` for EgoClass::Advance
  0x4B3670 fixed the Egos scroll loop where a bool-local form did not.

## Named results move stores (NearMiss469, 2026-11-01)

- `int length = Get_String(...); if (length == 0)` lets the two inlined CRC temporaries share a frame slot (0x5014);
  `if (Get_String(...) == 0)` keeps them apart (0x5028) (INIClass::Get_Unicode 0x50EDF0).
- An inline helper that names its returned value (`Cell adjacent = ...; return Map[adjacent];`) moves the copy's store
  after the push and `this` setup at every inlined caller: a change to one helper body re-scores all its inliners.
- RA2 Direction-style code subtracts in ints and negates: `int dy = to.Y - from.Y; atan2((double)-dy, (double)dx)`
  gives the original's `sub; neg`.

## Switch cases do not share temporaries (Loco468, 2026-11-01)

Lab-confirmed (build/class-work/Loco468/lab/t1-t3.cpp): unnamed temporaries in different `case`s of one `switch` never
share a stack slot, while the same code as plain `if`s does, and temporaries inside inlined helpers share even within
a switch. In a big state-machine Process (Rocket 0x63DE90), routing each `LinkedTo->Center_Coord()`-style temporary
through a file-static helper (Ground_Distance, Direction_To, Distance_To) cut the frame from 0x9C-0xAC to the
original 0x84. A real arithmetic helper (`static inline int Square(int)`) adds inline sites and can push a later
constructor out of line, as the original did (CoordStruct ctor 0x41B630 in 0x63DE10's inlined copies).

## Merged calls and member-ctor store barriers (NearMiss474, 2026-11-01)

- Two `htons` calls in an if/else get merged by VC6 into one call, and that merge is what reads an int global as a
  16-bit word; a single call on an unsigned short local always loads a dword (UDPInterfaceClass 0x76CD40).
- VC6 never moves a store above an inlined member constructor: Point2D members act as a barrier for the zoom double's
  low-dword store in the Tactical ctor 0x6A24B0, while plain ints/bools let it rise to the top. Member types can be
  read off store order.

## Shared tails and hoisted loads (Rocket473, 2026-11-01)

- In a switch, two cases with identical endings get merged; the merge can pull post-switch code up behind the
  earlier case. Writing a test as `exploded = f(x); if (!exploded) {...}` instead of `if (f(x)) { exploded = true;
  break; }` kept the case-5 block apart (Rocket Process 0x63DE90).
- When an object pointer is chosen by if/else, VC6 loads a member first and then hoists the load both paths share; a
  single-use local in each branch restores the hoist, one local for every use spills it (labs Rocket473 lab/t6-t7n).

## Dialog procs (Opts476, 2026-11-02)

- VC6 lays out switch cases by value, not source order; source order still changes the inline budget.
- `HWND h = GetDlgItem(...)` as a named temporary, not a nested argument, fixes GetDlgItem call order and registers.
- Of two duplicate error blocks, VC6 keeps as the shared tail the one whose branch has an explicit `return`.
- (Near481) VC6 reorders ungrouped FP sums; only explicit grouping fixes product order: Closest_Object 0x5D5090
  matched with double locals y, z, x and `x * x + (y * y + z * z)`; none of 36 ungrouped orders did.

## Callee conventions and TibSun helpers (Wol483, 2026-11-02)

- A parameterless callee's calling convention moves the caller's epilogue scheduling: Wonline_Main 0x73A300's
  `xor eax,eax` lands before the pops only when unknown_close_all_dialogs 0x753F50 is declared __fastcall.
- Where TibSun calls SendDlgItemMessage and RA2 compiles GetDlgItem + SendMessageA, the original used an inlined
  helper (Send_Dlg_Item_Message); TibSun's inline accessors (MultiMission::Get_Official) fix load order.
- (Abuf490) Tail merging depends on the unit: identical masked/opaque case tails never merge in a one-function file
  but do merge after the unit's earlier functions in the joined population (unvq.cpp 0xA000 case). Standalone
  "tail-merge plateaus" can be scoring artefacts: always rescore joined (HALF 87.5 and 4x2 TRANS 88.2 became exact).

## DynamicVectorClass::ID loops on Count() (Port500, 2026-11-02)

Westwood's DYNAVEC.CPP and TibSun vector.h write `for (index = 0; index < Count(); index++)` in
DynamicVectorClass<T>::ID. HEAD had used `index < ActiveCount`, and that caused the long-standing "count/vector ecx/edx
swap in the inlined ID after an inlined Add" plateaus: PhoneEdit Dial/Add, the HouseTypeClass ctor and
RulesClass::Sides all went exact once ID called Count(). The 144 explicit-instance units still compile `ActiveCount`
under `#ifndef VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS`, so they emit no Count COMDAT. Rescore any miss with an inlined
ID/Add register swap.

## How /Ob2 refuses an inline site (Plan512, 2026-11-02)

Lab-confirmed (build/class-work/Plan512/lab/L1-L9): each call site is decided on its own. A callee expands when its
own source body fits the caller's remaining allowance, and that allowance shrinks with every expansion already made.
Sites are processed in forward order (see "Nested inline sites" below for the exact rule): an inline call placed after a site, even an empty one, pushes that
site's inner callees out of line; the same call placed before it does nothing. The callee's body size is what counts
(named int locals and struct copies count: four named ints flipped Planning_Centered_Rect, two did not); padding the
caller or parent helpers does nothing. To refuse a helper where the original calls it, give that helper a larger,
still-exact body (named locals), then rescore every accepted row that uses it (Plan512 x/fam.py).

## Nested inline sites: the full /Ob2 rule, validated (InlineLab518, 2026-11-02)

Inline248's C2.DLL rule is complete; it also explains Plan512 ("reverse source order") and Plan515 ("~145 units,
nested formula open"). 88 fresh predicted lab cases, all exact at their flip points (build/class-work/InlineLab518
lab/h1.py, r1.py random 4-level trees, v2.cpp), plus in-place probes of Draw_Node 0x619870 predicted to the unit.
- Sizes: s(f) is f's own unexpanded IL; callee bodies never add to it. Root budget B = max(1000, 2*S(F)).
- Sites of a body = calls to functions with IL (inline, in-class, non-inline functions of the unit under the ~175
  auto-inline cap), in evaluation order (an argument before the call it feeds), a loop body once. Over-cap,
  declared-only and virtual calls are not sites and count nowhere.
- For site i with N_i = sites from i to the end of the same body (i included): refuse iff s > 40 and s > R (costs
  nothing, its body is never examined); else charge s if s > 40 (s <= 40 is free), then decide the callee's body
  with (R after the charge) // N_i and subtract whatever that consumed.
- So a depth-1 site depends only on earlier accepted depth-1 charges. A nested site depends on later sites of every
  enclosing body (they raise N) and on its parent's own size (charged before the division). An inline call placed
  after a parent starves the parent's callees; the same call placed before only lowers R if it is charged.
- Unit costs (2-unit resolution): empty body 12; constant store to a global array element 6, scalar global 4;
  parameter store 8; extra parameter 2; `f();` 4, `ext(1);` 6; `return k;` 2; named local `int a = k; use a` +6
  over the direct form; `if (g) store` 14; struct copy through a local 12, direct 6. operator== as
  `if (...) return 1; return 0;` 72, `return a && b && c;` 62 (int) / 60 (bool).
- Reading a plateau: if the original refuses a charged callee and then accepts later charged callees at the same
  depth whose sum exceeds that callee's size, the refused one is one level deeper in the original (a free wrapper,
  an inline accessor or a constructor chain), never a different statement order. Draw_Node: the out-of-line
  0x41B630 at both CoordStruct(-1,-1,-1) sites needs TibSun's `Coord(int x, int y, int z) : BASECLASS(x, y, z) {}`
  over TPoint3D<int> (RA2_COORD_TPOINT3D: wrapper 44, TPoint3D ctor 48 refused at depth 2, call bound with
  `@ref ??0?$TPoint3D@H@@QAE@HHH@Z=0041b630`), and Member_Owner/Planning_Techno_Color (refused at R = 828) need a
  colour helper; with the 62-unit operator== (also exact at 0x61A8B0) the whole call sequence matches. The planning
  population stays 168/168 with RA2_COORD_TPOINT3D and that operator==.
- Tools: InlineLab518 x/meas.py (callee size by a charged Spend flip), x/model.py + run.py (simulate a call tree and
- Applying the rule (Ob2Apply519): the IL size of an out-of-line callee is itself a lever. A byte-identical rewrite of 0x54FAB0 (its result held in a local through an if/else-if/else chain, +13 to 18 units over the two-return forms) moved where Collapse_Cliff 0x562F50's nested decisions flip.
- A delete of a class with an inline empty destructor adds IL but no code, in the nested-if form only; the && form emits a ??_G call (Free_Buildup 0x45E920). Measure a missing spend with Ob2Apply519/prb.py (remaining-budget probe for a joined function).
  compare with the compiler), x/inplace.py (many variants of one function in one unit compile), x/probe.py (the
  remaining budget at any source line of a real function).

## Loop tails and known-value threading (Scout526, 2026-11-02)
- **Separate loop exit (`jne top` plus its own return copy).** Write one shared `return x;` as the last statement of the loop body, reached by positive nesting. Example, from Get_Next_Port 0x5B9F10: `if (transport && mode == 4) { if (!Open) continue; Close; } return port;`. The exhausted path is a return after the `while (tries--)` loop. If the body has two separate early returns, VC6 tail-merges the exit into `je exit; jmp top`. The same loop is inlined in Get_Mangled_Port 0x5BAF50 and Detect 0x5BA2C0.
- **Known-value threading.** VC6 threads a failed `x == 1` sub-test straight past a following `x == 2` test. Where the original still makes the second comparison, assign `x` again between the two ifs (Get_Allocation_Delta 0x5BAC50).
- **Register plateau in repeated loops (codex1 r847, Collapse_Cliff 0x562F50).** Three identical register-allocation diffs, one per half-2 loop, went away when the loops shared one `row_width` local that each loop reloaded in the original's order. The /Ob2 inline decisions had already been fixed through the 0x54FAB0 IL-size lever (Ob2Apply519). Treat a repeated per-loop register diff as a sign of one shared local.
