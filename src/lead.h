#pragma once
#include <string>
#include <vector>
#include "follow.h"

using namespace std;

class lead
{
public:
	lead();
	lead(string n, int r);
	~lead();
	string name;
	int times_danced;
	bool beenFront;
	bool inFront;
	bool dancing;
	bool just_danced;
	int skill_rating;
	vector<string> follows_danced_with;
};

