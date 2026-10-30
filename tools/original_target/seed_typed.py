"""Adapt typed Ghidra scratch seeds to existing shared C++ declarations.

The generated method adapter has no fields; its body uses a pointer to the real
shared class. Raw virtual dispatch remains an explicit Ghidra ABI hypothesis.
No class layout, member, or reference address is manufactured by this adapter.
"""
from pathlib import Path
import re
from seed_shared_types import SharedTypes, code_view, type_name, _CLASS, _closing


class TypedRefusal(ValueError):
    pass


def exported_owner(params, param_parts):
    if not params:
        return None
    kind, name = param_parts(params[0])
    if kind.count('*') != 1:
        return None
    candidate = type_name(kind)
    return candidate if candidate not in ('void','int','uint','undefined4','char','byte') else None


def placeholder_types(passes, entry=None):
    """Read only the chosen export's explicit type stubs, never older layouts.

    A full or conflicting declaration wins over a one-byte placeholder. This
    avoids applying old byte scaling after a newer pass supplies a real type.
    """
    directories=list(map(Path,passes))
    if entry is not None:
        directories=[p for p in directories if (p/'decompiled'/('%08x.c'%entry)).is_file()][:1]
    for directory in directories[:1]:
        files=[directory/n for n in ('types_body.h','types.h') if (directory/n).is_file()]
        if not files:
            files=[directory.parent/n for n in ('types_body.h','types.h') if (directory.parent/n).is_file()]
        declarations={}
        for path in files:
            view=code_view(path.read_text(encoding='utf-8',errors='replace'))
            for match in _CLASS.finditer(view):
                opening=match.end()-1
                body=view[opening+1:_closing(view,opening)]
                stub=bool(re.fullmatch(r'\s*char\s+unknown_0\s*;\s*',body)) and not match[3]
                declarations.setdefault(match[2],set()).add(stub)
        return {name for name,forms in declarations.items() if forms=={True}}
    return set()


def scalar_preamble(shared):
    text=(Path(shared)/'ghidra_types.hpp').read_text()
    widths=text[text.index('typedef unsigned char undefined'):text.index('// Win32 names')]
    macros=text[text.index('#define CONCAT11'):text.rindex('#endif')]
    return widths+'\n'+macros


def scalar_conflict_aliases(source, variables):
    """Keep Ghidra's conflict spelling for its exported fixed-width integers.

    These aliases carry storage width/signedness only, like ghidra_types.hpp.
    Unknown names and names already owned by a declaration stay unresolved.
    """
    view=code_view(source);owned=_declared_types(source)|set(variables);lines=[]
    for base in ('uchar','ushort','uint','ulong','sbyte','longlong','ulonglong'):
        alias=base+'_conflict'
        if alias in owned:continue
        use=re.search(r'\b'+alias+r'\s+\**\s*[A-Za-z_]\w*\s*[,;)\[=]',view)
        cast=re.search(r'\(\s*'+alias+r'(?:\s*\*)*\s*\)\s*[A-Za-z_0-9(&*~-]',view)
        if use or cast:lines.append('typedef '+base+' '+alias+';')
    return '\n'.join(lines)


def _closure(shared, headers):
    result={}
    pending=list(headers)
    while pending:
        header=pending.pop()
        if header in result or not header.startswith('shared/'):
            continue
        path=Path(shared)/header[len('shared/'):]
        if not path.is_file():
            continue
        text=path.read_text(encoding='utf-8')
        result[header]=text
        pending.extend(re.findall(r'^\s*#\s*include\s*"(shared/[^"]+)"',text,re.M))
    return result


def _declared_types(text):
    view=code_view(text)
    names=set(re.findall(r'\b(?:class|struct|union|enum)\s+(?:__declspec\([^)]*\)\s*)?(\w+)',view))
    names.update(re.findall(r'^\s*#\s*define\s+(\w+)',view,re.M))
    for match in re.finditer(r'\btypedef\s+([^;{}]+);',view):
        declaration=match[1]
        function=re.search(r'\(\s*(?:__\w+\s*)?\*\s*(\w+)\s*\)',declaration)
        if function:
            names.add(function[1])
        else:
            for part in declaration.split(','):
                words=re.findall(r'\b[A-Za-z_]\w*\b',part)
                if words:names.add(words[-1])
    return names


def _reuse_shared_records(source, entry, closure):
    complete=set()
    for text in closure.values():
        complete.update(m[2] for m in _CLASS.finditer(code_view(text)))
    namespace='namespace seed_%08x {'%entry
    first=source.index(namespace)+len(namespace)
    adapter='Owner_%08x::FUN_%08x'%(entry,entry)
    if adapter in source:
        last=source.index(adapter)
    else:
        definition=re.search(r'(?m)^[^\n;{}]*\bFUN_%08x\s*\([^;{}]*\)\s*\n\{'%entry,code_view(source))
        last=definition.start() if definition else len(source)
    prefix=source[first:last]
    view=code_view(prefix)
    spans=[]
    for match in _CLASS.finditer(view):
        if match[2] not in complete:continue
        end=_closing(view,match.end()-1)+1
        suffix=re.match(r'\s*;',view[end:])
        if suffix is not None:spans.append((match.start(),end+suffix.end()))
    # A complete SDK record can contain nested record declarations. Remove
    # only outer spans, and retain following typedefs against the shared type.
    outer=[]
    for start,end in sorted(spans,key=lambda x:(x[0],-x[1])):
        if not any(a<=start and end<=b for a,b in outer):outer.append((start,end))
    for start,end in reversed(outer):prefix=prefix[:start]+prefix[end:]
    return source[:first]+prefix+source[last:]


def null_void_views(body):
    """A Ghidra C void-pointer zero is a C++ null pointer constant.

    Keep nonzero addresses and values in comments/literals unchanged. The
    generated callee argument casts still supply their declared pointer type.
    """
    pattern=re.compile(r'\(\s*void\s*\*\s*\)\s*(?:0[xX]0+|0)[uUlL]*(?![\w.])')
    edits=[(m.start(),m.end()) for m in pattern.finditer(code_view(body))]
    for first,last in reversed(edits):body=body[:first]+'0'+body[last:]
    return body


def pointer_member_assignments(body,variables,schema):
    """Spell the C pointer conversion required by a real shared field type.

    Only simple public pointer-member stores are covered. Arrays, aggregate
    assignments, unknown template parameters and unbalanced expressions remain
    unresolved; no guessed member, layout or access-control change is made.
    """
    pattern=re.compile(r'(?m)^([ \t]*)([A-Za-z_]\w*(?:(?:->|\.)[A-Za-z_]\w*)+)[ \t]*=[ \t]*(?!=)([^;\n]+);')
    view=code_view(body);edits=[]
    for match in pattern.finditer(view):
        root=re.match(r'\w+',match[2])[0];kind=variables.get(root);field=None
        if kind is None:continue
        for part in re.finditer(r'(?:->|\.)([A-Za-z_]\w*)',match[2]):
            field=schema.field(kind,part[1])
            if field is None or field.access!='public' or field.dimensions:
                field=None;break
            kind=field.kind
        if field is None or '*' not in re.sub(r'<.*>','',kind) or re.search(r'\b(?:T|U|K|V)\b',kind):continue
        rhs=match[3];stack=[];balanced=True
        for char in rhs:
            if char in '([':stack.append(char)
            elif char in ')]':
                if not stack or stack.pop()!={')':'(',']':'['}[char]:balanced=False;break
            elif char in '{}' or char==',' and not stack:balanced=False;break
        if not balanced or stack:continue
        kind=re.sub(r'\bmutable\s+','',kind).strip()
        original=body[match.start(3):match.end(3)]
        if original.lstrip().startswith('('+kind+')'):continue
        edits.append((match.start(3),match.end(3),'('+kind+')('+original+')'))
    for first,last,text in reversed(edits):body=body[:first]+text+body[last:]
    return body


def _vtable_reads(body):
    pattern=re.compile(r'\b([A-Za-z_]\w*(?:(?:->|\.)[A-Za-z_]\w*)*)(->|\.)vftable_([0-9a-f]+)\b')
    edits=[]
    for match in pattern.finditer(code_view(body)):
        receiver=body[match.start(1):match.end(1)]
        address=receiver if match[2]=='->' else '&('+receiver+')'
        offset=int(match[3],16)
        edits.append((match.start(),match.end(),'(*(code ***)((char *)('+address+') + 0x%x))'%offset))
    for start,end,text in reversed(edits):body=body[:start]+text+body[end:]
    return body


def _vtable_aliases(body):
    assignments=re.compile(r'(?m)^[ \t]*(\w+)\s*=\s*([^;\n]+);')
    aliases={}
    for match in assignments.finditer(body):
        if 'code ***' not in match[2]:continue
        name=match[1]
        declaration=re.search(r'\bvoid\s*(\*+)\s*'+re.escape(name)+r'\s*;',body)
        if declaration and len(declaration[1])>=2:aliases[name]='code '+declaration[1]
    for name,kind in aliases.items():
        body=re.sub(r'\bvoid\s*\*+\s*'+re.escape(name)+r'\s*;',kind+' '+name+';',body)
    def store(match):
        kind=aliases.get(match[1])
        if kind is None or match[2].lstrip().startswith('('+kind+')'):return match[0]
        return match[1]+' = ('+kind+')('+match[2]+');'
    return assignments.sub(store,body)


def byte_pointer_arithmetic(body, variables, stubs):
    edits=[]
    view=code_view(body)
    for name,kind in variables.items():
        if kind.count('*')!=1 or type_name(kind) not in stubs:continue
        pattern=re.compile(r'\b'+re.escape(name)+r'\b(?=\s*(?:\+(?!\+)|-(?![-=>])))')
        for match in pattern.finditer(view):edits.append((match.start(),match.end(),'((char *)'+name+')'))
    for start,end,text in sorted(edits,reverse=True):body=body[:start]+text+body[end:]
    return body


_PRIORITY={'shared/gscreen.hpp':-10,'shared/map.hpp':-9,'shared/display.hpp':-8,
           'shared/radar.hpp':-7,'shared/power.hpp':-6,'shared/sidebar.hpp':-5,
           'shared/tab.hpp':-4,'shared/scroll.hpp':-3,'shared/building_class.hpp':-2,'shared/cell.hpp':-1}


def adapt_seed(source, original, entry, owner, schema, variables, recast, stubs=(), static_method=None):
    adapter='Owner_%08x'%entry
    function='FUN_%08x'%entry
    definition=source.find(adapter+'::'+function)
    if definition<0:raise TypedRefusal('Typed member has no representable method adapter')
    start=source.index('{',definition)
    namespace_end=source.rindex('}  // namespace')
    end=source.rfind('}',0,namespace_end)+1
    body=source[start:end]
    notes=[]
    runtime=owner
    signature=None
    initializer='this'
    if static_method is not None:
        # A forced Ghidra thiscall may actually be a static function whose sole
        # fastcall parameter is an object reference (e.g. Read_INI).
        if '__fastcall' not in static_method.declaration or ',' in static_method.parameters:
            raise TypedRefusal('Static shared signature contradicts the supplied thiscall; original ABI needs review')
        parameter=static_method.parameters.split('=')[0].strip()
        part=re.fullmatch(r'(.+?[&*])\s*(\w+)',parameter)
        if part is None or type_name(part[1]) not in schema.records:
            raise TypedRefusal('Static input has no evidenced class receiver')
        runtime=type_name(part[1])
        initializer='&'+part[2] if '&' in part[1] else part[2]
        signature=re.sub(r'^static\s+','',static_method.declaration).rstrip(';')
        signature=re.sub(r'\b'+re.escape(static_method.name)+r'\b',function,signature,count=1)
        notes.append('Ghidra thiscall corrected to the shared static fastcall signature')
    variables=dict(variables,this=runtime+' *')
    body=_vtable_reads(body)
    body=_vtable_aliases(body)
    body,field_notes=schema.rewrite_members(body,variables)
    notes.extend(field_notes)
    body=null_void_views(body)
    body=pointer_member_assignments(body,variables,schema)
    body=byte_pointer_arithmetic(body,variables,stubs)
    receiver='typed_this'
    while re.search(r'\b'+receiver+r'\b',code_view(body)):receiver+='_'
    view=code_view(body)
    edits=[(m.start(),m.end(),receiver) for m in re.finditer(r'\bthis\b',view)]
    for first,last,text in reversed(edits):body=body[:first]+text+body[last:]
    if edits:
        body=body[:1]+'\n    '+runtime+' *'+receiver+' = '+initializer+';'+body[1:]
    body=recast(body)
    source=source[:start]+body+source[end:]
    if signature is None:
        source=source.replace('struct '+adapter+' {','struct '+adapter+' : public ::'+owner+' {',1)
    else:
        source=re.sub(r'(?m)^struct '+adapter+r'\s*\{[^\n]+\};\s*\n','',source,count=1)
        definition=source.index(adapter+'::'+function)
        first=source.rfind('\n',0,definition)+1
        brace=source.index('{',definition)
        source=source[:first]+signature+'\n'+source[brace:]
    words=set(re.findall(r'\b[A-Za-z_]\w*\b',original))
    words.update(re.findall(r'^(?:class|struct) (\w+);',source,re.M))
    provided=set(schema.records).intersection(words)|{owner,runtime}
    for name in provided:
        source=re.sub(r'\b(?:class|struct)\s+'+re.escape(name)+r'\s*;', '', source)
    headers={schema.records[name].header for name in provided if name in schema.records}
    if (schema.directory/'com_persist.hpp').is_file():headers.add('shared/com_persist.hpp')
    closure=_closure(schema.directory,headers)
    platform_names=_declared_types('\n'.join(closure.values()))
    source=_reuse_shared_records(source,entry,closure)
    aliases=[('HDC','void *'),('LPSTR','char *')]
    if 'IID' in set(re.findall(r'\b\w+\b',code_view(source))) and 'GUID' in platform_names:
        aliases.append(('IID','GUID'))  # the canonical ghidra_types.hpp SDK alias
    bridge='\n'.join('typedef '+kind+' '+name+';' for name,kind in aliases if name not in platform_names)
    bridge+='\n'+scalar_conflict_aliases(source,variables)
    head='\n'.join(['#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS','#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS']+
                   ['#include "'+header+'"' for header in sorted(headers,key=lambda h:(_PRIORITY.get(h,0),h))])
    source=source.replace('#include "shared/ghidra_types.hpp"',head,1)
    namespace='namespace seed_%08x {'%entry
    source=source.replace(namespace,namespace+'\n'+scalar_preamble(schema.directory)+'\n'+bridge,1)
    source='// Typed-layout scratch seed: existing shared declarations; raw virtual ABI remains a hypothesis.\n'+source
    if notes:source='\n'.join('// '+note for note in notes)+'\n'+source
    return source,notes
