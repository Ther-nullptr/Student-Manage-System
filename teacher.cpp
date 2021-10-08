#include <iostream>
#include <iomanip>
#include "teacher.h"

using std::cin;
using std::cout;
using std::endl;
using std::setprecision;
using std::setw;


Teacher::Teacher()
{
	user = usertype::teacher;
	name = "NaN";
}

void Teacher::init(string _ID)
{
	ID = string(_ID.c_str());
}

void Teacher::setType(char c_type)
{
	switch (c_type)
	{
	case '1':
		type = jobtype::professor;
		break;
	case '2':
		type = jobtype::associate_professor;
		break;
	case '3':
		type = jobtype::lecturer;
		break;
	default:
		type = jobtype::null;
		break;
	}
}

void Teacher::getBasicInfo()
{
	auto sex = [](gendertype g) -> const char*
	{
		switch (g)
		{
		case gendertype::male:
			return "男";
		case gendertype::female:
			return "女";
		default:
			return "NaN";
		}
	};

	auto job = [](jobtype j) -> const char*
	{
		switch (j)
		{
		case jobtype::lecturer:
			return "讲师";
		case jobtype::professor:
			return "教授";
		case jobtype::associate_professor:
			return "副教授";
		default:
			return "NaN";
		}
	};

	cout << std::setiosflags(ios::left);
	cout << setw(40) << "ID" << ID << endl;
	cout << setw(40) << "名字" << name << endl;
	cout << setw(40) << "性别" << sex(gender) << endl;
	cout << setw(40) << "职称" << job(type) << endl;
	cout << setw(40) << "专业" << department << endl;
	cout << std::resetiosflags(ios::left);
}

void Teacher::inputBasicInfo()
{
	char c_gender, c_type;
	while (cin >> c_gender, !(c_gender == '1' || c_gender == '2') || cin.fail())
	{
		Set_TextColor(RED);
		cout << "请重新输入性别(1--男 2--女)!" << endl;
		Set_TextColor(DEFAULT);
		cin.clear();
		cin.ignore();
	}

	while (cin >> c_type, !(c_type == '1' || c_type == '2' || c_type == '3') || cin.fail())
	{
		Set_TextColor(RED);
		cout << "请重新输入职称(1--教授 2--副教授 3--讲师)!" << endl;
		Set_TextColor(DEFAULT);
		cin.clear();
		cin.ignore();
	}

	cin >> department;
	setGender(c_gender);
	setType(c_type);
}

void Teacher::changeBasicInfo(char a)
{
	double sum = 0;
	switch (a)
	{
	case 'A':
	case 'a':
		char c_gender;
		while (cin >> c_gender, !(c_gender == '1' || c_gender == '2') || cin.fail())
		{
			Set_TextColor(RED);
			cout << "请重新输入性别(1--男 2--女)!" << endl;
			Set_TextColor(DEFAULT);
			cin.clear();
			cin.ignore();
		}
		setGender(c_gender);
		break;

	case 'B':
	case 'b':
		char c_type;
		while (cin >> c_type, !(c_type == '1' || c_type == '2' || c_type == '3') || cin.fail())
		{
			Set_TextColor(RED);
			cout << "请重新输入职称(1--教授 2--副教授 3--讲师)!" << endl;
			Set_TextColor(DEFAULT);
			cin.clear();
			cin.ignore();
		}
		setType(c_type);
		break;

	case 'C':
	case 'c':
		cin >> department;
		break;

	case 'D':
	case 'd':
		lessonID = ID;
		break;

	case 'E':
	case 'e':
		cin >> Lesson::lessonName;
		break;

	case 'F':
	case 'f':
		char c_mode;
		while (cin >> c_mode, !(c_mode == '1' || c_mode == '2' || c_mode == '3') || cin.fail())
		{
			Set_TextColor(RED);
			cout << "请重新输入课程类型(1--必修 2--限选 3--任选)!" << endl;
			Set_TextColor(DEFAULT);
			cin.clear();
			cin.ignore();
		}
		setLessonMode(c_mode);
		break;

	case 'G':
	case 'g':
	scanWeight:
		sum = 0;
		for (auto it = weight.begin(); it != weight.end(); it++)
		{
			cout << it->first << ':';
			while (cin >> it->second, !(it->second<1.0001 && it->second>-0.0001) || cin.fail())
			{
				Set_TextColor(RED);
				cout << "权重非法!" << endl;
				Set_TextColor(DEFAULT);
				cin.clear();
				cin.ignore();
			}
			sum += it->second;
		}
		if (sum <= 0.99 || sum >= 1.01)
		{
			Set_TextColor(RED);
			cout << "总权重不为1!" << endl;
			Set_TextColor(DEFAULT);
			goto scanWeight;
		}
		break;

	case 'H':
	case 'h':
	scanAdjust:
		while (cin >> policy.first, cin.fail())
		{
			cin.clear();
			cin.ignore();
			Set_TextColor(RED);
			cout << "输入非法!" << endl;
			Set_TextColor(DEFAULT);
		}
		while (cin >> policy.second, cin.fail())
		{
			cin.clear();
			cin.ignore();
			Set_TextColor(RED);
			cout << "输入非法!" << endl;
			Set_TextColor(DEFAULT);
		}
		if (policy.first < 1 || policy.second < 0)
		{
			Set_TextColor(RED);
			cout << "调分政策非法!" << endl;
			Set_TextColor(DEFAULT);
			goto scanAdjust;
		}
		break;

	case 'I':
	case 'i':
		while (cin >> credit, !(credit >= 1 && credit <= 15) || cin.fail())
		{
			Set_TextColor(RED);
			cout << "学分非法(建议为1-15)!" << endl;
			Set_TextColor(DEFAULT);
			cin.clear();
			cin.ignore();
		}
		break;
	}
}

void Teacher::getLessonInfo()
{
	string weightString;
	cout << std::setiosflags(ios::left);
	auto lesson = [](Lessontype l) -> const char*
	{
		switch (l)
		{
		case Lessontype::Compulsory:
			return "必修";
			break;
		case Lessontype::Limited:
			return "限选";
			break;
		case Lessontype::Optional:
			return "任选";
			break;
		default:
			return "NaN";
			break;
		}
	};
	cout << setw(40) << "任课教师" << name << endl;
	cout << setw(40) << "课程ID" << lessonID << endl;
	cout << setw(40) << "课程名称" << lessonName << endl;
	cout << setw(40) << "课程类型" << lesson(lessontype) << endl;
	GetTime();
	cout << setw(40) << "学分" << credit << endl;

	cout << setw(20) << "评分规则";
	for (auto it = weight.begin(); it != weight.end(); it++)
	{
		weightString += it->first;
		weightString += std::to_string(int(100 * (it->second))) + "% ";
	}
	cout << weightString << endl;
	cout << std::resetiosflags(ios::left);
}

void Teacher::getGPA() {}

void Teacher::ReadfromFile()
{
	ifstream f = filemanager->openFile_R(ID, user);
	char c_gender, c_jobtype;

	// 录入教师的基本信息
	f >> ID;
	f >> name;
	f >> c_gender;
	setGender(c_gender);
	f >> c_jobtype;
	setType(c_jobtype);
	f >> department;

	// 录入教师的课堂信息
	char c_lessontype;
	f >> lessonID;
	f >> lessonName;
	f >> c_lessontype;
	setLessonMode(c_lessontype);
	f >> credit;
	for (int i = 0; i < 5; i++)
	{
		f >> weight[i].first;
		f >> weight[i].second;
	}
	f >> policy.first;
	f >> policy.second;

	char c_weekmode;
	f >> c_weekmode;
	SetWeekType(c_weekmode);
	f >> lessontime[0].first;
	f >> lessontime[0].second;
	f >> lessontime[1].first;
	f >> lessontime[1].second;
	f.close();


}

void Teacher::WritetoFile()
{
	ofstream f = filemanager->openFile_W(ID, user);
	f << ID << " " << name << " " << short(gender) << " " << short(type) << " " << department << endl;
	f << lessonID << " " << lessonName << " " << short(lessontype) << " " << credit << endl;
	for (auto it = weight.begin(); it != weight.end(); it++)
	{
		f << it->first << " " << it->second << " ";
	}
	f << endl;
	f << policy.first << " " << policy.second;
	f << endl;
	f << short(weektype) << ' ';
	f << lessontime[0].first << ' ';
	f << lessontime[0].second << ' ';
	f << lessontime[1].first << ' ';
	f << lessontime[1].second << ' ';
	f.close();
}

const string Teacher::getLessonName()
{
	return lessonName;
}

Teacher::~Teacher() {}