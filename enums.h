//定义程序中的枚举值变量
#pragma once

enum class gendertype
{
	null,
	male,
	female,
	
};

enum class usertype
{
	student,
	teacher,
	academic_affairs
};

enum class Lessontype
{
	null,
	Compulsory,
	Limited,
	Optional
};

enum class jobtype
{
	null,
	professor,
	associate_professor,
	lecturer
};

enum class RWmode //文件的读写方式
{
	read, 
	write
};

enum class WeekType
{
	null,
	F_half,//前8周
	S_half,//后8周
	All//全周
};