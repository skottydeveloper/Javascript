#ifndef TESTS_HPP
#define TESTS_HPP

#include <ctime>
#include <cassert>
#include <string>
#include <forward_list>
#include "my_forward_list.hpp"

class Tests {
public:
    Tests() {
        srand(time(NULL));
    }

    void test_size_initialization(void) {
        Forward_list<int> my_int_list;
        
        assert(my_int_list.size() == 0);

        Forward_list<std::string> my_string_list;
        
        assert(my_string_list.size() == 0);
        
        std::cout << "passed test_size_initialization\n";
    }

    void test_push_pop(void) {
        for (int test_count = 0; test_count < 3; ++test_count) {
            Forward_list<int> my_list;
            std::forward_list<int> real_list;

            for (unsigned i = 1; i <= 30; ++i) {
                int value = rand() % 1000;

                my_list.push_front(value);
                real_list.push_front(value);
                
                assert(my_list.size() == i);
            }

            for (unsigned i = 30; i >= 1; --i) {
                assert(my_list.front() == real_list.front());
                
                real_list.pop_front();
                my_list.pop_front();
                
                assert(my_list.size() == i - 1);
            }
        }

        std::cout << "passed test_push_pop\n";
    }

    void test_null_copy(void) {
        Forward_list<int> first_list;
        Forward_list<int> second_list {first_list};

        assert(second_list.size() == 0);
        
        std::cout << "passed test_null_copy\n";
    }

    void test_copy_constructor(void) {
        Forward_list<int> first_list;

        for (int i = 1; i <= 30; ++i) {
            int value = rand() % 1000;

            first_list.push_front(value);
        }

        Forward_list<int> second_list {first_list};
        
        for (unsigned i = 30; i >= 1; --i) {
            assert(first_list.front() == second_list.front());
            assert(second_list.size() == i);

            first_list.pop_front();
            second_list.pop_front();
        }

        std::cout << "passed test_copy_constructor\n";
    }

    void test_initializer_list(void) {
        std::initializer_list<int> inputs = {5, 23, 1, 105, -2, 7, 88, 0};

        Forward_list<int> my_list {inputs};
        
        std::forward_list<int> real_list {inputs};
        
        for (unsigned i = 8; i > 0; --i) {
            assert(my_list.front() == real_list.front());
            assert(my_list.size() == i);

            real_list.pop_front();
            my_list.pop_front();
        }

        std::cout << "passed test_initializer_list\n";
    }

    void test_initializer_list_str(void) {
        std::initializer_list<std::string> str_inputs = {"kangaroo", "bilby", "koala", "platypus", "taipan"};
        
        Forward_list<std::string> my_list {str_inputs};
        
        std::forward_list<std::string> real_list {str_inputs};
        
        for (unsigned i = 5; i > 0; --i) {
            assert(my_list.front() == real_list.front());
            assert(my_list.size() == i);
            
            real_list.pop_front();
            my_list.pop_front();
        }

        std::cout << "passed test_initializer_list_str\n";
    }

    void test_merge(void) {
        for (int test_counter = 0; test_counter < 3; ++test_counter) {
            const unsigned s1 = 1 + (rand() % 20);
            const unsigned s2 = 1 + (rand() % 20);
            
            std::vector<int> v1(s1);
            std::vector<int> v2(s2);
            
            std::generate(v1.begin(), v1.end(), [](){ return rand() % 100; });
            std::generate(v2.begin(), v2.end(), [](){ return rand() % 100; });
            
            std::sort(v1.rbegin(), v1.rend());
            std::sort(v2.rbegin(), v2.rend());
            
            Forward_list<int> my_list1;
            
            std::forward_list<int> real_list1;
            
            for (int x : v1) {
                my_list1.push_front(x);
                real_list1.push_front(x);
            }

            Forward_list<int> my_list2;
            
            std::forward_list<int> real_list2;
            
            for (int x : v2) {
                my_list2.push_front(x);
                real_list2.push_front(x);
            }

            my_list1.merge(my_list2);
            real_list1.merge(real_list2);
            
            for (unsigned i = 0; i < s1 + s2; ++i) {
                assert(my_list1.front() == real_list1.front());
                
                my_list1.pop_front();
                real_list1.pop_front();
            }
        }

        std::cout << "passed test_merge\n";
    }

    void test_merge_edge_cases(void) {
        // The other vector is empty.
        std::vector<int> vec(8);
        std::generate(vec.begin(), vec.end(), [](){ return rand() % 100; });
        std::sort(vec.rbegin(), vec.rend());
        
        Forward_list<int> my_list1;
        
        for (int x : vec) {
            my_list1.push_front(x);
        }

        Forward_list<int> my_list2;
        
        my_list1.merge(my_list2);
        
        for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
            assert(my_list1.front() == *it);

            my_list1.pop_front();
        }

        assert(my_list1.empty());
        assert(my_list2.empty());
        
        // Now testing when "*this" is empty.
        for (int x : vec) {
            my_list2.push_front(x);
        }

        my_list1.merge(my_list2);
        
        for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
            assert(my_list1.front() == *it);

            my_list1.pop_front();
        }

        assert(my_list1.empty());
        assert(my_list2.empty());
        
        std::cout << "passed test_merge_edge_cases\n";
    }

    void test_split(void) {
        for (int test_counter = 0; test_counter < 3; ++test_counter) {
            const unsigned s = 1 + (rand() % 20);
            unsigned middle = ((s % 2) == 0) ? s >> 1 : (s + 1) >> 1;

            std::vector<int> v1(s);
            
            std::generate(v1.begin(), v1.end(), [](){ return rand() % 100; });
            
            Forward_list<int> my_list;
            
            for (auto it = v1.rbegin(); it != v1.rend(); ++it) {
                my_list.push_front(*it);
            }

            Forward_list<int> second = my_list.split();

            assert(my_list.size() == middle);
            
            for (auto it = v1.begin(); it != v1.begin() + middle; ++it) {
                assert(*it == my_list.front());
                
                my_list.pop_front();
            }

            assert(my_list.empty());
            
            for (auto it = v1.begin() + middle; it != v1.end(); ++it) {
                assert(*it == second.front());
                
                second.pop_front();
            }

            assert(second.empty());
        }

        std::cout << "passed test_split\n";
    }

    void test_sort(void) {
        const unsigned s = 1 + (rand() % 20);

        std::vector<int> v1(s);
        
        std::generate(v1.begin(), v1.end(), [](){ return rand() % 100; });
        
        Forward_list<int> my_list;
        
        for (auto it = v1.rbegin(); it != v1.rend(); ++it) {
            my_list.push_front(*it);
        }

        my_list.sort();
        
        std::sort(v1.begin(), v1.end());
        
        for (auto x : v1) {
            assert(my_list.front() == x);
            my_list.pop_front();
        }

        std::cout << "passed test_sort\n";
    }

    void test_split_and_merge(void) {   
        const unsigned s = 1 + (rand() % 20);
    
        std::vector<int> v1(s);
        
        std::generate(v1.begin(), v1.end(), []() {
            return rand() % 100;
        });

        unsigned middle = ((s % 2) == 0) ? s >> 1 : (s + 1) >> 1;
        
        std::sort(v1.begin(), v1.begin() + middle);
        std::sort(v1.begin() + middle, v1.end());
        
        Forward_list<int> my_list; 
        
        for (auto it = v1.rbegin(); it != v1.rend(); ++it) {   
            my_list.push_front(*it);
        }

        Forward_list<int> second = my_list.split();
        
        my_list.merge(second);
        
        std::sort(v1.begin(), v1.end());
        
        for (int x : v1) {   
            assert(x == my_list.front());
            my_list.pop_front();
        }

        std::cout << "passed test_split_and_merge\n";
    }   
};

#endif