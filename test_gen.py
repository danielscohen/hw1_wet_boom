
from __future__ import division
from operator import itemgetter, attrgetter
import random
import sys


commandStr = ["AddCourse", "RemoveCourse", "WatchClass",
              "TimeViewed", "GetMostViewedClasses"]

SUCCESS = "SUCCESS"
FAILURE = "FAILURE"
INVALID_INPUT = "INVALID_INPUT"

lectures = []
courses = dict()



def initline():
    inLine = "Init"
    outLine = "init done."
    return inLine, outLine

# AddLecture hour room_id course_id
def AddCourse():
    global lectures, courses
    courseID = random.randint(-3, 10)
    numOfClasses = random.randint(-3, 20)
    inLine = "AddCourse %d %d" % (courseID, numOfClasses)
    outLine = "AddCourse: "
    if courseID <= 0 or numOfClasses <= 0:
        outLine += INVALID_INPUT
    elif courseID in courses.keys():
        outLine += FAILURE
    else:
        courses[courseID] = [0]*numOfClasses
        for i in range(numOfClasses):
            lectures.append([0, courseID, i])
        outLine += SUCCESS
    return inLine, outLine


# DeleteLecture hour room_id
def RemoveCourse():
    global courses, lectures
    courseID = random.randint(-5, 15)
    inLine = "RemoveCourse %d" % (courseID)
    outLine = "RemoveCourse: "
    if courseID <= 0:
        outLine += INVALID_INPUT
    elif courseID not in courses.keys():
        outLine += FAILURE
    else:
        del courses[courseID]
        lectures = [x for x in lectures if x[1] != courseID]
        outLine += SUCCESS
    return inLine, outLine

def WatchClass():
    global courses, lectures
    courseID = random.randint(-5, 15)
    classID = random.randint(-5, 15)
    time = random.randint(-5, 15)
    inLine = "WatchClass %d %d %d" % (courseID, classID, time)
    outLine = "WatchClass: "
    if courseID <= 0 or classID < 0 or time <= 0:
        outLine += INVALID_INPUT
    elif courseID in courses.keys() and classID + 1 > len(courses[courseID]):
        outLine += INVALID_INPUT
    elif courseID not in courses.keys():
        outLine += FAILURE
    else:
        courses[courseID][classID] += time
        for i in range(len(lectures)):
            if lectures[i][1] == courseID and lectures[i][2] == classID:
                lectures[i][0] += time
        outLine += SUCCESS
    return inLine, outLine

def TimeViewed():
    global courses, lectures
    courseID = random.randint(-5, 15)
    classID = random.randint(-5, 15)
    inLine = "TimeViewed %d %d" % (courseID, classID)
    outLine = "TimeViewed: "
    if courseID <= 0 or classID < 0:
        outLine += INVALID_INPUT
    elif courseID in courses.keys() and classID + 1 > len(courses[courseID]):
        outLine += INVALID_INPUT
    elif courseID not in courses.keys():
        outLine += FAILURE
    else:
        outLine += "%d" %(courses[courseID][classID])
    return inLine, outLine

def GetMostViewedClasses():
    global courses, lectures
    numOfClasses = random.randint(-5, 15)
    inLine = "GetMostViewedClasses %d" % (numOfClasses)
    outLine = "GetMostViewedClasses: "
    if numOfClasses <= 0:
        outLine += INVALID_INPUT
    elif len(lectures) < numOfClasses:
        outLine += FAILURE
    else:
        lectures.sort(key=itemgetter(2))
        lectures.sort(key=itemgetter(1))
        lectures.sort(key=itemgetter(0), reverse=True)
        outLine += SUCCESS
        outLine += "\nCourse\t|\tClass\n"
        for i in range(numOfClasses):
            outLine += "%d\t|\t%d\n" %(lectures[i][1], lectures[i][2])
        outLine += "--End of most viewed classes--"
    return inLine, outLine

def main():
    if len(sys.argv) < 3:
        print ("Usage %s <lines>" % sys.argv[0])
        exit(0)
    lines = int(sys.argv[1])
    infname = "in%s.txt" % sys.argv[2]
    outfname = "out%s.txt" % sys.argv[2]
    functions = [AddCourse, RemoveCourse, WatchClass, GetMostViewedClasses, TimeViewed]
    with open(infname, 'wb') as infhandler:
        with open(outfname, 'wb') as outfhandler:
            inLine, outLine = initline()
            infhandler.write(inLine + "\n")
            outfhandler.write(outLine + "\n")
            while lines > 0:
                f = random.randint(0, len(functions)-1)
                func = functions[f]
                inLine, outLine = func()
                if inLine is not "":
                    infhandler.write(inLine + "\n")
                    outfhandler.write(outLine + "\n")
                    lines -= 1
            infhandler.write("Quit\n")
            outfhandler.write("quit done.\n")


main()
