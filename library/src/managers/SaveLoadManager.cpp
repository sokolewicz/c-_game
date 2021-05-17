//
// Created by student on 12.06.2020.
//

#include "managers/SaveLoadManager.h"
#include <model/PlayerRepository.h>
#include <model/WorldRepository.h>
#include <model/InteractiveFieldAndMonsterRepository.h>
#include <fstream>
#include <boost/date_time.hpp>

using namespace std;

SaveLoadManager::SaveLoadManager(WorldRepository *world_repo, PlayerRepository *player_repo,
                                 InteractiveFieldAndMonsterRepository *monsters_repo,  InputManager* input_manager)
                                 : world_repository(world_repo), player_repository(player_repo), monster_repository(monsters_repo), input_manager(input_manager){}

SaveLoadManager::~SaveLoadManager() {}

bool SaveLoadManager::save_game()
{
    ofstream file;

    try {

        file.open(world_file_name, ios::trunc);
    }
    catch (std::ostream::failure failure)
    {
        string s = "Unable to open file: ";
        s += world_file_name;
        s += "\n";
        s += failure.what();
        input_manager->show_message(s);
        return false;
    }

    file << world_repository->get_world_size_x() << " " <<world_repository->get_world_size_y() << "\n";

    for (const auto &i: world_repository->get_fields())
    {
        file << i->get_x() << " " << i->get_y() << " " << i->is_enable_movement() << " " << i->get_representation() << "\n";
    }

    file.close();

    try {

        file.open(player_file_name, ios::trunc);
    }
    catch (std::ostream::failure failure)
    {
        string s = "Unable to open file: ";
        s += player_file_name;
        s += "\n";
        s += failure.what();
        input_manager->show_message(s);
        return false;
    }


    for (const auto &i: player_repository->get_players())
    {
        file << i->get_x() << " " << i->get_y() << " " << i->get_representation() << " " << i->get_name() << " "<<i->is_turn() << " " <<i->get_health()
        << " " << i->get_stars() << " " << i->get_id() << "\n";
    }

    file.close();

    try {

        file.open(monster_file_name, ios::trunc);
    }
    catch (std::ostream::failure failure)
    {
        string s = "Unable to open file: ";
        s += monster_file_name;
        s += "\n";
        s += failure.what();
        input_manager->show_message(s);
        return false;
    }

    for (const auto &i: monster_repository->get_monsters())
    {
        file << i->get_x() << " " << i->get_y() << " " << i->get_representation() << 0 << "\n";
    }

    for (const auto &i: monster_repository->get_interactive_fields())
    {
        file << i->get_x() << " " << i->get_y() << " " << i->get_representation() << 1 << "\n";
    }

    file.close();

    return true;
}

bool SaveLoadManager::load_game()
{
    ifstream file;

    char representation;
    int x,y, type, health, stars, id;
    bool enable_movement;
    string name;
    bool turn;

    try {

        file.open(world_file_name);
    }
    catch (std::istream::failure failure)
    {
        string s = "Unable to open file: ";
        s += world_file_name;
        s += "\n";
        s += failure.what();
        input_manager->show_message(s);
        return false;
    }

    file >> x >> y;
    file.get();

    world_repository->set_new_world_size(x,y);

    while (!file.eof())
    {
        file >> x >> y >> enable_movement >> representation;
        file.get();

        world_repository->create_field(x,y,representation,enable_movement);
    }

    file.close();

    try {

        file.open(player_file_name);
    }
    catch (std::istream::failure failure)
    {
        string s = "Unable to open file: ";
        s += player_file_name;
        s += "\n";
        s += failure.what();
        input_manager->show_message(s);
        return false;
    }

    while (!file.eof())
    {
        file >> x >> y >> representation >> name >> turn >> health >> stars >> id;
        file.get();

        player_repository->create_player(x,y,representation,name,turn, health, stars, id);
    }

    file.close();

    try {

        file.open(monster_file_name);
    }
    catch (std::istream::failure failure)
    {
        string s = "Unable to open file: ";
        s += monster_file_name;
        s += "\n";
        s += failure.what();
        input_manager->show_message(s);
        return false;
    }

    while (!file.eof())
    {
        file >> x >> y >> representation >> type;
        file.get();

        if (type == 0)
        monster_repository->create_monster(x,y,representation);

        if (type == 1)
        monster_repository->create_interactive_field(x,y,representation);
    }

    file.close();

    return true;
}

bool SaveLoadManager::is_loading_game_available()
{
    fstream f1(world_file_name);
    fstream f2(player_file_name);
    fstream f3(monster_file_name);

    return (f1.good() && f2.good() && f3.good());

}

void SaveLoadManager::save_starting_time()
{
    ofstream file;
    try {

        file.open(time_file_name, ios::trunc);

    }
    catch (std::istream::failure failure)
    {
        string s = "Unable to open file: ";
        s += time_file_name;
        s += "\n";
        s += failure.what();
        input_manager->show_message(s);
        return;
    }

    file<<boost::posix_time::second_clock::local_time();
    file.close();
}

std::string SaveLoadManager::load_starting_time()
{
    ifstream file;
    try {

        file.open(time_file_name);

    }
    catch (std::istream::failure failure)
    {
        string s = "Unable to open file: ";
        s += time_file_name;
        s += "\n";
        s += failure.what();
        input_manager->show_message(s);
        return "0";
    }
    string s;
    getline (file, s);
    return s;
}

void SaveLoadManager::clear_all()
{
    remove(world_file_name);
    remove(monster_file_name);
    remove(world_file_name);
    remove(time_file_name);
}