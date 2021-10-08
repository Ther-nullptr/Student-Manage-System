#pragma once
//教师类
#include<string>
#include"person.h"
#include"lesson.h"
#include"file.hpp"

using std::string;

#define RED 4
#define WHITE 7
#define DEFAULT WHITE

extern void Set_TextColor(int);


class Teacher :public Person,public Lesson
{
public:
	Teacher();
	virtual void init(string);
	virtual void getBasicInfo();//获取自身权限下所能获得的信息
	virtual void inputBasicInfo();
	virtual void changeBasicInfo(char);//修改自身信息
	virtual void getLessonInfo();
	virtual void getGPA();
	virtual void ReadfromFile();
	virtual void WritetoFile();
	virtual bool operator>(const Person&) { return true; }
	virtual ~Teacher();
    const string getLessonName();

private:
	jobtype type;
	string department;//所属专业
	void setType(char);
	//所教课程的对象
};