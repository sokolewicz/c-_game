#include <model/RandomInteraction.h>
#include <iostream>
#include "model/PlayerRepository.h"
#include "model/WorldRepository.h"
PlayerRepository::PlayerRepository(void (GameManager::*call_back_function)(bool moved), GameManager* game_manager, WorldRepository* world_repository)
: call_back_function(call_back_function), game_manager(game_manager), worldRepository(world_repository) {

}
PlayerRepository::PlayerRepository(unsigned int number_of_players,  const std::vector<std::string> &players_names, WorldRepository *worldRepository, void (GameManager::*call_back_function)(bool moved), GameManager* game_manager) :
worldRepository(worldRepository), call_back_function(call_back_function), game_manager(game_manager){
    if (worldRepository== nullptr) throw PlayerRepositoryException("Canot create PlayerRepository without WorldRepository");

    for(int i=0;i<number_of_players;i++)
    {
        {
            PlayerPtr player(new Player(worldRepository->get_world_size_x()-2, 1+2*(i+1), this->rand_representation(i), true, players_names[i], 100, 0, i, (i==0)));

            players.push_back(player);
        }
    }
}
PlayerRepository::~PlayerRepository() {
}

bool PlayerRepository::create_player(int x, int y, char representation, const std::string &name, bool current_player, int health, int stars, int id) {

    bool enable_movement;
    int current_size=players.size();

    auto p = worldRepository->find_field_<PlayerPtr>(x,y,players);

    if (p != players.end())
        return false;

    PlayerPtr player (new Player(x,y,representation,enable_movement,name,health,stars,this->get_players_number(), current_player));
    players.push_back(player);
    return current_size != players.size(); //sprawdzamy, czy zwiększyła się liczba elementów wektora players
}

unsigned int PlayerRepository::get_players_number() {

    return players.size();
}

PlayerPtr PlayerRepository::get_current_player() {
    PlayerPtr current_player= nullptr;

    for (auto & player : players)
    {
        if(player->is_turn())
            current_player=player;
    }
    if(current_player== nullptr) throw PlayerRepositoryException{"Player not found"};
    return current_player;
}


void PlayerRepository::change_to_next_player() {
    PlayerPtr current_player=get_current_player();
    unsigned int current_player_id=current_player->get_id();
    current_player->set_turn(false);
    PlayerPtr next_player=players[(current_player_id+1 >players.size() - 1) ? 0 : current_player_id + 1 ];
    next_player->set_turn(true);
}

void PlayerRepository::remove_current_player() {
    PlayerPtr current_player=get_current_player();
    unsigned int current_player_id=current_player->get_id();
    this->change_to_next_player();
    players.erase(players.begin()+(current_player_id));
}

bool PlayerRepository::move_current_player(int offsetX, int offsetY) {
    PlayerPtr current_player=get_current_player();
    int d_x = current_player->get_x();
    int d_y = current_player->get_y();
    d_x += offsetX;
    d_y += offsetY;
if (worldRepository->is_field_empty(d_x, d_y))
{
   std:: vector<PlayerPtr>::const_iterator p = worldRepository->find_field_<PlayerPtr>(d_x, d_y, get_players());

    if (p == get_players().end())
    {
        current_player->set_x(d_x);
        current_player->set_y(d_y);
        ((*game_manager).*call_back_function)(true);
        return true;
    }
}
return false;
}

const std::vector<PlayerPtr> &PlayerRepository::get_players() const {
    return players;
}

PlayerPtr PlayerRepository::get_player(unsigned int id) const {
    PlayerPtr player = nullptr;
    for (const auto & i : players) {
        if (i->get_id()==id)
            player = i;

    }
    if (player== nullptr) throw PlayerRepositoryException {"Player not found"};
    return player;
}

bool PlayerRepository::current_player_is_dead() {

    PlayerPtr player = get_current_player();

    return player->get_health() <= 0;

}

const char PlayerRepository::rand_representation(unsigned int i) {
    char sign=' ';

        if(i>3)
            throw PlayerRepositoryException{"Inwalid number argument, allowed [0,3]"};
        switch (i) {
            case (0):
                sign = '@';
                break;
            case (1):
                sign = '%';
                break;
            case (2):
                sign = '+';
                break;
            case (3):
                sign = '*';
                break;
        }
        if(sign==' ') throw PlayerRepositoryException{ " Sign not set correctly"};
    return sign;
}



