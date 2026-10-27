# SPDX-License-Identifier: GPL-3.0-or-later
import copy,re,unittest
from pathlib import Path
from unittest.mock import patch
import compare_borrowed_cell_scatter as d
class BorrowedCellEvidenceTests(unittest.TestCase):
 def test_all_sources_exist(self):
  for p in d.SOURCES:self.assertTrue((d.ROOT/p).is_file(),p)
 def test_default_protocols_preserve_original_inputs(self):
  for parent in (d.parent,d.nearby):self.assertEqual(d.parse(parent.command()),parent.parse(parent.command()))
 def test_missing_actor_heads_refused(self):
  for parent in (d.parent,d.nearby):
   for field in (7,8):
    cells=parent.defaults()['cells'];cells[4][field]=2
    with self.assertRaises(ValueError):d.parse(parent.command(cells=cells))
 def test_missing_actor_next_destination_refused(self):
  for field in (1,14):
   objects=d.parent.defaults()['objects'];objects[0][field]=2
   with self.assertRaises(ValueError):d.parse(d.parent.command(objects=objects))
 def test_unbound_type_refused(self):
  with self.assertRaises(ValueError):d.parse(d.nearby.command(type_indexes=[0,2,2,3,4]))
 def test_unused_original_actor_not_promoted_to_bound_owner(self):
  objects=d.parent.defaults()['objects'];objects[3][7]=1
  with self.assertRaises(ValueError):d.parse(d.parent.command(objects=objects))
 def test_transitive_headers_fingerprinted(self):
  for p in d.source_closure():self.assertIn(p,d.SOURCES)
  for p in ('src/assets/PreparedUnitMembership.cpp','src/assets/BorrowedCellUnitScatterWorld.hpp','src/assets/BorrowedPreparedUnitAdmission.hpp','tests/borrowed_cell_scatter_fixture.hpp'):
   self.assertIn(p,d.SOURCES)
 def test_missing_scope_or_drift_refused(self):
  with patch.object(d,'validate_receipt'):
   with self.assertRaises(ValueError):d.validate({'evidence':{}},{},'hash',{})
if __name__=='__main__':unittest.main()
