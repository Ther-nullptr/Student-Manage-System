#pragma once
//课程类,记录教师的授课信息
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
	gradeWeight weight; //课程评分权重,依次为:签到、平时作业、大作业、期中、期末,权重之和必须为1.0
	Lessontype lessontype;
	adjustPolicy policy;//调分政策

};

