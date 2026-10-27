#!/usr/bin/env python3
"""Render reviewed connected-family models to NEW ignored candidates only."""
import argparse
import hashlib
import catalog_io
import json
from pathlib import Path
from source_paths import source_path

def digest(data):
    return hashlib.sha256(data).hexdigest()

def require(value, reason):
    if not value:
        raise ValueError(reason)

def render_family(repository, plan_path, template_dir, executable, evidence_paths, output):
    repository=Path(repository).resolve();output=Path(output).resolve()
    require(any(output.is_relative_to(repository/name) and output != repository/name
                for name in ('private','build')), 'Ignored private/build child output required')
    require(not output.exists(), 'New output required; no overwrites')
    plan=json.loads(Path(plan_path).read_bytes());require(plan['schema'] in
        ('ra2-readable-message-gadget-plan-v1','ra2-readable-connected-family-plan-v1'),'Wrong schema')
    original=Path(executable).read_bytes();require(len(original)==plan['target']['size'] and digest(original)==plan['target']['sha256'],'Wrong original target')
    require(set(evidence_paths)==set(plan['evidence_sha256']),'Evidence binding names differ')
    evidence={}
    for name, expected in plan['evidence_sha256'].items():
        data=Path(evidence_paths[name]).read_bytes();require(digest(data)==expected,'Evidence drift: '+name);evidence[name]=data
    facts={r['entry']:r for r in json.loads(evidence['original_facts'])}
    catalog=catalog_io.load(catalog_io.locate(repository), references=False);require(catalog['target']==plan['target'],'Canonical target differs')
    current={r['entry']:r for r in catalog['regions']};observed={};sources=[]
    require(len(current)==len(catalog['regions']) and plan['regions'] and
            len({r['entry'] for r in plan['regions']})==len(plan['regions']), 'Empty/duplicate mappings')
    header_pins=plan['shared_headers'] if 'shared_headers' in plan else [plan['shared_header']]
    require(header_pins and len({h['path'] for h in header_pins})==len(header_pins), 'Empty/duplicate shared headers')
    headers=[]
    for pin in header_pins:
        path=Path(pin['path'])
        require(not path.is_absolute() and path.as_posix()==pin['path'] and
                '..' not in path.parts and path.parts[:2]==('src','shared'), 'Unsafe shared header path')
        header_path=repository/path
        require(header_path.resolve().is_relative_to(repository/'src/shared'),'Shared header escapes tree')
        header=header_path.read_bytes();require(digest(header)==pin['sha256'],'Shared header drift')
        require(sum(h==pin for h in catalog.get('headers',[]))==1,'Header not uniquely catalogued')
        headers.append((pin,header_path,header))
    for row in plan['regions']:
        fact=facts[row['entry']]
        for key in ('body_bytes','body_sha256','region_bytes','region_sha256'):
            require(row[key]==fact[key],'Original fact differs: '+key)
        path=current[row['entry']]['source']
        canonical=source_path(repository,path)
        require(Path(row['template']).name==row['template'] and row['template'].endswith('.cpp.in'), 'Unsafe template path')
        data=(Path(template_dir)/row['template']).read_bytes();require(digest(data)==row['source_sha256'],'Template drift')
        observed[path]=digest(canonical.read_bytes())
        sources.append((dict(row,source=path),data))
    # Validation completes before output creation; canonical sources are never templates.
    output.mkdir(parents=True)
    for pin,_,header in headers:
        p=output/pin['path'];p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(header)
    for row,data in sources:
        p=output/row['source'];p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(data)
    require(all(digest((repository/p).read_bytes())==h for p,h in observed.items()),'Canonical source changed during generation')
    require(all(path.read_bytes()==data for _,path,data in headers),'Canonical header changed during generation')
    receipt={'schema':'ra2-readable-message-gadget-render-v1','regions':len(sources),'body_bytes':sum(r['body_bytes'] for r,_ in sources),'padding_bytes':sum(r['region_bytes']-r['body_bytes'] for r,_ in sources),'observed_canonical_sha256':observed,'limits':'Candidate generation only; manual canonical edits preserved, not used as templates; no compiler or fidelity claim.'}
    (output/'generation-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n')
    return receipt

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--repository',type=Path,required=True);p.add_argument('--plan',type=Path,required=True);p.add_argument('--templates',type=Path,required=True);p.add_argument('--executable',type=Path,required=True);p.add_argument('--evidence',action='append',default=[],metavar='NAME=PATH');p.add_argument('--output',type=Path,required=True);a=p.parse_args();print(json.dumps(render_family(a.repository,a.plan,a.templates,a.executable,dict(v.split('=',1) for v in a.evidence),a.output),indent=2))
if __name__=='__main__':main()
