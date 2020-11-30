//
// Created by dcohe on 30/11/2020.
//

#ifndef HW1_WET_BOOM_ARRAYLIST_H
#define HW1_WET_BOOM_ARRAYLIST_H

class ArrayList{
    struct Node{
        int prev, next;
    };

    Node* arr;
    int head;
    int iterator;
public:
    explicit ArrayList(int size);
    virtual ~ArrayList();
    int getFirst();
    int getNext();
    void remove(int index);
    bool isTail();
    bool isEmpty;
};

#endif //HW1_WET_BOOM_ARRAYLIST_H
