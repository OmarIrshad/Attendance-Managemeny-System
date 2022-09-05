#include <string>
#include <iostream>
#include "AttendanceRecord.h"
#include "Date.h"

using std::cout;
//Attendance constructor
AttendanceRecord :: AttendanceRecord(std::string course_id, std::string student_id, Date time): course_id(course_id), student_id(student_id), time(time){

}

// std::ostream& operator<<(std::ostream& os, const AttendanceRecord& ar){
// 	os << ar.getDate().getMonth() << "/" <<ar.getDate().getDay() << "/" << ar.getDate().getYear()
// 	<< " " << ar.getDate().getHour() << ":" << ar.getDate().getMin() << ar.getDate().getSec() << "," <<
// 	ar.getCourseID() << "," << ar.getStudentID() << std::endl;
// }