

#ifndef FIELD_DEV_MOVABLEMONSTER_H
#define FIELD_DEV_MOVABLEMONSTER_H


#include <model/Interaction.h>
#include <model/MovableObject.h>

class MovableMonster: public MovableObject {
private:
    Interaction * interaction;
public:
    MovableMonster( int x,  int y, char representation, bool enable_movement, Interaction * interaction);
    virtual ~MovableMonster();
   std::string get_all_info() ;
    virtual std::string get_object_type() override ;

    Interaction *get_interaction() const override;

};


#endif //FIELD_DEV_MOVABLEMONSTER_H
