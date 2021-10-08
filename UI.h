#pragma once
//UI.h 与用户界面有关的宏、类、函数
#include"person.h"
#include"student.h"
#include"teacher.h"
#include"academic_affairs.h"
#include"lesson.h"
#include"enums.h"
#include<string>
#include<regex>
#include<iostream>
#include<iomanip>
#include<utility>
#include<map>
#include<set>
#include<list>
#include<conio.h>
#include<setjmp.h>//设置不同函数之间的快速跳转

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::setw;

#define BLUE 1
#define GREEN 2
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define DEFAULT WHITE

#define B_BLUE 16
#define B_GREEN 32
#define B_RED 64
#define INTENSITY 128

typedef std::pair<string, GPAtype>  Ordered_stu_info; //排序用

static jmp_buf StartMenu;//用于跳转至开始界面


/*
颜色函数SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),前景色 | 背景色 | 前景加强 | 背景加强);
前景色：数字0-15 或 FOREGROUND_XXX 表示	（其中XXX可用BLUE、RED、GREEN表示） 
前景加强：数字8 或 FOREGROUND_INTENSITY 表示
背景色：数字16 32 64 或 BACKGROUND_XXX 三种颜色表示 
背景加强： 数字128 或 BACKGROUND_INTENSITY 表示
*/

void Set_TextColor(int);	//自定义函根据参数改变字体颜色 
void Set_BackgroundColor(int);   //自定义函根据参数改变背景颜色 

static const string crossline1("-----------------------------------------------------------------------"); //分割线
static const string instructions("学生信息管理系统(student information management system)\nCopyRight (C) 2021 Computer Program Design(2) \nAll rights reserved");
static const string choosemode("请选择模式(键入对应字母):");
static const string errormsg("不合法的输入,请重新键入!");
static const string inputmsg("录入成功");
static const string changedmsg("修改成功!");
static const string basicinfo("您的基本信息如下:");
static const string pressinfo("请按任意键以继续...");


struct fileinfo // 由文档读入的数据存放在此结构体中,供文档使用
{
	//写文件用
	std::list<Student> Wstudentinfo;
	std::list<Teacher> Wteacherinfo;

	//读文件用
	std::map<index, Student> Rstudentinfo;
	std::map<index, Teacher> Rteacherinfo;
};


class UI
{
public:
	UI();

    //基本UI界面
	void showStartMenu();
	void showLoginMenu();
	char showStudentMenu();
	char showTeacherMenu();
	char showAffairMenu();
	void showEndMenu();
	void getHelp();

	//学生的UI界面
	void showBasicInfo_Student();
	void inputBasicInfo_Student();
	void changeBasicInfo_Student();
	void getLessons_Student();//查看所有的开课信息
	void chooseLessons();//选课
	void deleteLessons();//退课
	void getGPA();

	//教师的UI界面
	void showBasicInfo_Teacher();
	void inputBasicInfo_Teacher();
	void changeBasicInfo_Teacher();
	void setLessons();//添加课程(简单起见,一个教师教一门课)(包括课程信息、评分标准、调课规则等)
	void getLessons_Teacher();//展示自身课程基本信息
	void getLessons_Teacher_2();
	void getStudentList();//返回课堂所有学生的信息(可以排序)
	void inputGrade();//为课堂上所有学生录入成绩
	void setLessonTime();//设置课堂时间

    //教师和学生共有的界面
    void bindingName();
    void logOff();

	//教务处的界面
	void getStudentAllInfo();
	void getTeacherAllInfo();
	void deleteInfo();
	void deleteAllInfo();
	

    //UI运行函数和内核
	void mapInit();//初始化要读入的字典
	void Play();
	void Play_Student();
	void Play_Teacher();
	void Play_Affairs();
	void Exit();
	


private:
	bool statusflag;//判定UI输入是否合理的标志位(1正确 0错误) 这个设置是否合理?
	usertype user;
	fileinfo info;
	Person* pptr;
	File* filemanager;
	void lessons();//课程列表,由于有多个模块要用到,所以将其单独提取出来
	
};

class SortRule //重载()以便对GPA进行排序
{
public:
	bool operator()(const Ordered_stu_info& v1, const Ordered_stu_info& v2)
	{
		return v1.second.first > v2.second.first;
	}
};

