# SPDX-License-Identifier: GPL-3.0-or-later
"""Content/receipt/engine invalidation in the promoted-data replay boundary."""
import json,tempfile,unittest
from pathlib import Path
from replay_promoted_data import ROOT,DISC,PATCHED,sha,validate_evidence
class ReplayGuards(unittest.TestCase):
 def fixture(self,root):
  source=root/'source'/'game.exe';source.parent.mkdir();source.write_bytes(b'exe fixture')
  out=root/'evidence';out.mkdir();asset=out/'assets'/'test.bin';asset.parent.mkdir();asset.write_bytes(b'fixture')
  report={'executable_sha256':PATCHED,'profile':'supplied-ra2-1006','native_data_executable_sha256':DISC,
          'evidence_mode':'fresh-original','original_instructions_executed':True,
          'oracle_sources':{str(Path(__file__).resolve()):sha(Path(__file__))},
          'assets_sha256':{'test.bin':sha(asset)},'exporter_sha256':'historical binary'}
  expected=out/'expected.json';expected.write_text(json.dumps({'executable_sha256':PATCHED,'profile':'supplied-ra2-1006','commands':['test'],'expected':[['test']],'evidence':report}))
  (out/'report.json').write_text(json.dumps({**report,'expectations_sha256':sha(expected)}))
  return source,expected,asset
 def test_unchanged_fixture_survives_exporter_rebuild(self):
  with tempfile.TemporaryDirectory(dir=ROOT/'build') as temp:
   source,expected,asset=self.fixture(Path(temp))
   checks=validate_evidence(expected,PATCHED,'supplied-ra2-1006',source)
   self.assertEqual(checks[str(asset)],sha(asset))
 def test_changed_fixture_refused(self):
  with tempfile.TemporaryDirectory(dir=ROOT/'build') as temp:
   source,expected,asset=self.fixture(Path(temp));asset.write_bytes(b'changed')
   with self.assertRaisesRegex(ValueError,'identity differs'):validate_evidence(expected,PATCHED,'supplied-ra2-1006',source)
 def test_receipt_tampering_refused(self):
  with tempfile.TemporaryDirectory(dir=ROOT/'build') as temp:
   source,expected,asset=self.fixture(Path(temp));receipt=expected.parent/'report.json'
   data=json.loads(receipt.read_text());data['expectations_sha256']='changed';receipt.write_text(json.dumps(data))
   with self.assertRaisesRegex(ValueError,'fingerprint differs'):validate_evidence(expected,PATCHED,'supplied-ra2-1006',source)
 def test_cross_engine_refused(self):
  with tempfile.TemporaryDirectory(dir=ROOT/'build') as temp:
   source,expected,asset=self.fixture(Path(temp))
   with self.assertRaisesRegex(ValueError,'engine/profile differs'):validate_evidence(expected,DISC,'allied-disc',source)
if __name__=='__main__':unittest.main()
