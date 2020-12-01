//
// Created by dcohe on 30/11/2020.
//

#ifndef HW1_WET_BOOM_ARRAYLIST_H
#define HW1_WET_BOOM_ARRAYLIST_H

#include <memory>

class ArrayList{
public:
    struct Node{
        int prev, next;
    };

    Node* arr;
    int head;
    int iterator;
    explicit ArrayList(int size);
    int getFirst();
    int getNext();
    void remove(int index);

    virtual ~ArrayList();

    bool isTail();
    bool isEmpty;
    int getPrev();
    int getNext2();
    void initZero();
};

#endif //HW1_WET_BOOM_ARRAYLIST_H
