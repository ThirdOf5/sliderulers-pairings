#include "follow.h"


follow::follow()
{
	name = "Jane";
	times_danced = 0;
	dancing = false;
	just_danced = false;
	skill_rating = 2;
}

follow::follow(string n, int r)
{
	name = n;
	skill_rating = r;
	times_danced = 0;
	dancing = false;
	just_danced = false;
}


follow::~follow()
{
}
