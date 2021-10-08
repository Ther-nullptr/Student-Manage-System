#include<iostream>
#include<iomanip>
#include<cstdio>
#include<direct.h>
#include"academic_affairs.h"

using std::cout;
using std::setw;
using std::endl;

#define WHITE 7
#define DEFAULT WHITE

#define B_BLUE 16
#define B_GREEN 32
#define B_RED 64
#define INTENSITY 128

extern File f;
extern void Set_BackgroundColor(int);

void Affairs::GetStudentInfo(Student &_s)
{
	cout << endl;
	_s.ReadfromFile();

	Set_BackgroundColor(B_BLUE);
	cout << "基本信息" << endl;
	Set_BackgroundColor(DEFAULT);
	_s.getBasicInfo();

	cout << endl;

	Set_BackgroundColor(B_GREEN);
	cout << "绩点信息" << endl;
	Set_BackgroundColor(DEFAULT);
	cout << "课程名称" << setw(35) << "绩点" << setw(6) << "等级" << endl;

	_s.getGPA();
}

void Affairs::GetTeacherInfo(Teacher &_t)
{
	cout << endl;
	_t.ReadfromFile();

	Set_BackgroundColor(B_BLUE);
	cout << "基本信息" << endl;
	Set_BackgroundColor(DEFAULT);
	_t.getBasicInfo();

	cout << endl;

	Set_BackgroundColor(B_GREEN);
	cout << "课程信息" << endl;
	Set_BackgroundColor(DEFAULT);
	_t.getLessonInfo();
}

bool Affairs::DeleteInfo(usertype type,string s)
{
	bool flag=0;
	string txtname;
	string cwd = f.getcwdName();
	switch (type)
	{

	case usertype::student:
		txtname = cwd + "\\STUDENT" + "\\" + s + ".txt";
		flag = remove(txtname.c_str());//删除文件
		f.filelist.studentFiles.erase(s);
		break;

	case usertype::teacher:
		txtname = cwd + "\\TEACHER" + "\\" + s + ".txt";
		flag = remove(txtname.c_str());//删除文件
		f.filelist.teacherFiles.erase(s);
		break;
	}
	return flag;
}

void Affairs::DeleteAllInfo()
{
	for (auto it = f.filelist.studentFiles.begin(); it != f.filelist.studentFiles.end(); it++)
	{
		DeleteInfo(usertype::student, *it);
	}
	for (auto it = f.filelist.teacherFiles.begin(); it != f.filelist.teacherFiles.end(); it++)
	{
		DeleteInfo(usertype::teacher, *it);
	}
	f.filelist.studentFiles.clear();
	f.filelist.teacherFiles.clear();
}

void Affairs::getStudentID()
{
	int count = 0;
	for (auto it = f.filelist.studentFiles.begin(); it != f.filelist.studentFiles.end(); it++)
	{
		cout << *it<<' ';
		count++;
		if (count % 5 == 0)
		{
			cout << endl;
		}
	}
	cout << endl;
}

void Affairs::getTeacherID()
{
	int count = 0;
	for (auto it = f.filelist.teacherFiles.begin(); it != f.filelist.teacherFiles.end(); it++)
	{
		cout << *it << ' ';
		count++;
		if (count % 5 == 0)
		{
			cout << endl;
		}
	}
	cout << endl;
}