# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_team_membership as d
class TeamMembershipEvidence(unittest.TestCase):
 def fixture(self):
  rows=list(d.scenarios());identity=dict(original={'inspection':'exact','sources':{'oracle':'original'}},native_sources={'kernel':'old'})
  meta=dict(d.FLAGS,identities=identity,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False)
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in rows],labels=[s for s,_ in rows],expected=[['F',*['0']*43] for _ in rows],evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),copy.deepcopy(identity)
 def test_domain(self):
  rows=list(d.scenarios());self.assertEqual(len(rows),237);[d.parse(c) for _,c in rows]
  for kw in (dict(slot=6),dict(op=4),dict(script=10),dict(onmap=256),dict(op=0,head=1),dict(op=3,head=2),dict(op=2,head=0,subject=1)):
   with self.assertRaises(ValueError):d.parse(d.command(**kw))
 def test_native_current_original_reused(self):
  e,r,c=self.fixture();c['native_sources']['kernel']='new';d.validate(e,r,'receipt',c)
  c['original']['sources']['oracle']='changed'
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
 def test_receipt_and_order_guards(self):
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):d.validate(e,r,'wrong',c)
  for key in ('commands','labels','expected'):
   bad=copy.deepcopy(e);bad[key]=bad[key][1:]
   with self.assertRaises(ValueError):d.validate(bad,r,'receipt',c)
  for row in ([],['F'],['F','F'],['4','0','0','0','0','0','F',*['0']*43]):
   with self.assertRaises(ValueError):d.validate_row(row)
 def test_wrong_engine(self):
  with self.assertRaises(ValueError):d.verify(b'wrong engine')
if __name__=='__main__':unittest.main()
