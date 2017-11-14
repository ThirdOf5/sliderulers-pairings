#pragma once
#include <string>
#include "lead.h"
#include "follow.h"

class couple
{
public:
	couple();
	~couple();
	couple(lead* l, follow* f);

	void print();

	lead* leader;
	follow* follower;

	bool inFront;
};

