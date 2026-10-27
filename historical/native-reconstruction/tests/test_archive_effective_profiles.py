# SPDX-License-Identifier: GPL-3.0-or-later
"""Effective-source replay guards using synthetic receipts, no original execution."""
import unittest
from replay_archive_effective import validate
class EffectiveArchiveEvidenceTests(unittest.TestCase):
 def test_each_identity_must_match(self):
  sources={'reader':'a'};files={'owned':'b'}
  evidence={'evidence_mode':'fresh-original-decoded-index-fixtures','executable_sha256':'engine',
            'profile':'profile','sources':sources,'owned_root_files':files}
  validate(evidence,'engine','profile',sources,files)
  for key in ['executable_sha256','profile','sources','owned_root_files']:
   with self.assertRaisesRegex(ValueError,'identity differs'):
    validate({**evidence,key:'changed'},'engine','profile',sources,files)
 def test_replay_and_broader_parity_labels_cannot_replace_fresh_fixture_evidence(self):
  for mode in ['cached-original-decoded-index-replay','fresh-original',None]:
   with self.assertRaisesRegex(ValueError,'fresh original decoded-index'):
    validate({'evidence_mode':mode},'engine','profile',{}, {})
if __name__=='__main__':unittest.main()
