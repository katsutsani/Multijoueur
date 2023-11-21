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

//void JSON::UpdatePlayerJson()
//{
//    playerj << dataPlayer;
//}
//
//void JSON::UpdateGameJson()
//{
//    gamej << dataGame;
//}

void JSON::InitPlayer(std::string player, int idGame)
{
    std::string name;
    int victory;

    name = dataPlayer[player]["name"];
    victory = dataPlayer[player]["victory"];

    json jsonFile;

    jsonFile["player" + std::to_string(idGame)]["name"] = name;
    jsonFile["player" + std::to_string(idGame)]["victory"] = victory;

    gamej << jsonFile;
}

void JSON::UpdateGame(std::string posToken, std::string tokenPlayer)
{
    std::string tab[9] = { dataGame["posToken"] };

    for (int i = 0; i < 9; i++)
    {
        if (tab[i] == posToken)
        {
            tab[i] = tokenPlayer;
        }
    }

    json jsonFile;

    jsonFile["posToken"] = tab;

    gamej << jsonFile;
}


void JSON::RestartGame()
{
    std::string tab[9] = { "A1", "A2", "A3", "B1", "B2", "B3", "C1", "C2", "C3" };
    std::string name1 = "joueurX";
    std::string name2 = "joueurO";
    int victory = 0;

    json jsonFile;

    jsonFile["posToken"] = tab;
    jsonFile["player1"]["name"] = name1;
    jsonFile["player2"]["name"] = name2;
    jsonFile["player1"]["victory"] = victory;
    jsonFile["player2"]["victory"] = victory;

    gamej << jsonFile;
}

void JSON::CheckPlayer(std::string player)
{
    nbPlayer++;

    if (dataPlayer[player]["name"] == player)
    {
        InitPlayer(player, nbPlayer);
    }
    else
    {
        CreatePlayer(player);
    }
}

void JSON::CreatePlayer(std::string player)
{
    std::string name;
    int victory = 0;

    json jsonFile;
    
    jsonFile[player]["name"] = name;
    jsonFile[player]["victory"] = victory;

    playerj << jsonFile;

    InitPlayer(player, nbPlayer);
}
