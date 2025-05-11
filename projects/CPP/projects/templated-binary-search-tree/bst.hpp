#ifndef BST_ASSIGNMENT_HPP
#define BST_ASSIGNMENT_HPP

#include <iostream>
#include <algorithm>

template <typename T>
class BST {
public:
    /* We have a Node class with more features now. In addition to pointers to the left and right child, there is also a pointer to the parent of Node.  
    The parent of the root should always be nullptr. We also have a height field to store the height of a node in the tree. */
    class Node {
    public:
        T key;
        int height = 0;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
        
        // Default constructor.
        Node(){}
        
        // This is a constructor that takes one or optionally 2 arguments. If only one argument is passed in the second argument, it defaults to nullptr.
        Node(T k, Node* input_node = nullptr) {
            key = k;
            parent = input_node;
        }
    };

private:
    /* The BST has two private variables: a pointer to the root, and an unsigned integer to hold its size.
    We make the style choice of indicating these are private data variables by having a trailing underscore in their names. */
    Node* root_ = nullptr;
    unsigned int size_ = 0;

public:
    // Default constructor.
    BST(); 

    // Destructor.
    ~BST();

    /* Insert the key k into the BST while maintaining the BST property. 
    Like std::set, if k is already in the tree then no action is taken. 
    Update the size_ variable and heights of nodes accordingly. */
    void insert(T k);

    /* Return a pointer to the node containing the smallest key larger than k. 
    Return nullptr if k is the largest key in the tree. 
    Also return nullptr if k is not in the tree. */
    Node* successor(T k);

    /* Delete the minimum, and erase the minimum key in the tree. 
    Take no action if tree is empty. */
    void delete_min();

    /* Locate the key k in the tree and remove it.
    If k is not in the tree you do not have to do anything.
    Update the size_ variable and heights of nodes accordingly. */
    void erase(T k);

    /* Implement a right rotation about the node pointed to by node, as described in Lecture 8.6. This will only be called when node has a left child.  
    If left_child points to the left child of *node, then *left_child becomes the parent of *node, and the right subtree of *left_child becomes the left subtree of *node.  
    Node heights should be properly updated after this operation. */
    void rotate_right(Node* node);

    // Returns the number of keys in the tree.
    unsigned size();

    // Prints out the keys in the tree via an in-order traversal.
    void print();

    // Returns a pointer to the node containing the key k.
    Node* find(T k);

    // Creates a vector holding the keys in the tree by doing an in-order traversal.
    std::vector<T> make_vec();

    // The next two functions are to check the height values. 
    std::vector<int> your_postorder_heights();
    
    std::vector<int> real_postorder_heights();

    // Returns the value stored at the root.
    T get_root_value();

    // Returns a pointer to the node containing the minimum key in the tree.
    Node* min();

private: 
    // This function assumes that the subtrees rooted at node's children have correct heights and then walks up the tree from node to the root correcting the heights.
    void fix_height(Node* node);

    // Helper function for the destructor.
    void delete_subtree(Node* node);

    // Returns the pointer to the minimum node in the subtree rooted by node, while assuming that the node is not nullptr.
    Node* min(Node* node);

    // Helper function for print().
    void print(Node* node);

    // Helper function for make_vec().
    void make_vec(Node* node, std::vector<T>& vec);

    // The next two functions are to check the height values.
    void your_postorder_heights(Node* node, std::vector<int>& vec);

    int real_postorder_heights(Node* node, std::vector<int>& vec);
};

// Default constructor.
template <typename T>
BST<T>::BST() {
}

// Destructor.
template <typename T>
BST<T>::~BST() {
    delete_subtree(root_);
}

// Helper function for the destructor.
template <typename T>
void BST<T>::delete_subtree(Node* node) {
    if (node == nullptr) {
        return;
    }

    delete_subtree(node->left);
    delete_subtree(node->right);
    
    delete node;
}

/* The "fix_height()" function corrects the heights while walking up the binary search tree from the node to the root. 
The function does this under the assumption that the subtrees rooted at the node's children, have the correct heights. */
template <typename T>
void BST<T>::fix_height(Node* node) {
    while (node != nullptr) {
        int left_height = height(node->left);
        int right_height = height(node->right);
        node->height = 1 + std::max(left_height, right_height);
        node = node->parent;
    } 
}

/* The "insert()" function involves inserting the key "k" into the binary search tree while still maintaining its binary search tree property. 
    If "k" is already in the tree, then no action is taken. Update the "size_" variable and heights of nodes accordingly. */
template <typename T>
void BST<T>::insert(T k) {
    // The node will iterate down through the tree, starting from the root.
    Node* node = root_;
    
    // "prev_node" will hold the node's parent.
    Node* prev_node = node;
    bool went_right;

    // If the tree is empty, then point the root node to a newly created node, and increment the size by one. 
    if (node == nullptr) {
        root_ = new Node(k);
        ++size_;

        return;
    }

    // While the node isn't null, insert the key "k" into the binary search tree - according to its size.  
    while (node != nullptr) {
        prev_node = node;
        
        if (k < node->key) {
            node = node->left;
            went_right = false;
        } else if (k > node->key) {
            node = node->right;
            went_right = true;
        } else { // If the item is already in the set.
            return;
        }
    }

    // The new node is either the left or right child of "prev_node".
    if (went_right) {
        prev_node->right = new Node(k, prev_node);
    } else {
        prev_node->left = new Node(k, prev_node);
    }

    // Correct height of ancestors of "prev_node".
    fix_height(prev_node);

    // Increment the size by one. 
    ++size_;
}

/* There are two cases here:
    -  If the node containing k has a right child, then the successor will be the minimum node in its right subtree.
    -  Otherwise, the successor will be the first node with a key bigger than k on the path from the node with key k to the root. */
template <typename T>
typename BST<T>::Node* BST<T>::successor(T k) {
    struct Node* current = find(k);
	
    // If the current node is null, point the memory address of the current node - to zero.
    if (current == nullptr) {
        return nullptr;
    } 

    /* If the node to the right of the current node isn't null - return its minimum key. 
    Otherwise, while the parent node isn't the current node: 
        - Make the successor node the parent node, and push it to the left. 
        - Or, simply push the parent node to the right. */
	if (current->right != nullptr) {
		return min(current->right);
	} else {
		struct Node* successor = nullptr;
		struct Node* parent = root_;
		
        while (parent != current) {
		    if (current->key < parent->key) {
				successor = parent;
				parent = parent->left;
			} else {
                parent = parent->right;
            }	
		}

		return successor;
	}
}

/* The "delete_min()" method takes the root of the binary search tree as an argument and returns the root of the tree. */
template <typename T>
void BST<T>::delete_min() { 
    // Case 1: If the tree is empty, then don't do anything.  
    if (root_ == nullptr) {
        return; 
    } 

    // Case 2: If the root is the smallest node, then the right child of the root will be made the new root. 
	if (root_->left != nullptr) { 
		Node* parent = root_; 
		Node* min_node = root_->left;

		while (min_node->left != nullptr) { 
			parent = min_node; 
			min_node = min_node->left; 

            // Correct height of ancestors of "min_node".
            fix_height(min_node); 
		} 
		 
		if (min_node->right == nullptr) { 
			parent->left = nullptr;

            // Correct height of ancestors of "min_node".
            fix_height(min_node);  
			
            // Update pointers to remove "min_node" from the tree.
            min_node = nullptr;  
        
            delete min_node; 
		} else {
		/* Case 3: Traverse to the leftmost child (smallest node) and keep track of its parent. 
            - If the smallest node does not have a right child, make the left child of the smallest node's parent - to be null.
            - If the smallest node has a right child, make that the left child of the smallest node's parent.
            - Delete the smallest node.*/
            parent->left = min_node->right;

            // Correct height of ancestors of "min_node".
            fix_height(min_node); 
			
            // Update pointers to remove "min_node" from the tree.
            min_node = nullptr;  
        
            delete min_node; 
		}

	} else {
        Node* tmp = root_;
         
		root_ = root_->right; 

        // Correct height of ancestors of "tmp".
        fix_height(tmp);
		
        // Update pointers to remove "tmp" from the tree.
        tmp = nullptr;  

        delete tmp;
	} 
}

/* There are three steps to the process of erasing a node:
    -  Step 1: Locate node holding key 'k', simply return if k is not in tree. Let 'node_to_remove' be a pointer to the node to be removed.
    -  Step 2: Find a node, replacement, to replace node_to_remove. We break this down into 3 cases:
        -  Case 1: 'node_to_remove' has no right child. 
        -  Case 2: 'node_to_remove' has no left child.
        -  Case 3: 'node_to_remove' has both children; in this case replacement is successor of node_to_remove. 
        
        There is a further instance of Case 3 that needs special handling. This is where replacement is the right child of node_to_remove. */
template <typename T>
void BST<T>::erase(T k) {
    // Find the node with search value that matches key "k" in the binary search tree.
    Node* node_to_remove = find(k); // Help variable. 
    Node* parent = nullptr; // The parent node.

    // If the node isn't found, there's nothing to delete.
    if (node_to_remove == nullptr) {
        return;
    }

    // Case 1: "node_to_remove" has no children nodes.
    if (node_to_remove->left == nullptr && node_to_remove->right == nullptr) {
        // If "node_to_remove" is the root node, make the root null.
        if (node_to_remove == root_) {
            root_ = nullptr;
            
            return;
        }

        // The parent is made equal to "node_to_remove", as it was set by "find(k)".
        parent = node_to_remove;

        // Delete "node_to_remove" from its parent, by making its children null.
        if (parent->left == node_to_remove) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }

        return;
    }

    /* Case 2: "node_to_remove" has one child node. 
        If it's true that the left child of "node_to_remove" isn't null, then "node_to_remove" has a left child. */
    if (node_to_remove->right == nullptr) {
        // If "node_to_remove" is the root node, make the root null.
        if (node_to_remove == root_) {
            root_ = root_->left;
            
            return;
        }

        // The parent is made equal to "node_to_remove", as it was set by "find(k)".
        parent = node_to_remove;

        // Link the left child of "node_to_remove" to its parent child.
        if (parent->left == node_to_remove) {
            parent->left = node_to_remove->left;
        } else {
            parent->right = node_to_remove->left;
        }

        return;
    }

    // If it's true that the right child of "node_to_remove" isn't null, then "node_to_remove" has a right child.
    if (node_to_remove->left == nullptr) {
        // If "node_to_remove" is the root node, make the root null.
        if (node_to_remove == root_) {
            root_ = root_->right;
            
            return;
        }

        // The parent is made equal to "node_to_remove", as it was set by "find(k)".
        parent = node_to_remove;

        // Link the right child of "node_to_remove" to its parent child.
        if (parent->left == node_to_remove) {
            parent->left = node_to_remove->right;
        } else {
            parent->right = node_to_remove->right;
        }

        return;
    }

    /* Case 3: The node has two children, and the successor of "node_to_remove" must be found. 
    The successor of "node_to_remove" is as follows: move one step to the right, and then all the way left.
    This is all done, while considering that the successor of "node_to_remove" doesn't have a left child. */
    if (node_to_remove->right->left == nullptr) {
        node_to_remove->key = node_to_remove->right->key; // Replace the "node_to_remove" key value.
        node_to_remove->right = node_to_remove->right->right; // Replace the right subtree.

        return;
    }

    Node* successor; // The successor node.
    
    successor = node_to_remove->right; // Move right just once.
    
    Node* successor_parent = node_to_remove; // We must also know the parent of the successor node.

    // Find the successor node of "node_to_remove", and the successor's parent node.
    while (successor->left != nullptr) {
        successor_parent = successor; // Track the successor's parent.
        successor = successor->left;
    }

    node_to_remove->key = successor->key; // Replace "node_to_remove"'s information with the successor's information.
    successor_parent->left = successor->right; // Link the right tree to the parent's left.

    // Fix the heights from the bottom-most node affected by the changes.
    fix_height(node_to_remove);  

    // Update pointers to remove "node_to_remove" from the tree.
    node_to_remove = nullptr;

    delete node_to_remove;

    // Decrement the size by one. 
    --size_;    
}

/* Assumptions: The node is not nullptr and must have a left child.

There are 3 pairs (parent and child) of pointers to change:
    1) The node's left child becomes "move_up_node's" right child.
    2) The node's original parent becomes "move_up_node's" parent.
    3) The "move_up_node's" right child becomes node. */
template <typename T>
void BST<T>::rotate_right(Node* node) {
    Node* move_up_node = node->left;
    
    if (node == root_) {
        root_ = move_up_node;
    } else if (node == node->parent->left) {
        node->parent->left = move_up_node;
    } else {
        node->parent->right = move_up_node;
    }

    move_up_node->parent = node->parent;
    node->left = node->left->right;
    
    if (node->left) {
        node->left->parent = node;
    }

    move_up_node->right = node;
    node->parent = move_up_node;

    // Correct height of ancestors of node. 
    fix_height(node);
}

// Returns a pointer to the minimum node.
template <typename T>
typename BST<T>::Node* BST<T>::min() {
    if (root_ == nullptr) {
        return root_;
    } else {
        return min(root_);
    }
}

// Returns the pointer to the minimum node in the subtree rooted by node, while assuming that the node is not "nullptr".
template <typename T>
typename BST<T>::Node* BST<T>::min(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    } 

    return node;
}

// Returns a pointer to the node with key "k".
template <typename T>
typename BST<T>::Node* BST<T>::find(T k) {
    Node* node = root_;  

    while (node != nullptr && node->key != k) {
        node = k < node->key ?  node->left : node->right;
    }

    return node;  
}

// Returns the number of keys in the tree.
template <typename T>
unsigned BST<T>::size() {
    return size_;
}

// Prints out the keys in the tree using in-order traversal.
template <typename T>
void BST<T>::print() {
    print(root_);
}

template <typename T>
void BST<T>::print(Node* node) {
    if (node == nullptr) {
        return;
    }

    print(node->left);
    std::cout << node->key << " height " << node->height << '\n';
    print(node->right);
}

/*** Testing functions: ***/

template <typename T>
typename std::vector<T> BST<T>::make_vec() {
    std::vector<T> vec;
    vec.reserve(size_);
    make_vec(root_, vec);
    
    return vec;
}

template <typename T>
void BST<T>::make_vec(Node* node, std::vector<T>& vec) {
    if (node == nullptr) {
        return;
    }

    make_vec(node->left, vec);
    vec.push_back(node->key);
    make_vec(node->right, vec);
}

template <typename T>
void BST<T>::your_postorder_heights(Node* node, std::vector<int>& vec) {
    if (node == nullptr) {
        return;
    }

    your_postorder_heights(node->left, vec);
    your_postorder_heights(node->right, vec);
    vec.push_back(node->height);
}

template <typename T>
int BST<T>::real_postorder_heights(Node* node, std::vector<int>& vec) {
    if (node == nullptr) {
        return -1;
    }

    int left_height = real_postorder_heights(node->left, vec);
    int right_height = real_postorder_heights(node->right, vec);
    int node_height = 1 + std::max(left_height, right_height);
    
    vec.push_back(node_height);
    
    return node_height;
}

template <typename T>
typename std::vector<int> BST<T>::your_postorder_heights() {
    std::vector<int> vec;
    
    vec.reserve(size_);
    your_postorder_heights(root_, vec);
    
    return vec;
}

template <typename T>
typename std::vector<int> BST<T>::real_postorder_heights() {
    std::vector<int> vec;
    
    vec.reserve(size_);
    real_postorder_heights(root_, vec);
    
    return vec;
}

template <typename T>
T BST<T>::get_root_value() {
    if (root_ == nullptr) {
        //std::cout << "Calling get_root_value on empty tree\n";
        T dummy {};
        return dummy;
    } else {
        return root_->key;
    }
}

#endif