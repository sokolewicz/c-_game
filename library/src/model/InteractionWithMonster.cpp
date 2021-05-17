#include "model/InteractionWithMonster.h"
#include <model/PlayerRepository.h>
InteractionWithMonster::InteractionWithMonster(const std::string &message, PlayerRepository* playerRepository): Interaction(message, playerRepository) {
    this->set_valid_message(5);

}

InteractionWithMonster::~InteractionWithMonster() {

}

std::string InteractionWithMonster::interact() {
    int a=(rand()%50)-50;
    if(playerRepository== nullptr){
        throw InteractionException{"Cannot perform interaction without PlayerRepository"};
    }
    playerRepository->get_current_player()->set_health(a);
    return get_message();
}

