# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from compare_process_terminal_scatter import command,parse,defaults,FLAGS,SOURCES,source_closure,validate
from compare_original import PATCHED_EXPECTED
from verify_process_terminal_scatter import verify
class ProcessTerminalEvidence(unittest.TestCase):
 def fixture(self):
  current=dict(scope='pilot',pilot_limit=1,sources={'one':'two'})
  meta=dict(FLAGS,identities=current,evidence_mode='fresh-original',native_sha256='runner',audited_complete_Process_calls=1,actual_counts={'Process_return.0':1},per_case_counts=[{}])
  e=dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[command()],labels=['fixture'],expected=[['state',*['actor']*4,'geometry','scratch','moving','process-return','process-state']],evidence=meta)
  return e,dict(meta,expectations_sha256='fingerprint'),copy.deepcopy(current)
 def test_roundtrip(self):
  c=parse(command());c.pop('terminal_record');self.assertEqual(c,defaults())
 def test_exact_target_and_sources(self):
  with self.assertRaises(ValueError):verify(b'wrong binary')
  self.assertTrue(set(source_closure())<=set(SOURCES))
 def test_domain(self):
  for k,v in [('process_track',-2),('process_ramp',21),('process_percentage',0x7ff0000000000000),('queue',[0]*24),('owned',1)]:
   with self.subTest(k=k),self.assertRaises(ValueError):parse(command(**{k:v}))
 def test_scope_and_receipt_cannot_be_relabelled(self):
  e,r,c=self.fixture();validate(e,r,'fingerprint',c)
  for k,v in FLAGS.items():
   e,r,c=self.fixture();e['evidence'][k]=r[k]=not v
   with self.subTest(k=k),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
  for mutation in ('receipt','scope','sources','pilot_limit','root_count','case_counts'):
   e,r,c=self.fixture()
   if mutation=='receipt':r['expectations_sha256']='changed'
   elif mutation=='root_count':e['evidence']['audited_complete_Process_calls']=2
   elif mutation=='case_counts':e['evidence']['per_case_counts']=[]
   else:c[mutation]='changed'
   with self.subTest(mutation=mutation),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_projection_and_input_guards(self):
  for tag in ('state','actor','geometry','scratch','moving','process-return','process-state'):
   e,r,c=self.fixture();e['expected'][0].remove(tag)
   with self.subTest(tag=tag),self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
  e,r,c=self.fixture();e['commands'][0]+=' trailing'
  with self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
 def test_full_scope_requires_actual_all_caller_and_preparation_branches(self):
  e,r,c=self.fixture();c['scope']=e['evidence']['identities']['scope']='full'
  with self.assertRaises(ValueError):validate(e,r,'fingerprint',c)
if __name__=='__main__':unittest.main()
