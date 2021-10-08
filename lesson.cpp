#include"lesson.h"
#include"enums.h"

Lesson::Lesson()
{
	//默认设置
	weight.push_back(make_pair("签到", 0.05));
	weight.push_back(make_pair("平时作业", 0.15));
	weight.push_back(make_pair("大作业", 0.20));
	weight.push_back(make_pair("期中考试", 0.25));
	weight.push_back(make_pair("期末考试", 0.35));
	
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