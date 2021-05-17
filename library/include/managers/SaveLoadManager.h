//
// Created by student on 12.06.2020.
//

#include <iostream>
#include "InputManager.h"


class PlayerRepository;
class WorldRepository;
class InteractiveFieldAndMonsterRepository;
class SaveLoadManager {

private:
    WorldRepository* world_repository;
    PlayerRepository* player_repository;
    InteractiveFieldAndMonsterRepository* monster_repository;
    InputManager* input_manager;
    const char* player_file_name = "pfn";
    const char* monster_file_name = "mfn";
    const char* world_file_name = "wfn";
    const char* time_file_name = "tfn";
public:
    SaveLoadManager(WorldRepository* world_repo, PlayerRepository* player_repo, InteractiveFieldAndMonsterRepository* monsters_repo, InputManager* input_manager);
    ~SaveLoadManager();
    bool is_loading_game_available ();
    bool load_game ();
    bool save_game ();

    std::string load_starting_time ();
    void save_starting_time ();
    void clear_all ();
};


