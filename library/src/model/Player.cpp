#include <sstream>
#include "model/Player.h"



Player::Player(int x, int y, char representation, bool enable_movement, const std::string &name, unsigned int health, int stars,
               unsigned int id, bool turn):
        MovableObject( x, y, representation, enable_movement), name(name), health(100), stars(0), id(id), turn(turn) {

}


Player::~Player() {

}

const unsigned int Player::get_health() const {
    return health;
}

const  int Player::get_stars() const {
    return stars;
}

const std::string Player::get_name() const{
    return name;
}

void Player::set_health( int offset_health) {
health+=offset_health;
}

void Player::set_stars( int offset_stars) {
    stars+=offset_stars;

}


 std::string Player::get_object_type() {
    std::string type="Player";
    return type;
}

 unsigned int Player::get_id() const{
    return id;
}

bool Player::is_turn() {
    return turn;
}

void Player::set_turn(bool new_turn) {

turn=new_turn;
}

 std::string Player::info() const {

    std::stringstream s;

    s << "Name: " <<get_name()<<" Id: "<<get_id()<<" Representation: "<<get_representation()<<" Health: "<<get_health()<<" Stars: "<<get_stars()<<" Position: "<<get_coordinates()<<std::endl;

    return s.str();
}
