#pragma once

#include "framework.h"


using json = nlohmann::json;


class JSON
{
public:

	int GetVictory();
	json GetPlayer();
	json UpdateJson();
	char GetPos();


private:

	char mPos;
	

};

