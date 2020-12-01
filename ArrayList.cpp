//
// Created by dcohe on 30/11/2020.
//

#include "ArrayList.h"

ArrayList::ArrayList(int size) :arr(new Node[size]), head(0), iterator(0), isEmpty(false) {
    arr[0].prev = -1;
    arr[0].next = 1;
    arr[size - 1].next = -1;
    if(size > 1) {
        arr[size - 1].prev = size - 2;
        for(int i = 1; i < (size - 1); i++){
            arr[i].prev = i - 1;
            arr[i].next = i + 1;
        }
    }
}


int ArrayList::getFirst() {
    iterator = head;
    return iterator;
}

int ArrayList::getNext() {
    iterator = arr[iterator].next;
    return iterator;
}

void ArrayList::remove(int index) {
    if(arr[index].prev == -1 && arr[index].next == -1) isEmpty = true;
    else if (arr[index].prev == -1) {
        arr[arr[index].next].prev = -1;
        head = arr[index].next;
    } else if (arr[index].next == -1) {
        arr[arr[index].prev].next = -1;
    } else {
        arr[arr[index].prev].next = arr[index].next;
        arr[arr[index].next].prev = arr[index].prev;
    }
}

bool ArrayList::isTail() {
    return arr[iterator].next == -1;
}

int ArrayList::getPrev() {
    return arr[iterator].prev;
}

int ArrayList::getNext2() {
    return arr[iterator].next;
}

ArrayList::~ArrayList() {
    delete[] arr;
}

void ArrayList::initZero() {

}

