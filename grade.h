#pragma once
//成绩类,记录学生的绩点及相关操作
#include<string>
#include<utility> //std::pair
#include<vector>
#include<map>
#include<algorithm>
#include"time.h"

#define PF 100 //值本身无意义,只为标志PF
#define NaN 0 //值本身无意义,只为表示未录入


typedef std::pair<double, std::string> GPAtype; // 定义GPA类型数据
typedef std::map<std::string, GPAtype> GPAlist;

class Grade
{
public:
	Grade(){}
	Grade(int,bool);
	GPAtype score_to_GPA(int);
	const GPAlist getGPAlist();//供老师打分用


protected:
	bool isPF;
	GPAlist GPA;
};




