# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_sprite_converter as d
class SpriteConverterEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(d.scenarios());current=dict(original={'inspection':'exact','sources':{'oracle':'original'}},native_sources={'kernel':'old'})
  meta=dict(d.FLAGS,identities=current,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False)
  expected=[]
  for _,cmd in rows:
   row=[]
   for call in range(4):
    if not cmd[1]&(1<<call):row+=['W',str(call%2),'0']
    row+=['R',*['0']*34]
   expected.append(row)
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in rows],labels=[s for s,_ in rows],expected=expected,evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),copy.deepcopy(current)
 def test_domain(self):
  self.assertEqual(len(list(d.scenarios())),288)
  for _,cmd in d.scenarios():d.parse(cmd)
  for cmd in ([2,0,0,0,0],[1,16,0,0,0],[1,0,0,2**31,0],[1,0,0,0,1]):
   with self.assertRaises(ValueError):d.parse(cmd)
 def test_current_native_reuses_original_only(self):
  e,r,c=self.fixture();c['native_sources']['kernel']='new';d.validate(e,r,'receipt',c)
  c['original']['sources']['oracle']='changed'
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
 def test_receipt_and_row_refusals(self):
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):d.validate(e,r,'different',c)
  for key in ('commands','labels','expected'):
   bad=copy.deepcopy(e);bad[key]=bad[key][1:]
   with self.assertRaises(ValueError):d.validate(bad,r,'receipt',c)
  with self.assertRaises(ValueError):d.validate_row(['R','0'],[1,15,0,0,0])
 def test_wrong_engine(self):
  with self.assertRaises(ValueError):d.verify(b'wrong engine')
if __name__=='__main__':unittest.main()
