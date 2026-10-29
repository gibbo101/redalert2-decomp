"""Connect explicit existing import identities to qualified C source models."""
import re
from seed_import_aliases import AliasRefusal, _masked, direct_import_aliases


def recorded_direct_imports(text, facts, parse_header, stack_bytes, reserved_names=()):
    """Return text and per-function import models; unsupported syntax is unchanged.

    seed_declaration is separate from the raw Ghidra import signature. Neither
    the export decoration nor argument expressions establish that prototype.
    """
    identifiers = set(re.findall(r'\b[A-Za-z_]\w*\b', _masked(text)))
    modeled = [fact for fact in facts.values() if fact.get('seed_declaration')]
    if not any(fact['seed_declaration'].get('source_alias') in identifiers for fact in modeled):
        return text, {}
    aliases, declarations = {}, {}
    try:
        for fact in modeled:
            model = fact['seed_declaration']
            source_alias, name = model['source_alias'], model['name']
            if source_alias in aliases or name in declarations:
                raise AliasRefusal('Ambiguous recorded imported alias')
            if not fact.get('dll') or not re.fullmatch(r'[0-9a-fA-F]{8}', fact.get('iat', '')):
                raise AliasRefusal('Recorded imported alias lacks an exact identity')
            if not model.get('model_source'):
                raise AliasRefusal('Recorded imported alias lacks prototype provenance')
            result, conv, parsed_name, params, span = parse_header(model['signature'])
            if (conv != '__stdcall' or model.get('convention') != conv or
                    parsed_name != name or '...' in params or
                    model.get('parameters') != len(params)):
                raise AliasRefusal('Recorded imported alias has an inconsistent prototype')
            width = sum(stack_bytes(param) for param in params)
            if (fact['name'] != '_' + name + '@' + str(width) or
                    source_alias != '_' + name + '_' + str(width)):
                raise AliasRefusal('Recorded imported alias disagrees with formal stack width')
            aliases[source_alias] = name
            declarations[name] = dict(name=name, dll=fact['dll'], iat=fact['iat'],
                convention=conv, parameters=len(params), signature=model['signature'])
        changed, edits = direct_import_aliases(text, aliases, reserved_names)
    except (AliasRefusal, KeyError, ValueError, TypeError):
        # A refused optional repair preserves the pre-existing seed byte-for-byte.
        return text, {}
    used = {name for first, last, name in edits}
    return changed, {name: declarations[name] for name in used}
