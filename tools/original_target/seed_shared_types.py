"""Read existing shared class declarations for typed Ghidra scratch seeds.

This index supplies names and access rules, never guessed fields or byte offsets.
Incomplete/ambiguous declarations are left unresolved. It does not change headers.
"""
from dataclasses import dataclass
from pathlib import Path
import re

_TOKEN = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|//[^\n]*|/\*[\s\S]*?\*/')
_CLASS = re.compile(r'\b(class|struct)\s+(?:__declspec\s*\([^)]*\)\s*)?(\w+)\s*(?::([^;{}]+))?\s*\{')
_FIELD = re.compile(r'^\s*(.*?)\b([A-Za-z_]\w*)\s*((?:\[[^;\]]*\])*)\s*;\s*$')
_CHAIN = re.compile(r'\b([A-Za-z_]\w*(?:\[[^\[\]\n]*\])*)((?:(?:->|\.)[A-Za-z_]\w*(?:\[[^\[\]\n]*\])*)+)')


def code_view(text):
    return _TOKEN.sub(lambda m: ''.join('\n' if c == '\n' else ' ' for c in m[0]), text)


def type_name(kind):
    kind = re.sub(r'\b(?:class|struct|const|volatile|mutable)\b', '', kind).strip()
    return re.split(r'[<*&\[]', kind, 1)[0].strip().split('::')[-1]


def _closing(view, opening):
    depth = 0
    for position in range(opening, len(view)):
        depth += view[position] == '{'
        depth -= view[position] == '}'
        if depth == 0:
            return position
    raise ValueError('Unbalanced shared class declaration')


def _member_statements(body, access):
    depth = 0
    current = ''
    for char in body:
        if char == '{':
            depth += 1
            current = ''
        elif char == '}':
            depth -= 1
            current = ''
        elif depth == 0:
            if char == ':' and current.strip() in ('public', 'private', 'protected'):
                access = current.strip()
                current = ''
            elif char == ';':
                if current.strip():
                    yield current.strip(), access
                current = ''
            else:
                current += char


@dataclass(frozen=True)
class Field:
    name: str
    kind: str
    access: str
    dimensions: str = ''


@dataclass(frozen=True)
class Method:
    name: str
    declaration: str
    entry: int
    static: bool
    parameters: str


@dataclass
class Record:
    name: str
    header: str
    bases: tuple
    fields: dict
    methods: tuple = ()
    polymorphic: bool = False


def _methods(original, view):
    depth = 0
    preceding = []
    for raw, visible in zip(original.splitlines(), view.splitlines()):
        if depth == 0:
            if raw.strip().startswith('//'):
                preceding.append(raw)
            elif not raw.strip():
                preceding = []
            elif '(' in visible:
                prototype = visible.split('{',1)[0].strip()
                method = re.search(r'(~?[A-Za-z_]\w*)\s*\((.*)\)', prototype)
                comment = raw.split('//',1)[1] if '//' in raw else '\n'.join(preceding)
                addresses = re.findall(r'\b0x([0-9a-fA-F]{8})\b', comment)
                if method and len(set(addresses)) == 1:
                    yield Method(method[1], prototype, int(addresses[0],16),
                                 bool(re.search(r'\bstatic\b',prototype)),method[2])
                preceding = []
            else:
                preceding = []
        depth += visible.count('{') - visible.count('}')


class SharedTypes:
    def __init__(self, directory):
        self.directory = Path(directory)
        choices = {}
        for path in sorted(self.directory.glob('*.hpp')):
            text = path.read_text(encoding='utf-8')
            view = re.sub(r"^[ \t]*#[^\n]*", lambda m: " " * len(m[0]), code_view(text), flags=re.M)
            for match in _CLASS.finditer(view):
                opening = match.end() - 1
                closing = _closing(view, opening)
                body = view[opening + 1:closing]
                access = 'public' if match[1] == 'struct' else 'private'
                fields = {}
                for statement, access in _member_statements(body, access):
                    field = _FIELD.match(statement + ';')
                    if field and '(' not in statement and not re.match(r'^\s*(?:typedef|static|friend|using)\b', statement):
                        kind = field[1].strip()
                        if kind:
                            fields[field[2]] = Field(field[2], kind, access, field[3])
                bases = tuple(type_name(re.sub(r'\b(?:public|protected|private|virtual)\b', '', b))
                              for b in (match[3] or '').split(',') if b.strip())
                record = Record(match[2], 'shared/' + path.name, bases, fields, tuple(_methods(text[opening+1:closing], body)), bool(re.search(r'\bvirtual\b', body)))
                choices.setdefault(record.name, []).append(record)
        self.records = {}
        self.ambiguous = set()
        for name, records in choices.items():
            # Full declarations have more fields than intentional light views/stubs.
            largest = max(len(r.fields) for r in records)
            best = [r for r in records if len(r.fields) == largest]
            stem = re.sub(r'Class$', '', name).replace('_','').lower()
            canonical = [r for r in best if re.sub(r'_class$', '', Path(r.header).stem).replace('_','').lower() == stem]
            if canonical:
                best = canonical
            if len(best) == 1:
                self.records[name] = best[0]
            elif all((r.bases, r.fields) == (best[0].bases, best[0].fields) for r in best):
                self.records[name] = min(best, key=lambda r: (len(r.header), r.header))
            else:
                self.ambiguous.add(name)

    def method_at(self, entry):
        choices = [(record, method) for record in self.records.values() for method in record.methods
                   if method.entry == entry]
        return choices[0] if len(choices) == 1 else None

    def constructor_owner(self, entry):
        owners = {record.name for record in self.records.values() for method in record.methods
                  if method.entry == entry and method.name == record.name}
        return next(iter(owners)) if len(owners) == 1 else None

    def field(self, owner, name, visited=()):
        owner = type_name(owner)
        if owner in visited or owner not in self.records:
            return None
        record = self.records[owner]
        if name in record.fields:
            return record.fields[name]
        inherited = [self.field(base, name, visited + (owner,)) for base in record.bases]
        inherited = [f for f in inherited if f is not None]
        return inherited[0] if len(inherited) == 1 else None

    def field_names(self, owner, visited=()):
        owner = type_name(owner)
        if owner in visited or owner not in self.records:
            return set()
        record = self.records[owner]
        names = set(record.fields)
        for base in record.bases:
            names.update(self.field_names(base, visited + (owner,)))
        return names

    def flat_path(self, owner, flat, visited=()):
        owner = type_name(owner)
        if (owner, flat) in visited:
            return None
        direct = self.field(owner, flat)
        if direct:
            return (direct,)
        matches = []
        for name in sorted(self.field_names(owner), key=lambda n: (-len(n), n)):
            if not flat.startswith(name + '_'):
                continue
            field = self.field(owner, name)
            if not field or '*' in re.sub(r'<.*>', '', field.kind) or field.dimensions:
                continue
            rest = self.flat_path(field.kind, flat[len(name) + 1:], visited + ((owner, flat),))
            if rest:
                matches.append((field,) + rest)
        return matches[0] if len(matches) == 1 else None

    def vector_data_view(self, expression, separator, parent_kind, field):
        # This is the fixed original-target x86 MSVC layout, not a host ABI:
        # a root polymorphic VectorClass stores its first pointer after vptr+4.
        # Validate that the real declaration still has exactly that shape.
        root = self.records.get('VectorClass')
        if not root or root.bases or not root.polymorphic or next(iter(root.fields),None) != 'Vector':
            return None
        kind = field.kind
        if re.search(r'\bT\b', kind):
            argument = re.search(r'<(.*)>', parent_kind)
            if not argument:
                return None
            kind = re.sub(r'\bT\b', lambda m: argument[1], kind)
        address = expression if separator == '->' else '&(' + expression + ')'
        return '(*(' + kind + ' *)((char *)' + address + ' + 4))'

    def rewrite_members(self, body, variables):
        """Resolve flat member names; protected vector reads use real public APIs.

        Writes/address-taken protected fields remain unresolved, rather than
        exposing access controls or pretending an accessor returns a reference.
        """
        view = code_view(body)
        edits = []
        notes = []
        for match in _CHAIN.finditer(view):
            root = re.match(r'[A-Za-z_]\w*',match[1])[0]
            kind = variables.get(root)
            if not kind:
                continue
            expression = body[match.start(1):match.end(1)]
            changed = False
            parts = list(re.finditer(r'(->|\.)(\w+)((?:\[[^\[\]\n]*\])*)', match[2]))
            valid = True
            for number, part in enumerate(parts):
                path = self.flat_path(kind, part[2])
                if path is None:
                    valid = False
                    break
                parent_kind = kind
                for index, field in enumerate(path):
                    separator = part[1] if index == 0 else '.'
                    if field.access != 'public':
                        suffix = view[match.end():].lstrip()
                        address = view[:match.start()].rstrip().endswith('&')
                        write = re.match(r'(?:=(?!=)|\+\+|--|[+*/%-]=)', suffix)
                        vector = type_name(parent_kind) in ('VectorClass', 'DynamicVectorClass', 'TypeList')
                        if address or write or not vector or index != len(path)-1 or number != len(parts)-1:
                            valid = False
                            notes.append('Unresolved protected member: ' + expression + separator + field.name)
                            break
                        if field.name in ('ActiveCount', 'VectorMax'):
                            expression += separator + ('Count()' if field.name == 'ActiveCount' else 'Length()')
                        elif field.name == 'Vector':
                            value = self.vector_data_view(expression, separator, parent_kind, field)
                            if value is None:
                                valid = False
                                notes.append('Unresolved protected Vector storage: ' + expression)
                                break
                            expression = value
                        else:
                            valid = False
                            break
                    else:
                        expression += separator + field.name
                    parent_kind = field.kind
                if not valid:
                    break
                expression += body[match.start(2)+part.start(3):match.start(2)+part.end(3)]
                kind = path[-1].kind
                changed = changed or expression != match[0]
            if valid and changed and expression != match[0]:
                edits.append((match.start(), match.end(), expression))
        for start, end, replacement in reversed(edits):
            body = body[:start] + replacement + body[end:]
        return body, notes
