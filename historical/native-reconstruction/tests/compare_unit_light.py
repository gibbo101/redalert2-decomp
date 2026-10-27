#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare ordinary cell/house lighting inputs, full scheme tables and clipped planes."""
import argparse,hashlib,math,random,struct
from pathlib import Path
from unit_light_evidence import prepare, identities, save, replay, run_native

def words(values):return hashlib.sha256(struct.pack('<'+'H'*len(values),*values)).hexdigest()
def section(text,name):
    active=False;result={}
    for line in text.splitlines():
        line=line.split(';',1)[0].strip()
        if line.startswith('['):active=line.lower()=='['+name.lower()+']'
        elif active and '=' in line:
            k,v=line.split('=',1);result[k.strip().lower()]=v.strip()
    return result
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--exe',type=Path,required=True);p.add_argument('--data-dir',type=Path,default=Path('private/game'))
p.add_argument('--native',type=Path,default=Path('build/native/unit-light-vectors'))
p.add_argument('--render-data',type=Path,default=Path('private/derived/render-data.bin'));p.add_argument('--raster-data',type=Path,default=Path('private/derived/raster-data.bin'))
p.add_argument('--report',type=Path);p.add_argument('--expectations',type=Path)
p.add_argument('--native-data-exe',type=Path,help='Explicit retained disc identity; required for patched research')
p.add_argument('--exporter',type=Path,default=Path('build/native/map-light-vectors'))
p.add_argument('--staging-exporter',type=Path,default=Path('build/native/staging-vectors'))
a=p.parse_args();engine_digest,engine_profile,native_data,work=prepare(a)
if a.expectations:
    replay(a,engine_digest,engine_profile,native_data,work)
    raise SystemExit(0)
from original_unit_light import UnitLightOracle
from original_map_light import MapLightOracle
o=UnitLightOracle(a.exe,allow_patched=True);cells=MapLightOracle(a.exe,allow_patched=True);rng=random.Random(0x52413132)
assets=a.assets;commands=[];expected=[];labels=[];groups={}
def add(group,command,result):
    commands.append(' '.join(map(str,command)));expected.append(list(map(str,result)));labels.append(group);groups[group]=groups.get(group,0)+1
values=[0.,.2,-.2,.6,-.15,1.,10.,-10.]
for n in range(-256,257):
    v=n/1000;values.extend([math.nextafter(v,-math.inf),v,math.nextafter(v,math.inf)] if v else [v])
for value in values:add('extra_numeric_block',['Q',value],[o.extra(value)])
positions=[-1048576,-65537,-257,-256,-255,-1,0,1,255,256,257,65535,1048576]
positions.extend(rng.randrange(-1048576,1048577) for _ in range(243))
for x in positions:
    y=rng.choice(positions);add('actor_cell_coordinates',['X',x,y],o.coordinates(x,y))
for ambient in [-32768,-501,-500,-1,0,1,1000,1300,1499,1500,1501,1800,1999,2000,32767]:
    for extra in [-2147483648,-10000,-200,0,200,10000,2147483647]:
        for flags,predicate,effects in [(0,False,0),(0x10000,False,0),(0x10000,True,0),(0,False,2),(0x10000,False,2),(0x10000,True,3)]:
            add('ordinary_brightness_effects',['B',ambient,extra,flags,int(predicate),effects],o.brightness(ambient,extra,flags,predicate,effects))
for i in range(512):
    n=1+i%19;ids=list(range(n));rng.shuffle(ids);index=rng.randrange(n)
    add('house_converter_selection',['H',index,n,*ids],o.selection(index,ids))
rules=(assets/'rules.ini').read_text();colors=section(rules,'Colors');extra_raw=float(section(rules,'AudioVisual')['extraunitlight']);extra=o.extra(extra_raw)
add('owned_extra_unit_light',['Q',extra_raw],[extra])
unit=[x<<2 for x in (assets/'unittem.pal').read_bytes()];theater=[x<<2 for x in (assets/'temperat.pal').read_bytes()]
palettes={}
for name,text in colors.items():
    color=list(map(int,text.split(',')));table,mask,tint=o.scheme(color,unit,theater)
    assert mask==[int(not 240<=i<255) for i in range(256)] and tint==[1000]*3
    palettes[name]=table
    add('complete_owned_house_converters',['P',assets/'unittem.pal',*color],[words(table)])
# Every alpha input through the actual original blitter, including 2000..65535.
brightness_values=[-2147483648,-2000,-1,0,1,1993,1994,1999,2000,2001,2200,32767,65535]
brightness_values.extend(rng.randrange(-10000,65536) for _ in range(96))
table=[s for s in range(53) for i in range(256)]
for brightness in brightness_values:
    c,d=o.blit(256,1,[1]*256,256,1,[0,0,256,1],[0,0],[0,0,256,1],-1,brightness,[0]*256,[65535]*256,list(range(256)),table)
    assert d==[65535]*256
    add('saturated_brightness_all_alpha',['R',brightness],[words(c)])
raw=cells.quantize([1,1,1,.87,0,.028]);names=list(colors)
for i in range(182):
    name=names[i%len(names)];color=list(map(int,colors[name].split(',')))
    settings=[raw,[100,200,20,50,0,28],[180,50,100,100,0,100],[30,100,100,200,500,0]][i%4]
    x,y,z=33,86,i%8;detail=i%3
    sources=[[x*256+128+(i%5)*256,y*256+128,416,5000,200,50,50,10,i%2,2]]
    if i%7==0:sources.append([x*256+128,y*256+128,-100,1024,-300,1000,-200,30,1,0])
    if i>=128:
        settings=raw;x=35+(i-128)-27;y=86;z=4;detail=2
        sources=[[35*256+128,86*256+128,416,5000,200,50,50,10,1,2]]
    fields=cells.cell(settings,x,y,z,sources,detail)
    flags=0x10000 if i%11==0 else 0;predicate=i%2;effects=2 if i%13==0 else 0
    if i>=128:flags=effects=0
    brightness=o.brightness(fields[2],extra,flags,predicate,effects)[1]
    # Actual house/scheme lookup selects the table identity used below.
    selection=o.selection(i%len(names),list(range(len(names))))[0];assert names[selection]==name
    w,h,sw,sh=40,32,21,17;box=[1,2,18,14];at=[rng.randrange(-12,38),rng.randrange(-10,30)];clip=[0,0,w,h] if i%2 else [3,5,30,23];adjust=-1-z*15
    src=[rng.randrange(256) if j%7 else 0 for j in range(sw*sh)]
    target=[rng.randrange(65536) for _ in range(w*h)];depth=[rng.choice([0,32730,32760,32767,32768,65535]) for _ in target];alpha=[127 if i%3==0 else rng.randrange(256) for _ in target]
    c,d=o.final_blit(w,h,src,sw,sh,box,at,clip,adjust,brightness,target,depth,alpha,palettes[name])
    add('combined_cell_house_surfaces',['C',assets/'unittem.pal',*color,*settings,x,y,z,detail,len(sources),*[v for source in sources for v in source],extra,flags,predicate,effects,w,h,sw,sh,*box,*at,*clip,adjust,*src,*target,*depth,*alpha],[fields[2],brightness,words(c),words(d)])
for value in [.2,.6,-.15]:add('numeric_after_constructors_surfaces',['Q',value],[o.extra(value)])
o.check_heap()
report={**identities(a,engine_digest,engine_profile,native_data),'groups':groups,'seed':0x52413132,
        'owned_extra_unit_light':[extra_raw,extra],'fixture_services':o.services,'heap_file_services':o.counts,
        'audited_callable_roots':o.audit_calls+cells.audit_calls,'audited_blocks':o.audit_blocks+cells.audit_blocks,
        'guarded_scheme_allocations':o.scheme_allocations,'independent_scheme_fixture_resets':o.scheme_resets,
        'original_instructions_modified':False,
        'scope':'Actual ExtraUnitLight block, complete coordinates/effects, ordinary brightness and house selection blocks, full ordinary ColorScheme/LightConvert/byte-word Convert construction with successful heap and warm original alpha registry. Combined cell/house and final surfaces. Bounded caller/input/permitted-write/heap audits exclude ordered native-original writes, full actor arenas, full Unit draw, house creation, alternate weather/fog, converter/allocator lifetime and full-frame parity.'}
actual=run_native(a,commands)
if len(actual)!=len(expected):raise AssertionError(f'Result count {len(actual)}/{len(expected)}')
for i,(x,y) in enumerate(zip(actual,expected)):
    if x!=y:raise AssertionError(f'{i}: {commands[i][:160]}: native {x}, original {y}')
report['cases']=len(commands)
report.update(identities(a,engine_digest,engine_profile,native_data))
save(a,work,commands,expected,labels,report)
print(f'{engine_profile}: {len(commands):,} original/native unit-light cases: PASS; {groups}')
