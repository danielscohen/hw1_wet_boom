//
// Created by dcohe on 11/06/2020.
//

#ifndef COURSES_MANAGER_LIST_H
#define COURSES_MANAGER_LIST_H

#include <memory>
#include "library.h"


class List {


    struct Node{
        int key;

        explicit Node(int key);
        Node();

        std::shared_ptr<Node> next;

    };

    std::shared_ptr<Node> head;
    std::shared_ptr<Node> iterator;

public:

    StatusType add(int key);
    StatusType remove(int key);
    int getItKey();
    bool itAtEnd();
    void itNext();
    void resetIterator();

    List();
};

#endif
