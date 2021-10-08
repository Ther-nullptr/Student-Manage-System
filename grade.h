#pragma once
//�ɼ���,��¼ѧ���ļ��㼰��ز���
#include<string>
#include<utility> //std::pair
#include<vector>
#include<map>
#include<algorithm>
#include"time.h"

#define PF 100 //ֵ����������,ֻΪ��־PF
#define NaN 0 //ֵ����������,ֻΪ��ʾδ¼��


typedef std::pair<double, std::string> GPAtype; // ����GPA��������
typedef std::map<std::string, GPAtype> GPAlist;

class Grade
{
public:
	Grade(){}
	Grade(int,bool);
	GPAtype score_to_GPA(int);
	const GPAlist getGPAlist();//����ʦ�����


protected:
	bool isPF;
	GPAlist GPA;
};




