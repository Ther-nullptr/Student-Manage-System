#include<Windows.h>
#include<algorithm>
#include"UI.h"

//单次循环运行时所操纵的全局对象,通过基类指针进行管理
extern Student student;
extern Teacher teacher;

//管理员对象,不受控于基类指针
extern Affairs affair;

//全局文件管理对象
extern File f;

//用于匹配ID
std::regex allNumbers("\\d{5,12}"); 

//控制控制台字体颜色
//0 = 黑色，1 = 蓝色，2 = 绿色，3 = 湖蓝色，4 = 红色，5 = 紫色；6 = 黄色，7 = 白色，8 = 灰色，9 = 淡蓝色
void Set_TextColor(int color)
{
	if (color >= 0 && color <= 15)	//参数在0-15的范围颜色    	
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	else	//默认的颜色白色 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

//控制控制台背景颜色
//16:蓝 32:绿 64:红 128:亮色
void Set_BackgroundColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


UI::UI()
{
	pptr = nullptr;
	filemanager = &f;
	ifstream fi;
	//初始化学生和老师列表
	mapInit();
}


void UI::mapInit()
{
	f.findAllFiles(usertype::student);
	f.findAllFiles(usertype::teacher);
	for (auto it = filemanager->filelist.studentFiles.begin(); it != filemanager->filelist.studentFiles.end(); it++)
	{
		Student _student;//专门用于读取文件的学生对象
		_student.init(*it);//初始化对象,以便找到相应的文件进行读入
		_student.ReadfromFile();//读入信息
		info.Rstudentinfo.insert(make_pair(_student.getID(), _student));//以ID和名字为索引储存每一个学生的信息
	}
	for (auto it = filemanager->filelist.teacherFiles.begin(); it != filemanager->filelist.teacherFiles.end(); it++)
	{
		Teacher _teacher;//专门用于读取文件的教师对象
		_teacher.init(*it);//初始化对象,以便找到相应的文件进行读入
		_teacher.ReadfromFile();//读入信息
		info.Rteacherinfo.insert(make_pair(_teacher.getID(), _teacher));//以ID和名字为索引储存每一个老师的信息
	}
}


void UI::showStartMenu() //开始界面,只需登录,登录信息就会被自动录入文件
{
	system("cls");
	char num;
	statusflag = 1;
	cout << instructions << endl;
	cout << endl;
	pptr = nullptr;
	do
	{
		cout << "请键入你的身份:(1--学生 2--教师 3--教务处),按'Q'退出,按'H'获取帮助:";
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
	cout << "本系统拥有三种使用模式:学生模式、教师模式、教务处模式。" << endl;
	cout << "若使用学生模式或教师模式,需要键入ID。" << endl;
	cout << endl;

	Set_BackgroundColor(B_BLUE);
	cout << "学生模式" << endl;
	Set_BackgroundColor(DEFAULT);
	cout << "1.(A)查看个人信息：输出ID、姓名、性别、年级、班级、专业。" << endl;
	cout << "2.(B)录入个人信息：输入个人信息，包括年级、班级、系别、性别等（ID和姓名已经事先决定或绑定，不能在此选项中修改）。适用于初次登录。" << endl;
	cout << "3.(C)修改个人信息：输入相应字母，修改自身的对应选项。适用于登录后的调整。" << endl;
	cout << "4.(D)查看所修课程信息：查看目前所有所修课程的名称、绩点以及均绩。" << endl;
	cout << "5.(E)查看所有课程信息：查看目前所有开设课程的信息。" << endl;
	cout << "6.(F)选课：输入课程的ID，可以返回课程的开课信息（课程名、开课教师、评分标准等），学生可以根据课程信息选择所需要的课程。" << endl;
	cout << "7.(G)退课：输入课程的ID，可以退掉这门课程。" << endl;
	cout << "8.(X)实名认证：若此账号初次登录，则会被要求进行实名认证，绑定用户真实姓名。姓名一经绑定将无法修改。" << endl; 
	cout << "9.(Y)退出登录：退出当前账号，保存当前录入的信息，返回登录界面。" << endl;
	cout << "10.(Z)退出程序：退出当前程序。" << endl;
	cout << endl;

	Set_BackgroundColor(B_GREEN);
	cout << "教师模式" << endl;
	Set_BackgroundColor(DEFAULT);
	cout << "1.(A)查看个人信息：输出ID、姓名、性别、职称、专业。" << endl;
	cout << "2.(B)录入个人信息：同学生模式" << endl;
	cout << "3.(C)修改个人信息：同学生模式。" << endl;
	cout << "4.(D)查看所教课程信息：课程的ID、任课教师、名称、类型、时间、学分、评分规则。" << endl;
	cout << "5.(E)查看所有课程信息：同学生模式。" << endl;
	cout << "6.(F)录入所教课程信息：录入所教课程的名称、类型、时间、评分规则等。" << endl;
	cout << "7.(G)查看学生绩点信息：查看所有报课学生的绩点，可选择是否按照绩点高低排序。" << endl;
	cout << "8.(H)录入成绩：为所有未获得成绩的报课学生录入各项成绩。" << endl;
	cout << "9.(X)实名认证：同学生模式。" << endl;
	cout << "10.(Y)退出登录：同学生模式。" << endl;
	cout << "11.(Z)退出程序：同学生模式。" << endl;
	cout << endl;

	Set_BackgroundColor(B_RED);
	cout << "教务处模式" << endl;
	Set_BackgroundColor(DEFAULT);
	cout << "1.(A)查找学生信息：输入学生ID，返回这个学生的所有信息。" << endl;
	cout << "2.(B)查找教师信息：输入教师ID，返回这个教师的所有信息。" << endl;
	cout << "3.(C)删除选定信息：输入ID，删除某一学生或某一教师的全部信息。" << endl;
	cout << "4.(D)删除全部信息：清空数据库。" << endl;
	cout << "5.(Y)退出登录：同学生模式。" << endl;
	cout << "6.(Z)退出程序：同学生模式。" << endl;
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
	cout << "输入证件号码(5-12位,纯数字):";
	while(cin >> ID, !regex_match(ID, allNumbers)||cin.fail())
	{
		Set_TextColor(RED);
		cout << "不合法的ID!ID须为5-12位的纯数字字符串,请重新键入!"<<endl;
		Set_TextColor(DEFAULT);
		cin.clear();
		cin.ignore();
	}
	pptr->init(ID);
	Set_TextColor(GREEN);
	cout << "登录成功" << endl;
	Set_TextColor(DEFAULT);
	pptr->ReadfromFile();
	Sleep(2000);
}

char UI::showStudentMenu()
{
	system("cls");
	cout << choosemode << endl;
	cout << "A.查看个人信息" << endl;
	cout << "B.录入个人信息" << endl;
	cout << "C.修改个人信息" << endl;
	cout << "D.查看所修课程信息" << endl;
	cout << "E.查看所有课程信息" << endl;
	cout << "F.选课" << endl;
	cout << "G.退课" << endl;
	Set_TextColor(YELLOW);
	cout << "X.实名认证" << endl;
	Set_TextColor(DEFAULT);
	Set_TextColor(PURPLE);
	cout << "Y.退出登录" << endl;
	Set_TextColor(DEFAULT);
	Set_TextColor(RED);
	cout << "Z.退出程序" << endl;
	Set_TextColor(DEFAULT);
	if (pptr->getName() == "NaN")
	{
		Set_TextColor(RED);
		cout << "您还未绑定身份,请按X,及时绑定实名身份!" << endl;
		Set_TextColor(DEFAULT);
	}
	else
	{
		Set_TextColor(GREEN);
		cout << "欢迎使用," << pptr->getName() << endl;
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
	cout << "A.查看个人信息" << endl;
	cout << "B.录入个人信息" << endl;
	cout << "C.修改个人信息" << endl;
	cout << "D.查看所教课程信息" << endl;
	cout << "E.查看所有课程信息" << endl;
	cout << "F.录入所教课程信息" << endl;
	cout << "G.查看学生绩点信息" << endl;
	cout << "H.录入成绩" << endl;
	Set_TextColor(YELLOW);
	cout << "X.实名认证" << endl;
	Set_TextColor(DEFAULT);
	Set_TextColor(PURPLE);
	cout << "Y.退出登录" << endl;
	Set_TextColor(DEFAULT);
	Set_TextColor(RED);
	cout << "Z.退出程序" << endl;
	Set_TextColor(DEFAULT);

	if (pptr->getName() == "NaN")
	{
		Set_TextColor(RED);
		cout << "您还未绑定身份,请按X,及时绑定实名身份!" << endl;
		Set_TextColor(DEFAULT);
	}
	else
	{
		Set_TextColor(GREEN);
		cout << "欢迎使用," << pptr->getName() << endl;
		Set_TextColor(DEFAULT);
	}

	if (teacher.getLessonName() == "NaN")
	{
		Set_TextColor(RED);
		cout << "您还未录入您的课程信息,请按E,及时录入课程信息!" << endl;
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
	cout << "A.查找学生信息" << endl;
	cout << "B.查找教师信息" << endl;
	cout << "C.删除选定信息" << endl;
	cout << "D.删除全部信息" << endl;
	Set_TextColor(PURPLE);
	cout << "Y.退出登录" << endl;
	Set_TextColor(DEFAULT);
	Set_TextColor(RED);
	cout << "Z.退出程序" << endl;
	Set_TextColor(DEFAULT);
	char c_mode;
	cin >> c_mode;
	return c_mode;
}

void UI::showEndMenu()
{
	system("cls");
	//每一轮使用完毕后，都将对象的信息写入文件中
	cout << "感谢您的使用!" << endl;
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
	cout << "请依次键入:1.性别(1--男 2--女) 2.年级(数字编号(1-4)) 3.行政班级(数字编号(1-10)) 4.专业名称" << endl;
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
	cout << "修改您的信息(请键入A,B,C,D)" << endl;
	Set_TextColor(BLUE);
	cout << "A.性别 B.年级 C.行政班级 D.专业" << endl;
	Set_TextColor(DEFAULT);
	cin >> c_put;
	switch (c_put)
	{
	case 'A':
	case 'a':
		cout << "请键入性别(1--男 2--女):";
		pptr->changeBasicInfo('a');
		break;

	case 'B':
	case 'b':
		cout << "请键入年级(数字编号):";
		pptr->changeBasicInfo('b');
		break;

	case 'C':
	case 'c':
		cout << "请键入行政班级(数字编号):";
		pptr->changeBasicInfo('c');
		break;

	case 'D':
	case 'd':
		cout << "请键入专业:";
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
	cout << "课程列表如下:" << endl;
	auto _list = student.getGPAlist();
	
	for (auto it = info.Rteacherinfo.begin(); it != info.Rteacherinfo.end(); it++)
	{
		cout << crossline1 << endl;
		it->second.getLessonInfo();

		if (_list.find(it->second.getLessonName()) == _list.end())//未报名该课程
		{
			Set_TextColor(RED);
			cout << "(未选)" << endl;
			Set_TextColor(DEFAULT);
		}
		else
		{
			Set_TextColor(GREEN);
			cout << "(已选)" << endl;
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

	cout << "您所修课程的GPA如下:" << endl;//TODO
	cout << crossline1 << endl;
	cout << "课程名称" << setw(35) << "绩点" << setw(6) << "等级" << endl;

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

	cout << "键入课程ID,以实现选课操作:" << endl;
	string _index;
	while (cin >> _index, !regex_match(_index, allNumbers) || cin.fail())
	{
		Set_TextColor(RED);
		cout << "不合法的ID!ID须为5-12位的纯数字字符串,请重新键入!"<<endl;
		Set_TextColor(DEFAULT);
		cin.clear();
		cin.ignore();
	}

	auto it = info.Rteacherinfo.find(_index);
	
	if (it == info.Rteacherinfo.end())
	{
		Set_TextColor(RED);
		cout << "未能查找到课程ID,请重新键入!" << endl;
		Set_TextColor(DEFAULT);
		Sleep(2000);
	}
	else if (_list.find(it->second.getLessonName()) != _list.end())
	{
		Set_TextColor(RED);
		cout << "您已选择该课程!" << endl;
		Set_TextColor(DEFAULT);
		Sleep(2000);
	}
	else
	{
		cout << crossline1 << endl;
		it->second.getLessonInfo();
		cout << crossline1 << endl;
		cout << "确认选择此课程(Y--是 其他--否)?" << endl;
		char c1;
		cin >> c1;
		if (c1 == 'Y' || c1 == 'y')
		{
			student.setLesson(it->second.getLessonName());
			Set_TextColor(GREEN);
			cout << "选课成功!" << endl;
			Set_TextColor(DEFAULT);
			Sleep(2000);
		}
	}
	char c2;
	cout << "是否继续选课(Y--是 其他--否)" << endl;
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

	cout << "输入您想要退掉的课程的ID:" << endl;
	string _ID;
	while (cin >> _ID, !regex_match(_ID, allNumbers) || cin.fail())
	{
		Set_TextColor(RED);
		cout << "不合法的ID!ID须为5-12位的纯数字字符串,请重新键入!" << endl;
		Set_TextColor(DEFAULT);
		cin.clear();
		cin.ignore();
	}

	auto it = info.Rteacherinfo.find(_ID);
	if (it == info.Rteacherinfo.end())
	{
		Set_TextColor(RED);
		cout << "未能查找到课程ID,请重新键入!" << endl;
		Set_TextColor(DEFAULT);
		Sleep(2000);
	}
	else if (_list.find(it->second.getLessonName()) == _list.end())
	{
		Set_TextColor(RED);
		cout << "您未选择该课程!" << endl;
		Set_TextColor(DEFAULT);
		Sleep(2000);
	}
	else 
	{
		cout << "退课后,您将无法获得该课程的学分,确认继续吗(Y--是 其他--否):" << endl;
		char c1;
		cin >> c1;
		if (c1 == 'Y' || c1 == 'y')
		{
			student.deleteLesson(it->second.getLessonName());
			Set_TextColor(GREEN);
			cout << "退课成功!" << endl;
			Set_TextColor(DEFAULT);
			Sleep(2000);
		}
	}

	cout << "是否继续退课(Y--是 其他--否):"<<endl;
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
	cout << "请依次键入:1.性别(1--男 2--女) 2.职称(1--教授 2--副教授 3--讲师) 3.专业名称" << endl;
	Set_TextColor(BLUE);
	cout << "若需调整所教课程的信息,请选择'录入所教课程信息'选项" << endl;
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
	cout << "修改您的信息(请键入A,B,C)" << endl;
	Set_TextColor(BLUE);
	cout << "A.性别 B.职称 C.专业" << endl;
	Set_TextColor(DEFAULT);
	cin >> c_put;
	switch (c_put)
	{
	case 'A':
	case 'a':
		cout << "请键入性别(1--男 2--女):";
		pptr->changeBasicInfo('a');
		break;

	case 'B':
	case 'b':
		cout << "请键入职称(1--教授 2--副教授 3--讲师):";
		pptr->changeBasicInfo('b');
		break;

	case 'C':
	case 'c':
		cout << "请键入专业:";
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
	cout << "输入您的课程名称:" << endl;
	pptr->changeBasicInfo('e');
	cout << "输入课程类型(1--必修 2--限选 3--任选):" << endl;
	pptr->changeBasicInfo('f');
	cout << "输入课程学分:" << endl;
	pptr->changeBasicInfo('i');
	cout << "输入课程时间:" << endl;
	setLessonTime();
	cout << "输入您的课程评分权重(依次为签到、平时作业、大作业、期中考试、期末考试,权重之和必须为1):" << endl;
	pptr->changeBasicInfo('g');
	cout << "输入您的调分政策(两个数字a(a>=1)和b(b>=0)):" << endl;
	Set_TextColor(BLUE);
	cout << "初评成绩x和最终成绩y有如下关系:y=ax+b,y最大为100.此条目学生不可见." << endl;
	Set_TextColor(DEFAULT);
	pptr->changeBasicInfo('h');

	Set_TextColor(RED);
	cout << "课程信息一经录入将无法修改,是否确认(Y--是 其他--否)?" << endl;
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
	cout << "课程周数(1--全周 2--前八周 3--后八周):"<<endl;
	teacher.SetTime('5');
	cout << "课时一(依次输入星期和节次):"<<endl;
	teacher.SetTime('1');
	teacher.SetTime('3');
	char _c;
	cout << "是否添加课时2(Y--是 其他--否)?:"<<endl;
	cin >> _c;
	if (_c == 'Y' || _c == 'y')
	{
		cout << "课时二(依次输入星期和节次):"<<endl;
		teacher.SetTime('2');
		teacher.SetTime('4');
	}
}

void UI::getStudentList()//这应该完全是一个文件的操作
{
	std::map<index, Student>::iterator it;
	system("cls");

	char mode;
	cout << "是否开启按GPA高低排序(Y--是 其他--否)?" << endl;
	cin >> mode;

	cout << "所有选课学生的GPA如下:" << endl;
	cout << crossline1 << endl;
	cout << "学生" << setw(16) << "绩点" << setw(14) << "等级" << endl;
	cout << crossline1 << endl;

	if (mode == 'Y' || mode == 'y')
	{
		std::vector<Ordered_stu_info> ordered_stu_vector;
		for (it = info.Rstudentinfo.begin(); it != info.Rstudentinfo.end(); it++)
		{
			Student _s = it->second;
			GPAlist _GPAlist = _s.getGPAlist();
			string _lessonname = teacher.getLessonName();
			auto GPAit = _GPAlist.find(_lessonname);//寻找学生是否报了自己课
			if (GPAit != _GPAlist.end())//学生报课
			{
				ordered_stu_vector.push_back(std::make_pair(_s.getName(),GPAit->second));//存入学生的姓名以及成绩
			}
		}

		std::sort(ordered_stu_vector.begin(), ordered_stu_vector.end(), SortRule());//排序

		
		for (auto it2 = ordered_stu_vector.begin(); it2 != ordered_stu_vector.end(); it2++)//输出信息
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
			auto GPAit = _GPAlist.find(_lessonname);//寻找学生是否报了自己课
			if (GPAit != _GPAlist.end())//学生报课
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
	const string _string[5] = { "签到:","平时作业:","大作业:","期中考试:","期末考试:" };
	bool emptyclass = 1;
	double gradelist[5];
	int totalgrade = 0;
	gradeWeight weight;
	adjustPolicy policy;

	Set_TextColor(BLUE);
	cout << "注:每一项的满分均为100分" << endl;
	Set_TextColor(DEFAULT);

	std::map<index, Student>::iterator it;
	for (it = info.Rstudentinfo.begin(); it != info.Rstudentinfo.end(); it++)
	{
		Student _s = it->second;
		GPAlist _GPAlist = _s.getGPAlist();
		string _lessonname = teacher.getLessonName();
		auto GPAit = _GPAlist.find(_lessonname);//寻找学生是否报了自己课
		if (GPAit != _GPAlist.end() && GPAit->second.first == NaN)//学生报课,且成绩已经被录入
		{
			//录入成绩
			emptyclass = 0;
			totalgrade = 0;
			cout << "请为" << _s.getName() << "录入成绩:" << endl;
			for (int i = 0; i < 5; i++)
			{
				cout << _string[i];
				while (cin >> gradelist[i], !(gradelist[i] >= 0 && gradelist[i] <= 100) || cin.fail())
				{
					Set_TextColor(RED);
					cout << "请重新输入分数(0-100)!" << endl;
					Set_TextColor(DEFAULT);
					cin.clear();
					cin.ignore();
				}
			}

			//计算总评
			weight = teacher.getweight();
			for (int i = 0; i < 5; i++)
			{
				totalgrade += weight[i].second * gradelist[i];
			}

			//调分
			policy = teacher.getpolicy();
			totalgrade *= policy.first;
			totalgrade += policy.second;
			if (totalgrade > 100)
			{
				totalgrade = 100;
			}

			//为学生录入成绩
			_s.GPAinit(teacher.getLessonName(), totalgrade);

			//将更改后的学生信息加入到将要录入文件的list里
			info.Wstudentinfo.push_back(_s);
			cout << endl;
		}
	}
	if (emptyclass)
	{
		Set_TextColor(RED);
		cout << "当前没有任何学生选择您的课或所有学生的成绩均已经被录入!" << endl;
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
	cout << "目前管理系统中的学生ID列表如下:" << endl;
	affair.getStudentID();
	cout << crossline1 << endl;
	cout << "键入学生ID,以实现查询功能:" << endl;
	string _ID;
	cin >> _ID;

	if (std::find(f.filelist.studentFiles.cbegin(), f.filelist.studentFiles.cend(), _ID) != f.filelist.studentFiles.cend())//找到文件
	{
		Student _s;
		_s.init(_ID);
		affair.GetStudentInfo(_s);
		cout << endl;
	}
	else
	{
		Set_TextColor(RED);
		cout << "当前列表中没有该学生的信息!" << endl;
		Set_TextColor(DEFAULT);
		Sleep(2000);
	}

	cout << "是否继续查找(Y--是 其他--否)?" << endl;
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
	cout << "目前管理系统中的教师ID列表如下:" << endl;
	affair.getTeacherID();
	cout << crossline1 << endl;
	cout << "键入教师ID,以实现查询功能:" << endl;
	string _ID;
	cin >> _ID;
	if (std::find(f.filelist.teacherFiles.cbegin(), f.filelist.teacherFiles.cend(), _ID) != f.filelist.teacherFiles.cend())//找到文件
	{
		Teacher _t;
		_t.init(_ID);
		affair.GetTeacherInfo(_t);
		cout << endl;
	}
	else
	{
		Set_TextColor(RED);
		cout << "当前列表中没有该教师的信息!" << endl;
		Set_TextColor(DEFAULT);
		Sleep(2000);
	}

	cout << "是否继续查找(Y--是 其他--否)?" << endl;
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
	cout << "键入您需要删除的信息类型(S--学生 T--教师):" << endl;
	char _c;
	string _ID;
	cin >> _c;
	switch (_c)
	{

	case 'S':
	case 's':
		cout << "目前管理系统中的学生ID列表如下:" << endl;
		affair.getStudentID();
		cout << crossline1 << endl;
		cout << "键入您想要删除的ID:" << endl;
		cin >> _ID;
		if (f.filelist.studentFiles.count(_ID)==1)//找到文件
		{
			bool _status = affair.DeleteInfo(usertype::student, _ID);
			if (!_status)
			{
				Set_TextColor(GREEN);
				cout << "删除成功!" << endl;
				Set_TextColor(DEFAULT);
				Sleep(2000);
			}
		}
		else
		{
			Set_TextColor(RED);
			cout << "当前列表中没有该学生的信息!" << endl;
			Set_TextColor(DEFAULT);
			Sleep(2000);
		}
		break;

	case 'T':
	case 't':
		cout << "目前管理系统中的教师ID列表如下:" << endl;
		affair.getTeacherID();
		cout << crossline1 << endl;
		cout << "键入您想要删除的ID:" << endl;
		cin >> _ID;		
		if (f.filelist.teacherFiles.count(_ID) == 1)//找到文件
		{
			bool _status = affair.DeleteInfo(usertype::teacher, _ID);
			if (!_status)
			{
				Set_TextColor(GREEN);
				cout << "删除成功!" << endl;
				Set_TextColor(DEFAULT);
				Sleep(2000);
			}
		}
		else
		{
			Set_TextColor(RED);
			cout << "当前列表中没有该教师的信息!" << endl;
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
	cout << "此操作将删除管理系统中的所有信息,确认继续吗?(Y--是 其他--否)" << endl;
	Set_TextColor(DEFAULT);
	char _c;
	cin >> _c;
	switch (_c)
	{
	case 'Y':
	case 'y':
		affair.DeleteAllInfo();
		Set_TextColor(GREEN);
		cout << "删除全部数据成功!" << endl;
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
		cout << "输入您的名字:" << endl;

		Set_TextColor(BLUE);
		cout << "注:在键入名字时避免出现空格,以防止文件读写出现错误;若确需输入空格,请键入'_'以代替" << endl;
		Set_TextColor(DEFAULT);
		cin >> s;

		Set_TextColor(RED);
		cout << "绑定后无法修改,是否确认?(Y--是 其他--否)" << endl;
		Set_TextColor(DEFAULT);
		cin >> flag;

		if (flag != 'Y' && flag != 'y')
		{
			goto initname;
		}
		pptr->setName(s);

		Set_TextColor(GREEN);
		cout << "绑定成功!" << endl;
		Set_TextColor(DEFAULT);
		Sleep(2000);
	}
	else
	{
		system("cls");
		Set_TextColor(GREEN);
		cout << "您已绑定该账号,无需再绑定!" << endl;
		Set_TextColor(DEFAULT);
		Sleep(2000);
	}
}

void UI::logOff()
{
	Set_TextColor(GREEN);
	cout << "退出登录成功!您的信息将会自动保存" << endl;
	Set_TextColor(DEFAULT);
	Sleep(2000);
	if (pptr != nullptr)
	{
		Teacher* _t = new Teacher;
		Student* _s = new Student;
		switch (pptr->getType())//将现有对象的信息清空,赋新值
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

		//将现有信息写入文档
		for (auto it = info.Wstudentinfo.begin(); it != info.Wstudentinfo.end(); it++)
		{
			it->WritetoFile();
		}
		for (auto it = info.Wteacherinfo.begin(); it != info.Wteacherinfo.end(); it++)
		{
			it->WritetoFile();
		}

		//读取文档
		mapInit();

		//清空数组信息
		info.Wstudentinfo.clear();
		info.Wteacherinfo.clear();
	}

	longjmp(StartMenu, 1);//跳转至开始界面
}

void UI::Play()
{
	setjmp(StartMenu);//跳转的标志位
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

	//清空数组信息
	info.Wstudentinfo.clear();
	info.Wteacherinfo.clear();
	Sleep(3000);
	exit(0);
}

