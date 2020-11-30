//
// Created by dcohe on 11/06/2020.
//

#ifndef MUSIC_MANAGER_2_ALLSONGSBYSTREAMSKEY_H
#define MUSIC_MANAGER_2_ALLSONGSBYSTREAMSKEY_H


class LectureKey {
public:
    int lectureID;
    int courseID;
    int time;

    LectureKey(int lectureID, int courseID, int time);

    friend bool operator<(const LectureKey& lhs, const LectureKey& rhs);
    friend bool operator>(const LectureKey& lhs, const LectureKey& rhs);
    friend bool operator==(const LectureKey& lhs, const LectureKey& rhs);
    friend bool operator!=(const LectureKey& lhs, const LectureKey& rhs);
};


#endif //MUSIC_MANAGER_2_ALLSONGSBYSTREAMSKEY_H
