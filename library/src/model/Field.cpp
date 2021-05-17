
#include <sstream>
#include "../../include/model/Field.h"

Field::Field(int x, int y, char representation, bool enable_movement): x(x), y(y), representation(representation), enable_movement(enable_movement)
{

}

Field::~Field() {
    if (get_interaction() != nullptr)
        delete get_interaction();
}
const int Field::get_x() const{
    return x;
}

const int Field::get_y() const{
    return y;
}

 std::string Field::get_coordinates() const {
    std::stringstream coordinates;
    coordinates<<"("<<x<<", "<<y<<")";
    return coordinates.str();
}

 bool Field::is_enable_movement() const {
    return enable_movement;
}

const char Field::get_representation() const {
    return representation;
}

 std::string Field::get_all_info() const {
    std::stringstream info;
    info<<"Field "<<this->get_coordinates()<<" "<<representation<<" "<<"enable movement= "<<enable_movement;
    return info.str();
}

 Interaction *Field::get_interaction() const {
    return nullptr;
}

void Field::set_enable_movement(bool enable)
{
    enable_movement = enable;
}

void Field::set_representation(char new_representation)
{
    this->representation = new_representation;
}

