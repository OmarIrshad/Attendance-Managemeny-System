#include <iostream>
#include <string>
#include "Course.h"
#include "Date.h"
#include "AttendanceRecord.h"

using std::string;
using std::ostream;
using std::endl;
using std::cout;

//Course constrcutor:
Course :: Course (std::string id, std::string title, Date startTime, Date endTime): id(id), title(title), startTime(startTime), endTime(endTime),attendanceRecords{} {

}

void Course:: addAttendanceRecord(AttendanceRecord ar){
	//we want to check the attendance record and make sure that they work compare to the start and end time

	if(ar.getDate() >= startTime && ar.getDate() <= endTime){
		attendanceRecords.push_back(ar);
		return;
	}
	else{
		 throw(std::invalid_argument("Invalid attendance Record input"));
	}
}
void Course:: outputAttendance(std::ostream& os) const {

	if(attendanceRecords.size() != 0) {
		for (unsigned int  i = 0; i < attendanceRecords.size() ; i++){
			os << attendanceRecords[i].getDate().getDateTime()  << "," <<
			attendanceRecords[i].getCourseID() << "," << attendanceRecords[i].getStudentID() << endl;
		}
	}
	else {
		os << "No records" << endl;
	}



}

void Course::outputAttendance(std::ostream& os, std::string student_id) const{
	int checker = 0;
	if(attendanceRecords.size() != 0){
		for(unsigned int i = 0; i < attendanceRecords.size(); ++i){
			if(attendanceRecords[i].getStudentID() == student_id){
				os << attendanceRecords[i].getDate().getDateTime()  << "," <<
				attendanceRecords[i].getCourseID() << "," << attendanceRecords[i].getStudentID() << endl;
				checker++;
			}
		}
		if(checker == 0){
			os <<"No records" << endl;
		}
	}
	else{
		os << "No records" << endl;
	}
}
