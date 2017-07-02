#pragma once

using namespace std;

template <typename T>
class DList {
private:

    //nest node inside the list class to avoid naming conflict
    struct Node {
        // node's data
        T data_;

        //node's links
        Node* next_;
        Node* prev_;

        //node's constructor
        Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr) {
            data_ = data;
            next_ = next;
            prev_ = prev;
        }
    };

    // the head and tail of the list
    Node* front_;
    Node* back_;

    //list size
    int size_;

public:
    //######################  iterator classes #################//;

    //constant iterator class
    class const_iterator {
    protected:
        // current node 
        Node* current_;
        //constructor: using node

        const_iterator(Node* node) {
            current_ = node;
        }
        
        friend class DList<T>;
        
    public:

        // initialize the iterator to the begin
        const_iterator() {
            current_ = nullptr;
        }


        //overload operator ==
        bool operator==(const_iterator rhs) const {
            return current_ == rhs.current_;
        }


        //overload operator !=
        bool operator!=(const_iterator rhs) const {

            //use operator ==
            return !(this->current_ == rhs.current_);
        }


        //overload prefix ++ operator
        const_iterator operator++() {
            current_ = current_->next_;
            return *this;
        }


        //overload postfix ++ operator
        const_iterator operator++(int) {

            //save the current iterator to temp
            const_iterator temp = *this;

            //use prefix ++ operator to increase current iterator
            ++(*this);

            //return old one
            return temp;
        }


        // overload prefix -- operator
        const_iterator operator--() {
            current_ = current_->prev_;
            return *this;
        }

        //overload postfix -- operator
        const_iterator operator--(int) {

            //save the current iterator to temp
            const_iterator temp = *this;

            //use prefix -- operator to increase current iterator
            --(*this);

            //return old one
            return temp;
        }

        //overload pointer dereference operator *
        const T& operator*() const {
            return current_->data_;
        }
        
        // getter
        Node* getCurrent() {
            return current_;
        }
    };


    // Non-constant iterator class
    class iterator : public const_iterator {
    protected:

        friend class DList<T>;

        //constructor: using node
        iterator(Node* node) : const_iterator(node) {}

    public:
        
        // default constructor
        iterator() {
            this->current_ = nullptr;
        };

        //overload operator ==
        bool operator==(iterator rhs) {
            return this->current_ == rhs.current_;
        }


        //overload operator !=
        bool operator!=(iterator rhs) {
            //use operator ==
            return !(this->current_ == rhs.current_);
        }

        //overload pointer dereference operator *
        T& operator*() {
            return (this->current_)->data_;
        }


        //overload prefix ++ operator
        iterator operator++() {
            this->current_ = this->current_->next_;
            return *this;
        }

        //overload postfix ++ operator
        iterator operator++(int) {

            //save the current iterator to temp
            iterator temp(this->current_);

            //increase current iterator

            (this->current_) = (this->current_)->next_;

            //return old one
            return temp;
        }


        // overload prefix -- operator
        iterator operator--() {
            this->current_ = this->current_->prev_;
            return *this;
        }

        //overload postfix -- operator
        iterator operator--(int) {

            //save the current iterator to temp
            iterator temp = *this;

            //decrease current iterator
            this->current_ = this->current_->prev_;

            //return old one
            return temp;
        }



        //getter function
        Node* getCurrent() {
            return this->current_;
        }
    };





    // non constant iterator point to first element;
    iterator begin() {
        return iterator(front_->next_);
    }

    // return the one after last element(back sentinel); 
    iterator end() {
        return iterator(back_);

    };

    // find the first node iterator
    const_iterator begin() const {
        return const_iterator(front_->next_);
    }

    //return the one after last element(back sentinel); 
    const_iterator end() const {
        return const_iterator(back_);
    }

    //add data to front of list
    void push_front(const T& data) {
        Node* newNode = new Node(data, front_->next_, front_);
        (front_->next_)->prev_ = newNode;
        front_->next_ = newNode;
        size_++;
    }

    //add data to back of list
    void push_back(const T& data) {

        Node* newNode = new Node(data, back_, back_->prev_);

        
        (back_->prev_)->next_ = newNode;
        (back_->prev_) = newNode;
        size_++;
    }

    //remove first element
    void pop_front() {
        //check if list is empty, if not do "pop front"
        if (!empty()) {
            //find the front node
            Node* temp = front_->next_;

            front_->next_ = temp->next_;
            (temp->next_)->prev_ = front_;

            delete temp;
            size_--;
        }
    }

    //remove last element
    void pop_back() {
        //check if list is empty, if not do "pop back"
        if (!empty()) {
            //find the last node
            Node* temp = back_->prev_;

            back_->prev_ = temp->prev_;
            (temp->prev_)->next_ = back_;

            delete temp;
            size_--;
        }
    }

    // Insert a new node before the iterator loc
    iterator insert(iterator loc, const T& data) {

        //construct a new node
        Node* newNode = new Node(data);

        //insert

        if (loc == end()) { // end() iterator is special situation need to deal
            newNode->next_ = back_;
            newNode->prev_ = back_->prev_;
            (back_->prev_)->next_ = newNode;
            back_->prev_ = newNode;

            //increase list size by 1
            ++size_;

            return iterator(newNode);
        } else {
            newNode->next_ = loc.getCurrent();
            newNode->prev_ = loc.getCurrent()->prev_;
            (loc.getCurrent()->prev_)->next_ = newNode;
            (loc.getCurrent()->prev_) = newNode;

            //increase list size by 1
            ++size_;


            //return the iterator pointer to the new elements
            return --loc;
        }
    };


    // Erase a node from a list
    void erase(iterator it) {

        // Check if list is a empty list or if it iterator == end(), 
        // if not , erase, Otherwise, do noting
        if (!empty() && it != end()) {
            // a temporary pointer to current node
            Node* cur = it.getCurrent();
            (cur->prev_)->next_ = cur->next_;
            (cur->next_)->prev_ = cur->prev_;

            //delete the node
            delete cur;

            //decrease list size by 1
            size_--;
        }
    };

    // Erase elements from first to last
    void erase(iterator first, iterator last) {
        // Erase from first to the one before last

        bool isEmpty = empty();
        if (!isEmpty) {
            while (first != last && first != end()){ 
                iterator next;
                next.current_ = first.current_->next_;
                erase(first);                
                first = next;
            }
            
        }
    }

    // Find the first occurrence  that its data is same with the data searching
    // if data is not found, return end()
    iterator search(const T& data) {
        iterator result = end();
        for (iterator it = begin(); it != end(); it++) {
            if (*it == data) result = it;
        }

        return result;

    };

    // Find the first occurrence  that its data is same with the data searching
    // if data is not found, return end()
    const_iterator search(const T& data) const {
        const_iterator result = end();
        for (const_iterator it = begin(); it != end(); it++) {
            if (*it == data) result = it;
        }

        return result;
    };


    // return true if the size of list is 0;
    bool empty() const {
        return (size_ == 0);
    };
    
    //return the size of the list
    int size() const {
        return size_;
    };

    //destructor 
    ~DList() {
        //using erase function to empty list
        erase(begin(), end());
        
        //delete sentinel nodes       
        delete front_;
        delete back_;
    };

    //constructor
    DList() {
        front_ = new Node(T{}, nullptr, nullptr);
        back_ = new Node(T{}, nullptr, nullptr);
        front_ ->next_ = back_;
        back_ ->prev_ = front_;

        size_ = 0;
    }


    // Copy constructor with const parameter: using assignment operator
    DList(const DList& dl) {

        //initialize sentinels
        front_ = new Node(T{}, nullptr, nullptr);
        back_ = new Node(T{}, nullptr, nullptr);
        front_ ->next_ = back_;
        back_ ->prev_ = front_;

        size_ = 0;

        // using assignment operator
        *this = dl;

    };



    // Copy constructor without const parameter: using assignment operator
    DList(DList& dl) {

        //initialize sentinels
        front_ = new Node(T{}, nullptr, nullptr);
        back_ = new Node(T{}, nullptr, nullptr);
        front_ ->next_ = back_;
        back_ ->prev_ = front_;

        size_ = 0;

        // using assignment operator
        *this = dl;

    };

    // Assignment operator overload with const parameter
    DList& operator=(const DList& dl) {

        // Check if it is a self assignment, if it is self assignment do nothing
        if (this != &dl) {
            if (!empty()) {
                //empty the list
                erase(begin(), end());
                size_ = 0;
            }


            //copy the nodes
            for (iterator it = dl.begin(); (it.getCurrent()) != dl.back_; it++) {
                push_back(*it);
            }

            //copy size_
            size_ = dl.size_;

        }
        // do nothing for self assignment

        return *this;
    };


    // Assignment operator overload without const parameter
    DList& operator=(DList& dl) {

        // Check if it is a self assignment, if it is self assignment do nothing
        if (this != &dl) {
            if (!empty()) {
                //empty the list
                erase(begin(), end());
                size_ = 0;
            }


            //copy the nodes
            for (iterator it = dl.begin(); it != dl.end(); it++) {
                push_back(*it);
            }

            //copy size_
            size_ = dl.size_;

        }
        // do nothing for self assignment
        return *this;
    };

    //move constructor
    DList(DList&& dl) {

        //initialize sentinels
        front_ = new Node(T{}, nullptr, nullptr);
        back_ = new Node(T{}, nullptr, nullptr);
        front_ ->next_ = back_;
        back_ ->prev_ = front_;

        size_ = 0;

        *this = move(dl);
    };


    //move assignment
    DList& operator=(DList&& dl) {
        // Check if it is a self assignment, if it is self assignment do nothing
        if (this != &dl) {
            if (!empty()) { // if this list is not empty, empty it first

                //empty the list
                erase(begin(), --end());
            }


            //link current object to  dl's nodes 
            front_->next_ = dl.front_->next_;
            (dl.front_->next_)->prev_ = front_;
            back_->prev_ = dl.back_ -> prev_;
            (dl.back_ -> prev_)->next_ = back_;

            //make dl empty by link two sentinel nodes together
            dl.front_->next_ = dl.back_;
            dl.back_->prev_ = dl.front_;


            //copy size_
            size_ = dl.size_;

            //dl size now is 0
            dl.size_ = 0;


        }// do nothing for self assignment

        return *this;
    };

};