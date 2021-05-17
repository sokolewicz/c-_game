//
// Created by student on 03.06.2020.
//

#ifndef WORKSHOP_GAMEMANAGER_H
#define WORKSHOP_GAMEMANAGER_H

#include <boost/shared_ptr.hpp>
#include <boost/date_time.hpp>
#include "OutputManager.h"

class SaveLoadManager;
class PlayerRepository;
class WorldRepository;
class InteractiveFieldAndMonsterRepository;
class InputManager;
template <class T> using PtrTemplate = std::shared_ptr<T>;
typedef boost::posix_time::ptime date_time;
class GameManager {



private:

    PtrTemplate <WorldRepository> world_repository;
    PtrTemplate <PlayerRepository> player_repository;
    PtrTemplate <InteractiveFieldAndMonsterRepository> monster_and_interactive_field_repository;
    PtrTemplate <InputManager> input_manager;
    PtrTemplate <OutputManager> output_manager;
    PtrTemplate <SaveLoadManager> save_load_manager;
    bool player_has_been_moved;
    date_time starting_time;


    void play();
    void end_game();
    void win ();
    void menu(int option);
    void set_player_has_been_moved (bool moved);

public:
    GameManager (InputManager* input_manager, int option);
    ~GameManager();


};


#endif //WORKSHOP_GAMEMANAGER_H
