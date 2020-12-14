
#ifndef BOOM_COURSE_KEY_H
#define BOOM_COURSE_KEY_H

#include <iostream>
#include "ArrayList.h"

class CourseKey {
public:
    int courseID;
    int numLectures;
    ArrayList zeroTimeLectures;
    int* lectureArr;

    virtual ~CourseKey();

    CourseKey(int courseId, int numLec);

    friend bool operator<(const CourseKey& lhs, const CourseKey& rhs);
    friend bool operator>(const CourseKey& lhs, const CourseKey& rhs);
    friend bool operator==(const CourseKey& lhs, const CourseKey& rhs);
    friend bool operator!=(const CourseKey& lhs, const CourseKey& rhs);
};


#endif //
