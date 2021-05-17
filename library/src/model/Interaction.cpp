

#include <model/InteractionWithMonster.h>
#include "../../include/model/Interaction.h"
#include <model/PlayerRepository.h>



Interaction ::Interaction (const std::string &message, PlayerRepository* playerRepository):message(message), playerRepository(playerRepository)
{

}

Interaction::~Interaction() {

}


const std::string& Interaction::get_message() const {
    return message;
}


void Interaction::set_valid_message(unsigned int num) {
   if (num>5||num<0) throw InteractionException{"Invalid number, allowed [0,5]"};
  auto lambda =[num]()-> std::string{

        for (auto &[i,j]:std::map<int,std::string> {{0,"You found some stars "},
                                         {1,"You got robbed and lost some stars :("},
                                         { 2, "You lost a little bit of health level, better take care of yourself next time"},
                                         {3,"You found magic cure, your health level increased"},
                                         {4,"We decided to teleport you, becasuse why not?"},
                                         {5, "You meet monster"}} )

            if (i==num)
                return j;

  };
       message = lambda();
}

