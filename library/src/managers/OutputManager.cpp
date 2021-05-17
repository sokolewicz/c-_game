
#include <iostream>
#include "managers/OutputManager.h"
#include <model/PlayerRepository.h>
#include <model/InteractiveFieldAndMonsterRepository.h>
#include <model/WorldRepository.h>


OutputManager::OutputManager(PlayerRepository *playerRepository, WorldRepository *worldRepository, InteractiveFieldAndMonsterRepository *monsters)
:playerRepository(playerRepository), worldRepository(worldRepository), monstersRepository(monsters) {

}

OutputManager::~OutputManager() {

}

void OutputManager::clear_screen() {
  system ("clear");
}

void OutputManager::show_board() {
    unsigned  int x_size=worldRepository->get_world_size_x();
    unsigned int y_size=worldRepository->get_world_size_y();
    char board [x_size][y_size];
    std::vector<MonsterPtr>::const_iterator m;
    std::vector<InteractiveFieldPtr>::const_iterator in;
    for(int i=0;i<x_size;i++)
    {
        for (int j = 0; j <y_size; j++)
        {
                board [i][j]=worldRepository->find_field_<FieldPtr>(i,j, worldRepository->get_fields())->get()->get_representation();

                m = worldRepository->find_field_<MonsterPtr>(i,j,monstersRepository->get_monsters());

                if (m != monstersRepository->get_monsters().end())
                    board[i][j] = m->get()->get_representation();

                else
                {
                    in = worldRepository->find_field_<InteractiveFieldPtr>(i,j,monstersRepository->get_interactive_fields());

                    if (in != monstersRepository->get_interactive_fields().end())
                        board[i][j] = in->get()->get_representation();
                }
        }


    }
    char sign;

        for (int i = 0; i < x_size; i++) {
            for (int j = 0; j <y_size; j++) {

                sign = board[i][j];
                    for (PlayerPtr p:playerRepository->get_players()) {
                        if (p->get_x() == i && p->get_y() == j)
                            sign = p->get_representation();
                    }

                std::cout << sign;

            }
            std::cout <<std::endl;

        }
    }



