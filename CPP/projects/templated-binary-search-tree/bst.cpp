#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "bst.hpp"
#include "unit_tests.hpp"

int main() {
    Tester my_test;

    for (int i = 0; i < 5; ++i) {
        my_test.test_insert_string();
        my_test.test_insert_size();
        my_test.test_insert_values();
        my_test.test_insert_heights();
        my_test.test_delete_min();
        my_test.test_delete_min_heights();
        my_test.test_successor();
        my_test.test_successor_max();
        my_test.test_erase();
        my_test.test_erase_heights();
        my_test.test_erase_root();
        my_test.test_erase_successor_child();
        my_test.test_rotate_right();
        my_test.test_rotate_root();
        my_test.test_rotate_heights();
    }
    
    return 0;
}