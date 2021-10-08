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
			return "��";
		case gendertype::female:
			return "Ů";
		default:
			return "NaN";
		}
	};

	auto job = [](jobtype j) -> const char*
	{
		switch (j)
		{
		case jobtype::lecturer:
			return "��ʦ";
		case jobtype::professor:
			return "����";
		case jobtype::associate_professor:
			return "������";
		default:
			return "NaN";
		}
	};

	cout << std::setiosflags(ios::left);
	cout << setw(40) << "ID" << ID << endl;
	cout << setw(40) << "����" << name << endl;
	cout << setw(40) << "�Ա�" << sex(gender) << endl;
	cout << setw(40) << "ְ��" << job(type) << endl;
	cout << setw(40) << "רҵ" << department << endl;
	cout << std::resetiosflags(ios::left);
}

void Teacher::inputBasicInfo()
{
	char c_gender, c_type;
	while (cin >> c_gender, !(c_gender == '1' || c_gender == '2') || cin.fail())
	{
		Set_TextColor(RED);
		cout << "�����������Ա�(1--�� 2--Ů)!" << endl;
		Set_TextColor(DEFAULT);
		cin.clear();
		cin.ignore();
	}

	while (cin >> c_type, !(c_type == '1' || c_type == '2' || c_type == '3') || cin.fail())
	{
		Set_TextColor(RED);
		cout << "����������ְ��(1--���� 2--������ 3--��ʦ)!" << endl;
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
			cout << "�����������Ա�(1--�� 2--Ů)!" << endl;
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
			cout << "����������ְ��(1--���� 2--������ 3--��ʦ)!" << endl;
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
			cout << "����������γ�����(1--���� 2--��ѡ 3--��ѡ)!" << endl;
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
				cout << "Ȩ�طǷ�!" << endl;
				Set_TextColor(DEFAULT);
				cin.clear();
				cin.ignore();
			}
			sum += it->second;
		}
		if (sum <= 0.99 || sum >= 1.01)
		{
			Set_TextColor(RED);
			cout << "��Ȩ�ز�Ϊ1!" << endl;
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
			cout << "����Ƿ�!" << endl;
			Set_TextColor(DEFAULT);
		}
		while (cin >> policy.second, cin.fail())
		{
			cin.clear();
			cin.ignore();
			Set_TextColor(RED);
			cout << "����Ƿ�!" << endl;
			Set_TextColor(DEFAULT);
		}
		if (policy.first < 1 || policy.second < 0)
		{
			Set_TextColor(RED);
			cout << "�������߷Ƿ�!" << endl;
			Set_TextColor(DEFAULT);
			goto scanAdjust;
		}
		break;

	case 'I':
	case 'i':
		while (cin >> credit, !(credit >= 1 && credit <= 15) || cin.fail())
		{
			Set_TextColor(RED);
			cout << "ѧ�ַǷ�(����Ϊ1-15)!" << endl;
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
			return "����";
			break;
		case Lessontype::Limited:
			return "��ѡ";
			break;
		case Lessontype::Optional:
			return "��ѡ";
			break;
		default:
			return "NaN";
			break;
		}
	};
	cout << setw(40) << "�ον�ʦ" << name << endl;
	cout << setw(40) << "�γ�ID" << lessonID << endl;
	cout << setw(40) << "�γ�����" << lessonName << endl;
	cout << setw(40) << "�γ�����" << lesson(lessontype) << endl;
	GetTime();
	cout << setw(40) << "ѧ��" << credit << endl;

	cout << setw(20) << "���ֹ���";
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

	// ¼���ʦ�Ļ�����Ϣ
	f >> ID;
	f >> name;
	f >> c_gender;
	setGender(c_gender);
	f >> c_jobtype;
	setType(c_jobtype);
	f >> department;

	// ¼���ʦ�Ŀ�����Ϣ
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