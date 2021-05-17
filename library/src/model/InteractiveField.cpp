#include <sstream>
#include "model/InteractiveField.h"

InteractiveField::InteractiveField(int x, int y, char representation, bool enable_movement,
                                   Interaction *interaction) : Field(x,y,representation,enable_movement), interaction(interaction){

}

InteractiveField::~InteractiveField() {

}
const std::string InteractiveField::get_all_info() {
    std::stringstream info;
    std::string Fieldinfo=Field::get_all_info();
    info<<"Interactive Field "<<Fieldinfo.substr(Fieldinfo.find_first_of(" \t")+1)<<" interaction "<<interaction;
    return info.str();
}

Interaction *InteractiveField::get_interaction() const {
    return interaction;
}
