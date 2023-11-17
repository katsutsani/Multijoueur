#include "JSON.h"

/*=========================*/

std::ifstream playerf("player.json");
json dataPlayer = json::parse(playerf);

std::ofstream playerj("player.json");

/*=========================*/

std::ifstream gamef("game.json");
json dataGame = json::parse(gamef);

std::ofstream gamej("game.json");

/*=========================*/

int JSON::GetVictory(std::string player)
{
    return GetPlayer(player)["victory"];
}

json JSON::GetPlayer(std::string player)
{
    return dataPlayer[player];
}

void JSON::UpdatePlayerJson()
{
    playerj << dataPlayer;
}

void JSON::UpdateGameJson()
{
    gamej << dataGame;
}

char JSON::GetPos()
{
    return mPos;
}
