# SPDX-License-Identifier: GPL-3.0-or-later
import ast,copy,re,unittest
from compare_owned_advance_runtime import parse,validate,authored_inputs,SOURCES
from presentation_evidence import ROOT
import test_owned_scheduled_preview_evidence as scheduled_evidence

class AdmittedRuntimeEvidence(unittest.TestCase):
 def fixture(self):
  e,r,c=scheduled_evidence.ScheduledEvidence().fixture()
  for key in ('same_schedule_original_Process0_Process1_finish0_finish1','runtime_owned_world_and_tick',
   'independent_original_order_calls_on_actual_actors','genuine_shared_world_Advance_admission','physical_target_membership_measured'):
   e['evidence'][key]=r[key]=True
  initial=[(cmd,res,l) for cmd,res,l in zip(e['commands'],e['expected'],e['labels']) if cmd.split()[0] in ('P','O','I','J')]
  draws=[(cmd,res,l) for cmd,res,l in zip(e['commands'],e['expected'],e['labels']) if cmd.startswith('D ')][:2]
  moves=[(cmd,res,l) for cmd,res,l in zip(e['commands'],e['expected'],e['labels']) if cmd.startswith('M ')]
  step=('H 101',{'events0':[['R',0,1]],'events1':[['R',1,1]],'state':[]},'step')
  rows=[]
  for id in (0,1):rows+=initial+[(f'K {id} 3200 3200 0 19 37 7 1',{'state':[]},'seed')]+moves+draws+[(f'X {id}',{'state':[]},'preview')]+[step]+draws
  e['commands'],e['expected'],e['labels']=map(list,zip(*rows))
  return e,r,c
 def test_protocol_requires_actual_steps_commands_and_later_draws(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
  for mutation in ('seed','warm','after','clock','command','return','role'):
   e,r,c=self.fixture()
   if mutation=='seed':e['commands'][4]='K 0 0 0 0 64 1 0 1'
   elif mutation=='warm':e['commands'][7]='X 0';e['expected'][7]={'state':[]}
   elif mutation=='after':e['commands']=e['commands'][:-2];e['expected']=e['expected'][:-2];e['labels']=e['labels'][:-2]
   elif mutation=='clock':e['commands'][e['commands'].index('H 101')]='H 102'
   elif mutation=='command':e['commands'][6]='S 0 100'
   elif mutation=='return':e['expected'][10]['events1']=[['R',0,1]]
   elif mutation=='role':
    for i,cmd in enumerate(e['commands']):
     if cmd.startswith('K 1 '):e['commands'][i]=cmd.replace('K 1 ','K 0 ',1)
     elif cmd=='X 1':e['commands'][i]='X 0'
   with self.subTest(mutation=mutation),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_receipt_and_scope_guards(self):
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):validate(e,r,'wrong',c)
  with self.assertRaises(ValueError):validate(e,r,'fingerprint',{})
  for key in ('runtime_owned_world_and_tick','genuine_shared_world_Advance_admission','physical_target_membership_measured'):
   e,r,c=self.fixture();e['evidence'][key]=r[key]=False
   with self.subTest(key=key),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_old_output_is_not_an_input(self):
  class Forbidden:
   def __getitem__(self,key):
    if key=='expected':raise AssertionError('Prior original output reused')
    return {'commands':['P authored','D authored'],'labels':['case','other']}[key]
  self.assertEqual(authored_inputs(Forbidden(),'case'),['P authored'])
 def test_complete_root_is_inherited(self):
  tree=ast.parse((ROOT/'tests/original_owned_advance_runtime.py').read_text())
  cls=next(n for n in tree.body if isinstance(n,ast.ClassDef))
  self.assertEqual(cls.bases[0].id,'OwnedOrdersWorldOracle')
  self.assertFalse(any(isinstance(n,ast.FunctionDef) for n in cls.body))
 def test_strict_steps(self):
  for cmd in ('H','H 1 2','H 2147483648','X 2','X -1','T 0 101','F 0 101','U 0 100 0 0 0 0 0'):
   with self.subTest(cmd=cmd),self.assertRaises(ValueError):parse(cmd)
 def test_native_header_closure(self):
  pending=[p for p in SOURCES if p.endswith('.cpp')];seen=set()
  while pending:
   p=pending.pop()
   if p in seen:continue
   seen.add(p);self.assertIn(p,SOURCES)
   for name in re.findall(r'^#include "([^"]+)"',(ROOT/p).read_text(),re.M):
    local=(ROOT/p).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
if __name__=='__main__':unittest.main()
