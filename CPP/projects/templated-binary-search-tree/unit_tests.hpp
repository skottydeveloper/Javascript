#ifndef ASSERT_TESTS_HPP
#define ASSERT_TESTS_HPP

#include <unordered_set>
#include <vector>
#include <string>
#include <cassert>
#include <random>
#include "bst.hpp"

class Tester {
public:
    std::vector<int> generate_without_duplicates() {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<unsigned> size_dist(2, 20);
        unsigned size = size_dist(mt);
        std::vector<int> vec;
        vec.reserve(size);
        std::unordered_set<int> setto;
        std::uniform_int_distribution<int> val_dist(0, 100);
        unsigned i = 0;

        while(i < size) {
            int val = val_dist(mt);
            
            if (setto.count(val) == 0) {
                setto.insert(val);
                vec.push_back(val);
                ++i;
            }
        }

        return vec;
    }

//*** 4 tests of insert
    void test_insert_string(void) {
        std::vector<std::string> vec {"Sydney", "Melbourne", "Hobart", "Adelaide", "Perth", "Brisbane", "Darwin"};
        BST<std::string> tree;

        for (const auto& x : vec) {
            tree.insert(x);
        }

        assert(vec.size() == tree.size());
        std::sort(vec.begin(), vec.end());
        std::vector<std::string> inorder_vec = tree.make_vec();
        assert(inorder_vec == vec);
        std::cout << "passed test_insert_string\n";
    }

    void test_insert_size(void) {
        std::vector<int> vec = generate_without_duplicates();
        BST<int> tree;

        for (int x : vec) {
            tree.insert(x);
        }

        assert(vec.size() == tree.size());
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<unsigned> index_dist(0, vec.size() - 1);
        
        for (int i = 0; i < 5; ++i) {
            unsigned index = index_dist(mt);
            tree.insert(vec[index]);
            assert(vec.size() == tree.size());
        }

        std::cout << "passed test_insert_size\n";
    }

    void test_insert_values(void) {
        std::vector<int> vec = generate_without_duplicates();
        BST<int> tree;

        for (int x : vec) {
            tree.insert(x);
        }

        std::vector<int> tree_inorder = tree.make_vec();
        std::sort(vec.begin(), vec.end());
        assert(vec == tree_inorder);
        std::cout << "passed test_insert_values\n";
    }
    
    void test_insert_heights(void) {
        std::vector<int> vec = generate_without_duplicates();
        BST<int> tree;

        for (int x : vec) {
            tree.insert(x);
        }

        std::vector<int> your_heights = tree.your_postorder_heights(); 
        std::vector<int> real_heights = tree.real_postorder_heights(); 
        assert(!your_heights.empty());
        assert(your_heights == real_heights);
        std::cout << "passed test_insert_heights\n";
    }

//*** 2 tests of delete_min
    void test_delete_min(void) {
        std::vector<int> vec = generate_without_duplicates();
        BST<int> tree;

        for (int x : vec) {
            tree.insert(x);
        }

        std::sort(vec.begin(), vec.end());
        
        for(int x : vec) {
            BST<int>::Node* node = tree.min();
            assert(node != nullptr);
            assert(node->key ==  x);
            tree.delete_min();
        }

        std::cout << "passed test_delete_min\n";
    }

    void test_delete_min_heights(void) {
        std::vector<int> vec = generate_without_duplicates();
        BST<int> tree;

        for (int x : vec) {
            tree.insert(x);
        }

        tree.delete_min();
        std::vector<int> your_heights = tree.your_postorder_heights(); 
        std::vector<int> real_heights = tree.real_postorder_heights(); 
        assert(!your_heights.empty());
        assert(your_heights == real_heights);
        std::cout << "passed test_delete_min_heights\n";
    }

//*** 2 tests of successor
    void test_successor(void) {
        std::vector<int> vec = generate_without_duplicates();
        BST<int> tree;

        for (int x : vec) {
            tree.insert(x);
        }

        std::sort(vec.begin(), vec.end());
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<unsigned> index_dist(0, vec.size() - 2);
        
        for (int i = 0; i < 3; ++i) {
            unsigned index = index_dist(mt);
            BST<int>::Node* node = tree.successor(vec[index]);
            assert(node != nullptr);
            assert(node->key == vec[index + 1]);
        }

        std::cout << "passed test_successor\n";
    }

    void test_successor_max(void) {
        std::vector<int> vec = generate_without_duplicates();
        BST<int> tree;

        for (int x : vec) {
            tree.insert(x);
        }

        std::sort(vec.begin(), vec.end());
        BST<int>::Node* node = tree.successor(vec.back());
        assert(node == nullptr);
        std::cout << "passed test_successor_max\n";
    }

//*** 4 tests of erase
    void test_erase(void) {
        std::vector<int> vec = generate_without_duplicates();
        BST<int> tree;

        for (int x : vec) {
            tree.insert(x);
        }

        std::sort(vec.begin(), vec.end());
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<unsigned> index_dist(0, vec.size() - 1);
        unsigned index = index_dist(mt);
        tree.erase(vec[index]);
        vec.erase(vec.begin() + index);
        std::sort(vec.begin(), vec.end());
        std::vector<int> tree_inorder = tree.make_vec();
        assert(tree_inorder == vec);
        assert(tree.size() == vec.size());
        std::cout << "passed test_erase\n";
    }

    void test_erase_heights(void) {
        std::vector<int> vec = generate_without_duplicates();
        BST<int> tree;

        for (int x : vec) {
            tree.insert(x);
        }

        std::sort(vec.begin(), vec.end());
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<unsigned> index_dist(0, vec.size() - 1);
        unsigned index = index_dist(mt);
        tree.erase(vec[index]);
        std::vector<int> your_heights = tree.your_postorder_heights(); 
        std::vector<int> real_heights = tree.real_postorder_heights(); 
        assert(!your_heights.empty());
        assert(your_heights == real_heights);
        std::cout << "passed test_erase_heights\n";
    }

    void test_erase_root(void) {
        std::vector<int> vec = generate_without_duplicates();
        BST<int> tree;

        for (int x : vec) {
            tree.insert(x);
        }

        int root_val = tree.get_root_value();
        tree.erase(root_val);
        auto it = vec.begin();
        
        for (; it != vec.end(); ++it) {
            if(*it == root_val) break;
        }

        assert(it != vec.end());
        vec.erase(it); 
        std::sort(vec.begin(), vec.end());
        std::vector<int> tree_inorder = tree.make_vec();
        assert(tree_inorder == vec);
        std::cout << "passed test_erase_root\n";
    }

    void test_erase_successor_child(void) {
        std::vector<int> vec {7, 3, 13, 1, 5, 11, 20};
        BST<int> tree;

        for (int x : vec) {
            tree.insert(x);
        }

        tree.erase(13);
        std::vector<int> after_erase {1, 3, 5, 7, 11, 20};
        std::vector<int> tree_inorder = tree.make_vec();
        assert(tree_inorder == after_erase);
        std::cout << "passed test_erase_successor_child\n";
    }

//*** 3 tests of rotate_right
    void test_rotate_right(void) {
        std::vector<int> vec = generate_without_duplicates();
        BST<int> tree;

        for (int x : vec) {
            tree.insert(x);
        }

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<unsigned> index_dist(0, vec.size() - 1);
        unsigned index = index_dist(mt);
        BST<int>::Node* node = tree.find(vec[index]);
        assert(node != nullptr);
        
        if (node->left == nullptr) {
            return;
        }

        BST<int>::Node* left_child = node->left;
        BST<int>::Node* original_parent = node->parent;
        tree.rotate_right(node);
        assert(left_child->right == node);  
        assert(left_child == node->parent);  
        assert(left_child->parent == original_parent);  
        
        // check that BST property is still satisfied
        std::sort(vec.begin(), vec.end());
        std::vector<int> tree_inorder = tree.make_vec();
        assert(tree_inorder == vec); 
        std::cout << "passed test_rotate_right\n";
    }

    void test_rotate_root(void) {
        std::vector<int> vec = generate_without_duplicates();
        BST<int> tree;

        for (int x : vec) {
            tree.insert(x);
        }

        // ensure that root has a left child
        tree.insert(-1);
        vec.push_back(-1);
        int root_val = tree.get_root_value();
        BST<int>::Node* node = tree.find(root_val);
        assert(node != nullptr);
        BST<int>::Node* left_child = node->left;
        assert(left_child != nullptr);
        BST<int>::Node* original_parent = node->parent;
        tree.rotate_right(node);
        assert(left_child->right == node);  
        assert(left_child == node->parent);  
        assert(left_child->parent == original_parent);  
        
        // check that BST property is still satisfied
        std::sort(vec.begin(), vec.end());
        std::vector<int> tree_inorder = tree.make_vec();
        assert(tree_inorder == vec); 
        std::cout << "passed test_rotate_root\n";
    }

    void test_rotate_heights(void) {
        std::vector<int> vec = generate_without_duplicates();
        BST<int> tree;

        for (int x : vec) {
            tree.insert(x);
        }

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<unsigned> index_dist(0, vec.size() - 1);
        unsigned index = index_dist(mt);
        BST<int>::Node* node = tree.find(vec[index]);
        assert(node != nullptr);
        
        if (node->left == nullptr) {
            return;
        }

        tree.rotate_right(node);
        std::vector<int> your_heights = tree.your_postorder_heights(); 
        std::vector<int> real_heights = tree.real_postorder_heights(); 
        assert(!your_heights.empty());
        assert(your_heights == real_heights);
        std::cout << "passed test_rotate_heights\n";
    }
};

#endif