#pragma once
#include <string>
using namespace std;

class follow
{
public:
	follow();
	follow(string n, int r);
	~follow();
	string name;
	int times_danced;
	bool dancing;
	bool just_danced;
	int skill_rating;
};

