#ifndef MY_FORWARD_LIST_HPP
#define MY_FORWARD_LIST_HPP

#include <algorithm>

template <typename T>
class Forward_list {
public:
    class Node {
    public:
        // A node that will hold data of type T.
        T data{};
        
        // The "next" variable will point to the next node in the list, and is initialised to "nullptr".
        Node* next = nullptr;

        // The default constructor.
        Node(){}

        /* This is a constructor that takes the T data to be copied into the data member variable. 
        There is an optional second argument which is used to update the next pointer. 
        This defaults to "nullptr" if the constructor is called with just one argument. */
        Node(T input_data, Node* next_node = nullptr) {
            data = input_data;
            next = next_node;
        }

        // The destructor.
        ~Node(){}
    };

private:
    // Private member variables for Forward_list. The trailing underscore is a stylistic choice to distinguish these as private member variables.
    unsigned size_ = 0;
    Node* head_ = nullptr;

public:
    /* The public member functions of the Forward_list class. */
    // Default constructor.
    Forward_list();
   
    // The destructor.
    ~Forward_list();

    // The copy constructor.
    Forward_list(const Forward_list<T>& other);

    // The constructor from initializer list.
    Forward_list(std::initializer_list<T> input);

    // Add an element to the front of the list.
    void push_front(const T& data);

    // Add an element at a specified position of the list (Extra function #1).
    void push_position(const T& data, int position);

    // Remove the first element of the list.
    void pop_front();

    // Remove an element from a specified position of the list (Extra function #2).
    void pop_position(const T& position);

    // Return the data held in the first item of the list. This function doesn't change the list, which is why it is declared "const".
    T front() const;

    // Print out all the data in the list in sequence.
    void display() const;

    // Outputs if the list is empty or not.
    bool empty() const;

    // Outputs the size of the list.
    unsigned size() const;

    // Merge two sorted lists, "*this" and "other".
    void merge(Forward_list& other);

    // Split "*this" into its first half, which becomes the new "*this", and its second half which is returned.
    Forward_list split();

    // The sort function uses the helper functions "merge" and "split".
    void sort();

private:
    // Sort is implemented via a recursive merge sort.
    void merge_sort(Forward_list&);
};

// The default constructor.
template <typename T>
Forward_list<T>::Forward_list() {
}

// The destructor.
template <typename T>
Forward_list<T>::~Forward_list() {
    while (head_ != nullptr) { // While the list isn't empty. 
        Node* tmp = head_;

        head_ = head_->next; // Point the head pointer of the list to the next node.
        
        delete tmp; // Deallocate the memory allocated to the "tmp" variable.
        
        --size_; // Decrease the size of the list by one.
    }
}

// The copy constructor.
/* The copy constructor takes as argument a const reference to a another Forward_list "other". The "const" means that the function will not modify "other".
The function makes a "deep copy" of the other list, i.e. creating a new node for every node in other and copying the data of other into these new nodes. */  
template <typename T>
Forward_list<T>::Forward_list(const Forward_list& other) {
    if (other.head_ != nullptr) { // If the "other" list isn't empty.
        head_ = new Node(other.head_->data); // Point the head pointer to head's data of the other list being copied.

        Node* current = head_; // Assign the current node of the first list, as the head pointer of the first list.
        Node* object_head = other.head_; // Assign "object_head" as the head pointer of the second list.
        Node* current2 = object_head; // Assign the current node of the second list, as the head pointer of the second list. 

        /* While the second list isn't empty: 
            - Go through and copy each node's data and size in the first list. 
            - Transfer the copied data and size of each node from the first list, to the nodes in the second list. */  
        while (current2->next != nullptr) {
            current->next = new Node(current2->next->data);
            current2 = current2->next;
            current = current->next;
            size_ = other.size_;
        }

    } else {
        head_ = nullptr; // The list is empty, so the head pointer is pointed to a memory address of zero.
    }
}

// The constructor from an initializer list.
/* This implements the functionality of, for example, "std::forward_list<int> my_list = {1,2,3}", which creates a new linked list where the first node holds 1, second 2, and third 3.
The "{1,2,3}" here is of type "std::initializer_list<int>" and this is the argument to this constructor (with data of type "T" rather than just int).
The elements of a "std::initializer_list" are accessed, via an iterator. */
template <typename T>
Forward_list<T>::Forward_list(std::initializer_list<T> input) {
    for (auto it = input.begin(); it != input.end(); ++it) { // Iterate through the list that's the size of what the user has inputted. 
        Node* new_node = new Node(*it); // Create a new node, which is pointed to the start of the list. 
        
        if (empty()) {
            head_ = new_node; // Point the head pointer of the empty list to the newly created node.
        } else {
            Node* tmp = head_; // Assign "tmp" as the head pointer. 

            // Keep pointing the head pointer of the list to the next node, until the end of the list is reached.
            while (tmp->next != nullptr) {
                tmp = tmp->next;
            }

            tmp->next = new_node; // Point the node after the current head pointer, to the newly created node (i.e. the end of the list). 
        }

        size_++; // Increase the size of the list by one.
    }
}

// Add the element to front of list.
template <typename T>
void Forward_list<T>::push_front(const T& data) {
    Node* new_node = new Node(); // Create a new node. 
    
    new_node->data = data; // Point the newly created node's data to the data of the list.
    new_node->next = head_; // Point the node after "new_node", to the head pointer. 
    head_ = new_node; // Point the head pointer to the newly created node. 
    
    size_++; // Increase the size of the list by one.
}

// Add the element to a specified position in the list (Extra function #1).
template <typename T>
void Forward_list<T>::push_position(const T& data, int position) {
    Node* previous_node = new Node(); // The node before the current node, in the list.
    Node* current = new Node(); // The current node in the list.
    Node* tmp = new Node(); // A temporary node. 
    
    current = head_; // Point the current node in the list, to the head pointer.
    
    /* Going through each node of the list: 
        - Point the previous node to the current node.
        - Point the current node to the next node in the list. */
    for (int i = 1; i < position; i++) {
        previous_node = current;
        current = current->next;
    }

    tmp->data = data; // Point the data of "tmp", to the data of the list. 
    previous_node->next = tmp; // Point the node after the previous node, to the data of the list.
    tmp->next = current; // Point the node after "tmp" to the current node of the list. 

    // Deallocate the memory allocated to "previous_node", "current" and "tmp".
    delete previous_node;
    delete current;
    delete tmp;

    size_++; // Increase the size of the list by one.
} 

// Remove the front element of the list. If the list is empty, don't do anything.
template <typename T>
void Forward_list<T>::pop_front() {
    if (!empty()) {
        Node* tmp = new Node(); // Create a new node, named "tmp". 
        
        // Assign "tmp" as the head pointer, and point it to the next node in the list.  
        tmp = head_;
        head_ = head_->next;
        
        delete tmp; // Deallocate the memory allocated to the "tmp" variable.
        
        size_--; // Decrease the size of the list by one.
    }

    return;
}

// Remove the element from a specified position of the list. If the list is empty, don't do anything (Extra function #2). 
template <typename T>
void Forward_list<T>::pop_position(const T& position) {
    if (!empty()) {
        Node* current = new Node(); // The current node in the list.
        Node* previous_node = new Node(); // The node before the current node, in the list.
    
        current = head_; // Point the current node of the list to the head pointer.
    
        /* Going through each node of the list: 
            - Point the previous node to the current node.
            - Point the current node to the next node in the list. */
        for (int i = 1; i < position; i++) {
            previous_node = current;
            current = current->next;
        }

        previous_node->next = current->next; // Point the node after the previous node, to the node after the current node.  

        size_--; // Decrease the size of the list by one.
    }
    
    return;
}

// Return the data in the front element of the list. If the list is empty, the behaviour is undefined, and no value is returned. 
template <typename T>
T Forward_list<T>::front() const {
    if (!empty()) {
        return head_->data;
    }

    return 0;
}

// Prints out each element of the list, if it isn't empty.
template <typename T>
void Forward_list<T>::display() const {
    Node* tmp = head_;
    
    while (!empty()) {
        std::cout << tmp->data << " ";
        tmp = tmp->next;
    }
}

// Outputs if the list is empty or not.
template <typename T>
bool Forward_list<T>::empty() const {
    return (head_ == nullptr);
}

// Returns the size of the list.
template <typename T>
unsigned Forward_list<T>::size() const {
    return size_;
}

/* The split function splits "*this" into its first half, which becomes the new "*this", and its second half is returned if the the size of "*this" is "n". 
Then, after "split", the size of "*this" will be "ceiling(n / 2)", and the size of the returned list will be "floor(n / 2)". */
template <typename T>
Forward_list<T> Forward_list<T>::split() {
    Forward_list<T> other; // A second list is declared.

    Node* tmp = head_; // Head pointer for the first list.
    Node* tmp2 = head_; // Head pointer for the second list. 
    
    /* While the end of the list isn't reached, for each node, and every second node in the list: 
        - Point the head of the first list to two nodes forward in its list.
        - Point the head of the second list to the next node in its list. */
    while (tmp->next != nullptr && tmp->next->next != nullptr) {   
        tmp = tmp->next->next;   
        tmp2 = tmp2->next;   
    } 

    // Point the head pointer of the second list to the next node of its list, which is the last node. 
    other.head_ = tmp2->next;   
    tmp2->next = nullptr;

    // Halve the size of the second list, then perform the difference of the two lists' size - so that the first list's size is equal to the second list's size.  
    other.size_ = size_ / 2; 
    size_ = size_ - other.size_;   
    
    return other; 
}

/* For this function it is assumed that both "*this" and the input Forward_list "other" are already sorted.
The function merges the two lists into sorted order, and the merger becomes the new "*this". */
template <typename T>
void Forward_list<T>::merge(Forward_list& other) {
    Node* tmp = head_; // Head pointer for the first list.
    Node* tmp2 = other.head_; // Head pointer for the second list.

    Node* dummy_node = new Node(); // Create a new node.
    Node* previous_node = dummy_node; // Point the previous node in the list to the newly created node. 

    while (tmp != nullptr && tmp2 != nullptr) {
        /* If the head pointer's data of the first list is smaller than the data of the second list's head pointer:
            - Point the node after the previous node, to the head pointer of the first list.
            - Point the head pointer of the first list, to the node after it.
           
           Else:  
            - Point the node after the previous node, to the head pointer of the second list.
            - Point the head pointer of the second list, to the node after it. */
        if (tmp->data < tmp2->data) {
            previous_node->next = tmp;
            tmp = tmp->next;
        } else {
            previous_node->next = tmp2;
            tmp2 = tmp2->next;
        }

        previous_node = previous_node->next; // Point the previous node, to the node after it. 
    }

    // If the first list isn't empty, point the node after the previous one, to its head pointer.
    if (tmp != nullptr) {
        previous_node->next = tmp;
    }
    
    // If the second list isn't empty, point the node after the previous one, to its head pointer.
    if (tmp2 != nullptr) {
        previous_node->next = tmp2;
    }

    head_ = dummy_node->next; // Point the head pointer to the node after "dummy_node". 
    
    delete dummy_node; // Deallocate the memory allocated to "dummy_node".
    
    // The other list is merged with the first list, so there isn't a head now, as the second list no longer exists.
    other.head_ = nullptr; 
    other.size_ = 0;
}   

/* Recursive implementation of "merge_sort", which involves sorting the two merged lists from the "merge" function. 
If the size of the list is smaller than two, then don't do anything. */  
template <typename T>
void Forward_list<T>::merge_sort(Forward_list& my_list) {
    if (my_list.size() == 0 || my_list.size() == 1) {
        return;
    }

    Forward_list<T> second = my_list.split();
    merge_sort(my_list);
    merge_sort(second);
    my_list.merge(second);
}

// Sorts the list by calling "merge_sort".
template <typename T>
void Forward_list<T>::sort() {
    merge_sort(*this);
}

#endif