//
// Created by meir_ on 13/05/2020.
//

#include "Course.h"
#include "StreamsList.h"
Course::Course(int numOfSongs): numOfSongs(numOfSongs) {
    songsArray = new StreamsList::StreamNode*[numOfSongs];
}

Course::~Course() {
    delete[] songsArray;
}
