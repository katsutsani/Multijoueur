#pragma once

#include "framework.h"


using json = nlohmann::json;


class JSON
{
public:

	int GetVictory(std::string player);
	json GetPlayer(std::string player);
	/*void UpdatePlayerJson();
	void UpdateGameJson();*/
	void InitPlayer(std::string player, int id);
	void UpdateGame(std::string posToken, std::string tokenPlayer);
	void RestartGame();
	void CheckPlayer(std::string player);
	void CreatePlayer(std::string player);

private:
	int nbPlayer = 0;

};

