# SPDX-License-Identifier: GPL-3.0-or-later
import copy,unittest
import compare_scenery_current as d
class HistoricalSceneryEvidence(unittest.TestCase):
 def fixture(self):
  current=dict(oracle_sources={'oracle':'exact'},mapping_tools={'map':'exact'},render_data_sha256='render',assets_sha256={'asset':'original bytes'},fixture_sha256={'synthetic':'original bytes'},suite='scenery')
  origin=dict(current,exporter_sha256='historical exporter',evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False)
  e=dict(executable_sha256=d.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=['command']*420,labels=['case']*420,expected=[['value']]*420,evidence=origin)
  return e,dict(origin,expectations_sha256='receipt'),current
 def test_captured_bytes_allow_current_native(self):
  e,r,c=self.fixture();d.validate(e,r,'receipt',c)
  self.assertEqual(e['evidence']['exporter_sha256'],'historical exporter')
 def test_changed_original_inputs_refuse(self):
  for key in ('oracle_sources','mapping_tools','render_data_sha256','assets_sha256','fixture_sha256','suite'):
   e,r,c=self.fixture();c[key]='changed'
   with self.assertRaises(ValueError):d.validate(e,r,'receipt',c)
 def test_receipt_and_missing_rows_refuse(self):
  e,r,c=self.fixture()
  with self.assertRaises(ValueError):d.validate(e,r,'different',c)
  for key in ('commands','labels','expected'):
   bad=copy.deepcopy(e);bad[key]=bad[key][1:]
   with self.assertRaises(ValueError):d.validate(bad,r,'receipt',c)
if __name__=='__main__':unittest.main()
