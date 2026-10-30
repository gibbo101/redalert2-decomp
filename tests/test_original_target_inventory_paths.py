import sys,unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools/original_target'))
from inventory import split_inventory_paths,Inventory

class InventoryPathTests(unittest.TestCase):
    def test_windows_drive_colons_are_not_list_separators(self):
        self.assertEqual(split_inventory_paths('C:/ra2/trial;D:/other',';'),['C:/ra2/trial','D:/other'])
        self.assertEqual(split_inventory_paths('C:\\ra2\\trial',';'),['C:\\ra2\\trial'])
    def test_windows_legacy_colon_lists_keep_drive_letters(self):
        self.assertEqual(split_inventory_paths('trial:old',';'),['trial','old'])
        self.assertEqual(split_inventory_paths('C:/trial:D:/old',';'),['C:/trial','D:/old'])
    def test_posix_lists_keep_native_colon_contract(self):
        self.assertEqual(split_inventory_paths('/trial:/old',':'),['/trial','/old'])
    def test_empty_elements_do_not_select_current_directory(self):
        self.assertEqual(split_inventory_paths(';C:/trial;;',';'),['C:/trial'])
        self.assertEqual(split_inventory_paths('',':'),[])
    def test_explicit_empty_inventory_is_not_default_inventory(self):
        self.assertEqual(Inventory([]).passes,[])

if __name__=='__main__':unittest.main()
