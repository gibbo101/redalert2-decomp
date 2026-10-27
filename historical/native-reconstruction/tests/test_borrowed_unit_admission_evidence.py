#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
import copy,re,unittest
from pathlib import Path
import compare_borrowed_unit_admission as driver
import compare_moving_unit_admission as parent

class BorrowedAdmissionEvidenceTests(unittest.TestCase):
 def test_declared_source_paths_exist(self):
  for path in driver.SOURCES:self.assertTrue((driver.ROOT/path).is_file(),path)
 def test_default_command_retains_original_input(self):
  self.assertEqual(driver.parse(driver.command()),parent.parse(parent.command()))
 def test_unbound_resident_refused(self):
  for layer in (11,12):
   cells=copy.deepcopy(parent.CELLS);cells[0][layer]=2
   with self.assertRaises(ValueError):driver.parse(driver.command(cells=cells))
 def test_unbound_target_or_next_refused(self):
  for field in (1,13,14):
   objects=copy.deepcopy(parent.OBJECTS);objects[0][field]=2
   with self.assertRaises(ValueError):driver.parse(driver.command(objects=objects))
 def test_unused_original_actor_cannot_be_changed(self):
  objects=copy.deepcopy(parent.OBJECTS);objects[3][7]=1
  with self.assertRaises(ValueError):driver.parse(driver.command(objects=objects))
 def test_all_borrowed_implementation_dependencies_declared(self):
  for path in ('src/sim/BorrowedUnitAdmission.hpp','src/assets/BorrowedPreparedUnitAdmission.hpp',
   'src/assets/PreparedUnitMembership.cpp','tests/borrowed_admission_fixture.hpp',
   'tests/borrowed_unit_admission_check.cpp','tests/borrowed_unit_admission/CMakeLists.txt'):
   self.assertIn(path,driver.SOURCES)
 def test_transitive_native_headers_are_fingerprinted(self):
  pending=['tests/borrowed_unit_admission_vectors.cpp','tests/borrowed_unit_admission_check.cpp'];seen=set()
  while pending:
   path=pending.pop()
   if path in seen:continue
   seen.add(path);self.assertIn(path,driver.SOURCES)
   for name in re.findall(r'^#include "([^"]+)"',(driver.ROOT/path).read_text(),re.M):
    target=Path('src')/name
    if not (driver.ROOT/target).is_file():target=Path(path).parent/name
    pending.append(str(target))
 def test_legacy_policy_headers_are_fingerprinted(self):
  import compare_movement_gate as gates
  import compare_unit_admission as admission
  for driver,start in ((gates,'src/sim/MovementGate.cpp'),(admission,'src/sim/UnitAdmission.cpp')):
   pending=[start];seen=set()
   while pending:
    path=pending.pop()
    if path in seen:continue
    seen.add(path);self.assertIn(path,driver.SOURCES)
    for name in re.findall(r'^#include "([^"]+)"',(driver.ROOT/path).read_text(),re.M):
     pending.append('src/'+name)
 def test_missing_prepared_evidence_scope_refused(self):
  from unittest.mock import patch
  with patch.object(parent,'validate'):
   with self.assertRaisesRegex(ValueError,'prepared-owner'):
    driver.validate({'evidence':{}},{},'hash',{})
 def test_unknown_fields_in_source_identity_refused(self):
  e={'evidence':{'identities':{'sources':{'a':'one'}}},'executable_sha256':driver.PATCHED_EXPECTED,'profile':'supplied-ra2-1006'}
  from unittest.mock import patch
  with patch.object(parent,'validate_receipt'):
   with self.assertRaisesRegex(ValueError,'identity'):
    driver.validate(e,{},'hash',{'sources':{'a':'two'}})

if __name__=='__main__':unittest.main()
