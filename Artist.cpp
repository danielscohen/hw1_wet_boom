//
// Created by meir_ on 13/05/2020.
//

#include "Artist.h"
#include "StreamsList.h"
Artist::Artist(int numOfSongs): numOfSongs(numOfSongs) {
    songsArray = new StreamsList::StreamNode*[numOfSongs];
}

Artist::~Artist() {
    delete[] songsArray;
}
