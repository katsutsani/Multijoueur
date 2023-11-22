#include "JSON.h"

void JSON::function()
{
    std::ifstream playerf("player.json", std::ios::app);
    playerf >> dataPlayer;
    /*dataPlayer = json::parse(playerf);*/

    std::ifstream gamef("game.json", std::ios::app);
    gamef >> dataGame;
    /*dataGame = json::parse(gamef);*/
}

int JSON::GetVictory(std::string player)
{
    return GetPlayer(player)["victory"];
}

json JSON::GetPlayer(std::string player)
{
    return dataPlayer[player];
}

void JSON::InitPlayer(std::string player, int idGame)
{
    function();

    std::string name;
    int victory;

    name = dataPlayer[player]["name"];
    victory = dataPlayer[player]["victory"];

    dataGame["player" + std::to_string(idGame)]["name"] = name;
    dataGame["player" + std::to_string(idGame)]["victory"] = victory;

    std::ofstream gamej("game.json", std::ios::trunc);

    gamej << dataGame;
}

void JSON::UpdateGame(std::string posToken, std::string tokenPlayer)
{
    function();
    std::string tab[9] = { dataGame["posToken"] };

    for (int i = 0; i < 9; i++)
    {
        if (tab[i] == posToken)
        {
            tab[i] = tokenPlayer;
        }
    }

    dataGame["posToken"] = tab;

    std::ofstream gamej("game.json", std::ios::trunc);

    gamej << dataGame;
}


void JSON::RestartGame()
{

    function();
    std::string tab[9] = { "A1", "A2", "A3", "B1", "B2", "B3", "C1", "C2", "C3" };
    std::string name1 = "joueurX";
    std::string name2 = "joueurO";
    int victory = 0;

    dataGame["posToken"] = tab;
    dataGame["player1"]["name"] = name1;
    dataGame["player2"]["name"] = name2;
    dataGame["player1"]["victory"] = victory;
    dataGame["player2"]["victory"] = victory;

    std::ofstream gamej("game.json", std::ios::trunc);

    gamej << dataGame;
}

void JSON::CheckPlayer(std::string player)
{
    function();
    nbPlayer++;

    if (dataPlayer[player]["name"] == player)
    {
        InitPlayer(player, nbPlayer);
    }
    else
    {
        if (CreatePlayer(player))
        {
            InitPlayer(player, nbPlayer);
        }
    }
}

bool JSON::CreatePlayer(std::string player)
{

    function();
    std::string name = player;
    int victory = 0;
    
    dataPlayer[player]["name"] = name;
    dataPlayer[player]["victory"] = victory;

    std::ofstream playerj("player.json", std::ios::trunc);

    playerj << dataPlayer;

    return true;
}
