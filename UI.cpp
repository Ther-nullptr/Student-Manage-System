#include<Windows.h>
#include<algorithm>
#include"UI.h"

//����ѭ������ʱ�����ݵ�ȫ�ֶ���,ͨ������ָ����й���
extern Student student;
extern Teacher teacher;

//����Ա����,���ܿ��ڻ���ָ��
extern Affairs affair;

//ȫ���ļ��������
extern File f;

//����ƥ��ID
std::regex allNumbers("\\d{5,12}"); 

//���ƿ���̨������ɫ
//0 = ��ɫ��1 = ��ɫ��2 = ��ɫ��3 = ����ɫ��4 = ��ɫ��5 = ��ɫ��6 = ��ɫ��7 = ��ɫ��8 = ��ɫ��9 = ����ɫ
void Set_TextColor(int color)
{
	if (color >= 0 && color <= 15)	//������0-15�ķ�Χ��ɫ    	
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	else	//Ĭ�ϵ���ɫ��ɫ 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

//���ƿ���̨������ɫ
//16:�� 32:�� 64:�� 128:��ɫ
void Set_BackgroundColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


UI::UI()
{
	pptr = nullptr;
	filemanager = &f;
	ifstream fi;
	//��ʼ��ѧ������ʦ�б�
	mapInit();
}


void UI::mapInit()
{
	f.findAllFiles(usertype::student);
	f.findAllFiles(usertype::teacher);
	for (auto it = filemanager->filelist.studentFiles.begin(); it != filemanager->filelist.studentFiles.end(); it++)
	{
		Student _student;//ר�����ڶ�ȡ�ļ���ѧ������
		_student.init(*it);//��ʼ������,�Ա��ҵ���Ӧ���ļ����ж���
		_student.ReadfromFile();//������Ϣ
		info.Rstudentinfo.insert(make_pair(_student.getID(), _student));//��ID������Ϊ��������ÿһ��ѧ������Ϣ
	}
	for (auto it = filemanager->filelist.teacherFiles.begin(); it != filemanager->filelist.teacherFiles.end(); it++)
	{
		Teacher _teacher;//ר�����ڶ�ȡ�ļ��Ľ�ʦ����
		_teacher.init(*it);//��ʼ������,�Ա��ҵ���Ӧ���ļ����ж���
		_teacher.ReadfromFile();//������Ϣ
		info.Rteacherinfo.insert(make_pair(_teacher.getID(), _teacher));//��ID������Ϊ��������ÿһ����ʦ����Ϣ
	}
}


void UI::showStartMenu() //��ʼ����,ֻ���¼,��¼��Ϣ�ͻᱻ�Զ�¼���ļ�
{
	system("cls");
	char num;
	statusflag = 1;
	cout << instructions << endl;
	cout << endl;
	pptr = nullptr;
	do
	{
		cout << "�����������:(1--ѧ�� 2--��ʦ 3--����),��'Q'�˳�,��'H'��ȡ����:";
		cin >> num;
		switch (num)
		{
		case '1':
			user = usertype::student;
			pptr = &student;
			statusflag = 1;
			break;

		case '2':
			user = usertype::teacher;
			pptr = &teacher;
			statusflag = 1;
			break;

		case '3':
			user = usertype::academic_affairs;
			statusflag = 1;
			break;

		case 'Q':
		case 'q':
			Exit();
			break;

		case 'H':
		case 'h':
			getHelp();
			break;

		default:
			statusflag = 0;
			Set_TextColor(RED);
			cout << errormsg << endl;
			Set_TextColor(DEFAULT);
		}
		cin.ignore();
	} while (statusflag == 0);

}

void UI::getHelp()
{
	system("cls");
	cout << "��ϵͳӵ������ʹ��ģʽ:ѧ��ģʽ����ʦģʽ������ģʽ��" << endl;
	cout << "��ʹ��ѧ��ģʽ���ʦģʽ,��Ҫ����ID��" << endl;
	cout << endl;

	Set_BackgroundColor(B_BLUE);
	cout << "ѧ��ģʽ" << endl;
	Set_BackgroundColor(DEFAULT);
	cout << "1.(A)�鿴������Ϣ�����ID���������Ա��꼶���༶��רҵ��" << endl;
	cout << "2.(B)¼�������Ϣ�����������Ϣ�������꼶���༶��ϵ���Ա�ȣ�ID�������Ѿ����Ⱦ�����󶨣������ڴ�ѡ�����޸ģ��������ڳ��ε�¼��" << endl;
	cout << "3.(C)�޸ĸ�����Ϣ��������Ӧ��ĸ���޸�����Ķ�Ӧѡ������ڵ�¼��ĵ�����" << endl;
	cout << "4.(D)�鿴���޿γ���Ϣ���鿴Ŀǰ�������޿γ̵����ơ������Լ�������" << endl;
	cout << "5.(E)�鿴���пγ���Ϣ���鿴Ŀǰ���п���γ̵���Ϣ��" << endl;
	cout << "6.(F)ѡ�Σ�����γ̵�ID�����Է��ؿγ̵Ŀ�����Ϣ���γ��������ν�ʦ�����ֱ�׼�ȣ���ѧ�����Ը��ݿγ���Ϣѡ������Ҫ�Ŀγ̡�" << endl;
	cout << "7.(G)�˿Σ�����γ̵�ID�������˵����ſγ̡�" << endl;
	cout << "8.(X)ʵ����֤�������˺ų��ε�¼����ᱻҪ�����ʵ����֤�����û���ʵ����������һ���󶨽��޷��޸ġ�" << endl; 
	cout << "9.(Y)�˳���¼���˳���ǰ�˺ţ����浱ǰ¼�����Ϣ�����ص�¼���档" << endl;
	cout << "10.(Z)�˳������˳���ǰ����" << endl;
	cout << endl;

	Set_BackgroundColor(B_GREEN);
	cout << "��ʦģʽ" << endl;
	Set_BackgroundColor(DEFAULT);
	cout << "1.(A)�鿴������Ϣ�����ID���������Ա�ְ�ơ�רҵ��" << endl;
	cout << "2.(B)¼�������Ϣ��ͬѧ��ģʽ" << endl;
	cout << "3.(C)�޸ĸ�����Ϣ��ͬѧ��ģʽ��" << endl;
	cout << "4.(D)�鿴���̿γ���Ϣ���γ̵�ID���ον�ʦ�����ơ����͡�ʱ�䡢ѧ�֡����ֹ���" << endl;
	cout << "5.(E)�鿴���пγ���Ϣ��ͬѧ��ģʽ��" << endl;
	cout << "6.(F)¼�����̿γ���Ϣ��¼�����̿γ̵����ơ����͡�ʱ�䡢���ֹ���ȡ�" << endl;
	cout << "7.(G)�鿴ѧ��������Ϣ���鿴���б���ѧ���ļ��㣬��ѡ���Ƿ��ռ���ߵ�����" << endl;
	cout << "8.(H)¼��ɼ���Ϊ����δ��óɼ��ı���ѧ��¼�����ɼ���" << endl;
	cout << "9.(X)ʵ����֤��ͬѧ��ģʽ��" << endl;
	cout << "10.(Y)�˳���¼��ͬѧ��ģʽ��" << endl;
	cout << "11.(Z)�˳�����ͬѧ��ģʽ��" << endl;
	cout << endl;

	Set_BackgroundColor(B_RED);
	cout << "����ģʽ" << endl;
	Set_BackgroundColor(DEFAULT);
	cout << "1.(A)����ѧ����Ϣ������ѧ��ID���������ѧ����������Ϣ��" << endl;
	cout << "2.(B)���ҽ�ʦ��Ϣ�������ʦID�����������ʦ��������Ϣ��" << endl;
	cout << "3.(C)ɾ��ѡ����Ϣ������ID��ɾ��ĳһѧ����ĳһ��ʦ��ȫ����Ϣ��" << endl;
	cout << "4.(D)ɾ��ȫ����Ϣ��������ݿ⡣" << endl;
	cout << "5.(Y)�˳���¼��ͬѧ��ģʽ��" << endl;
	cout << "6.(Z)�˳�����ͬѧ��ģʽ��" << endl;
	cout << endl;

	while (1)
	{
		if (_getch())
			longjmp(StartMenu, 1);
	}

}

void UI::showLoginMenu()
{
	system("cls");
	string  ID;
	cout << "����֤������(5-12λ,������):";
	while(cin >> ID, !regex_match(ID, allNumbers)||cin.fail())
	{
		Set_TextColor(RED);
		cout << "���Ϸ���ID!ID��Ϊ5-12λ�Ĵ������ַ���,�����¼���!"<<endl;
		Set_TextColor(DEFAULT);
		cin.clear();
		cin.ignore();
	}
	pptr->init(ID);
	Set_TextColor(GREEN);
	cout << "��¼�ɹ�" << endl;
	Set_TextColor(DEFAULT);
	pptr->ReadfromFile();
	Sleep(2000);
}

char UI::showStudentMenu()
{
	system("cls");
	cout << choosemode << endl;
	cout << "A.�鿴������Ϣ" << endl;
	cout << "B.¼�������Ϣ" << endl;
	cout << "C.�޸ĸ�����Ϣ" << endl;
	cout << "D.�鿴���޿γ���Ϣ" << endl;
	cout << "E.�鿴���пγ���Ϣ" << endl;
	cout << "F.ѡ��" << endl;
	cout << "G.�˿�" << endl;
	Set_TextColor(YELLOW);
	cout << "X.ʵ����֤" << endl;
	Set_TextColor(DEFAULT);
	Set_TextColor(PURPLE);
	cout << "Y.�˳���¼" << endl;
	Set_TextColor(DEFAULT);
	Set_TextColor(RED);
	cout << "Z.�˳�����" << endl;
	Set_TextColor(DEFAULT);
	if (pptr->getName() == "NaN")
	{
		Set_TextColor(RED);
		cout << "����δ�����,�밴X,��ʱ��ʵ�����!" << endl;
		Set_TextColor(DEFAULT);
	}
	else
	{
		Set_TextColor(GREEN);
		cout << "��ӭʹ��," << pptr->getName() << endl;
		Set_TextColor(DEFAULT);
	}
	char c_mode;
	cin >> c_mode;
	return c_mode;
}

char UI::showTeacherMenu()
{
	system("cls");
	cout << choosemode << endl;
	cout << "A.�鿴������Ϣ" << endl;
	cout << "B.¼�������Ϣ" << endl;
	cout << "C.�޸ĸ�����Ϣ" << endl;
	cout << "D.�鿴���̿γ���Ϣ" << endl;
	cout << "E.�鿴���пγ���Ϣ" << endl;
	cout << "F.¼�����̿γ���Ϣ" << endl;
	cout << "G.�鿴ѧ��������Ϣ" << endl;
	cout << "H.¼��ɼ�" << endl;
	Set_TextColor(YELLOW);
	cout << "X.ʵ����֤" << endl;
	Set_TextColor(DEFAULT);
	Set_TextColor(PURPLE);
	cout << "Y.�˳���¼" << endl;
	Set_TextColor(DEFAULT);
	Set_TextColor(RED);
	cout << "Z.�˳�����" << endl;
	Set_TextColor(DEFAULT);

	if (pptr->getName() == "NaN")
	{
		Set_TextColor(RED);
		cout << "����δ�����,�밴X,��ʱ��ʵ�����!" << endl;
		Set_TextColor(DEFAULT);
	}
	else
	{
		Set_TextColor(GREEN);
		cout << "��ӭʹ��," << pptr->getName() << endl;
		Set_TextColor(DEFAULT);
	}

	if (teacher.getLessonName() == "NaN")
	{
		Set_TextColor(RED);
		cout << "����δ¼�����Ŀγ���Ϣ,�밴E,��ʱ¼��γ���Ϣ!" << endl;
		Set_TextColor(DEFAULT);
	}

	char c_mode;
	cin >> c_mode;
	return c_mode;
}

char UI::showAffairMenu()
{
	system("cls");
	cout << choosemode << endl;
	cout << "A.����ѧ����Ϣ" << endl;
	cout << "B.���ҽ�ʦ��Ϣ" << endl;
	cout << "C.ɾ��ѡ����Ϣ" << endl;
	cout << "D.ɾ��ȫ����Ϣ" << endl;
	Set_TextColor(PURPLE);
	cout << "Y.�˳���¼" << endl;
	Set_TextColor(DEFAULT);
	Set_TextColor(RED);
	cout << "Z.�˳�����" << endl;
	Set_TextColor(DEFAULT);
	char c_mode;
	cin >> c_mode;
	return c_mode;
}

void UI::showEndMenu()
{
	system("cls");
	//ÿһ��ʹ����Ϻ󣬶����������Ϣд���ļ���
	cout << "��л����ʹ��!" << endl;
}

void UI::showBasicInfo_Student()
{

	system("cls");
	cout << basicinfo << endl;
	cout << crossline1 << endl;
	pptr->getBasicInfo();
	cout << crossline1 << endl;
	cout << pressinfo << endl;
	while (1)
	{
		if (_getch())
			break;
	}

}

void UI::inputBasicInfo_Student()
{
	system("cls");
	cout << "�����μ���:1.�Ա�(1--�� 2--Ů) 2.�꼶(���ֱ��(1-4)) 3.�����༶(���ֱ��(1-10)) 4.רҵ����" << endl;
	pptr->inputBasicInfo();
	Set_TextColor(GREEN);
	cout << inputmsg << endl;
	Set_TextColor(DEFAULT);
	Sleep(2000);

}

void UI::changeBasicInfo_Student()
{
change_BasicInfo_Student:
	char c_put;
	system("cls");
	cout << "�޸�������Ϣ(�����A,B,C,D)" << endl;
	Set_TextColor(BLUE);
	cout << "A.�Ա� B.�꼶 C.�����༶ D.רҵ" << endl;
	Set_TextColor(DEFAULT);
	cin >> c_put;
	switch (c_put)
	{
	case 'A':
	case 'a':
		cout << "������Ա�(1--�� 2--Ů):";
		pptr->changeBasicInfo('a');
		break;

	case 'B':
	case 'b':
		cout << "������꼶(���ֱ��):";
		pptr->changeBasicInfo('b');
		break;

	case 'C':
	case 'c':
		cout << "����������༶(���ֱ��):";
		pptr->changeBasicInfo('c');
		break;

	case 'D':
	case 'd':
		cout << "�����רҵ:";
		pptr->changeBasicInfo('d');
		break;

	default:
		Set_TextColor(RED);
		cout << errormsg << endl;
		Set_TextColor(DEFAULT);
		Sleep(1000);
		goto change_BasicInfo_Student;
	}

	Set_TextColor(GREEN);
	cout << changedmsg << endl;
	Set_TextColor(DEFAULT);
	Sleep(2000);
}

void UI::lessons()
{
	cout << "�γ��б�����:" << endl;
	auto _list = student.getGPAlist();
	
	for (auto it = info.Rteacherinfo.begin(); it != info.Rteacherinfo.end(); it++)
	{
		cout << crossline1 << endl;
		it->second.getLessonInfo();

		if (_list.find(it->second.getLessonName()) == _list.end())//δ�����ÿγ�
		{
			Set_TextColor(RED);
			cout << "(δѡ)" << endl;
			Set_TextColor(DEFAULT);
		}
		else
		{
			Set_TextColor(GREEN);
			cout << "(��ѡ)" << endl;
			Set_TextColor(DEFAULT);
		}
		cout << crossline1 << endl;
	}
}

void UI::getLessons_Student()
{
	system("cls");
	lessons();

	cout << pressinfo << endl;
	while (1)
	{
		if (_getch())
		{
			break;
		}
	}
}

void UI::getGPA()
{
	system("cls");

	cout << "�����޿γ̵�GPA����:" << endl;//TODO
	cout << crossline1 << endl;
	cout << "�γ�����" << setw(35) << "����" << setw(6) << "�ȼ�" << endl;

	pptr->getGPA();
	cout << crossline1 << endl;

	cout << pressinfo << endl;
	while (1)
	{
		if (_getch())
		{
			break;
		}
	}
}

void UI::chooseLessons()
{
chooselesson_student:
	system("cls");
	lessons();
	auto _list = student.getGPAlist();
	cout << endl;

	cout << "����γ�ID,��ʵ��ѡ�β���:" << endl;
	string _index;
	while (cin >> _index, !regex_match(_index, allNumbers) || cin.fail())
	{
		Set_TextColor(RED);
		cout << "���Ϸ���ID!ID��Ϊ5-12λ�Ĵ������ַ���,�����¼���!"<<endl;
		Set_TextColor(DEFAULT);
		cin.clear();
		cin.ignore();
	}

	auto it = info.Rteacherinfo.find(_index);
	
	if (it == info.Rteacherinfo.end())
	{
		Set_TextColor(RED);
		cout << "δ�ܲ��ҵ��γ�ID,�����¼���!" << endl;
		Set_TextColor(DEFAULT);
		Sleep(2000);
	}
	else if (_list.find(it->second.getLessonName()) != _list.end())
	{
		Set_TextColor(RED);
		cout << "����ѡ��ÿγ�!" << endl;
		Set_TextColor(DEFAULT);
		Sleep(2000);
	}
	else
	{
		cout << crossline1 << endl;
		it->second.getLessonInfo();
		cout << crossline1 << endl;
		cout << "ȷ��ѡ��˿γ�(Y--�� ����--��)?" << endl;
		char c1;
		cin >> c1;
		if (c1 == 'Y' || c1 == 'y')
		{
			student.setLesson(it->second.getLessonName());
			Set_TextColor(GREEN);
			cout << "ѡ�γɹ�!" << endl;
			Set_TextColor(DEFAULT);
			Sleep(2000);
		}
	}
	char c2;
	cout << "�Ƿ����ѡ��(Y--�� ����--��)" << endl;
	cin >> c2;
	if (c2 == 'Y' || c2 == 'y')
	{
		goto chooselesson_student;
	}
}

void UI::deleteLessons()
{
deletelesson_student:
	system("cls");
	lessons();
	auto _list = student.getGPAlist();
	cout << endl;

	cout << "��������Ҫ�˵��Ŀγ̵�ID:" << endl;
	string _ID;
	while (cin >> _ID, !regex_match(_ID, allNumbers) || cin.fail())
	{
		Set_TextColor(RED);
		cout << "���Ϸ���ID!ID��Ϊ5-12λ�Ĵ������ַ���,�����¼���!" << endl;
		Set_TextColor(DEFAULT);
		cin.clear();
		cin.ignore();
	}

	auto it = info.Rteacherinfo.find(_ID);
	if (it == info.Rteacherinfo.end())
	{
		Set_TextColor(RED);
		cout << "δ�ܲ��ҵ��γ�ID,�����¼���!" << endl;
		Set_TextColor(DEFAULT);
		Sleep(2000);
	}
	else if (_list.find(it->second.getLessonName()) == _list.end())
	{
		Set_TextColor(RED);
		cout << "��δѡ��ÿγ�!" << endl;
		Set_TextColor(DEFAULT);
		Sleep(2000);
	}
	else 
	{
		cout << "�˿κ�,�����޷���øÿγ̵�ѧ��,ȷ�ϼ�����(Y--�� ����--��):" << endl;
		char c1;
		cin >> c1;
		if (c1 == 'Y' || c1 == 'y')
		{
			student.deleteLesson(it->second.getLessonName());
			Set_TextColor(GREEN);
			cout << "�˿γɹ�!" << endl;
			Set_TextColor(DEFAULT);
			Sleep(2000);
		}
	}

	cout << "�Ƿ�����˿�(Y--�� ����--��):"<<endl;
	char c2;
	cin >> c2;
	if (c2 == 'Y' || c2 == 'y')
	{
		goto deletelesson_student;
	}
}

void UI::showBasicInfo_Teacher()
{
	system("cls");
	cout << basicinfo << endl;
	cout << crossline1 << endl;
	pptr->getBasicInfo();
	cout << crossline1 << endl;
	cout << pressinfo << endl;
	while (1)
	{
		if (_getch())
		{
			break;
		}
	}
}

void UI::inputBasicInfo_Teacher()
{
	system("cls");
	cout << "�����μ���:1.�Ա�(1--�� 2--Ů) 2.ְ��(1--���� 2--������ 3--��ʦ) 3.רҵ����" << endl;
	Set_TextColor(BLUE);
	cout << "����������̿γ̵���Ϣ,��ѡ��'¼�����̿γ���Ϣ'ѡ��" << endl;
	Set_TextColor(DEFAULT);
	pptr->inputBasicInfo();
	Set_TextColor(GREEN);
	cout << inputmsg << endl;
	Sleep(2000);
	Set_TextColor(DEFAULT);
}

void UI::changeBasicInfo_Teacher()
{
	char c_put;
	system("cls");
	cout << "�޸�������Ϣ(�����A,B,C)" << endl;
	Set_TextColor(BLUE);
	cout << "A.�Ա� B.ְ�� C.רҵ" << endl;
	Set_TextColor(DEFAULT);
	cin >> c_put;
	switch (c_put)
	{
	case 'A':
	case 'a':
		cout << "������Ա�(1--�� 2--Ů):";
		pptr->changeBasicInfo('a');
		break;

	case 'B':
	case 'b':
		cout << "�����ְ��(1--���� 2--������ 3--��ʦ):";
		pptr->changeBasicInfo('b');
		break;

	case 'C':
	case 'c':
		cout << "�����רҵ:";
		pptr->changeBasicInfo('c');
		break;

	}
	Set_TextColor(GREEN);
	cout << changedmsg << endl;
	Sleep(2000);
	Set_TextColor(DEFAULT);
}

void UI::setLessons()
{
setlessons:
	system("cls");
	pptr->changeBasicInfo('d');
	cout << "�������Ŀγ�����:" << endl;
	pptr->changeBasicInfo('e');
	cout << "����γ�����(1--���� 2--��ѡ 3--��ѡ):" << endl;
	pptr->changeBasicInfo('f');
	cout << "����γ�ѧ��:" << endl;
	pptr->changeBasicInfo('i');
	cout << "����γ�ʱ��:" << endl;
	setLessonTime();
	cout << "�������Ŀγ�����Ȩ��(����Ϊǩ����ƽʱ��ҵ������ҵ�����п��ԡ���ĩ����,Ȩ��֮�ͱ���Ϊ1):" << endl;
	pptr->changeBasicInfo('g');
	cout << "�������ĵ�������(��������a(a>=1)��b(b>=0)):" << endl;
	Set_TextColor(BLUE);
	cout << "�����ɼ�x�����ճɼ�y�����¹�ϵ:y=ax+b,y���Ϊ100.����Ŀѧ�����ɼ�." << endl;
	Set_TextColor(DEFAULT);
	pptr->changeBasicInfo('h');

	Set_TextColor(RED);
	cout << "�γ���Ϣһ��¼�뽫�޷��޸�,�Ƿ�ȷ��(Y--�� ����--��)?" << endl;
	Set_TextColor(DEFAULT);
	char c;
	cin >> c;
	if (c == 'Y' || c == 'y')
	{
		Set_TextColor(GREEN);
		cout << inputmsg << endl;
		Set_TextColor(DEFAULT);
		Sleep(2000);
	}
	else
	{
		goto setlessons;
	}
}

void UI::setLessonTime()
{
	cout << "�γ�����(1--ȫ�� 2--ǰ���� 3--�����):"<<endl;
	teacher.SetTime('5');
	cout << "��ʱһ(�����������ںͽڴ�):"<<endl;
	teacher.SetTime('1');
	teacher.SetTime('3');
	char _c;
	cout << "�Ƿ���ӿ�ʱ2(Y--�� ����--��)?:"<<endl;
	cin >> _c;
	if (_c == 'Y' || _c == 'y')
	{
		cout << "��ʱ��(�����������ںͽڴ�):"<<endl;
		teacher.SetTime('2');
		teacher.SetTime('4');
	}
}

void UI::getStudentList()//��Ӧ����ȫ��һ���ļ��Ĳ���
{
	std::map<index, Student>::iterator it;
	system("cls");

	char mode;
	cout << "�Ƿ�����GPA�ߵ�����(Y--�� ����--��)?" << endl;
	cin >> mode;

	cout << "����ѡ��ѧ����GPA����:" << endl;
	cout << crossline1 << endl;
	cout << "ѧ��" << setw(16) << "����" << setw(14) << "�ȼ�" << endl;
	cout << crossline1 << endl;

	if (mode == 'Y' || mode == 'y')
	{
		std::vector<Ordered_stu_info> ordered_stu_vector;
		for (it = info.Rstudentinfo.begin(); it != info.Rstudentinfo.end(); it++)
		{
			Student _s = it->second;
			GPAlist _GPAlist = _s.getGPAlist();
			string _lessonname = teacher.getLessonName();
			auto GPAit = _GPAlist.find(_lessonname);//Ѱ��ѧ���Ƿ����Լ���
			if (GPAit != _GPAlist.end())//ѧ������
			{
				ordered_stu_vector.push_back(std::make_pair(_s.getName(),GPAit->second));//����ѧ���������Լ��ɼ�
			}
		}

		std::sort(ordered_stu_vector.begin(), ordered_stu_vector.end(), SortRule());//����

		
		for (auto it2 = ordered_stu_vector.begin(); it2 != ordered_stu_vector.end(); it2++)//�����Ϣ
		{
			cout <<it2->first<< setw(14);
			if (it2->second.first == NaN)
			{
				cout << "**" << setw(14);
			}
			else
			{
				cout << it2->second.first << setw(14);
			}
			cout << it2->second.second << endl;
		}
		
	}

	else 
	{
		for (it = info.Rstudentinfo.begin(); it != info.Rstudentinfo.end(); it++)
		{
			Student _s = it->second;
			GPAlist _GPAlist = _s.getGPAlist();
			string _lessonname = teacher.getLessonName();
			auto GPAit = _GPAlist.find(_lessonname);//Ѱ��ѧ���Ƿ����Լ���
			if (GPAit != _GPAlist.end())//ѧ������
			{
				cout << it->second.getName() << setw(6);
				if (GPAit->second.first == NaN)
				{
					cout << "**" << setw(6);
				}
				else
				{
					cout << GPAit->second.first << setw(6);
				}
				cout << GPAit->second.second << endl;
			}
		}

	}

	cout << crossline1 << endl;

	cout << pressinfo << endl;
	while (1)
	{
		if (_getch())
			break;
	}
}

void UI::inputGrade()
{
	system("cls");
	const string _string[5] = { "ǩ��:","ƽʱ��ҵ:","����ҵ:","���п���:","��ĩ����:" };
	bool emptyclass = 1;
	double gradelist[5];
	int totalgrade = 0;
	gradeWeight weight;
	adjustPolicy policy;

	Set_TextColor(BLUE);
	cout << "ע:ÿһ������־�Ϊ100��" << endl;
	Set_TextColor(DEFAULT);

	std::map<index, Student>::iterator it;
	for (it = info.Rstudentinfo.begin(); it != info.Rstudentinfo.end(); it++)
	{
		Student _s = it->second;
		GPAlist _GPAlist = _s.getGPAlist();
		string _lessonname = teacher.getLessonName();
		auto GPAit = _GPAlist.find(_lessonname);//Ѱ��ѧ���Ƿ����Լ���
		if (GPAit != _GPAlist.end() && GPAit->second.first == NaN)//ѧ������,�ҳɼ��Ѿ���¼��
		{
			//¼��ɼ�
			emptyclass = 0;
			totalgrade = 0;
			cout << "��Ϊ" << _s.getName() << "¼��ɼ�:" << endl;
			for (int i = 0; i < 5; i++)
			{
				cout << _string[i];
				while (cin >> gradelist[i], !(gradelist[i] >= 0 && gradelist[i] <= 100) || cin.fail())
				{
					Set_TextColor(RED);
					cout << "�������������(0-100)!" << endl;
					Set_TextColor(DEFAULT);
					cin.clear();
					cin.ignore();
				}
			}

			//��������
			weight = teacher.getweight();
			for (int i = 0; i < 5; i++)
			{
				totalgrade += weight[i].second * gradelist[i];
			}

			//����
			policy = teacher.getpolicy();
			totalgrade *= policy.first;
			totalgrade += policy.second;
			if (totalgrade > 100)
			{
				totalgrade = 100;
			}

			//Ϊѧ��¼��ɼ�
			_s.GPAinit(teacher.getLessonName(), totalgrade);

			//�����ĺ��ѧ����Ϣ���뵽��Ҫ¼���ļ���list��
			info.Wstudentinfo.push_back(_s);
			cout << endl;
		}
	}
	if (emptyclass)
	{
		Set_TextColor(RED);
		cout << "��ǰû���κ�ѧ��ѡ�����Ŀλ�����ѧ���ĳɼ����Ѿ���¼��!" << endl;
		Set_TextColor(DEFAULT);
		Sleep(2000);
	}
	else
	{
		Set_TextColor(GREEN);
		cout << inputmsg << endl;
		Set_TextColor(DEFAULT);
		Sleep(2000);
	}
}

void UI::getLessons_Teacher()
{
	system("cls");
	cout << basicinfo << endl;
	cout << crossline1 << endl;
	pptr->getLessonInfo();
	cout << crossline1 << endl;
	cout << pressinfo << endl;
	while (1)
	{
		if (_getch())
			break;
	}
}

void UI::getLessons_Teacher_2()
{
	getLessons_Student();
}

void UI::getStudentAllInfo()
{
get_Student_Info:
	system("cls");
	cout << "Ŀǰ����ϵͳ�е�ѧ��ID�б�����:" << endl;
	affair.getStudentID();
	cout << crossline1 << endl;
	cout << "����ѧ��ID,��ʵ�ֲ�ѯ����:" << endl;
	string _ID;
	cin >> _ID;

	if (std::find(f.filelist.studentFiles.cbegin(), f.filelist.studentFiles.cend(), _ID) != f.filelist.studentFiles.cend())//�ҵ��ļ�
	{
		Student _s;
		_s.init(_ID);
		affair.GetStudentInfo(_s);
		cout << endl;
	}
	else
	{
		Set_TextColor(RED);
		cout << "��ǰ�б���û�и�ѧ������Ϣ!" << endl;
		Set_TextColor(DEFAULT);
		Sleep(2000);
	}

	cout << "�Ƿ��������(Y--�� ����--��)?" << endl;
	char _c;
	cin >> _c;
	if (_c == 'Y' || _c == 'y')
	{
		goto get_Student_Info;
	}
}

void UI::getTeacherAllInfo()
{
get_Teacher_Info:
	system("cls");
	cout << "Ŀǰ����ϵͳ�еĽ�ʦID�б�����:" << endl;
	affair.getTeacherID();
	cout << crossline1 << endl;
	cout << "�����ʦID,��ʵ�ֲ�ѯ����:" << endl;
	string _ID;
	cin >> _ID;
	if (std::find(f.filelist.teacherFiles.cbegin(), f.filelist.teacherFiles.cend(), _ID) != f.filelist.teacherFiles.cend())//�ҵ��ļ�
	{
		Teacher _t;
		_t.init(_ID);
		affair.GetTeacherInfo(_t);
		cout << endl;
	}
	else
	{
		Set_TextColor(RED);
		cout << "��ǰ�б���û�иý�ʦ����Ϣ!" << endl;
		Set_TextColor(DEFAULT);
		Sleep(2000);
	}

	cout << "�Ƿ��������(Y--�� ����--��)?" << endl;
	char _c;
	cin >> _c;
	if (_c == 'Y' || _c == 'y')
	{
		goto get_Teacher_Info;
	}
}

void UI::deleteInfo()
{
delete_Info:
	system("cls");
	cout << "��������Ҫɾ������Ϣ����(S--ѧ�� T--��ʦ):" << endl;
	char _c;
	string _ID;
	cin >> _c;
	switch (_c)
	{

	case 'S':
	case 's':
		cout << "Ŀǰ����ϵͳ�е�ѧ��ID�б�����:" << endl;
		affair.getStudentID();
		cout << crossline1 << endl;
		cout << "��������Ҫɾ����ID:" << endl;
		cin >> _ID;
		if (f.filelist.studentFiles.count(_ID)==1)//�ҵ��ļ�
		{
			bool _status = affair.DeleteInfo(usertype::student, _ID);
			if (!_status)
			{
				Set_TextColor(GREEN);
				cout << "ɾ���ɹ�!" << endl;
				Set_TextColor(DEFAULT);
				Sleep(2000);
			}
		}
		else
		{
			Set_TextColor(RED);
			cout << "��ǰ�б���û�и�ѧ������Ϣ!" << endl;
			Set_TextColor(DEFAULT);
			Sleep(2000);
		}
		break;

	case 'T':
	case 't':
		cout << "Ŀǰ����ϵͳ�еĽ�ʦID�б�����:" << endl;
		affair.getTeacherID();
		cout << crossline1 << endl;
		cout << "��������Ҫɾ����ID:" << endl;
		cin >> _ID;		
		if (f.filelist.teacherFiles.count(_ID) == 1)//�ҵ��ļ�
		{
			bool _status = affair.DeleteInfo(usertype::teacher, _ID);
			if (!_status)
			{
				Set_TextColor(GREEN);
				cout << "ɾ���ɹ�!" << endl;
				Set_TextColor(DEFAULT);
				Sleep(2000);
			}
		}
		else
		{
			Set_TextColor(RED);
			cout << "��ǰ�б���û�иý�ʦ����Ϣ!" << endl;
			Set_TextColor(DEFAULT);
			Sleep(2000);
		}
		break;

	default:
		Set_TextColor(RED);
		cout << errormsg<<endl;
		Set_TextColor(DEFAULT);
		Sleep(1000);
		goto delete_Info;
	}
}

void UI::deleteAllInfo()
{
	system("cls");
	Set_TextColor(RED);
	cout << "�˲�����ɾ������ϵͳ�е�������Ϣ,ȷ�ϼ�����?(Y--�� ����--��)" << endl;
	Set_TextColor(DEFAULT);
	char _c;
	cin >> _c;
	switch (_c)
	{
	case 'Y':
	case 'y':
		affair.DeleteAllInfo();
		Set_TextColor(GREEN);
		cout << "ɾ��ȫ�����ݳɹ�!" << endl;
		Set_TextColor(DEFAULT);
		Sleep(2000);
		break;
	}

}


void UI::bindingName()
{
	if (pptr->getName() == "NaN")
	{
		string s;
		char flag;
	initname:
		system("cls");
		cout << "������������:" << endl;

		Set_TextColor(BLUE);
		cout << "ע:�ڼ�������ʱ������ֿո�,�Է�ֹ�ļ���д���ִ���;��ȷ������ո�,�����'_'�Դ���" << endl;
		Set_TextColor(DEFAULT);
		cin >> s;

		Set_TextColor(RED);
		cout << "�󶨺��޷��޸�,�Ƿ�ȷ��?(Y--�� ����--��)" << endl;
		Set_TextColor(DEFAULT);
		cin >> flag;

		if (flag != 'Y' && flag != 'y')
		{
			goto initname;
		}
		pptr->setName(s);

		Set_TextColor(GREEN);
		cout << "�󶨳ɹ�!" << endl;
		Set_TextColor(DEFAULT);
		Sleep(2000);
	}
	else
	{
		system("cls");
		Set_TextColor(GREEN);
		cout << "���Ѱ󶨸��˺�,�����ٰ�!" << endl;
		Set_TextColor(DEFAULT);
		Sleep(2000);
	}
}

void UI::logOff()
{
	Set_TextColor(GREEN);
	cout << "�˳���¼�ɹ�!������Ϣ�����Զ�����" << endl;
	Set_TextColor(DEFAULT);
	Sleep(2000);
	if (pptr != nullptr)
	{
		Teacher* _t = new Teacher;
		Student* _s = new Student;
		switch (pptr->getType())//�����ж������Ϣ���,����ֵ
		{

		case usertype::teacher:
			teacher = *(_t);
			break;

		case usertype::student:
			student = *(_s);
			break;

		}
		delete _t;
		delete _s;

		//��������Ϣд���ĵ�
		for (auto it = info.Wstudentinfo.begin(); it != info.Wstudentinfo.end(); it++)
		{
			it->WritetoFile();
		}
		for (auto it = info.Wteacherinfo.begin(); it != info.Wteacherinfo.end(); it++)
		{
			it->WritetoFile();
		}

		//��ȡ�ĵ�
		mapInit();

		//���������Ϣ
		info.Wstudentinfo.clear();
		info.Wteacherinfo.clear();
	}

	longjmp(StartMenu, 1);//��ת����ʼ����
}

void UI::Play()
{
	setjmp(StartMenu);//��ת�ı�־λ
	showStartMenu();
	if (pptr != nullptr)
	{
		showLoginMenu();
		switch (pptr->getType())
		{
		case usertype::student:
			Play_Student();
			break;
		case usertype::teacher:
			Play_Teacher();
			break;
		}
	}
	else
	{
		Play_Affairs();
	}

	Exit();
}

void UI::Play_Student()
{
Play_Student:
	char c_mode = showStudentMenu();
	switch (c_mode)
	{
	case 'A':
	case 'a':
		showBasicInfo_Student();
		break;

	case 'B':
	case 'b':
		inputBasicInfo_Student();
		break;

	case 'C':
	case 'c':
		changeBasicInfo_Student();
		break;

	case 'D':
	case 'd':
		getGPA();
		break;

	case 'E':
	case 'e':
		getLessons_Student();
		break;

	case 'F':
	case 'f':
		chooseLessons();
		break;

	case 'G':
	case 'g':
		deleteLessons();
		break;

	case 'X':
	case 'x':
		bindingName();
		break;

	case 'Y':
	case 'y':
		info.Wstudentinfo.push_back(student);
		logOff();
		break;

	case 'Z':
	case 'z':
		info.Wstudentinfo.push_back(student);
		Exit();
		break;

	default:
		Set_TextColor(RED);
		cout << errormsg << endl;
		Set_TextColor(DEFAULT);
		Sleep(1000);

	}
	goto Play_Student;

}

void UI::Play_Teacher()
{
Play_Teacher:
	char c_mode = showTeacherMenu();
	switch (c_mode)
	{
	case 'A':
	case 'a':
		showBasicInfo_Teacher();
		break;

	case 'B':
	case 'b':
		inputBasicInfo_Teacher();
		break;

	case 'C':
	case 'c':
		changeBasicInfo_Teacher();
		break;

	case 'D':
	case 'd':
		getLessons_Teacher();
		break;

	case 'E':
	case 'e':
		getLessons_Teacher_2();
		break;

	case 'F':
	case 'f':
		setLessons();
		break;

	case 'G':
	case 'g':
		getStudentList();
		break;

	case 'H':
	case 'h':
		inputGrade();
		break;

	case 'X':
	case 'x':
		bindingName();
		break;

	case 'Y':
	case 'y':
		info.Wteacherinfo.push_back(teacher);
		logOff();
		break;

	case 'Z':
	case 'z':
		info.Wteacherinfo.push_back(teacher);
		Exit();
		break;

	default:
		Set_TextColor(RED);
		cout << errormsg << endl;
		Set_TextColor(DEFAULT);
		Sleep(1000);

	}
	goto Play_Teacher;
}

void UI::Play_Affairs()
{
Play_Affairs:
	char c_mode = showAffairMenu();
	switch (c_mode)
	{
	case 'A':
	case 'a':
		getStudentAllInfo();
		break;

	case 'B':
	case 'b':
		getTeacherAllInfo();
		break;

	case 'C':
	case 'c':
		deleteInfo();
		break;

	case 'D':
	case 'd':
		deleteAllInfo();
		break;

	case 'Y':
	case 'y':
		logOff();
		break;

	case 'Z':
	case 'z':
		Exit();
		break;

	default:
		Set_TextColor(RED);
		cout << errormsg << endl;
		Set_TextColor(DEFAULT);
		Sleep(1000);
	}
	goto Play_Affairs;
}

void UI::Exit()
{
	showEndMenu();
	for (auto it = info.Wstudentinfo.begin(); it != info.Wstudentinfo.end(); it++)
	{
		it->WritetoFile();
	}
	for (auto it = info.Wteacherinfo.begin(); it != info.Wteacherinfo.end(); it++)
	{
		it->WritetoFile();
	}

	//���������Ϣ
	info.Wstudentinfo.clear();
	info.Wteacherinfo.clear();
	Sleep(3000);
	exit(0);
}

