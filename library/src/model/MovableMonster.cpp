#include <sstream>
#include "model/MovableMonster.h"

MovableMonster::MovableMonster( int x, int y, char representation, bool enable_movement,
                                Interaction *interaction): MovableObject(x,y,representation,enable_movement), interaction(interaction) {

}

MovableMonster::~MovableMonster() {

}

 std::string MovableMonster::get_all_info() {
    std::stringstream info;
    std::string Fieldinfo=Field::get_all_info();
    info<<this->get_object_type()<<" "<<Fieldinfo.substr(Fieldinfo.find_first_of(" \t")+1)<<" "<<interaction;
    return info.str();
}
std::string MovableMonster::get_object_type() {
   std:: string type="Monster";
    return type;
}

Interaction *MovableMonster::get_interaction() const {
    return interaction;
}
