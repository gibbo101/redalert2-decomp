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

## Frame slots and unsigned loop ends (Scout531, 2026-11-02)
- Unused stack bytes can be the home slot of a struct whose other members stay in registers. In Render() 0x7178E0, a named `Rect rect` filled member-wise keeps X, Width and Height in registers and spills Y into the Rect's own slot. That reproduced the original's 0x34 frame.
- Loop strength reduction keeps a signed compare (`jl`) for every index form: int, unsigned, size_t, an unsigned bound, `!=` and `<=`. Only a pointer compare in the source gives `jb` (Convert_Voxel_Colors 0x716FC0: walk a pointer to each entry's middle byte, with the output pointer declared first).
- Stack-slot sharing: a shared slot can grow to at most twice its size. Making one 4-byte local a 6-byte struct let a 12-byte object share its slot, which gave Detect 0x5BA2C0's 0x188 frame. To diagnose slot problems, compile the joined unit with /FAs and read the frame map (Scout531 t/fa.sh, t/fab.sh).

## Late-day mechanisms (Scout528/530/532, 2026-11-02)
- **Coupled register choices (Detect 0x5BA2C0).** Two distant register diffs can be one effect. Writing `result |= relative ? 0x20 : 0x10;` as `int kind; if (relative) kind = 0x20; else kind = 0x10; result |= kind;` gives the same neg/sbb code but a different temporary order, and that fixed both diffs.
- **FP operand order.** VC6 re-sorts flat `+` chains, but parenthesising one product changes the order it picks (Matrix3D rows, Scout530; +4 to +20 points).
- **Extern re-emission.** VC6 emits a global's dynamic initializer again after every later `extern` redeclaration in the same file. Put such externs in a header the unit includes before the definition. Avoid widely shared headers: random2.hpp changed Pick_Lobby 0x744090.
- **Joined scoring.** A by-value return whose copy constructor is defined earlier in the population auto-inlines. operator*(Matrix3D, Matrix3D) scored 64 standalone and was exact joined, so always score such rows joined.
- **Jump thunks** compile from a one-line forwarding function. Rows that start inside the alignment pad before the true entry hide real functions (Scout528 t/early.py).
- **A member array of a global struct gets strength-reduced; a plain global array does not** (Multiplayer_Debug_Print 0x526D90: frames-behind as session +0x28EC, indexed by the same i as `this->Connection[i]`).
- **Init-list copy vs body assignment.** `List(other.List)` in the ctor init list differs from assigning in the body by two bytes in the clear loop (copy ctor 0x6025A0).
- **/Ob2 levers from the late passes.** A forwarding-only explicit specialization is a free site: later callers inline it and then call the refused callee. A typed `delete` on a class with an inline empty destructor adds a later root site, and one level less of inline depth can win back a refused sibling site (0x5EDB20).
- **Reference locals force a reload.** `int &slot = ActiveSlot; if (--slot < 0) slot = 31;` stops VC6 reusing the compare's load and gives the original `dec eax / jns` (LineTrail::AI 0x539530). The order of member stores then decides which local holds the node in ebp.
- **Guarding a declaration for one joined population.** Define the guard macro in that population's header-statics source. diff_candidate scores only the original's instruction span, so read `--full` when a probe adds calls after it.
- **Repeated bool tests merge.** VC6 always merges two consecutive tests of the same bool unless a different test sits between them, and its later passes do not fold that test away (Queue 0x6279D0, Scout536; a guard that only keeps the second test is steering, so it is a resume point, not a fix).
- **A named source local moves `this`** (Copy_Nodes_To 0x613550, Scout539): `TechnoClass *owner = Owner; PlanningMemberClass *source = node->Member_For(owner);` moved `this` from edi to esi, where it shares the register with the Owner load. This is another case of the coupled-register rule.
- **Inline refusal depends on the remaining budget.** Adding a free inline call after a site can push a nested ctor out of line (PaletteName::Load 0x603380, Scout539 hv/t1). The 40-unit threshold is not the deciding factor.
- **Near-tied register webs follow real use counts** (Scout540). Register ties between two webs, such as Get_Input's this/input and Add_Compressed_Events' index/storedsize, are decided by use counts after optimization. Declaration order, reference copies and dead initializers never break them; only a real change in uses does. If the bytes show no such use, the tie may be unreachable from source.
- **Check @refs before shape work.** MapSizeGameOption::Describe 0x728AB0 gained 3.6 points from a missing `?MapSize_Labels@WorldDominationTour@@3QBQBDB=007af140` @ref.
- **Rect copy-init vs direct init.** `Rect r = Rect(...)` keeps X/W/H in registers and stores them late; `Rect r(...)` stores them early. In Draw_Radial_Indicator 0x451BF0 that was worth 22 points (Scout543). Also bind FP constants by @ref: 0x79D168 is 1/2π and 0x79D160 is 3π/2.
- **Field-address registers in pointer loops** (Scout542). If a loop reads `p->Field` right after `p` is assigned, both on the loop-entry path and at the loop bottom, VC6 keeps `&p->Field` in its own register, and that one extra register shifts the whole function's allocation. Testing the field before the pointer copy and looping with do/while avoids it (LineTrail::Draw 0x5395C0, 65.64 -> 96.94).
- **Inline wrappers change evaluation order** (Scout541). Inline operands are evaluated before plain calls, and two inline operands are evaluated right to left. A temporary that is the destination of a `sub` tends to get ebx, while a read-only temporary gets edi (Get_Obstacle 0x4BBAF0).
- **Pushing ??_G out of line.** Two more /Ob2 sites after a nested `delete` make ??_GWideString go out of line. An explicit specialization defined after an earlier inline use is called out of line. VC6 emits nothing for an explicit specialization of an in-class member that nothing calls (control registry 0x5DEE00).
- **Double lvalue in `?:` is copied as integers** (Made_A_Kill 0x713360, Scout549). When a double lvalue is the false arm of `?:` (MIN), VC6 copies it as two dwords; an rvalue arm (an inline returning double, `+x`, `x * 1.0`) is reloaded with fld/fstp. TibSun's `MIN(Experience, Veteran_Cap())` form matched.
- **Growing the root's own body restores a site** (tracker 0x4128A0). Writing `edge.X = center.X + radius;` instead of `+=` enlarges the root, and since the root budget is twice its size this brought back an Append_Bin inline site that a bigger Shift_Bin had pushed out.
- **Inline wrappers as register levers (evaluation order and rotation).**
  - An inline argument is evaluated before a plain call. An identity inline `Rect const &Wall_Rect(Rect const &r) { return r; }` around the first Union argument gave the original's call order (Wall_Update 0x475960, Scout550). This form is a hypothesis: it is not TibSun-shaped, so replace it when a natural source shape turns up.
  - A file-local `static inline` wrapper around every SendMessageA call adds code-free temporaries that bring the scratch-register rotation into step (Fill_Port 0x66D5A0, Scout551). Dead or no-op statements never help, because VC6 drops them before it assigns registers.
- **A dead 3D temporary keeps its 12-byte frame slot** even when its Z stores are removed (Wide_Area_Damage 0x47F6E0, TibSun 3D-coordinate Distance, Scout552). An inline argument temporary bound to a const reference keeps its memory home and its stores, while a named struct local loses both (IonBlast AI).
- **Discarded results keep inline bodies.** `Union(a, b) - origin;` with the result discarded keeps the partial inlined Union body and supplies cheap inline sites that push other callees out of line (Wall_Update).
- **Rebuilt temporaries reorder struct stores** (UnknownBeacon 0x42DD60, Scout555). `dst = CoordStruct(src.X, src.Y, src.Z);` is not a no-op: it reorders the member webs, which moved Z to esi and Y to edx as in the original. The inline-wrapper lever was neutral there.
- **Guarded atexit means a class static** (Scout557, Scout559). An atexit that tests and sets a guard bit, or a thunk that only sets a guard bit, is the destructor callback for a class static data member whose type has a user-declared destructor (empty in Scout559's case). A plain global of the same type gets a bare `ret`. Declare such statics under a unit macro: unguarded, they renumber `_$E`/`_$S` in every includer. A guarded declaration takes one `_$E` number from the whole unit.
- **Small late levers** (Scout557, Scout560).
  - `Cell const &offset = table[i]; cell + offset` gives the cell.X-first add.
  - A bool local read before an unrelated store keeps identical stores in two branches from merging.
  - A static inline helper in an argument list is expanded before the argument pushes.
  - A rebuilt temporary used as an operator operand moves member-load choices across statements, not only within its own statement.
- **Final-pass levers** (Scout561-563).
  - A static inline bounds helper adds an /Ob2 site after a `new`, which pushes a nested VectorClass ctor out of line (Collect_Boundary_Cells 0x56ED10).
  - A member-wise difference stored Y, X, Z, from a copy-initialised rebuilt `from`, splits the loop-sum fix from the subtraction load order (Find_First_Obstacle 0x4BB890).
  - A lone float stored at frame offset 0 of a 12-byte slot is the X member of a 3D local; `Vector3 facing; facing.X = cos(...)` gave IonBlast AI the original 0xB8 frame (84.41 -> 96.30).
- **One-use float copies set x87 operand order** (IonBlast AI 0x521340, Scout566). In a commutative fmul of two memory floats, a float local used only once is loaded first. `float c2 = facing.X; float s2 = facing_sin;` just before each fabs test matched the original's operand order. VC6 propagates int copies away but keeps these float copies.
- **One-use float copies also move integer scheduling** (operator*(Matrix3D, Vector3) 0x591380, Scout572). Reading all nine rotation elements into one-use float locals placed `mov eax, ecx` where the original has it.
- **Comma-assigned pointer in a short-circuit condition** (IonBlast AI 0x521340, Scout571). When an expression is read twice in a condition, writing the second read as `(voxel = expr, !voxel->field)` moves that load's register, and the change carries into the next statement's pointer copy.
- **Push vs mov after a call** (PaletteName::Load, Scout574). The original puts `mov reg, eax` before `push imm` only when the call result lives in a register; ours pushes first. Resume point: find accepted matches that show the mov-first order.
- **Correction to the use-count note (Scout570).** The Add_Compressed_Events 0x627B60 esi/edi tie was broken by the order of independent initialisations, not by use counts. Moving `units = 0; whom = 0;` from the declarations to just after the memset changed where their register lifetimes start, and the function became exact. Try initialisation placement before concluding that a tie is unreachable.
- **One-use field copies stop alias reloads** (Execute_DoList / Process_Receive_Packet, Scout579). Copy a field that is read before several stores into a local used once (`int response = ...ResponseTime`). This removes reloads the compiler makes because it assumes the stores may alias, and can flip function-wide register choices.
- **Late joins change earlier drafts.** A helper accepted later and now joined into a row's unit can start auto-inlining into rows drafted before it; for example 0x62E5C0 now inlines into Process_Receive_Packet. Rescore old drafts against HEAD, and refuse the helper's inlining with an exact, larger rewrite landed in the same plan. Also: diff_candidate does not flag missing string @refs, so run the strict audit.
- **Single-member explicit instantiation emits nothing** under /O2, without a warning; `template class` emits every member. A template member therefore lands with its real caller (Scout580).
- **Byte-identical rewrites that add IL are a budget lever** (Options_Menu_Proc 0x4DD8A0, Scout582). Measure the missing /Ob2 budget with probe pads, then close the gap with natural forms that compile to the same bytes but carry more IL: TibSun store-then-override, nested ifs, named pointers, explicit `!= 0`. Never land the probe pads.

## Float chains and MAX macros (Scout585, 2026-11-03)
- VC6 sorts a flat floating-point `+` chain and reuses repeated subexpressions across it, so neither the term order nor an inline helper stops the reuse. A miss where the original recomputes a squared term (railgun 0x60C050) needs a different evidenced shape, not reordering.
- An expanded TibSun-style MAX macro (`a > b ? a : b` written out at the site) gives `add reg,-N` for a constant clamp, where a helper call gives cmp/branch forms.
- A local `Random2Class &rng` reference held across several random calls changes the register assignment (spark 0x60B670 62 -> 78.8).
- Matrix temporaries (Scout588): VC6 keeps the two Rotate_Vector temporaries separate when the Slope_Vector result is assigned, and shares the matrix temporaries when the slope matrix is assigned in its own statement.
- Including a header that defines VECTOR_IMPLEMENT_* renumbers a unit's guarded-static labels ($S42 -> $S64), and acceptance refuses the result as unbound .bss. Move a global the unit needs into a small header of its own instead (frame_rate.hpp for unknown_a6eb1c, ParticleClass 0x609D10).
- Import-call wrappers (Scout587/589): a code-free file-local `static inline` wrapper around an import changes which callee-saved register caches that import. Get_Item(HWND, int) around GetDlgItem matched 0x466A50 (98.98 -> exact; +4.4 on 0x634670, +13.8 on 0x6340F0). Send_Message around SendMessageA matched 0x596540 and Fill_Port 0x66D5A0. Wrap the import that appears in the tie, every site first, then single sites. The wrappers are neutral on loop-index ties, and in functions near the /Ob2 inline budget they make things worse. They are hypotheses, not Westwood shapes.
- Session members vs aliases (Scout591): reaching a member through the session object (`unknown_session_a3d298.Players`) or through its global alias changes alias reloads and the register choice in an inlined DVC Add. Try both.
- A branch that ends in `break` to a shared tail and a branch that repeats the tail and returns leave different blocks after VC6's tail merging (Net_Join_Dialog 0x5BD070: the guest path repeats the tail).
- A new parameter in a widely included prototype can change unrelated functions (lobby.hpp: Pick_Lobby 0x744090 and Print_CRCs 0x62A360 by 4 bytes each). Moving a prototype into its only caller is neutral.
- Command dispatch (Scout593, Get_Join_Responses 0x5C08A0, 83.7 -> exact): one if/else-if chain over the command lets VC6 keep the compared constants in callee-saved registers across the loop. Separate `if (cmd == X) { ...; continue; }` blocks give the same block shape but different constant registers.
- A dead counting loop (`if (!strcmp(...)) dups++;`, TibSun) keeps the loop and its dead stack store. `x = strcmp(...)` or an empty if removes the loop.
- Reading a bitfield once through the global alias and once through the session member gives the original's separate dword and byte loads.
- diff_candidate does not flag an unbound string literal; acceptance refuses it. Add @ref for every literal the original references (`","` 0x7CE9C0).
- Declaring an import `__declspec(dllimport)` (timeGetTime in Dropship_Screen 0x4A6B90) gives the original's `call [imp]` and register caching of the import pointer: +21 points. A plain prototype calls a thunk.
- Aggregate initialisers instead of memset for local arrays gave the original's stores (+3.3, 0x4A6B90).
- Classes whose RTTI mangling is PAV must be declared `class`, not `struct` (ButtonFadeEffect, CrossDissolveEffect).
- A function-local static with a destructor makes the unit emit its `$E` atexit thunk. Acceptance refuses an @ref binding of that thunk, so the thunk's row must be taken into the plan (0x5C01D0).
- A static inline accessor used as a sprintf argument is evaluated before the other pushes and moves that load into a callee-saved register (0x5BC940).
- Refused first inline site (Scout596, Skirmish_Command 0x6829F0, 78.89 -> exact): when the original calls a helper at one site and expands it at the others, and no IL probe at depth 1 refuses it, move that case into a static helper (depth 2) followed by enough free root sites (here code-free Get_Item wrappers) for the budget to refuse it. `#pragma auto_inline(off)` also refuses it, but breaks the other sites.
- A value read into a local before a constructor call (`mode = Session.Mode;` before `WideString message;`) is held in a callee-saved register across the call, which also fixes later frame-slot order.
- Nested call arguments: when the original pushes a constant after an inner call, make the inner call's result a temporary.
- A free inline function from a header that an earlier function in the unit expanded stays expandable; a member-call form avoids it (`cliprect.Intersect(Get_Rect())` instead of the free rect_intersect.hpp `Intersect(a, b)`, DSurface slot 13).
- A const-reference local to a field (`unsigned long const &received = rec->ReceiveTime;`) reorders the operand loads of the sum it feeds (0x524870, 98.50 -> exact).
- A cached constant register lives until its last source use. TibSun's `if (SUCCEEDED(result)) { ...; result = S_OK; } return result;` keeps the cached zero alive to the end, so it stops sharing a register with a pointer defined late. An early `if (FAILED(result)) return result;` frees it (TechnoTypeClass::Load 0x6DE260, 99.64 -> exact).
- SIB operand order inside an inlined callee is set at the call site, not in the callee: VC6 canonicalises the callee's address tree. Read_INI 0x44AB80 got [ecx+edi] by calling through a pointer copy (`BuildingClass *building = b; building->Turn_On();`).

## What counts as an /Ob2 site (Scout614, 2026-11-03; measurements in build/class-work/Scout614/NOTES.md)
- A site is any call of a user-written function that has IL in the unit, implicit calls included. Each of these is one site: an inline accessor or wrapper; an explicit temporary; a local declared without an initializer whose type has a user default ctor (`CoordStruct c;`); a user-written copy ctor or operator=, also in `T v = f();` and by-value arguments; a converting ctor (base-copy conversions included); a default argument that builds an object; an inline operator (`+=`, `==`). A local with a user dtor adds one site per dtor call, plus one for its ctor.
- None of these is a site: compiler-generated copies, assignments and by-value passing; derived-to-base conversions; field reads; declared-only calls; release `assert` (TibSun's compiles to `((void)0)`).
- An accessor in place of a field read adds exactly one free site and 2-6 root IL units. Most recorded "N sites short" misses come from the original calling user-written inline functions, mostly the position accessor (Position_Coord_004f3f40 / Object_Coord, TibSun Get_Coord/Center_Coord), where our source reads the field. Example: Aircraft 0x416420 under the ComPtr299 comip model, 63.48 -> exact by passing Position_Coord_004f3f40() instead of CoordStruct(Coord). A second family is user ctors, dtors and conversions of value types (Scout605's Coord crossings).
- Not every deficit is a site count. A deficit measured in IL units (Ship Draw_Matrix about 170) or a very large one (Unlimbo 60-70) points to a missing inline level instead.
- Scout614 also ruled out a user-written Vector3 copy for BuildingLight: the original's integer moves are the implicit copy.
- A function-local DynamicVectorClass makes the unit emit its vtable. Acceptance refuses that .rdata unless every slot of the DVC vtable and its base VectorClass vtable is bound by @ref, read from the original vtables (TechnoClass::AI: 0x79D0AC, 0x79D0CC).
- A local DynamicVectorClass whose stores come out as Vector, IsValid, vptr, GrowthStep, ActiveCount, IsAllocated, VectorMax is the ctor followed by an inlined `Clear()` (TibSun's `ActiveCount = 0; BASECLASS::Clear();`, its `if (Vector && IsAllocated)` folds away). VC6 keeps those stores in IL order. The Clear call costs one /Ob2 site, so another later root site has to go (UnitClass::Read_INI 0x706AE0).
- A 12-byte frame gap whose only spilled member is Y is a Rect built with the size calls as ctor arguments (`Rect rect(cell->X, cell->Y, type->Width(), type->Foundation_Height(false));`, DisplayClass 0x499390). The same gap is in 0x4991D0.
- Loop bound shape decides hoisting: `y < ymin + ysize` (with `int ysize = 2 * adj + rect.Height;`) is hoisted into the outer loop's preheader after the guard, which puts the bound in a register and leaves x in memory. A named `ymax` computes it before the guard (Passes_Proximity_Check 0x4991D0).
- TibSun's `Coord(int x, int y, int z = 0) : BASECLASS(x, y, z)` wrapper, built in place for offsets, adds one free /Ob2 site per use and fixes add operand order (Aircraft Fire_At 0x415790). A DVC-style example of Scout614's user-ctor site family.
- Read_INI 0x49CFD0: the surface size is `Get_Width() * Get_Height() * Bytes_Per_Pixel()`, and a CoordStruct built member by member (`homecoord.X = ...`) fixed a later loop's register choice. Including building_type.hpp instead of building_type_class.hpp pulled in an extra dynamic initializer that acceptance refuses.
- Dead frame bytes can be an unused member of a by-value temporary: Fire_At's 8 bytes are the Z of a 24-byte BulletVelocity built through TibSun's copy ctor.
- Braces are IL (Scout626): removing the braces from four one-statement ifs took Sidebar C850 from 168 to 162 /Ob2 units with identical code; an early return gave 158. Write braces as TibSun does when a budget is tight.
- A call refused inside an inlined copy in another function names the callee the source really calls: Recalc 0x6802D0's inlined C850 calls 0x6820F0, which reveals C850's own source.
- Free callees (40 IL units or less) are never refused, even at allowance 0, so a callee the original refuses somewhere is over 40.
- A local's scope decides whether it takes a dead parameter's stack slot: a Cell declared inside `if (best == 0) { ... }` reuses the dead `point` parameter slot, while one at function scope gets its own (Tactical 0x6AA990). Splitting a Point2D into two ints gives the original's scalar slots.

## The per-unit declaration counter (Scout627, 2026-11-03; measurements in build/class-work/Scout627/NOTES.md)
- VC6 numbers symbols, new function signatures and `$L` labels with one counter per translation unit, and some c2 tie-breaks follow that number mod 64. Each `struct X;`, `extern int x;` or `void f();` counts 1, and a declaration with a new signature counts 2. Names, comments, declaration order within a block, and anything declared after the row do not matter.
- Print_CRCs 0x62A360 (three reload-order sites; 20 of 64 offsets are good) and Refresh_Wonline_Players 0x73FEE0 (one site; 48 of 64 good) depend on the counter at their own function. Every declaration before them in the joined population moves them, so include order cannot harden them. When a header change breaks one, land a natural re-roll of the victim's own body in the same round. Check header copies first with build/class-work/Scout627/fragile_probe.py.
- Pick_Lobby 0x744090 depended on where INIClass and CCFileClass are declared relative to each other. Including ini_class.hpp and cc_file_class.hpp first in the wonline unit hardened it (9c4945b18).
- Static data members (CDFileClass's five) declared before a unit's initializers advance its `$E`/`$S` names. The plan's initializer symbol_prefix values must follow them, or acceptance refuses `.CRT$XCU`.
- Seed_Lake 0x57E100 (82.45 -> exact): the grow block as its own `if (success && origin == Cell(0,0)) {...}` after the whole success/else chain gives the original's layout (grow block after the return tail). The spread loop is `while (n < count) { if (node == 0 || !success) break; ... }`, not if plus do/while. An inlined helper written as one float expression (`return a*Rand()+b*s-c*t;`, no double casts or named locals) leaves the random fraction on the x87 stack as the original does.
- Empty inline functions (`static inline void f() {}`) are not /Ob2 sites, even 140 of them; a probe body needs at least one store to count (Scout637).
- A bool-returning accessor gives `shr; test cl,1`; the original's `and eax,1` out of line and `test ah,1` inline mean it returns an unsigned int bit (CellClass IsUnderBridge 0x4788D0).
- Two TibSun `min()` calls supplied the two later /Ob2 sites that make the original call operator+ 0x42ADD0 out of line (Repair_High_Bridge_Span 0x54B560). Fix the call sequence first, then the frame.
- A variable reused as a walk cell whose address goes to an out-of-line operator+ is not merged with a later copy's stack slot. A loop `if (flag) { if (++n >= 4) return; } else break;` gets its own epilogue copy (Scout640).

## Loop-invariant step values (Scout645, 2026-11-03; lab in build/class-work/Scout645/lab/)
- In a loop that stores to an address-taken local (a walk Cell), VC6 hoists the X/Y values of `AdjacentCell[step & 7]` into registers only when `step` is a `?:` of two constants; it tracks the select's value set. When `step` comes from an if/else diamond (`if (c) step = S; else step = E;`), or from a load, call or bitfield, it hoists only the address and re-reads both members on every pass. The diamond is if-converted after the loop optimizer, so it emits the same `neg/sbb/and/add` bytes as the `?:`; only the loop body tells them apart. `int step = E; if (c) step = S;` keeps a branch instead. This gave Destroy_Train_Bridge_Connections 0x553570 (61.84 -> exact) and Repair_Bridge 0x555A60 (63.60 -> 99.75). scan.py lists other original loops with a hoisted address.
- One named local re-read before each test breaks a this/parameter register tie (TechnoClass slot 174 0x6C1380, Scout644).
- VC6 reuses an incoming parameter's stack slot for a later temporary once the parameter is held in a register for the rest of the function (0x553000 `dir`, 0x5539B0 `cell`). If ours gives the temporary its own slot, the parameter is probably not kept in a register.
- Membership tests as plain loops with a `found` flag and the target on the left (`target == list[k]`) thread the original's branch; an inlined ID() compared with -1 does not. Reading `T *item = list[i];` before the value test in a loop over local vectors hoists both Vector pointers and stops VC6 turning the loop into a countdown (TechnoClass 0x6D4400, 72 -> exact).
- Commutative 16-bit Cell sum operand order flips with the function's count of named locals mod 8; position does not matter, a local that is copied away does not count, and declarations before the function have no effect (Scout648, Scout650). Survey an operand-order residue with a probe `Cell probeN;`, then find the natural local; unused probes must not land. `wchar_t *wname = ...` before each call fixed IPX Service's function-wide register rotation.

## The per-function operand tie (Scout651, 2026-11-03; lab in build/class-work/Scout651/lab/gen4..8)
- A commutative tie flips on one phase of key = T + offs mod 8, and the whole compile, frame and registers included, repeats with period 8 unless the /Ob2 budget moves. T counts parameters and referenced locals in any scope, c1 temporaries (a `(Cell)` cast, `f(a+b)`, assigning a Cell return), and one per distinct field of a local struct named directly (`walk.X`). T does not count never-referenced locals, statements, calls, statics, earlier declarations, or one-return inlines such as Facing_Add. offs comes only from inline expansions earlier in the source text; layout does not set it, so a block laid out after a statement can still be written after it. Survey with dead locals and dead inlines; dead probes must not land. The c2 structure behind mod 8 is not identified.
- `Delete(T(id, false))` builds the temporary in the argument and schedules its store as the original does; a named local with the same ctor does not (0x566C30).
- Two Cell-sum mechanisms (Scout652): X-type sites follow N mod 8; Y-type sites ignore N, dead probes and `(Cell)` casts and flip by parity along the function, with each preceding wrapper result copy. Symmetric edits to two families cannot flip only one; an asymmetric source is required (OverlayClass Mark 0x5DA970).

## Locomotion Process and While_Moving forms (Scout654, Hover 0x4FBFC0, 0x4FCBC0)
- A named `int const &result = ok;` used for the first test stops known-value threading of `ok` past later tests. Only a named reference does this; an inline with a const-ref parameter or a value copy does not.
- An X,Y-only copy of a moved Coord is a Point2D move step: `TPoint2D<int> moved = ...; coord.X = moved.X; coord.Y = moved.Y;`. The dead Z goes and the frame comes right.
- A helper that takes the exit coordinate by reference and reads `count` inside, before its call, shares the register the way the original does; the same read in the caller does not.
- An unreferenced row after a switch table needs its predecessor's extent on record, so it lands one round later, with its definition inline in the predecessor's draft for that round.
- Natural free /Ob2 sites that make As_Cell and operator== refuse inside Start: Under_Bridge, Abs, Object_Coord accessors and TibSun's Is_Complete_Turn with its operator- and operator>=. No pads were needed.

## Key probes, refined (Scout653)
- A k probe moves only sites after it, which narrows the earlier "position does not matter" claim. `int q; q;` is a pure T probe with no IL; `int q = 0` also moves S and hits budget flips.
- Copy-propagated locals add nothing to T; `(Cell)` casts do.
- A site stable over every k is an initialisation-order problem, not a key problem: try moving each `= 0` first (0x5629D0 went 82.86 to exact with `int found = 0;` before `xx`).

## Constant webs and Coord differences (Scout655, Ship 0x676F60)
- `(Object_Coord(LinkedTo) - dest_coord)` gives `mov esi,edx`; `movement + Object_Coord(LinkedTo)` gives `mov ebx,edx`. An unexplained register copy around a Coord difference is usually one more inline level.
- A cached constant (-1 in edi) is a conflict rule, not a type rule: compare types do not detach it, but a real pseudo at the difference peak or live across a call evicts it. Constants compete: a second zero use at the head caches zero in edi and moves -1 to ebx.
- TibSun's Point2DStruct: `Point2D(Point2DStruct const &)` built through a nested call reads Y first. `(double)X*(double)X...` Length gives the original FP order.

## Inline budget levers (Scout656)
- `Cell temp(first);` in a small local swap helper is a charged site; `Cell temp = first` is smaller and misses the window. `current.X++` instead of `+= Cell(1,0)` removes sites, lowering N so a larger early charge fits.
- An inline member-wise operator= makes a struct assignment a charged site with no code change. Static helpers are free sites that only raise N.
- The first nested accept can have zero margin: one added site anywhere later flips it, even a spend probe, so the charge must come from existing sites or helper sizes.
- One shared int across disjoint loops gives a shared frame slot; block-scoped locals do not. Naming a count before a call lets `add ebp,0x30` coalesce with the dying pointer. Two side steps written the same way (`facing - 4`) CSE as in the original.

## Frames, FP and statics (Scout657)
- Frame order follows object size: an 8-byte Point2D sorts before 12-byte objects, and a `CoordStruct delta` with Z dead ties with them (0x608440). An inline value helper such as TibSun's `Random_Double(a, b)` moves a `fild` temp into the first-dead argument home; a named int does not.
- Register setups before pushes in a free function mean `__fastcall`, even with no callers (0x53F490).
- Inserting a function with local statics renumbers later `$S` and `_$E` symbols, which shows up as "Unsupported .bss" and "Unaccounted code". Newly emitted inline slots need @refs too.
- To break FP product CSE, use casts in the first sum and fresh double locals in the second; casts or locals in both sums CSE the squares. `double angle = a; angle *= b; angle *= c;` keeps operand order and stops the `fst` forward.
- `dir += x` then `Normalize(particle->fc)`, not `Normalize(dir)`, gives fstp plus reload. `fld st0; fld mem; fcompp` needs a float-typed value and the limit read through an inline returning double.
- T-phase interaction: naming a local can fix a sum order and move a later tie; dropping another referenced local restores it (0x60C050).

## Loops and charge (Scout658)
- TibSun pointer walks can be VC6 strength reduction, so write the real index loop. A vector used in the loop is read before the guard; one used only in the guard sinks.
- A non-inline callee near the 175 cap gives a narrow IL window: more charge per site, and two more locals stop it expanding at all.
- A local helper taking the record and a const& gives a charge without a global operator= changing other rows. Naming values in a helper raises its size, so a later ctor site can be refused (0x565E20).
- `rowx += count; x = rowx` rotated three long webs in 0x563D80.

## Byte reads, blend loops, wparam (Scout659)
- A bool at a 4-aligned struct offset read through the struct object gives `mov ecx,[x]; and ecx,0xff`; the extern bool alias gives `xor; mov cl`; offset +1 is a plain byte read.
- Blend loops: compute `dest = &buffer[out]` inside the loop, write `int in = y*pitch + start_x` before the branch, and `out++; in++` at the bottom with `x` only as the counter. That puts the `lea` after the guard and gives the original induction order (0x68CF90 went 84 to 99.55).
- `unsigned short code = wparam >> 16; if (code == 0)` gives `shr; jne`, not `test reg,0xffff0000`. `int value = (unsigned short)(wparam >> 16)` plus a second `(unsigned short)(wparam >> 16) == 1` keeps wparam intact.
- Hypothesis: scratch registers rotate eax, ecx, edx and the rotation persists to the function end. Code-free temps did not move it, so adding a wrapper is not a reliable lever. Declaration order fixes store order but all six orders left frame slots unchanged on 0x6340F0.

## Y-sum parity and small forms (Scout660)
- Y sum parity ignores k probes. A named pop slot (`CellClass **slot = &stack[count]; cur = *slot;`) plus `visited[..]++` flips it, `= 1` does not; known-zero threading keeps the `++` store a plain `mov 1`.
- A register plus a write-through home can be two variables (zoneptr/zonerow, like TibSun's x/rowx). A pointer assigned before `1 << n` lands in edx because ecx holds the count. `Rect bounds(0, 0, w, w)` after the other inits delays `xor ebp`. `walk -= Cell(1, 0)` gives `dec word` plus a rewrite of the other coordinate. Writing Cell arithmetic through the real operator- raises the /Ob2 charge at the natural place.
- Rewriting a low draft to TibSun flow or correcting it against the disassembly pays more than variants (0x564290 +24, 0x569320 +35).

## Free sites and helper size (Scout661)
- TibSun's one-line `Get_Cell_Data` is IL <= 40, so it is a free /Ob2 site; a long cast form was charged at every use, and that alone flipped a loop Insert inline (0x586340). Inline decisions are monotone in the helper's size.
- `float &first_key = nodes[0].Key;` fixes store order, as in Create_Resource_Patch.
- An inlined copy can differ from the out-of-line row: Grow_Water's score copies use TibSun's RMG_RANDOM_DOUBLE2 order, while 0x582970 keeps `weight*heading+rand*jitter*unit`. A separate inline helper fixes the fxch family.

## Layout, loops and refusals (Scout662; tool Scout662/t/fa.sh + fm.py prints a frame map with reference counts)
- Frame slot order follows reference counts. A join statement sinks arm tails but drops the variable's frame refs by one.
- `switch (found) { case false: S; break; default: F; }` lays F first with S earlier in source; plain if/else and goto do not.
- `for (;;)` and `do ... while (true)` rotate the loop, `while (true)` does not; an inlined `if` in the head stops the rotation.
- Reading a field twice keeps a one-use pointer local alive while CSE still gives one load.
- One extra inline depth moves a nested refusal: an accessor at the same level as 0x54FA60 took 0x566340 to 18 of 18 calls.

## Threading and slot weight (Scout663)
- `if (placed && success)` with a named bool keeps `success` in memory, because threading would have to cross the placed test; it also fixes block layout.
- `while (queue.Count != 0) { if (queue.Count >= 1020) break; ... }`, then the drain loop, then `if (processed > 1) return true; return false;` gives the shared false tail through threading.
- A rotated top-register tie unmoved by k probes was init order: `int attempt = 0` after the random offset.
- Rows accepted in another population can expand through file-local `inline` definitions in the draft, with no allow_split.
- Stack slot order is weighted by references that survive to final code; code-free references do nothing.

## Cross-jump and callee-saved swaps (Scout664)
- Reading both coordinates of a const& into named ints before the arithmetic keeps Y in a callee-saved register and can flip a whole-function callee-saved swap (0x566340).
- In a cross-jump the first copy in layout stays unless a later one falls into the join. Scheduling runs after tail merge. A rotated loop, or a second call at the bottom, adds one frame ref (the copy's lea) without changing the tail. Loop-bottom tests known true fold before tail merge, so the join block stays empty.

## In-place Cell arithmetic (Scout665)
- `tail += Cell(a, b)` and `bias -= Cell(...)` in place of TibSun's field assigns fix eax/edx choices, the literal `mov word [m],0` and the zero CSE; the unused `Y += 0` keeps the temp live.
- `short offset = down ? forward : -forward` replaces TibSun's `backward` local. Recomputing `second.Y - first.Y` instead of naming height keeps abs in eax and gives `lea eax,[ecx+1]`.
- TibSun's int margins are needed on the Plan rows: Rect margins reach shape 100 with the wrong frame order, and int margins also flip the operand tie.
- Correction to the k-probe note: a referenced local (`Rect const &area = rect`) flipped a `[rect+8]/[rect]` load tie that k probes did not.

## Labels, duplicated tests and RMW (Scout666)
- A label's return block moves to just after its last `goto`, even one that folds. Gotos before the last site share one block; plain `return`s after it get inline epilogs.
- Source can duplicate a test: giving each distance arm its own `if (range > 0 && dist > range) return false;` took 0x6C5570 from 80 to 91 and fixed frame slots and ebp.
- 3D `fild` order depends on the key: `double y = c.Y` first, or any extra referenced local, gives Y,Z,X.
- `*x += y` uses three instructions when a scratch register is free and `add [m],r` when none is, so an RMW mismatch means a register web difference, not a statement form. High-byte tests always load a register, so a lone read can look like a CSE web.

## Refusals by counting, constants and self-copies (Scout667)
- To refuse a ctor, count the inline sites after it: survey with throwaway `Nop()` sites, then replace them with real one-line helpers, or move IL into helpers to lower the root budget. Real rows defined later in the unit still inline (Map_Clamped_Gaussian).
- `double const &h = data.f; data.f = h;` keeps a self-copy as integer moves; a plain self-assign vanishes.
- One shared `tries` int gives the shared frame slot. A named `position` before `Map[]` fixes an eax/edx tie.
- An implicit `DynamicVectorClass<double>` needs an @ref for each emitted COMDAT.
- A small `differing_bytes` can be a wrong constant binding the score does not show: 15.0 exists at both 0x7a5398 and 0x7a5ce8; cmp.py plus report.json find it.

## Scratch rotation and duplicated statements (Scout668, 0x6C9260)
- Scratch registers advance round robin through eax, ecx, edx; ecx is skipped when reserved for `this`, and al byte loads do not advance it. This confirms Scout659's hypothesis.
- Tail merge runs after register allocation, so a cross-jumped copy still advances the rotation. If an if arm ends in `jmp` and the register sequence after it is shifted by one, a statement is duplicated in both arms. That took Can_Fire from 82.58 to 96.77 with the land test in each arm.
- Which arm uses `return 5` and which `goto ILLEGAL` picks the surviving copy. Nesting the rest in `if (weapon != 0) { ... return 0; } CANT: return 6; ILLEGAL: return 5;` keeps CANT last with no folded goto.
- A memory `test byte [m],imm8` of a parameter changes the register piece of its later refs.

## Threading, tails and constant registers (Scout670)
- `int limit = f; if (f <= 0) {...} if (limit <= 0)` keeps both tests; two tests on `limit` thread away.
- An inlined real row shows up as one shared cross-jump tail. All four case tails merged only once a combined `||` return was split into two ifs.
- `while (true) { ...; k++; if (k >= 3) break; }` gives `jge out; jmp top`. A plain named temporary (`int id = over[i];`) moves the scratch rotation by one.
- 46 repeated `X = -1` stores put -1 in a register, and later uses go through it, including inline strlen; pushes alone do not.
- Dropping named locals lowers S and can stand in for one more inline site.

## Region and ramp forms (Scout669)
- `(second-Cell(span,0)).X-first.X-5` through operator- keeps the word subtracts on X-field rows; North also needs `bias.X =` rather than `bias +=`.
- `Rect rect2 = rect1` gives register copies. `for (; tries < 200; tries++) { if (result) break;` keeps a head test that do-while rotates away. A single flat do-while with `||` restores frame and index CSE.
- `if (fail) x = false; if (x && y) {...}` as two statements stops a cross-jump. Repeating `Is_Valid()` in both arms keeps a second test that nesting threads away.
- The block scope of one Cell can decide constant caching across a whole function, so test scope before constant probes: `Cell end` declared in each loop body took 0x587330 from 78.56 to 99.06.
- Unused file-local inlines are not budget sites. Count with Nop probes, then replace them with real helpers.

## Forward substitution and threaded flags (Scout672)
- Tree forward substitution is block-local and runs before threading. A local defined in the block before a known-result flag test stays a web, even though threading later merges the blocks: `bool valid = false; int first; if (a && b) { first = start.X; valid = true; } if (valid && end.X - first >= 6)` gives a right-operand-first `sub`. Helpers, casts and negations all normalize to one tree.
- Rotation model: pure eax/ecx/edx rotation where a register still live as a later operand's source is skipped.
- Twin arms need not share a form: each read order is what the rotation at that arm needs (0x582FD0).
- A read through inline `Get_Cell_Data(cell->MapCoords)` keeps the second Y read uncached and the cell pointer in ecx.

## Argument hoists, tails and local statics (Scout671)
- A call inside a ctor argument hoists the whole argument before the pushes; an inline wrapper hoists only the call (0x47C3A0 went 83.85 to 98.91).
- A row written out with loops can exceed the auto-inline cap; its form with helper calls inlines into later rows.
- `lowcolor = X` in each arm plus one `highcolor = lowcolor` after the if/else gives the shared tail; `highcolor = lowcolor = X` does not.
- In a function-local static table, leading constants stay in .data and everything from the first non-constant element on is stored by code.
- shape_file.hpp in a unit without an empty rect row needs SHAPE_FILE_EMPTY_RECT, or the unit gets an extra initializer and acceptance refuses .CRT$XCU.

## Statements first, doubles and literals (Scout673, 0x57ECF0)
- Fix statements first: Seed_River's frame and `this`/zero registers came right on their own, and slot packing followed reference counts.
- A hand-written copy of an inline shows as left-to-right evaluation and a plain variable pushed as ints.
- A second named double keeps a value on the x87 stack (`fst m; fld st(0)`). `fst dev; fadd lo` versus `fstp dev; fld lo; fadd dev` follows declaration order of dev relative to lo.
- A constant left of a compare after folding needs the row written `mean-deviation > maximum`. The same double at two addresses is an extern const double. A dword load before a byte store needs a named int.
- A 1 ulp wrong literal scores 100 but fails acceptance with "Unsupported allocatable data section"; check literals with Scout673's rd.py.

## Second-site inlining and facing ties (Scout674, 0x4F4070)
- A wrapper one level down moves a callee out of line at that site only; it was the only form that did (Scout642 had ruled out charged units there).
- `int n = 0` placed next to a loop init coalesces the zero with the index, which put the index in memory as in the original (73 to 96.57). Reusing locals across blocks fixes frame slots. A live named local holds a register across an arm, so dropping it matters.
- diff_candidate scores unbound string literals as fine but acceptance refuses their .data: rows with strings need the @ref, and /FAs gives the mangled name.
- Constant-facing tie: the first two distinct facings give `add dx,[global]`, the rest `add dx,[esp]`; with three distinct the set decides, and sets containing 0 or 7 stay all global.
- `T result(rect1)` is not the same as `T result = rect1`. A false epilog copy whose next statement is adjacent is removed; one whose next statement is far away stays.

## Case order and spills (Scout675)
- Switch source order follows TibSun (E, W, S, N on Waterfall), not numeric case order: reordering alone took a draft from 22.55 to 50.47.
- `mov byte [eax],0` beside a zero cached in ebp is forced, because ebp has no byte form; it is not a separate statement.
- A spilled pseudo shows as defs `lea ebx; mov [m],ebx` and reads `mov eax,[m]; add edi,eax`. If the original spills a pseudo ours keeps in registers, look for a statement diff first: Seed_River's equivalent came right only after its statements did.
- Arms must start with a differing statement, or identical X/Y stores hoist above the `if`. `for (int side = 2; side != 0; side--)` gives the `jmp` over the loop-top `xor`.

## Dead slots and statics (Scout676)
- `Cell x = Cell(0,0)`, unlike `Cell x(0,0)`, leaves a dead temp slot, which made the 0x4F03C0 frame size exact.
- Early Adjacent_Cell sites refuse op+ through R//N while late sites inline it, so in-function site order alone explains mixed call and inline sites.
- A function-local Cell table with an empty atexit thunk implies an element type with an empty dtor, built from Cell temps; the frame carries one temp per element.
- An inline helper taking double parameters fixes int-to-double evaluation order that an int-parameter helper gets wrong. A reused byte slot can be one bool reassigned.
- Gap: frame order follows sharing groups, not single-variable reference counts. The Study42 sort rule did not predict the 0x4F03C0 layout.

## Promoted temporaries and CSE rank (Scout677, 0x57FF20 from 58 to exact)
- `Rect pre(0,0,0,0)` then `pre = Rect(...)` in each arm makes a promoted temporary, which decides which field pseudo spills; field assigns do not.
- Repeating an expression instead of naming it makes a CSE temp that ranks differently from a named local, and that decides which pseudo wins the register. `x_offsets[direction / 2]` twice with no index local gives the `shl eax,2` CSE.
- `Rect a = src; a.X += 1; a.Width -= 2;` gives `inc` and `sub r,2`; ctor arguments give `add r,-2`. `center = Point2D(a, b)` fixes read order. `base + Cell(-1, 0)` and `base - Cell(1, 0)` differ.
- Rows ending in switch tables need table-inclusive body_bytes.

## Flag reuse and aliasing (Scout678, 0x4F2350 from 88 to exact)
- `flag = !(a && b && ...); if (flag) {B} else A;` places B after the next unconditional jmp and lets A fall into the join; plain `if (!cond) B else A` normalizes and does not move it. Scout678's scan.py lists matched rows with out-of-line arms that jump back.
- A store through a reference blocks later loads from scheduling above it; a direct this-member store does not.
- Aliasing is flow-insensitive: an address-taken local keeps store order against pointer loads even when the address is taken later.
- The threader sees through named bools, copies, inline helpers, joins and De Morgan forms; only a path with the flag unknown keeps a test.

## Frame maps and slot sharing (Scout680, 0x4F03C0 from 63 to exact)
- Scout680's fa.py (a /FAs frame variable map with ref counts and first references) and rm.py (raw original-to-ours slot map) replace blind frame hunting.
- Slot sharing groups reveal source objects. `Point2D delta` with field assigns replaced two ints and explained `neg; neg`: X stays in memory, Y is forward-substituted. Wrapping a body in `else { }` lets a local share a temp and changes a static's mangled scope. Function-block address-taken objects overlap everything in the block.
- Tied temp slots came out right once one temp's ref count was right. `Map[Adjacent_Cell(...)]` without a named cell fixed registers.
- A member rename must use mangling_rewrite: a plain `renames` entry leaves symbol_prefix stale.

## Second frame sort, ternaries and hoists (Scout679, 0x529870 and 0x6D4920)
- Above about 0x80 local bytes a second sort orders slots by density (summed refs of the sharing vars / size). All-tie behaviour: for each lo, mid = lo + (hi - lo) / 2, swap A[lo] and A[mid]; lab/sim5.py reproduces N=35, 36, 37 and 46. Its input is the first-phase order (size, refs, last ref), so a char array's declared size inside its 4-byte rounding changes key order with no code change (`suffix[10]` vs `[12]`: 95.09 to 99.75). Test frame ties that ignore declaration order with array sizes.
- A function-scope buffer overlaps a pre-loop temp, so two loop temps share a slot instead.
- A ternary of named int locals (`i < n ? full : empty`) stays a real conditional until const-prop, so the setcc runs before the arg temps; constant arms fold in place at the push (60 to 91).
- `dec` after a loop guard means a hoisted value: write `for (j = rows - 1; ...)` inside the outer loop, not a precomputed count.
- Commutative imul order can flip on an unrelated temp elsewhere in the function; source operand order does not reach it.
- diff_candidate shows nothing for what acceptance refuses unless bound: the `""` literal (.bss COMDAT), every string, vtables, ??_G, GenericNode and ??1INIClass COMDATs, and `_$E`/`$S` shifts in later rows. Scout679/cs.py lists code sections with no ref.

## Hidden results and budget sites (Scout681)
- `lea ecx,tmp; push y; push x; call` with no result pointer pushed is `__fastcall` with the hidden result in ecx and a by-value struct on the stack; it looks like a thiscall ctor.
- `bool techno; if (p != 0) { techno = p->IsTechno; } if (p != 0 && techno)` explains a dead byte store.
- Double locals inside an inline Length hoist ahead of the rest of the expression and give dot-before-sqrt order. An inline Percent_Chance reads the Rules value before calling Random.
- Coord_To_Pixel with its result ignored expands with the compares dead; a site's depth decides which nested callees stay out of line.
- Point2D-local sums (`Point2D offset(0,2); a += offset; b += offset;`) supply pending inline sites and emit nothing extra. Find the count with Nop probes, then use real statements.
- The Print_CRCs counter depends on which real declarations land with a header change: over one header, k=2, 4, 5, 7 extra decls were good and 1, 3, 6, 8 bad.

## Constant webs by threshold (Scout682, Ship 0x676F60)
- Constant webs compete by use count, not by a pseudo at the peak (this corrects Scout655): one more zero use at the tail makes `xor edi,edi` win, which flips the head immediate and the edge defs. A literal 0 one inline level down counts; nesting it through a helper leaves a local `xor edx,edx`.
- A named `CoordStruct partial(0,0,0)` is block-live, and that alone fixed three slot groups.
- `double x, y, z` in that order with `x*x + (y*y + z*z)` gives X,Y,Z fild order.
- `Point2D offset = ptr[..].Offset` direct-init reads X first; assignment reads Y first. The right operand of != is evaluated first, so `Cell here = pos.As_Cell(); if (here != head.As_Cell())` gives left-first order.
- Scout682's om.py maps each frame object to its original slot, with push depth corrected. scan.py runs a source toggle across all 8 T phases.

## Label locals and inlined members (Scout683)
- A 4-byte local sorted into the 8-byte group is a Point2D with a constant field (`Point2D offset(0, rect.Y + 1)`), and `pixel - offset` supplies sites.
- A separately named pointer plus a repeated expression gives a CSE temp, so the pointer spills at once.
- A charge of about 54 to 130 before a site splits depth-3 sites; it must sit where it does not disturb argument evaluation (a wrapper on Fancy_Text_Print is exact, one on CC_Draw_Shape is not).
- A member with "no callers" may be inlined: WM_CHAR is really `if (flag) Put_Char(wparam)`, which alone explains a last-site call. Check such members before adding pending sites.
- A duplicated case tail can be fall-through. Mixed `jl top; jmp tail` is a for-loop with a guard, not `while (true)`. TibSun's `-30 + pixel.X + 30` is really `pixel.X -= 30; point.X = pixel.X + 30`.

## Frame placement and address-taken order (Scout684, Ship 0x676F60 from 86 to 99)
- Frame objects are placed in descending last-ref order, newest compatible slot first. One named `Cell gate = c.As_Cell();` made a temp share a slot and fixed the frame size.
- An address-taken local's store sits ahead of later reads, forcing a copy: `Cell a0 = ...; Cell b0 = ...; Cell newcell = ...; if (a0 != b0)` keeps the reads first.
- T phase depends only on the total count, not where a local sits, and the distance between two sites matters, not just the total. Identifier renames change nothing.

## Tactical forms (Scout685)
- TibSun's `LONG x, y` with `(int &)` casts raises S just enough for one more inline site, which merged a whole block. `-1 - 15*h` puts the product in a fresh register: name both products before the second call.
- The field choice decides which operand `add` writes. A CSE reload on an edge means an operand-order tie made a word load available from a known dword; fixing the tie brings in the reload and the rotation together.
- A named pointer with an unnamed `ptr->Type` CSE fixed an arm-by-arm rotation; a named `type` did not. Slot sharing across sections exposed one reused pair (`start`, `dims`): 65 to 93.
- Nested expressions in an argument can refuse where a named `Cell cell = ...` expands.
- `bool inrange` set in both arms keeps `setle; test; je`, and the tails cross-jump. `bool clear = f() == 0; return clear;` gives `test; sete`; plain `return f() == 0` gives neg/sbb/inc.
- Right-associated `X*X + (Y*Y + Z*Z)` reaches the x87 order; named doubles and left-associated forms do not. Promoted double locals keep the same order under any spelling.

## Address-exposed joins and copy order (Scout686, Ship and Drive to exact)
- Y and Z reads hoist over an X store only when coordinates come through a local pointer; a repeated member gives the original order, as its CSE temp keeps the struct copy in order. A copy from a CSE temp also survives copy-prop (`lea eax; mov ecx,eax`).
- `mov esi,eax; test esi,esi` needs the join variable address-exposed: `T *object = cond ? a : b; T *&ref = object; T *occupier = ref;`. `T *&`, `T * const &`, `T **p = &o` all work; inline reference parameters fold away. `mov R,eax; test R,R` is the default only after calls.
- A `do` head with a same-condition bottom threads away before copy-prop. T phase is exactly mod 8.
- Scout686's mini.py with mi.sh compiles a small standalone file with /FAs in about 3 s; it reproduced both residues outside the 5.7 KB function. Reduce to a small test when a residue survives many variants.

## Y order and control flow (Scout687)
- Y operand order can follow control flow, not T: `if (range <= 0) continue;` plus a `for` gives scan-first; dropping the guard so the `for`'s rotated guard does the `jle` gives adj-first. T-only probes never reach Y.
- `Point2D point = Point2D(a, b)` keeps the point in the frame; `Point2D point(a, b)` promotes it.
- A named `CoordStruct coord = bptr->Coord;` made 0x6AA300 exact.

## Hoisted loads and early returns (Scout688, Start_Of_Move)
- A member load used in an expression with a call hoists over the call, and that web can take the register the original gives another value. A named reference (`CellClass const &here = Map[...]; here.x + (...)`) fixes it: 62 to 77.
- Inline sites go monotonically with N: one form at seven sites gives refused (ctor, Length), then refused (ctor), then none.
- A pure temporary shares a dead slot and can fix the frame; a named Cell never does.
- `if (!(a != b)) return false;` lays the block far and cross-jumps. `A || B` return goes far; `A && B` stays inline. `if (!ok && !same) { Y; return false; } T; return true;` gives one block order.
- Scout688's seg.py is a call-aligned segment diff that ignores frame offsets; difflib under-reports on misaligned rows.

## Depth budgets and traps (Scout689)
- TibSun's explicit Absolute plus minus can be a Coord_To_Pixel statement with Absolute refused at depth 2; a copy keeps the pixel out of memory.
- For "A in, B out" at depth, with m = b - s_parent, it needs m - s_B < s_A <= m/2. A bigger S can raise B above 1000; charging spend and adding N are not interchangeable.
- `extern Rect x;` after `Rect x(0,0,0,0);` in one TU re-emits a dynamic initializer (stray `_$E85`, refused as .CRT$XCU #2).
- Identical repeated global stores are removed as dead, so zero-use probes must write distinct array elements.
- 0x6A2900 is exact as TibSun's `Vector3 position(point.X, point.Y, 0.0)`, which explains a Z-first store.

## Threaded else and exposed tests (Scout690, Start_Of_Move twins)
- Dropping `else nextface = facing` lets threading produce a far `jle`.
- A stop copy without `xor` needs an address-exposed test: `bool found = ...; bool &result = found; if (!result) {... return found;}`. Plain `if (!found)` folds to a constant and merges with the other site.
- A two-arm `if (train) cando = 0; else if (crusher...) cando = 0;` fixed a join reload and cleared several rotation residues at once.
- `FootClass *unit = LinkedTo;` before a test explains a load ahead of the test. A scoped block around a named `CoordStruct center` fixes evaluation order and frame slot.
- A fild order of Y, Z, X comes from a rotated Length with declarations y, z, x. An inline chain's symbol depth counts toward T: a rotated helper needs the same depth as the plain one. Removing named locals is not always the inverse of adding probes.

## By-value parameters and Matrix3D (Scout692)
- A by-value parameter that is never exposed keeps fields in registers (`to.X` and `to.Y` in esi/edi): write `x = CoordStruct(to.X, to.Y, to.Z);` and `Map[CoordStruct(to)]`. Field-written copies give frame misses (Jumpjet Move_To 35 to 94).
- `f(CoordStruct(cell))` evaluates in place; `f(Cell_Coord(cell))` hoists before the pushes.
- Draw_Matrix: `Matrix3D transform` at function scope, `transform = transform * Get_Slope_Matrix() * basemtx * rotation;` keeps slope temps in the multiply statement. An empty `~Matrix3D() {}` stops the by-value slope helper from inlining.
- Frame order follows final-code refs: code-free references and dead objects never move it, a real extra ref does.

## Pointer copies, halving and missing defs (Scout691)
- A named `CoordStruct const &x = f(); Coord y = x;` is the only form that gives the pointer copy `mov edx,eax`; no inline parameter form does.
- Y/2 at dim+4 with Z at dim+8 means halving in place: `int x = dim.X / 2; dim.Y /= 2; int y = dim.Y;`.
- IL costs: `{}` adds none, a pointer double cast a little, a real call +4, a named local +6; a window can be 2 units wide.
- A reload on a single-predecessor edge means a missing def: `result = 5;` falling into `if (result == 5) return 5;` gives both the reload and `mov eax,5` through threading.
- `CoordStruct half = dim / 2` with an inline operator/ refuses only the second nested ctor, because the zero-divisor ctor folds.

## Declare-then-assign and slot lifetime (Scout693)
- `T r; r = f();` in an inlined helper fixes reload order across arms, and the out-of-line copy stays exact.
- Temporaries and distinct named Cells share one slot by linear lifetime. A repeated store to one slot means separate objects.
- A named copy of a returned struct adds a register copy and rotates following code; `a + (Map[c].f() - b)` removes it.
- A default-first pointer (`p = &A; if (...) p = &B;`) keeps the source live, so `p` cannot coalesce and gives a register compare.
- `Distance(Point2D(a), Point2D(b))` reads the right argument's coordinates before a virtual call on the left.

## FP past rep movs and layout (Scout694)
- A `float const &` parameter on only the first argument of an inline ctor helper exposes that temp, so its fstp stays after `rep movsd` while fld/fchs hoist.
- `fstp` then `fld Y, Z, X` then `fld st(n); fmul` comes from double locals declared y, z, x with `x*x + z*z + y*y`.
- A later row can inline only when its callee is one call deep. A false block follows the memory-last goto. Compare-chain switches lay out default, then cases descending.
- Scout694's crt.py lists $E/$S and init relocs that a local score does not show.

## Array sizes and timers (Scout696)
- A frame slot with no references can be an array's declared size inside its rounding: check accepted siblings first (`char options[132]` in 0x755180).
- Timer residues with a `mov ecx,esi; test ecx` shape come from a Value form that rereads DelayTime on the idle path; named, reference and inline-parameter result copies all fold.
- In a label group at function end, source order of the blocks does not change layout. Some sum ties are not T or offs ties: real statements added at the top did not move them.

## Selector locals and helper temps (Scout697)
- A named selector local can hold a frame slot: replacing it with `if ((a && A) || (!a && B)) { shape = a ? A : B; ... }` flipped two slots. That order ignored ref counts, last-ref, first-def, alignment and aggregate class.
- Moving two tests into an inline helper fixed frame groups; the density sort moved when one ref left a temp group. Temps in a helper appear block-lived (inferred).
- `xy + Point2D(o.X, o.Y)` reads the offset first; a copy-form `Point2D(o)` does not. Removing a named reference can save enough budget to keep sites inline.
- VC6 mangles a free `operator*` as `??D@YI...`; an @ref to it scores 100 locally but is refused at acceptance as unbound. rl2.py lists unbound relocations plan-wide.

## Web weight, narrowing and islands (Scout699)
- A copy local in one branch halves a web's weight and flips esi/edi without emitting code.
- Stepwise `x = a; x -= b; x -= 3` on an unsigned short keeps the 16-bit op on the first operand; `a - b - 3` narrows the wrong operand and hoists a push.
- A 12 B coord written only X,Y through a by-const-ref inline drops the Z store.
- VC6 moves an island ending in `jmp next` past the next barrier when a threaded xor reaches ELSE. A named struct of doubles with an inline member Length spills only the last value; scalars never spill.

## Hidden counters and regimes (Scout698, Dropship 0x4A6B90)
- ebp is never a base without a disp, so `[Data+ebp]` carries no order information.
- Some sum ties ignore T, self-assigns, plain calls and plain loads, and move only with statements that make a CSE or IV temp, even after the site: they behave like a hidden counter.
- Dead local count sets regimes almost regardless of position (0-9, 10-11, 12-20, 21+ on Dropship); probes inside one arm do not act like probes at the top.

## MIN spelled out and Point2D forms (Scout700)
- TibSun's MIN/MAX macro spelled out with the repeated expression differs from a named `last` (94 to exact).
- A zero constant takes the register of the web defined just after it unless the source assigns that web first.
- `Point2D p; p.X = q.X; p.Y = q.Y - v;` gives lea/sub and the original registers; `p = q; p.Y -= v` gives shl/neg; `p -= Point2D(0, v)` keeps lea but loses the registers.
- An ebp frame in an /O2 row plus a dword-compared global in a tight loop points to original inline asm: stop drafting.
- Low seed scores can be stale; redraft before parking.

## COM coordinates and prior rows (Scout702)
- Is_Moving_Here takes a plain CoordStruct: the conversion operator hoists X,Y,Z into three registers ahead of the test (39 to 85); `MapCoords.As_Coord()` made it exact.
- A named `bool flat = otype->DrawFlat` flipped three register webs. `Point2D point = offset() + xpoint` with `point -= clip.Top_Left()` gives the original register order.
- With /Ob2 a row in the same unit inlines at its call sites, so a missing out-of-line ctor at a site can point to an earlier row's form: one row can be exact in five forms that differ only at the inlined site. TU position does not decide this.
- `Rect rect = Rect(0,0,0,0)` versus direct init changes which temp shares a slot and splits the zero web.

## Named bools and joins (Scout703)
- `A && B` tests hoisted into named bools from named locals stop threading from dropping a useless compare. A `jne` from one chain into another chain's assign blocks is `if (Count() || p == 0 || p == 1 ...) { same chain }`, not two chains.
- A vptr reload after a nested virtual argument means a separate statement: within one expression tree VC6 CSEs `*this`.
- `mov eax,K; jmp` into `cmp [r],eax` is a join on a named value.
- Scout703's sh.py is a structural diff with registers and frame offsets normalised: the fastest first read of a new draft. tp.py + ts.sh run a T phase scan.

## First function of a TU (Scout701)
- VC6 does not tail-merge two identical tails in the first function of a TU; any function before it, even a trivial one, turns the merge on. Blank lines before it or functions after it change nothing. Check this for rows that differ only by a merged tail.
- Local constants count as locals for T: plain `const int` locals act like probes, `static const int` do not.

## Case joins and add destinations (Scout704)
- `mov eax,K` plus a backward `jmp` from a case body means source copies merged after register allocation, such as per-case `if (result < 5)` with one case falling into default; a join on one local cannot produce that layout.
- A statement adding `this` refs can flip this/cell in ebx/ebp, and any non-`this` IL in the loop flips it back, so the weight looks like refs over span.
- `else { if (!pressed) call }` gives a threaded jump past the call while keeping setne/test.
- X+Y is canonical in VC6: Y+X, split sums and named copies give the same code; the add dest flips only when an operand stays live past the add.
- A float length temp folded into its one use lifted Fire_At from 62 to 71.

## Pointer reads and negation pairs (Scout705)
- `CoordStruct base = house->BaseCenter; Coord_Distance(base, center)` gives `lea r,[member]; mov edx,r` pointer reads; the same copy written directly folds (62 to 78).
- `bool const &on = e; bool off = !on;` keeps a second flag test after a failed chain.
- The order of a virtual-call `==` pair flips once two `bool x = !y` values exist anywhere in the function; ints, compares and copies do not count.
- `double dy = -delta.Y;` fixed fstp order and a tail push order. A constant used inside an inlined body in a loop joins and hoists the web of the same constant in the outer function.

## Float lengths and evictions (Scout706)
- TibSun `TPoint3D<float>::Length` with `(double)X*(double)X` casts spills X and Y to the struct and keeps Z on the x87 stack. Sum order z,x,y comes from `double s = Z2; s += X2 + Y2;`. Unnamed int Length casts give the X2 and whole-sum FP CSEs on their own.
- A long pseudo is evicted around cold arms and reloaded later; reloads seem to add weight, so one eviction can cancel the next (inferred). TypeList::Pick turns off the count CSE, as its inline `this` hides the member read until after CSE.

## Reload order and first fit (Scout707)
- Loop-region reload order is the reverse of the symbols' first occurrence in the IL, not declaration order. A code-free reference placed before the other's definition flips it.
- `Point2D delta; delta.X = offset.X; delta.Y = offset.Y; int dy = -delta.Y;` took a row from 64 to 99.9.
- A temp's slot follows first fit: a block-lived named or `$S` result conflicts with the earlier temp and pulls an 8 B double into its 12 B slot.
- In /FAs listings a pointer load hoisted above a guard can mark an unmerged return path.

## Temps, call order and arm folds (Scout708)
- `CoordStruct x; if (a) x = f(); else x = g();` shares one return temp across arms; a ternary keeps two.
- `Random_Pick(0, X)` computes the Random `this` after the pushes; `Random()(0, X)` before.
- A named `float length = (float)sqrt(sum); return length;` inside an inline Length sinks the fstp past the next load.
- A member-style inline for a field read stops CSE across a virtual call (83 to 94).
- Per-arm `faceto = Dir_To_256(...)` keeps the `and eax,0xff` that a single assignment folds into movsx. `int facing = 0` before the first test gives a shared zero web.

## Reassignment and zero webs (Scout710)
- Reassigning one variable (`here = Map.f(here, ...)`) gives a `mov ax,dx` X copy and a shared slot; a new named Cell does not.
- Wrapping distance in inline helpers keeps Center temps block-lived; three distance sites in one `||` statement otherwise each hold their own temps (frame 0x80 to 0x54).
- `default: break;` on a switch can give the zero constant a register web across the whole function.
- Tail merging and a far earlier vptr register can flip on a local changed much later: treat these as the hidden-counter class.

## Dying locals and FP operands (Scout709)
- An add destination can come right when a call result is a dying local inside an inline: `static inline int Bridge_Height(coord, int &ground) { int height = call; ground = height; return height + j; }` gives `add eax,ecx`; direct forms stay flat.
- `double gravity = Rules->x; velocity.Z -= gravity;` gives `fld; fild; fsubp` on a Vector3 (89 to 99).
- An inline's return slot adds frame bytes and moves temps: the assigned form and the return-ignored form differ by the return slot.

## Real helpers and arm order (Scout711)
- The real Process_DD_Result with its early returns, called before `result == DD_OK`, lets threading produce far arms; hand expansion does not (76 to exact).
- `Rect area(r.left, r.top, r.right - r.left, r.bottom - r.top)` keeps a width read ahead of a flag test; a plain int forward-substitutes into the arm.
- Statement order inside an arm decides the `and` destination register. `if (flag) {arm} else {...}` lays the flag arm after the ret; `if (!flag)` does not.
- A loop written `if (cb) cb(); while (...) { if (cb) cb(); }` supplies the fourth zero use that hoists zero into a register (58 to exact).
- A spelled-out MAX with `shift = MAX(a); shift -= MAX(b);` closed a register swap. Writing `box.Y =` into a Rect local fixed a `push; sub` tie.

## Temps within one statement (Scout712)
- Two temps inside one statement or one inline conflict even when the first is used up before the second is born. A coord whose Z store is dead vanishes from code but still takes a 12 B slot.
- `CoordStruct(Point2D(call), height)` evaluates the Point2D first, against right-to-left; a by-const-ref helper keeps height first.
- A this/position ebx/ebp swap tracks final-code base refs only: dead reads, aliases and inline params do not count.
- `R|G|B` reassociation does not follow source order; it looks register-need driven.

## Phase scan first, long compare lists (Scout713, Scout714)
- A first-read tie (`mov cx,[K+ecx*4]` vs `mov cx,[eax]; add cx,[edx]`) unmoved by about 60 helper forms was a T-phase tie: run tp.py before more form variants. Rows parked before Scout651 may hide the same tie.
- A repeated return in the one arm that would fall into the tail moves the whole case past the ret, and the copies cross-jump.
- `(Cell)` casts cost frame slots. Declaring a loop counter before the value it is added to swaps which register the `add` writes.
- `bool c12 = list; if (c12)` sets arm layout for long compare lists. `x != old_x || y != old_y` after up-front copies threads away compares on unchanged fields. One if/else-if chain with one trailing call tail-duplicates it into each arm; a per-arm call merges with a `jmp`.

## Statement shapes and budget (Scout716)
- An inline's statement shape sets its IL size and so the /Ob2 budget of its callers; put a per-population macro around it when other units need the old shape.
- `if (p) delete p` where `delete p` was meant changes the tail register and the IL. `(style & (unsigned char)7) == (unsigned char)7` gives `and ecx; cmp cl`. `RGB()` folds before IL and adds no budget.
- Slot and reload ties can depend on whether a double local is an FP-register candidate.

## Add destinations and depth (Scout715)
- Apparent tail-merge copy differences can be add-destination ties on an inlined Add, with the merges following from them. Phase period can be 32 in local count, not 8, in a large function; a Point2D temp counts as 2K only for sites after it. Calls and labels do not move those fronts.
- Rows out of line at the first case of a huge function, when budget is ample, mean an inline wrapper around the statement.
- `bool const &x = obj->Bitfield;` gives a dead byte store. `CoordStruct(coord)` as a by-value argument hoists X, Y, Z ahead of `Checked()`. `jl` on a loop over a static table means an int index loop, not a pointer loop.

## comip levels and budget probes (Scout718)
- Real comip levels decide the inline budget: `_QueryInterface` with its else arm, GetIID, Attach and an inline `_Release`, with the dtor calling `_Release`. One inline source then gave expand-release, expand-ctor and call-both at three rows.
- `clsid == CLSID` through the shared GUID operator== counts as a site. Hand-expanded blocks can hide real calls: calling the real row took another row out of line and fixed three rows.
- Empty inline probes after a suspect site measure the budget shortfall in about three compiles (kp.py, thr.sh); never deliver them.

## Real helpers hiding in units (Scout717)
- A row spelling out a long inlined list may hide a real predicate seed in the same unit: calling it shrinks callers' IL below the auto-inline cap. 0x5ED180's missing budget was a real call to the unit's mask builder.
- A new row that other rows inline needs body_bytes in the plan, or the composite pass splits and those rows are missed.
- A charged helper level over `if (Count) Get(...)` keeps a first lookup out of line; a by-value key fixes key stores.

## Pending sites and op- (Scout719)
- A nested argument does not divide the budget: in `f(a - b)` the op- gets all of it. One pending inline site after op- in the same body sends it out of line; wrapper depth with single-site bodies does nothing.
- Temps inside an inline wrapper always go to shared locals. Case layout follows source order, which limits the earlier by-value note.

## Unit rows as inline sites (Scout720)
- Unit rows can hide as inline sites: 0x5E7230 and 0x5E7620 are tests expanded inside 0x5E7EB0, and in Get form they reproduce its mixed lookups.
- `T *const &found = record; if (found)` stops known-zero threading past a record test. A root-level `unsigned int key` holds its slot, so later keys take a new one.
- A missing first-lookup call can be pending sites: about 38 empty sites without a helper level, 5 to 8 with one. Row wordiness moves the charge at its inline sites.

## Rect members and FP order (Scout721)
- `Rect(-2,-2,3,3)+point` is an inline over the out-of-line sum and corner ctor. `rect.Intersect(x)` as a member supplies the 16 B result copy that a free call does not.
- Vector3 Length with `double z, y, x` locals loads the FP stack as Z,Y,X. A `double dist2` with a `(float)dist2` final use flips which operand gets loaded.
- `StageClass(noinit)` with a plain CDTimerClass member stays inline where a wrapper goes out of line.

## Later rows and real calls (Scout722)
- A row can inline a later-addressed row: 0x5EDB20 is really a callback enumeration plus a direct call of 0x5EDD30, and that depth division keeps a nested row a call.
- An arm that looks spelled out can be calls of real unit rows. Pending inline sites decide which rows go out of line.

## Double locals and by-value Rects (Scout723)
- `double angle` plus `double scaled = distance` inside inline Move_Coord fixes the frame by 8 B: the double makes a Y spill and a call result share a slot.
- An inline taking `Rect box` by value and intersecting inside gives crossed Rect slots with no named local.
- `Cell offset(ox, oy)` and fieldwise stores each fix only one add destination; a ctor for X plus a separate Y update fixes both.
- `test ah,N` where `test esi,imm` was expected means the test is on a masked value, not the raw one.

## Consumption before a dtor (Scout725)
- Missing IL can be consumption before a ??_G site rather than a bigger dtor: `int size = (wcslen(text) + 1) * 2;` plus a per-arm `next` kept the delete out of line, where an `if (p) { delete p; p = 0; }` form stopped the dtor inlining elsewhere.
- Rect ctor charges can be the root budget: which Rects are field-assigned reproduces the arm pattern. A `while (length && w > max) text[--length]` loop gives the hoisted pointer and rotation.

## Repeated calls and short rows (Scout726)
- A call repeated inside an inlined loop means the call was passed as an inline argument: `Get_Unit_Count(x.Get_All_Totals(), x.UnitCount)` re-evaluates per iteration. A row defined later in the file still inlines.
- Reusing `i` for an outer loop, rather than a separate named counter, can fix frame slot order (97.12 to 98.14).
- `Timer(0)` picks the out-of-line long ctor 0x4DE1E0 with no change to row 0x6682C0.
- `return Anims.ID(anim) == -1 ? true : false;` keeps Is_Anim_Done and Show_Credits exact where the plain comparison does not.
- A shared-header overlay can change a fragile row's inlining: guard new declarations under a macro defined only by the new source (RA2_STATS_UNIT) and run fragile_probe.
- Real functions hide behind short inventory rows; check accepted-coverage gaps (Scout726 gaps.py) and carry body_bytes plus bound_evidence.

## Charged forms of exact rows (Scout728)
- A free callee under the 40 IL limit becomes charged with one extra statement: `bool done = ...; return done;` gives identical row bytes but makes the inlined caller call it out of line. A call site missing from a caller of an already-exact row means looking for a wordier form of that row.
- Pending-site budget shows up as a region, not a count: Presentation needed a<=3 and a+b>=5 (a sites at the end, b between two named sites). One free wrapper per string fetch met it, and only `Fetch_Text(label, file, line)` kept the register ties; `(label, line)` gave 93.99.
- A block-scoped redeclaration of a local in the last else moved two frame slots. A `char *` local picked the original induction variable. `int id2 = Players[i]->ID` fixed a load order and about 50 diff rows.
- Build_Hicolor_Pixel with constant args: the original evaluates shifts r|b|g, not header order.
- Original bugs to keep: the fame test reads hallfame[i].score with i stale at 10.

## Strength reduction and reused Rects (Scout727)
- An uncollapsed `row - row_base` can be `for (int index = first; ...)` with `(index - first) * height` written twice: VC6 distributes and strength-reduces, one imul feeds two slots, no CSE of the subs. No row variable exists.
- `int length = wcslen(text); text_28 = new((length + 1) * 2);` is the Set_Wide_Text form that holds in all its users.

## Frame maps and web evidence (Scout730)
- Map real target slots against our variables (Scout730 fm.py, em.py) before permuting declarations: it finds split variables directly. One variable's last three refs were a separate Rect in another slot group, and fixing that moved the density sort.
- A function-scope Rect overlaps slots across switch cases, so a later 28-byte object skips it and takes the next-newest slot. Case scope gave no change; function scope gave the original's order.
- Stack reads from a Rect home are not proof of an escape. A non-escaped Rect with spilled X and Y has the same loads, but the allocator sees different webs: escaped reads leave temporaries that keep a value out of esi and give `lea`; spilled webs give in-place `add` and `mov cl`/`test cl,cl`.
- A zero constant web needs a use inside its range, not one that survives to final code. `master ? master->alternate_cd : false` in one arm threads a literal 0 and flips X/Y from ebp to zero. Dead `= 0` initialisers and uses after the arm's join do not count.
- A bare `return 0` cross-jumps to the epilogue of the last `return 0` written in the source, whatever the layout order, and case blocks stay in place when moved in the source. The block carrying the shared epilogue schedules separately. A single-site probe sweep (rz.py) found this where diff scores stalled at 99.91.
- `Size = Size >> 1` versus `old_size >> 1` swaps which copy gets the load.
