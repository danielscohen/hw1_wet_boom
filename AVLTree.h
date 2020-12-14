
#ifndef BOOM_AVL_TREE_H
#define BOOM_AVL_TREE_H

template <class T>
class AVLTree {

    struct Node{
        Node *father;
        Node *lSon;
        Node *rSon;
        T key;
        int height;

        Node(T key, Node *father);

    };

    Node *root;
    Node *max;
    Node *min;
    Node *iterator;


    Node* lRole(Node *current);
    Node* rRole(Node *current);
    int calcNewHeight(Node *i);
    int bf(Node *i);
    void balancePath(Node *current);
    void updateMax();
    void updateMin();
    void postOrderDelete(Node* current);






public:

    AVLTree();

    ~AVLTree();
    T getNext();
    T get(T key) const;
    T getFirst();
    void insert(T key);
    void remove(T key);
    bool isEmpty() const;
    bool isMember(T key) const;

    bool isLast() const;


};

template <class T>
AVLTree<T>::Node::Node(T key, Node *father) : father(father), lSon(nullptr), rSon(nullptr), key(key),
                                              height(0){}



template <class T>
AVLTree<T>::AVLTree() : root(nullptr), max(nullptr), min(nullptr){}



template <class T>
AVLTree<T>::~AVLTree(){
    postOrderDelete(root);
}

template <class T>
void AVLTree<T>::postOrderDelete(Node* current){
    if(current == nullptr) return;
    postOrderDelete(current->lSon);
    postOrderDelete(current->rSon);
    delete current;
}

template <class T>
T AVLTree<T>::get(T key) const {
    const Node *current = root;
    while(current != nullptr){
        if(*(current->key) == *key) return current->key;
        if(*(current->key) > *key) current = current->lSon;
        else current = current->rSon;
    }
    return nullptr;
}

template <class T>
void AVLTree<T>::insert(T key){

    if(root == nullptr){
        root = new Node(key, nullptr);
        max = root;
        min = root;
        return;
    }



//search for location and then insert node
    Node *current = root;
    while(1) {
        if (*(current->key) == *key) return;
        if (*(current->key) > *key && current->lSon == nullptr) {
            current->lSon = new Node(key, current);
            break;
        } else if (*(current->key) < *key && current->rSon == nullptr) {
            current->rSon = new Node(key, current);
            break;
        } else if (*(current->key) > *key) {
            current = current->lSon;
        } else {
            current = current->rSon;
        }
    }






    //post insertion corrections


    balancePath(current);

    updateMax();
    updateMin();

}

template <class T>
void AVLTree<T>::remove(T key){
    Node *current = root;
    while(current != nullptr && *(current->key) != *key){
        if(*(current->key) > *key) current = current->lSon;
        else current = current->rSon;
    }

    if (current == nullptr) return;
    if (current == root && current->lSon == nullptr && current->rSon == nullptr) {
        delete current;
        root = nullptr;
        max = nullptr;
        min = nullptr;
        return;
    }


    if(current->lSon == nullptr && current->rSon == nullptr){
        current = current->father;
        if (current->lSon != nullptr && *(current->lSon->key) == *key) {
            delete current->lSon;
            current->lSon = nullptr;
        } else {
            delete current->rSon;
            current->rSon = nullptr;
        }
    } else if(current->lSon == nullptr && current == root) {
        root = current->rSon;
        delete current;
        root->father = nullptr;
        current = root;

    } else if(current->lSon == nullptr) {
        Node *toRemove = current;
        current = current->father;
        if (*(current->lSon->key) == *key) {
            current->lSon = toRemove->rSon;
            current->lSon->father = current;
        } else {
            current->rSon = toRemove->rSon;
            current->rSon->father = current;
        }
        delete toRemove;

    } else if(current->rSon == nullptr && current == root) {
        root = current->lSon;
        delete current;
        root->father = nullptr;
        current = root;

    } else if(current->rSon == nullptr) {
        Node *toRemove = current;
        current = current->father;
        if (*(current->lSon->key) == *key) {
            current->lSon = toRemove->lSon;
            if(current->lSon != nullptr) current->lSon->father = current;

        } else {
            current->rSon = toRemove->lSon;
            if(current->rSon != nullptr) current->rSon->father = current;
        }
        delete toRemove;
    }else if(current->rSon->lSon == nullptr){
        Node *a = current->lSon;
        Node *b = current->father;
        Node *c = current->rSon;
        Node *d = c->rSon;
        current->father = c;
        current->lSon = nullptr;
        current->rSon = d;
        c->father = b;
        if(b != nullptr){
            if(b->lSon == current) b->lSon = c;
            else b->rSon = c;
        }
        c->lSon = a;
        a->father = c;
        c->rSon = current;
        if(current == root) root = c;
        if(current->rSon == nullptr){
            delete current;
            c->rSon = nullptr;
        }
        else{
            c->rSon = current->rSon;
            c->rSon->father = c;
            delete current;
        }
        current = c;
    }else if(current->rSon->lSon->lSon == nullptr){
        Node *a = current->rSon->lSon->rSon;
        Node *b = current->rSon->lSon;
        Node *c = current->rSon;

        b->lSon = current->lSon;
        b->lSon->father = b;
        b->rSon = c;
        c->father = b;
        b->father = current->father;
        if(b->father != nullptr){
            if(b->father->lSon == current) b->father->lSon = b;
            else b->father->rSon = b;
        }
        else root = b;
        if(a == nullptr){
            c->lSon = nullptr;
        }
        else {
            c->lSon = a;
            a->father = c;
        }
        delete current;
        current = c;

    } else {
        Node *b = current->rSon;
        while(b->lSon != nullptr) b = b->lSon;
        Node *a = b->rSon;
        Node *c = b->father;
        b->lSon = current->lSon;
        b->lSon->father = b;
        b->rSon = current->rSon;
        b->rSon->father = b;
        b->father = current->father;
        if(current == root) root = b;
        if(b->father != nullptr){
            if(b->father->lSon == current) b->father->lSon = b;
            else b->father->rSon = b;
        }
        if(a == nullptr){
            c->lSon = nullptr;
        }
        else{
            c->lSon = a;
            a->father = c;
        }
        delete current;
        current = c;
    }


    balancePath(current);

    updateMax();

    updateMin();

}





template <class T>
typename AVLTree<T>::Node* AVLTree<T>::lRole(Node *current){
    Node *a = current->lSon->rSon, *b = current->lSon, *c = current, *d = current->father;
    if (d != nullptr && d->lSon == c) d->lSon = b;
    else if (d != nullptr) d->rSon = b;
    b->father = d;
    b->rSon = c;
    c->father = b;
    c->lSon = a;
    if(a != nullptr)  a->father = c;
    c->height = calcNewHeight(c);
    b->height = calcNewHeight(b);
    if(d == nullptr) root = b;
    return d;
}

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::rRole(Node *current){
    Node *a = current->rSon->lSon, *b = current->rSon, *c = current, *d = current->father;
    if (d != nullptr && d->lSon == c) d->lSon = b;
    else if (d != nullptr) d->rSon = b;
    b->father = d;
    b->lSon = c;
    c->father = b;
    c->rSon = a;
    if(a != nullptr)  a->father = c;
    c->height = calcNewHeight(c);
    b->height = calcNewHeight(b);
    if(d == nullptr) root = b;
    return d;
}

template <class T>
int AVLTree<T>::calcNewHeight(Node *i){
    if (i->lSon == nullptr && i->rSon == nullptr) return 0;
    if(i->lSon == nullptr) return i->rSon->height + 1;
    if(i->rSon == nullptr) return i->lSon->height + 1;
    return 1 + (i->lSon->height > i->rSon->height ? i->lSon->height : i->rSon->height);
}


template <class T>
int AVLTree<T>::bf(Node *i){
    if (i->lSon == nullptr && i->rSon == nullptr) return 0;
    if(i->lSon == nullptr) return -1 - i->rSon->height;
    if(i->rSon == nullptr) return i->lSon->height + 1;
    return i->lSon->height - i->rSon->height;
}

template <class T>
void AVLTree<T>::balancePath(Node *current){
    while(current != nullptr){
        current->height = calcNewHeight(current);
        if(bf(current) == 2 && bf(current->lSon) >= 0) current = lRole(current);
        else if (bf(current) == 2) {
            current = current->lSon;
            current = lRole( rRole(current));
        } else if (bf(current) == -2 && bf(current->rSon) <= 0) current = rRole(current);
        else if (bf(current) == -2){
            current=current->rSon;
            current = rRole( lRole(current));
        } else current = current->father;
    }
}

template <class T>
void AVLTree<T>::updateMax(){
    Node *current = root;
    if(current == nullptr) max = nullptr;
    else{
        while(current->lSon != nullptr){
            current = current->lSon;
        }
        max = current;
    }
}


template <class T>
void AVLTree<T>::updateMin(){
    Node *current = root;
    if(current == nullptr) min = nullptr;
    else{
        while(current->rSon != nullptr){
            current = current->rSon;
        }
        min = current;
    }
}


template <class T>
bool AVLTree<T>::isEmpty() const{
    return root == nullptr;
}

template<class T>
bool AVLTree<T>::isMember(T key) const {
    const Node *current = root;
    while(current != nullptr){
        if(*(current->key) == *key) return true;
        if(*(current->key) > *key) current = current->lSon;
        else current = current->rSon;
    }
    return false;
}



template<class T>
T AVLTree<T>::getFirst() {
    iterator = max;
    if(max == nullptr) return nullptr;
    return max->key;
}

template<class T>
T AVLTree<T>::getNext(){
    if(iterator == min) return nullptr;
    if(iterator->rSon == nullptr && iterator->father->lSon == iterator) {
        iterator = iterator->father;
    } else if(iterator->rSon == nullptr) {
        while(iterator->father->rSon == iterator) iterator = iterator->father;
        iterator = iterator->father;
    } else {
        iterator = iterator->rSon;
        if(iterator->lSon != nullptr){
            while(iterator->lSon != nullptr) iterator = iterator->lSon;
        }
    }
    return iterator->key;
}

template<class T>
bool AVLTree<T>::isLast() const {
    return iterator == min;
}

#endif // BOOM_AVL_TREE_H
