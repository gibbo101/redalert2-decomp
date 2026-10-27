# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_infantry_sight_schedule as c
class InfantrySightScheduleEvidence(unittest.TestCase):
 def test_sequences_and_scope(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),64)
  for _,cmd in rows:c.parse(cmd)
  self.assertIn('src/sim/InfantrySightSchedule.cpp',c.NATIVE)
 def test_guards(self):
  good=next(c.scenarios())[1]
  for cmd in ('',good+' 0',good.replace('S ','X ',1)):
   with self.assertRaises(ValueError):c.parse(cmd)
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_reuse_scope(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');expected=[['M','R','0','0','0','0','A','0','0','0','0','P'] for _ in rows]
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=expected,evidence=meta);r=dict(meta,expectations_sha256='receipt')
  c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}));bad=copy.deepcopy(e);bad['evidence']['production_visibility_schedule']=True
  with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()
