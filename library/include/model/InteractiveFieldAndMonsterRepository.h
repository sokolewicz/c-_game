//
// Created by student on 10.06.2020.
//

#ifndef GAMEMANAGER_PART3_DEV_INTERACTIVEFIELDANDMONSTERREPOSITORY_H
#define GAMEMANAGER_PART3_DEV_INTERACTIVEFIELDANDMONSTERREPOSITORY_H

#include <boost/shared_ptr.hpp>
#include "MovableMonster.h"
#include "InteractiveField.h"
#include "RandomInteraction.h"
#include "WorldRepository.h"
#include <vector>

typedef std::shared_ptr<MovableMonster> MonsterPtr;
typedef std::shared_ptr<InteractiveField> InteractiveFieldPtr;
class PlayerRepository;
class WorldRepository;
class InteractionWithMonster;
class InteractiveFieldAndMonsterRepository {


private:
    std::vector<MonsterPtr> monsters;
    std::vector<InteractiveFieldPtr> interactive_fields;
    InteractionWithMonster* monster_interaction;
    RandomInteraction* random_interaction;
    WorldRepository* world_repository;
    PlayerRepository* player_repository;
    bool is_field_empty (int x, int y, bool find_monsters = false, bool find_interactive_field = false) const;
    const Field * find_monster_or_interactive_field (int x, int y) const;


    const Field *find_monster_or_interactive_field() const;

public:
    InteractiveFieldAndMonsterRepository (WorldRepository * world_repository, PlayerRepository* player_repository);
    InteractiveFieldAndMonsterRepository (WorldRepository* world_repository, PlayerRepository* player_repository, unsigned int number_of_monsters, unsigned int number_of_interactive_fields, const char &monster_representation, const char &interactive_field_representation);
    ~InteractiveFieldAndMonsterRepository();
    bool create_monster (unsigned const int &x, unsigned const int &y, const char &representation);
    bool create_interactive_field (unsigned const int &x, unsigned const int &y, const char &representation);
    const Field* get_current_monster_or_interactive_field () const;
    void move_monsters_randomly ();
    const std::vector<InteractiveFieldPtr> &get_interactive_fields () const;
    const std::vector<MonsterPtr> &get_monsters () const;


};


#endif //GAMEMANAGER_PART3_DEV_INTERACTIVEFIELDANDMONSTERREPOSITORY_H
