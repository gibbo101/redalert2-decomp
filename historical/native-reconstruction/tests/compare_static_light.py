#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare stock static-source construction, immediate updates and converter decisions."""
import argparse,math,random,subprocess
from pathlib import Path
from static_light_evidence import prepare,identities,save,replay,run_native
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--exe',type=Path,required=True);p.add_argument('--data-dir',type=Path,default=Path('private/game'))
p.add_argument('--native',type=Path,default=Path('build/native/static-light-vectors'))
p.add_argument('--render-data',type=Path,default=Path('private/derived/render-data.bin'))
p.add_argument('--report',type=Path);p.add_argument('--expectations',type=Path)
p.add_argument('--native-data-exe',type=Path,help='Explicit retained disc identity; required for patched research')
p.add_argument('--exporter',type=Path,default=Path('build/native/map-light-vectors'))
a=p.parse_args();engine_digest,engine_profile,native_data,work=prepare(a)
if a.expectations:
    replay(a,engine_digest,engine_profile,native_data,work)
    raise SystemExit(0)
from original_static_light import StaticLightOracle
o=StaticLightOracle(a.exe,allow_patched=True);rng=random.Random(0x52413131);commands=[];expected=[];labels=[];groups={}
def add(group,command,result):
    commands.append(' '.join(map(str,command)));expected.append(list(map(str,result)));labels.append(group);groups[group]=groups.get(group,0)+1
values=[0.,1.,-1.,.2,.05,.01,-.15,.6,10.,-10.]
for n in range(-128,129):
    v=n/1000;values.extend([math.nextafter(v,-math.inf),v,math.nextafter(v,math.inf)] if v else [v])
for v in values:
    raw=[v,-v,.6,.01];add('type_numeric_blocks',['Q',5000,*raw],[5000,*[o.type_value(x) for x in raw]])
tints=[[1000]*3,[0]*3,[1000,1000,1001],[1000,1000,0],[1000,1000,32],[1000,1000,48],[1000,0,0],[-1,1001,2000]]
tints.extend([[rng.randrange(-500,2001) for _ in range(3)] for _ in range(500)])
for detail in range(3):
    for tint in tints:add('complete_factory_decisions',['K',detail,*tint],o.factory(tint,detail))
for i in range(128):
    type_values=[rng.choice([1,128,256,1000,5000,17000]),rng.randrange(-500,501),*[rng.randrange(-1000,2001) for _ in range(3)]]
    position=[rng.randrange(-4096,131072),rng.randrange(-4096,131072),rng.randrange(-4096,4097)]
    add('complete_source_constructors',['C',*type_values,*position],o.construct(type_values,position))
for i in range(128):
    cx,cy=rng.choice([(33,86),(1,1),(511,511)]);position=[cx*256+rng.randrange(-128,257),cy*256+rng.randrange(-128,257),rng.randrange(-4096,4097)]
    cells=[(x,y,(x*3+y*7+i)%32) for y in range(max(0,cy-5),min(512,cy+6)) for x in range(max(0,cx-5),min(512,cx+6)) if (x+y+i)%7]
    rng.shuffle(cells)
    type_values=[rng.choice([1,128,255,256,257,512,1000,2048,5000]),rng.randrange(-500,501),*[rng.randrange(-200,501) for _ in range(3)]]
    settings=[rng.randrange(201),*[rng.randrange(201) for _ in range(3)],rng.randrange(-200,201),rng.randrange(-32,65)]
    initial,active,detail,enabled=[(False,True,2,True),(True,False,2,True),(True,True,2,True),(False,False,2,True),(False,True,0,True),(True,False,1,True),(False,True,2,False)][i%7]
    command=['A',*type_values,*position,*settings,int(initial),int(active),detail,int(enabled),len(cells),*[v for c in cells for v in c]]
    add('complete_immediate_updates',command,o.update(type_values,position,settings,cells,initial,active,detail,enabled))
# Reuse the existing protected read-only asset exporter; no original map is changed.
assets=a.assets
def section(text,name):
    found=False;result={}
    for line in text.splitlines():
        line=line.split(';',1)[0].strip()
        if line.startswith('['):found=line.lower()=='['+name.lower()+']'
        elif found and '=' in line:
            k,v=line.split('=',1);result[k.strip().lower()]=v.strip()
    return result
rules=section((assets/'rules.ini').read_text(),'INGALITE');radius=int(rules['lightvisibility'])
raw=[float(rules[k]) for k in ['lightintensity','lightredtint','lightgreentint','lightbluetint']]
stock=[radius,*[o.type_value(v) for v in raw]]
add('owned_stock_type',['Q',radius,*raw],stock)
lighting=section((assets/'mp03t4.map').read_text(),'Lighting')
settings=o.quantize([float(lighting[k]) for k in ['ambient','red','green','blue','ground','level']])
rows=subprocess.check_output([str(a.exporter),'--cells',str(assets/'mp03t4.map')],text=True)
cells=[tuple(map(int,row.split())) for row in rows.splitlines()]
position=[35*256+128,86*256+128,4*104]
for detail in range(3):
    command=['P',*stock,*position,*settings,0,1,detail,1,len(cells),*[v for c in cells for v in c]]
    add('owned_building_creation_blocks',command,o.building(stock,position,settings,cells,detail))
    zero=[radius,0,*stock[2:]]
    command=['P',*zero,*position,*settings,0,1,detail,1,len(cells),*[v for c in cells for v in c]]
    add('zero_intensity_building_blocks',command,o.building(zero,position,settings,cells,detail))
for initial,active in [(False,True),(True,False),(True,True)]:
    command=['A',*stock,*position,*settings,int(initial),int(active),2,1,len(cells),*[v for c in cells for v in c]]
    add('owned_complete_map_updates',command,o.update(stock,position,settings,cells,initial,active,2,True))
# Deliberate translation-cache regression: conversion after complete sqrt and
# source calls must retain the exact original decimal and bias results.
for v in [.2,.05,.01,-.15,.6]:add('numeric_after_source_calls',['Q',5000,v,v,v,v],[5000,*[o.type_value(v) for _ in range(4)]])
report={**identities(a,engine_digest,engine_profile,native_data),'groups':groups,'seed':0x52413131,
        'stock_ingalite_integers':stock,'stock_position':position,'fixture_services':o.services,
        'flat_height_fixture_calls':o.getter_calls,'original_instructions_modified':False,
        'audited_callable_roots':o.audit_calls,'audited_blocks':o.audit_blocks,
        'supplied_allocation_calls':o.services.get(hex(o.va(0x76d5a7)),0),
        'scope':'Complete source constructor/immediate activation/deactivation, actual cell calculation/installation and terrain converter decisions. Building block executes actual 1x1 coordinate getter. Bounded caller/input/write audits exclude ordered native-original writes, full actor arenas, original INI parsing, deferred mode-1, house/source/converter lifetime, redraw implementation and frame parity.'}
actual=run_native(a,commands)
if len(actual)!=len(expected):raise AssertionError(f'Result count {len(actual)}/{len(expected)}')
for i,(label,x,y) in enumerate(zip(labels,actual,expected)):
    if x!=y:raise AssertionError(f'{i}: {label}: native {x[:10]}, original {y[:10]}')
report['cases']=len(commands)
report.update(identities(a,engine_digest,engine_profile,native_data))
save(a,work,commands,expected,labels,report)
print(f'{engine_profile}: {len(commands):,} original/native static-light results: PASS; {groups}')
