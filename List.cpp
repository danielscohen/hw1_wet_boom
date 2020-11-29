//
// Created by dcohe on 11/06/2020.
//



#include "List.h"

StatusType List::add(int key) {
    std::shared_ptr<Node> temp;
    try {
        temp = std::make_shared<Node>(Node(key));
    }catch(...) {return ALLOCATION_ERROR;}
    std::shared_ptr<Node> current;
    for(current = head; current->next != nullptr; current = current->next){};
    temp->next = current->next;
    current->next = temp;
    return SUCCESS;
}

StatusType List::remove(int key) {
    std::shared_ptr<Node> temp = head;
    while(temp->next != nullptr){
        if(temp->next->key == key){
            temp->next = temp->next->next;
            return SUCCESS;
        }
        temp = temp->next;
    }
    return FAILURE;
}

T List::get(int key) {
    std::shared_ptr<Node> left = head->next;
}

List::Node::Node(int key):key(key), next(nullptr) {}

List::Node::Node():key(-1), next(nullptr) {}

List::List() {
    head = std::make_shared<Node>(Node());
}


int List::getItKey() {
    return iterator->key;
}

void List::resetIterator() {
    iterator = head->next;
}

bool List::itAtEnd() {
    return iterator == nullptr;
}

void List::itNext() {
    iterator = iterator->next;
}


#include "List.h"


