
#ifndef BOOM_LECTURE_KEY_H
#define BOOM_LECTURE_KEY_H


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


#endif //
