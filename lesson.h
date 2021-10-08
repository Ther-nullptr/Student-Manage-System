#pragma once
//�γ���,��¼��ʦ���ڿ���Ϣ
#include<string>
#include<vector>
#include<utility>
#include"time.h"
#include"enums.h"

using std::make_pair;

typedef std::vector<std::pair<std::string, double>> gradeWeight;
typedef std::pair<double, double> adjustPolicy;



class Lesson:public Time
{
public:
	Lesson();
	~Lesson();
	const gradeWeight getweight();
	const adjustPolicy getpolicy();

protected:
	void setLessonMode(char);
	short credit;
	std::string lessonID;
	std::string lessonName;
	gradeWeight weight; //�γ�����Ȩ��,����Ϊ:ǩ����ƽʱ��ҵ������ҵ�����С���ĩ,Ȩ��֮�ͱ���Ϊ1.0
	Lessontype lessontype;
	adjustPolicy policy;//��������

};

