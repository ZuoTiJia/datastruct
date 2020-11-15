#ifndef __MYLIST__
#define __MYLIST__

template <typename T>
class node;
template <typename T>
class Iter;
template <typename T>
class List;


template <typename T>
class node {
    friend class Iter<T>;
    friend class List<T>;
    T val;
    node<T> *prev;
    node<T> *next;
    public:
    node(T value);
    node();
};


template <typename T>
class Iter {
    friend class List<T>;
    public:
        Iter(node<T>*);
        Iter<T>& operator ++();
        Iter<T>& operator --();
        Iter<T> operator ++(int);
        Iter<T> operator --(int);
        T& operator *();
        T* operator ->();
        // Iter<T>& operator+=(int);
        // Iter<T>& operator-=(int);
        bool operator !=(const Iter<T>& b);
        bool operator ==(const Iter<T>& b);
    private:
        node<T> *cur;
};


template <typename T>
class List {

    friend class Iter<T>;
    
    private:
        node<T> *head;
        int number;
    public:
        List();
        ~List();
        void push_back(T);
        void push_front(T);
        void pop_back();
        void pop_front();
        void clear();
        void swap(Iter<T> a, Iter<T> b);
        Iter<T>& insert(Iter<T>&, T);
        Iter<T>& erase(Iter<T>&); 
        Iter<T> begin();
        Iter<T> end();
        int node_number() {return number;}
};
template <typename T>
node<T>::node(T value):val(value) {
    next = prev = this;
}

template <typename T>
node<T>::node() {
    next = prev = this;
}

//=========================================

template <typename T>
Iter<T>::Iter(node<T>* p) {
    cur = p;
}

template <typename T>
Iter<T>& Iter<T>::operator ++() {
    cur = cur->next;
    return *this;
}


template <typename T>
Iter<T> Iter<T>::operator ++(int) {
    Iter<T>  tmp(*this);
    operator++();
    return tmp;
}

template <typename T>
Iter<T>& Iter<T>::operator --() {
    cur = cur->prev;
    return *this;
}


template <typename T>
Iter<T> Iter<T>::operator --(int) {
    Iter<T> tmp(*this);
    cur = cur->prev;
    return tmp;
}


template <typename T>
T& Iter<T>::operator *() {
    return cur->val;
}


template <typename T>
T* Iter<T>::operator ->() {
    return cur;
}

template <typename T>
bool Iter<T>::operator!= (const Iter<T>& b) {
    return cur != b.cur;
}
template <typename T>
bool Iter<T>::operator== (const Iter<T>& b) {
    return cur == b.cur;
}
// template <typename T>
// Iter<T>& Iter<T>::operator+=(int step) {
//     for(int i=0; i<step; i++)
//         (*this)++;
//     return *this;
// }
//=================================

template <typename T>
List<T>::List() {
    head = new node<T>();
    number = 0;
}

template <typename T>
List<T>::~List() {
    clear();
    delete head;
}

template <typename T> 
void List<T>::push_back(T value) {
    node<T> *new_node = new node<T>(value);
    new_node->prev = head->prev;
    new_node->next = head;
    head->prev->next = new_node;
    head->prev = new_node;
    number++;
}

template <typename T>
void List<T>::push_front(T value) {
    node<T> *new_node = new node<T>(value);
    new_node->prev = head;
    new_node->next = head->next;
    head->next->prev = new_node;
    head->next = new_node;
    number++;
}

template <typename T>
void List<T>::pop_back() {
    if(number == 0)
        return;
    node<T> *pop_node = head->prev;
    head->prev = pop_node->prev;
    pop_node->prev->next = head;
    delete pop_node;
    number--;
}

template <typename T>
void List<T>::pop_front() {
    if(number == 0)
        return;
    node<T> *pop_node = head->next;
    head->next = pop_node->next;
    head->next->prev = head;

    delete pop_node;
    number--;
}

template <typename T>
void List<T>::swap(Iter<T> a, Iter<T> b) {
    T t;
    if(a==end() || b==end())
        return;
    t = *a;
    *a = *b;
    *b = t;
}

template <typename T>
Iter<T>& List<T>::insert(Iter<T>& p, T value) {
    node<T> *new_node = new node<T>(value);
    number++; 
    new_node->next = p.cur;
    new_node->prev = p.cur->prev;
    new_node->prev->next = new_node;
    new_node->next->prev = new_node;
    p.cur = new_node;
    return p;
}


template <typename T>
Iter<T>& List<T>::erase(Iter<T>& p) {
    if(p.cur == head) 
        return p;
    node<T> *delete_node;
    delete_node = p.cur;
    p.cur->next->prev = p.cur->prev;
    p.cur->prev->next = p.cur->next;
    p.cur = p.cur->next;
    delete delete_node;
    number--;
    return p;
}
template <typename T>
Iter<T> List<T>::begin() {
    return Iter<T>(head->next);
}
template <typename T>
Iter<T> List<T>::end() {
    return Iter<T>(head);
}
template <typename T>
void List<T>::clear() {
    for(Iter<T> i=begin(); i!=end();) {
        erase(i);
    }
    number = 0;
}
#endif