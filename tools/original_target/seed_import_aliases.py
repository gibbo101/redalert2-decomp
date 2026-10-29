"""Closed C-syntax ownership check for explicit imported direct-call aliases.

This parses declarations and statements; it does not infer ABI, C++ ownership,
types, addresses or expression semantics. Unparsed/ambiguous inputs refuse.
"""
import re


class AliasRefusal(ValueError):
    pass


# Syntax-only typedef names already used by the Ghidra/Win32 seed vocabulary.
# Their dummy parser types never enter emitted C++ or supply layout evidence.
TYPE_NAMES = frozenset('''undefined undefined1 undefined2 undefined3 undefined4
undefined8 byte uchar sbyte ushort word wchar16 uint uint3 dword ulong int3
ulonglong qword longlong float10 code bool UINT DWORD WPARAM LPARAM LRESULT
BOOL WORD BYTE HWND HANDLE HINSTANCE HMODULE LPVOID HDC HKEY CHAR LCID LONG
tagRECT RECT GUID IID LPSTR LPCSTR LPDWORD LPWSTR LPCWSTR LPCRITICAL_SECTION
LPSECURITY_ATTRIBUTES LPOVERLAPPED MSG tagMSG POINT tagPOINT LPPOINT'''.split())

KEYWORDS = frozenset('''auto break case char const continue default do double
else enum extern float for goto if int long register return short signed sizeof
static struct switch typedef union unsigned void volatile while _Alignas
_Alignof _Atomic _Bool _Complex _Generic _Imaginary _Noreturn _Static_assert
_Thread_local alignas alignof and and_eq asm bitand bitor bool catch char16_t
char32_t class compl concept consteval constexpr constinit const_cast co_await
co_return co_yield decltype delete dynamic_cast explicit export false friend
import inline module mutable namespace new noexcept not not_eq nullptr operator
or or_eq private protected public reinterpret_cast requires static_assert
static_cast template this thread_local throw true try typeid typename using
virtual wchar_t xor xor_eq __asm __asm__ __cdecl __clrcall __declspec __except
__fastcall __finally __int8 __int16 __int32 __int64 __leave __stdcall __thiscall
__try __vectorcall __pragma _Pragma'''.split())


def _masked(text, literals=True):
    pattern = r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\''
    def replace(match):
        value = match[0]
        if not literals and not value.startswith(('/', '*')):
            return value
        return ''.join('\n' if c == '\n' else ' ' for c in value)
    return re.sub(pattern, replace, text)


def direct_import_aliases(text, aliases, reserved_names=()):
    """Return changed text and verified direct-call edits, or refuse entirely.

    aliases is an explicit, independently validated source-token -> C-name map.
    A replacement name already occurring in the function is refused even if a
    parser could resolve it: this routine has no evidence for its global owner.
    """
    if not aliases:
        return text, []
    view = _masked(text)
    identifiers = list(re.finditer(r'\b[A-Za-z_]\w*\b', view))
    present = {m[0] for m in identifiers} & set(aliases)
    if not present:
        return text, []
    names = {name: aliases[name] for name in present}
    if (len(set(aliases.values())) != len(aliases) or
            set(aliases) & set(aliases.values()) or
            any(not re.fullmatch(r'[A-Za-z_]\w*', name, re.ASCII)
                for name in set(aliases) | set(aliases.values()))):
        raise AliasRefusal('Ambiguous imported alias identity')
    if set(aliases.values()) & (TYPE_NAMES | KEYWORDS | set(reserved_names)):
        raise AliasRefusal('Imported replacement name is owned by language or emission context')
    if {m[0] for m in identifiers} & set(names.values()):
        raise AliasRefusal('Imported replacement name already has source occurrences')
    # Translation-phase escapes and preprocessing can change token ownership
    # before comments are removed. No attempt is made to emulate those phases.
    if (re.search(r'\\(?:\r\n|\n|\r)', text) or '??' in text or
            any(token in view for token in ('#', '%:', '<%', '%>', '<:', ':>', '::')) or
            '\\' in view or any(ord(c) > 127 for c in view) or
            re.search(r'\b(?:u8|u|U|L)?R\s*"', text) or
            {m[0] for m in identifiers} & {'_Pragma', '__pragma'}):
        raise AliasRefusal('Imported alias has unsupported preprocessing or C++ syntax')
    try:
        from pycparser import c_ast, c_parser
    except ImportError as error:
        raise AliasRefusal('Closed imported-alias C parser unavailable') from error
    parser_text = _masked(text, literals=False)
    parser_text = re.sub(r'\b(?:__fastcall|__thiscall|__stdcall|__cdecl)\b',
                         lambda m: ' ' * len(m[0]), parser_text)
    prefix = ''.join('typedef int %s;\n' % name for name in sorted(TYPE_NAMES))
    try:
        ast = c_parser.CParser().parse(prefix + parser_text, filename='import-alias.c')
    except Exception as error:
        raise AliasRefusal('Imported alias lacks a complete C ownership parse') from error
    declarations = ast.ext[len(TYPE_NAMES):]
    if len(declarations) != 1 or not isinstance(declarations[0], c_ast.FuncDef):
        raise AliasRefusal('Imported alias requires one complete function only')
    starts = [0] + [m.end() for m in re.finditer('\n', parser_text)]
    prefix_lines = prefix.count('\n')
    observed = []
    protected = set(names) | set(names.values())

    def walk(node, parent=None):
        if isinstance(node, c_ast.ID):
            if node.name in protected:
                if (node.name not in names or not isinstance(parent, c_ast.FuncCall)
                        or parent.name is not node):
                    raise AliasRefusal('Imported alias occurs outside an unqualified direct call')
                line = node.coord.line - prefix_lines
                if not 1 <= line <= len(starts):
                    raise AliasRefusal('Imported alias coordinate is outside source')
                offset = starts[line - 1] + node.coord.column - 1
                if view[offset:offset + len(node.name)] != node.name:
                    raise AliasRefusal('Imported alias coordinate/token mismatch')
                observed.append((offset, offset + len(node.name), names[node.name]))
        elif not isinstance(node, c_ast.Constant):
            # These include all Decl/Typedef/TypeDecl names, struct/union/enum
            # tags/members, labels, goto targets and IdentifierType names.
            for attr in node.attr_names:
                value = getattr(node, attr)
                values = value if isinstance(value, (list, tuple)) else [value]
                if any(isinstance(item, str) and item in protected for item in values):
                    raise AliasRefusal('Imported alias is owned by a source declaration or type')
        for _, child in node.children():
            walk(child, node)
    walk(declarations[0])
    expected = {(m.start(), m.end()) for m in identifiers if m[0] in names}
    actual = {(a, z) for a, z, _ in observed}
    if actual != expected or len(actual) != len(observed):
        raise AliasRefusal('Imported alias token ownership is incomplete')
    changed = text
    for a, z, replacement in sorted(observed, reverse=True):
        changed = changed[:a] + replacement + changed[z:]
    return changed, sorted(observed)


def check_generated_import_names(declarations, imported):
    """Require each emitted C-name to occur only in its one import declaration."""
    for name, expected in imported.items():
        uses = [text for text in declarations
                if re.search(r'\b' + re.escape(name) + r'\b', _masked(text))]
        if uses != [expected]:
            raise AliasRefusal('Generated declaration owns imported replacement name: ' + name)
