#include "couple.h"
#include "lead.h"
#include "follow.h"
#include <iostream>

couple::couple()
{
	inFront = false;
}

couple::couple(lead* l, follow* f)
{
	inFront = false;
	leader = l;
	follower = f;
}


couple::~couple()
{
}

void couple::print(){
	cout << leader->name << " with " << follower->name;
	if (leader->inFront == true){
		cout << " <- FRONT ";
	}
	cout << endl;
}
