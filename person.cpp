#include"person.h"

extern File f;

Person::Person()
{
	filemanager = &f;
	gender = gendertype::null;
}

Person::Person(string _ID)
{
	ID = _ID;
	gender = gendertype::null;
}

usertype Person::getType()
{
	return user;
}

Person::~Person(){}

void Person::setGender(char c_gender)
{
	switch (c_gender)
	{
	case '1':
		gender = gendertype::male;
		break;
	case '2':
		gender = gendertype::female;
		break;
	}

}

void Person::setName(string s)
{
	name = s;
}

const string Person::getName()
{
	return name;
}

const string Person::getID()
{
	return ID;
}