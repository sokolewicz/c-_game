#ifndef OUTPUT_DEV_RANDOMINTERACTION_H
#define OUTPUT_DEV_RANDOMINTERACTION_H
#include "Interaction.h"
#include "PlayerRepository.h"

class RandomInteraction : public Interaction{


public:
    RandomInteraction( const std::string &message, PlayerRepository *playerRepository);
    virtual ~RandomInteraction();
    virtual std::string interact() override;
    void set_rand_message();

};


#endif //OUTPUT_DEV_RANDOMINTERACTION_H
