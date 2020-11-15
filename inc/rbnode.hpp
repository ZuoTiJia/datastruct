enum node_color {
    RB_RED = 0,
    RB_BLACK = 1
};

template <typename K, typename T=K>
struct rb_node {
    rb_node<T> *left;
    rb_node<T> *right;
    rb_node<T> *parent;
    T val;
    K key;
    node_color color;
    rb_node(K key_, T val_) 
        : key(key_)
        , val(val_)
        , left(nullptr)
        , right(nullptr)
        , parent(nullptr)
        , color(RB_RED) {}  
};