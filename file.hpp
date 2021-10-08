#pragma once
// 文件管理系统
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

	void setFolder()//创建文件夹
	{
		setFolder1();
		setFolder2();
	}

	ofstream openFile_W(string s,usertype type)//创建文件 //文件指针??
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

	ifstream openFile_R(string s, usertype type)//打开一个需要读的文件
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
		if (handle == -1) // 检查是否成功
			return;
		while (_findnext(handle, &findData) == 0)
		{
			if (strstr(findData.name, ".txt"))//判断是不是txt文件
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
		_findclose(handle); // 关闭搜索句柄
	}
	
	Filelist filelist;//文件列表(不带后缀)

private:

	string cwd;//当前工程.cpp文件所在目录
	void deleteString(string& s)//删除字符末尾的4个字符
	{
		int size = s.size();
		for (int i = size; i >= size - 4; i--)
		{
			s.erase(i);
		}
	}
};
