//
// Created by dcohe on 11/06/2020.
//

#ifndef MUSIC_MANAGER_2_ALLSONGSBYSTREAMSKEY_H
#define MUSIC_MANAGER_2_ALLSONGSBYSTREAMSKEY_H


class AllLecturesByTimeKey {
public:
    int lectureID;
    int courseID;
    int time;

    AllLecturesByTimeKey(int songId, int artistId, int numStreams);

    friend bool operator<(const AllLecturesByTimeKey& lhs, const AllLecturesByTimeKey& rhs);
    friend bool operator>(const AllLecturesByTimeKey& lhs, const AllLecturesByTimeKey& rhs);
    friend bool operator==(const AllLecturesByTimeKey& lhs, const AllLecturesByTimeKey& rhs);
    friend bool operator!=(const AllLecturesByTimeKey& lhs, const AllLecturesByTimeKey& rhs);
};


#endif //MUSIC_MANAGER_2_ALLSONGSBYSTREAMSKEY_H
