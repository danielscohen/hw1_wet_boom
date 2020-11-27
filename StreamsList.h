//
// Created by dcohe on 13/05/2020.
//

#ifndef MUSIC_MANAGER_STREAMSLIST_H
#define MUSIC_MANAGER_STREAMSLIST_H


#include "AVLTree.h"
#include "library1.h"



class StreamsList {



public:

    struct StreamNode{
        int numStreams;
        AVLTree<AVLTree<int> > *artistTree;
        StreamNode *prev;
        StreamNode *next;

        StreamNode(int numStreams, AVLTree<AVLTree<int> > *artistTree, StreamNode *prev, StreamNode *next);

        virtual ~StreamNode();
    };

    StreamsList();
    StatusType addStreamToSong(StreamNode *current, int songID, int artistID, bool& nodeRemoved);
    void deleteArtistSongsTree(StreamNode *current, int artistID);
    StatusType getRecommendedSongs(int numOfSongs, int *artists, int *songs);
    StatusType addArtistSongs(int numSongs, int artistID);
    ~StreamsList();
    StreamNode *getZeroStreams();
    StreamNode *getback();

private:
    StreamNode *front;
    StreamNode *back;



};


#endif //MUSIC_MANAGER_STREAMSLIST_H
