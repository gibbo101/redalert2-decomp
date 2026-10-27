# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_infantry_update_position_effects_e1 as c
class JoinedInfantryE1Evidence(unittest.TestCase):
 def test_sequences_and_scope(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),80)
  for _,cmd in rows:c.parse(cmd)
  self.assertIn('src/sim/InfantryPositionEffectsE1.cpp',c.NATIVE)
 def test_guards(self):
  good=next(c.scenarios())[1]
  for cmd in ('',good+' 0',good.replace('J ','X ',1)):
   with self.assertRaises(ValueError):c.parse(cmd)
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_reuse_scope(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');expected=[['m']*(7+4*c.parse(cmd)['onMap'])+['C']*3+['6']*2+['2']*2+['1']*2 for _,cmd in rows];e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=expected,evidence=meta);r=dict(meta,expectations_sha256='receipt')
  with self.assertRaises(ValueError):c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
  bad=copy.deepcopy(e);bad['evidence']['production_schedule']=True
  with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()
