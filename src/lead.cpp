#include "lead.h"


lead::lead()
{
}

lead::lead(string n, int r)
{
	name = n;
	skill_rating = r;
	times_danced = 0;
	beenFront = false;
	dancing = false;
	just_danced = false;
	inFront = false;
}


lead::~lead()
{
}
