#ifndef LIBRARY_INTERACTIONWITHMONSTER_H
#define LIBRARY_INTERACTIONWITHMONSTER_H
#include <model/Interaction.h>

class InteractionWithMonster: public Interaction {
public:
    InteractionWithMonster(const std::string &message, PlayerRepository *playerRepository);
    virtual ~InteractionWithMonster();
    virtual std::string interact () override;
};


#endif //LIBRARY_INTERACTIONWITHMONSTER_H
