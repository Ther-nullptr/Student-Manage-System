#pragma once
//学生类
#include<string>
#include<map>
#include<vector>
#include"person.h"
#include"grade.h"
#include"time.h"
#include"file.hpp"

using std::string;

#define RED 4
#define WHITE 7
#define DEFAULT WHITE

extern void Set_TextColor(int);

class Student:public Person,public Grade
{
public:
	Student();
	virtual void init(string);//登录时的初始化
	virtual void getBasicInfo();//获取自身权限下所能获得的信息
	virtual void inputBasicInfo();//这是老师学生共有的信息
	virtual void changeBasicInfo(char);//修改自身信息
	virtual void getLessonInfo();
	virtual void getGPA();
	virtual void ReadfromFile();
	virtual void WritetoFile();
	virtual bool operator>(const Person&);
	virtual ~Student() {};
    void setLesson(const string);
	void deleteLesson(const string);
	void GPAinit(const string,const int);//录入学生某门课程的GPA

private:
	int grade;//年级
	short admin_class;//行政班级
	string department;//专业
};

