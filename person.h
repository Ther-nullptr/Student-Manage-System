#pragma once
//'��'�������
#include<string>
#include<map>
#include<fstream>
#include<limits>
#include"enums.h"
#include"file.hpp"

using std::string;

typedef string id, name,filename;
typedef id index; //���ص���Ϣ����˫������ʽ����(ID������)

class Person
{
public:
	Person(); //
	Person(string);
	
	virtual void init(id) = 0;
	virtual void getBasicInfo() = 0;//��ȡ����Ȩ�������ܻ�õ���Ϣ
	virtual void inputBasicInfo() = 0;//����������Ϣ
	virtual void changeBasicInfo(char) = 0;//�޸�������Ϣ
	virtual void getLessonInfo() = 0;//ѧ��ģʽ�½��������п���ѡ��Ŀβ�ѡ��;��ʦģʽ�½������Լ����̿γ̵���Ϣ
	virtual void getGPA() = 0;//ѧ��ģʽ�·���ѧ�����ſεļ��㼰ƽ������,��ʦģʽ�·�������ѡ��ѧ���ļ����Լ�ƽ���ɼ�,������������ʽ
	virtual void ReadfromFile() = 0;//����Ϣ���뵱ǰ��������������
	virtual void WritetoFile() = 0;//����ǰ�洢��������Ϣ�������ļ���
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