

#include "model/InteractiveFieldAndMonsterRepository.h"
#include "model/WorldRepository.h"
#include "model/InteractionWithMonster.h"
#include <model/PlayerRepository.h>
#include <iostream>

using namespace std;

InteractiveFieldAndMonsterRepository::InteractiveFieldAndMonsterRepository(WorldRepository *world_repository, PlayerRepository* player_repository,
                                                                           unsigned int number_of_monsters,
                                                                           unsigned int number_of_interactive_fields, const char &monster_representation, const char &interactive_field_representation)
                                                                           : world_repository(world_repository), player_repository(player_repository)
{
    monster_interaction = new InteractionWithMonster("You meet monster", player_repository);
    random_interaction =  new RandomInteraction ("Random Interaction", player_repository);

    srand(time(NULL));

    int max_x = world_repository->get_world_size_x();
    int max_y = world_repository->get_world_size_y();

    int x,y;

    while (number_of_monsters > 0)
{
        x = rand()%max_x - 2;
        y = rand()%max_y;


        if (world_repository->is_field_empty(x,y))
        {
            if (is_field_empty(x,y,true, true))
            {
                create_monster(x, y, monster_representation);
                number_of_monsters--;
            }
        }
    }

    while (number_of_interactive_fields > 0)
    {
        x = rand()%max_x - 2;
        y = rand()%max_y;
    if (world_repository->is_field_empty(x,y))
        {
            if (is_field_empty(x,y,true, true))
            {
                create_interactive_field(x, y, interactive_field_representation);
                number_of_interactive_fields--;
            }

        }
    }

}

InteractiveFieldAndMonsterRepository::InteractiveFieldAndMonsterRepository(WorldRepository *world_repository, PlayerRepository* player_repository) : world_repository(world_repository), player_repository(player_repository) {}

InteractiveFieldAndMonsterRepository::~InteractiveFieldAndMonsterRepository() {}

bool InteractiveFieldAndMonsterRepository::create_monster(const unsigned int &x, const unsigned int &y, const char &representation)
{
    if (!world_repository->is_field_empty(x,y))
        return false;

    if (!is_field_empty(x,y, true, false))
        return false;

    monster_interaction = new InteractionWithMonster("You meet monster",player_repository);
    MovableMonster *m = new MovableMonster(x,y, representation, true, monster_interaction);

    MonsterPtr p(m);

    monsters.push_back(p);

    return true;
}

bool InteractiveFieldAndMonsterRepository::create_interactive_field(const unsigned int &x, const unsigned int &y, const char &representation)
{
    if (!world_repository->is_field_empty(x,y))
        return false;

    if (!is_field_empty(x,y, false, true))
        return false;

    random_interaction = new RandomInteraction("Random", player_repository);
    InteractiveField *m = new InteractiveField(x,y,representation, true, random_interaction);

    InteractiveFieldPtr p(m);

    interactive_fields.push_back(p);

    return true;
}


const Field * InteractiveFieldAndMonsterRepository::get_current_monster_or_interactive_field() const
{
    shared_ptr<Player> p = player_repository->get_current_player();
   const Player* pl = p.get();

    int x = pl->get_x();
    int y = pl->get_y();

    return find_monster_or_interactive_field(x,y);

}

const Field *InteractiveFieldAndMonsterRepository::find_monster_or_interactive_field(int x, int y) const {

    for (const auto &i : monsters)
    {
        if (i->get_x() == x && i->get_y() == y)
            return i.get();
    }
    for (const auto &i : interactive_fields)
{
        if (i->get_x() == x && i->get_y() == y)
            return i.get();
    }

    return nullptr;
}

bool InteractiveFieldAndMonsterRepository::is_field_empty(int x, int y, bool find_monsters, bool find_interactive_field) const {

    if (find_monsters) {
        auto i = world_repository->find_field_<MonsterPtr>(x,y,monsters);

        if (i != monsters.end())
            return false;
    }
    if (find_interactive_field) {
        auto i2 = world_repository->find_field_<InteractiveFieldPtr>(x,y,interactive_fields);

        if (i2 != interactive_fields.end())
            return false;

    }
    return true;

}

void InteractiveFieldAndMonsterRepository::move_monsters_randomly()
{
    srand(time(NULL));
    int direction[4] = {1,2};
    int values[2] = {-1,1};
    int d,v;
    for (auto &i : monsters)
    {
        d = direction[rand()%2];
        v = values[rand()%2];

        switch (d)
        {
            case 1:

                if (world_repository->is_field_empty(i->get_x()+v, i->get_y()))
                {
                    if (is_field_empty(i->get_x()+v, i->get_y(), true, true))
                    {
                        i->set_x(i->get_x()+v);
                    }
                }

                break;

            case 2:

                if (world_repository->is_field_empty(i->get_x(), i->get_y() + v))
                {
                    if (is_field_empty(i->get_x(), i->get_y() + v, true, true))
                    {
                        i->set_y(i->get_y()+v);
                    }
                }
                break;
        }
    }
}

const std::vector<InteractiveFieldPtr> & InteractiveFieldAndMonsterRepository::get_interactive_fields() const
{
    return interactive_fields;
}

const std::vector<MonsterPtr>& InteractiveFieldAndMonsterRepository::get_monsters() const
{
    return monsters;
}

