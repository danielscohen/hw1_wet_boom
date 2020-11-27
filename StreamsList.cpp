//
// Created by dcohe on 13/05/2020.
//

#include "StreamsList.h"



StreamsList::StreamsList() : front(new StreamNode(-1, nullptr, nullptr, nullptr)),
    back(front){}





StreamsList::StreamNode::StreamNode(int numStreams, AVLTree<AVLTree<int> > *artistTree, StreamNode *prev, StreamNode *next) :
    numStreams(numStreams), artistTree(artistTree), prev(prev), next(next){}

StreamsList::StreamNode::~StreamNode() {
    if(artistTree != nullptr) delete artistTree;
}


StatusType StreamsList::addStreamToSong(StreamsList::StreamNode *current, int songID, int artistID, bool& nodeRemoved){
    AVLTree<int> *songTree = new AVLTree<int>();
    try{
        AVLTree<AVLTree<int> > *artistStreamTree = new AVLTree<AVLTree<int> >();
            try{
                StreamNode *node = new StreamNode(current->numStreams + 1, artistStreamTree, nullptr, nullptr);
                if(current->next == nullptr){
                    current->next = node;
                    node->prev = current;
                    node->next = nullptr;
                    back = node;
                    node->artistTree->insert(artistID, songTree);
                    node->artistTree->get(artistID)->insert(songID, nullptr);
                } else if (current->next->numStreams != current->numStreams + 1){
                    StreamNode *temp = current->next;
                    current->next = node;
                    node->next = temp;
                    temp->prev = node;
                    node->prev = current;
                    node->artistTree->insert(artistID, songTree);
                    node->artistTree->get(artistID)->insert(songID, nullptr);
                } else if (current->next->artistTree->get(artistID) == nullptr){
                    current->next->artistTree->insert(artistID, songTree);
                    current->next->artistTree->get(artistID)->insert(songID, nullptr);
                    delete node;
                } else{
                    current->next->artistTree->get(artistID)->insert(songID, nullptr);
                    delete node;
                    delete songTree;
                }
                current->artistTree->get(artistID)->remove(songID);
                if(current->artistTree->get(artistID)->isEmpty()) current->artistTree->remove(artistID);
                if(current->artistTree->isEmpty()){
                    current->next->prev = current->prev;
                    current->prev->next = current->next;
                    delete current;
                    nodeRemoved = true;

                }
            } catch (...){
             delete artistStreamTree;
                throw;
            }
    } catch (...){
        delete songTree;
        return ALLOCATION_ERROR;
    }
return SUCCESS;
}

void StreamsList::deleteArtistSongsTree(StreamsList::StreamNode *current, int artistID) {
    //todo check if artist node already erased
    if(current == nullptr || current->artistTree->get(artistID) == nullptr) return;
    current->artistTree->remove(artistID);
    if(current->artistTree->isEmpty()){
        if(current != back){
            current->next->prev = current->prev;
            current->prev->next = current->next;

        } else{
            current->prev->next = nullptr;
            back = current->prev;
        }
        delete current;
    }
}

StreamsList::~StreamsList() {
    for (StreamNode* n = front->next; n != nullptr ; n = n->next) {
        delete n->prev;
    }
    delete back;
}

StatusType StreamsList::getRecommendedSongs(int numOfSongs, int *artists, int *songs) {
    int counter = 0;
    for (StreamNode *node = back; node != front ; node = node->prev) {
        for (AVLTree<int> *artist = node->artistTree->getMin() ; artist != nullptr; artist = node->artistTree->getNextBigger()) {
            for (int songID = artist->getMinKey() ; songID != -1; songID = artist->getNextBiggerKey()) {
                songs[counter] = songID;
                artists[counter] = node->artistTree->getCurrentKey();
                counter++;
                if(counter == numOfSongs) return SUCCESS;
            }
        }
    }
    return FAILURE;
}

StatusType StreamsList::addArtistSongs(int numSongs, int artistID){

    AVLTree<int> *songTree = new AVLTree<int>();
    try {
        songTree->fill(numSongs);
        if (front->next != nullptr && front->next->numStreams == 0) {
            front->next->artistTree->insert(artistID, songTree);
        }
        else{
            AVLTree<AVLTree<int> > *artistTree = new AVLTree<AVLTree<int> >();
            try{
                StreamNode *node = new StreamNode(0, artistTree, front, nullptr);
                try{
                    artistTree->insert(artistID, songTree);
                    if(front->next == nullptr){
                        front->next = node;
                        back = node;
                    }
                    else{
                        StreamNode *temp = front->next;
                        front->next = node;
                        node->prev = front;
                        node->next = temp;
                        temp->prev = node;
                    }
                } catch(...){
                    delete node;
                    throw;
                }
            } catch(...){
                delete artistTree;
                throw;
            }
        }
    }catch(...){
        delete songTree;
        return ALLOCATION_ERROR;
    }

    return SUCCESS;

}

StreamsList::StreamNode* StreamsList::getZeroStreams(){
    return front->next;
}

StreamsList::StreamNode* StreamsList::getback(){
    return back;
}








