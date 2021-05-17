#include "model/WorldRepository.h"
#include <cstdlib>
#include <time.h>
#include <list>
#include <iostream>

using namespace std;

WorldRepository::WorldRepository(PlayerRepository** player_repo) : player_repository(player_repo) { world_size_x = world_size_y = 0;}

WorldRepository::WorldRepository(unsigned int world_size_x, unsigned int world_size_y,
                                 unsigned int number_of_obstacles, PlayerRepository** player_repo) : world_size_x(world_size_x), world_size_y(world_size_y), player_repository(player_repo)
{

    finish_x = 1;
    finish_y = world_size_y/2;

    for (int i=0;i<world_size_x;i++)
    {
        for (int j = 0; j<world_size_y;j++)
        {

            if ( i == world_size_x-1 ||i==0 || j == world_size_y-1||j==0)
            {
                Field* field = new Field(i,j,'#',false);
                FieldPtr ptr(field);
                fields.push_back(ptr);
           }
            else
            {
                if (i == finish_x && j == finish_y)
                {
                    Field* field = new Field(i,j,'F', true);
                    FieldPtr ptr(field);

                    fields.push_back(ptr);
                } else
                {
                    Field* field = new Field(i,j,'_', true);
                    FieldPtr ptr(field);
                    fields.push_back(ptr);
                }
            }


        }
    }

    srand(time(NULL));

    while (number_of_obstacles > 0)
    {
        int x = rand()%(world_size_x-2) ;
        int y = rand()%(world_size_y-1) ;

        auto i = find_field_<FieldPtr>(x,y, fields);
        if (i->get()->is_enable_movement())
        {
            i->get()->set_enable_movement(false);
            i->get()->set_representation('#');
            number_of_obstacles--;
        }
    }

}

WorldRepository::~WorldRepository() {}

unsigned int WorldRepository::get_world_size_x() const
{
    return world_size_x;
}

unsigned int WorldRepository::get_world_size_y() const
{
    return world_size_y;
}

bool WorldRepository::is_field_empty(unsigned int destination_x, unsigned int destination_y) const
{
    vector<FieldPtr>::const_iterator i = find_field_<FieldPtr>(destination_x, destination_y, fields);

    if (i != fields.end()) {


        return i->get()->is_enable_movement();
    }

    if (fields.size() < world_size_y*world_size_x || fields.size() > world_size_y*world_size_x) return false;

    return true;
}

bool WorldRepository::create_field(unsigned int x, unsigned int y, char representation, bool enable_movement)
{
    vector<FieldPtr>::const_iterator i = find_field_<FieldPtr>(x, y, fields);

    if (i != fields.end()) {
        return false;
    }


    Field* field = new Field(x,y,representation,enable_movement);
    FieldPtr ptr(field);

    fields.push_back(ptr);

    return true;
}

bool WorldRepository::set_new_world_size(unsigned int world_size_x, unsigned int world_size_y)
{
    this->world_size_x = world_size_x;
    this->world_size_y = world_size_y;

    finish_x = 0;
    finish_y = world_size_y/2;
}


const std::vector<FieldPtr> &WorldRepository::get_fields() const {
    return fields;
}

unsigned int WorldRepository::get_number_of_fields() const {
    return fields.size();
}


FieldPtr WorldRepository::get_field(unsigned int i) const {
    if (i<get_number_of_fields())
    {
        return fields [i];
    }

}

bool WorldRepository::is_end()
{
    if ((*player_repository)->get_players_number() == 1)
        return true;

    PlayerPtr p = (*player_repository)->get_current_player();

    return (p->get_x() == finish_x && p->get_y() == finish_y);

}

void WorldRepository::player_has_been_moved(bool moved) {

    this->moved = moved;
}

