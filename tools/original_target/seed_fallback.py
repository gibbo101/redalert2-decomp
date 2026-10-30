"""One compile-triggered fallback to the frozen, untyped pass5 export.

This selects scratch source only. It changes no bounds, references, scoring or
acceptance rules. Both attempts and the selected source remain reviewable.
"""
from pathlib import Path
from inventory import Inventory,INVENTORY


def frozen_inventory():
    return Inventory([INVENTORY/'seeded-pass5',INVENTORY/'seeded-pass3',INVENTORY/'seeded-pass2',INVENTORY])


def export_pass(entry,inventory):
    name='%08x.c'%entry
    return next((Path(p) for p in inventory.passes if (Path(p)/'decompiled'/name).is_file()),None)


def has_fallback(entry,inventory,baseline=None):
    baseline=baseline or frozen_inventory()
    preferred=export_pass(entry,inventory);old=export_pass(entry,baseline)
    return preferred is not None and old is not None and preferred.resolve()!=old.resolve()


def fallback_source(entry,inventory,accepted,render,baseline=None):
    baseline=baseline or frozen_inventory()
    if not has_fallback(entry,inventory,baseline):return None
    return dict(source=render(entry,baseline,accepted,_typed=False),seed_mode='pass5',
                export_pass=export_pass(entry,baseline).as_posix())


def choose_seed(entry,inventory,accepted,render,compile_source,baseline=None):
    """Try the preferred seed, then pass5 only when generation/compilation fails.

    compile_source(text, mode) returns a dict with a Boolean compiled field and
    optional artifact paths. Compiler/IO infrastructure exceptions propagate;
    an unavailable compiler is not evidence against a typed seed.
    """
    baseline=baseline or frozen_inventory();attempts=[];preferred=None;old=None
    try:
        preferred=render(entry,inventory,accepted)
    except ValueError as error:
        attempts.append(dict(seed_mode='preferred',compiled=False,generation_error=str(error)))
    else:
        result=dict(compile_source(preferred,'preferred'))
        if type(result.get('compiled')) is not bool:raise ValueError('Compiler check did not return a Boolean result')
        result['seed_mode']='preferred';attempts.append(result)
        if result.get('compiled') is True:
            return dict(source=preferred,seed_mode='preferred',compiled=True,attempts=attempts)
    try:
        old=fallback_source(entry,inventory,accepted,render,baseline)
    except ValueError as error:
        attempts.append(dict(seed_mode='pass5',compiled=False,generation_error=str(error)))
    if old is not None:
        result=dict(compile_source(old['source'],'pass5'))
        if type(result.get('compiled')) is not bool:raise ValueError('Compiler check did not return a Boolean result')
        result.update(seed_mode='pass5',export_pass=old['export_pass']);attempts.append(result)
        if result.get('compiled') is True:
            return dict(source=old['source'],seed_mode='pass5',compiled=True,attempts=attempts)
    source=preferred if preferred is not None else old['source'] if old else None
    if source is None:raise ValueError('No compilable or reviewable seed: '+str(attempts))
    return dict(source=source,seed_mode='preferred' if preferred is not None else 'pass5',compiled=False,attempts=attempts)
