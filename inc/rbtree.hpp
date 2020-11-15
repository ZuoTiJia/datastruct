#include "rbnode.hpp"

template <typename K, typename T=K>
class RB_Tree {
    public:
        RB_Tree():root(nullptr) {};
        ~RB_Tree();
        void insertNode(K key_, T val_);
        void eraseNode(K key_);
        T find(K key_);

    private:
        rb_node<K, T> *root;
        void delete_case1(rb_node<K, T> *cur);
        void leftRotate(rb_node<K, T> *cur);
        void rightRotate(rb_node<K, T> *cur);
        rb_node<K, T> *findNode(K key_);
        rb_node<K, T> *replaceNode(rb_node<K, T> *cur);
        void eraseFix(rb_node<K, T> *cur);
        void replace(rb_node<K, T> *old, rb_node<K, T> *new_node);
        bool normalInsert(rb_node<K, T> *cur);
};
//把二叉树转链式栈
//迭代实现
template <typename K, typename T>
RB_Tree<K, T>::~RB_Tree() {
    if(root == root) 
        return ;
    rb_node<K, T> *top = nullptr;
    rb_node<K, T> *next, *temp;


    next = root->left;
    top = root;
    root->left = nullptr;

    while(top != nullptr) {
        while(next != nullptr) {
            temp = next;
            next = next->left;
            temp->left = top;
            top = temp;
        }
        next = top;
        if(next->right == nullptr) {
            
            top = top->left;
            delete next;
            next = nullptr;
        } else {

            temp = next;
            next = next->right;
            temp->right = nullptr;
        }
    }
    root = nullptr;
}
template <typename K, typename T>
bool RB_Tree<K, T>::normalInsert(rb_node<K, T> *cur) {
    if(root == nullptr) {
        root = cur;  
        return true;
    } 
    rb_node<K, T> *p = root;
    rb_node<K, T> *parent;
    while(p != nullptr) {
        parent = p;
        if(cur->key < p->key)
            p = p->left;
        else
            p = p->right;
    }
    if(cur->key < parent->key)
        parent->left = cur;
    else if(cur->key > parent->key)
        parent->right = cur;
    else {
        //已存在key值,替换退出
        parent->val = cur->val;
        delete cur;
        return false;
    }
    cur->parent = parent;
    return true;
}
template <typename K, typename T>
void RB_Tree<K, T>::insertNode(K key_, T val_) {
    rb_node<K, T> *cur = new rb_node<K, T>(key_, val_);
    //普通的二叉树插入
    //当存在key值替换返回
    if(!normalInsert(cur)) {
        return;
    }
    while(1) {
        if(cur == root) {
            //情形1 根节点
            cur->color = RB_BLACK;
            return;
        } else {
            //情形2 父节点是黑
            if(cur->parent->color == RB_BLACK)
                return;
            else {
                //先求叔叔节点
                rb_node<K, T> *uncle;
                if(cur->parent == cur->parent->parent->left)
                    uncle = cur->parent->parent->right;
                else 
                    uncle = cur->parent->parent->left;
                //情形3 父节点是红色 叔叔节点是红色
                if(uncle!=nullptr && uncle->color == RB_RED) {
                    cur->parent->color = RB_BLACK;
                    uncle->color = RB_BLACK;
                    cur->parent->parent->color = RB_RED;
                    cur = cur->parent->parent;
                    continue;
                } else {
                    //情形4 父节点红 叔叔节点黑或null 自己是左（右）儿子，父亲是右（左）儿子
                    if( cur == cur->parent->left 
                        && cur->parent == cur->parent->parent->right) {
                        rightRotate(cur->parent);
                        cur = cur->right;
                    } else if(  cur == cur->parent->right
                                && cur->parent == cur->parent->parent->left) {
                        leftRotate(cur->parent);
                        cur = cur->left;
                    }
                    //情形5 父节点红 叔叔节点黑或null 自己是左（右）儿子 ， 父亲是左（右）儿子
                    cur->parent->color = RB_BLACK;
                    cur->parent->parent->color = RB_RED;
                    if( cur == cur->parent->left 
                        && cur->parent == cur->parent->parent->left) {
                        rightRotate(cur->parent->parent);
                    } else if(  cur == cur->parent->right
                                && cur->parent == cur->parent->parent->right) {
                        leftRotate(cur->parent->parent);
                    }
                    return ;
                }
            }
        }
    }
}

template <typename K, typename T>
void RB_Tree<K, T>::leftRotate(rb_node<K, T> *cur) {
    
    if(cur == root) 
        root = cur->right;
    else if(cur == cur->parent->left) 
        cur->parent->left = cur->right;
    else 
        cur->parent->right = cur->right;
    
    cur->right->parent = cur->parent;

    rb_node<T, K> *p = cur->right->left;
    cur->right->left = cur;
    cur->parent = cur->right;
    
    cur->right = p;
    if(p != nullptr)
        p->parent = cur;

}
template <typename K, typename T>
void RB_Tree<K, T>::rightRotate(rb_node<K, T> *cur) {
    
    if(cur == root) 
        root = cur->left;
    else if(cur == cur->parent->left)
        cur->parent->left = cur->left;
    else  
        cur->parent->right = cur->left;
    cur->left->parent = cur->parent;

    rb_node<T, K> *p = cur->left->right;
    cur->left->right = cur;
    cur->parent = cur->left;

    cur->left = p;
    if(p != nullptr)
        p->parent = cur;
    
}


template <typename K, typename T>
rb_node<K, T> *RB_Tree<K, T>::findNode(K key_) {
    if(root == nullptr) 
        return nullptr;
    rb_node<K, T> *cur = root;
    while(cur) {
        if(key_ == cur->key)
            return cur;
        if(key_ > cur->key)
            cur = cur->right;
        else 
            cur = cur->left;
    }
    return cur;
}
template <typename K, typename T>
T RB_Tree<K, T>::find(K key_) {
    rb_node<K, T> *p = findNode(key_);
    if(p == nullptr)
        throw "没有这个元素";
    return p->val;
}
template <typename K, typename T>
void RB_Tree<K, T>::replace(rb_node<K, T> *old, rb_node<K, T> *new_node) {
    if(old == new_node)
        return;
    old->key = new_node->key;
    old->val = new_node->val;
}
template <typename K, typename T>
rb_node<K, T> *RB_Tree<K, T>::replaceNode(rb_node<K, T> *cur) {
    //如果只有一个非空节点 直接替换.,父节点一定是黑的一定满足红黑树性质
    rb_node<K, T> *p = cur;
    while(1) {
        if(p->left == nullptr && p->right == nullptr)
            break;
        else if(p->left != nullptr && p->right == nullptr)  
            p = p->left;
        else if(p->left == nullptr && p->right != nullptr) 
            p = p->right;
        else if(p->left != nullptr && p->right != nullptr) {
            p = p->right;
            while(p->left != nullptr)
                p = p->left;
        }
    }
    replace(cur, p);
    return p;
}
template <typename K, typename T>
void RB_Tree<K, T>::eraseFix(rb_node<K, T> *cur) {
    while(1) {
        //是根修复完毕
        if(cur == root)
            break;
        //是红修复完毕
        if(cur->color == RB_RED)
            break;
        //如果是黑节点可以断言必有兄弟节点
        rb_node<K, T> *brother;
        if(cur == cur->parent->left) {
            brother = cur->parent->right;
            //兄弟是黑的
            if(brother->color == RB_BLACK) {
                //可以断定兄弟节点只有一个子节点， 那么这个子节点一定是红的
                if(brother->left != nullptr && brother->right == nullptr) {
                    brother->color = RB_RED;
                    brother->left->color = RB_BLACK;
                    rightRotate(brother);
                    continue;
                }
                //兄弟有右儿子 且是红色的， 修复后退出
                if(brother->right != nullptr && brother->right->color == RB_RED) {
                    brother->color = brother->parent->color;
                    cur->parent->color = RB_BLACK;
                    brother->right->color = RB_BLACK;
                    leftRotate(cur->parent);
                    break ;
                }
                //兄弟没有子节点
                if  ((brother->left == nullptr && brother->right == nullptr) ||
                    (brother->left->color == RB_BLACK && brother->right->color == RB_BLACK )) {
                    brother->color = RB_RED;
                    cur = cur->parent;
                    continue;
                }
            } else {
                //如果兄弟节点是红色， 可以断定兄弟节点必有两个黑色节点，父亲节点必定是黑
                brother->color = RB_BLACK;
                brother->left->color = RB_RED;
                leftRotate(cur->parent);
                break;
            }
        } else {
            brother = cur->parent->left;
            if(brother->color == RB_BLACK) {
                if(brother->left == nullptr && brother->right != nullptr) {
                    brother->color = RB_RED;
                    brother->right->color = RB_BLACK;
                    leftRotate(brother);
                    continue;
                }
                if(brother->left != nullptr && brother->left->color == RB_RED) {
                    brother->color = brother->parent->color;
                    cur->parent->color = RB_BLACK;
                    brother->left->color = RB_BLACK;
                    rightRotate(cur->parent);
                    break;
                }
                if((brother->left == nullptr && brother->right == nullptr) ||
                    (brother->left->color == RB_BLACK && brother->right->color == RB_BLACK) ) {
                    brother->color = RB_RED;
                    cur = cur->parent;
                    continue;
                }
                
            } else {
                brother->color = RB_BLACK;
                brother->right->color = RB_RED;
                rightRotate(cur->parent);
                break;
            }
        }
    }
    cur->color = RB_BLACK;
}
template <typename K, typename T>
void RB_Tree<K, T>::eraseNode(K key_) {
    rb_node<K, T> *cur, *replace_node;
    cur = findNode(key_);
    if(cur == nullptr)
        return ;
    //转化为删除叶子节点的场景
    cur = replaceNode(cur);
    //修复
    eraseFix(cur);
    if(cur == root)
        root = nullptr;
    else if(cur == cur->parent->left) 
        cur->parent->left = nullptr;
    else if(cur == cur->parent->right) 
        cur->parent->right = nullptr;
    delete cur;
}
