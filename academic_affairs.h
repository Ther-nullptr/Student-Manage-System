#pragma once
//教务处类
#include"person.h"
#include"student.h"
#include"teacher.h"
#include"enums.h"
class Affairs 
{
public:
	void GetStudentInfo(Student&);
	void GetTeacherInfo(Teacher&);
	bool DeleteInfo(usertype,string);
	void DeleteAllInfo();
	void getStudentID();
	void getTeacherID();
};