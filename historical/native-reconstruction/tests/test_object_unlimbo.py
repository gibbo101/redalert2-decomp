# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_object_unlimbo as d
class ObjectUnlimboEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(d.scenarios());identity=dict(original={'inspection':'exact','sources':{'oracle':'original'}},native_sources={'kernel':'old'})
  meta=dict(d.FLAGS,identities=identity,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False)
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in rows],labels=[s for s,_ in rows],expected=[['F',*['0']*9] for _ in rows],evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),copy.deepcopy(identity)
 def test_domain(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),624);[d.parse(c) for _,c in rows]
  for kw in (dict(enabled=256),dict(width=32768),dict(mark=-1),dict(mutation=7),dict(x=2**31),dict(alpha=2)):
   with self.assertRaises(ValueError):d.parse(d.command(**kw))
 def test_current_native_with_original_reuse(self):
  e,r,c=self.fixture();c['native_sources']['kernel']='new';d.validate(e,r,'receipt',c)
  c['original']['sources']['oracle']='changed'
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
 def test_rows_receipt_and_scope(self):
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):d.validate(e,r,'wrong',c)
  for key in ('commands','labels','expected'):
   bad=copy.deepcopy(e);bad[key]=bad[key][1:]
   with self.assertRaises(ValueError):d.validate(bad,r,'receipt',c)
  e['evidence']['children_supplied']=False;r=dict(e['evidence'],expectations_sha256='receipt')
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
  for row in ([],['F'],['F','F'],['99',*['0']*5,'F',*['0']*9]):
   with self.assertRaises(ValueError):d.validate_row(row)
 def test_engine(self):
  with self.assertRaises(ValueError):d.verify(b'other executable')
if __name__=='__main__':unittest.main()
