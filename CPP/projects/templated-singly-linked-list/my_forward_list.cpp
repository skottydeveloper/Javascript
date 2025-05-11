#include <iostream>
#include <ctime>
#include <vector>
#include <forward_list>
#include <algorithm>
#include "my_forward_list.hpp"
#include "tests.hpp"

int main() {
    Forward_list<int> my_list;
    Tests tester;
   
    tester.test_size_initialization();
    tester.test_push_pop();
    tester.test_null_copy();
    tester.test_copy_constructor();
    tester.test_initializer_list();
    tester.test_initializer_list_str();
    tester.test_merge();
    tester.test_merge_edge_cases();
    tester.test_split();
    tester.test_split_and_merge();
    tester.test_sort();

    return 0;
}