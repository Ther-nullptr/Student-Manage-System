#pragma once
//ѧ����
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
	virtual void init(string);//��¼ʱ�ĳ�ʼ��
	virtual void getBasicInfo();//��ȡ����Ȩ�������ܻ�õ���Ϣ
	virtual void inputBasicInfo();//������ʦѧ�����е���Ϣ
	virtual void changeBasicInfo(char);//�޸�������Ϣ
	virtual void getLessonInfo();
	virtual void getGPA();
	virtual void ReadfromFile();
	virtual void WritetoFile();
	virtual bool operator>(const Person&);
	virtual ~Student() {};
    void setLesson(const string);
	void deleteLesson(const string);
	void GPAinit(const string,const int);//¼��ѧ��ĳ�ſγ̵�GPA

private:
	int grade;//�꼶
	short admin_class;//�����༶
	string department;//רҵ
};

