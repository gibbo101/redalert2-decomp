#!/usr/bin/env python3
"""Turn a frozen Ghidra export into a compilable scratch candidate.

The seed is a starting point for iteration with diff_candidate.py, never
recovered source: Ghidra types, conventions, noreturn guesses and control flow
are hypotheses. The tool adds VC6-compatible Ghidra type names, declares each
FUN_/DAT_ reference with an address-bearing name (so diff_candidate.py binds it
automatically), turns __thiscall owners and callees into member functions with
the correct ECX ABI, and notes callees that already have accepted canonical
source.
"""
import argparse
import catalog_io
import json
from pathlib import Path
import re
import sys

REPOSITORY = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))

INCLUDE = '#include "shared/ghidra_types.hpp"'
MARKER = ('// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;\n'
          '// delete this line when editing it by hand.')
HEADER = re.compile(r'^\s*(?P<ret>[\w\s\*]+?)\s*(?P<conv>__thiscall|__fastcall|__stdcall|__cdecl)?\s*'
                    r'(?P<name>FUN_[0-9a-f]{8}|\w+)\s*\((?P<params>[^)]*)\)\s*$', re.M)
CALLEE = re.compile(r'\b(FUN_[0-9a-f]{8})\b')
# PTR_ labels may name their target kind (PTR_FUN_, PTR_DAT_, PTR_s_...); the
# trailing address is always the label's own location.
DATA = re.compile(r'\b(_?PTR_(?:\w+?_)?[0-9a-f]{8}|_?DAT_[0-9a-f]{8}|LAB_[0-9a-f]{8})\b')
STRING = re.compile(r'\b([su]_\w*_[0-9a-f]{8})\b')
# Horizontal whitespace only, with a mandatory identifier between repetitions.
# Masked long literals/comments can otherwise cause catastrophic backtracking.
LOCAL = re.compile(r'^[\t ]+([A-Za-z_]\w*(?:[\t ]+[A-Za-z_]\w*)*?'
                   r'(?:[\t ]*\*+[\t ]*|[\t ]+))([A-Za-z_]\w*)'
                   r'([\t ]*\[\w+\])?;[\t ]*$', re.M)
ASSIGN = re.compile(r'^(\s*)(\w+) = (.+);\s*$', re.M)
PARTIAL = re.compile(r'\b(\w+)\._(\d+)_(\d+)_')
PARTIAL_TYPES = {'1': 'uchar', '2': 'ushort', '4': 'uint'}
# Ghidra label names keep the label text, including characters C++ rejects
# (`s_Object_>RTTI_____d_007d8004`, `PTR_s_<none>_007cd978`).
LABEL = re.compile(r'\b((?:_?PTR_)?[su]_)([^\s,;()\[\]]*?)(_[0-9a-f]{8})\b')
# Absolute-address globals Ghidra names by type prefix (`iRam00000000`).
RAM = re.compile(r'\b([a-z]*)Ram([0-9a-f]{8})\b')
RAM_TYPES = {'i': 'int', 'u': 'uint', 'c': 'char', 'b': 'byte', 's': 'short', 'us': 'ushort',
             'f': 'float', 'd': 'double', 'p': 'void *', 'pi': 'int *', 'pu': 'uint *', 'pc': 'char *',
             'pp': 'void **', 'pb': 'byte *', 'ps': 'short *'}

# Only scratch declarations. Opaque SDK objects stay incomplete; do not invent
# their layout just to make a field access compile. No platform SDK is included.
SDK_PREAMBLE = r'''
typedef long HRESULT, LSTATUS, INT_PTR;   // LPARAM, LRESULT come from ghidra_types.hpp (unsigned)
typedef unsigned int SIZE_T, ULONG_PTR, UINT_PTR, DWORD_PTR, REGSAM, COLORREF, MMRESULT;
typedef short SHORT;
typedef unsigned short ATOM, WCHAR;
typedef int *LPBOOL;
typedef byte *LPBYTE;
typedef WORD *LPWORD;
typedef DWORD *PDWORD;
typedef UINT *PUINT;
typedef LONG *PLONG;
typedef void *PVOID;
typedef const void *LPCVOID;
typedef char *LPCH;
typedef const char *PCNZCH;
typedef wchar16 *LPWCH, *LPOLESTR;
typedef const wchar16 *PCNZWCH, *LPCOLESTR;
typedef wchar16 **SNB;
typedef void *HACCEL, *HBITMAP, *HBRUSH, *HCURSOR, *HFONT, *HGDIOBJ, *HGLOBAL;
typedef void *HICON, *HIMAGELIST, *HIMC, *HLOCAL, *HMENU, *HRGN, *HRSRC;
typedef HKEY *PHKEY;
typedef GUID CLSID;
typedef CLSID *LPCLSID;
typedef RECT *LPRECT;
struct POINT { LONG x, y; };
typedef POINT *LPPOINT;
struct FILETIME { DWORD dwLowDateTime, dwHighDateTime; };
typedef FILETIME *LPFILETIME, *PFILETIME;
struct SYSTEMTIME { WORD wYear, wMonth, wDayOfWeek, wDay, wHour, wMinute, wSecond, wMilliseconds; };
typedef SYSTEMTIME *LPSYSTEMTIME;
union LARGE_INTEGER { struct { DWORD LowPart; LONG HighPart; }; __int64 QuadPart; };
struct MEMORYSTATUS { DWORD dwLength, dwMemoryLoad, dwTotalPhys, dwAvailPhys, dwTotalPageFile, dwAvailPageFile, dwTotalVirtual, dwAvailVirtual; };
typedef MEMORYSTATUS *LPMEMORYSTATUS;
struct MEMORY_BASIC_INFORMATION { void *BaseAddress, *AllocationBase; DWORD AllocationProtect; SIZE_T RegionSize; DWORD State, Protect, Type; };
typedef MEMORY_BASIC_INFORMATION *PMEMORY_BASIC_INFORMATION;
struct MSG { HWND hwnd; UINT message; WPARAM wParam; LPARAM lParam; DWORD time; POINT pt; };
typedef MSG *LPMSG;
struct PAINTSTRUCT { HDC hdc; BOOL fErase; RECT rcPaint; BOOL fRestore, fIncUpdate; BYTE rgbReserved[32]; };
typedef PAINTSTRUCT *LPPAINTSTRUCT;
struct XFORM { float eM11, eM12, eM21, eM22, eDx, eDy; };
typedef int (__stdcall *FARPROC)();
typedef LRESULT (__stdcall *WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef INT_PTR (__stdcall *DLGPROC)(HWND, UINT, WPARAM, LPARAM);
typedef BOOL (__stdcall *WNDENUMPROC)(HWND, LPARAM);
typedef BOOL (__stdcall *LOCALE_ENUMPROCA)(LPSTR);
typedef DWORD (__stdcall *LPTHREAD_START_ROUTINE)(LPVOID);
typedef void (__stdcall *TIMERPROC)(HWND, UINT, UINT_PTR, DWORD);
typedef void (__stdcall *LPTIMECALLBACK)(UINT, UINT, DWORD_PTR, DWORD_PTR, DWORD_PTR);
typedef BOOL (__stdcall *PHANDLER_ROUTINE)(DWORD);
struct EXCEPTION_POINTERS;
typedef LONG (__stdcall *LPTOP_LEVEL_EXCEPTION_FILTER)(EXCEPTION_POINTERS *);
struct IUnknown; typedef IUnknown *LPUNKNOWN;
struct IStream; typedef IStream *LPSTREAM;
struct IPersistStream; typedef IPersistStream *LPPERSISTSTREAM;
struct IStorage;
'''.strip()
SDK_OPAQUE = {
    'CANDIDATELIST': 'LPCANDIDATELIST', 'DLGTEMPLATE': 'LPCDLGTEMPLATEA',
    'COMMTIMEOUTS': 'LPCOMMTIMEOUTS', 'COMSTAT': 'LPCOMSTAT', 'CPINFO': 'LPCPINFO',
    'DCB': 'LPDCB', 'OSVERSIONINFOA': 'LPOSVERSIONINFOA',
    'PROCESS_INFORMATION': 'LPPROCESS_INFORMATION', 'STARTUPINFOA': 'LPSTARTUPINFOA',
    'TEXTMETRICA': 'LPTEXTMETRICA', 'TIME_ZONE_INFORMATION': 'LPTIME_ZONE_INFORMATION',
    'BY_HANDLE_FILE_INFORMATION': 'LPBY_HANDLE_FILE_INFORMATION',
    'WIN32_FIND_DATAA': 'LPWIN32_FIND_DATAA', 'EXCEPTION_RECORD': 'PEXCEPTION_RECORD',
    'INPUT_RECORD': 'PINPUT_RECORD',
}
SDK_PREAMBLE += '\n' + '\n'.join('struct %s; typedef %s *%s;' % (kind, kind, alias)
                                for kind, alias in sorted(SDK_OPAQUE.items()))
SDK_PREAMBLE += '\nstruct BITMAPINFO; struct LOGFONTA; struct MSGBOXPARAMSA; struct WNDCLASSA;'


def code_view(text):
    """Mask comments and literals, preserving positions and line breaks."""
    pattern = r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\''
    return re.sub(pattern, lambda m: ''.join('\n' if c == '\n' else ' ' for c in m[0]), text)


def scalar_declarations(view):
    """Find simple statement/parameter declarations, including nested scopes.

    This conservative index is for refusing shadowing, not inferring layouts.
    Comma declarations are flagged separately because the later names have no
    repeated type spelling. Ghidra's ordinary local list uses one name per line.
    """
    pattern = re.compile(r'(?:^|(?<=[;{}(\n]))[\t ]*'
                         r'([A-Za-z_]\w*(?:[\t ]+[A-Za-z_]\w*)*?'
                         r'(?:[\t ]*[*&]+[\t ]*|[\t ]+))([A-Za-z_]\w*)'
                         r'([\t ]*\[[^\]\n]*\])?(?=[\t ]*[;=,)])', re.M)
    rows, comma = [], False
    for match in pattern.finditer(view):
        kind, name, array = match.groups()
        if kind.strip().split()[0] in ('return', 'goto', 'delete', 'throw', 'break', 'continue'):
            continue
        rows.append((kind.strip(), name, array))
        comma |= ',' in view[match.end():].split(';', 1)[0]
    return rows, comma


def nan_artifacts(body, params=(), named_functions=()):
    """Spell Ghidra's NaN predicate on a stable floating scalar as self-inequality.

    No helper call, argument store or new precision boundary is introduced.
    Expressions with effects, volatile/unknown storage and named real functions
    remain unresolved. This recovers a value predicate, not exception behavior;
    a source candidate still needs the complete original instruction audit.
    """
    view = code_view(body)
    if ('NAN' in named_functions or re.search(r'#\s*(?:define|undef)\s+NAN\b', view) or
            re.search(r'(?:^|[;{}\n])\s*(?!return\b|throw\b|delete\b|goto\b)'
                      r'(?:[A-Za-z_]\w*\s+)+\**\s*NAN\s*\(', view)):
        return body
    slots = {}
    for kind, name in map(param_parts, params):
        if name:
            slots.setdefault(name, []).append((kind.strip(), None))
    declarations, comma = scalar_declarations(view)
    if comma or re.search(r'\(\s*\*\s*NAN\s*\)', view+' '+code_view(' '.join(params))):
        return body
    for kind, name, array in declarations:
        slots.setdefault(name, []).append((kind.strip(), array))
    if 'NAN' in slots:
        return body
    kinds = {'float', 'double', 'float10', 'const float', 'const double', 'const float10'}
    edits = []
    for match in re.finditer(r'\bNAN\s*\(\s*([A-Za-z_]\w*)\s*\)', view):
        name = match[1]
        declarations = slots.get(name, [])
        if len(declarations) != 1:
            continue
        kind, array = declarations[0]
        if kind not in kinds or array:
            continue
        edits.append((match.start(), match.end(), '(%s != %s)' % (name, name)))
    for start, end, replacement in reversed(edits):
        body = body[:start] + replacement + body[end:]
    return body


def sdk_named_types(body, params=(), result='void'):
    """Supply used Win32 interface names, without guessing opaque game layouts.

    The file-search record is the same 0x140-byte ANSI Windows interface as
    shared/win32_find.hpp. POINT's tag and ULONG have their documented Win32
    definitions. Leave unrelated seeds, authored types and shadowing unchanged.
    No SDK headers, global macro guards or emitted helper code are introduced.
    """
    view = code_view(body)
    signature = code_view(' '.join([result] + list(params)))
    declarations = scalar_declarations(view)[0]
    identifiers = {name for _, name, _ in declarations}
    identifiers.update(name for _, name in map(param_parts, params))

    def needed(name):
        if not re.search(r'\b' + name + r'\b', view + ' ' + signature):
            return False
        if name in identifiers or re.search(r'#\s*(?:define|undef)\s+' + name + r'\b', view):
            return False
        if (re.search(r'\btypedef\b[^;{}]*\b' + name + r'\s*;', view) or
                re.search(r'\b(?:struct|class|union)\s+' + name + r'\s*[{:]', view) or
                re.search(r'\b' + name + r'\s*\(', view)):
            return False
        return True

    preamble = SDK_PREAMBLE
    if needed('tagPOINT'):
        preamble = preamble.replace('struct POINT { LONG x, y; };',
                                    'struct tagPOINT { LONG x, y; };\ntypedef tagPOINT POINT;')
    if needed('ULONG'):
        preamble += '\ntypedef unsigned long ULONG;'
    names = ('_WIN32_FIND_DATAA', 'WIN32_FIND_DATAA', 'PWIN32_FIND_DATAA', 'LPWIN32_FIND_DATAA')
    # One real interface type serves the tag, typedef and pointer spellings.
    # Do not add a conflicting definition when the seed owns any of these names.
    blocked = any(name in identifiers or re.search(r'\btypedef\b[^;{}]*\b' + name + r'\s*;', view) or
                  re.search(r'\b(?:struct|class|union)\s+' + name + r'\s*[{:]', view) or
                  re.search(r'#\s*(?:define|undef)\s+' + name + r'\b', view) for name in names)
    if not blocked and any(needed(name) for name in names):
        record = ('struct _WIN32_FIND_DATAA {\n'
                  '    DWORD dwFileAttributes;\n'
                  '    FILETIME ftCreationTime, ftLastAccessTime, ftLastWriteTime;\n'
                  '    DWORD nFileSizeHigh, nFileSizeLow, dwReserved0, dwReserved1;\n'
                  '    CHAR cFileName[260], cAlternateFileName[14];\n'
                  '};\n'
                  'typedef _WIN32_FIND_DATAA WIN32_FIND_DATAA;\n'
                  'typedef WIN32_FIND_DATAA *PWIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;')
        preamble = preamble.replace('struct WIN32_FIND_DATAA; typedef WIN32_FIND_DATAA *LPWIN32_FIND_DATAA;', record)
    return com_interface_types(preamble, view, signature, identifiers)


def com_interface_types(preamble, view, signature, identifiers):
    """Supply documented C COM vtables for explicitly named SDK interfaces.

    These are i386 SDK declarations, not recovered game classes. Full vtable
    lengths keep pointer arithmetic/sizeof honest; unused record pointees stay
    incomplete. C REFIID/REFCLSID are pointers. No SDK headers or helper bodies.
    """
    names = {'IUnknown', 'IStream', 'IPersistStream', 'IStorage',
             'IUnknownVtbl', 'IStreamVtbl', 'IPersistStreamVtbl', 'IStorageVtbl',
             'LPUNKNOWN', 'LPSTREAM', 'LPPERSISTSTREAM', 'LPSTORAGE'}
    if not any(re.search(r'\b' + name + r'\b', view + ' ' + signature) for name in names):
        return preamble
    dependencies = names | {'ULONG', 'LARGE_INTEGER', 'ULARGE_INTEGER',
                            'STATSTG', 'IEnumSTATSTG'}
    # An authored definition, macro, callable or shadowing identifier owns its
    # spelling. Refuse the entire coupled interface group on a conflict.
    for name in dependencies:
        if (name in identifiers or
                re.search(r'\btypedef\b[^;{}]*\b' + name + r'\s*;', view) or
                re.search(r'\b(?:struct|class|union)\s+' + name + r'\s*[{:]', view) or
                re.search(r'#\s*(?:define|undef)\s+' + name + r'\b', view) or
                re.search(r'\b' + name + r'\s*\(', view)):
            return preamble
    if 'typedef unsigned long ULONG;' not in preamble:
        preamble += '\ntypedef unsigned long ULONG;'
    return preamble + r'''
// Documented i386 COM C ABI; nominal Ghidra interface identity still needs proof.
union ULARGE_INTEGER { struct { DWORD LowPart, HighPart; }; unsigned __int64 QuadPart; };
struct tagSTATSTG; typedef tagSTATSTG STATSTG;
struct IEnumSTATSTG;
struct IUnknownVtbl {
    HRESULT (__stdcall *QueryInterface)(IUnknown *, IID const *, void **);
    ULONG (__stdcall *AddRef)(IUnknown *);
    ULONG (__stdcall *Release)(IUnknown *);
};
struct IUnknown { IUnknownVtbl *lpVtbl; };
struct IStreamVtbl {
    HRESULT (__stdcall *QueryInterface)(IStream *, IID const *, void **);
    ULONG (__stdcall *AddRef)(IStream *);
    ULONG (__stdcall *Release)(IStream *);
    HRESULT (__stdcall *Read)(IStream *, void *, ULONG, ULONG *);
    HRESULT (__stdcall *Write)(IStream *, void const *, ULONG, ULONG *);
    HRESULT (__stdcall *Seek)(IStream *, LARGE_INTEGER, DWORD, ULARGE_INTEGER *);
    HRESULT (__stdcall *SetSize)(IStream *, ULARGE_INTEGER);
    HRESULT (__stdcall *CopyTo)(IStream *, IStream *, ULARGE_INTEGER, ULARGE_INTEGER *, ULARGE_INTEGER *);
    HRESULT (__stdcall *Commit)(IStream *, DWORD);
    HRESULT (__stdcall *Revert)(IStream *);
    HRESULT (__stdcall *LockRegion)(IStream *, ULARGE_INTEGER, ULARGE_INTEGER, DWORD);
    HRESULT (__stdcall *UnlockRegion)(IStream *, ULARGE_INTEGER, ULARGE_INTEGER, DWORD);
    HRESULT (__stdcall *Stat)(IStream *, STATSTG *, DWORD);
    HRESULT (__stdcall *Clone)(IStream *, IStream **);
};
struct IStream { IStreamVtbl *lpVtbl; };
struct IPersistStreamVtbl {
    HRESULT (__stdcall *QueryInterface)(IPersistStream *, IID const *, void **);
    ULONG (__stdcall *AddRef)(IPersistStream *);
    ULONG (__stdcall *Release)(IPersistStream *);
    HRESULT (__stdcall *GetClassID)(IPersistStream *, CLSID *);
    HRESULT (__stdcall *IsDirty)(IPersistStream *);
    HRESULT (__stdcall *Load)(IPersistStream *, IStream *);
    HRESULT (__stdcall *Save)(IPersistStream *, IStream *, BOOL);
    HRESULT (__stdcall *GetSizeMax)(IPersistStream *, ULARGE_INTEGER *);
};
struct IPersistStream { IPersistStreamVtbl *lpVtbl; };
struct IStorageVtbl {
    HRESULT (__stdcall *QueryInterface)(IStorage *, IID const *, void **);
    ULONG (__stdcall *AddRef)(IStorage *);
    ULONG (__stdcall *Release)(IStorage *);
    HRESULT (__stdcall *CreateStream)(IStorage *, wchar16 const *, DWORD, DWORD, DWORD, IStream **);
    HRESULT (__stdcall *OpenStream)(IStorage *, wchar16 const *, void *, DWORD, DWORD, IStream **);
    HRESULT (__stdcall *CreateStorage)(IStorage *, wchar16 const *, DWORD, DWORD, DWORD, IStorage **);
    HRESULT (__stdcall *OpenStorage)(IStorage *, wchar16 const *, IStorage *, DWORD, SNB, DWORD, IStorage **);
    HRESULT (__stdcall *CopyTo)(IStorage *, DWORD, IID const *, SNB, IStorage *);
    HRESULT (__stdcall *MoveElementTo)(IStorage *, wchar16 const *, IStorage *, wchar16 const *, DWORD);
    HRESULT (__stdcall *Commit)(IStorage *, DWORD);
    HRESULT (__stdcall *Revert)(IStorage *);
    HRESULT (__stdcall *EnumElements)(IStorage *, DWORD, void *, DWORD, IEnumSTATSTG **);
    HRESULT (__stdcall *DestroyElement)(IStorage *, wchar16 const *);
    HRESULT (__stdcall *RenameElement)(IStorage *, wchar16 const *, wchar16 const *);
    HRESULT (__stdcall *SetElementTimes)(IStorage *, wchar16 const *, FILETIME const *, FILETIME const *, FILETIME const *);
    HRESULT (__stdcall *SetClass)(IStorage *, CLSID const *);
    HRESULT (__stdcall *SetStateBits)(IStorage *, DWORD, DWORD);
    HRESULT (__stdcall *Stat)(IStorage *, STATSTG *, DWORD);
};
struct IStorage { IStorageVtbl *lpVtbl; };
typedef IStorage *LPSTORAGE;
'''


def sdk_preamble(body, params=(), result='void'):
    """Only used, known Windows interface types enter a seed's namespace.

    Keep the alias inside each seed's namespace. A shared macro guard would
    suppress the typedef in subsequent namespaces of a composite population.
    Explicit typedefs and identifier shadowing stay with their authored text.
    """
    preamble = sdk_named_types(body, params, result)
    view = code_view(body)
    signature = code_view(' '.join([result] + list(params)))
    if not re.search(r'\bwchar_t\b', view + ' ' + signature):
        return preamble
    if re.search(r'\btypedef\b[^;{}]*\bwchar_t\s*;', view):
        return preamble
    if any(name == 'wchar_t' for _, name in map(param_parts, params)):
        return preamble
    if any(name == 'wchar_t' for _, name, _ in scalar_declarations(view)[0]):
        return preamble
    return preamble + '\ntypedef wchar16 wchar_t;'


def local_labels(body):
    """Keep real goto labels local, drop unused label declarations, refuse gaps."""
    view = code_view(body)
    definitions = set(re.findall(r'^\s*(LAB_[0-9a-f]{8})\s*:', view, re.M))
    targets = set(re.findall(r'\bgoto\s+(LAB_[0-9a-f]{8})\s*;', view))
    missing = targets - definitions
    if missing:
        raise ValueError('Missing Ghidra goto label(s): ' + ', '.join(sorted(missing)))
    # The label and its following statement have independent indentation.
    body = re.sub(r'^(\s*)(LAB_[0-9a-f]{8})\s*:',
                  lambda m: m[1] + (m[2] + ':;' if m[2] in targets else ''), body, flags=re.M)
    return body, definitions


def concat_artifacts(body):
    """Expand width-exact CONCAT operations, evaluating each operand once."""
    pattern = re.compile(r'\bCONCAT([1-8])([1-8])\s*\(')
    while True:
        sites = list(pattern.finditer(code_view(body)))
        if not sites:
            return body
        match = sites[-1]  # innermost/rightmost first
        high, low = int(match[1]), int(match[2])
        if high + low > 8:
            raise ValueError('CONCAT wider than 64 bits')
        end = matching_paren(body, match.end() - 1)
        args = split_args(body[match.end():end])
        if len(args) != 2:
            raise ValueError('CONCAT requires two operands')
        result = 'uint' if high + low <= 4 else 'ulonglong'
        def operand(text, width):
            kind = {1: 'uchar', 2: 'ushort', 4: 'uint', 8: 'ulonglong'}.get(width)
            if kind:
                return '(%s)(%s)' % (kind, text)
            return '((%s)(%s) & 0x%x%s)' % (result, text, (1 << (8 * width)) - 1,
                                             'ui64' if width > 4 else '')
        expression = '(((%s)(%s) << %d) | (%s)(%s))' % (
            result, operand(args[0], high), low * 8, result, operand(args[1], low))
        body = body[:match.start()] + expression + body[end + 1:]


def extend_artifacts(body):
    """Width-exact zero/sign extension; no signed reinterpretation of uint64."""
    pattern = re.compile(r'\b([ZS])EXT([1248])([1248])\s*\(')
    while True:
        sites = list(pattern.finditer(code_view(body)))
        if not sites:
            return body
        match = sites[-1]
        first, last = int(match[2]), int(match[3])
        if first > last:
            raise ValueError('Invalid Ghidra extension width')
        end = matching_paren(body, match.end() - 1)
        args = split_args(body[match.end():end])
        if len(args) != 1:
            raise ValueError('Ghidra extension requires one operand')
        kinds = {1: 'char', 2: 'short', 4: 'int', 8: 'longlong'}
        source = kinds[first]
        destination = kinds[last]
        if match[1] == 'Z':
            source = {1: 'uchar', 2: 'ushort', 4: 'uint', 8: 'ulonglong'}[first]
            destination = {1: 'uchar', 2: 'ushort', 4: 'uint', 8: 'ulonglong'}[last]
        elif first == 1:
            source = 'signed char'
        body = body[:match.start()] + '((%s)(%s)(%s))' % (destination, source, args[0]) + body[end + 1:]


def byte_update_artifacts(body, params=()):
    """Recover standalone low-byte stores, without reading an invented uint24.

    Ghidra spells a byte store into a reused four-byte slot as
    x = CONCAT31(x._1_3_, value). The other three bytes are preserved, not
    loaded by a wider unaligned access. Only declared scalar slots and constant
    array elements qualify. Used assignment results, effectful values, unknown
    storage, volatile objects and masks changing the upper bytes stay untouched.
    """
    view = code_view(body)
    slots = {name: (kind, None) for kind, name in map(param_parts, params) if name}
    for kind, name, array in LOCAL.findall(view):
        if kind.strip().split()[0] in ('return', 'goto', 'delete', 'throw', 'break', 'continue'):
            continue
        slots[name] = (kind.strip(), array.strip() if array else None)
    pattern = re.compile(r'^[\t ]*(?P<slot>[A-Za-z_]\w*(?:[\t ]*\[[\t ]*\d+[\t ]*\])?)'
                         r'[\t ]*=(?!=)\s*', re.M)
    edits = []
    for match in pattern.finditer(view):
        before = view[:match.start()].rstrip()
        if before and before[-1] not in '{;}':
            continue  # A line break does not make a used assignment standalone.
        slot = re.sub(r'\s+', '', match['slot'])
        name = slot.split('[', 1)[0]
        kind, array = slots.get(name, ('', None))
        if re.search(r'\b(?:const|volatile)\b', kind):
            continue
        kind = clean_type(kind)
        if kind not in INTEGRAL32 and kind not in POINTER_ALIASES and '*' not in kind:
            continue
        if '[' in slot:
            count = re.fullmatch(r'\[\s*(\d+)\s*\]', array or '')
            if not count or int(slot[slot.index('[')+1:-1]) >= int(count[1]):
                continue
        elif array:
            continue
        cursor = match.end()
        cast = re.match(r'\(([\w\t ]+(?:\s*\*)*)\)\s*', view[cursor:])
        if cast:
            if clean_type(cast[1]) != kind:
                continue
            cursor += cast.end()
        concat = re.match(r'CONCAT31\s*\(', view[cursor:])
        if not concat:
            continue
        opening = cursor + concat.end() - 1
        closing = matching_paren(view, opening)
        args = split_args(body[opening+1:closing])
        if len(args) != 2 or re.sub(r'\s+', '', args[0]) != slot + '._1_3_':
            continue
        value = args[1]
        value_view = code_view(value)
        # A call or write can change the slot while the high bytes are being
        # assembled. Do not replace that expression with a different ordering.
        if re.search(r'\+\+|--|(?<![=!<>])=(?!=)|,|\b\w+\s*\(', value_view):
            continue
        calls = False
        for parenthesis in re.finditer(r'\)\s*\(', value_view):
            end = parenthesis.start()
            depth, start = 1, end - 1
            while start >= 0 and depth:
                depth += (value_view[start] == ')') - (value_view[start] == '(')
                start -= 1
            inside = clean_type(value_view[start+2:end])
            if inside not in INTEGRAL32 | {'char', 'uchar', 'byte', 'undefined1', 'ushort', 'short', 'undefined2'}:
                calls = True
                break
        if calls:
            continue
        tail = re.match(r'\s*(?:&\s*(0x[0-9a-fA-F]+|\d+)[uU]?)?\s*;', view[closing+1:])
        if not tail:
            continue
        if tail[1]:
            mask = int(tail[1], 16 if tail[1].lower().startswith('0x') else 10)
            if mask > 0xffffffff or mask & 0xffffff00 != 0xffffff00:
                continue
            value = '(uchar)(%s) & 0x%02x' % (value, mask & 0xff)
        replacement = '*(uchar *)&(%s) = (uchar)(%s);' % (slot, value)
        edits.append((match.start('slot'), closing + 1 + tail.end(), replacement))
    for start, end, replacement in reversed(edits):
        body = body[:start] + replacement + body[end:]
    return body


def stack_artifacts(body, params, convention):
    """Name stack storage honestly, reusing a known local/argument when possible.

    Ghidra stack offsets are hypotheses. An otherwise absent slot gets a
    width-only unknown local and a review note, never an absolute pointer.
    """
    slots = {}
    for kind, name, array in LOCAL.findall(body):
        offset = re.fullmatch(r'(?:\w*Stack|local)_([0-9a-f]+)', name)
        if offset:
            slots.setdefault(-int(offset[1], 16), []).append(name)
    offset = 4
    skip = {'__thiscall': 1, '__fastcall': 2}.get(convention, 0)
    for param in params[skip:]:
        kind, name = param_parts(param)
        if name:
            slots.setdefault(offset, []).append(name)
        offset += stack_bytes(param)
    declarations = []
    for token in sorted(set(re.findall(r'\bstack0x[0-9a-f]{8}\b', code_view(body)))):
        raw = int(token[7:], 16)
        signed = raw - (1 << 32) if raw & (1 << 31) else raw
        known = slots.get(signed, [])
        if len(known) == 1:
            replacement = known[0]
        else:
            replacement = 'unknown_stack_%08x' % raw
            declarations.append('    undefined4 %s; // TODO: unknown stack storage width/aliasing (%s).' %
                                (replacement, token))
        body = re.sub(r'\b' + token + r'\b', replacement, body)
    if declarations:
        body = body.replace('{', '{\n' + '\n'.join(declarations), 1)
    return body


def pointer_global_type(body, symbol):
    """Reuse an unambiguous local pointer type; prefixes alone do not fix layout."""
    types = variable_types(body)
    assigned = {types[m[1]] for m in re.finditer(r'\b(\w+)\s*=\s*' + re.escape(symbol) + r'\s*;', body)
                if m[1] in types and '*' in types[m[1]]}
    if len(assigned) == 1:
        return assigned.pop()
    return 'code *' if re.match(r'_?PTR_(?:FUN|LAB)_', symbol) else 'void *'


def variable_types(body, params=()):
    types = {name: kind for kind, name in map(param_parts, params) if name}
    types.update({name: kind.strip() + (' *' if array else '')
                  for kind, name, array in LOCAL.findall(code_view(body))
                  if kind.strip().split()[0] not in ('return', 'goto', 'delete', 'throw', 'break', 'continue')})
    return types


def scalar_address_views(body, params=()):
    """Type memory views of merged 32-bit locals, retaining their storage type.

    Ghidra sometimes reuses one undefined4 slot for packed values and addresses,
    then writes a bare *slot or slot[index]. A unique explicit pointer-assignment
    type supplies a four-byte primitive view, not a new local type or layout.
    Numeric uses, partial writes, address taking and evaluation order stay as
    written. Conflicting/unknown pointees and duplicate declarations refuse it.
    This repairs scratch C++ syntax; the original loads/ABI still need proof.
    """
    view, declarations = code_view(body), {}
    for match in LOCAL.finditer(view):
        declarations.setdefault(match[2], []).append(match)
    parameters = {param_parts(p)[1] for p in params}
    pointee32 = {'int', 'uint', 'undefined4', 'long', 'ulong', 'unsigned int',
                 'unsigned long', 'signed int', 'signed long'}
    edits, notes = [], []
    for name, decls in declarations.items():
        if len(decls) != 1 or name in parameters:
            continue
        decl = decls[0]
        if decl[3] or clean_type(decl[1]) not in INTEGRAL32:
            continue
        token = r'\b' + re.escape(name) + r'\b'
        hints = set()
        for match in re.finditer(token + r'\s*=\s*\(\s*([^()]+?)\s*\*\s*\)', view):
            before = view[:match.start()].rstrip()
            if before.endswith(('*', '.', '->', '::', ']')):
                continue
            # Qualifiers are meaningful for a memory access. Do not erase
            # const/volatile as clean_type does for ABI-width comparisons.
            hints.add(' '.join(match[1].split()))
        if len(hints) != 1 or not hints <= pointee32:
            continue
        pointee, count = next(iter(hints)), 0
        for match in re.finditer(token, view):
            before, after = view[:match.start()].rstrip(), view[match.end():].lstrip()
            if before.endswith(('.', '->', '::')) or after.startswith(('(', '.', '->', '::')):
                continue
            if before.endswith('*') and unary_operator(view, len(before)-1):
                # Do not infer the additional pointer level in **slot.
                prefix = before[:-1].rstrip()
                if prefix.endswith('*') and unary_operator(view, len(prefix)-1):
                    continue
                edits.append((match.start(), match.end(), '(%s *)%s' % (pointee, name)))
            elif after.startswith('['):
                edits.append((match.start(), match.end(), '((%s *)%s)' % (pointee, name)))
            else:
                continue
            count += 1
        if count:
            notes.append('// Scratch %s memory view: %s * from explicit assignments; '
                         'merged %s storage retained, original-load/type proof still required.' %
                         (name, pointee, clean_type(decl[1])))
    for first, last, replacement in sorted(edits, reverse=True):
        body = body[:first] + replacement + body[last:]
    return body, notes


def unary_operator(view, position):
    before = view[:position].rstrip()
    # A cast can precede a unary load: (code **)*DAT reads DAT's pointee.
    # Treating that star as multiplication would cast DAT itself to uint,
    # producing illegal indirection and losing the intended memory read.
    # Peel each cast in (int)(uint)*DAT. A closing parenthesis alone cannot
    # distinguish this from f(uint)*DAT; its complete left context matters.
    while True:
        if not before or before[-1] in '([=!,;:{}?&|^~+-*/%<>' or re.search(r'\breturn$', before):
            return True
        if not before.endswith(')'):
            return False
        depth, start = 1, len(before)-2
        while start >= 0:
            if before[start] == ')':
                depth += 1
            elif before[start] == '(':
                depth -= 1
                if depth == 0:
                    break
            start -= 1
        if start < 0:
            return False
        kind = before[start+1:-1].strip()
        pointer_cast = re.fullmatch(r'[A-Za-z_]\w*(?:::\w+)*(?:\s+[A-Za-z_]\w*)*\s*\*+\s*', kind)
        scalar_cast = clean_type(kind) in INTEGRAL32 | {
            'bool', 'char', 'signed char', 'unsigned char', 'short', 'ushort', 'unsigned short',
            'longlong', 'ulonglong', 'undefined1', 'undefined2', 'undefined3', 'undefined8',
            'float', 'double', 'float10', 'byte', 'uchar', 'code'}
        if not pointer_cast and not scalar_cast:
            return False
        # f(uint), sizeof(uint), T(uint) and a[index](uint) stop at their
        # expression/callee prefix rather than being mistaken for casts.
        before = before[:start].rstrip()


def cast_void_global_offsets(body, globals_):
    """Keep literal byte offsets on otherwise opaque global pointers explicit.

    Ghidra uses byte offsets on a void pointer. Cast the stored address bits,
    leaving the outer load/store width untouched. Indexing, pointer differences,
    variable offsets and unknown layouts are not inferred by this narrow rule.
    """
    view, sites = code_view(body), []
    for symbol, kind in globals_.items():
        if not re.fullmatch(r'void\s*\*', clean_type(kind)):
            continue
        pattern = (r'\b' + re.escape(symbol) +
                   r'\b(?=\s*[+-]\s*(?:0x[0-9a-fA-F]+|\d+)\b(?![.\w]))')
        for match in re.finditer(pattern, view):
            before = view[:match.start()].rstrip()
            if before.endswith(('&', '*')) and unary_operator(view, len(before) - 1):
                continue
            if before.endswith(('(uint)', '(int)', '(unsigned int)')):
                continue
            sites.append((match.start(), match.end()))
    for first, last in sorted(sites, reverse=True):
        body = body[:first] + '(uint)' + body[first:last] + body[last:]
    return body


_SHARED_POINTERS = {}


def shared_pointer_types(directory=None):
    """Read unambiguous, address-annotated pointer declarations from shared layouts.

    Only existing top-level class/struct names and primitive pointees are used.
    No struct layout, inheritance, or field offset is synthesized by this index.
    """
    directory = Path(directory or REPOSITORY / 'src/shared').resolve()
    if directory in _SHARED_POINTERS:
        return _SHARED_POINTERS[directory]
    texts = {p: p.read_text(encoding='utf-8') for p in sorted(directory.glob('*.hpp'))}
    tags = {}
    for text in texts.values():
        tags.update({name: tag for tag, name in re.findall(r'^(class|struct)\s+(\w+)\b', code_view(text), re.M)})
    choices = {}
    pattern = re.compile(r'^\s*extern\s+([A-Za-z_]\w*\s*\*)\s*(\w+)\s*;[^\n]*//\s*0x([0-9a-fA-F]{8})\b', re.M)
    for path, text in texts.items():
        for match in pattern.finditer(text):
            kind = match[1].strip()
            pointee = kind.rstrip('*').strip()
            if pointee not in tags and pointee not in ('int', 'uint', 'char', 'short', 'ushort', 'byte', 'void'):
                continue
            kind = pointee + ' *'
            choices.setdefault(int(match[3], 16), []).append(dict(
                kind=kind, header='shared/' + path.name,
                forward=('%s %s;' % (tags[pointee], pointee)) if pointee in tags else None))
    result = {address: rows[0] for address, rows in choices.items()
              if len({r['kind'] for r in rows}) == 1}
    _SHARED_POINTERS[directory] = result
    return result


def recover_global_pointers(body, params=(), shared=None):
    """Infer stored pointer globals from their uses, without inventing layouts.

    An address taken with &DAT is storage, not evidence of a stored pointer.
    Direct dereferences/subscripts and consistent pointer assignments supply
    evidence. Conflicting pointee types keep a width-only uint pointee. Ghidra
    byte-offset arithmetic is kept explicit at the pointer/integer boundary;
    subscripts retain their inferred element stride. These remain hypotheses.
    """
    view, types = code_view(body), variable_types(body, params)
    shared = shared or {}
    inferred = {}
    for symbol in sorted(set(DATA.findall(view))):
        if not re.fullmatch(r'_?DAT_[0-9a-f]{8}', symbol):
            continue
        token = r'\b' + re.escape(symbol) + r'\b'
        hints = set()
        for match in re.finditer(r'^\s*(\w+)\s*=\s*' + token + r'\s*;', view, re.M):
            kind = types.get(match[1], '')
            if '*' in kind:
                hints.add(kind)
        for match in re.finditer(token + r'\s*(?:==|!=|=)\s*\(([^()]+\*)\)', view):
            hints.add(match[1].strip())
        callable_ = re.search(r'\(\s*\*\s*' + token + r'\s*\)\s*\(', view)
        dereferenced = False
        for match in re.finditer(r'\*\s*' + token, view):
            if unary_operator(view, match.start()):
                dereferenced = True
        indexed = re.search(token + r'\s*\[', view)
        known = shared.get(int(symbol[-8:], 16))
        if known and not callable_ and not dereferenced and not indexed:
            # Incomplete shared owner types suffice at raw address boundaries.
            # Direct pointee accesses remain width-only until fields are recovered.
            inferred[symbol] = known['kind']
        elif callable_:
            inferred[symbol] = 'code *'
        elif hints or dereferenced or indexed:
            inferred[symbol] = hints.pop() if len(hints) == 1 else 'undefined4 *'
    for symbol in inferred:
        # A cast is at the raw byte-offset boundary, rather than at every read.
        view = code_view(body)
        sites = list(re.finditer(r'\b' + symbol + r'\b', view))
        for match in reversed(sites):
            before = view[:match.start()].rstrip()
            after = view[match.end():].lstrip()
            if before.endswith(('&', '*')) and unary_operator(view, len(before) - 1):
                continue
            if not re.match(r'(?:[+\-*/%]|<<|>>|[&|^])', after) and not before.endswith(('+', '-', '*', '/', '%', '^', '|', '&', '<<', '>>')):
                continue
            body = body[:match.start()] + '(uint)' + body[match.start():]
    return body, inferred


def expression_end(view, start):
    """End of an assignment RHS, including multiline and for-loop clauses."""
    depth = 0
    for index in range(start, len(view)):
        char = view[index]
        if char in '([':
            depth += 1
        elif char in ')]':
            if depth == 0:
                return index
            depth -= 1
        elif depth == 0 and char in ';,':
            return index
    return len(view)


def lvalue_type(left, types):
    """Recover only explicit cast-dereferences and declared scalar/array slots."""
    left = left.rstrip()
    # Explicit dereference casts include nested addresses and partial fields.
    line = left[left.rfind('\n') + 1:].strip()
    while line.startswith('(') and line.endswith(')'):
        try:
            if matching_paren(line, 0) != len(line) - 1:
                break
        except ValueError:
            break
        line = line[1:-1].strip()
    cast = re.match(r'^\*\s*\(\s*([\w\s]+(?:\s*\*)+)\s*\)', line)
    if cast:
        return cast[1].rsplit('*', 1)[0].strip()
    # Most expressions end in a declared name (also assignments within for/if).
    match = re.search(r'\b(\w+)$', line)
    if match:
        name = match[1]
        if name in types:
            kind = types[name]
            prefix = line[:match.start()].rstrip()
            return kind.rsplit('*', 1)[0].strip() if prefix.endswith('*') and '*' in kind else kind
    array = re.search(r'\b(\w+)\s*\[[^\[\]]*\]$', line)
    if array and '*' in types.get(array[1], ''):
        return types[array[1]].rsplit('*', 1)[0].strip()
    return None


def cast_storage_boundaries(body, params=(), globals_=None):
    """Spell C's scalar assignment conversions at stores, not every operand.

    Ghidra output includes multiline/embedded stores that the old line regex
    missed. The declared destination fixes the conversion width. Never cast
    aggregate assignments or transform compound assignments as plain stores.
    """
    types = variable_types(body, params)
    types.update(globals_ or {})
    view = code_view(body)
    edits = []
    for match in re.finditer(r'(?<![=!<>+\-*/%&|^])=(?!=)', view):
        kind = lvalue_type(view[:match.start()], types)
        if not kind or not re.fullmatch(r'[\w\s]+(?:\s*\*)*', kind):
            continue
        end = expression_end(view, match.end())
        rhs = body[match.end():end]
        value = rhs.strip()
        if not value or value.startswith('(' + kind + ')'):
            continue
        # Shared aggregate types are not scalar conversion targets.
        if '*' not in kind and not re.fullmatch(r'(?:unsigned |signed )?(?:char|short|int|long|long long|__int64)|'
                                               r'undefined[1-8]?|u?int[1-8]?|byte|u?char|u?short|u?long|'
                                               r'float(?:10)?|double|u?longlong|[dq]word|size_t|BOOL|DWORD|UINT|'
                                               r'LONG|SHORT|WORD|BYTE|LPARAM|WPARAM|LRESULT|HWND|HANDLE|HINSTANCE', kind):
            continue
        # Preserve nested assignment evaluation by inserting paired tokens.
        first = match.end() + len(rhs) - len(rhs.lstrip())
        last = end - len(rhs) + len(rhs.rstrip())
        edits += [(first, '(%s)(' % kind), (last, ')')]
    for position, text in sorted(edits, key=lambda item: item[0], reverse=True):
        body = body[:position] + text + body[position:]
    return body


INTEGRAL32 = {'int', 'uint', 'undefined4', 'long', 'ulong', 'unsigned', 'signed',
              'unsigned int', 'signed int', 'unsigned long', 'signed long',
              'DWORD', 'UINT', 'LONG', 'ULONG', 'BOOL', 'LPARAM', 'WPARAM', 'LRESULT'}
POINTER_ALIASES = {'HWND', 'HANDLE', 'HINSTANCE', 'HMODULE', 'LPVOID', 'HDC', 'HKEY',
                   'LPSTR', 'LPCSTR', 'LPDWORD', 'LPCRITICAL_SECTION', 'LPSECURITY_ATTRIBUTES',
                   'LPOVERLAPPED', 'LPWSTR', 'LPCWSTR', 'PVOID', 'LPCVOID', 'FARPROC'}


def clean_type(kind):
    return ' '.join(re.sub(r'\b(?:extern|static|const|volatile)\b', '', kind).split())


def equality_operand(view, boundary, direction):
    """Find one full equality operand without crossing a lower-precedence operator."""
    index = boundary if direction == 1 else boundary - 1
    stack = []
    while 0 <= index < len(view):
        char = view[index]
        opening, closing = ('([', ')]') if direction == 1 else (')]', '([')
        if char in opening:
            stack.append(char)
        elif char in closing:
            if not stack:
                break
            stack.pop()
        elif not stack:
            if char in ';,{}?:=' or char == '!' and view[index:index+2] == '!=':
                break
            if char in '&|^':
                double = view[index:index+2] in ('&&', '||') or view[index-1:index+1] in ('&&', '||')
                if double or char != '&' or not unary_operator(view, index):
                    break
        index += direction
    first, last = (boundary, index) if direction == 1 else (index + 1, boundary)
    while first < last and view[first].isspace(): first += 1
    while last > first and view[last-1].isspace(): last -= 1
    if direction == -1:
        match = re.match(r'return\b\s*', view[first:last])
        if match: first += match.end()
    return first, last


def one_atom(text):
    if re.fullmatch(r'\w+(?:\+\+|--)?', text):
        return True
    if text.startswith('('):
        try:
            return matching_paren(text, 0) == len(text) - 1
        except ValueError:
            return False
    match = re.match(r'\w+\s*\[', text)
    if match:
        depth = 1
        for index in range(match.end(), len(text)):
            if text[index] == '[': depth += 1
            elif text[index] == ']': depth -= 1
            if depth == 0: return index == len(text) - 1
    return False


def equality_type(expression, types):
    expression = expression.strip()
    while expression.startswith('('):
        try:
            if matching_paren(expression, 0) != len(expression)-1: break
        except ValueError:
            return None
        expression = expression[1:-1].strip()
    if re.fullmatch(r'\w+', expression):
        kind = clean_type(types.get(expression, ''))
        return 'pointer' if '*' in kind or kind in POINTER_ALIASES else ('int32' if kind in INTEGRAL32 else None)
    if re.fullmatch(r'&\s*\w+', expression):
        return 'pointer'
    load = re.match(r'^\*\s*\(\s*([\w\s]+(?:\s*\*)+)\s*\)\s*', expression)
    if load and one_atom(expression[load.end():]):
        kind = clean_type(load[1].rsplit('*', 1)[0])
        return 'pointer' if '*' in kind or kind in POINTER_ALIASES else ('int32' if kind in INTEGRAL32 else None)
    cast = re.match(r'^\(\s*([\w\s]+(?:\s*\*)*)\s*\)\s*', expression)
    if cast and one_atom(expression[cast.end():]):
        kind = clean_type(cast[1])
        return 'pointer' if '*' in kind or kind in POINTER_ALIASES else ('int32' if kind in INTEGRAL32 else None)
    array = re.match(r'^(\w+)\s*\[', expression)
    if array and one_atom(expression) and '*' in types.get(array[1], ''):
        kind = clean_type(types[array[1]].rsplit('*', 1)[0])
        return 'pointer' if '*' in kind or kind in POINTER_ALIASES else ('int32' if kind in INTEGRAL32 else None)
    # Ghidra often indexes a pointer loaded from an explicit pointer-to-pointer
    # view: (*(int **)(owner + offset))[index]. Keep both original reads.
    if expression.startswith('('):
        try:
            close = matching_paren(expression, 0)
        except ValueError:
            return None
        suffix = expression[close+1:].strip()
        if suffix.startswith('[') and one_atom('base' + suffix):
            base = expression[1:close].strip()
            load = re.match(r'^\*\s*\(\s*([\w\s]+\*\s*\*+)\s*\)\s*', base)
            if load and one_atom(base[load.end():]):
                kind = clean_type(load[1].rsplit('*', 2)[0])
                return 'pointer' if '*' in kind or kind in POINTER_ALIASES else ('int32' if kind in INTEGRAL32 else None)
    return None


def full_pointer_equality(body, params=(), globals_=None):
    types = variable_types(body, params)
    types.update(globals_ or {})
    view = code_view(body)
    edits = []
    for match in re.finditer(r'==|!=', view):
        left = equality_operand(view, match.start(), -1)
        right = equality_operand(view, match.end(), 1)
        if view[:left[0]].rstrip().endswith(('==','!=')) or view[right[1]:].lstrip().startswith(('==','!=')):
            continue
        values = [view[first:last] for first,last in (left,right)]
        kinds = [equality_type(value, types) for value in values]
        if 'pointer' not in kinds or any(kind not in ('pointer','int32') for kind in kinds):
            continue
        if all(re.fullmatch(r'\w+', value) for value in values) and clean_type(types.get(values[0],'')) == clean_type(types.get(values[1],'')):
            continue
        # Cast the complete value, including an address-of or loaded pointer.
        # The existing dereference keeps its original width and single evaluation.
        for (first,last), kind in zip((left,right), kinds):
            if kind == 'pointer':
                edits.extend(((first, '(uint)('), (last, ')')))
    # Ambiguous/chained equalities can select overlapping operands; refuse them.
    positions = [position for position, _ in edits]
    if len(positions) != len(set(positions)):
        return body
    for position, text in sorted(edits, reverse=True):
        body = body[:position] + text + body[position:]
    return body


UNSIGNED32 = {'uint', 'undefined4', 'ulong', 'unsigned', 'unsigned int', 'unsigned long',
              'DWORD', 'UINT', 'ULONG', 'LPARAM', 'WPARAM', 'LRESULT'}
PROMOTED_SMALL = {'bool', 'char', 'signed char', 'unsigned char', 'byte', 'uchar',
                  'short', 'signed short', 'unsigned short', 'ushort', 'undefined1', 'undefined2'}


def expression_category(kind):
    """Only evidenced i386 pointer and ordinary integral categories."""
    kind = clean_type(kind or '')
    if '::*' in kind or '(' in kind:
        return None
    if '*' in kind or kind in POINTER_ALIASES:
        return 'pointer'
    if kind in UNSIGNED32:
        return 'unsigned32'
    if kind in INTEGRAL32 or kind in PROMOTED_SMALL:
        return 'signed32'
    return None


def seed_expression_type(expression, types, depth=0):
    """Infer an operand's existing type, never change its arithmetic or reads.

    This small grammar refuses unknown calls/types, FP/wide arithmetic and
    conditionals. Explicit casts and loads, ordinary promoted integral math,
    and pointer +/- integer keep their existing widths and element strides.
    """
    if depth > 64:
        return None
    expression = expression.strip()
    while expression.startswith('('):
        try:
            if matching_paren(expression, 0) != len(expression)-1:
                break
        except ValueError:
            return None
        expression = expression[1:-1].strip()
    operators, stack, index = [], [], 0
    ranks = {'|':0, '^':1, '&':2, '<<':3, '>>':3, '+':4, '-':4, '*':5, '/':5, '%':5}
    while index < len(expression):
        char = expression[index]
        if char in '([':
            stack.append(char)
        elif char in ')]':
            if not stack:
                return None
            stack.pop()
        elif not stack:
            pair = expression[index:index+2]
            if pair in ('++', '--', '->', '&&', '||'):
                index += 2
                continue
            op = pair if pair in ('<<', '>>') else char
            if op in ranks and not (op in ('+', '-', '*', '&') and unary_operator(expression, index)):
                operators.append((ranks[op], index, op))
            if len(op) == 2:
                index += 1
        index += 1
    if stack:
        return None
    if operators:
        _, at, op = min(operators, key=lambda item:(item[0],-item[1]))
        left = seed_expression_type(expression[:at], types, depth+1)
        right = seed_expression_type(expression[at+len(op):], types, depth+1)
        a, b = expression_category(left), expression_category(right)
        integral = {'signed32', 'unsigned32'}
        if a in integral and b in integral:
            return ('uint' if a == 'unsigned32' else 'int') if op in ('<<', '>>') else ('uint' if 'unsigned32' in (a,b) else 'int')
        if op in ('+', '-') and a == 'pointer' and b in integral:
            return left
        if op == '+' and b == 'pointer' and a in integral:
            return right
        if op == '-' and a == b == 'pointer' and clean_type(left) == clean_type(right):
            return 'int'
        return None
    variable = re.fullmatch(r'(?:\+\+|--)?(\w+)(?:\+\+|--)?', expression)
    if variable and variable[1] in types:
        return types[variable[1]]
    literal = re.fullmatch(r'(0[xX][0-9a-fA-F]+|[0-9]+)([uUlL]*)', expression)
    if literal and literal[2].lower() in ('', 'u', 'l', 'ul', 'lu'):
        value = int(literal[1], 16 if literal[1].lower().startswith('0x') else 10)
        if value <= 0xffffffff and ('u' in literal[2].lower() or value <= 0x7fffffff or literal[1].lower().startswith('0x')):
            return 'uint' if 'u' in literal[2].lower() or value > 0x7fffffff else 'int'
    load = re.match(r'^\*\s*\(\s*([\w\s]+(?:\s*\*)+)\s*\)\s*', expression)
    if load and one_atom(expression[load.end():]):
        return load[1].rsplit('*',1)[0].strip()
    cast = re.match(r'^\(\s*([\w\s]+(?:\s*\*)*)\s*\)\s*', expression)
    if cast:
        rest = expression[cast.end():].strip()
        if rest and (one_atom(rest) or seed_expression_type(rest, types, depth+1) is not None):
            return cast[1].strip()
    array = re.match(r'^(\w+)\s*\[', expression)
    if array and one_atom(expression) and '*' in types.get(array[1], ''):
        return types[array[1]].rsplit('*',1)[0].strip()
    if expression.startswith(('+', '-', '~', '!')):
        kind = seed_expression_type(expression[1:], types, depth+1)
        category = expression_category(kind)
        if expression[0] == '!' and category:
            return 'bool'
        if category in ('signed32', 'unsigned32'):
            return 'uint' if category == 'unsigned32' else 'int'
    if expression.startswith('&') and re.fullmatch(r'&\s*\w+', expression):
        return 'void *'
    if expression.startswith('*'):
        operand = expression[1:].strip()
        simple = re.fullmatch(r'(\w+)(?:\+\+|--)?', operand)
        if simple and '*' in types.get(simple[1], ''):
            return types[simple[1]].rsplit('*',1)[0].strip()
    return None


def unsigned_pointer_ordering(body, params=(), globals_=None):
    """Order pointer bits only against an already unsigned32 operand.

    Signed/unknown/wide/FP counterparts stay unresolved. Cast the COMPLETE
    pointer operand once; do not change pointee loads or arithmetic strides.
    """
    types = variable_types(body, params)
    types.update(globals_ or {})
    view, edits = code_view(body), []
    for match in re.finditer(r'(?<![<>=!])(?:<=|>=|<|>)(?![<>=])', view):
        spans = [equality_operand(view,match.start(),-1), equality_operand(view,match.end(),1)]
        values = [view[a:b] for a,b in spans]
        categories = [expression_category(seed_expression_type(value,types)) for value in values]
        if sorted(categories, key=str) != sorted(['pointer','unsigned32']):
            continue
        scalar = values[categories.index('unsigned32')]
        if re.fullmatch(r'0(?:[uUlL]*)', scalar):
            continue  # A literal zero can already be a null pointer constant.
        first,last = spans[categories.index('pointer')]
        if any(first < b and last > a for a,b in edits):
            return body
        edits.append((first,last))
    for first,last in sorted(edits,reverse=True):
        body = body[:first] + '(uint)(' + body[first:last] + ')' + body[last:]
    return body


def normalize_import_exrefs(body, facts=None):
    """Resolve only known imported-function external-reference spellings."""
    if facts is None:
        facts = import_facts()
    view = code_view(body)
    edits = [(match.start(), match.end(), match[1])
             for match in re.finditer(r'\b(\w+)_exref\b', view) if match[1] in facts]
    for first,last,name in reversed(edits):
        body = body[:first] + name + body[last:]
    return body



def pointer_equality_boundaries(body, params=(), globals_=None):
    """Compare address bits once when Ghidra gives incompatible pointer views."""
    types = variable_types(body, params)
    types.update(globals_ or {})
    view = code_view(body)
    edits = []
    def bare_identifier(start, end):
        before, after = view[:start].rstrip(), view[end:].lstrip()
        return not before.endswith(('*', '&', '.', '->', ')')) and not after.startswith(('[', '.', '->', '('))
    for match in re.finditer(r'\b(\w+)\s*(==|!=)\s*(\w+)\b', view):
        if not bare_identifier(match.start(1), match.end(1)) or not bare_identifier(match.start(3), match.end(3)):
            continue
        left, right = types.get(match[1], ''), types.get(match[3], '')
        if not left or not right or left == right or '*' not in left + right:
            continue
        if any('*' not in kind and re.search(r'\b(?:float(?:10)?|double|u?longlong|(?:unsigned |signed )?__int64)\b', kind) for kind in (left, right)):
            continue
        # Equality is independent of signedness. No relational ordering or
        # pointer arithmetic is rewritten under this rule.
        for group, kind in ((1, left), (3, right)):
            if '*' in kind:
                edits.append((match.start(group), '(uint)'))
    for position, text in sorted(edits, reverse=True):
        body = body[:position] + text + body[position:]
    view = code_view(body)
    edits = []
    for match in re.finditer(r'\b(\w+)\s*(==|!=)\s*\(\s*[\w\s]+\*+\s*\)\s*(0x[0-9a-fA-F]+|[0-9]+)\b', view):
        if '*' not in types.get(match[1], '') or not bare_identifier(match.start(1), match.end(1)):
            continue
        if int(match[3], 0) > 0xffffffff:
            continue
        edits.append((match.start(), match.end(), '(uint)%s %s %s' % (match[1], match[2], match[3])))
    for first, last, text in reversed(edits):
        body = body[:first] + text + body[last:]
    return full_pointer_equality(body, params, globals_)


def return_boundaries(body, kind):
    """Make 32-bit pointer/value return conversions explicit at the ABI boundary."""
    if '*' not in kind and kind not in ('int', 'uint', 'undefined4', 'long', 'ulong', 'DWORD', 'LRESULT', 'HWND', 'HANDLE'):
        return body
    view, edits = code_view(body), []
    for match in re.finditer(r'\breturn\s+', view):
        end = expression_end(view, match.end())
        rhs = body[match.end():end]
        value = rhs.strip()
        if not value or value.startswith('(' + kind + ')'):
            continue
        first = match.end() + len(rhs) - len(rhs.lstrip())
        last = end - len(rhs) + len(rhs.rstrip())
        edits.extend(((first, '(%s)(' % kind), (last, ')')))
    for position, text in sorted(edits, key=lambda item: item[0], reverse=True):
        body = body[:position] + text + body[position:]
    return body


def reindent(body):
    """Ghidra indents two spaces per level; the project uses four."""
    lines = []
    for line in body.splitlines():
        stripped = line.lstrip(' ')
        lines.append(' ' * (2 * (len(line) - len(stripped))) + stripped if stripped else '')
    return '\n'.join(lines)


def nonnegative_tests(body):
    """Rewrite Ghidra's `-1 < E` back to `E >= 0`.

    Ghidra normalizes signed `E >= 0` to `-1 < E`; VC6 compiles the former as
    `test`/`jl` and the latter as `cmp E, -1`. The operand E extends to the
    first `)`, `&&`, `||`, `?`, `:`, `;` or `,` at its own nesting depth; Ghidra
    parenthesizes anything that binds more loosely than `<`, so `E >= 0` keeps
    the same meaning.
    """
    output, cursor = '', 0
    for match in re.finditer(r'-1 < ', body):
        if match.start() < cursor or (match.start() and body[match.start() - 1] not in ' (!'):
            continue
        at, depth = match.end(), 0
        while at < len(body):
            char = body[at]
            if char in '([':
                depth += 1
            elif char in ')]':
                if depth == 0:
                    break
                depth -= 1
            elif depth == 0 and (char in '?:;,' or body.startswith('&&', at) or body.startswith('||', at)):
                break
            at += 1
        operand = body[match.end():at].rstrip()
        if not operand:
            continue
        output += body[cursor:match.start()] + operand + ' >= 0'
        cursor = match.end() + len(operand)
    return output + body[cursor:]


def split_params(text):
    text = text.strip()
    if not text or text == 'void':
        return []
    return [p.strip() for p in text.split(',')]


def parse_header(text):
    """Return (ret, conv, name, params, header span) for a Ghidra export."""
    for match in HEADER.finditer(text):
        if match.group('name').startswith('FUN_') or match.group('conv'):
            return (match.group('ret').strip(), match.group('conv') or '', match.group('name'),
                    split_params(match.group('params')), match.span())
    raise ValueError('No Ghidra function header found')


def param_parts(param):
    """'undefined4 *param_2' -> ('undefined4 *', 'param_2')."""
    match = re.match(r'^(.*?)(\w+)$', param.strip())
    if not match or param.strip() == '...':
        return param, ''
    return match.group(1).strip(), match.group(2)


def matching_paren(text, start):
    depth = 0
    for index in range(start, len(text)):
        if text[index] == '(':
            depth += 1
        elif text[index] == ')':
            depth -= 1
            if depth == 0:
                return index
    raise ValueError('Unbalanced call at %d' % start)


def split_args(text):
    args, depth, current = [], 0, ''
    for index, char in enumerate(code_view(text)):
        if char == ',' and depth == 0:
            args.append(current); current = ''; continue
        depth += char in '([' ; depth -= char in ')]'
        current += text[index]
    if current.strip():
        args.append(current)
    return [a.strip() for a in args]


def call_sites(body, name):
    """Yield (start, end, args, value_used) for each call of name."""
    view = code_view(body)
    for match in re.finditer(r'\b' + name + r'\s*\(', view):
        open_at = match.end() - 1; close_at = matching_paren(view, open_at)
        before = view[:match.start()].rstrip()
        used = bool(before) and before[-1] in '=(),!&|+-*<>?:' or before.endswith('return')
        yield match.start(), close_at + 1, split_args(body[open_at + 1:close_at]), used


def ecx_owners(row):
    """Callee address -> ECX setups before each direct call in the original.

    Each entry is ('imm', value) for `mov ecx, imm32`, ('reg', name) for a
    register copy, or None when the setup is not a plain load just before the
    call (looked for among the six preceding instructions, stopping at any
    other write of ECX).
    """
    if not row:
        return {}
    import capstone
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    owners = {}
    for span in row['ranges']:
        instructions = list(decoder.disasm(bytes.fromhex(span['bytes_hex']), int(span['start'], 16)))
        for index, insn in enumerate(instructions):
            if insn.mnemonic != 'call' or not insn.op_str.startswith('0x'):
                continue
            setup = None
            for previous in reversed(instructions[max(0, index - 6):index]):
                operands = previous.op_str.split(', ')
                if operands[0] != 'ecx':
                    if previous.mnemonic in ('call', 'ret', 'jmp') or previous.mnemonic.startswith('j'):
                        break
                    continue
                if previous.mnemonic == 'mov' and len(operands) == 2 and operands[1].startswith('0x'):
                    setup = ('imm', int(operands[1], 16))
                elif previous.mnemonic == 'mov' and len(operands) == 2 and operands[1] in ('esi', 'edi', 'ebx', 'ebp'):
                    setup = ('reg', operands[1])
                break
            owners.setdefault(int(insn.op_str, 16), []).append(setup)
    return owners


def declare_callee(body, name, prototype, owner_hint=None):
    """Return (body, declarations) shaped by Ghidra's call sites.

    Caller-side arity often differs from the callee export (an implicit ECX
    owner, dropped stack arguments); each distinct arity becomes an overload,
    which keeps the address in every mangled name.
    """
    c_ret, c_conv, c_params = prototype
    sites = list(call_sites(body, name))
    # Ghidra callers treat 32-bit results as whatever they need; a uint return
    # keeps EAX semantics and converts with the caller's own casts.
    wide = re.search(r'float|double|longlong|undefined8|qword', c_ret)
    if c_ret.strip() != 'void' and not wide or any(site[3] for site in sites) and not wide:
        c_ret = 'undefined4'
    members = c_conv == '__thiscall'
    expected = c_params[1:] if members else c_params
    signatures, output, cursor = {}, '', 0
    for start, end, args, _ in sites:
        if start < cursor:
            continue
        if members:
            owner_known = len(args) == len(c_params)
            owner = args[0] if owner_known else owner_hint or '0 /* TODO: implicit ECX owner */'
            rest = args[1:] if owner_known else args
            call = '((Callee_%s*)(%s))->%s(%s)' % (name[4:], owner, name, ', '.join(rest))
        else:
            rest = args
        params = expected if len(rest) == len(expected) else ['int'] * len(rest)
        signatures[len(rest)] = params
        # C-style casts to the declared parameter types keep 32-bit values
        # unchanged while satisfying C++ pointer conversion rules.
        rest = ['(%s)(%s)' % (param_parts(p)[0] or p, a) for p, a in zip(params, rest)]
        if members:
            call = '((Callee_%s*)(%s))->%s(%s)' % (name[4:], owner, name, ', '.join(rest))
        else:
            call = '%s(%s)' % (name, ', '.join(rest))
        output += body[cursor:start] + call; cursor = end
    body = output + body[cursor:]
    if not signatures:
        # Only the address is taken (`(code *)FUN_...`): any declaration that
        # keeps the address-bearing name binds it.
        return body, ['extern void __cdecl %s(void);' % name]
    if members:
        methods = ' '.join('%s %s(%s);' % (c_ret, name, ', '.join(p)) for p in signatures.values())
        return body, ['struct Callee_%s { %s };' % (name[4:], methods)]
    return body, ['extern %s %s %s(%s);' % (c_ret, c_conv, name, ', '.join(p) or 'void')
                  for p in signatures.values()]


ADDRESS_STORE = re.compile(r'^(\s*)(\*\w+|\w+\[[^\]\n]+\]) = (&\w+);', re.M)


def address_stores(body):
    """`*p = &label;` / `p[k] = &label;` store an address into a 32-bit slot.

    Ghidra writes vtable-pointer and table stores this way; C++ needs the
    pointer converted explicitly (the stored 32-bit value is unchanged).
    """
    return ADDRESS_STORE.sub(lambda m: '%s%s = (undefined4)(%s);' % m.groups(), body)


def cast_assignments(body, params):
    """Make Ghidra's C-style implicit pointer/integer assignments explicit.

    `local = rhs;` becomes `local = (T)(rhs);` for declared locals/params. The
    conversion is the one C would apply implicitly, so 32-bit values and
    arithmetic conversions are unchanged; C++ merely requires it spelled out.
    """
    types = variable_types(body, params)
    def repl(match):
        indent, name, rhs = match.groups()
        kind = types.get(name)
        if not kind or rhs.startswith('(' + kind + ')'):
            return match.group(0)
        return '%s%s = (%s)(%s);' % (indent, name, kind, rhs)
    return ASSIGN.sub(repl, body)


_IMPORTS = []


def import_facts():
    """Recorded import signatures and IAT slots; no inferred platform ABI."""
    if not _IMPORTS:
        path = Path(__file__).resolve().parents[2] / 'manifests/imports.json'
        _IMPORTS.append({i['name']: i for i in json.loads(path.read_bytes())['imports']} if path.exists() else {})
    return _IMPORTS[0]


def imported_calls(body):
    """Imported API calls and function-address values -> recorded import facts."""
    facts = import_facts()
    names = set(re.findall(r'\b[A-Za-z_]\w*\b', code_view(body)))
    return {name: facts[name] for name in names if name in facts}


def declare_import(body, name, fact):
    """Use the recorded SDK signature and bind the actual IAT slot.

    A missing/unknown convention or inconsistent arity stays a seed refusal;
    counting source arguments cannot establish a callee's stack convention.
    """
    if fact.get('convention') not in ('__stdcall', '__cdecl') or not fact.get('signature'):
        raise ValueError('Import signature/convention unavailable: ' + name)
    ret, conv, parsed_name, params, _ = parse_header(fact['signature'])
    if conv != fact['convention'] or parsed_name != name:
        raise ValueError('Inconsistent import signature: ' + name)
    variadic = bool(params and params[-1] == '...')
    fixed = params[:-1] if variadic else params
    output, cursor = '', 0
    for start, end, args, used in call_sites(body, name):
        if start < cursor:
            continue
        if len(args) < len(fixed) or not variadic and len(args) != len(fixed):
            raise ValueError('Import argument count disagrees with manifest: ' + name)
        arguments = ['(%s)(%s)' % (param_parts(p)[0] or p, a) for p, a in zip(fixed, args)]
        arguments += args[len(fixed):]
        output += body[cursor:start] + name + '(' + ', '.join(arguments) + ')'
        cursor = end
    stack = sum(stack_bytes(p) for p in fixed)
    binding = '__imp__%s@%d' % (name, stack) if conv == '__stdcall' else '__imp__' + name
    declaration = 'extern "C" __declspec(dllimport) %s %s %s(%s); // @ref %s=%s' % (
        ret, conv, name, ', '.join(params) or 'void', binding, fact['iat'])
    return output + body[cursor:], declaration


KEYWORDS = {'if', 'while', 'for', 'switch', 'return', 'sizeof', 'do'}


def named_calls(body, inventory):
    """Non-FUN_ callees Ghidra named (operator_new, _strcmp...) -> address."""
    names = getattr(inventory, '_seed_named_calls', None)
    if names is None:
        names = {}
        for directory in inventory.passes:
            for entry, row in inventory.rows(directory).items():
                if not row['name'].startswith('FUN_') and re.match(r'^[A-Za-z_]\w*$', row['name']):
                    names.setdefault(row['name'], entry)
        inventory._seed_named_calls = names
    return {n: names[n] for n in set(re.findall(r'\b([A-Za-z_]\w*)\s*\(', code_view(body)))
            if n in names and n not in KEYWORDS}


def named_thunk_values(body, entry, inventory, params=()):
    """Declare address-only thunk names from positive original DATA evidence.

    The existing `code` type means an unknown callable signature. No new call
    or helper body is generated, and no ABI or bounds acceptance is implied.
    A shared suffix/jump target alone never identifies a thunk's own address.
    """
    view = code_view(body)
    tokens = set(re.findall(r'\bthunk_[A-Za-z_]\w*\b', view))
    if not tokens:
        return []
    groups = getattr(inventory, '_seed_thunk_value_names', None)
    if groups is None:
        groups = {}
        for directory in inventory.passes:
            for at, row in inventory.rows(directory).items():
                if re.fullmatch(r'thunk_[A-Za-z_]\w*', row['name']):
                    groups.setdefault(row['name'], set()).add(at)
        inventory._seed_thunk_value_names = groups
    identifiers = set(variable_types(body, params))
    identifiers.update(name for _, name, _ in scalar_declarations(view)[0])
    declarations = []
    for name in sorted(tokens & groups.keys()):
        if name in identifiers or list(call_sites(body, name)):
            continue
        uses = list(re.finditer(r'\b' + re.escape(name) + r'\b', view))
        if any(view[:m.start()].rstrip().endswith(('::', '.', '->')) or
               re.match(r'\s*(?:\)*\s*\(|\[)', view[m.end():]) for m in uses):
            continue
        from seed_thunk_values import original_thunk_address
        proof = original_thunk_address(entry, groups[name], inventory)
        if proof is None:
            continue
        sites = ','.join('%08x' % at for at in proof['push_sites'])
        declarations.append('// Address-only thunk: original DATA PUSH sites %s; inventory bounds/entry roots and callable ABI remain hypotheses.' % sites)
        # Namespace-local C++ linkage keeps different owners' bindings separate
        # when a composite population contains both same-named thunk entries.
        declarations.append('extern code %s; // @ref ?%s@seed_%08x@@=%08x' %
                            (name, name, entry, proof['entry']))
    return declarations


def accepted_sources(catalog):
    return {r['entry']: r['source'] for r in catalog.get('regions', [])}


def stack_cleanup(row):
    """Bytes a function pops on return (`ret N`), from its frozen original body.

    None when the body has no return or returns inconsistently (tail calls,
    noreturn paths), in which case the Ghidra convention is left alone.
    """
    if not row:
        return None
    import capstone
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    pops = set()
    for span in row['ranges']:
        for insn in decoder.disasm(bytes.fromhex(span['bytes_hex']), int(span['start'], 16)):
            if insn.mnemonic == 'ret':
                pops.add(int(insn.op_str, 16) if insn.op_str else 0)
    return pops.pop() if len(pops) == 1 else None


def stack_bytes(param):
    """Stack bytes of one parameter: 8 for 64-bit integers and doubles, else 4."""
    kind = param_parts(param)[0]
    if '*' in kind:
        return 4
    return 8 if re.search(r'double|float10|longlong|undefined8|qword|__int64', kind) else 4


def fit_convention(conv, params, popped, has_this):
    """Correct Ghidra's convention/stack parameters with the original `ret N`.

    Callee-cleanup (`ret N`) means __stdcall/__thiscall/__fastcall stack
    parameters totalling N bytes; a plain `ret` means caller cleanup. Missing
    stack parameters are added as unused dwords so the callee pops N bytes.
    """
    if popped is None:
        return conv, params
    fixed = {'__thiscall': 1, '__fastcall': 2}.get(conv, 0) if has_this or conv == '__fastcall' else 0
    stack = params[fixed:]
    if popped == 0 and conv == '__stdcall' and stack:
        return '__cdecl', params
    if popped > 0 and conv in ('', '__cdecl'):
        conv = '__stdcall'
    used = sum(stack_bytes(p) for p in stack)
    if popped > 0 and conv in ('__stdcall', '__thiscall', '__fastcall') and used < popped:
        params = params + ['int unused_%d' % i for i in range(len(stack), len(stack) + (popped - used) // 4)]
    return conv, params


CHAR = r"'(?:\\.|[^'\\])+'"


def byte_global(body, symbol):
    """True when Ghidra uses the global only as a character value."""
    name = re.escape(symbol)
    uses = len(re.findall(r'\b%s\b' % name, body))
    chars = len(re.findall(r'\b%s\s*(?:==|!=|=)\s*%s' % (name, CHAR), body)) + \
        len(re.findall(r'%s\s*(?:==|!=)\s*%s\b' % (CHAR, name), body)) + \
        len(re.findall(r'\(char\)%s\b' % name, body))
    return uses > 0 and chars == uses


RTTI_ADDRESS = re.compile(r'(?<![\w&])&\s*([A-Za-z_]\w*(?:::[A-Za-z_]\w*)*)::RTTI_Type_Descriptor\b')
_RTTI_ADDRESSES = []


def rtti_address_names(descriptors):
    """Only unambiguous, ordinary class/struct names from original RTTI."""
    found, repeated = {}, set()
    for symbol, address in descriptors.items():
        match = re.fullmatch(r'\?\?_R0\?A[UV]([A-Za-z_]\w*(?:@[A-Za-z_]\w*)*)@@@8', symbol)
        if not match:
            continue
        name = '::'.join(reversed(match[1].split('@')))
        if name in found and found[name] != address:
            repeated.add(name)
        found[name] = address
    return {name: address for name, address in found.items() if name not in repeated}


def original_rtti_addresses():
    """Hash the exact target, then reuse the strict auditor's RTTI bindings."""
    if not _RTTI_ADDRESSES:
        from verify_manifest import Audit
        audit = Audit(REPOSITORY, 'private/original-target-20261020/inputs/game.exe')
        _RTTI_ADDRESSES.append(rtti_address_names(audit.original_type_descriptors()))
    return _RTTI_ADDRESSES[0]


def rtti_address_labels(body, addresses=None):
    """Name address-only RTTI labels without inventing the owning class layout.

    A DAT label supplies the same address bits. Direct descriptor values,
    fields, arrays and descriptor-pointer arithmetic remain unsupported.
    """
    view = code_view(body)
    matches = list(RTTI_ADDRESS.finditer(view))
    if not matches:
        return body, []
    addresses = original_rtti_addresses() if addresses is None else addresses
    edits, used = [], {}
    for match in matches:
        address = addresses.get(match[1])
        if type(address) is not int or not 0 < address <= 0xffffffff:
            continue
        before = re.sub(r'(?:\(\s*)+$', '', view[:match.start()].rstrip()).rstrip()
        if before.endswith('*'):
            continue              # a descriptor value/sizeof-object needs its real type
        after = view[match.end():].lstrip()
        # Also reject arithmetic after parentheses around the address. This
        # conservatively skips arithmetic on an enclosing call result too.
        after = re.sub(r'^(?:\)\s*)+', '', after)
        if after.startswith(('.', '->', '::', '[', '+', '-', '*', '/', '%', '<<', '>>')):
            continue
        label = 'DAT_%08x' % address
        edits.append((match.start(), match.end(), '&' + label))
        used[match[1]] = address
    for start, end, replacement in reversed(edits):
        body = body[:start] + replacement + body[end:]
    notes = ['// Original RTTI address: %s -> DAT_%08x; descriptor layout is not modeled.' % item
             for item in sorted(used.items())]
    return body, notes


_SWITCH_ORIGINAL = []


def original_index_switch(entry, dispatch, table):
    from seed_switches import inspect_index_switch
    if not _SWITCH_ORIGINAL:
        from verify_manifest import Audit
        audit = Audit(REPOSITORY, 'private/original-target-20261020/inputs/game.exe')
        catalog = catalog_io.load(catalog_io.locate(REPOSITORY), references=False)
        _SWITCH_ORIGINAL.append((audit, {row['entry'] for row in catalog['regions']}))
    audit, accepted = _SWITCH_ORIGINAL[0]
    return inspect_index_switch(audit, entry, dispatch, table, accepted)


def indexed_switch_artifacts(body, entry, params=(), facts=None):
    """Use verified integer cases, never a runtime array of instruction pointers."""
    from seed_switches import UnsupportedSwitch
    pattern = re.compile(r'\bswitch\s*\(\s*\(\s*&switchD_([0-9a-f]{8})::switchdataD_([0-9a-f]{8})'
                         r'\s*\)\s*\[\s*([A-Za-z_]\w*)\s*\]\s*\)')
    view = code_view(body)
    matches = list(pattern.finditer(view))
    if not matches:
        return body, []
    types, edits, notes = variable_types(body, params), [], []
    for match in matches:
        if clean_type(types.get(match[3], '')) not in INTEGRAL32:
            continue
        opening = match.end()
        while opening < len(view) and view[opening].isspace():
            opening += 1
        if opening == len(view) or view[opening] != '{':
            continue
        depth, cursor, cases, unsupported = 1, opening+1, [], False
        while cursor < len(view) and depth:
            if view[cursor] == '{': depth += 1
            elif view[cursor] == '}': depth -= 1
            elif (depth == 1 and view.startswith('case', cursor) and
                  not (view[cursor-1].isalnum() or view[cursor-1] == '_') and
                  (cursor+4 == len(view) or not (view[cursor+4].isalnum() or view[cursor+4] == '_'))):
                case = re.match(r'case\s*\(\s*undefined\s*\*\s*\)\s*0x([0-9a-fA-F]+)\s*:', view[cursor:])
                if not case:
                    unsupported = True
                    break
                cases.append((cursor, cursor+case.end(), int(case[1], 16)))
                cursor += case.end()-1
            cursor += 1
        if unsupported or depth or not cases:
            continue
        dispatch, table = int(match[1], 16), int(match[2], 16)
        try:
            proof = original_index_switch(entry, dispatch, table) if facts is None else facts[(dispatch, table)]
        except (UnsupportedSwitch, KeyError):
            continue
        targets = proof['targets']
        if len({target for _, _, target in cases}) != len(cases) or {target for _, _, target in cases} != set(targets):
            continue
        # Refuse overlapping edits; nested case labels belong to their own switch.
        if any(start < cursor and end > match.start() for start, end, _ in edits):
            continue
        edits.append((match.start(), match.end(), 'switch(%s)' % match[3]))
        for start, end, target in cases:
            indices = [index for index, at in enumerate(targets) if at == target]
            edits.append((start, end, ' '.join('case %d:' % index for index in indices)))
        notes.append('// Original guarded switch %08x: integer indices from read-only table %08x; '
                     'local-flow/call/entry hypotheses remain explicit.' % (dispatch, table))
    for start, end, replacement in sorted(edits, reverse=True):
        body = body[:start]+replacement+body[end:]
    return body, notes


def seed(entry, inventory, accepted):
    text = inventory.decompiled(entry)
    if text is None:
        raise ValueError('No Ghidra export for %08x' % entry)
    ret, conv, name, params, (start, end) = parse_header(text)
    conv, params = fit_convention(conv, params, stack_cleanup(inventory.function(entry)[1]),
                                  conv == '__thiscall')
    body = nonnegative_tests(reindent(text[end:].strip()))
    body = normalize_import_exrefs(body)
    body, labels = local_labels(body)
    body, switch_notes = indexed_switch_artifacts(body, entry, params)
    body = nan_artifacts(body, params, named_calls(body, inventory) if re.search(r'\bNAN\s*\(', code_view(body)) else ())
    body = byte_update_artifacts(body, params)
    body = stack_artifacts(extend_artifacts(concat_artifacts(body)), params, conv)
    body = LABEL.sub(lambda m: m.group(1) + re.sub(r'\W', '_', m.group(2)) + m.group(3), body)
    body = RAM.sub(lambda m: '(*(%s *)0x%s)' % (RAM_TYPES.get(m.group(1), 'int'), m.group(2)), body)
    body = PARTIAL.sub(lambda m: '(*(%s*)((char*)&%s + %s))' % (PARTIAL_TYPES.get(m.group(3), 'uint'),
                                                               m.group(1), m.group(2)), body)
    body, scalar_view_notes = scalar_address_views(body, params)
    body, rtti_notes = rtti_address_labels(body)
    declarations, notes = [], list(rtti_notes) + switch_notes + scalar_view_notes
    owners = ecx_owners(inventory.function(entry)[1])
    this_name = param_parts(params[0])[1] if conv == '__thiscall' and params else None
    for callee in sorted(set(CALLEE.findall(code_view(body))) - {name}):
        address = int(callee[4:], 16)
        if address in accepted:
            notes.append('//   %s -> %s' % (callee, accepted[address]))
        callee_text = inventory.decompiled(address)
        try:
            c_ret, c_conv, _, c_params, _ = parse_header(callee_text or '')
        except ValueError:
            declarations.append('extern void %s(...);  // no Ghidra prototype' % callee); continue
        popped = stack_cleanup(inventory.function(address)[1])
        if popped and c_conv in ('', '__cdecl'):
            c_conv = '__stdcall'          # callee pops its own arguments
        elif popped == 0 and c_conv == '__stdcall':
            c_conv = '__cdecl'
        # The original's ECX load before each call names an owner Ghidra's
        # text dropped: one global object for every site, or this function's
        # own `this` kept in a register.
        setups = set(owners.get(address, []))
        hint = None
        if len(setups) == 1 and None not in setups:
            kind, value = next(iter(setups))
            if kind == 'imm':
                hint = '&DAT_%08x' % value
                if c_conv in ('', '__cdecl', '__stdcall') and (popped or not c_params):
                    c_conv, c_params = '__thiscall', ['void *this_'] + list(c_params)
            elif this_name:
                hint = this_name
        body, lines = declare_callee(body, callee, (c_ret, c_conv, c_params), hint)
        declarations.extend(lines)
    if list(call_sites(body, name)):
        body, _ = declare_callee(body, name, (ret, conv, params), this_name)
        body = body.replace('Callee_%08x' % entry, 'Owner_%08x' % entry)
    imports = imported_calls(body)
    for api, fact in sorted(imports.items()):
        body, declaration = declare_import(body, api, fact)
        declarations.append(declaration)
    for library, address in sorted(named_calls(body, inventory).items()):
        if library in imports:
            continue
        declarations.append('extern "C" undefined4 __cdecl %s(...);  // @ref _%s=%08x' % (library, library, address))
    declarations.extend(named_thunk_values(body, entry, inventory, params))
    evidence_root = (REPOSITORY / 'private/original-target-20261020/inventory').resolve()
    shared = (shared_pointer_types() if any(p.resolve().is_relative_to(evidence_root) for p in inventory.passes) else {})
    body, global_types = recover_global_pointers(body, params, shared)
    for symbol, kind in sorted(global_types.items()):
        known = shared.get(int(symbol[-8:], 16))
        if known and known['kind'] == kind:
            if known['forward'] and known['forward'] not in declarations:
                declarations.append(known['forward'])
            declarations.append('// %s pointer type from %s; raw field offsets remain explicit.' % (symbol, known['header']))
    for symbol in sorted(set(DATA.findall(code_view(body))) - labels):
        kind = global_types.get(symbol) or (pointer_global_type(body, symbol) if 'PTR_' in symbol else 'char' if symbol.startswith('LAB_') else 'undefined4')
        global_types[symbol] = kind
        if kind == 'undefined4' and byte_global(body, symbol):
            # Ghidra compares or assigns it as a character: a byte global.
            global_types[symbol] = 'char'
            declarations.append('extern "C" char %s;' % symbol); continue
        declarations.append('extern "C" %s %s%s;' % (kind, symbol, '[]' if kind == 'char' else ''))
    for symbol in sorted(set(STRING.findall(code_view(body)))):
        declarations.append('extern "C" %s %s[];' % ('wchar16' if symbol.startswith('u_') else 'char', symbol))
    body = cast_void_global_offsets(body, global_types)
    body = pointer_equality_boundaries(body, params, global_types)
    body = unsigned_pointer_ordering(body, params, global_types)
    body = cast_storage_boundaries(body, params, global_types)
    body = address_stores(cast_assignments(body, params))
    body = return_boundaries(body, ret)
    if conv == '__thiscall' and params:
        this_type, this_name = param_parts(params[0])
        owner = 'Owner_%08x' % entry
        local = '' if this_name == 'this' else '    %s %s = (%s)this;\n' % (this_type, this_name, this_type)
        definition = ('struct %s { %s %s(%s); };\n\n%s %s::%s(%s)\n{\n%s%s' % (
            owner, ret, name, ', '.join(params[1:]), ret, owner, name, ', '.join(params[1:]),
            local, body.lstrip('{').lstrip('\n')))
    else:
        definition = '%s %s %s(%s)\n%s' % (ret, conv, name, ', '.join(params) or 'void', body)
    # A private namespace per seed lets accepted seeds share one compiler
    # translation unit without clashing declarations or cross-seed inlining;
    # every mangled name still carries the FUN_ address.
    return '\n'.join(documentation(entry, inventory, text[start:end].strip(), notes) +
                     [MARKER, INCLUDE, '', 'namespace seed_%08x {' % entry, '',
                      sdk_preamble(body+'\n'+'\n'.join(declarations), params, ret), ''] +
                     (declarations + [''] if declarations else []) +
                     [definition.rstrip(), '', '}  // namespace seed_%08x' % entry, ''])


_OWNERS = []


def _owners():
    if not _OWNERS:
        from class_owners import ClassOwners
        _OWNERS.append(ClassOwners())
    return _OWNERS[0]


def documentation(entry, inventory, prototype, callee_notes):
    """Header comment: what is known about the function, without guessing."""
    _, row = inventory.function(entry)
    lines = ['// 0x%08x: function not yet identified' % entry, '//']
    owner = _owners().owner(entry)
    if owner:
        lines.append('// Owner: %s, %s (from RTTI/vtables).' % owner)
    if row:
        lines.append('// Body: %d bytes (frozen inventory bound).' % sum(r['length'] for r in row['ranges']))
        refs = row.get('entry_references') or []
        kinds = sorted({r['type'].lower().replace('_', ' ') for r in refs})
        lines.append('// Referenced from %d site%s%s.' % (len(refs), '' if len(refs) == 1 else 's',
                                                       ' (' + ', '.join(kinds) + ')' if kinds else ''))
    lines.append('// Ghidra prototype: ' + ' '.join(prototype.split()))
    if callee_notes:
        lines += ['// Callees with accepted source:'] + callee_notes
    lines += ['//', '// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);',
              '// rename and retype as the purpose becomes known.', '//']
    return lines


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('entries', nargs='+', help='original entry addresses (hex)')
    parser.add_argument('--output', type=Path, default=REPOSITORY / 'build/candidates')
    parser.add_argument('--force', action='store_true', help='overwrite an existing scratch seed')
    args = parser.parse_args()
    from inventory import Inventory
    inventory = Inventory()
    accepted = accepted_sources(catalog_io.load(catalog_io.locate(REPOSITORY), references=False))
    for item in args.entries:
        entry = int(item, 16)
        if entry in accepted:
            print('%08x already accepted: %s' % (entry, accepted[entry])); continue
        path = args.output / ('%08x' % entry) / 'candidate.cpp'
        if path.exists() and not args.force:
            print('%08x exists: %s (use --force)' % (entry, path)); continue
        path.parent.mkdir(parents=True, exist_ok=True)
        with open(path, 'w', encoding='utf-8', newline='\n') as stream:
            stream.write(seed(entry, inventory, accepted))
        print(path)


if __name__ == '__main__':
    main()
