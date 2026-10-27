# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_infantry_weapon_selection as c
class InfantryWeaponSelectionEvidence(unittest.TestCase):
 def test_sequences(self):
  rows=list(c.scenarios());self.assertEqual(len(rows),64)
  for _,cmd in rows:c.parse(cmd)
  self.assertEqual(sum(c.parse(x)['mission']==16 for _,x in rows),8)
 def test_guards(self):
  good=next(c.scenarios())[1]
  for cmd in ('',good+' 0',good.replace('S ','X ',1)):
   with self.assertRaises(ValueError):c.parse(cmd)
  with self.assertRaises(ValueError):c.verify(b'wrong executable')
 def test_reuse_scope(self):
  rows=list(c.scenarios());identity=dict(original={'engine':'one'},native_sources={'native':'old'});meta=dict(c.FLAGS,identities=identity,evidence_mode='fresh-original');expected=[]
  for _,cmd in rows:
   q=c.parse(cmd);sec=c.selected(q,'Secondary');calls=1+(1+int(c.elite(q) and not q['eliteSecondary']))+(1+int(c.elite(q) and not q['elitePrimary']) if sec else 0);expected.append(['T']*calls+['R','0'])
  e=dict(executable_sha256=c.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[x for _,x in rows],labels=[x for x,_ in rows],expected=expected,evidence=meta);r=dict(meta,expectations_sha256='receipt')
  with self.assertRaises(ValueError):c.validate(e,r,'receipt',dict(identity,native_sources={'native':'new'}))
  bad=copy.deepcopy(e);bad['evidence']['production_position_effect_schedule']=True
  with self.assertRaises(ValueError):c.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity)
if __name__=='__main__':unittest.main()
