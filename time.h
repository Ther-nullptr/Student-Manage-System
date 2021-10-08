#pragma once
#include<utility>
#include<vector>
#include"enums.h"

typedef short week;
typedef short section;
typedef std::vector<std::pair<week,section>> Lessontime;

class Time
{
public:
	Time();
	void SetTime(char);
	void GetTime();
	bool operator == (const Time& t2);//重载==,若时间存在冲突返回1
	~Time();

protected:
	Lessontime lessontime;
	WeekType weektype;
	void SetWeekType(char);
};