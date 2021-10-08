#include"grade.h"


GPAtype Grade::score_to_GPA(int score)
{
	switch (score/5)
	{
	case 20:
		return GPAtype(4.0, "A+");
		break;
	case 19:
		return GPAtype(4.0, "A");
		break;
	case 18:
		return GPAtype(4.0, "A-");
		break;
	case 17:
		return GPAtype(3.6, "B+");
		break;
	default:
		return GPAtype(3.3, "B");
		break;
	}
}


const GPAlist Grade::getGPAlist()
{
	return GPA;
}