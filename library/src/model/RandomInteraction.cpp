
#include "model/RandomInteraction.h"
#include <sstream>
#include <iostream>

RandomInteraction::RandomInteraction( const std::string &message, PlayerRepository *playerRepository)
        : Interaction(message, playerRepository)
{
this->set_rand_message();
}
std::string RandomInteraction::interact() {
    int a;

    if(playerRepository== nullptr){
        throw InteractionException{"Cannot perform interaction without PlayerRepository"};
    }
    PlayerPtr current_player=playerRepository->get_current_player();
    {
        if(this->get_message()=="You found some stars ")
        {
             a=(rand ()%500)+1;
            current_player->set_stars(a);
        }
        if(this->get_message()=="You got robbed and lost some stars :(")
        {
            a=(rand ()%500)-501;
            current_player->set_stars(a);
        }
        if(this->get_message()=="You lost a little bit of health level, better take care of yourself next time")
        {
            a=(rand ()%10)-11;
            current_player->set_health(a);
        }
        if(this->get_message()=="You found magic cure, your health level increased")
        {
            a=(rand ()%10)+1;
            current_player->set_health(a);
        }
        if(this->get_message()=="We decided to teleport you, becasuse why not?")
        {
            int number_of_attempts = 10;
            int b;

            while (number_of_attempts > 0) {
                a = (rand() % 10) - 5;
                b = (rand() % 10) - 5;

                        if (playerRepository->move_current_player(a, b))
                            return get_message();
                        number_of_attempts--;
            }

            return "We wanted to teleport You but maybe not";
        }

    }
    return get_message();
}

RandomInteraction::~RandomInteraction() {

}
void RandomInteraction::set_rand_message() {
     unsigned int a=random()%5;
   this->set_valid_message(a);

}




