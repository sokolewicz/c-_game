
#include "model/MovableObject.h"

MovableObject::MovableObject( int x, int y, char representation, bool enable_movement) : Field(x, y, representation,
                                                                                                         enable_movement) {
    set_enable_movement(true);

}

MovableObject::~MovableObject() {

}

void MovableObject::set_x( int offsetX) {
    x=offsetX;

}

void MovableObject::set_y( int offsetY) {
    y=offsetY;
}


