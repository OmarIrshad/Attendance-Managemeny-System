#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "School.h"
#include "AttendanceRecord.h"

using std::string;
using std::ostream;
using std::ifstream;
using std::istringstream;
using std::endl;
using std::cout;



// one method is provided to students; students implement all other methods
//addCoursesMethod 
void School::addCourses(std::string filename){
    ifstream ifs(filename);
    if (!ifs.is_open()) {
    throw std::invalid_argument("addCourses: can't open file");
  }
  while (!ifs.eof()){
        string line; 
        getline(ifs,line);
        istringstream ss(line);
        string id;

        getline(ss,id,','); //Stores the ID
        string startTime;
        getline(ss,startTime,','); //Stores the Start Time
        string endTime;
        getline(ss,endTime, ','); //Stores the endtime in Course 
        string startTimeHr;
        string startTimeMin;
        string random;
        if(ss.fail()){
            break;
        }
        //split the start time:
        istringstream sT(startTime);
        getline(sT,startTimeHr, ':');
        getline(sT,startTimeMin, ':');
        getline(sT,random);
        int sTHr = std::stoi(startTimeHr);
        int sTMin = std::stoi(startTimeMin);
        
        //split the end time
        string endTimeHr;
        string endTimeMin;

        istringstream eT(endTime);
        getline(eT,endTimeHr, ':');
        getline(eT,endTimeMin, ':');
        int eThr = std::stoi(endTimeHr);
        int eTMin = std::stoi(endTimeMin);
        int sec = 0;
        //create data types that will be inserted as our Course
        Date cStartTime(sTHr, sTMin, sec);
        Date cEndTime(eThr, eTMin, sec);

        //Now we need ALL the titles:
        string titlenames; 
        getline(ss, titlenames);

        Course finalCourse(id,titlenames,cStartTime, cEndTime);
        // cout << "ID: " << id << endl;
        // cout << "legth of id: " << id.length() << endl;
        // cout << "titlename: " << titlenames << endl;
        courses.push_back(finalCourse);
  }
}
//listcourses TODO
void School::listCourses(std::ostream& os) const{
    
    if (courses.size() == 0){
        os << "No courses" << endl;
    }
    else{
        for(size_t i = 0; i < courses.size(); ++i){ //loop through and list  out the courses
            Date time_start = courses[i].getStartTime();
            Date time_end = courses[i].getEndTime();
            os << courses[i].getID() << "," << time_start.getTime(false) << "," << time_end.getTime(false) << "," <<
            courses[i].getTitle() << endl;
        } 
    }
}

//GivenlL

void School::addStudents(string filename) {
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    throw std::invalid_argument("addStudents: can't open file");

  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string uin;
    getline(ss, uin, ',');
    string name;
    getline(ss, name);
    if (!ss.fail()) {
        Student student(uin, name);
        bool exists = false;
        for (Student s : students) {
            if (s == student) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            students.push_back(student);
        }
    }
  }
}

bool School:: isCourse(std::string course_id) const{
    for(size_t i = 0; i < courses.size(); i++){
        if(courses[i].getID() == course_id){
            return true;
        }
    }
    return false;
}
//liststudents implement:
bool School:: isEnrolled(std::string student_id) const{
    for(size_t i = 0; i < students.size(); i++){
        if(students[i].get_id() == student_id){
            return true;
        }
    }
    return false;
}
void School::listStudents(std::ostream& os) const {
    if (students.size() == 0){
        os << "No students" << endl;
    }
    else{
        for(size_t i = 0; i < students.size(); i++){
            os << students[i].get_id() << "," << students[i].get_name() << endl;
        }
    }

}


unsigned int School:: addAttendanceData(std::string filename){
    unsigned int invalid_entries = 0;
    ifstream ifs(filename);
    while(!ifs.eof()){
        string line;
        getline(ifs,line); //line for each spread sheet

        //Everything we need to capture one line worth of data 
        string datemonth;
        string dateday;
        string dateyear;
        string datehour;
        string datemin;
        string datesec;
        string course_id;
        string student_id;

        //capturing all of the data
        istringstream ss(line);
        getline(ss, dateyear, '-');
        getline(ss, datemonth, '-');
        getline(ss,dateday, ' ');
        getline(ss,datehour, ':');
        getline(ss,datemin, ':');
        getline(ss,datesec, ',');
        getline(ss,course_id, ',');
        getline(ss,student_id, ' ');
        //Checking the Date: 
        //convert all our strings into dates:
        if(ss.fail()){
            break;
        }
        //recreate variables:
        int datey = std::stoi(dateyear);
        int datemon = std::stoi(datemonth);
        int dated = std::stoi(dateday);
        int dateh = std::stoi(datehour);
        int dateminn = std::stoi(datemin);
        int dates = std::stoi(datesec);




        //create a Date data type:
        Date Check(datey,datemon,dated,dateh,dateminn,dates); 
        if(Check.isValid() == false){
            invalid_entries++;
            continue;
        }
        //Checking the course ID 
        //can immediately go to comparing this with our vector
        unsigned int s = 0;
        size_t course_count = 0;
        for(size_t i = 0; i < courses.size(); i++){
            if(courses[i].getID() == course_id){
                course_count = 1;
                s = i;
                break;
            }
        }
        if(course_count == 0){
            invalid_entries++;
            continue;
        } 
        //Checking the student ID
        size_t student_count = 0;

        for(size_t i = 0; i < students.size(); i++){
            if(students[i].get_id() == student_id){
                student_count = 1;
            }
        }
        if(student_count == 0){
            invalid_entries++;
            continue;
        }
     if ( invalid_entries == 0){
        AttendanceRecord lol(course_id,student_id, Check);
        courses[s].addAttendanceRecord(lol);
    }    

    }

    return invalid_entries;
}

void School::outputCourseAttendance(std::ostream& os, std::string course_id) const {
    //check if the course is valid in our vector:
    for(size_t i = 0; i < courses.size(); i++){
        // Course output(courses[i]);
        if(courses[i].getID() == course_id){
            courses[i].outputAttendance(cout); 
        }
    }
    os << endl;
}
void School::outputStudentAttendance(std::ostream& os, std::string student_id, 
                               std::string course_id) const{   
    for(size_t i = 0; i < courses.size(); i++){
        // Course output(courses[i]);
        if(courses[i].getID() == course_id){
            courses[i].outputAttendance(cout,student_id); 
        }
    }
    os << endl;
}

