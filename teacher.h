#pragma once
//��ʦ��
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
	virtual void getBasicInfo();//��ȡ����Ȩ�������ܻ�õ���Ϣ
	virtual void inputBasicInfo();
	virtual void changeBasicInfo(char);//�޸�������Ϣ
	virtual void getLessonInfo();
	virtual void getGPA();
	virtual void ReadfromFile();
	virtual void WritetoFile();
	virtual bool operator>(const Person&) { return true; }
	virtual ~Teacher();
    const string getLessonName();

private:
	jobtype type;
	string department;//����רҵ
	void setType(char);
	//���̿γ̵Ķ���
};