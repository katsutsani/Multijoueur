#pragma once

#include "framework.h"


using json = nlohmann::json;


class JSON
{
public:

	int GetVictory(std::string player);
	json GetPlayer(std::string player);
	void UpdatePlayerJson();
	void UpdateGameJson();
	char GetPos();


private:

	char mPos;
	

};

