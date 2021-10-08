#include<iostream>
#include<iomanip>
#include"time.h"

using std::cin;
using std::cout;
using std::setw;

#define RED 4
#define WHITE 7
#define DEFAULT 7

extern void Set_TextColor(int);

Time::Time()
{
	lessontime.resize(2);//��������ĳߴ�Ϊ2
}

void Time::SetTime(char c)//sֻ�ṩ�ӿ�,�������������ʾ���������
{
	char c_weekmode;
	switch (c)
	{
	case '1':
		while (cin >> lessontime[0].first, !(lessontime[0].first >= 1 && lessontime[0].first <= 7) || cin.fail())
		{
			Set_TextColor(RED);
			cout << "�������Ƿ�(1-7)!" << std::endl;
			Set_TextColor(DEFAULT);
			cin.clear();
			cin.ignore();
		}
		break;

	case '2':
		while (cin >> lessontime[1].first, !(lessontime[1].first >= 1 && lessontime[1].first <= 7) || cin.fail())
		{
			Set_TextColor(RED);
			cout << "�������Ƿ�(1-7)!" << std::endl;
			Set_TextColor(DEFAULT);
			cin.clear();
			cin.ignore();
		}
		break;

	case '3':
		while (cin >> lessontime[0].second, !(lessontime[0].second >= 1 && lessontime[0].second <= 6) || cin.fail())
		{
			Set_TextColor(RED);
			cout << "�����Ƿ�(1-6)!" << std::endl;
			Set_TextColor(DEFAULT);
			cin.clear();
			cin.ignore();
		}
		break;

	case '4':
		while (cin >> lessontime[1].second, !(lessontime[1].second >= 1 && lessontime[1].second <= 6) || lessontime[1].second == lessontime[0].second || cin.fail())
		{
			Set_TextColor(RED);
			cout << "�����Ƿ�(1-6)��ʱ���ͻ!" << std::endl;
			Set_TextColor(DEFAULT);
			cin.clear();
			cin.ignore();
		}
		break;

	case '5':
		while (cin >> c_weekmode, !(c_weekmode == '1' || c_weekmode == '2' || c_weekmode == '3') || cin.fail())
		{
			Set_TextColor(RED);
			cout << "�����Ƿ�(1--ȫ�� 2--ǰ���� 3--�����)!" << std::endl;
			Set_TextColor(DEFAULT);
			cin.clear();
			cin.ignore();
		}
		SetWeekType(c_weekmode);
		break;
	}
}

void Time::GetTime()
{
	cout << setw(40) << "�γ�ʱ��";
	auto _weektype = [](WeekType w) -> const char*
	{
		switch (w)
		{
		case WeekType::All:
			return "ȫ��";
			break;
		case WeekType::F_half:
			return "ǰ����";
			break;
		case WeekType::S_half:
			return "�����";
			break;
		default:
			return "NaN";
			break;
		}
	};
	cout << _weektype(weektype) << ',';
	cout << "��" << lessontime[0].first << '(' << lessontime[0].second << ')';
	if (lessontime[1].second != 0)
	{
		cout << "��" << lessontime[1].first << '(' << lessontime[1].second << ')';
	}
	cout << std::endl;
}

bool Time::operator == (const Time& t2)
{
	bool b1 = (lessontime[0].first == t2.lessontime[0].first) || (lessontime[1].first == t2.lessontime[1].first);
	bool b2 = (lessontime[0].second == t2.lessontime[0].second) || (lessontime[1].second == t2.lessontime[1].second);
	//b1 b2������˵������ͬ���Ͽ�ʱ��
	bool b3 = !(bool(weektype) * bool(t2.weektype));//�ų�һ���������:ǰ���ܺͺ���ܵĿγ����Ͽ�ʱ����ȫ��ͬ�����
	return (b1 && b2 && b3);
}

void Time::SetWeekType(char c_weekmode)
{
	switch (c_weekmode)
	{
	case '1':
		weektype = WeekType::All;
		break;
	case '2':
		weektype = WeekType::F_half;
		break;
	case '3':
		weektype = WeekType::S_half;
		break;
	default:
		weektype = WeekType::null;
		break;
	}
}


Time::~Time() {}
