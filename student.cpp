#include<iostream>
#include<iomanip>
#include"student.h"

using std::cin;
using std::cout;
using std::setw;
using std::endl;
using std::make_pair;


Student::Student()
{
	user = usertype::student;//确定类型
	name = "NaN";
}

void Student::init(string _ID)
{
	ID = string(_ID.c_str());
}

void Student::getBasicInfo()
{
	auto sex = [](gendertype g)->const char* {if (g == gendertype::male)  return "男"; else return "女"; };
	cout << std::setiosflags(ios::left);
	cout << setw(40) << "ID" << ID << endl;
	cout << setw(40) << "名字" << name << endl;
	cout << setw(40) << "性别" << sex(gender) << endl;
	cout << setw(40) << "年级" << grade << endl;
	cout << setw(40) << "班级" << admin_class << endl;
	cout << setw(40) << "专业" << department << endl;
	cout << std::resetiosflags(ios::left);
}

void Student::inputBasicInfo()
{
	char g;
	while (cin >> g, !(g == '1' || g == '2') || cin.fail())
	{
		Set_TextColor(RED);
		cout << "请重新输入性别(1--男 2--女)!" << endl;
		Set_TextColor(DEFAULT);
		cin.clear(); 
		cin.ignore(); 
	}
	while (cin >> grade, !(grade >= 1 && grade <= 4) || cin.fail())
	{
		Set_TextColor(RED);
		cout << "请重新输入年级(1-4)!" << endl;
		Set_TextColor(DEFAULT);
		cin.clear();
		cin.ignore();
	}
	while (cin >> admin_class, !(admin_class >= 1 && admin_class <= 10) || cin.fail())
	{
		Set_TextColor(RED);
		cout << "请重新输入行政班级(1-10)!" << endl;
		Set_TextColor(DEFAULT);
		cin.clear();
		cin.ignore();
	}
	cin >> department;
	switch (g)
	{
	case '1':
		gender = gendertype::male;
		break;
	case '2':
		gender = gendertype::female;
		break;
	}
}

void Student::changeBasicInfo(char a)
{
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
		while (cin >> grade, !(grade >= 1 && grade <= 4) || cin.fail())
		{
			Set_TextColor(RED);
			cout << "请重新输入年级(1-4)!" << endl;
			Set_TextColor(DEFAULT);
			cin.clear();
			cin.ignore();
		}
		break;
	case 'C':
	case 'c':
		while (cin >> admin_class, !(admin_class >= 1 && admin_class <= 10) || cin.fail())
		{
			Set_TextColor(RED);
			cout << "请重新输入行政班级(1-10)!" << endl;
			Set_TextColor(DEFAULT);
			cin.clear();
			cin.ignore();
		}
		break;
	case 'D':
	case 'd':
		cin >> department;
		break;
	}
}

void Student::getLessonInfo()
{

}

void Student::getGPA()
{
	double sum = 0;
	int scoredlessons = 0;
	cout << std::setiosflags(ios::left);
	for (auto it = GPA.begin(); it != GPA.end(); it++)
	{
		cout << setw(40) << it->first;
		if (it->second.first == NaN)
		{
			cout << setw(6) << "**";
		}
		else
		{
			cout << setw(6) << it->second.first;
			sum += it->second.first;
			++scoredlessons;
		}
		cout << it->second.second << endl;
	}
	cout << std::resetiosflags(ios::left);
	cout << endl;
	if (scoredlessons != 0)
	{
		cout << "均绩:" << sum / scoredlessons << endl;
	}
}

void Student::ReadfromFile()
{
	ifstream fi = filemanager->openFile_R(ID, user);
	char c_gender;

	//录入学生的基本信息
	fi >> ID;
	fi >> name;
	fi >> c_gender;
	setGender(c_gender);
	fi >> grade;
	fi >> admin_class;
	fi >> department;

	//录入学生的成绩信息
	int i = 0;
	string _lessonname, _rank;
	double _point;
	while (fi >> _lessonname)
	{
		fi >> _point;
		fi >> _rank;
		GPA.insert(make_pair(_lessonname, make_pair(_point, _rank)));
		i++;
	}
	fi.close();

}

void Student::WritetoFile()
{
	ofstream f = filemanager->openFile_W(ID, user);
	f << ID << " " << name << " " << short(gender) << " " << grade << " " << admin_class << " " << department << endl;
	for (auto it = GPA.begin(); it != GPA.end(); it++)
	{
		f << it->first << " " << it->second.first << " " << it->second.second << endl;
	}

	f.close();
}

void Student::setLesson(const string s)
{
	GPA.insert(std::make_pair(s, std::make_pair(NaN, "**")));
}

void Student::deleteLesson(const string s)
{
	GPAlist::iterator it = GPA.begin();
	while (it != GPA.end())
	{
		if (it->first == s)
		{
			GPA.erase(it++);
		}
		else
		{
			it++;
		}
	}
}

bool Student::operator>(const Person& p)
{
	return true;
}

void Student::GPAinit(const string lessonName, const int totalgrade)
{
	auto it = GPA.find(lessonName);
	it->second = score_to_GPA(totalgrade);
}

