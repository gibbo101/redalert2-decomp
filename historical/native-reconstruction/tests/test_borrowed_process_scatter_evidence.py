# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
from types import SimpleNamespace
from unittest.mock import patch
import compare_borrowed_process_scatter as d
from compare_original import PATCHED_EXPECTED
class BorrowedProcessEvidence(unittest.TestCase):
 def fixture(self):
  current=dict(scope='pilot',pilot_limit=1,sources={'one':'two'},legacy_native_sha256='legacy')
  meta=dict(d.parent.FLAGS,**d.FLAGS,identities=current,evidence_mode='fresh-original',native_sha256='runner',audited_complete_Process_calls=1,actual_counts={'Process_return.0':1},per_case_counts=[{}])
  e=dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=[d.command()],labels=['fixture'],expected=[['state',*['actor']*4,'geometry','scratch','moving','process-return','process-state']],evidence=meta)
  return e,dict(meta,expectations_sha256='fingerprint'),copy.deepcopy(current)
 def test_all_sources_exist(self):
  for p in d.SOURCES:self.assertTrue((d.ROOT/p).is_file(),p)
 def test_protocol_unchanged(self):self.assertEqual(d.parse(d.command()),d.parent.parse(d.command()))
 def test_unbound_actor_refused(self):
  cells=d.parent.defaults()['cells'];cells[4][7]=2
  with self.assertRaises(ValueError):d.parse(d.command(cells=cells))
 def test_unbound_next_destination_refused(self):
  for field in (1,14):
   objects=d.parent.defaults()['objects'];objects[0][field]=2
   with self.assertRaises(ValueError):d.parse(d.command(objects=objects))
 def test_no_promoted_Process1_or_runtime_claim(self):
  for key in ('complete_Process1_verified','production_runtime_enabled'):
   self.assertFalse(d.FLAGS[key])
   e,r,c=self.fixture();e['evidence'][key]=r[key]=True
   with self.assertRaises(ValueError):d.validate(e,r,'fingerprint',c)
 def test_receipt_source_runner_and_scope_guards(self):
  e,r,c=self.fixture();d.validate(e,r,'fingerprint',c)
  for key in ('sources','legacy_native_sha256','scope'):
   e,r,c=self.fixture();c[key]='changed'
   with self.assertRaises(ValueError):d.validate(e,r,'fingerprint',c)
  e,r,c=self.fixture();r['expectations_sha256']='changed'
  with self.assertRaises(ValueError):d.validate(e,r,'fingerprint',c)
 def test_both_current_native_runners_execute(self):
  a=SimpleNamespace(native='borrowed',legacy_native='legacy')
  with patch.object(d.parent,'compare',return_value=1) as run:
   self.assertEqual(d.compare(a,['input'],[['output']],d.ROOT/'private/unused-report'),1)
   self.assertEqual([v.args[0].native for v in run.call_args_list],['borrowed','legacy'])
 def test_borrowed_transitive_headers_and_profile_fingerprinted(self):
  for p in ('src/assets/ProcessTerminalScatterWorld.hpp','src/assets/AdvanceTerminalScatterWorld.hpp','src/assets/AdvanceNearbyScatterWorld.hpp','src/assets/AdvanceCellScatterWorld.hpp','src/assets/BorrowedPreparedUnitAdmission.hpp','tests/borrowed_cell_scatter_fixture.hpp','tests/borrowed_process_scatter/CMakeLists.txt'):
   self.assertIn(p,d.SOURCES)
if __name__=='__main__':unittest.main()
