# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_infantry_destination as d
import compare_unit_destination_current as legacy
import test_unit_destination_evidence as legacy_tests
class InfantryDestinationEvidence(unittest.TestCase):
 def test_inputs_scope_and_closure(self):
  pairs=list(d.scenarios());self.assertTrue(pairs)
  for _,cmd in pairs:self.assertEqual(len(d.parse(cmd)['route']),24)
  self.assertIn('src/sim/FootDestination.hpp',d.SOURCES)
  self.assertIn('src/sim/InfantryDestination.hpp',d.SOURCES)
  self.assertNotIn('src/platform/BootCampPreview.cpp',d.SOURCES)
  for cmd in ('',d.command(jump=1),d.command(refs=0),d.command(mask=64),d.command(actions=[]),d.command()+' extra'):
   with self.assertRaises(ValueError):d.parse(cmd)
  with self.assertRaises(ValueError):d.verify(b'wrong executable')
 def fixture(self):
  pairs=list(d.scenarios());identity=dict(original={'source':'original'},native_sources={'source':'old'})
  meta=dict(d.FLAGS,identities=identity,audited_original_calls=sum(len(d.parse(c)['actions']) for _,c in pairs),evidence_mode='fresh-original')
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[c for _,c in pairs],labels=[l for l,_ in pairs],
   expected=[['R']*len(d.parse(c)['actions'])+['Z'] for _,c in pairs],evidence=meta)
  return e,dict(meta,expectations_sha256='receipt'),identity
 def test_reuse_still_requires_original_identity_and_receipt(self):
  e,r,c=self.fixture();d.validate(e,r,'receipt',dict(c,native_sources={'source':'rebuilt'}))
  for fingerprint,current in (('wrong',c),('receipt',dict(c,original={'source':'changed'}))):
   with self.assertRaises(ValueError):d.validate(e,r,fingerprint,current)
  e,r,c=self.fixture();e['expected'][0]=['Z']
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
 def test_no_fidelity_scope_promotion_or_input_changes(self):
  for k,v in d.FLAGS.items():
   e,r,c=self.fixture();e['evidence'][k]=not v;r=dict(e['evidence'],expectations_sha256='receipt')
   with self.subTest(k=k),self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
  e,r,c=self.fixture();e['commands'][0]=d.command(tick=101)
  with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
 def test_legacy_adapter_retains_every_original_source(self):
  e,r,c=legacy_tests.UnitDestinationEvidence().fixture()
  c['sources']={'tests/oracle.py':'original','src/old.hpp':'old'}
  e['evidence']['identities']=copy.deepcopy(c);r=dict(e['evidence'],expectations_sha256='fingerprint')
  current=copy.deepcopy(c);current['sources']['src/old.hpp']='rebuilt';current['sources']['src/new.hpp']='new'
  legacy.validate(e,r,'fingerprint',current)
  for key in ('inspection','sources'):
   bad=copy.deepcopy(current)
   if key=='sources':bad[key]['tests/oracle.py']='changed'
   else:bad[key]='changed'
   with self.assertRaises(ValueError):legacy.validate(e,r,'fingerprint',bad)
  with self.assertRaises(ValueError):legacy.validate(e,r,'bad receipt',current)
if __name__=='__main__':unittest.main()
