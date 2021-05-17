
#ifndef LIBRARY_PLAYERREPOSITORY_H
#define LIBRARY_PLAYERREPOSITORY_H
#include "Player.h"
#include <vector>
#include <exception>
class WorldRepository;
class GameManager;
class PlayerRepositoryException: public std::logic_error {
public:
explicit PlayerRepositoryException(const std::string& what_arg) : std::logic_error(what_arg) {}
};

class PlayerRepository {
private:
    std::vector<PlayerPtr> players;
    void (GameManager::*call_back_function)(bool moved );
    WorldRepository *worldRepository;
    GameManager* game_manager;
public:
    PlayerRepository (void (GameManager::*call_back_function)(bool moved ), GameManager* game_manager, WorldRepository* world_repository);
    PlayerRepository(unsigned int number_of_players,  const std::vector<std::string> &players_names, WorldRepository *worldRepository, void (GameManager::*call_back_function)(bool moved ), GameManager* game_manager);
    virtual ~PlayerRepository();
    bool create_player(int x,int y, char representation,const std::string &name, bool current_player, int health, int stars, int id);
    unsigned int get_players_number ();
    PlayerPtr get_current_player();//sprawdza, którego gracza jest aktualnie kolej
    void change_to_next_player(); //zmienia wartości turn, tak aby była kolejka następnego gracza
    void remove_current_player();
    bool move_current_player(int offsetX, int offsetY);
    const std::vector<PlayerPtr> &get_players () const;
    PlayerPtr get_player(unsigned int id) const; //zwraca gracza o kontretnym id
    bool current_player_is_dead ();
    static const char rand_representation(unsigned int i);
};


#endif //LIBRARY_PLAYERREPOSITORY_H
