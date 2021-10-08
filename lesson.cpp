#include"lesson.h"
#include"enums.h"

Lesson::Lesson()
{
	//Ĭ������
	weight.push_back(make_pair("ǩ��", 0.05));
	weight.push_back(make_pair("ƽʱ��ҵ", 0.15));
	weight.push_back(make_pair("����ҵ", 0.20));
	weight.push_back(make_pair("���п���", 0.25));
	weight.push_back(make_pair("��ĩ����", 0.35));
	
	policy.first = 1.0;
	policy.second = 0.0;
}

Lesson::~Lesson(){}

const gradeWeight Lesson::getweight()
{
	return weight;
}

const adjustPolicy Lesson::getpolicy()
{
	return policy;
}

void Lesson::setLessonMode(char c_lessonmode)
{
	switch (c_lessonmode)
	{
	case '1':
		lessontype = Lessontype::Compulsory;
		break;
	case '2':
		lessontype = Lessontype::Limited;
		break;
	case '3':
		lessontype = Lessontype::Optional;
		break;
	}
}