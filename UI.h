#pragma once
//UI.h ���û������йصĺꡢ�ࡢ����
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
#include<setjmp.h>//���ò�ͬ����֮��Ŀ�����ת

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

typedef std::pair<string, GPAtype>  Ordered_stu_info; //������

static jmp_buf StartMenu;//������ת����ʼ����


/*
��ɫ����SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),ǰ��ɫ | ����ɫ | ǰ����ǿ | ������ǿ);
ǰ��ɫ������0-15 �� FOREGROUND_XXX ��ʾ	������XXX����BLUE��RED��GREEN��ʾ�� 
ǰ����ǿ������8 �� FOREGROUND_INTENSITY ��ʾ
����ɫ������16 32 64 �� BACKGROUND_XXX ������ɫ��ʾ 
������ǿ�� ����128 �� BACKGROUND_INTENSITY ��ʾ
*/

void Set_TextColor(int);	//�Զ��庯���ݲ����ı�������ɫ 
void Set_BackgroundColor(int);   //�Զ��庯���ݲ����ı䱳����ɫ 

static const string crossline1("-----------------------------------------------------------------------"); //�ָ���
static const string instructions("ѧ����Ϣ����ϵͳ(student information management system)\nCopyRight (C) 2021 Computer Program Design(2) \nAll rights reserved");
static const string choosemode("��ѡ��ģʽ(�����Ӧ��ĸ):");
static const string errormsg("���Ϸ�������,�����¼���!");
static const string inputmsg("¼��ɹ�");
static const string changedmsg("�޸ĳɹ�!");
static const string basicinfo("���Ļ�����Ϣ����:");
static const string pressinfo("�밴������Լ���...");


struct fileinfo // ���ĵ���������ݴ���ڴ˽ṹ����,���ĵ�ʹ��
{
	//д�ļ���
	std::list<Student> Wstudentinfo;
	std::list<Teacher> Wteacherinfo;

	//���ļ���
	std::map<index, Student> Rstudentinfo;
	std::map<index, Teacher> Rteacherinfo;
};


class UI
{
public:
	UI();

    //����UI����
	void showStartMenu();
	void showLoginMenu();
	char showStudentMenu();
	char showTeacherMenu();
	char showAffairMenu();
	void showEndMenu();
	void getHelp();

	//ѧ����UI����
	void showBasicInfo_Student();
	void inputBasicInfo_Student();
	void changeBasicInfo_Student();
	void getLessons_Student();//�鿴���еĿ�����Ϣ
	void chooseLessons();//ѡ��
	void deleteLessons();//�˿�
	void getGPA();

	//��ʦ��UI����
	void showBasicInfo_Teacher();
	void inputBasicInfo_Teacher();
	void changeBasicInfo_Teacher();
	void setLessons();//��ӿγ�(�����,һ����ʦ��һ�ſ�)(�����γ���Ϣ�����ֱ�׼�����ι����)
	void getLessons_Teacher();//չʾ����γ̻�����Ϣ
	void getLessons_Teacher_2();
	void getStudentList();//���ؿ�������ѧ������Ϣ(��������)
	void inputGrade();//Ϊ����������ѧ��¼��ɼ�
	void setLessonTime();//���ÿ���ʱ��

    //��ʦ��ѧ�����еĽ���
    void bindingName();
    void logOff();

	//���񴦵Ľ���
	void getStudentAllInfo();
	void getTeacherAllInfo();
	void deleteInfo();
	void deleteAllInfo();
	

    //UI���к������ں�
	void mapInit();//��ʼ��Ҫ������ֵ�
	void Play();
	void Play_Student();
	void Play_Teacher();
	void Play_Affairs();
	void Exit();
	


private:
	bool statusflag;//�ж�UI�����Ƿ����ı�־λ(1��ȷ 0����) ��������Ƿ����?
	usertype user;
	fileinfo info;
	Person* pptr;
	File* filemanager;
	void lessons();//�γ��б�,�����ж��ģ��Ҫ�õ�,���Խ��䵥����ȡ����
	
};

class SortRule //����()�Ա��GPA��������
{
public:
	bool operator()(const Ordered_stu_info& v1, const Ordered_stu_info& v2)
	{
		return v1.second.first > v2.second.first;
	}
};

