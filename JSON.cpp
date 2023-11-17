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

int JSON::GetVictory()
{
    return 0;
}

json JSON::GetPlayer()
{
    return json();
}

json JSON::UpdateJson()
{
    return json();
}

char JSON::GetPos()
{
    return mPos;
}
