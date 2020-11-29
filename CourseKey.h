//
// Created by dcohe on 11/06/2020.
//

#ifndef MUSIC_MANAGER_2_ARTISTSONGSBYIDKEY_H
#define MUSIC_MANAGER_2_ARTISTSONGSBYIDKEY_H


class CourseKey {
public:
    int courseID;
    int numLectures;
    int* lectureArr;

    virtual ~CourseKey();

    CourseKey(int courseId, int numLec);

    friend bool operator<(const CourseKey& lhs, const CourseKey& rhs);
    friend bool operator>(const CourseKey& lhs, const CourseKey& rhs);
    friend bool operator==(const CourseKey& lhs, const CourseKey& rhs);
    friend bool operator!=(const CourseKey& lhs, const CourseKey& rhs);
};


#endif //MUSIC_MANAGER_2_ARTISTSONGSBYIDKEY_H