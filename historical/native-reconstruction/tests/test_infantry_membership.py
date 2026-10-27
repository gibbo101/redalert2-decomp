# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_infantry_membership as d
import compare_membership_current as replay
class InfantryMembershipEvidence(unittest.TestCase):
 def test_real_owners_and_scenarios(self):
  rows=list(d.scenarios([0]*100));self.assertGreater(len(rows),250)
  self.assertEqual(len(rows),len(set(c for _,c in rows)))
  for _,cmd in rows:d.parent.parse(cmd)
  for source in ('src/assets/MutableUnitMap.cpp','src/assets/PreparedInfantryMembership.hpp',
   'src/sim/BorrowedMembership.hpp','src/sim/MembershipPolicy.hpp','src/sim/InfantrySubcell.cpp'):
   self.assertIn(source,d.source_closure())
  self.assertNotIn('src/platform/BootCampPreview.cpp',d.SOURCES)
 def test_wrong_binary_refuses(self):
  with self.assertRaises(ValueError):d.verify(b'wrong engine')
 def test_new_originals_are_separate_from_native(self):
  rows=list(d.scenarios([0]*100));identity=dict(original={'planes':[0]*100},native_sources={'source':'old'})
  meta=dict(d.FLAGS,identities=identity,evidence_mode='fresh-original',audited_original_calls=sum(len(d.parent.parse(c)[4]) for _,c in rows))
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in rows],
   labels=[s for s,_ in rows],expected=[['S']*len(d.parent.parse(c)[4]) for _,c in rows],evidence=meta)
  r=dict(meta,expectations_sha256='receipt');d.validate(e,r,'receipt',dict(identity,native_sources={'source':'rebuilt'}))
  for f,current in (('wrong',identity),('receipt',dict(identity,original={'planes':[1]*100}))):
   with self.assertRaises(ValueError):d.validate(e,r,f,current)
  bad=copy.deepcopy(e);bad['evidence']['actual_Walk_Process_join']=True
  with self.assertRaises(ValueError):d.validate(bad,dict(bad['evidence'],expectations_sha256='receipt'),'receipt',identity)
 def test_resident_replay_checks_original_and_separates_native(self):
  old=replay.resident;command=old.cases()[0][1]
  origin=dict(inspection='base',sources={'src/assets/ResidentCellPreparation.cpp':'old','tests/original_resident_cell.py':'original'})
  meta=dict(identities=origin,evidence_mode='fresh-original')
  e=dict(executable_sha256=old.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[command],expected=[['state','events']],labels=['resident'],evidence=meta)
  r=dict(meta,expectations_sha256='receipt');current=copy.deepcopy(origin)
  current['sources']['src/assets/ResidentCellPreparation.cpp']='new';replay.validate(old,e,r,'receipt',current)
  current['sources']['tests/original_resident_cell.py']='changed'
  with self.assertRaises(ValueError):replay.validate(old,e,r,'receipt',current)
 def test_redraw_replay_keeps_original_dependencies_and_receipt(self):
  old=replay.redraw
  origin=dict(inspection='exact',sources={'src/render/Redraw.cpp':'old','tests/original_redraw.py':'original','tests/compare_redraw.py':'generator'})
  meta=dict(identities=origin,evidence_mode='fresh-original')
  e=dict(executable_sha256=old.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=['M 0 0 0 1 0 0'],expected=[['result']],labels=['redraw'],evidence=meta)
  r=dict(meta,expectations_sha256='receipt');current=copy.deepcopy(origin)
  current['sources']['src/render/Redraw.cpp']='borrowed-current';replay.validate(old,e,r,'receipt',current)
  for key in ('tests/original_redraw.py','tests/compare_redraw.py'):
   bad=copy.deepcopy(current);bad['sources'][key]='changed'
   with self.assertRaises(ValueError):replay.validate(old,e,r,'receipt',bad)
  bad=copy.deepcopy(current);bad['inspection']='other'
  with self.assertRaises(ValueError):replay.validate(old,e,r,'receipt',bad)
  with self.assertRaises(ValueError):replay.validate(old,e,r,'wrong',current)
 def test_old_receipt_and_all_original_dependencies_remain_checked(self):
  old=replay.mark;identity=dict(inspection='base',sources={'src/sim/UnitMark.cpp':'old','tests/original_unit_mark.py':'original'})
  e=dict(executable_sha256=old.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[old.command()],expected=[['S']],labels=['test'],
   evidence=dict(identities=identity,evidence_mode='fresh-original'))
  r=dict(e['evidence'],expectations_sha256='receipt')
  current=copy.deepcopy(identity);current['sources']['src/sim/UnitMark.cpp']='new'
  replay.validate(old,e,r,'receipt',current)
  for key,value in (('inspection','other'),('sources',{'src/sim/UnitMark.cpp':'new','tests/original_unit_mark.py':'changed'})):
   bad=copy.deepcopy(current);bad[key]=value
   with self.assertRaises(ValueError):replay.validate(old,e,r,'receipt',bad)
  with self.assertRaises(ValueError):replay.validate(old,e,r,'changed-receipt',current)
if __name__=='__main__':unittest.main()
