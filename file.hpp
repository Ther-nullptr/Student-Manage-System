#pragma once
// �ļ�����ϵͳ
#include<string>
#include<cstring>
#include<fstream>
#include<iostream>
#include<set>
#include<direct.h>
#include<io.h>
#include"enums.h"


using std::string;
using std::set;
using std::ifstream;
using std::ofstream;
using std::ios;


struct Filelist
{
	set<string> studentFiles;
	set<string> teacherFiles;
};

class File
{
public:

	File()
	{
		char buf[100];
		_getcwd(buf, sizeof(buf));
		cwd = buf;
		setFolder();
		findAllFiles(usertype::student);
		findAllFiles(usertype::teacher);
	}

	const string getcwdName()
	{
		return cwd;
	}

	void setFolder1()
	{
		string dirName = cwd+"\\STUDENT";
		_mkdir(dirName.c_str());
	}

	void setFolder2()
	{
		string dirName = cwd + "\\TEACHER";
		_mkdir(dirName.c_str());
	}

	void setFolder()//�����ļ���
	{
		setFolder1();
		setFolder2();
	}

	ofstream openFile_W(string s,usertype type)//�����ļ� //�ļ�ָ��??
	{
		string filename;
		ofstream fo;
		switch (type)
		{	
		case usertype::student:
			filename = cwd + "\\STUDENT\\" + s + ".txt";
			fo.open(filename,ios::out);
			break;
		case usertype::teacher:
			filename = cwd + "\\TEACHER\\" + s + ".txt";
			fo.open(filename,ios::out);
			break;
		}
		return fo;
	}

	ifstream openFile_R(string s, usertype type)//��һ����Ҫ�����ļ�
	{
		string filename;
		ifstream fi;
		switch (type)
		{
		case usertype::student:
			filename = cwd + "\\STUDENT\\" + s + ".txt";
			fi.open(filename, ios::in);
			break;
		case usertype::teacher:
			filename = cwd + "\\TEACHER\\" + s + ".txt";
			fi.open(filename, ios::in);
			break;
		}
		return fi;
	}


	void findAllFiles(usertype type)
	{
		string newpath(cwd);
		switch (type)
		{
		case usertype::student:
			newpath += "\\STUDENT";
			break;
		case usertype::teacher:
			newpath += "\\TEACHER";
			break;
		}
		newpath += "\\*.*";
		int handle;
		_finddata_t findData;
		handle = _findfirst(newpath.c_str(), &findData);
		if (handle == -1) // ����Ƿ�ɹ�
			return;
		while (_findnext(handle, &findData) == 0)
		{
			if (strstr(findData.name, ".txt"))//�ж��ǲ���txt�ļ�
			{ 
				string txtname = string(findData.name);
				switch (type)
				{
				case usertype::student:
					deleteString(txtname);
					filelist.studentFiles.insert(txtname);
					break;
				case usertype::teacher:
					deleteString(txtname);
					filelist.teacherFiles.insert(txtname);
					break;
				}
			}
		}
		_findclose(handle); // �ر��������
	}
	
	Filelist filelist;//�ļ��б�(������׺)

private:

	string cwd;//��ǰ����.cpp�ļ�����Ŀ¼
	void deleteString(string& s)//ɾ���ַ�ĩβ��4���ַ�
	{
		int size = s.size();
		for (int i = size; i >= size - 4; i--)
		{
			s.erase(i);
		}
	}
};
