#pragma once
//'人'抽象基类
#include<string>
#include<map>
#include<fstream>
#include<limits>
#include"enums.h"
#include"file.hpp"

using std::string;

typedef string id, name,filename;
typedef id index; //返回的信息将以双索引形式储存(ID和名称)

class Person
{
public:
	Person(); //
	Person(string);
	
	virtual void init(id) = 0;
	virtual void getBasicInfo() = 0;//获取自身权限下所能获得的信息
	virtual void inputBasicInfo() = 0;//输入自身信息
	virtual void changeBasicInfo(char) = 0;//修改自身信息
	virtual void getLessonInfo() = 0;//学生模式下将返回所有可以选择的课并选课;教师模式下将返回自己所教课程的信息
	virtual void getGPA() = 0;//学生模式下返回学生各门课的绩点及平均绩点,教师模式下返回所有选课学生的绩点以及平均成绩,共设两种排序方式
	virtual void ReadfromFile() = 0;//将信息读入当前程序所操作的类
	virtual void WritetoFile() = 0;//将当前存储的所有信息储存在文件中
	virtual bool operator>(const Person&) = 0;

	usertype getType();
	const string getName();
	const string getID();
	void setName(string);
	virtual ~Person();


protected:
	usertype user;
	gendertype gender;
	string ID;
	string name;
	File* filemanager;
	void setGender(char);
	
};